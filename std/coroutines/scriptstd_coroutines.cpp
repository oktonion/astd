
#include "scriptstd_coroutines.h"


#include <cassert>
#include <string>
#include <cstring>
#include <map>


BEGIN_AS_NAMESPACE
extern const asPWORD CONTEXT_MGR;

namespace astd {
    struct gc_reference {
        gc_reference(asITypeInfo & type_info)
            : gc()
            , ref()
            , type()
        { 
            gc.flag = false;
            ref.count = 1;
            type.info = (static_cast<void>(type_info.AddRef()), &type_info);
        }
        ~gc_reference() {
            type.info->Release();
        }

        virtual void enumrefs(asIScriptEngine* engine) = 0;
        virtual void releaserefs(asIScriptEngine* engine) = 0;
        
        void setgcflag() { gc.flag = true; }
        bool getgcflag() const { return gc.flag; }
        void addref() { gc.flag = false; asAtomicInc(ref.count); }
        void release() { gc.flag = false; asAtomicDec(ref.count); }
        int getrefcount() const { return ref.count; }

        struct meta {
            static const char* enumrefs_cstr() { return "void enumrefs(int&in)"; }
            static const char* releaserefs_cstr() { return "void releaserefs(int&in)"; }

            static const char* setgcflag_cstr() { return "void setgcflag()"; }
            static const char* getgcflag_cstr() { return "bool getgcflag()"; }
            static const char* addref_cstr() { return "void addref()"; }
            static const char* release_cstr() { return "void release()"; }
            static const char* getrefcount_cstr() { return "int getrefcount()"; }
        };

        template<class T>
        static bool register_behaviours(asIScriptEngine& engine, const char *type_cstr = T::meta::type_cstr()) throw()
        {
            typedef T type;
            int r = 0;

            r = engine.RegisterObjectBehaviour(
                type_cstr,
                asBEHAVE_ADDREF,
                type::meta::addref_cstr(),
                asMETHODPR(type, addref, (), void),
                asCALL_THISCALL
            ); if (r >= 0)

            r = engine.RegisterObjectBehaviour(
                type_cstr,
                asBEHAVE_RELEASE,
                type::meta::release_cstr(),
                asMETHODPR(type, release, (), void),
                asCALL_THISCALL
            ); if (r >= 0)

            r = engine.RegisterObjectBehaviour(
                type_cstr,
                asBEHAVE_GETREFCOUNT,
                type::meta::getrefcount_cstr(),
                asMETHODPR(type, getrefcount, () const, int),
                asCALL_THISCALL
            ); if (r >= 0)

            r = engine.RegisterObjectBehaviour(
                type_cstr,
                asBEHAVE_SETGCFLAG,
                type::meta::setgcflag_cstr(),
                asMETHODPR(type, setgcflag, (), void),
                asCALL_THISCALL
            ); if (r >= 0)

            r = engine.RegisterObjectBehaviour(
                type_cstr,
                asBEHAVE_GETGCFLAG,
                type::meta::getgcflag_cstr(),
                asMETHODPR(type, getgcflag, () const, bool),
                asCALL_THISCALL
            ); if (r >= 0)

            r = engine.RegisterObjectBehaviour(
                type_cstr,
                asBEHAVE_ENUMREFS,
                type::meta::enumrefs_cstr(),
                asMETHODPR(type, enumrefs, (asIScriptEngine*), void),
                asCALL_THISCALL
            ); if (r >= 0)

            r = engine.RegisterObjectBehaviour(
                type_cstr,
                asBEHAVE_RELEASEREFS,
                type::meta::releaserefs_cstr(),
                asMETHODPR(type, releaserefs, (asIScriptEngine*), void),
                asCALL_THISCALL
            ); if (r >= 0)
                return true;
            return false;
        }
    protected:

        const asITypeInfo& type_info() const {
            return *type.info;
        }

    private:
        struct {
            bool flag;
        } gc;
        struct {
            mutable int count;
        } ref;
        struct {
            asITypeInfo* info;
        } type;
    };
}

namespace astd {

    namespace context {
        static bool throw_exception(const char* message, asIScriptContext* ctx = asGetActiveContext()) throw() {
            if (ctx)
                ctx->SetException(message);
            return !!ctx;
        }
    }



    struct coroutine_state {
        enum { stack_size = 1 };
        struct {
            asDWORD             stackFramePointer;
            asIScriptFunction* currentFunction;
            asDWORD             programPointer;
            asDWORD             stackPointer;
            asDWORD             stackIndex;
        } call_state_reg[stack_size];

        struct {
            asIScriptFunction* callingSystemFunction;
            asIScriptFunction* initialFunction;
            asDWORD             originalStackPointer;
            asDWORD             argumentSize;
            asQWORD             valueRegister;
            void* objectRegister;
            asITypeInfo* objectRegisterType;
        } state_reg[stack_size];

        struct {
            struct var {
                const char* name; 
                int typeId; 
                asETypeModifiers typeModifiers; 
                bool isVarOnHeap; 
                int stackOffset;
                void* address;
            };
            std::map<int, var> info;
            int count() const { return static_cast<int>(info.size()); }
            const var& operator[](std::size_t i) const { return info.at(i); }
        } var[stack_size];

        void* this_pointer[stack_size];

        static bool save(asIScriptContext& context, coroutine_state& state)
            // save state
        {
            for (int stacklvl = 0; stacklvl < sizeof(state.call_state_reg) / sizeof(state.call_state_reg[0]); ++stacklvl)
            {
                const int err = context.GetCallStateRegisters(
                    stacklvl,
                    &state.call_state_reg[stacklvl].stackFramePointer,
                    &state.call_state_reg[stacklvl].currentFunction,
                    &state.call_state_reg[stacklvl].programPointer,
                    &state.call_state_reg[stacklvl].stackPointer,
                    &state.call_state_reg[stacklvl].stackIndex
                );
                if (asSUCCESS != err) return false;
            }

            for (int stacklvl = 0; stacklvl < sizeof(state.var) / sizeof(state.var[0]); ++stacklvl)
            {
                for (int i = 0; i < context.GetVarCount(stacklvl); ++i)
                {
                    const int err = context.GetVar(i, stacklvl,
                        &state.var[stacklvl].info[i].name,
                        &state.var[stacklvl].info[i].typeId,
                        &state.var[stacklvl].info[i].typeModifiers,
                        &state.var[stacklvl].info[i].isVarOnHeap,
                        &state.var[stacklvl].info[i].stackOffset
                    );
                    if (asSUCCESS != err) return false;
                    state.var[stacklvl].info[i].address =
                        context.GetAddressOfVar(i, stacklvl, true, true);
                }
            }

            for (int stacklvl = 0; stacklvl < stack_size; ++stacklvl)
            {
                const int err = context.GetStateRegisters(
                    stacklvl,
                    &state.state_reg[stacklvl].callingSystemFunction,
                    &state.state_reg[stacklvl].initialFunction,
                    &state.state_reg[stacklvl].originalStackPointer,
                    &state.state_reg[stacklvl].argumentSize,
                    &state.state_reg[stacklvl].valueRegister,
                    &state.state_reg[stacklvl].objectRegister,
                    &state.state_reg[stacklvl].objectRegisterType
                );
                if (asSUCCESS != err) return false;
            }

            for (int stacklvl = 0; stacklvl < stack_size; ++stacklvl)
            {
                state.this_pointer[stacklvl] = context.GetThisPointer(stacklvl);
            }

            return true;
        }

        bool restore_callstack(asIScriptContext& context)
            // copy state
        {
            enum { co_routine_call };            
            
            int err = context.StartDeserialization();
            if (asSUCCESS != err) return false;

            if (context.GetCallstackSize() <= co_routine_call)
            {
                err = context.PushFunction(call_state_reg[co_routine_call].currentFunction, this_pointer[co_routine_call]);
                if (asSUCCESS != err) return false;
            }

            err = context.FinishDeserialization();
            if (asSUCCESS != err) return false;

            return true;
        }

        bool restore(asIScriptContext& context)
            // copy state
        {
            enum { co_routine_call };

            int err = context.StartDeserialization();
            if (asSUCCESS != err) return false;

            if (context.GetCallstackSize() <= co_routine_call)
            {
                err = context.PushFunction(call_state_reg[co_routine_call].currentFunction, this_pointer[co_routine_call]); 
                if (asSUCCESS != err) return false;
            }

            err = context.SetCallStateRegisters(
                co_routine_call,
                call_state_reg[co_routine_call].stackFramePointer,
                call_state_reg[co_routine_call].currentFunction,
                call_state_reg[co_routine_call].programPointer,
                call_state_reg[co_routine_call].stackPointer,
                call_state_reg[co_routine_call].stackIndex
            );
            if (asSUCCESS != err) return false;

            //for (int i = 0; i < var[co_routine_call].count(); ++i)
            //{
            //    const int err = context.GetVar(i, co_routine_call,
            //        &var[co_routine_call][i].name,
            //        &var[co_routine_call][i].typeId,
            //        &var[co_routine_call][i].typeModifiers,
            //        &var[co_routine_call][i].isVarOnHeap,
            //        &var[co_routine_call][i].stackOffset
            //    );
            //    if (asSUCCESS != err) return false;
            //    var[co_routine_call][i].address =
            //        context.GetAddressOfVar(i, co_routine_call, true, true);
            //}

            err = context.SetStateRegisters(
                co_routine_call,
                state_reg[co_routine_call].callingSystemFunction,
                state_reg[co_routine_call].initialFunction,
                state_reg[co_routine_call].originalStackPointer,
                state_reg[co_routine_call].argumentSize,
                state_reg[co_routine_call].valueRegister,
                state_reg[co_routine_call].objectRegister,
                state_reg[co_routine_call].objectRegisterType
            );
            if (asSUCCESS != err) return false;

            err = context.FinishDeserialization();
            if (asSUCCESS != err) return false;

            return true;
        }
    };

    struct coroutine_handle {
        bool done() const {
            return (asEXECUTION_FINISHED == context->GetState()
                || asEXECUTION_ABORTED == context->GetState());
        }

        operator bool() const {
            return !done();
        }

        void resume() const {
            if (asEXECUTION_SUSPENDED == context->GetState())
                if (!done()) 
                    context->Execute();
        }

        void operator()() const { return resume(); }

        coroutine_handle(asIScriptContext& context = 
            (static_cast<void>(assert(asGetActiveContext() != NULL)), *asGetActiveContext()))
            : context(&context)
        {}

    private:
        asIScriptContext* context;
    };

    struct awaitable_interface 
        : gc_reference
    {

        struct meta
            : gc_reference::meta
        {
            static const char* type_cstr() throw() { return "Awaitable"; }

            static const char* await_ready_cstr() throw() { return "bool await_ready() const"; }
            static const char* await_suspend_cstr() throw() { return "bool await_suspend()"; }
            static const char* await_resume_cstr() throw() { return "void" " await_resume() const"; }

            template<class T>
            static asSFuncPtr await_ready_ptr() throw() { return asMETHODPR(T, await_ready, () const, bool); }
            template<class T>
            static asSFuncPtr await_suspend_ptr() throw() { return asMETHODPR(T, await_suspend, (coroutine_handle), bool); }
            template<class T>
            static asSFuncPtr await_resume_ptr() throw() { return asMETHODPR(T, await_resume, () const, void); }
        };

        awaitable_interface(asITypeInfo& type_info)
            : gc_reference(type_info) {}
        
        template<class T>
        static bool register_methods(asIScriptEngine& engine, const char *type_cstr = T::meta::type_cstr()) throw()
        {
            typedef T type;
            int r = 0;

            r = engine.RegisterObjectMethod(
                type_cstr,
                type::meta::await_ready_cstr(),
                type::meta::template await_ready_ptr<type>(),
                asCALL_THISCALL
            ); if (r >= 0)

            
            r = engine.RegisterObjectMethod(
                type_cstr,
                type::meta::await_suspend_cstr(),
                type::meta::template await_suspend_ptr<type>(),
                asCALL_THISCALL
            ); if (r >= 0)

            r = engine.RegisterObjectMethod(
                type_cstr,
                type::meta::await_resume_cstr(),
                type::meta::template await_resume_ptr<type>(),
                asCALL_THISCALL
            ); if (r >= 0)
                return true;
            return false;
        }

        virtual bool await_ready() const = 0;

        virtual bool await_suspend(coroutine_handle) = 0;

        virtual void await_resume() const = 0;
    };
    
    struct awaitable
        : awaitable_interface
    {
        struct meta :
            awaitable_interface::meta {

            static const char* type_cstr() throw() { return "awaitable"; }
        };
        bool await_ready() const
        {
            return await_ready(type_info().GetMethodByDecl(awaitable::meta::await_ready_cstr()));
        }

        bool await_suspend(coroutine_handle)
        {
            return await_suspend(type_info().GetMethodByDecl(awaitable::meta::await_suspend_cstr()));
        }
        
        void await_resume() const
        {
            return await_resume(type_info().GetMethodByDecl(awaitable::meta::await_resume_cstr()));
        }

        awaitable(asIScriptObject& that) 
            : awaitable_interface((
                  static_cast<void>(assert(that.GetObjectType() != NULL)) // check for script object to have type
                , *that.GetObjectType()
            ))
        { }

    private:
        bool await_ready(asIScriptFunction* await_ready) const
        {
            return false;
        }
        bool await_suspend(asIScriptFunction* await_suspend)
        {
            return true;
        }
        void await_resume(asIScriptFunction* await_resume) const
        {
        }
    };

    struct async_wait_for_awaitable
        : awaitable_interface
    {
        void enumrefs(asIScriptEngine*) {}
        void releaserefs(asIScriptEngine*) {}

        bool await_ready() const
        {
            return milliSeconds <= 0;
        }

        bool await_suspend(coroutine_handle co_handle)
        {
            co_handle.resume();
            return false;
        }

        void await_resume() const
        { }

        struct meta 
            : awaitable_interface::meta
        {
#           define TYPE_NAME "async_wait_for_awaitable"
            static const char* type_cstr() throw() { return TYPE_NAME; }
            //static const char* create_uint_cstr() throw() { return TYPE_NAME"@ create(uint&in) explicit"; }
            static const char* awaitable_cast_cstr() throw() { return "Awaitable@ opImplCast()"; }
            static const char* awaitable_cast_const_cstr() throw() { return "const Awaitable@ opImplCast() const"; }
#           undef TYPE_NAME
        };

        async_wait_for_awaitable(asUINT milliSeconds, 
            asITypeInfo& type_info = (
                  static_cast<void>(assert(asGetActiveContext() != NULL)) // check for context to be active
                , static_cast<void>(assert(asGetActiveContext()->GetEngine() != NULL)) // check for engine to be running
                , static_cast<void>(assert(asGetActiveContext()->GetEngine()->GetTypeInfoByName(meta::type_cstr()) != NULL)) // check for type info registered with meta name
                , (*asGetActiveContext()->GetEngine()->GetTypeInfoByName(meta::type_cstr())) // getting type info by meta name
            )
        )
            : awaitable_interface(type_info)
            , milliSeconds(milliSeconds) 
        { }


        static async_wait_for_awaitable* create(asUINT milliSeconds) throw()
        {
            async_wait_for_awaitable* result = NULL;
            try {
                result = new async_wait_for_awaitable(milliSeconds);
                if (!result)
                {
                    context::throw_exception("async_wait_for_awaitable::ctor(uint&in): out of memory");
                }
            }
            catch (...)
            {
                context::throw_exception("async_wait_for_awaitable::ctor(uint&in): unknown exception");
            }
            return result;
        }

        static async_wait_for_awaitable* create(asUINT milliSeconds, asIScriptEngine &engine) throw()
        {
            async_wait_for_awaitable* result = NULL;
            try {
                asITypeInfo* type_info = engine.GetTypeInfoByName(async_wait_for_awaitable::meta::type_cstr());
                assert(type_info != NULL);
                result = new async_wait_for_awaitable(milliSeconds, *type_info);
                if (!result)
                {
                    context::throw_exception("async_wait_for_awaitable::ctor(uint&in): out of memory");
                }
            }
            catch (...)
            {
                context::throw_exception("async_wait_for_awaitable::ctor(uint&in): unknown exception");
            }
            return result;
        }

        static awaitable_interface* awaitable_cast(async_wait_for_awaitable& that) {
            that.addref();
            return &that;
        }

        asUINT milliSeconds;
    };

    static async_wait_for_awaitable* async_wait_for(asUINT milliSeconds)
    {
        typedef async_wait_for_awaitable awaitable;
        assert(asGetActiveContext() != NULL);
        asIScriptContext& context = *asGetActiveContext();
        assert(context.GetEngine() != NULL);
        asIScriptEngine& engine = *context.GetEngine();
        
        awaitable* result = awaitable::create(milliSeconds, engine);
        if (!result)
        {
            context.SetException("cannot instatiate async_wait_for awaitable");
            return NULL;
        }
        return result;
    }

    static void scr_co_yield()
    {
    }

    static void scr_co_await(asIScriptObject *that)
    {
        //auto *type_info = that->GetObjectType();
        //awaitable awaitable = that;
        //if (awaitable.await_ready())
    }

    static void cpp_co_await(awaitable_interface& that)
    {
        if (!that.await_ready())
        {
            // suspend coroutine
            {
                asIScriptContext* context = asGetActiveContext();

                // Suspend its execution. The VM will continue until the current
                // statement is finished and then return from the Execute() method
                context->Suspend();
            }

            typedef coroutine_handle handle_type;

            if (that.await_suspend(handle_type()))
            {
                
                return;
            }
        }

        that.await_resume();
    }

    static void scr_co_return_void() {

    }

    static void scr_co_return(void*, int) {

    }

    static void scr_co_routine() {
        asIScriptContext* context = asGetActiveContext();

        if (context->GetCallstackSize() < 2)
            return; // called co_routine for main or we are inside co_routine context

        // get return type info
        struct ReturnType {
            ReturnType(asIScriptFunction *func, asDWORD flags = 0)
                : id(func->GetReturnTypeId(&flags))
                , is_reference(0 != (flags& asTM_INOUTREF))
                , is_const_reference(
                    is_reference && 
                    (0 != (flags& asTM_CONST)) 
                )
            { }

            const int id;
            const bool is_reference;
            const bool is_const_reference;
        } call_func_return_type(context->GetFunction());

        asITypeInfo *call_func_return_type_info =
            context->GetEngine()->GetTypeInfoById(call_func_return_type.id);

        const bool check_for_promise = false;
        if (check_for_promise)
        {
            if (!call_func_return_type_info)
                return;


            // check if "ipromise" interface 
            if (!call_func_return_type_info->Implements(context->GetEngine()->GetTypeInfoByDecl("ipromise")))
                return;
        }


        coroutine_state state; 
        if (!coroutine_state::save(*context, state))
            return;

        asIScriptContext *co_context = context->GetEngine()->RequestContext();


        state.restore_callstack(*co_context);
        co_context->Execute();
    }
}

namespace astd_script { namespace {
    using namespace astd;
    namespace {
        template<int N>
        struct RegisterScriptStdFunctionHelperN {
            static int call(asIScriptEngine* engine) { return 0; } static void call_next(asIScriptEngine* engine) {}
        };

        template<int N>
        struct RegisterScriptStdFunctionHelper {
            static int call(asIScriptEngine* engine)
            {
                if (sizeof(RegisterScriptStdFunctionHelperN<N>::call(engine), short()) > sizeof(short))
                    return 0;
                RegisterScriptStdFunctionHelperN<N>::call_next(engine);
                return 1;
            }
        };

#       define RegisterScriptStdFunction(N) \
            template<> struct RegisterScriptStdFunctionHelperN<N> \
            { static void call(asIScriptEngine * engine); static void call_next(asIScriptEngine * engine) { call(engine); RegisterScriptStdFunctionHelper<N+1>::call(engine); } }; void RegisterScriptStdFunctionHelperN<N>::call

        enum {
            co_, sync_wait_for_awaitable, async_wait_for
        };

        RegisterScriptStdFunction(co_)(asIScriptEngine* engine)
        {
            int r = 0;
            std::string ns = engine->GetDefaultNamespace(); if (!ns.empty()) ns += "::";
            r = engine->SetDefaultNamespace(""); assert(r >= 0);

            if (!engine->GetGlobalFunctionByDecl("void co_routine()"))
                r = engine->RegisterGlobalFunction(
                    "void co_routine()",
                    asFUNCTION(astd::scr_co_routine),
                    asCALL_CDECL
                ); assert(r >= 0);

            if (!engine->GetGlobalFunctionByDecl("void co_yield()"))
                r = engine->RegisterGlobalFunction(
                    "void co_yield()",
                    asFUNCTION(astd::scr_co_yield),
                    asCALL_CDECL
                ); assert(r >= 0);

            if (!engine->GetGlobalFunctionByDecl("void co_await(awaitable@)"))
                r = engine->RegisterGlobalFunction(
                    "void co_await(awaitable@)",
                    asFUNCTION(astd::scr_co_await),
                    asCALL_CDECL
                ); assert(r >= 0);

            if (!engine->GetGlobalFunctionByDecl("void co_await(Awaitable@)")) // for C++ objects
                r = engine->RegisterGlobalFunction(
                    "void co_await(Awaitable@)",
                    asFUNCTION(astd::cpp_co_await),
                    asCALL_CDECL
                ); assert(r >= 0);

            if (!engine->GetGlobalFunctionByDecl("void co_return()"))
                r = engine->RegisterGlobalFunction(
                    "void co_return()",
                    asFUNCTION(astd::scr_co_return_void),
                    asCALL_CDECL
                ); assert(r >= 0);

            if (!engine->GetGlobalFunctionByDecl("void co_return(?&out result)"))
                r = engine->RegisterGlobalFunction(
                    "void co_return(?&out result)",
                    asFUNCTION(astd::scr_co_return),
                    asCALL_CDECL
                ); assert(r >= 0);

            r = engine->SetDefaultNamespace(ns.c_str()); assert(r >= 0);
        }

        RegisterScriptStdFunction(async_wait_for)(asIScriptEngine* engine)
        {
            int r = 0;
            std::string ns = engine->GetDefaultNamespace(); if (!ns.empty()) ns += "::";

            r = engine->RegisterGlobalFunction(
                (std::string(async_wait_for_awaitable::meta::type_cstr()) + "@ async_wait_for(uint ms)").c_str(),
                asFUNCTION(astd::async_wait_for),
                asCALL_CDECL
            ); assert(r >= 0);

            r = engine->SetDefaultNamespace(ns.c_str()); assert(r >= 0);
        }

        RegisterScriptStdFunction(sync_wait_for_awaitable)(asIScriptEngine* engine)
        {
            int r = 0;
            std::string ns = engine->GetDefaultNamespace(); if (!ns.empty()) ns += "::";

            typedef astd::async_wait_for_awaitable type;

            r = engine->RegisterObjectType(
                type::meta::type_cstr(),
                sizeof(type),
                asOBJ_REF | asOBJ_GC
            ); assert(r >= 0);
            // registering object behaviours
            {
                // registering garbage collect and reference behaviour
                static_cast<gc_reference*>(static_cast<type*>(NULL)); // static check for 'gc_reference' inheritance
                static_cast<gc_reference::meta*>(static_cast<type::meta*>(NULL)); // static check for 'gc_reference::meta' inheritance
                r = gc_reference::register_behaviours<type>(*engine) ? 0 : -1; assert(r >= 0);
            }

            // registering object relation functions (casting, inheritance etc.)
            {
                r = engine->RegisterObjectMethod(
                    type::meta::type_cstr(),
                    type::meta::awaitable_cast_cstr(),
                    asFUNCTION(&type::awaitable_cast),
                    asCALL_CDECL_OBJFIRST
                ); assert(r >= 0);

                r = engine->RegisterObjectMethod(
                    type::meta::type_cstr(),
                    type::meta::awaitable_cast_const_cstr(),
                    asFUNCTION(&type::awaitable_cast),
                    asCALL_CDECL_OBJFIRST
                ); assert(r >= 0);
            }

            // registering object member functions
            {
                // registering awaitable interface member functions
                static_cast<awaitable_interface*>(static_cast<type*>(NULL)); // static check for 'awaitable_interface' inheritance
                static_cast<awaitable_interface::meta*>(static_cast<type::meta*>(NULL)); // static check for 'awaitable_interface::meta' inheritance

                r = awaitable_interface::register_methods<type>(*engine) ? 0 : -1; assert(r >= 0);
            }


            r = engine->SetDefaultNamespace(ns.c_str()); assert(r >= 0);
        }


#       undef RegisterScriptStdFunction

        static void RegisterScriptStdFunctions(asIScriptEngine* engine)
        {
            typedef RegisterScriptStdFunctionHelper<0> functions;
            functions::call(engine);
        }
    }
}}

void RegisterScriptStd_Coroutines_Native(asIScriptEngine *engine)
{
    int r;  

    // registering awaitable script interface
    {
        typedef astd::awaitable::meta type_meta;
        r = engine->RegisterInterface(
            type_meta::type_cstr()
        ); assert(r >= 0);

        r = engine->RegisterInterfaceMethod(
            type_meta::type_cstr(),
            type_meta::await_ready_cstr()
        ); assert(r >= 0);

        r = engine->RegisterInterfaceMethod(
            type_meta::type_cstr(),
            type_meta::await_suspend_cstr()
        ); assert(r >= 0);

        r = engine->RegisterInterfaceMethod(
            type_meta::type_cstr(),
            type_meta::await_resume_cstr()
        ); assert(r >= 0);
    }

    // registering Awaitable base class
    {
        typedef astd::awaitable_interface type;
        typedef type::meta type_meta;
        r = engine->RegisterObjectType(
            type_meta::type_cstr(),
            sizeof(type),
            asOBJ_REF | asOBJ_GC
        ); assert(r >= 0);

        // registering object behaviours
        {
            // registering garbage collect and reference behaviour
            static_cast<astd::gc_reference*>(static_cast<type*>(NULL)); // static check for 'gc_reference' inheritance
            static_cast<astd::gc_reference::meta*>(static_cast<type::meta*>(NULL)); // static check for 'gc_reference::meta' inheritance
            r = astd::gc_reference::register_behaviours<type>(*engine) ? 0 : -1; assert(r >= 0);
        }
    }


    const std::string ns = engine->GetDefaultNamespace();

    r = engine->SetDefaultNamespace("std"); assert(r >= 0);

    astd_script::RegisterScriptStdFunctions(engine);

    r = engine->SetDefaultNamespace(""); assert(r >= 0);

    astd_script::RegisterScriptStdFunctions(engine);

    r = engine->SetDefaultNamespace(ns.c_str()); assert(r >= 0);
}


void RegisterScriptStd_Coroutines_Generic(asIScriptEngine *engine)
{
    int r;

    // double versions of the same
    //r = engine->RegisterGlobalFunction("double cos(double)", asFUNCTION(cos_generic), asCALL_GENERIC); assert( r >= 0 );
}

void RegisterScriptStd_Coroutines(asIScriptEngine *engine)
{
    if( strstr(asGetLibraryOptions(), "AS_MAX_PORTABILITY") )
        RegisterScriptStd_Coroutines_Generic(engine);
    else
        RegisterScriptStd_Coroutines_Native(engine);
}

END_AS_NAMESPACE



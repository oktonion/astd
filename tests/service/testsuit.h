#ifndef SERVICE_TESTSUITE_H
#define SERVICE_TESTSUITE_H

#define DOCTEST_CONFIG_NO_DELETED_FUNCTIONS
#define DOCTEST_CONFIG_NO_RVALUE_REFERENCES
#define DOCTEST_CONFIG_NO_NULLPTR
#define DOCTEST_CONFIG_NO_VARIADIC_MACROS
#define DOCTEST_CONFIG_NO_LONG_LONG
#define DOCTEST_CONFIG_NO_STATIC_ASSERT

#define DOCTEST_CONFIG_TREAT_CHAR_STAR_AS_STRING
#include "./../doctest/doctest.h"


#define SERVICE_CONCAT3(a, b) a##b
#define SERVICE_CONCAT2(a, b) SERVICE_CONCAT3(a,b)
#define SERVICE_CONCAT(a, b) SERVICE_CONCAT2(a,b)
#define SERVICE_WRAP(a) a

#ifndef ASTD_DIRECTORY
#   define ASTD_DIRECTORY ../std/
#endif
#ifndef ANGELSCRIPT_SDK_DIRECTORY
#   define ANGELSCRIPT_SDK_DIRECTORY ../angelscript/sdk/
#endif
#ifndef ANGELSCRIPT_ADD_ON_DIRECTORY
#   define ANGELSCRIPT_ADD_ON_DIRECTORY SERVICE_WRAP(ANGELSCRIPT_SDK_DIRECTORY)add_on/
#endif

#define SCRIPTSTD_H_PATH(name) <SERVICE_WRAP(SERVICE_WRAP(ASTD_DIRECTORY)name)SERVICE_CONCAT(/scriptstd_,name.h)>
#ifndef ANGELSCRIPT_LIB_H_PATH
#   define ANGELSCRIPT_LIB_H_PATH <SERVICE_WRAP(ANGELSCRIPT_SDK_DIRECTORY)angelscript/include/angelscript.h>
#endif
#define ANGELSCRIPT_LIB_SRC_H_PATH(name) <SERVICE_WRAP(ANGELSCRIPT_SDK_DIRECTORY)angelscript/source/name.h>
#define ANGELSCRIPT_ADD_ON_H_PATH(name) <SERVICE_WRAP(ANGELSCRIPT_ADD_ON_DIRECTORY)name/name.h>

#ifndef ANGELSCRIPT_SCRIPTBUILDER_H_PATH
#   define ANGELSCRIPT_SCRIPTBUILDER_H_PATH ANGELSCRIPT_ADD_ON_H_PATH(scriptbuilder)
#endif // ANGELSCRIPT_SCRIPTBUILDER_H_PATH

#include ANGELSCRIPT_LIB_SRC_H_PATH(as_scriptengine)
#include ANGELSCRIPT_SCRIPTBUILDER_H_PATH

#define SERVICE_MESSAGE_CALLBACK_WITH_ASSERTS(name) \
            static void name(const ANGELSCRIPT_NS_QUALIFIER asSMessageInfo* asSMessageInfo, void*)                                                                                     \
            {                                                                                                                                                                          \
                if (ANGELSCRIPT_NS_QUALIFIER asMSGTYPE_WARNING == asSMessageInfo->type)                                                                                                \
                {                                                                                                                                                                      \
                    DOCTEST_WARN_MESSAGE(asSMessageInfo, asSMessageInfo->section << " (" << asSMessageInfo->row << ", " << asSMessageInfo->col << ") : " << asSMessageInfo->message);  \
                }                                                                                                                                                                      \
                else if (ANGELSCRIPT_NS_QUALIFIER asMSGTYPE_INFORMATION == asSMessageInfo->type)                                                                                       \
                {                                                                                                                                                                      \
                    DOCTEST_MESSAGE(asSMessageInfo->section << " (" << asSMessageInfo->row << ", " << asSMessageInfo->col << ") : " << asSMessageInfo->message);                       \
                }                                                                                                                                                                      \
                else if (ANGELSCRIPT_NS_QUALIFIER asMSGTYPE_ERROR == asSMessageInfo->type)                                                                                             \
                {                                                                                                                                                                      \
                    DOCTEST_FAIL_CHECK(asSMessageInfo->section << " (" << asSMessageInfo->row << ", " << asSMessageInfo->col << ") : " << asSMessageInfo->message);                    \
                }                                                                                                                                                                      \
                else throw(asSMessageInfo->message);                                                                                                                                   \
            }

#ifdef AS_NAMESPACE_QUALIFIER
#   ifndef ANGELSCRIPT_NS_QUALIFIER
#       define ANGELSCRIPT_NS_QUALIFIER AS_NAMESPACE_QUALIFIER
#   endif // ANGELSCRIPT_NS_QUALIFIER
#else // ndef AS_NAMESPACE_QUALIFIER
#   ifndef ANGELSCRIPT_NS_QUALIFIER
#       define ANGELSCRIPT_NS_QUALIFIER AngelScript::
#   endif // ANGELSCRIPT_NS_QUALIFIER
#endif // AS_NAMESPACE_QUALIFIER

namespace testsuite {
    using ANGELSCRIPT_NS_QUALIFIER asSMessageInfo;
    using ANGELSCRIPT_NS_QUALIFIER asDWORD;
    using ANGELSCRIPT_NS_QUALIFIER asIScriptEngine;
    using ANGELSCRIPT_NS_QUALIFIER asIScriptContext;
    using ANGELSCRIPT_NS_QUALIFIER asCScriptEngine;
    using ANGELSCRIPT_NS_QUALIFIER asSFuncPtr;
    using ANGELSCRIPT_NS_QUALIFIER asSSystemFunctionInterface;
    using ANGELSCRIPT_NS_QUALIFIER CScriptBuilder;

    using ANGELSCRIPT_NS_QUALIFIER asCreateScriptEngine;
    
    namespace asECallConvTypes {
        using ANGELSCRIPT_NS_QUALIFIER asECallConvTypes;
        typedef asECallConvTypes type;
        using ANGELSCRIPT_NS_QUALIFIER asCALL_CDECL;
        using ANGELSCRIPT_NS_QUALIFIER asCALL_STDCALL;
        using ANGELSCRIPT_NS_QUALIFIER asCALL_THISCALL_ASGLOBAL;
        using ANGELSCRIPT_NS_QUALIFIER asCALL_THISCALL;
        using ANGELSCRIPT_NS_QUALIFIER asCALL_CDECL_OBJLAST;
        using ANGELSCRIPT_NS_QUALIFIER asCALL_CDECL_OBJFIRST;
        using ANGELSCRIPT_NS_QUALIFIER asCALL_GENERIC;
        using ANGELSCRIPT_NS_QUALIFIER asCALL_THISCALL_OBJLAST;
        using ANGELSCRIPT_NS_QUALIFIER asCALL_THISCALL_OBJFIRST;
    } using namespace asECallConvTypes;

    namespace asERetCodes {
        using ANGELSCRIPT_NS_QUALIFIER asERetCodes;
        typedef asERetCodes type;
        using ANGELSCRIPT_NS_QUALIFIER asNO_FUNCTION;
        using ANGELSCRIPT_NS_QUALIFIER asSUCCESS;
    } using namespace asERetCodes;


    namespace internalCallConv {
        using ANGELSCRIPT_NS_QUALIFIER internalCallConv;
        typedef internalCallConv type;
        using ANGELSCRIPT_NS_QUALIFIER ICC_GENERIC_FUNC;
        using ANGELSCRIPT_NS_QUALIFIER ICC_GENERIC_FUNC_RETURNINMEM; // never used
        using ANGELSCRIPT_NS_QUALIFIER ICC_CDECL;
        using ANGELSCRIPT_NS_QUALIFIER ICC_CDECL_RETURNINMEM;
        using ANGELSCRIPT_NS_QUALIFIER ICC_STDCALL;
        using ANGELSCRIPT_NS_QUALIFIER ICC_STDCALL_RETURNINMEM;
        using ANGELSCRIPT_NS_QUALIFIER ICC_THISCALL;
        using ANGELSCRIPT_NS_QUALIFIER ICC_THISCALL_RETURNINMEM;
        using ANGELSCRIPT_NS_QUALIFIER ICC_VIRTUAL_THISCALL;
        using ANGELSCRIPT_NS_QUALIFIER ICC_VIRTUAL_THISCALL_RETURNINMEM;
        using ANGELSCRIPT_NS_QUALIFIER ICC_CDECL_OBJLAST;
        using ANGELSCRIPT_NS_QUALIFIER ICC_CDECL_OBJLAST_RETURNINMEM;
        using ANGELSCRIPT_NS_QUALIFIER ICC_CDECL_OBJFIRST;
        using ANGELSCRIPT_NS_QUALIFIER ICC_CDECL_OBJFIRST_RETURNINMEM;
        using ANGELSCRIPT_NS_QUALIFIER ICC_GENERIC_METHOD;
        using ANGELSCRIPT_NS_QUALIFIER ICC_GENERIC_METHOD_RETURNINMEM; // never used
        using ANGELSCRIPT_NS_QUALIFIER ICC_THISCALL_OBJLAST;
        using ANGELSCRIPT_NS_QUALIFIER ICC_THISCALL_OBJLAST_RETURNINMEM;
        using ANGELSCRIPT_NS_QUALIFIER ICC_VIRTUAL_THISCALL_OBJLAST;
        using ANGELSCRIPT_NS_QUALIFIER ICC_VIRTUAL_THISCALL_OBJLAST_RETURNINMEM;
        using ANGELSCRIPT_NS_QUALIFIER ICC_THISCALL_OBJFIRST;
        using ANGELSCRIPT_NS_QUALIFIER ICC_THISCALL_OBJFIRST_RETURNINMEM;
        using ANGELSCRIPT_NS_QUALIFIER ICC_VIRTUAL_THISCALL_OBJFIRST;
        using ANGELSCRIPT_NS_QUALIFIER ICC_VIRTUAL_THISCALL_OBJFIRST_RETURNINMEM;
    } using namespace internalCallConv;
}

namespace testsuite {

    struct asIScriptEngineHack : asCScriptEngine 
    {
        static int GetMessageCallback(asIScriptEngine& engine_interface, asSFuncPtr* callback, void** obj, asDWORD* callConv)
        {
            asCScriptEngine& engine = dynamic_cast<asCScriptEngine&>(engine_interface); // will generate exception with some user provided engine class and that's allright
            bool& msgCallback = engine.msgCallback;

            if (!msgCallback)
                return asNO_FUNCTION;

            struct lambdas {
                typedef ANGELSCRIPT_NS_QUALIFIER asECallConvTypes asECallConvTypes;
                typedef ANGELSCRIPT_NS_QUALIFIER internalCallConv internalCallConv;
                static asECallConvTypes convert_call_conv(internalCallConv call_conv)
                {
                    if (ICC_GENERIC_FUNC == call_conv || ICC_GENERIC_FUNC_RETURNINMEM == call_conv || ICC_GENERIC_METHOD == call_conv || ICC_GENERIC_METHOD_RETURNINMEM == call_conv)
                        return asCALL_GENERIC;
                    if (ICC_CDECL == call_conv || ICC_CDECL_RETURNINMEM == call_conv)
                        return asCALL_CDECL;
                    if (ICC_CDECL_OBJFIRST == call_conv || ICC_CDECL_OBJFIRST_RETURNINMEM == call_conv)
                        return asCALL_CDECL_OBJFIRST;
                    if (ICC_CDECL_OBJLAST == call_conv || ICC_CDECL_OBJLAST_RETURNINMEM == call_conv)
                        return asCALL_CDECL_OBJLAST;
                    if (ICC_STDCALL == call_conv || ICC_STDCALL_RETURNINMEM == call_conv)
                        return asCALL_STDCALL;
                    if (ICC_THISCALL == call_conv || ICC_THISCALL_RETURNINMEM == call_conv || ICC_VIRTUAL_THISCALL == call_conv || ICC_VIRTUAL_THISCALL_RETURNINMEM == call_conv)
                        return asCALL_THISCALL;
                    if (ICC_THISCALL_OBJFIRST == call_conv || ICC_THISCALL_OBJFIRST_RETURNINMEM == call_conv || ICC_VIRTUAL_THISCALL_OBJFIRST == call_conv || ICC_VIRTUAL_THISCALL_OBJFIRST_RETURNINMEM == call_conv)
                        return asCALL_THISCALL_OBJFIRST;
                    if (ICC_THISCALL_OBJLAST == call_conv || ICC_THISCALL_OBJLAST_RETURNINMEM == call_conv || ICC_VIRTUAL_THISCALL_OBJLAST == call_conv || ICC_VIRTUAL_THISCALL_OBJLAST_RETURNINMEM == call_conv)
                        return asCALL_THISCALL_OBJLAST;
                    DOCTEST_FAIL("cannot convert internal calling convention: unknown ICC_ type");
                    return (asECallConvTypes)(42);

                }
            };

            asSSystemFunctionInterface& msgCallbackFunc = engine.msgCallbackFunc;
            void*& msgCallbackObj = engine.msgCallbackObj;

            asSFuncPtr msgCallbackOriginalFuncPtr = 0;
            msgCallbackOriginalFuncPtr.ptr.f.func = msgCallbackFunc.func;
            enum asECallConvTypes msgCallbackOriginalCallConv = lambdas::convert_call_conv(msgCallbackFunc.callConv);

            if (callback)
                *callback = msgCallbackOriginalFuncPtr;
            if (obj)
                *obj = msgCallbackObj;
            if (callConv)
                *callConv = msgCallbackOriginalCallConv;

            return asSUCCESS;
        }
    };
} // namespace testsuite

#define SERVICE_INIT_ENGINE_RAII() struct EngineRAII {                                                                                                            \
            typedef void (*MessageCallback_t)(const asSMessageInfo*, void*);                                                                                      \
            EngineRAII(MessageCallback_t MessageCallback = EngineRAII::MessageCallback, void* param = 0)                                                          \
            : engine(*asCreateScriptEngineFailedAssert()) { DOCTEST_REQUIRE( !operator()(MessageCallback, param) ); }                                             \
            MessageCallback_t operator()(MessageCallback_t MessageCallback = 0, void* param = 0) const { using namespace testsuite;                               \
                asSFuncPtr asSFuncPtr = 0; void* obj; asDWORD callConv; testsuite::asIScriptEngineHack::GetMessageCallback(engine, &asSFuncPtr, &obj, &callConv); \
                if (MessageCallback) engine.SetMessageCallback(asFUNCTION(MessageCallback), param, asCALL_CDECL);                                                 \
                if (asCALL_CDECL == callConv) return reinterpret_cast<MessageCallback_t>(asSFuncPtr.ptr.f.func);                                                  \
                return 0;                                                                                                                                         \
            }                                                                                                                                                     \
            ~EngineRAII(){ engine.ShutDownAndRelease(); }                                                                                                         \
            SERVICE_MESSAGE_CALLBACK_WITH_ASSERTS(MessageCallback)                                                                                                \
            testsuite::asIScriptEngine &engine;protected:                                                                                                         \
            static asIScriptEngine *asCreateScriptEngineFailedAssert() { using namespace testsuite;                                                               \
                asIScriptEngine* engine=0; DOCTEST_REQUIRE_MESSAGE((engine = asCreateScriptEngine()), "failed to create AngelScript engine"); return engine; }    \
            friend struct ContextRAII;                                                                                                                            \
        } EngineRAII

#define SERVICE_REQUEST_CONTEXT_RAII(name) struct ContextRAII {\
            ContextRAII(struct EngineRAII& EngineRAII): context(*RequestContextFailedAssert(EngineRAII.engine)){}\
            ~ContextRAII(){context.Release();}\
            asIScriptContext &context;protected:\
            static asIScriptContext *RequestContextFailedAssert(asIScriptEngine &engine) { using namespace testsuite;\
                asIScriptContext* context=0; DOCTEST_REQUIRE_MESSAGE((context = engine.RequestContext()), "failed to request AngelScript context"); return context; }\
        } ContextRAII(EngineRAII); testsuite::asIScriptContext &name = ContextRAII.context;


#define SERVICE_IMPORT_FUNCTION(name, decl_cstr, module_cstr) asIScriptFunction* name = 0;{                                                                                             \
            struct MessageCallbackRAII {                                                                                                                                                \
                typedef struct EngineRAII EngineRAII_t; const EngineRAII_t &EngineRAII; SERVICE_MESSAGE_CALLBACK_WITH_ASSERTS(MessageCallback)                                          \
                MessageCallbackRAII(const EngineRAII_t &EngineRAII) : EngineRAII(EngineRAII) {                                                                                          \
                    if (EngineRAII() == &EngineRAII_t::MessageCallback) { EngineRAII(&MessageCallbackRAII::MessageCallback); }                                                          \
                }                                                                                                                                                                       \
                ~MessageCallbackRAII() {                                                                                                                                                \
                    if (EngineRAII() == &MessageCallbackRAII::MessageCallback) { EngineRAII(&EngineRAII_t::MessageCallback); }                                                          \
                }                                                                                                                                                                       \
            } MessageCallbackRAII(EngineRAII); using namespace testsuite; asIScriptModule *asIScriptModule = 0;                                                                         \
            CScriptBuilder CScriptBuilder; asIScriptEngine *asIScriptEngine = &EngineRAII.engine; const std::string moduleName = module_cstr; const std::string decl = decl_cstr;       \
            DOCTEST_REQUIRE_MESSAGE(0 <= CScriptBuilder.StartNewModule(asIScriptEngine, moduleName.c_str()), "CScriptBuilder::StartNewModule: cannot start new module: " + moduleName); \
            DOCTEST_REQUIRE_MESSAGE(0 <= CScriptBuilder.AddSectionFromFile(moduleName.c_str()), "CScriptBuilder::AddSectionFromFile: cannot load script from: " + moduleName);          \
            DOCTEST_REQUIRE_MESSAGE(0 <= CScriptBuilder.BuildModule(), "CScriptBuilder::BuildModule: script has errors: " + moduleName);                                                \
            DOCTEST_REQUIRE_MESSAGE((asIScriptModule = asIScriptEngine->GetModule(moduleName.c_str())), "asIScriptEngine::GetModule: cannot find module: " + moduleName);               \
            DOCTEST_REQUIRE_MESSAGE((name = asIScriptModule->GetFunctionByDecl(decl.c_str())), "asIScriptModule::GetFunctionByDecl: cannot find function: " + decl);                    \
        } 

#endif // SERVICE_TESTSUITE_H

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

#include <cstring>
#include <string>
#include <fstream>

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

#define SERVICE_FILE_TRANSLATION_YYMMDD_DATE(name)                                           \
    const char name[] =                                                                      \
    {                                                                                        \
        /* YY year */                                                                        \
        *(__DATE__+9), *(__DATE__+10),                                                       \
                                                                                             \
        /* First month letter, Oct Nov Dec = '1' otherwise '0' */                            \
        (*(__DATE__+0) == 'O' || *(__DATE__+0) == 'N' || *(__DATE__+0) == 'D') ? '1' : '0',  \
                                                                                             \
        /* Second month letter */                                                            \
        (*(__DATE__+0) == 'J') ? ((*(__DATE__+1) == 'a') ? '1' :       /* Jan, Jun or Jul */ \
                                 ((*(__DATE__+2) == 'n') ? '6' : '7')) :                     \
        (*(__DATE__+0) == 'F') ? '2' :                                /* Feb */              \
        (*(__DATE__+0) == 'M') ? (*(__DATE__+2) == 'r') ? '3' : '5' :   /* Mar or May */     \
        (*(__DATE__+0) == 'A') ? (*(__DATE__+1) == 'p') ? '4' : '8' :   /* Apr or Aug */     \
        (*(__DATE__+0) == 'S') ? '9' :                                /* Sep */              \
        (*(__DATE__+0) == 'O') ? '0' :                                /* Oct */              \
        (*(__DATE__+0) == 'N') ? '1' :                                /* Nov */              \
        (*(__DATE__+0) == 'D') ? '2' :                                /* Dec */              \
        0,                                                                                   \
                                                                                             \
        /* First day letter, replace space with digit */                                     \
        *(__DATE__+4) == ' ' ? '0' : *(__DATE__+4),                                          \
                                                                                             \
        /* Second day letter */                                                              \
        *(__DATE__+5),                                                                       \
                                                                                             \
       '\0'                                                                                  \
    };

#define SERVICE_FILE_TRANSLATION_HHMMSS_TIME(name)                                                     \
    const char name[] = {                                                                              \
        *(__TIME__+0), *(__TIME__+1), *(__TIME__+3), *(__TIME__+4), *(__TIME__+6), *(__TIME__+7), '\0' \
    };

#define SERVICE_MESSAGE_CALLBACK_WITH_ASSERTS(name) \
            static void name(const ANGELSCRIPT_NS_QUALIFIER asSMessageInfo* asSMessageInfo, void*)                                                                                 \
            {   ANGELSCRIPT_NS_QUALIFIER asIScriptContext* asIScriptContext = ANGELSCRIPT_NS_QUALIFIER asGetActiveContext(); typedef ::std::string string;                         \
                const string message = asSMessageInfo->message? asSMessageInfo->message: ""; const string prefix = " ("; const string comma = ", ";                                \
                const string section = asSMessageInfo->section? asSMessageInfo->section: ""; const string suffix = ") : ";                                                         \
                if (ANGELSCRIPT_NS_QUALIFIER asMSGTYPE_WARNING == asSMessageInfo->type)                                                                                            \
                {                                                                                                                                                                  \
                    DOCTEST_WARN_MESSAGE(asSMessageInfo, section << prefix << asSMessageInfo->row << comma << asSMessageInfo->col << suffix << message);                           \
                }                                                                                                                                                                  \
                else if (ANGELSCRIPT_NS_QUALIFIER asMSGTYPE_INFORMATION == asSMessageInfo->type)                                                                                   \
                {                                                                                                                                                                  \
                    if (asIScriptContext)                                                                                                                                          \
                        DOCTEST_ADD_MESSAGE_AT(asIScriptContext->GetEngine()->GetModuleByIndex(0)->GetName(), asSMessageInfo->row,                                                 \
                                section << prefix << asSMessageInfo->row << comma << asSMessageInfo->col << suffix << message);                                                    \
                    else                                                                                                                                                           \
                        DOCTEST_MESSAGE(section << prefix << asSMessageInfo->row << comma << asSMessageInfo->col << suffix << message);                                            \
                }                                                                                                                                                                  \
                else if (ANGELSCRIPT_NS_QUALIFIER asMSGTYPE_ERROR == asSMessageInfo->type)                                                                                         \
                {                                                                                                                                                                  \
                    if (asIScriptContext)                                                                                                                                          \
                        DOCTEST_ADD_FAIL_CHECK_AT(asIScriptContext->GetEngine()->GetModuleByIndex(0)->GetName(), asSMessageInfo->row,                                              \
                            section << prefix << asSMessageInfo->row << comma << asSMessageInfo->col << suffix << message);                                                        \
                    else                                                                                                                                                           \
                        DOCTEST_FAIL_CHECK(section << prefix << asSMessageInfo->row << comma << asSMessageInfo->col << suffix << message);                                         \
                }                                                                                                                                                                  \
                else throw(asSMessageInfo->message);                                                                                                                               \
            }

#define SERVICE_EXCEPTION_CALLBACK_WITH_ASSERTS(name) \
            static void name(ANGELSCRIPT_NS_QUALIFIER asIScriptContext* asIScriptContext, void*)                                                                                   \
            {                                                                                                                                                                      \
                DOCTEST_ADD_MESSAGE_AT(asIScriptContext->GetEngine()->GetModuleByIndex(0)->GetName(), asIScriptContext->GetExceptionLineNumber(),                                  \
                        "unhandled exception in script caught at line " << asIScriptContext->GetExceptionLineNumber() << ": " << asIScriptContext->GetExceptionString());          \
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
    namespace AngelScript {
        using ANGELSCRIPT_NS_QUALIFIER asSMessageInfo;
        using ANGELSCRIPT_NS_QUALIFIER asDWORD;
        using ANGELSCRIPT_NS_QUALIFIER asIScriptEngine;
        using ANGELSCRIPT_NS_QUALIFIER asIScriptContext;
        using ANGELSCRIPT_NS_QUALIFIER asCScriptEngine;
        using ANGELSCRIPT_NS_QUALIFIER asCFuncdefType;
        using ANGELSCRIPT_NS_QUALIFIER asSFuncPtr;
        using ANGELSCRIPT_NS_QUALIFIER asSSystemFunctionInterface;
        using ANGELSCRIPT_NS_QUALIFIER CScriptBuilder;
        using ANGELSCRIPT_NS_QUALIFIER asITypeInfo;
        using ANGELSCRIPT_NS_QUALIFIER asUINT;
        using ANGELSCRIPT_NS_QUALIFIER asIScriptFunction;
        using ANGELSCRIPT_NS_QUALIFIER asCScriptFunction;
        using ANGELSCRIPT_NS_QUALIFIER asCArray;
        using ANGELSCRIPT_NS_QUALIFIER asIScriptModule;

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
    using namespace testsuite::AngelScript;
}

namespace testsuite {

    struct asCScriptEngineHack : asCScriptEngine 
    {
        virtual int GetMessageCallback(ANGELSCRIPT_NS_QUALIFIER asSFuncPtr* callback, void** obj, ANGELSCRIPT_NS_QUALIFIER asDWORD* callConv)
        {
            return asCScriptEngine::GetMessageCallback(callback, obj, callConv);
        }
        static int GetMessageCallback(ANGELSCRIPT_NS_QUALIFIER asIScriptEngine& asIScriptEngine, ANGELSCRIPT_NS_QUALIFIER asSFuncPtr* callback, void** obj, ANGELSCRIPT_NS_QUALIFIER asDWORD* callConv)
        {
            ANGELSCRIPT_NS_QUALIFIER asCScriptEngine& engine = dynamic_cast<ANGELSCRIPT_NS_QUALIFIER asCScriptEngine&>(asIScriptEngine); // will generate exception with some user provided engine class and that's allright
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

            ANGELSCRIPT_NS_QUALIFIER asSSystemFunctionInterface& msgCallbackFunc = engine.msgCallbackFunc;
            void*& msgCallbackObj = engine.msgCallbackObj;

            ANGELSCRIPT_NS_QUALIFIER asSFuncPtr msgCallbackOriginalFuncPtr = 0;
            msgCallbackOriginalFuncPtr.ptr.f.func = msgCallbackFunc.func;
            ANGELSCRIPT_NS_QUALIFIER asECallConvTypes msgCallbackOriginalCallConv = lambdas::convert_call_conv(msgCallbackFunc.callConv);

            if (callback)
                *callback = msgCallbackOriginalFuncPtr;
            if (obj)
                *obj = msgCallbackObj;
            if (callConv)
                *callConv = msgCallbackOriginalCallConv;

            return asSUCCESS;
        }
        static void UnregisterGlobalFunction(ANGELSCRIPT_NS_QUALIFIER asIScriptEngine& asIScriptEngine, ANGELSCRIPT_NS_QUALIFIER asIScriptFunction* asIScriptFunction)
        {
            ANGELSCRIPT_NS_QUALIFIER asCScriptFunction* func = &dynamic_cast<ANGELSCRIPT_NS_QUALIFIER asCScriptFunction&>(*asIScriptFunction); // will generate exception with some user provided function class and that's allright
            ANGELSCRIPT_NS_QUALIFIER asCScriptEngine& engine = dynamic_cast<ANGELSCRIPT_NS_QUALIFIER asCScriptEngine&>(asIScriptEngine); // will generate exception with some user provided engine class and that's allright

            const ANGELSCRIPT_NS_QUALIFIER asCArray<unsigned int>& idxs = engine.registeredGlobalFuncs.GetIndexes(func->nameSpace, func->name);
            for (ANGELSCRIPT_NS_QUALIFIER asUINT n = 0; n < idxs.GetLength(); n++)
            {
                ANGELSCRIPT_NS_QUALIFIER asCScriptFunction* f = engine.registeredGlobalFuncs.Get(idxs[n]);
                if (f->IsSignatureExceptNameAndReturnTypeEqual(func))
                {
                    engine.registeredGlobalFuncs.Erase(idxs[n]);
                    return;
                }
            }
        }

    };
} // namespace testsuite

namespace testsuite {
    namespace detail {
        template<class FuncT>
        FuncT func_call(FuncT call) { return call; }
    }
    long strtol(const std::string& str)
    {
        long result = 0;
        using namespace std;
        if (1 != detail::func_call(sscanf)(str.c_str(), "%d", &result)) 
            throw("");
        return result;
    }

    struct IEngineRAII {
        typedef void (*MessageCallback_t)(const asSMessageInfo*, void*);
        virtual MessageCallback_t operator()(MessageCallback_t MessageCallback = 0, void* param = 0) const = 0;
        testsuite::asIScriptEngine& engine;
        IEngineRAII(testsuite::asIScriptEngine& engine) : engine(engine) {}
        SERVICE_MESSAGE_CALLBACK_WITH_ASSERTS(MessageCallback)
    };
}
                                                                                                        

#define SERVICE_INIT_ENGINE_RAII() struct EngineRAII: testsuite::IEngineRAII {                                                                                    \
            EngineRAII(MessageCallback_t MessageCallback = EngineRAII::MessageCallback, void* param = 0)                                                          \
            : testsuite::IEngineRAII(*asCreateScriptEngineFailedAssert()) { DOCTEST_REQUIRE( !operator()(MessageCallback, param) ); }                             \
            MessageCallback_t operator()(MessageCallback_t MessageCallback = 0, void* param = 0) const { using namespace testsuite;                               \
                asSFuncPtr asSFuncPtr = 0; void* obj; asDWORD callConv; testsuite::asCScriptEngineHack::GetMessageCallback(engine, &asSFuncPtr, &obj, &callConv); \
                if (MessageCallback) engine.SetMessageCallback(asFUNCTION(MessageCallback), param, asCALL_CDECL);                                                 \
                if (asCALL_CDECL == callConv) return reinterpret_cast<MessageCallback_t>(asSFuncPtr.ptr.f.func);                                                  \
                return 0;                                                                                                                                         \
            }                                                                                                                                                     \
            ~EngineRAII(){ engine.ShutDownAndRelease(); }                                                                                                         \
            protected:                                                                                                                                            \
            static testsuite::asIScriptEngine *asCreateScriptEngineFailedAssert() { using namespace testsuite; using testsuite::asIScriptEngine;                  \
                asIScriptEngine* engine=0; DOCTEST_REQUIRE_MESSAGE((engine = asCreateScriptEngine()), "failed to create AngelScript engine"); return engine; }    \
            friend struct ContextRAII;                                                                                                                            \
        } EngineRAII

#define SERVICE_REQUEST_CONTEXT_RAII(name) struct ContextRAII {  SERVICE_EXCEPTION_CALLBACK_WITH_ASSERTS(ExceptionCallback)                                           \
            ContextRAII(struct EngineRAII& EngineRAII)                                                                                                                \
            : context(*RequestContextFailedAssert(EngineRAII.engine)) { context.SetExceptionCallback(asFUNCTION(ExceptionCallback), 0, asCALL_CDECL); }               \
            ~ContextRAII(){context.Release();}                                                                                                                        \
            testsuite::asIScriptContext &context;protected:                                                                                                           \
            static testsuite::asIScriptContext *RequestContextFailedAssert(asIScriptEngine &engine) { using namespace testsuite; using testsuite::asIScriptContext;   \
                asIScriptContext* context=0; DOCTEST_REQUIRE_MESSAGE((context = engine.RequestContext()), "failed to request AngelScript context"); return context; } \
        } ContextRAII(EngineRAII); name = ContextRAII.context;


#define SERVICE_IMPORT_FUNCTION(name, module_cstr, decl_cstr) testsuite::AngelScript::asIScriptFunction* name = 0;{                                                                          \
            struct MessageCallbackRAII {                                                                                                                                                     \
                typedef testsuite::IEngineRAII EngineRAII_t; const EngineRAII_t &EngineRAII; SERVICE_MESSAGE_CALLBACK_WITH_ASSERTS(MessageCallback)                                          \
                MessageCallbackRAII(const EngineRAII_t &EngineRAII) : EngineRAII(EngineRAII) {                                                                                               \
                    if (EngineRAII() == &testsuite::IEngineRAII::MessageCallback) { EngineRAII(&MessageCallback); }                                                                          \
                }                                                                                                                                                                            \
                ~MessageCallbackRAII() {                                                                                                                                                     \
                    if (EngineRAII() == &MessageCallback) { EngineRAII(&testsuite::IEngineRAII::MessageCallback); }                                                                          \
                }                                                                                                                                                                            \
            } MessageCallbackRAII(EngineRAII); testsuite::AngelScript::asIScriptModule *asIScriptModule = 0;                                                                                 \
            testsuite::AngelScript::CScriptBuilder CScriptBuilder; testsuite::AngelScript::asIScriptEngine *asIScriptEngine = &EngineRAII.engine;                                            \
            const std::string sectionStr = module_cstr; const std::string decl = decl_cstr;                                                                                                  \
            const bool is_file = !!std::fstream(sectionStr.c_str()); const std::string moduleName = is_file ? sectionStr : std::string(#name) + ": " + decl;                                 \
            DOCTEST_REQUIRE_MESSAGE(0 <= CScriptBuilder.StartNewModule(asIScriptEngine, moduleName.c_str()), "CScriptBuilder::StartNewModule: cannot start new module: " + moduleName);      \
            if (is_file) DOCTEST_REQUIRE_MESSAGE(0 <= CScriptBuilder.AddSectionFromFile(sectionStr.c_str()), "CScriptBuilder::AddSectionFromFile: cannot load script from: " + sectionStr);  \
            else DOCTEST_REQUIRE_MESSAGE(0 <= CScriptBuilder.AddSectionFromMemory(moduleName.c_str(), sectionStr.c_str(), sectionStr.length()),                                              \
                          "CScriptBuilder::AddSectionFromFile: cannot load script from: " + moduleName);                                                                                     \
            DOCTEST_REQUIRE_MESSAGE(0 <= CScriptBuilder.BuildModule(), "CScriptBuilder::BuildModule: script has errors: " + moduleName);                                                     \
            DOCTEST_REQUIRE_MESSAGE((asIScriptModule = asIScriptEngine->GetModule(moduleName.c_str())), "asIScriptEngine::GetModule: cannot find module: " + moduleName);                    \
            DOCTEST_REQUIRE_MESSAGE((name = asIScriptModule->GetFunctionByDecl(decl.c_str())), "asIScriptModule::GetFunctionByDecl: cannot find function: " + decl);                         \
        }

#include <cstdio>
#define SERVICE_FILE_RAII struct SERVICE_CONCAT(FileRAII, __LINE__){ \
             SERVICE_CONCAT(FileRAII, __LINE__)(std::string name):name(name) {}\
            ~SERVICE_CONCAT(FileRAII, __LINE__)() {std::remove(static_cast<std::string>(name).c_str());}\
            private: std::string name;\
        }SERVICE_CONCAT(FileRAII, __LINE__)

#endif // SERVICE_TESTSUITE_H

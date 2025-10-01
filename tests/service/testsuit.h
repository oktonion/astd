#ifndef SERVICE_TESTSUIT_H
#define SERVICE_TESTSUIT_H

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

#ifndef ASTD_DIRECTORY
#   define ASTD_DIRECTORY ../std/
#endif
#ifndef ANGELSCRIPT_ADD_ON_DIRECTORY
#   define ANGELSCRIPT_ADD_ON_DIRECTORY ../angelscript/sdk/add_on/
#endif

#define SCRIPTSTD_H_PATH(name) <SERVICE_CONCAT(ASTD_DIRECTORY, SERVICE_CONCAT(name, SERVICE_CONCAT(/scriptstd_,name.h)))>
#define ANGELSCRIPT_ADD_ON_H_PATH(name) <SERVICE_CONCAT(ANGELSCRIPT_ADD_ON_DIRECTORY, SERVICE_CONCAT(name/, name.h))>

#define SERVICE_MESSAGE_CALLBACK_WITH_ASSERTS(name) \
            static void name(const asSMessageInfo* asSMessageInfo, void*)                                                                                                              \
            {                                                                                                                                                                          \
                if (asMSGTYPE_WARNING == asSMessageInfo->type)                                                                                                                         \
                {                                                                                                                                                                      \
                    DOCTEST_WARN_MESSAGE(!asSMessageInfo, asSMessageInfo->section << " (" << asSMessageInfo->row << ", " << asSMessageInfo->col << ") : " << asSMessageInfo->message); \
                }                                                                                                                                                                      \
                else if (asMSGTYPE_INFORMATION == asSMessageInfo->type)                                                                                                                \
                {                                                                                                                                                                      \
                    DOCTEST_INFO(asSMessageInfo->section << " (" << asSMessageInfo->row << ", " << asSMessageInfo->col << ") : " << asSMessageInfo->message);                          \
                }                                                                                                                                                                      \
                else                                                                                                                                                                   \
                {                                                                                                                                                                      \
                    DOCTEST_FAIL_CHECK(asSMessageInfo->section << " (" << asSMessageInfo->row << ", " << asSMessageInfo->col << ") : " << asSMessageInfo->message);                    \
                }                                                                                                                                                                      \
            }

#define SERVICE_INIT_ENGINE_RAII() struct EngineRAII {                                                                                                        \
            typedef void (*MessageCallback_t)(const asSMessageInfo*, void*);                                                                                  \
            EngineRAII(MessageCallback_t MessageCallback = EngineRAII::MessageCallback, void* param = 0)                                                      \
            : engine(*asCreateScriptEngineFailedAssert()) { DOCTEST_REQUIRE( !operator()(MessageCallback, param) ); }                                         \
            MessageCallback_t operator()(MessageCallback_t MessageCallback = 0, void* param = 0) const {                                                      \
                asSFuncPtr asSFuncPtr = 0; void* obj; asDWORD callConv; engine.GetMessageCallback(&asSFuncPtr, &obj, &callConv);                              \
                if (MessageCallback) engine.SetMessageCallback(asFUNCTION(MessageCallback), param, asCALL_CDECL);                                             \
                if (asCALL_CDECL == callConv) return reinterpret_cast<MessageCallback_t>(asSFuncPtr.ptr.f.func);                                              \
                return 0;                                                                                                                                     \
            }                                                                                                                                                 \
            ~EngineRAII(){ engine.ShutDownAndRelease(); }                                                                                                     \
            SERVICE_MESSAGE_CALLBACK_WITH_ASSERTS(MessageCallback)                                                                                            \
            asIScriptEngine &engine;protected:                                                                                                                \
            static asIScriptEngine *asCreateScriptEngineFailedAssert()                                                                                        \
            { asIScriptEngine* engine=0; DOCTEST_REQUIRE_MESSAGE((engine = asCreateScriptEngine()), "failed to create AngelScript engine"); return engine; }  \
            friend struct ContextRAII;                                                                                                                        \
        } EngineRAII

#define SERVICE_REQUEST_CONTEXT_RAII(name) struct ContextRAII {\
            ContextRAII(struct EngineRAII& EngineRAII): context(*RequestContextFailedAssert(EngineRAII.engine)){}\
            ~ContextRAII(){context.Release();}\
            asIScriptContext &context;protected:\
            static asIScriptContext *RequestContextFailedAssert(asIScriptEngine &engine)\
            { asIScriptContext* context=0; DOCTEST_REQUIRE_MESSAGE((context = engine.RequestContext()), "failed to request AngelScript context"); return context; }\
        } ContextRAII(EngineRAII); asIScriptContext &name = ContextRAII.context;

#ifndef ANGELSCRIPT_SCRIPTBUILDER_H_PATH
#   define ANGELSCRIPT_SCRIPTBUILDER_H_PATH ANGELSCRIPT_ADD_ON_H_PATH(scriptbuilder)
#endif // ANGELSCRIPT_SCRIPTBUILDER_H_PATH

#include ANGELSCRIPT_SCRIPTBUILDER_H_PATH
#define SERVICE_IMPORT_FUNCTION(name, decl_cstr, module_cstr) asIScriptFunction* name = 0;{                                                                                             \
            struct MessageCallbackRAII {                                                                                                                                                \
                typedef struct EngineRAII EngineRAII_t; const EngineRAII_t &EngineRAII; SERVICE_MESSAGE_CALLBACK_WITH_ASSERTS(MessageCallback)                                          \
                MessageCallbackRAII(const EngineRAII_t &EngineRAII) : EngineRAII(EngineRAII) {                                                                                          \
                    if (EngineRAII() == &EngineRAII_t::MessageCallback) { EngineRAII(&MessageCallbackRAII::MessageCallback); }                                                          \
                }                                                                                                                                                                       \
                ~MessageCallbackRAII() {                                                                                                                                                \
                    if (EngineRAII() == &MessageCallbackRAII::MessageCallback) { EngineRAII(&EngineRAII_t::MessageCallback); }                                                          \
                }                                                                                                                                                                       \
            } MessageCallbackRAII(EngineRAII); asIScriptModule *asIScriptModule = 0;                                                                                                    \
            CScriptBuilder CScriptBuilder; asIScriptEngine *asIScriptEngine = &EngineRAII.engine; const std::string moduleName = module_cstr; const std::string decl = decl_cstr;       \
            DOCTEST_REQUIRE_MESSAGE(0 <= CScriptBuilder.StartNewModule(asIScriptEngine, moduleName.c_str()), "CScriptBuilder::StartNewModule: cannot start new module: " + moduleName); \
            DOCTEST_REQUIRE_MESSAGE(0 <= CScriptBuilder.AddSectionFromFile(moduleName.c_str()), "CScriptBuilder::AddSectionFromFile: cannot load script from: " + moduleName);          \
            DOCTEST_REQUIRE_MESSAGE(0 <= CScriptBuilder.BuildModule(), "CScriptBuilder::BuildModule: script has errors: " + moduleName);                                                \
            DOCTEST_REQUIRE_MESSAGE((asIScriptModule = asIScriptEngine->GetModule(moduleName.c_str())), "asIScriptEngine::GetModule: cannot find module: " + moduleName);               \
            DOCTEST_REQUIRE_MESSAGE((name = asIScriptModule->GetFunctionByDecl(decl.c_str())), "asIScriptModule::GetFunctionByDecl: cannot find function: " + decl);                    \
        } 

#endif // SERVICE_TESTSUIT_H

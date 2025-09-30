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

#define SERVICE_INIT_ENGINE_RAII() struct EngineRAII {\
            EngineRAII(void (*MessageCallback)(const asSMessageInfo*, void*) = EngineRAII::MessageCallback, void* param = 0)\
            : engine(*asCreateScriptEngineFailedAssert()){engine.SetMessageCallback(asFUNCTION(MessageCallback), param, asCALL_CDECL);}\
            ~EngineRAII(){engine.ShutDownAndRelease();}\
            asIScriptEngine &engine;protected:\
            static asIScriptEngine *asCreateScriptEngineFailedAssert()\
            { asIScriptEngine* engine=0; DOCTEST_REQUIRE_MESSAGE((engine = asCreateScriptEngine()), "failed to create AngelScript engine"); return engine; }\
            friend struct ContextRAII;\
            static void MessageCallback(const asSMessageInfo* msg, void*)                                                                       \
            {                                                                                                                                   \
                if (asMSGTYPE_WARNING == msg->type)                                                                                             \
                {                                                                                                                               \
                    DOCTEST_WARN_MESSAGE(!msg, msg->section << " (" << msg->row << ", " << msg->col << ") : " << msg->message);                 \
                }                                                                                                                               \
                else if (asMSGTYPE_INFORMATION == msg->type)                                                                                    \
                {                                                                                                                               \
                    DOCTEST_INFO(msg->section << " (" << msg->row << ", " << msg->col << ") : " << msg->message);                               \
                }                                                                                                                               \
                else                                                                                                                            \
                {                                                                                                                               \
                    DOCTEST_FAIL(msg->section << " (" << msg->row << ", " << msg->col << ") : " << msg->message);                               \
                }                                                                                                                               \
            }                                                                                                                                   \
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
#define SERVICE_IMPORT_FUNCTION(name, decl_cstr, module_cstr) asIScriptFunction* name = 0;{\
            CScriptBuilder builder; asIScriptEngine *asIScriptEngine = &EngineRAII.engine; const std::string module_name = module_cstr; const std::string decl = decl_cstr;\
            DOCTEST_REQUIRE_MESSAGE(0 <= builder.StartNewModule(asIScriptEngine, module_name.c_str()), "CScriptBuilder::StartNewModule: cannot start new module: " + module_name);\
            DOCTEST_REQUIRE_MESSAGE(0 <= builder.AddSectionFromFile(module_name.c_str()), "CScriptBuilder::AddSectionFromFile: cannot load script from: " + module_name);\
            DOCTEST_REQUIRE_MESSAGE(0 <= builder.BuildModule(), "CScriptBuilder::BuildModule: script has errors: " + module_name);\
            asIScriptModule *asIScriptModule = 0;\
            DOCTEST_REQUIRE_MESSAGE((asIScriptModule = asIScriptEngine->GetModule(module_name.c_str())), "asIScriptEngine::GetModule: cannot find module: " + module_name);\
            DOCTEST_REQUIRE_MESSAGE((name = asIScriptModule->GetFunctionByDecl(decl.c_str())), "asIScriptModule::GetFunctionByDecl: cannot find function: " + decl);\
        }

#endif // SERVICE_TESTSUIT_H

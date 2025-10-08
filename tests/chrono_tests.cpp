#include "service/testsuit.h"

#ifndef SCRIPTSTD_COROUTINES_H_PATH
#   define SCRIPTSTD_COROUTINES_H_PATH SCRIPTSTD_H_PATH(coroutines)
#endif // SCRIPTSTD_COROUTINES_H_PATH
#ifndef SCRIPTSTD_FORMAT_H_PATH
#   define SCRIPTSTD_FORMAT_H_PATH SCRIPTSTD_H_PATH(format)
#endif // SCRIPTSTD_FORMAT_H_PATH
#ifndef SCRIPTSTD_RATIO_H_PATH
#   define SCRIPTSTD_RATIO_H_PATH SCRIPTSTD_H_PATH(ratio)
#endif // SCRIPTSTD_RATIO_H_PATH
#ifndef SCRIPTSTD_CHRONO_H_PATH
#   define SCRIPTSTD_CHRONO_H_PATH SCRIPTSTD_H_PATH(chrono)
#endif // SCRIPTSTD_CHRONO_H_PATH

#ifndef ANGELSCRIPT_STRING_H_PATH
#   define ANGELSCRIPT_STRING_H_PATH ANGELSCRIPT_ADD_ON_H_PATH(scriptstdstring)
#endif
#ifndef ANGELSCRIPT_MATH_H_PATH
#   define ANGELSCRIPT_MATH_H_PATH ANGELSCRIPT_ADD_ON_H_PATH(scriptmath)
#endif

#include SCRIPTSTD_FORMAT_H_PATH
#include SCRIPTSTD_RATIO_H_PATH
#include SCRIPTSTD_CHRONO_H_PATH
#include SCRIPTSTD_COROUTINES_H_PATH

#include ANGELSCRIPT_STRING_H_PATH
#include ANGELSCRIPT_MATH_H_PATH

#include <string>
#include <cstring>


SERVICE_FILE_TRANSLATION_YYMMDD_DATE(TRANSLATION_YYMMDD_DATE);
SERVICE_FILE_TRANSLATION_HHMMSS_TIME(TRANSLATION_HHMMSS_TIME);

namespace {
    struct TestCase {
        testsuite::AngelScript::asIScriptContext* script_context;
        TestCase() : script_context(0){
        }

        void CheckSubcases(testsuite::IEngineRAII& EngineRAII, const std::string &script_path) {

            REQUIRE(script_context);
            testsuite::AngelScript::asIScriptContext& script_context = *this->script_context;

            SUBCASE("importing function 'int chrono_test()'")
            {
                
                SERVICE_IMPORT_FUNCTION(chrono_test, script_path, "int chrono_test()");

                CHECK(static_cast<int>(asSUCCESS) == script_context.Prepare(chrono_test));
                CHECK(static_cast<int>(asEXECUTION_FINISHED) == script_context.Execute());
            }

            SUBCASE("importing function 'int chrono_test()'")
            {

                SERVICE_IMPORT_FUNCTION(chrono_test, script_path, "int chrono_test()");

                CHECK(static_cast<int>(asSUCCESS) == script_context.Prepare(chrono_test));
                CHECK(static_cast<int>(asEXECUTION_FINISHED) == script_context.Execute());
            }
        }
        
    };
}

TEST_CASE_FIXTURE(TestCase, "astd: chrono: chrono_script.as")
{
    const std::string script_path = "./../service/resources/chrono_script.as";

    SERVICE_INIT_ENGINE_RAII();
    SERVICE_REQUEST_CONTEXT_RAII(testsuite::AngelScript::asIScriptContext & script_context);
    TestCase::script_context = &script_context;

    using namespace testsuite::AngelScript; // for all types of AngelScript

    {
        asIScriptEngine* asIScriptEngine = script_context.GetEngine();

        RegisterScriptStd_Ratio(asIScriptEngine);
        RegisterScriptStd_Chrono(asIScriptEngine);
    }

    CheckSubcases(EngineRAII, script_path);
}

TEST_CASE_FIXTURE(TestCase, "astd: chrono: script.as")
{
    const std::string script_path = "./../service/resources/script.as";

    SERVICE_INIT_ENGINE_RAII();
    SERVICE_REQUEST_CONTEXT_RAII(testsuite::AngelScript::asIScriptContext &script_context);
    TestCase::script_context = &script_context;

    using namespace testsuite::AngelScript; // for all types of AngelScript

    {
        asIScriptEngine* asIScriptEngine = script_context.GetEngine();

        RegisterStdString(asIScriptEngine);
        {
            const long translation_time_current = testsuite::strtol(TRANSLATION_HHMMSS_TIME);
            const long translation_date_current = testsuite::strtol(TRANSLATION_YYMMDD_DATE);
            const long translation_date_deadline = 261008; // as for 02.10.2025 AngelScript 2.39.0 WIP has bug with registering (...) functions, 
                                                           // see: https://github.com/anjo76/angelscript/issues/14#issuecomment-3355997388
                                                           // by 08.10.2025 it partially fixed and I hope that in next version by 08.10.2026 it would be fixed
            const long angelscript_ver = ANGELSCRIPT_VERSION;

            if (translation_date_current < translation_date_deadline 
                || angelscript_ver <= 23900)
            { // until bug is fixed we need to unregister 'extra' format function from `scriptstdstring` addon to continue with testing
                asIScriptFunction* string_addon_format_func = 0;
                REQUIRE((string_addon_format_func = asIScriptEngine->GetGlobalFunctionByDecl("string format(const string&in ,const ?&in...)")));

                REQUIRE_NOTHROW({
                    testsuite::asCScriptEngineHack::UnregisterGlobalFunction(*asIScriptEngine, string_addon_format_func);
                });
            }
        }
        {
            RegisterScriptMath(asIScriptEngine);
            asIScriptEngine->SetDefaultNamespace("std");
            RegisterScriptMath(asIScriptEngine);
            asIScriptEngine->SetDefaultNamespace("");
        }

        RegisterScriptFmt(asIScriptEngine);
        RegisterScriptStd_Coroutines(asIScriptEngine);
        RegisterScriptStd_Ratio(asIScriptEngine);
        RegisterScriptStd_Chrono(asIScriptEngine);
    }

    CheckSubcases(EngineRAII, script_path);

    SUBCASE("importing function 'int chrono_and_print_test()'")
    {

        SERVICE_IMPORT_FUNCTION(chrono_and_print_test, script_path, "int chrono_and_print_test()");

        CHECK(static_cast<int>(asSUCCESS) == script_context.Prepare(chrono_and_print_test));
        CHECK(static_cast<int>(asEXECUTION_FINISHED) == script_context.Execute()); 
    }
}
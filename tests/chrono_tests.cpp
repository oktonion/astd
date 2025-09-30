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

TEST_CASE("astd: chrono")
{
    const std::string script_path = "./../service/resources/script.as";

    SERVICE_INIT_ENGINE_RAII();
    SERVICE_REQUEST_CONTEXT_RAII(script_context);

    {
        asIScriptEngine* engine = script_context.GetEngine();
        RegisterStdString(engine);
        {
            RegisterScriptMath(engine);
            script_context.GetEngine()->SetDefaultNamespace("std");
            RegisterScriptMath(engine);
            script_context.GetEngine()->SetDefaultNamespace("");
        }

        RegisterScriptFmt(engine);
        RegisterScriptStd_Coroutines(engine);
        RegisterScriptStd_Ratio(engine);
        RegisterScriptStd_Chrono(engine);
    }

    SUBCASE("importing function 'int chrono_test()'")
    {
        SERVICE_IMPORT_FUNCTION(chrono_test, "int chrono_test()", script_path);
    }
}


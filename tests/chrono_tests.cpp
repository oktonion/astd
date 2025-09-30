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

#include SCRIPTSTD_FORMAT_H_PATH
#include SCRIPTSTD_RATIO_H_PATH
#include SCRIPTSTD_CHRONO_H_PATH
#include SCRIPTSTD_COROUTINES_H_PATH

#include ANGELSCRIPT_STRING_H_PATH

#include <string>

TEST_CASE("astd: chrono")
{
    const std::string script_path = "./../service/resources/script.as";

    SERVICE_INIT_ENGINE_RAII();
    SERVICE_REQUEST_CONTEXT_RAII(script_context);

    RegisterStdString(script_context.GetEngine());

    RegisterScriptFmt(script_context.GetEngine());
    RegisterScriptStd_Coroutines(script_context.GetEngine());
    RegisterScriptStd_Ratio(script_context.GetEngine());
    RegisterScriptStd_Chrono(script_context.GetEngine());

    SUBCASE("importing function 'void chrono_test()'")
    {
        SERVICE_IMPORT_FUNCTION(chrono_test, "void chrono_test()", script_path);
    }
}



#include "scriptstd_ratio.h"
#include "scriptstd_ratio.impl.hpp"

#include <memory>
#include <cassert>
#include <exception>
#include <stdexcept>
#include <string>
#include <cstring>
#include <climits>
#include <ctime>


BEGIN_AS_NAMESPACE




namespace astd_script {
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

#   define RegisterScriptStdFunction(N) \
        template<> struct RegisterScriptStdFunctionHelperN<N> \
        { static void call(asIScriptEngine * engine); static void call_next(asIScriptEngine * engine) { call(engine); RegisterScriptStdFunctionHelper<N+1>::call(engine); } }; void RegisterScriptStdFunctionHelperN<N>::call

        enum {
            typedefs, ratio
        };

        RegisterScriptStdFunction(typedefs)(asIScriptEngine* engine)
        {
            int r = 0;
            std::string ns = engine->GetDefaultNamespace(); if (!ns.empty()) ns += "::";


            r = engine->RegisterTypedef("uintmax",
                sizeof(asUINTMAX) == sizeof(asINT32) ?
                "uint" :
                sizeof(asUINTMAX) == sizeof(asINT64) ?
                "uint64" :
                sizeof(asUINTMAX) == sizeof(asINT16) ?
                "uint16" :
                sizeof(asUINTMAX) == sizeof(asINT8) ?
                "uint8" :
                "{unsigned integral}"
            ); assert(r >= 0);

            r = engine->RegisterTypedef("intmax",
                sizeof(asUINTMAX) == sizeof(asINT32) ?
                "int" :
                sizeof(asUINTMAX) == sizeof(asINT64) ?
                "int64" :
                sizeof(asUINTMAX) == sizeof(asINT16) ?
                "int16" :
                sizeof(asUINTMAX) == sizeof(asINT8) ?
                "int8" :
                "{signed integral}"
            ); assert(r >= 0);

            r = engine->SetDefaultNamespace(ns.c_str()); assert(r >= 0);
        }
        RegisterScriptStdFunction(ratio)(asIScriptEngine* engine)
        {
            int r = 0;
            std::string ns = engine->GetDefaultNamespace(); if (!ns.empty()) ns += "::";
            const asQWORD flags = asOBJ_VALUE | asOBJ_APP_CLASS_CD;

            struct type
                : astd::ratio {
                struct meta
                {
#               define TYPE_NAME "ratio<intmax, intmax>"
                    static const char* type_cstr() throw() { return "ratio<intmax, intmax>"; }
                    static const char* ctor_cstr() throw() { return "void ctor(int&in)"; }
                    static const char* copy_ctor_cstr() throw() { return "void cctor(int&in, const " TYPE_NAME "&in)"; }
                    static const char* dtor_cstr() throw() { return "void dtor()"; }
#               undef TYPE_NAME
                };
                static void ctor(asITypeInfo& type_info, astd::ratio& that) { new(&that) astd::ratio(1,1); }
                static void copy_ctor(asITypeInfo& type_info, const astd::ratio& other, astd::ratio& that) { new(&that) astd::ratio(other); }
                static void dtor(astd::ratio& that) { that.~ratio(); }
            };

            r = engine->RegisterObjectType(
                type::meta::type_cstr(),
                sizeof(astd::ratio),
                flags | asOBJ_TEMPLATE
            ); assert(r >= 0);

            //r = engine->RegisterObjectBehaviour(
            //    type::meta::type_cstr(),
            //    asBEHAVE_CONSTRUCT,
            //    type::meta::ctor_cstr(),
            //    asFUNCTIONPR(type::ctor, (asITypeInfo&, astd::ratio&), void), asCALL_CDECL_OBJLAST
            //); assert(r >= 0);

            r = engine->RegisterObjectBehaviour(
                type::meta::type_cstr(),
                asBEHAVE_CONSTRUCT,
                type::meta::copy_ctor_cstr(),
                asFUNCTIONPR(type::copy_ctor, (asITypeInfo&, const astd::ratio&, astd::ratio&), void), asCALL_CDECL_OBJLAST
            ); assert(r >= 0);

            r = engine->RegisterObjectBehaviour(
                type::meta::type_cstr(),
                asBEHAVE_DESTRUCT,
                type::meta::dtor_cstr(),
                asFUNCTIONPR(type::dtor, (astd::ratio&), void), asCALL_CDECL_OBJLAST
            ); assert(r >= 0);

            r = engine->SetDefaultNamespace(ns.c_str()); assert(r >= 0);
        }

#   undef RegisterScriptStdFunction
    }

    static void RegisterScriptStdFunctions(asIScriptEngine* engine)
    {
        typedef RegisterScriptStdFunctionHelper<0> functions;
        functions::call(engine);
    }
}

int RegisterScriptStd_Ratio_Native(asIScriptEngine *engine)
{
    int r;  

    const std::string ns = engine->GetDefaultNamespace();

    r = engine->SetDefaultNamespace("std"); assert(r >= 0); if (r < 0) return r;

    astd_script::RegisterScriptStdFunctions(engine);

    r = engine->SetDefaultNamespace(""); assert(r >= 0); if (r < 0) return r;

    astd_script::RegisterScriptStdFunctions(engine);

    r = engine->SetDefaultNamespace(ns.c_str()); assert(r >= 0); if (r < 0) return r;

    return r;
}


int RegisterScriptStd_Ratio_Generic(asIScriptEngine *engine)
{
    int r = 0;

    // double versions of the same
    //r = engine->RegisterGlobalFunction("double cos(double)", asFUNCTION(cos_generic), asCALL_GENERIC); assert( r >= 0 );

    return r;
}

int RegisterScriptStd_Ratio(asIScriptEngine *engine)
{
    if( strstr(asGetLibraryOptions(), "AS_MAX_PORTABILITY") )
        return RegisterScriptStd_Ratio_Generic(engine);
    else
        return RegisterScriptStd_Ratio_Native(engine);
}

END_AS_NAMESPACE



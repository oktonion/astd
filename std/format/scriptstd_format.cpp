
#include "scriptstd_format.h"

#include "./fmt/format.h"
#include "./fmt/printf.h"

BEGIN_AS_NAMESPACE

namespace fmt {
    static uint64_t init_arg(void* reference, asETypeIdFlags typeID, ::fmt::internal::Value& out)
    {
        typedef ::fmt::internal::ArgArray<1> ArgArray;

        const int baseID = typeID & (asTYPEID_MASK_OBJECT | asTYPEID_MASK_SEQNBR);

        if (baseID <= asTYPEID_DOUBLE)
        {
            if (typeID & asTYPEID_MASK_OBJECT)
            { // the type is an object. 
                out = ArgArray::make<
                    ::fmt::BasicFormatter<char> >(reference);
                return ::fmt::internal::make_type(reference);
            }
            else if (baseID == asTYPEID_BOOL)
            {
                out = ArgArray::make<
                    ::fmt::BasicFormatter<char> >(*(bool*)reference);
                return ::fmt::internal::make_type(bool());
            }
            else if (baseID == asTYPEID_INT32)
            {
                out = ArgArray::make<
                    ::fmt::BasicFormatter<char> >(*(asINT32*)reference);
                return ::fmt::internal::make_type(asINT32());
            }
            else if (baseID == asTYPEID_INT16)
            {
                out = ArgArray::make<
                    ::fmt::BasicFormatter<char> >(*(asINT16*)reference);
                return ::fmt::internal::make_type(asINT16());
            }
            else if (baseID == asTYPEID_INT8)
            {
                out = ArgArray::make<
                    ::fmt::BasicFormatter<char> >(*(asINT8*)reference);
                return ::fmt::internal::make_type(asINT8());
            }
            else if (baseID == asTYPEID_UINT32)
            {
                out = ArgArray::make<
                    ::fmt::BasicFormatter<char> >(*(asUINT*)reference);
                return ::fmt::internal::make_type(asUINT());
            }
            else if (baseID == asTYPEID_UINT16)
            {
                out = ArgArray::make<
                    ::fmt::BasicFormatter<char> >(*(asWORD*)reference);
                return ::fmt::internal::make_type(asWORD());
            }
            else if (baseID == asTYPEID_UINT8)
            {
                out = ArgArray::make<
                    ::fmt::BasicFormatter<char> >(*(asBYTE*)reference);
                return ::fmt::internal::make_type(asBYTE());
            }
            else if (baseID == asTYPEID_DOUBLE)
            {
                out = ArgArray::make<
                    ::fmt::BasicFormatter<char> >(*(double*)reference);
                return ::fmt::internal::make_type(double());
            }
            else if (baseID == asTYPEID_FLOAT)
            {
                out = ArgArray::make<
                    ::fmt::BasicFormatter<char> >(*(float*)reference);
                return ::fmt::internal::make_type(float());
            }
        }
        else // user defined type
        {
            out = ArgArray::make<
                ::fmt::BasicFormatter<char> >(reference);
            return ::fmt::internal::make_type(reference);
        }

        return 0;
    }


    template<int ARGS_NUMBER>
    std::string& format_args(const std::string& format_str, void* (&reference)[ARGS_NUMBER], asETypeIdFlags(&typeID)[ARGS_NUMBER], std::string& result)
    {
        int i = 0;
        typedef ::fmt::internal::ArgArray<ARGS_NUMBER> ArgArray;
        typename ArgArray::Type array;
        uint64_t ArgArrayType = 0;


        for (int i = 0; i < ARGS_NUMBER; ++i)
        {
            ArgArrayType = ArgArrayType | (init_arg(reference[i], typeID[i], array[i]) << (i * 4));
        }
        ::fmt::format(format_str, fmt::ArgList(ArgArrayType, array)).swap(result);
        return result;
    }

    template<int ARGS_NUMBER>
    int printf_args(const std::string& format_str, void* (&reference)[ARGS_NUMBER], asETypeIdFlags(&typeID)[ARGS_NUMBER], int &result)
    {
        int i = 0;
        typedef ::fmt::internal::ArgArray<ARGS_NUMBER> ArgArray;
        typename ArgArray::Type array;
        uint64_t ArgArrayType = 0;


        for (int i = 0; i < ARGS_NUMBER; ++i)
        {
            ArgArrayType = ArgArrayType | (init_arg(reference[i], typeID[i], array[i]) << (i * 4));
        }
        result = ::fmt::printf(format_str, fmt::ArgList(ArgArrayType, array));
        return result;
    }

    template<int ARGS_NUMBER>
    int print_args(const std::string& format_str, void* (&reference)[ARGS_NUMBER], asETypeIdFlags(&typeID)[ARGS_NUMBER], int& result)
    {
        int i = 0;
        typedef ::fmt::internal::ArgArray<ARGS_NUMBER> ArgArray;
        typename ArgArray::Type array;
        uint64_t ArgArrayType = 0;


        for (int i = 0; i < ARGS_NUMBER; ++i)
        {
            ArgArrayType = ArgArrayType | (init_arg(reference[i], typeID[i], array[i]) << (i * 4));
        }
        ::fmt::print(format_str, fmt::ArgList(ArgArrayType, array));
        return result;
    }

    int flush_stdout() {
        return std::fflush(stdout);
    }

#define ref_typeID_pair(n) void* ref##n,asETypeIdFlags typeID##n
#define ref_typeID_pair_type(n) void*,asETypeIdFlags
#define ref(n) void* ref##n
#define typeID(n) asETypeIdFlags typeID##n
#define ref_param(n) ref##n
#define typeID_param(n) typeID##n
#define arg(n) ?&in arg##n


#define INLINE_FUNCTION_WITH_REFERENCE_DECL(fname, n) (const std::string& ,FMT_GEN(n,	ref_typeID_pair_type))

#define INLINE_FUNCTION_WITH_REFERENCE(rtype, fname, n)													  \
    inline																							      \
    rtype fname##n(const std::string& format_str													      \
        ,FMT_GEN(n,	ref_typeID_pair)														              \
    )                                                                                                     \
    {																									  \
        rtype result;																				      \
        void* reference[] = { FMT_GEN(n, ref_param) };													  \
        asETypeIdFlags typeID[] = { FMT_GEN(n, typeID_param) };											  \
        return fname##_args(format_str, reference, typeID, result);										  \
    }                                                                                                     

#define INLINE_FUNCTION_WITH_REFERENCE_SIG_IMPL(rtype, fname, n)                                          \
    rtype fname(const string&in format_str 													              \
        ,FMT_GEN(n,	arg)														                          \
    )


#define TO_STR_IMPL(val) #val
#define TO_STR(val) TO_STR_IMPL(val)
#define INLINE_FUNCTION_WITH_REFERENCE_SIG(rtype, fname, n) TO_STR(INLINE_FUNCTION_WITH_REFERENCE_SIG_IMPL(rtype, fname, n))

    inline
    std::string format0(const std::string& format_str) { return ::fmt::format(format_str); }
    inline
    int printf0(const std::string& format_str) { return ::fmt::printf(format_str); }
    inline
    void print0(const std::string& format_str) { return ::fmt::print(format_str); }

INLINE_FUNCTION_WITH_REFERENCE(std::string, format, 1);
INLINE_FUNCTION_WITH_REFERENCE(std::string, format, 2);
INLINE_FUNCTION_WITH_REFERENCE(std::string, format, 3);
INLINE_FUNCTION_WITH_REFERENCE(std::string, format, 4);
INLINE_FUNCTION_WITH_REFERENCE(std::string, format, 5);
INLINE_FUNCTION_WITH_REFERENCE(std::string, format, 6);

INLINE_FUNCTION_WITH_REFERENCE(int, printf, 1);
INLINE_FUNCTION_WITH_REFERENCE(int, printf, 2);
INLINE_FUNCTION_WITH_REFERENCE(int, printf, 3);
INLINE_FUNCTION_WITH_REFERENCE(int, printf, 4);
INLINE_FUNCTION_WITH_REFERENCE(int, printf, 5);
INLINE_FUNCTION_WITH_REFERENCE(int, printf, 6);

INLINE_FUNCTION_WITH_REFERENCE(int, print, 1);
INLINE_FUNCTION_WITH_REFERENCE(int, print, 2);
INLINE_FUNCTION_WITH_REFERENCE(int, print, 3);
INLINE_FUNCTION_WITH_REFERENCE(int, print, 4);
INLINE_FUNCTION_WITH_REFERENCE(int, print, 5);
INLINE_FUNCTION_WITH_REFERENCE(int, print, 6);
}

static void RegisterScriptFmt_Native_Global(asIScriptEngine *engine)
{
    int r;

    r = engine->RegisterGlobalFunction(
        "int flush_stdout()",
        asFUNCTIONPR(fmt::flush_stdout,
            (),
            int
        ),
        asCALL_CDECL
    ); assert(r >= 0);

    std::fflush(stdout);

   r = engine->RegisterGlobalFunction(                           
        "string format(const string&in format_str)",
        asFUNCTIONPR(fmt::format0,                                   
            (const std::string&),
            std::string
        ),                                                            
        asCALL_CDECL                                                  
    ); assert( r >= 0 );

   r = engine->RegisterGlobalFunction(
       "int printf(const string&in format_str)",
       asFUNCTIONPR(fmt::printf0,
           (const std::string&),
           int
       ),
       asCALL_CDECL
   ); assert(r >= 0);

   r = engine->RegisterGlobalFunction(
       "void print(const string&in format_str)",
       asFUNCTIONPR(fmt::print0,
           (const std::string&),
           void
       ),
       asCALL_CDECL
   ); assert(r >= 0);

#define REGISTER_GLOBAL_FUNCTION(rtype_scr, rtype, fname, n)           \
    r = engine->RegisterGlobalFunction(                                \
        INLINE_FUNCTION_WITH_REFERENCE_SIG(rtype_scr, fname, n),       \
        asFUNCTIONPR(fmt::fname##n,                                    \
            INLINE_FUNCTION_WITH_REFERENCE_DECL(fname, n),             \
            rtype                                                      \
        ),                                                             \
        asCALL_CDECL                                                   \
    ); assert( r >= 0 );

    REGISTER_GLOBAL_FUNCTION(string, std::string, format, 1);
    REGISTER_GLOBAL_FUNCTION(string, std::string, format, 2);
    REGISTER_GLOBAL_FUNCTION(string, std::string, format, 3);
    REGISTER_GLOBAL_FUNCTION(string, std::string, format, 4);
    REGISTER_GLOBAL_FUNCTION(string, std::string, format, 5);
    REGISTER_GLOBAL_FUNCTION(string, std::string, format, 6);

    REGISTER_GLOBAL_FUNCTION(int, int, printf, 1);
    REGISTER_GLOBAL_FUNCTION(int, int, printf, 2);
    REGISTER_GLOBAL_FUNCTION(int, int, printf, 3);
    REGISTER_GLOBAL_FUNCTION(int, int, printf, 4);
    REGISTER_GLOBAL_FUNCTION(int, int, printf, 5);
    REGISTER_GLOBAL_FUNCTION(int, int, printf, 6);

    REGISTER_GLOBAL_FUNCTION(void, int, print, 1);
    REGISTER_GLOBAL_FUNCTION(void, int, print, 2);
    REGISTER_GLOBAL_FUNCTION(void, int, print, 3);
    REGISTER_GLOBAL_FUNCTION(void, int, print, 4);
    REGISTER_GLOBAL_FUNCTION(void, int, print, 5);
    REGISTER_GLOBAL_FUNCTION(void, int, print, 6);

}

static void RegisterScriptFmt_Native_Std(asIScriptEngine* engine)
{
    const std::string ns = engine->GetDefaultNamespace();
    engine->SetDefaultNamespace("std");
    RegisterScriptFmt_Native_Global(engine);
    engine->SetDefaultNamespace(ns.c_str());
}

void RegisterScriptFmt_Native(asIScriptEngine* engine)
{
    RegisterScriptFmt_Native_Global(engine);
    RegisterScriptFmt_Native_Std(engine);
}

namespace fmt {
    std::string format_generic1(asIScriptGeneric* gen)
    {
        void* f1 = gen->GetAddressOfArg(0);
        void* f2 = gen->GetAddressOfArg(1);
        *(double*)gen->GetAddressOfReturnLocation();// = pow(f1, f2);
        return "";
    }
}
void RegisterScriptFmt_Generic(asIScriptEngine *engine)
{
    int r;

    // double versions of the same
    //r = engine->RegisterGlobalFunction("double cos(double)", asFUNCTION(cos_generic), asCALL_GENERIC); assert( r >= 0 );
}

void RegisterScriptFmt(asIScriptEngine *engine)
{
    if( strstr(asGetLibraryOptions(), "AS_MAX_PORTABILITY") )
        RegisterScriptFmt_Generic(engine);
    else
        RegisterScriptFmt_Native(engine);
}

END_AS_NAMESPACE




#include "scriptstd_algorithm.h"

#include <algorithm>
#include <cassert>
#include <exception>
#include <stdexcept>
#include <string>
#include <cstdio>
#include <cstring>

BEGIN_AS_NAMESPACE


namespace astd {

    struct LegacyIteratorScriptFunctions {
        asIScriptFunction* opPreInc;
        asIScriptFunction* opPostInc;

        LegacyIteratorScriptFunctions()
            : opPreInc(0), opPostInc(0) { }

        void swap(LegacyIteratorScriptFunctions& other) {
            std::swap(*this, other);
        }
    };

    struct LegacyIterator
        : LegacyIteratorScriptFunctions 
    {

        struct Concept
            : LegacyIteratorScriptFunctions
        {
            Concept(const asITypeInfo* type_info) {
                if (!type_info)
                {
                    value = false;
                    return;
                }
                 opPreInc = type_info->GetMethodByName("opPreInc");
                 opPostInc = type_info->GetMethodByName("opPostInc");

                value =
                    opPreInc &&
                    opPostInc &&
                    (type_info->GetFlags() & asOBJ_APP_CLASS_C) &&
                    (type_info->GetFlags() & asOBJ_APP_CLASS_K)
                    ;
            }

            bool operator!() const {
                return !value;
            }

            bool value;
        };

        LegacyIterator(void* data, int type)
            : data(data), type(type) {
            init();
        }

        const asITypeInfo* type_info() const
        {
            asIScriptContext* script_ctx = asGetActiveContext();
            asIScriptEngine* script_engine = script_ctx->GetEngine();
            const asITypeInfo* type_info = script_engine->GetTypeInfoById(type);
            return type_info;
        }

        bool init() {
            Concept c(type_info()); c.swap(*this);
            return !!c;
        }

        static std::string to_string(int i) {

            char buf[1024] = { 0 };
            {using namespace std; sprintf(buf, "%d", i); }
        }

        LegacyIterator &operator++() {
            if (!opPreInc) return *this;
            asIScriptFunction* func = opPreInc;
            asIScriptContext* script_ctx = asGetActiveContext();

            script_ctx->Prepare(func); 
            const asEContextState state = asEContextState(
                script_ctx->Execute()
            );

            if (asEXECUTION_FINISHED != state)
            {
                if (asEXECUTION_EXCEPTION == state)
                {
                    throw std::runtime_error(
                        "Unexpected exception '" +
                        std::string(script_ctx->GetExceptionString()) + "' occured at line " +
                        to_string(script_ctx->GetExceptionLineNumber())

                    );
                }
            }

            return *this;
        }

        LegacyIterator& operator++(int) {
            if (!opPostInc) return *this;
            asIScriptFunction* func = opPostInc;
            asIScriptContext* script_ctx = asGetActiveContext();

            script_ctx->Prepare(func);
            const asEContextState state = asEContextState(
                script_ctx->Execute()
            );

            if (asEXECUTION_FINISHED != state)
            {
                if (asEXECUTION_EXCEPTION == state)
                {
                    throw std::runtime_error(
                        "Unexpected exception '" +
                        std::string(script_ctx->GetExceptionString()) + "' occured at line " +
                        to_string(script_ctx->GetExceptionLineNumber())

                    );
                }
            }

            return *this;
        }

    protected:
        void* data;
        int type;

    public:
        struct Script {
            typedef LegacyIterator Type;
            static const char(&Type_cstr())[sizeof "LegacyIterator"]
            { static const char name[] = "LegacyIterator"; return name; }
                static const char(&TypeTmpl_cstr())[sizeof "LegacyIterator<Iterator>"]
            { static const char name[] = "LegacyIterator<Iterator>"; return name; }
                static const char(&TypeTmplClass_cstr())[sizeof "LegacyIterator<class Iterator>"]
            { static const char name[] = "LegacyIterator<class Iterator>"; return name; }


            static void Construct(Type* memory, void* data, int type)
            {
                asIScriptContext* script_ctx = asGetActiveContext();
                asIScriptEngine* script_engine = script_ctx->GetEngine();
                const asITypeInfo *type_info = script_engine->GetTypeInfoById(type);


                if (!Concept(type_info))
                {
                    struct {
                        int row, col;
                        const char* sectionName;
                    } context_info;
                    context_info.row = 
                        script_ctx->GetLineNumber(0, &context_info.col, &context_info.sectionName);
                    script_engine->WriteMessage(
                        context_info.sectionName, context_info.row, context_info.col,
                        asMSGTYPE_ERROR,
                        "Iterator is not LegacyIterator"
                    );
                    script_ctx->SetException("Iterator is not LegacyIterator", false);
                }

                if (memory) new(memory) LegacyIterator(data, type);
            }

            static void Destruct(LegacyIterator* memory)
            {
                if (memory) memory->~LegacyIterator();
            }

            static bool InstatiateTemplate(asITypeInfo* type_info, bool& dontGarbageCollect)
            {
                bool template_can_be_instatiated = 
                    !!Concept(type_info);


                //dontGarbageCollect = true;
                return template_can_be_instatiated;
            }

            static int Register(asIScriptEngine* engine)
            {
                int r;

                {
                    r = engine->RegisterObjectType(TypeTmplClass_cstr(),
                        sizeof(Type),
                        asOBJ_VALUE | asOBJ_APP_CLASS_CDAK | asOBJ_TEMPLATE
                    ); assert(r >= 0); if (r < 0) return r;

                    r = engine->RegisterObjectBehaviour(TypeTmpl_cstr(),
                        asBEHAVE_CONSTRUCT,
                        "void ctor(const ?&in)",
                        asFUNCTIONPR(Construct, (Type*, void*, int), void), asCALL_CDECL_OBJFIRST
                    ); assert(r >= 0); if (r < 0) return r;

                    r = engine->RegisterObjectBehaviour(TypeTmpl_cstr(),
                        asBEHAVE_DESTRUCT,
                        "void dtor()",
                        asFUNCTIONPR(Destruct, (Type*), void), asCALL_CDECL_OBJFIRST
                    ); assert(r >= 0); if (r < 0) return r;

                    r = engine->RegisterObjectBehaviour(TypeTmpl_cstr(),
                        asBEHAVE_TEMPLATE_CALLBACK, 
                        "bool template(?&in, bool&out)", 
                        asFUNCTION(InstatiateTemplate), asCALL_CDECL
                    ); assert(r >= 0); if (r < 0) return r;
                }

                return 0;
            }
        };

    };


    struct LegacyInputIteratorScriptFunctions {
        asIScriptFunction* opEquals;

        LegacyInputIteratorScriptFunctions()
            : opEquals(0) { }

        void swap(LegacyInputIteratorScriptFunctions& other) {
            std::swap(*this, other);
        }
    };

    struct LegacyInputIterator
        : LegacyIterator
        , LegacyInputIteratorScriptFunctions
    {
        struct Concept
            : LegacyIterator::Concept
            , LegacyInputIteratorScriptFunctions 
        {
            Concept(const asITypeInfo* type_info)
                : LegacyIterator::Concept(type_info)
            {
                if (!value) return;
                opEquals = type_info->GetMethodByName("opEquals");

                value = !!opEquals && value;
            }

            void swap(LegacyInputIterator& other)
            {
                LegacyInputIteratorScriptFunctions::swap(other);
                LegacyIteratorScriptFunctions::swap(other);
            }
        };

        LegacyInputIterator(void* data, int type)
            : LegacyIterator(data, type)
        { init(); }

        bool init() {
            Concept c(type_info()); c.swap(*this);
            return !!c;
        }

        bool operator==(const LegacyInputIterator& other) const
        {
            if (!opEquals) return false;
            asIScriptFunction* func = opEquals;
            asIScriptContext* script_ctx = asGetActiveContext();

            script_ctx->Prepare(func);
            const asEContextState state = asEContextState(
                script_ctx->Execute()
            );

            if (asEXECUTION_FINISHED != state)
            {
                if (asEXECUTION_EXCEPTION == state)
                    throw std::runtime_error(
                        "Unexpected exception '" +
                        std::string(script_ctx->GetExceptionString()) + "' occured at line " +
                        to_string(script_ctx->GetExceptionLineNumber())

                    );
            }

            asBYTE result = script_ctx->GetReturnByte();

            return result != 0;
        }

        bool operator!=(const LegacyInputIterator& other) const
        {
            return !(*this == other);
        }

        struct Script {
            typedef LegacyInputIterator Type;
            static const char(&Type_cstr())[sizeof "LegacyInputIterator"]
            { static const char name[] = "LegacyInputIterator"; return name; }
                static const char(&TypeTmpl_cstr())[sizeof "LegacyInputIterator<Iterator>"]
            { static const char name[] = "LegacyInputIterator<Iterator>"; return name; }
                static const char(&TypeTmplClass_cstr())[sizeof "LegacyInputIterator<class Iterator>"]
            { static const char name[] = "LegacyInputIterator<class Iterator>"; return name; }


            static void Construct(Type* memory, void* data, int type)
            {
                asIScriptContext* script_ctx = asGetActiveContext();
                asIScriptEngine* script_engine = script_ctx->GetEngine();
                const asITypeInfo* type_info = script_engine->GetTypeInfoById(type);


                if (!Concept(type_info))
                {
                    struct {
                        int row, col;
                        const char* sectionName;
                    } context_info;
                    context_info.row =
                        script_ctx->GetLineNumber(0, &context_info.col, &context_info.sectionName);
                    script_engine->WriteMessage(
                        context_info.sectionName, context_info.row, context_info.col,
                        asMSGTYPE_ERROR,
                        "Iterator is not LegacyInputIterator"
                    );
                    script_ctx->SetException("Iterator is not LegacyInputIterator", false);
                }

                if (memory) new(memory) Type(data, type);
            }

            static void Destruct(Type* memory)
            {
                if (memory) memory->~Type();
            }

            static bool InstatiateTemplate(asITypeInfo* type_info, bool& dontGarbageCollect)
            {
                bool template_can_be_instatiated =
                    !!Concept(type_info);


                //dontGarbageCollect = true;
                return template_can_be_instatiated;
            }

            static int Register(asIScriptEngine* engine)
            {
                int r;

                {
                    r = engine->RegisterObjectType(TypeTmplClass_cstr(),
                        sizeof(Type),
                        asOBJ_VALUE | asOBJ_APP_CLASS_CDAK | asOBJ_TEMPLATE
                    ); assert(r >= 0); if (r < 0) return r;

                    r = engine->RegisterObjectBehaviour(TypeTmpl_cstr(),
                        asBEHAVE_CONSTRUCT,
                        "void ctor(const ?&in)",
                        asFUNCTIONPR(Construct, (Type*, void*, int), void), asCALL_CDECL_OBJFIRST
                    ); assert(r >= 0); if (r < 0) return r;

                    r = engine->RegisterObjectBehaviour(TypeTmpl_cstr(),
                        asBEHAVE_DESTRUCT,
                        "void dtor()",
                        asFUNCTIONPR(Destruct, (Type*), void), asCALL_CDECL_OBJFIRST
                    ); assert(r >= 0); if (r < 0) return r;

                    r = engine->RegisterObjectBehaviour(TypeTmpl_cstr(),
                        asBEHAVE_TEMPLATE_CALLBACK,
                        "bool template(?&in, bool&out)",
                        asFUNCTION(InstatiateTemplate), asCALL_CDECL
                    ); assert(r >= 0); if (r < 0) return r;
                }

                return 0;
            }
        };
    };


    struct LegacyOutputIteratorScriptFunctions {
        asIScriptFunction* fGet; 

        LegacyOutputIteratorScriptFunctions()
            : fGet(0) { }

        void swap(LegacyOutputIteratorScriptFunctions& other) {
            std::swap(*this, other);
        }
    };

    struct LegacyOutputIterator
        : LegacyIterator
        , LegacyOutputIteratorScriptFunctions
    {
        struct Concept
            : LegacyIterator::Concept
            , LegacyOutputIteratorScriptFunctions
        {
            Concept(const asITypeInfo* type_info)
                : LegacyIterator::Concept(type_info)
            {
                if (!value) return;
                fGet = type_info->GetMethodByName("get");

                if (!fGet)
                    fGet = type_info->GetMethodByName("get_value");

                value = !!fGet && value;
                if (!value) return;


                int value_type = fGet->GetReturnTypeId();

                if (value_type <= asTYPEID_DOUBLE)
                    return;

                const asITypeInfo* value_type_info = 
                    type_info->GetEngine()->GetTypeInfoById(value_type);
                value = !!value_type_info && value;
                if (!value) return;

                value = (value_type_info->GetFlags() & asOBJ_APP_CLASS_A) || (value_type_info->GetFlags() & asOBJ_APP_PRIMITIVE);
            }

            void swap(LegacyOutputIterator& other)
            {
                LegacyOutputIteratorScriptFunctions::swap(other);
                LegacyIteratorScriptFunctions::swap(other);
            }
        };

        LegacyOutputIterator(void* data, int type)
            : LegacyIterator(data, type)
        {
            init();
        }

        bool init() {
            Concept c(type_info()); c.swap(*this);
            return !!c;
        }

        void get(void *&result, int &result_type) const
        {
            if (!fGet) return ;
            asIScriptFunction* func = fGet;
            asIScriptContext* script_ctx = asGetActiveContext();

            script_ctx->Prepare(func);
            const asEContextState state = asEContextState(
                script_ctx->Execute()
            );

            if (asEXECUTION_FINISHED != state)
            {
                if (asEXECUTION_EXCEPTION == state)
                    throw std::runtime_error(
                        "Unexpected exception '" +
                        std::string(script_ctx->GetExceptionString()) + "' occured at line " +
                        to_string(script_ctx->GetExceptionLineNumber())

                    );
            }

            result = script_ctx->GetReturnAddress();
            result_type = func->GetReturnTypeId();
        }



        struct Script {
            typedef LegacyOutputIterator Type;
            static const char(&Type_cstr())[sizeof "LegacyOutputIterator"]
            { static const char name[] = "LegacyOutputIterator"; return name; }
                static const char(&TypeTmpl_cstr())[sizeof "LegacyOutputIterator<Iterator>"]
            { static const char name[] = "LegacyOutputIterator<Iterator>"; return name; }
                static const char(&TypeTmplClass_cstr())[sizeof "LegacyOutputIterator<class Iterator>"]
            { static const char name[] = "LegacyOutputIterator<class Iterator>"; return name; }


            static void Construct(Type* memory, void* data, int type)
            {
                asIScriptContext* script_ctx = asGetActiveContext();
                asIScriptEngine* script_engine = script_ctx->GetEngine();
                const asITypeInfo* type_info = script_engine->GetTypeInfoById(type);


                if (!Concept(type_info))
                {
                    struct {
                        int row, col;
                        const char* sectionName;
                    } context_info;
                    context_info.row =
                        script_ctx->GetLineNumber(0, &context_info.col, &context_info.sectionName);
                    script_engine->WriteMessage(
                        context_info.sectionName, context_info.row, context_info.col,
                        asMSGTYPE_ERROR,
                        "Iterator is not LegacyOutputIterator"
                    );
                    script_ctx->SetException("Iterator is not LegacyOutputIterator", false);
                }

                if (memory) new(memory) Type(data, type);
            }

            static void Construct(Type* memory, const Type& other)
            {
                new(memory)Type(other);
            }

            static void Destruct(Type* memory)
            {
                if (memory) memory->~Type();
            }

            static bool InstatiateTemplate(asITypeInfo* type_info, bool& dontGarbageCollect)
            {
                bool template_can_be_instatiated =
                    !!Concept(type_info);


                //dontGarbageCollect = true;
                return template_can_be_instatiated;
            }

            static int Register(asIScriptEngine* engine)
            {
                int r;

                {
                    r = engine->RegisterObjectType(TypeTmplClass_cstr(),
                        sizeof(Type),
                        asOBJ_VALUE |  asOBJ_TEMPLATE
                    ); assert(r >= 0); if (r < 0) return r;

                    r = engine->RegisterObjectBehaviour(TypeTmpl_cstr(),
                        asBEHAVE_CONSTRUCT,
                        "void ctor(const ?&in)",
                        asFUNCTIONPR(Construct, (Type*, void*, int), void), asCALL_CDECL_OBJFIRST
                    ); assert(r >= 0); if (r < 0) return r;
                    
                    //r = engine->RegisterObjectBehaviour(TypeTmpl_cstr(),
                    //    asBEHAVE_CONSTRUCT,
                    //    "void cctor(const LegacyOutputIterator &in)",
                    //    asFUNCTIONPR(Construct, (Type*, const Type&), void), asCALL_CDECL_OBJFIRST
                    //); assert(r >= 0); if (r < 0) return r;
                    
                    r = engine->RegisterObjectBehaviour(TypeTmpl_cstr(),
                        asBEHAVE_DESTRUCT,
                        "void dtor()",
                        asFUNCTIONPR(Destruct, (Type*), void), asCALL_CDECL_OBJFIRST
                    ); assert(r >= 0); if (r < 0) return r;

                    //r = engine->RegisterObjectBehaviour(TypeTmpl_cstr(),
                    //    asBEHAVE_TEMPLATE_CALLBACK,
                    //    "bool template(?&in, bool&out)",
                    //    asFUNCTION(InstatiateTemplate), asCALL_CDECL
                    //); assert(r >= 0); if (r < 0) return r;
                }

                return 0;
            }
        };
    };
    static LegacyOutputIterator copy(const LegacyInputIterator& first_iterator, const LegacyInputIterator& last_iterator,
        LegacyOutputIterator &first_iterator_dst)
    {
        //return std::copy(first_iterator, last_iterator, first_iterator_dst);
        return first_iterator_dst;
    }
}

static void RegisterScriptStd_Algorithm_Native_Global(asIScriptEngine *engine)
{
   int r;

   r = astd::LegacyIterator::Script::Register(engine); assert(r >= 0);
   r = astd::LegacyInputIterator::Script::Register(engine); assert(r >= 0);
   r = astd::LegacyOutputIterator::Script::Register(engine); assert(r >= 0);

   r = engine->RegisterGlobalFunction(                           
        "LegacyOutputIterator<Iterator>& copy(const LegacyInputIterator<Iterator>&in first_iterator, const LegacyInputIterator<Iterator>&in last_iterator, LegacyOutputIterator<Iterator> &in first_iterator_dst)",
        asFUNCTION(astd::copy),                                                            
        asCALL_CDECL                                                  
    ); assert( r >= 0 );
}

static void RegisterScriptStd_Algorithm_Native_Std(asIScriptEngine* engine)
{
    engine->SetDefaultNamespace("std");
    RegisterScriptStd_Algorithm_Native_Global(engine);
    engine->SetDefaultNamespace("");
}

void RegisterScriptStd_Algorithm_Native(asIScriptEngine* engine)
{
    RegisterScriptStd_Algorithm_Native_Global(engine);
    RegisterScriptStd_Algorithm_Native_Std(engine);
}


void RegisterScriptStd_Algorithm_Generic(asIScriptEngine *engine)
{
    int r;

    // double versions of the same
    //r = engine->RegisterGlobalFunction("double cos(double)", asFUNCTION(cos_generic), asCALL_GENERIC); assert( r >= 0 );
}

void RegisterScriptStd_Algorithm(asIScriptEngine *engine)
{
    if( strstr(asGetLibraryOptions(), "AS_MAX_PORTABILITY") )
        RegisterScriptStd_Algorithm_Generic(engine);
    else
        RegisterScriptStd_Algorithm_Native(engine);
}

END_AS_NAMESPACE



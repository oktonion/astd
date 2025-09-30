#ifndef SCRIPTSTD_MEMORY_H
#define SCRIPTSTD_MEMORY_H

#include <cstring>

#ifndef ANGELSCRIPT_H 
// Avoid having to inform include path if header is already include before
#include <angelscript.h>
#endif


BEGIN_AS_NAMESPACE

namespace astd {
    struct ptr_memory {

        ptr_memory(asIScriptEngine& engine, void* address, int subTypeId);
        ptr_memory(const ptr_memory& other);
        ptr_memory& operator=(const ptr_memory&);
        ~ptr_memory() throw();

        void* address() throw();
        const void* address() const throw();

    private:
        unsigned char data[sizeof(void*) * 2];

    };
}

template<class T, void(*FUNCTION)(T*, void*&, int&)>
int RegisterScriptStd_Memory_DataMixin(asIScriptEngine* engine, const char *type_decl) {

    struct lambdas {
        typedef T type;

        static astd::ptr_memory data(type* that)
        {
            void* address = NULL;
            int typeId = 0;

            FUNCTION(that, address, typeId);

            return astd::ptr_memory(*(asGetActiveContext()->GetEngine()), address, typeId);
        }
        static void data_generic(asIScriptGeneric* gen)
        {
            type* that = (type*)gen->GetObject();
            astd::ptr_memory result = data(that);
            gen->SetReturnObject(&result); // should copy
        }
    };

    int r = -1;
    if (type_decl && engine)
    {
        using namespace std;
        const bool generic_call = !!strstr(asGetLibraryOptions(), "AS_MAX_PORTABILITY");

        if (!engine->GetTypeInfoByDecl("ptr<T>")) return r;

        r = engine->RegisterObjectMethod(
            type_decl,
            "ptr<T> data()",
            generic_call ? asFUNCTION(lambdas::data_generic) : asFUNCTION(lambdas::data), generic_call ? asCALL_GENERIC : asCALL_CDECL_OBJFIRST
        ); if (r < 0) return r;

        r = engine->RegisterObjectMethod(
            type_decl,
            "const ptr<T> data() const",
            generic_call ? asFUNCTION(lambdas::data_generic) : asFUNCTION(lambdas::data), generic_call ? asCALL_GENERIC : asCALL_CDECL_OBJFIRST
        ); if (r < 0) return r;
    }

    return r;
}
template<void* (*FUNCTION)(void*)>
int RegisterScriptStd_Memory_DataMixin(asIScriptEngine* engine, asITypeInfo* type_info) {
    return RegisterScriptStd_Memory_DataMixin<void*, FUNCTION>(engine, type_info);
}


// This function will determine the configuration of the engine
// and use one of the two functions below to register the functions
int RegisterScriptStd_Memory(asIScriptEngine *engine);

// Call this function to register the functions
// using native calling conventions
int RegisterScriptStd_Memory_Native(asIScriptEngine *engine);

// Use this one instead if native calling conventions
// are not supported on the target platform
int RegisterScriptStd_Memory_Generic(asIScriptEngine *engine);

END_AS_NAMESPACE

#endif


#include "scriptstd_memory.h"

#include <memory>
#include <cassert>
#include <exception>
#include <stdexcept>
#include <string>
#include <cstring>
#include <climits>
#include <cstddef>


BEGIN_AS_NAMESPACE


namespace astd {
    namespace cstddef {
        using namespace std;
        namespace {
            typedef ptrdiff_t ptrdiff_type;
        }
    }


    struct ptr {
        typedef cstddef::ptrdiff_type intptr_t;
        intptr_t address;
        asITypeInfo* typeinfo;

        typedef char pointer_size_must_be_equal_int[sizeof(intptr_t) == sizeof(void*) ? 1 : -1];

        ptr(asITypeInfo* typeinfo, int address = 0
            , int(*)[sizeof(pointer_size_must_be_equal_int)] = 0)
            throw()
            : address(address)
            , typeinfo(typeinfo)
        { }

        ptr(asITypeInfo* typeinfo, void* address
            , int(*)[sizeof(pointer_size_must_be_equal_int)] = 0)
            throw()
            : address(0)
            , typeinfo(typeinfo)
        { 
            std::memcpy(&(this->address), &address, sizeof(address));
        }

        ptr(const ptr &other, asITypeInfo* typeinfo
            , int(*)[sizeof(pointer_size_must_be_equal_int)] = 0)
            throw()
            : address(other.address)
            , typeinfo(typeinfo)
        { }

        ~ptr() throw() 
        { }

        ptr& operator=(const ptr& other) throw() 
        {
            address = other.address;
            typeinfo = other.typeinfo;
            return *this;
        }


        std::size_t size(int(*)[sizeof(pointer_size_must_be_equal_int)] = 0) const throw() 
        {
            std::size_t result = 1;
            if (typeinfo) {
                asITypeInfo* subtype = typeinfo->GetSubType();
                if (subtype)
                    result = subtype->GetSize();
                else
                {
                    const int subtype_id = typeinfo->GetSubTypeId();
                    asIScriptContext* ctx = asGetActiveContext();
                    if (ctx)
                    {
                        asIScriptEngine* engine = ctx->GetEngine();
                        if (engine)
                            return engine->GetSizeOfPrimitiveType(subtype_id);
                    }
                }
            }
            if (result) return result;
            return 1;
        }

        ptr& operator++() throw()
        {
            address += size();
            return *this;
        }

        ptr operator++(int) throw()
        {
            ptr tmp = *this;
            address += size();
            return tmp;
        }

        ptr operator+(int shift) const throw()
        {
            return ptr(typeinfo, address + shift * size());
        }

        ptr operator-(int shift) const throw()
        {
            return ptr(typeinfo, address - shift * size());
        }

        ptr& operator+=(int shift) throw()
        {
            address += shift * size();
            return *this;
        }

        ptr& operator-=(int shift) throw()
        {
            address -= shift * size();
            return *this;
        }

        void* operator[](int index) throw()
        {
            unsigned char* data = 0;
            std::memcpy(&data, &address, sizeof(data));
            if (data) data += index * size();
            return data;
        }

        const void* operator[](int index) const throw()
        {
            const unsigned char* data = 0;
            std::memcpy(&data, &address, sizeof(data));
            if (data) data += index * size();
            return data;
        }

        bool operator==(const ptr& other) const throw()
        {
            if (typeinfo != other.typeinfo)
                return false;
            if (typeinfo && typeinfo->GetTypeId() != other.typeinfo->GetTypeId())
                return false;

            return address == other.address;
        }

        bool operator!=(const ptr& other) const throw()
        {
            return !(*this == other);
        }

        bool operator<(const ptr& other) const throw()
        {
            if (typeinfo != other.typeinfo)
                return typeinfo < other.typeinfo;
            return address < other.address;
        }

        bool operator>(const ptr& other) const throw()
        {
            if (typeinfo != other.typeinfo)
                return typeinfo > other.typeinfo;
            return address > other.address;
        }

        void* operator&() throw() {
            return &address;
        }
        const void* operator&() const throw() {
            return &address;
        }
    };

    typedef char ptr_memory_size_must_be_equal_ptr_size[sizeof(ptr_memory) == sizeof(ptr) ? 1 : -1];


    static ptr addressof(const void* reference, int typeId) {
        asIScriptEngine* engine = asGetActiveContext()->GetEngine();
        ptr memory = 
            engine->GetTypeInfoById(typeId);
        std::memcpy(&memory.address, &reference, sizeof(reference));
        return memory;
    }   


    ptr_memory::ptr_memory(asIScriptEngine& engine, void* address, int typeId) {
        const char* subTypeDecl = engine.GetTypeDeclaration(typeId, true);

        new(data) astd::ptr(engine.GetTypeInfoByDecl(
            (std::string("ptr<") + (subTypeDecl ? subTypeDecl : "T") + ">").c_str()
        ), address);
    }
    ptr_memory::ptr_memory(const ptr_memory& other) {
        std::memcpy(data, other.data, sizeof(data));
    }
    ptr_memory::~ptr_memory() throw() {
        reinterpret_cast<astd::ptr*>(data)->~ptr();
    }

    void* ptr_memory::address() throw()
    {
        void* result = NULL;
        std::memcpy(result, &reinterpret_cast<astd::ptr*>(data)->address, sizeof(result));
        return result;
    }

    const void* ptr_memory::address() const throw()
    {
        void* result = NULL;
        std::memcpy(result, &reinterpret_cast<const astd::ptr*>(data)->address, sizeof(result));
        return result;
    }
}

namespace astd {

    static asUINT size_of(const void*, int type)
    {
        asIScriptContext* ctx = asGetActiveContext();
        asIScriptEngine* engine = ctx->GetEngine();


        const std::size_t type_size =
            type <= asTYPEID_DOUBLE
            ? engine->GetSizeOfPrimitiveType(type)
            : engine->GetTypeInfoById(type)->GetSize()
            ;

        return type_size;
    }


    static ptr memcpy(ptr dst, ptr src, asUINT count)
    {
        unsigned char* dst_addr = 0;
        const unsigned char* src_addr = 0;
        std::memcpy(&dst_addr, &dst.address, sizeof(dst_addr));
        std::memcpy(&src_addr, &src.address, sizeof(src_addr));

        void *result_addr = std::memcpy(dst_addr, src_addr, count);
        ptr result = dst.typeinfo;
        std::memcpy(&result.address, &result_addr, sizeof(result_addr));
        return result;
    }

    namespace unsafe {
        static void bytecpy(unsigned char* dst, int dst_type, asUINT dst_byte_offset, const unsigned char* src, int src_type, asUINT src_byte_offset, asUINT count)
        {
            asIScriptContext* ctx = asGetActiveContext();
            asIScriptEngine* engine = ctx->GetEngine();


            const std::size_t dst_size =
                dst_type <= asTYPEID_DOUBLE
                ? engine->GetSizeOfPrimitiveType(dst_type)
                : engine->GetTypeInfoById(dst_type)->GetSize()
                ;
            const std::size_t src_size =
                src_type <= asTYPEID_DOUBLE
                ? engine->GetSizeOfPrimitiveType(src_type)
                : engine->GetTypeInfoById(src_type)->GetSize()
                ;

            if (dst_size && (count + dst_byte_offset) > dst_size)
                throw(std::logic_error("cannot copy bytes - destination buffer too small"));
            if (src_size && (count + src_byte_offset) > src_size)
                throw(std::logic_error("cannot copy bytes - source buffer too small"));

            std::memcpy(dst + dst_byte_offset, src + src_byte_offset, count);
        }

        static void bitcpy(unsigned char* dst, int dst_type, asUINT dst_bit_offset, const unsigned char* src, int src_type, asUINT src_bit_offset, asUINT count)
        {
            const std::size_t dst_byte_offset = (dst_bit_offset % CHAR_BIT);
            const std::size_t src_byte_offset = (src_bit_offset % CHAR_BIT);

            if (0 == dst_byte_offset && 0 == src_byte_offset)
            {
                const std::size_t byte_count = (count % CHAR_BIT);
                if (0 == byte_count)
                    return bytecpy(dst, dst_type, dst_byte_offset, src, src_type, src_byte_offset, byte_count);
            }

            asIScriptContext* ctx = asGetActiveContext();
            asIScriptEngine* engine = ctx->GetEngine();


            const std::size_t dst_size =
                dst_type <= asTYPEID_DOUBLE
                ? engine->GetSizeOfPrimitiveType(dst_type)
                : engine->GetTypeInfoById(dst_type)->GetSize()
                * CHAR_BIT;
            const std::size_t src_size =
                src_type <= asTYPEID_DOUBLE
                ? engine->GetSizeOfPrimitiveType(src_type)
                : engine->GetTypeInfoById(src_type)->GetSize()
                * CHAR_BIT;

            if (dst_size && (count + dst_bit_offset) > dst_size)
                throw(std::logic_error("cannot copy bits - destination buffer too small"));
            if (src_size && (count + src_bit_offset) > src_size)
                throw(std::logic_error("cannot copy bits - source buffer too small"));

            dst += dst_bit_offset / CHAR_BIT;
            dst_bit_offset = dst_byte_offset;
            src += src_bit_offset / CHAR_BIT;
            src_bit_offset = src_byte_offset;
            while (count--)
            {
                if (*src & (1 << src_bit_offset))
                    *dst |= (1 << dst_bit_offset);
                else
                    *dst &= ~(1 << dst_bit_offset);
                dst_bit_offset++;
                src_bit_offset++;
                if (dst_bit_offset == CHAR_BIT)
                {
                    dst_bit_offset = 0;
                    dst++;
                }
                if (src_bit_offset == CHAR_BIT)
                {
                    src_bit_offset = 0;
                    src++;
                }
            }
        }
    }

}

namespace astd_script { namespace {
    using namespace astd;

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

#   define RegisterScriptStdFunction \
        template<> struct RegisterScriptStdFunctionHelperN<N> \
        { static void call(asIScriptEngine * engine); static void call_next(asIScriptEngine * engine) { call(engine); RegisterScriptStdFunctionHelper<N+1>::call(engine); } }; void RegisterScriptStdFunctionHelperN<N>::call
    

#   define N 0
    RegisterScriptStdFunction(asIScriptEngine* engine)
#   undef N
    {
        int r = 0;
        std::string ns = engine->GetDefaultNamespace(); if (!ns.empty()) ns += "::";
        r = engine->SetDefaultNamespace(""); assert(r >= 0);

        if (!engine->GetGlobalFunctionByDecl("uint sizeof(const ?&in src)"))
        r = engine->RegisterGlobalFunction(
            "uint sizeof(const ?&in src)",
            asFUNCTION(astd::size_of),
            asCALL_CDECL
        ); assert(r >= 0);

        r = engine->SetDefaultNamespace(ns.c_str()); assert(r >= 0);
    }
#   define N 1
    RegisterScriptStdFunction(asIScriptEngine* engine)
#   undef N
    {
        int r = 0; 
        std::string ns = engine->GetDefaultNamespace(); if (!ns.empty()) ns += "::";
        r = engine->SetDefaultNamespace((ns + "unsafe").c_str()); assert(r >= 0);

        r = engine->RegisterGlobalFunction(
            "void bytecpy(?&out dst, uint dst_byte_offset, const ?&in src, uint src_byte_offset, uint count)",
            asFUNCTION(astd::unsafe::bytecpy),
            asCALL_CDECL
        ); assert(r >= 0);

        r = engine->RegisterGlobalFunction(
            "void bitcpy(?&out dst, uint dst_bit_offset, const ?&in src, uint src_bit_offset, uint bitcount)",
            asFUNCTION(astd::unsafe::bitcpy),
            asCALL_CDECL
        ); assert(r >= 0);

        r = engine->RegisterGlobalFunction(
            "ptr<void> memcpy(ptr<void> dst, ptr<void> src, uint count)",
            asFUNCTION(astd::memcpy),
            asCALL_CDECL
        ); assert(r >= 0);

        r = engine->SetDefaultNamespace(ns.c_str()); assert(r >= 0);
    }

#   define N 2
    RegisterScriptStdFunction(asIScriptEngine* engine)
#   undef N
    {
        int r = 0;

        r = engine->RegisterGlobalFunction(
            "ptr<void> addressof(const ?&in)",
            asFUNCTION(astd::addressof),
            asCALL_CDECL
        ); assert(r >= 0);
    }

#   undef RegisterScriptStdFunction

    static void RegisterScriptStdFunctions(asIScriptEngine* engine)
    {
        typedef RegisterScriptStdFunctionHelper<0> functions;
        functions::call(engine);
    }
}}

int RegisterScriptStd_Memory_Native(asIScriptEngine *engine)
{
    int r;  

    // registering pointer type
    {
        const std::string ns = engine->GetDefaultNamespace();
        r = engine->SetDefaultNamespace(""); assert(r >= 0);

#      define TYPE_NAME "ptr"
#      define TMPL_TYPE1_NAME "T"
#      define TYPE_TMPL_CLASS_NAME TYPE_NAME "<class " TMPL_TYPE1_NAME ">"
#      define TYPE_TMPL_NAME TYPE_NAME "<" TMPL_TYPE1_NAME ">"


        struct lambdas {
            static void ctor(astd::ptr* memory, asITypeInfo* typeinfo) {
                new(memory) astd::ptr(typeinfo);
            }
            static void ctor(astd::ptr* memory, asITypeInfo* typeinfo, const astd::ptr& reference) {
                new(memory) astd::ptr(reference, typeinfo);
            }
            static void dtor(astd::ptr* object) {
                object->~ptr();
            }

            static astd::ptr& opAssign(astd::ptr* that, const astd::ptr& other)
            {
                (*that) = other;
                return (*that);
            }

            static void opConv(astd::ptr* that, void** reference, int type)
            {
                std::memcpy(reference, &that->address, sizeof(*reference));
            }

            static astd::ptr conv(astd::ptr* that)
            {
                return *that;
            }

            static void* opIndex(astd::ptr* that, asUINT index)
            {
                return (*that)[index];
            }

            static const void* opIndex(const astd::ptr* that, asUINT index)
            {
                return (*that)[index];
            }

            static astd::ptr opPostInc(astd::ptr* that)
            {
                return (*that)++;
            }

            static astd::ptr& opPreInc(astd::ptr* that)
            {
                return ++(*that);
            }

            static astd::ptr opAdd(const astd::ptr* that, int bshift)
            {
                return (*that) + bshift;
            }

            static astd::ptr opSub(const astd::ptr* that, int bshift)
            {
                return (*that) - bshift;
            }

            static astd::ptr& opAddAssign(astd::ptr* that, int bshift)
            {
                return (*that) += bshift;
            }

            static astd::ptr& opSubAssign(astd::ptr* that, int bshift)
            {
                return (*that) -= bshift;
            }
        };

        r = engine->RegisterObjectType(
            TYPE_TMPL_CLASS_NAME,
            sizeof(astd::ptr),
            asOBJ_VALUE | asOBJ_APP_CLASS_CDAK  |asOBJ_TEMPLATE
        ); assert(r >= 0); if (r < 0) return r;

        r = engine->RegisterObjectBehaviour(
            TYPE_TMPL_NAME,
            asBEHAVE_CONSTRUCT,
            "void ctor(int&in)",
            asFUNCTIONPR(lambdas::ctor, (astd::ptr*, asITypeInfo*), void), asCALL_CDECL_OBJFIRST
        ); assert(r >= 0); if (r < 0) return r;

        r = engine->RegisterObjectBehaviour(
            TYPE_TMPL_NAME,
            asBEHAVE_CONSTRUCT,
            "void ctor(int&in, const " TYPE_TMPL_NAME "&in)", // templated copy ctor
            asFUNCTIONPR(lambdas::ctor, (astd::ptr*, asITypeInfo*, const astd::ptr&), void), asCALL_CDECL_OBJFIRST
        ); assert(r >= 0); if (r < 0) return r;

        r = engine->RegisterObjectBehaviour(
            TYPE_TMPL_NAME,
            asBEHAVE_DESTRUCT,
            "void dtor()",
            asFUNCTIONPR(lambdas::dtor, (astd::ptr*), void), asCALL_CDECL_OBJFIRST
        ); assert(r >= 0); if (r < 0) return r;

        r = engine->RegisterObjectMethod(
            TYPE_TMPL_NAME,
            TYPE_TMPL_NAME "& opAssign(const " TYPE_TMPL_NAME "&in)",
            asFUNCTIONPR(lambdas::opAssign, (astd::ptr*, const astd::ptr&), astd::ptr&), asCALL_CDECL_OBJFIRST
        ); assert(r >= 0); if (r < 0) return r;

        r = engine->RegisterObjectMethod(
            TYPE_TMPL_NAME,
            "void opConv(?&out)",
            asFUNCTIONPR(lambdas::opConv, (astd::ptr*, void**, int), void), asCALL_CDECL_OBJFIRST
        ); assert(r >= 0); if (r < 0) return r;

        r = engine->RegisterObjectMethod(
            TYPE_TMPL_NAME,
            TMPL_TYPE1_NAME " &opIndex(uint index)",
            asFUNCTIONPR(lambdas::opIndex, (astd::ptr*, asUINT), void*), asCALL_CDECL_OBJFIRST
        ); assert(r >= 0); if (r < 0) return r;

        r = engine->RegisterObjectMethod(
            TYPE_TMPL_NAME,
            "const " TMPL_TYPE1_NAME " &opIndex(uint index) const",
            asFUNCTIONPR(lambdas::opIndex, (const astd::ptr*, asUINT), const void*), asCALL_CDECL_OBJFIRST
        ); assert(r >= 0); if (r < 0) return r;

        r = engine->RegisterObjectMethod(
            TYPE_TMPL_NAME,
            TYPE_TMPL_NAME "& opPreInc()",
            asFUNCTIONPR(lambdas::opPreInc, (astd::ptr*), astd::ptr&), asCALL_CDECL_OBJFIRST
        ); assert(r >= 0); if (r < 0) return r;
        
        r = engine->RegisterObjectMethod(
            TYPE_TMPL_NAME,
            TYPE_TMPL_NAME " opPostInc()",
            asFUNCTIONPR(lambdas::opPostInc, (astd::ptr*), astd::ptr), asCALL_CDECL_OBJFIRST
        ); assert(r >= 0); if (r < 0) return r;

        r = engine->RegisterObjectMethod(
            TYPE_TMPL_NAME,
            TYPE_TMPL_NAME " opAdd(int) const",
            asFUNCTIONPR(lambdas::opAdd, (const astd::ptr*, int), astd::ptr), asCALL_CDECL_OBJFIRST
        ); assert(r >= 0); if (r < 0) return r;

        r = engine->RegisterObjectMethod(
            TYPE_TMPL_NAME,
            TYPE_TMPL_NAME " opSub(int) const",
            asFUNCTIONPR(lambdas::opSub, (const astd::ptr*, int), astd::ptr), asCALL_CDECL_OBJFIRST
        ); assert(r >= 0); if (r < 0) return r;

        r = engine->RegisterObjectMethod(
            TYPE_TMPL_NAME,
            TYPE_TMPL_NAME "& opAddAssign(int)",
            asFUNCTIONPR(lambdas::opAddAssign, (astd::ptr*, int), astd::ptr&), asCALL_CDECL_OBJFIRST
        ); assert(r >= 0); if (r < 0) return r;

        r = engine->RegisterObjectMethod(
            TYPE_TMPL_NAME,
            TYPE_TMPL_NAME "& opSubAssign(int)",
            asFUNCTIONPR(lambdas::opSubAssign, (astd::ptr*, int), astd::ptr&), asCALL_CDECL_OBJFIRST
        ); assert(r >= 0); if (r < 0) return r;


        // <void>
        r = engine->RegisterObjectMethod(
            TYPE_TMPL_NAME,
            TYPE_NAME "<void> opImplConv()",
            asFUNCTIONPR(lambdas::conv, (astd::ptr*), astd::ptr), asCALL_CDECL_OBJFIRST
        ); assert(r >= 0); if (r < 0) return r;

        r = engine->SetDefaultNamespace(ns.c_str()); assert(r >= 0); if (r < 0) return r;

        if (!engine->GetTypeInfoByDecl("ptr<T>")) return -1;

        //r = engine->RegisterTypedef(
        //    "std::" TYPE_NAME,
        //    "ptr"
        //); assert(r >= 0);

#      undef TYPE_NAME
    }



    const std::string ns = engine->GetDefaultNamespace();

    r = engine->SetDefaultNamespace("std"); assert(r >= 0); if (r < 0) return r;

    astd_script::RegisterScriptStdFunctions(engine);

    r = engine->SetDefaultNamespace(""); assert(r >= 0); if (r < 0) return r;

    astd_script::RegisterScriptStdFunctions(engine);

    r = engine->SetDefaultNamespace(ns.c_str()); assert(r >= 0); if (r < 0) return r;

    if (!engine->GetTypeInfoByDecl("ptr<T>")) return -1;

    return r;
}


int RegisterScriptStd_Memory_Generic(asIScriptEngine *engine)
{
    int r = 0;

    // double versions of the same
    //r = engine->RegisterGlobalFunction("double cos(double)", asFUNCTION(cos_generic), asCALL_GENERIC); assert( r >= 0 );

    return r;
}

int RegisterScriptStd_Memory(asIScriptEngine *engine)
{
    if( strstr(asGetLibraryOptions(), "AS_MAX_PORTABILITY") )
        return RegisterScriptStd_Memory_Generic(engine);
    else
        return RegisterScriptStd_Memory_Native(engine);
}

END_AS_NAMESPACE



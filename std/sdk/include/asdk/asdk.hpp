#ifndef ANGELSCRIPT_SOFTWARE_DEVELOPMENT_KIT_HPP
#define ANGELSCRIPT_SOFTWARE_DEVELOPMENT_KIT_HPP

#define ASDK_WRAP(a) a
#define ASDK_CAT3(a,b) a##b
#define ASDK_CAT2(a,b) ASDK_CAT3(a,b)
#define ASDK_CAT(a,b) ASDK_CAT2(a,b)

#define ASDK_STRINGIFY(a) #a

#ifndef ASDK_ANGELSCRIPT_DIRECTORY
#   define ASDK_ANGELSCRIPT_DIRECTORY angelscript/sdk/angelscript/
#endif

#ifndef ASDK_ANGELSCRIPT_LIB_H_PATH
#   define ASDK_ANGELSCRIPT_LIB_H_PATH <ASDK_WRAP(ASDK_ANGELSCRIPT_DIRECTORY)include/angelscript.h>
#endif

#include ASDK_ANGELSCRIPT_LIB_H_PATH


#undef ASDK_ANGELSCRIPT_DIRECTORY
#undef ASDK_ANGELSCRIPT_LIB_H_PATH

#ifdef AS_NAMESPACE_QUALIFIER
#   ifndef ASDK_ANGELSCRIPT_NS_QUALIFIER
#       define ASDK_ANGELSCRIPT_NS_QUALIFIER AS_NAMESPACE_QUALIFIER
#   endif // ASDK_ANGELSCRIPT_NS_QUALIFIER
#else // ndef AS_NAMESPACE_QUALIFIER
#   ifndef ASDK_ANGELSCRIPT_NS_QUALIFIER
#       define ASDK_ANGELSCRIPT_NS_QUALIFIER AngelScript::
#   endif // ASDK_ANGELSCRIPT_NS_QUALIFIER
#endif // AS_NAMESPACE_QUALIFIER

#include <string>
#include <cassert>
#include <cstring>
#include <exception>
#include <stdexcept>
#include <iterator>

// AngelScript functions, types etc.
namespace asdk {
    namespace AngelScript {
        using ASDK_ANGELSCRIPT_NS_QUALIFIER asSMessageInfo;
        using ASDK_ANGELSCRIPT_NS_QUALIFIER asDWORD;
        using ASDK_ANGELSCRIPT_NS_QUALIFIER asQWORD;
        using ASDK_ANGELSCRIPT_NS_QUALIFIER asWORD;
        using ASDK_ANGELSCRIPT_NS_QUALIFIER asIScriptEngine;
        using ASDK_ANGELSCRIPT_NS_QUALIFIER asIScriptContext;
        using ASDK_ANGELSCRIPT_NS_QUALIFIER asSFuncPtr;
        using ASDK_ANGELSCRIPT_NS_QUALIFIER asITypeInfo;
        using ASDK_ANGELSCRIPT_NS_QUALIFIER asUINT;
        using ASDK_ANGELSCRIPT_NS_QUALIFIER asIScriptFunction;

        using ASDK_ANGELSCRIPT_NS_QUALIFIER asCreateScriptEngine;
        using ASDK_ANGELSCRIPT_NS_QUALIFIER asGetActiveContext;

        namespace asECallConvTypes {
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asECallConvTypes;
            typedef asECallConvTypes type;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asCALL_CDECL;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asCALL_STDCALL;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asCALL_THISCALL_ASGLOBAL;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asCALL_THISCALL;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asCALL_CDECL_OBJLAST;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asCALL_CDECL_OBJFIRST;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asCALL_GENERIC;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asCALL_THISCALL_OBJLAST;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asCALL_THISCALL_OBJFIRST;
        } using namespace asECallConvTypes;

        namespace asERetCodes {
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asERetCodes;
            typedef asERetCodes type;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asNO_FUNCTION;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asSUCCESS;
        } using namespace asERetCodes;

        namespace asEObjTypeFlags
        {
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asEObjTypeFlags;
            typedef asEObjTypeFlags type;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asOBJ_REF;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asOBJ_VALUE;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asOBJ_GC;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asOBJ_POD;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asOBJ_NOHANDLE;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asOBJ_SCOPED;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asOBJ_TEMPLATE;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asOBJ_ASHANDLE;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asOBJ_APP_CLASS;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asOBJ_APP_CLASS_CONSTRUCTOR;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asOBJ_APP_CLASS_DESTRUCTOR;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asOBJ_APP_CLASS_ASSIGNMENT;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asOBJ_APP_CLASS_COPY_CONSTRUCTOR;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asOBJ_APP_CLASS_C;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asOBJ_APP_CLASS_CD;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asOBJ_APP_CLASS_CA;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asOBJ_APP_CLASS_CK;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asOBJ_APP_CLASS_CDA;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asOBJ_APP_CLASS_CDK;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asOBJ_APP_CLASS_CAK;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asOBJ_APP_CLASS_CDAK;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asOBJ_APP_CLASS_D;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asOBJ_APP_CLASS_DA;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asOBJ_APP_CLASS_DK;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asOBJ_APP_CLASS_DAK;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asOBJ_APP_CLASS_A;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asOBJ_APP_CLASS_AK;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asOBJ_APP_CLASS_K;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asOBJ_APP_CLASS_MORE_CONSTRUCTORS;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asOBJ_APP_PRIMITIVE;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asOBJ_APP_FLOAT;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asOBJ_APP_ARRAY;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asOBJ_APP_CLASS_ALLINTS;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asOBJ_APP_CLASS_ALLFLOATS;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asOBJ_NOCOUNT;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asOBJ_APP_CLASS_ALIGN8;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asOBJ_IMPLICIT_HANDLE;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asOBJ_APP_CLASS_UNION;
        } using namespace asEObjTypeFlags;

        // Behaviours
        namespace asEBehaviours
        {
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asEBehaviours;
            typedef asEBehaviours type;
            // Value object memory management
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asBEHAVE_CONSTRUCT;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asBEHAVE_LIST_CONSTRUCT;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asBEHAVE_DESTRUCT;
            // Reference object memory management
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asBEHAVE_FACTORY;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asBEHAVE_LIST_FACTORY;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asBEHAVE_ADDREF;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asBEHAVE_RELEASE;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asBEHAVE_GET_WEAKREF_FLAG;
            // Object operators
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asBEHAVE_TEMPLATE_CALLBACK;
            // Garbage collection behaviours
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asBEHAVE_FIRST_GC;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asBEHAVE_GETREFCOUNT;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asBEHAVE_SETGCFLAG;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asBEHAVE_GETGCFLAG;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asBEHAVE_ENUMREFS;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asBEHAVE_RELEASEREFS;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asBEHAVE_LAST_GC;

            using ASDK_ANGELSCRIPT_NS_QUALIFIER asBEHAVE_MAX;
        } using namespace asEBehaviours;

        // Calling conventions
        namespace asECallConvTypes
        {
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asECallConvTypes;
            typedef asECallConvTypes type;

            using ASDK_ANGELSCRIPT_NS_QUALIFIER asCALL_CDECL;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asCALL_STDCALL;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asCALL_THISCALL_ASGLOBAL;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asCALL_THISCALL;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asCALL_CDECL_OBJLAST;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asCALL_CDECL_OBJFIRST;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asCALL_GENERIC;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asCALL_THISCALL_OBJLAST;
            using ASDK_ANGELSCRIPT_NS_QUALIFIER asCALL_THISCALL_OBJFIRST;
        } using namespace asECallConvTypes;
    }

    namespace AngelScript {
        struct asType {
            asITypeInfo* type_info;
            int type_id;
            asType() : type_info(0), type_id(asTYPEID_APPOBJECT) {}
            asType(asITypeInfo& type_info) : type_info(&type_info), type_id(type_info.GetTypeId()) {}
            asType(asIScriptEngine& engine, int type_id) : type_info(engine.GetTypeInfoById(type_id)), type_id(type_info ? asTYPEID_APPOBJECT : type_id) {}
            bool is_void() const { return asTYPEID_VOID == type_id; }
            bool is_arithmetic() const { if (is_class()) return false; return type_id > asTYPEID_VOID && type_id < asTYPEID_DOUBLE; }
            bool is_handle() const { 
                if (type_info) return 0 != (type_info->GetFlags() & asOBJ_ASHANDLE); 
                return 0 != (type_id & asTYPEID_OBJHANDLE); 
            }
            bool is_enum() const {
                if (type_info) return 0 != (type_info->GetFlags() & asOBJ_ENUM);
                return type_id > asTYPEID_DOUBLE && type_id != asTYPEID_APPOBJECT; // enums have a type id larger than doubles
            }
            bool is_object() const { return !!type_info; }
            bool is_class() const { return is_object() && !is_enum(); }
            

            bool operator!() const {
                return !type_info && (asTYPEID_APPOBJECT == type_id || type_id < 0);
            }

            const char* name() const {
                if (!*this) return 0;
                if (type_info)
                    return type_info->GetName();
                switch (type_id)
                {
                case asTYPEID_VOID: return "void";
                case asTYPEID_BOOL: return "bool";
                case asTYPEID_DOUBLE: return "double";
                case asTYPEID_FLOAT: return "float";
                case asTYPEID_INT16: return "int16";
                case asTYPEID_INT32: return "int32";
                case asTYPEID_INT64: return "int64";
                case asTYPEID_UINT16: return "uint16";
                case asTYPEID_UINT32: return "uint32";
                case asTYPEID_UINT64: return "uint64";
                }

                return 0;
            }

            int size() const {
                if (type_info)
                {
                    int type_id = type_info->GetTypeId();
                    if (type_id & asTYPEID_MASK_OBJECT)
                        return sizeof(void*);
                    return type_info->GetSize();
                }

                switch (type_id)
                {
                case asTYPEID_VOID: return 0;
                case asTYPEID_BOOL: return sizeof(bool);
                case asTYPEID_DOUBLE: return sizeof(double);
                case asTYPEID_FLOAT: return sizeof(float);
                case asTYPEID_INT16: return sizeof(asINT16);
                case asTYPEID_INT32: return sizeof(asINT32);
                case asTYPEID_INT64: return sizeof(asINT64);
                case asTYPEID_UINT16: return sizeof(asINT16);
                case asTYPEID_UINT32: return sizeof(asINT32);
                case asTYPEID_UINT64: return sizeof(asINT64);
                }

                return -1;
            }

            int addref() {
                if (type_info) return type_info->AddRef(); return 0;
            }
            int release() {
                if (type_info) return type_info->Release(); return 0;
            }
            asType subtype(int index = 0) const {
                asType result;
                if (type_info)
                {
                    result.type_info = type_info->GetSubType(index);
                    if (result.type_info) result.type_id = result.type_info->GetTypeId();
                }
                return result;
            }
            asType underlying_type() const {
                asType result;
                if (is_enum())
                    result.type_id = type_info->GetUnderlyingTypeId();
                return result;
            }
        };
    }

    namespace AngelScript {
        struct asGCReference {
            template<class T>
            struct Template;

            asGCReference(const asType& type)
                : gc()
                , ref()
            {
                ctor(type, &dummy_deleter);
            }

            template<class Deleter>
            asGCReference(const asType& type, const Deleter &d)
                : gc()
                , ref()
            {
                ctor(type, d);
            }
            ~asGCReference() {
                ref.type.release();
                deleter.destruct(deleter.ptr);
            }
            asGCReference(const asGCReference& other)
                : gc(other.gc)
                , ref(other.ref)
                , deleter(other.deleter)
            {
                gc.flag = false;
                ref.count = 1;
                static_cast<void>(ref.type.addref());
                deleter.ptr = other.deleter.make_copy(other.deleter.ptr);
            }
            template<class Deleter>
            asGCReference(const asGCReference& other, const Deleter& d)
                : gc()
                , ref()
            {
                ctor(other.ref.type, d);
            }
            void swap(asGCReference& other) throw()
            {
                if (&other == this) return;

                std::swap(gc, other.gc);
                std::swap(ref, other.ref);
                std::swap(deleter, other.deleter);
            }
            asGCReference& operator=(const asGCReference& other)
            {
                if (&other != this)
                    asGCReference(other).swap(*this);
                return *this;
            }

            virtual void enumrefs(asIScriptEngine*) {}
            virtual void releaserefs(asIScriptEngine*) {}
        
            void setgcflag() { gc.flag = true; }
            bool getgcflag() const { return gc.flag; }
            void addref() { gc.flag = false; asAtomicInc(ref.count); }
            void release() { 
                gc.flag = false; 
                if (0 == asAtomicDec(ref.count))
                {
                    // When reaching 0 no more references to this instance
                    // exists and the object should be destroyed
                    deleter.call(deleter.ptr, this);
                }
            }
            int getrefcount() const { return ref.count; }

            struct meta {
                static const char* enumrefs_cstr() { return "void enumrefs(int&in)"; }
                static const char* releaserefs_cstr() { return "void releaserefs(int&in)"; }

                static const char* setgcflag_cstr() { return "void setgcflag()"; }
                static const char* getgcflag_cstr() { return "bool getgcflag()"; }
                static const char* addref_cstr() { return "void addref()"; }
                static const char* release_cstr() { return "void release()"; }
                static const char* getrefcount_cstr() { return "int getrefcount()"; }
            };
        protected:

            const asType& type() const {
                return ref.type;
            }

        private:
            struct {
                bool flag;
            } gc;
            struct {
                mutable int count;
                asType type;
            } ref;

            struct {
                void* ptr;
                void (*call)(void*, void*);
                void (*destruct)(void*);
                void* (*make_copy)(const void*);
            } deleter;
            static void dummy_deleter(asGCReference*) {  }
            template<class Deleter>
            void ctor(const asType& type, const Deleter& d)
            {
                gc.flag = false;
                ref.count = 1;
                ref.type = type;
                static_cast<void>(ref.type.addref());

                struct lambdas
                {
                    typedef Deleter deleter_type;
                    static void deleter_call(void* deleter, void* ptr) {
                        (*reinterpret_cast<deleter_type*>(deleter))(
                            reinterpret_cast<asGCReference*>(ptr)
                            );
                    }
                    static void deleter_destruct(void* deleter) { delete (reinterpret_cast<deleter_type*>(deleter)); }
                    static void* deleter_make_copy(const void* deleter) { if (!deleter) return 0; return new deleter_type(*reinterpret_cast<const deleter_type*>(deleter)); }
                };

                deleter.ptr = new Deleter(d);
                deleter.call = &lambdas::deleter_call;
                deleter.destruct = &lambdas::deleter_destruct;
                deleter.make_copy = &lambdas::deleter_make_copy;
            }
        };

        template<class T>
        struct asGCReference::Template
            : asGCReference
        {
            template<class Deleter>
            Template(const asType& type, const Deleter &d = &this_deleter)
                : asGCReference(type, d)
            { }
            Template(const asType & type, T& that)
                : asGCReference(type, deleter(that))
            { }
            template<class Deleter>
            Template(const Template& other, const Deleter & d)
                : asGCReference(other, d)
            { }
            Template(const Template& other, T& that)
                : asGCReference(other, deleter(that))
            { }

        private:
            static void this_deleter(asGCReference* this_type) {
                delete dynamic_cast<T*>(this_type);
            }

            struct deleter {
                T* ptr;
                void operator()(asGCReference* ref)
                {
                    delete ptr;
                }
                deleter(T& other) : ptr(&other) {}
            };
        
        };
    }

    namespace algorithm {

        namespace type_traits {
            template<class T>
            struct is_pointer {
                static const bool value = false;
            };
            template<class T>
            struct is_pointer<T*> {
                static const bool value = sizeof(T*) == sizeof(void*);
            };

            template<class T>
            struct remove_pointer {
                typedef T type;
            };
            template<class T>
            struct remove_pointer<T*> {
                typedef T type;
            };
        }
        
        namespace {
            class copy
            {
                template<class Iterator>
                struct increment_functor {
                    typedef void(*incr_type)(Iterator&, int);
                    typedef bool(*cmp_not_equal_type)(const Iterator&, const Iterator&);
                    struct type
                    {
                    private:
                        incr_type incr;
                        cmp_not_equal_type not_equal;
                    public:
                        type(incr_type incr, cmp_not_equal_type not_equal) : incr(incr), not_equal(not_equal) {}
                        type(cmp_not_equal_type not_equal, incr_type incr) : incr(incr), not_equal(not_equal) {}
                        void operator()(Iterator& it, int type_size) const { return incr(it, type_size); }
                        bool operator()(const Iterator &lhs, const Iterator& rhs) const { return not_equal(lhs, rhs); }
                        bool operator!() const { return !incr || !equal; }
                    };
                    
                    inline static void pre_incr(Iterator& it, int) { ++it; }
                    inline static void incr_by(Iterator& it, int type_size) { it += type_size; }
                    inline static bool cmp_not_equal(const Iterator& lhs, const Iterator& rhs) { return lhs != rhs; }
                    inline static bool cmp_not_equal_or_greater(const Iterator& lhs, const Iterator &rhs) {
                        if (!(lhs < rhs)) return false;
                        return true;
                    }
                };
                template<class Iterator, bool>
                struct increment_impl {
                    typedef increment_functor<Iterator> it_incr_functor;
                    typedef typename it_incr_functor::type functor_type;
                    inline
                    static functor_type make(Iterator& it, int type_size)
                    {
                        if (sizeof(typename type_traits::remove_pointer<Iterator>::type) < type_size)
                        {
                            return functor_type(it_incr_functor::incr_by, it_incr_functor::cmp_not_equal_or_greater);
                        }
                        else
                        {
                            return functor_type(it_incr_functor::pre_incr, it_incr_functor::cmp_not_equal);
                        }
                    }
                };
                template<class Iterator>
                struct increment_impl<Iterator, false> {
                    typedef increment_functor<Iterator> it_incr_functor;
                    typedef typename it_incr_functor::type functor_type;
                    template<class IteratorTag>
                    inline
                    static functor_type make_impl(Iterator& it, int type_size, IteratorTag)
                    {
                        if (sizeof(*it) < type_size)
                        {
                            return functor_type(0, 0);
                        }
                        else
                        {
                            return functor_type(it_incr_functor::pre_incr, it_incr_functor::cmp_not_equal);
                        }
                    }

                    inline
                    static functor_type make_impl(Iterator& it, int type_size, std::random_access_iterator_tag)
                    {
                        if (sizeof(*it) < type_size)
                        {
                            return functor_type(it_incr_functor::incr_by, it_incr_functor::cmp_not_equal_or_greater);
                        }
                        else
                        {
                            return functor_type(it_incr_functor::pre_incr, it_incr_functor::cmp_not_equal);
                        }
                    }

                    inline
                    static functor_type make(Iterator& it, int type_size)
                    {
                        typename std::iterator_traits<Iterator>::iterator_category tag;
                        return make_impl(it, type_size, tag);
                    }
                };


                template<class Iterator>
                struct increment 
                    : increment_impl<Iterator, type_traits::is_pointer<Iterator>::value> 
                {
                    typedef typename increment_functor<Iterator>::type functor_type;
                };
                
                template<class InIterator, class OutIterator>
                inline
                bool copy_handle(asIScriptEngine &engine, const int& type_size, const AngelScript::asType& type, InIterator inFirst, InIterator inLast, OutIterator outFirst) const
                {
                    const std::string decl =
                        std::string(type.name()) + "& opHndlAssign(const " + std::string(type.name()) + "&in)";
                    asIScriptFunction* func = type.type_info->GetMethodByDecl(decl.c_str());
                    if (func)
                    {
                        asIScriptContext* ctx = asGetActiveContext();
                        if (!ctx) ctx = engine.RequestContext();
                        if (0 != ctx->Prepare(func))
                            ctx = engine.RequestContext();
                        if (0 != ctx->Prepare(func))
                            throw(std::logic_error(std::string("astd::copy<") + type.name() + ">: cannot prepare context for 'opHndlAssign' function"));
                        typedef increment<OutIterator> outIncr; typedef increment<InIterator> inIncr;
                        typename outIncr::functor_type out_func = outIncr::make(outFirst, type_size);
                        typename inIncr::functor_type in_func = inIncr::make(inFirst, type_size);
                        for (; in_func(inFirst, inLast); out_func(outFirst, type_size), in_func(inFirst, type_size))
                        {
                            void* dst = &(*outFirst);
                            const void* src = &(*inFirst);
                            ctx->SetObject(dst);
                            ctx->SetArgAddress(0, const_cast<void*>(src));
                            // TODO: Handle errors
                            ctx->Execute();
                        }
                        engine.ReturnContext(ctx);
                        return true;
                    }
                    return false;
                }

                
                template<class InIterator, class OutIterator>
                inline
                void copy_class(asIScriptEngine& engine, const int &type_size, const AngelScript::asType& type, InIterator inFirst, InIterator inLast, OutIterator outFirst) const
                {
                    bool handle_assigned = false;
                    if (type.is_handle())
                    {
                        handle_assigned = copy_handle(engine, type_size, type, inFirst, inLast, outFirst);
                    }

                    if (!handle_assigned)
                    {
                        if (sizeof(void*) != type_size) throw(std::runtime_error(std::string("astd::copy<") + type.name() + ">: invalid type size != sizeof(void*)"));
                        // ordinary value assign instead
                        typedef increment<OutIterator> outIncr; typedef increment<InIterator> inIncr;
                        typename outIncr::functor_type out_func = outIncr::make(outFirst, type_size);
                        typename inIncr::functor_type in_func = inIncr::make(inFirst, type_size);
                        for (; in_func(inFirst, inLast); out_func(outFirst, type_size), in_func(inFirst, type_size))
                        {
                            void* dst = &(*outFirst);
                            const void* src = &(*inFirst);
                            const void* const& obj_ptr = *reinterpret_cast<void* const*>(dst); // made it a reference for debbuging purposes
                            if (!obj_ptr)
                            {
                                void* obj = engine.CreateScriptObjectCopy(const_cast<void*>(src), type.type_info);
                                if (!obj) throw(std::runtime_error(std::string("astd::copy<") + type.name() + ">: cannot create copy of script object"));
                                std::memcpy(dst, &obj, sizeof(void*)); // since we store just pointers
                            }
                            else
                            {
                                engine.AssignScriptObject(dst, const_cast<void*>(src), type.type_info);
                            }
                        }
                    }
                }
            public:
                template<class InIterator, class OutIterator>
                inline
                void operator()(const AngelScript::asType& type, InIterator inFirst, InIterator inLast, OutIterator outFirst) const
                {
                    if (inFirst == inLast) return;

                    if (!type) throw(std::runtime_error(std::string("astd::copy<") + type.name() + ">: invalid type"));

                    asIScriptEngine* engine = type.type_info->GetEngine();
                    if (!engine) throw(std::runtime_error(std::string("astd::copy<") + type.name() + ">: cannot get script engine"));

                    const int type_size = type.size();
                    if (type_size <= 0) throw(std::runtime_error(std::string("astd::copy<") + type.name() + ">: invalid type::size"));

                    if (type.is_class() && (type.type_id & ~asTYPEID_MASK_SEQNBR))
                    {
                        copy_class(*engine, type_size, type, inFirst, inLast, outFirst);
                    }
                    else if (type.is_handle())
                    {
                        typedef increment<OutIterator> outIncr; typedef increment<InIterator> inIncr;
                        typename outIncr::functor_type out_func = outIncr::make(outFirst, type_size);
                        typename inIncr::functor_type in_func = inIncr::make(inFirst, type_size);
                        for (; in_func(inFirst, inLast); out_func(outFirst, type_size), in_func(inFirst, type_size))
                        {
                            void* dst = &(*outFirst);
                            const void* src = &(*inFirst);
                            void* obj_ptr = *reinterpret_cast<void* const*>(dst);
                            void* value_obj_ptr = *reinterpret_cast<void* const*>(src); // since source is reference, 'src' stores pointer to pointer
                            engine->AddRefScriptObject(value_obj_ptr, type.type_info);
                            if (obj_ptr)
                                engine->ReleaseScriptObject(obj_ptr, type.type_info);
                        }
                    }
                    else
                    {
                        if (type_traits::is_pointer<InIterator>::value && type_traits::is_pointer<OutIterator>::value)
                        {
                            void* dst = &(*outFirst);
                            const void* src = &(*inFirst);
                            const std::ptrdiff_t count = std::distance(inFirst, inLast);
                            std::memcpy(dst, src, type_size * count);
                        }
                        else
                        {
                            typedef increment<OutIterator> outIncr; typedef increment<InIterator> inIncr;
                            typename outIncr::functor_type out_func = outIncr::make(outFirst, type_size);
                            typename inIncr::functor_type in_func = inIncr::make(inFirst, type_size);
                            for (; in_func(inFirst, inLast); out_func(outFirst, type_size), in_func(inFirst, type_size))
                            {
                                void* dst = &(*outFirst);
                                const void* src = &(*inFirst);
                                std::memcpy(dst, src, type_size);
                            }
                        }
                    }
                }
            } copy;

            class construct
            {
            public:
                inline
                void class_object(const AngelScript::asType& type, void* memory) const
                {
                    asIScriptEngine* engine = type.type_info->GetEngine();
                    if (!engine) throw(std::runtime_error(std::string("astd::construct<") + type.name() + ">::class_object: cannot get script engine"));

                    void* obj_ptr = engine->CreateScriptObject(type.type_info);
                    std::memcpy(memory, &obj_ptr, sizeof(void*));
                }

                inline
                void operator()(const AngelScript::asType& type, void* memory) const
                {
                    if (!memory) throw(std::runtime_error(std::string("astd::construct<") + type.name() + ">: null memory location"));
                    if (!type) throw(std::runtime_error(std::string("astd::construct<") + type.name() + ">: invalid type"));

                    const int type_size = type.size();
                    if (type_size <= 0) throw(std::runtime_error(std::string("astd::construct<") + type.name() + ">: invalid type::size"));

                    if (type.is_class() && !type.is_handle())
                    {
                        if (type_size != sizeof(void*)) 
                            throw(std::runtime_error(std::string("astd::construct<") + type.name() + ">: invalid type::size for script class object != sizeof(void*)"));

                        class_object(type, memory);
                    }
                    else
                    {
                        std::memset(memory, 0, type_size);
                    }
                }

                inline
                void operator()(const AngelScript::asType& type, void* memory, std::size_t count) const
                {
                    if (!memory) throw(std::runtime_error(std::string("astd::construct[]<") + type.name() + ">: null memory location"));
                    if (!type) throw(std::runtime_error(std::string("astd::construct[]<") + type.name() + ">: invalid type"));

                    const int type_size = type.size();
                    if (type_size <= 0) throw(std::runtime_error(std::string("astd::construct[]<") + type.name() + ">: invalid type::size"));

                    if (type.is_class() && !type.is_handle())
                    {
                        if (type_size != sizeof(void*)) 
                            throw(std::runtime_error(std::string("astd::construct[]<") + type.name() + ">: invalid type::size for script class object != sizeof(void*)"));

                        unsigned char* memory_it = static_cast<unsigned char*>(memory);
                        for (std::size_t i = 0; i < count; i += sizeof(void*))
                            class_object(type, memory_it + i);
                    }
                    else
                    {
                        std::memset(memory, 0, type_size * count);
                    }
                }
            } construct;
        }
    }
}

#include <string>
#include <stdexcept>
#include <functional>

// AngelScript SDK Exposing aka exporting C++ interface to script 
namespace asdk {
    namespace exposing {

        struct expose {

            typedef asdk::AngelScript::asECallConvTypes::type asECallConvTypes;
            typedef asdk::AngelScript::asEObjTypeFlags::type asEObjTypeFlags;
            typedef asdk::AngelScript::asEBehaviours::type asEBehaviours;
            typedef asdk::AngelScript::asSFuncPtr asSFuncPtr; 
            typedef asdk::AngelScript::asIScriptEngine asIScriptEngine;
            typedef asdk::AngelScript::asITypeInfo asITypeInfo;
            typedef asdk::AngelScript::asQWORD asQWORD;
            
            expose(asIScriptEngine& engine, const std::string& decl, asSFuncPtr func, asECallConvTypes callConv)
                : engine(&engine), obj()   , objSize()       , decl(decl), func(func), callConv(callConv), flags(-1) {}
            expose(asIScriptEngine& engine, const std::string& obj, const std::string& decl, asSFuncPtr func, asECallConvTypes callConv)
                : engine(&engine), obj(obj), objSize()       , decl(decl), func(func), callConv(callConv), flags(-1) {}
            expose(asIScriptEngine& engine, const std::string& obj, int objSize, asEObjTypeFlags flag1, asEObjTypeFlags flag2, asEObjTypeFlags flag3)
                : engine(&engine), obj(obj), objSize(objSize), decl(), func(func), callConv(asECallConvTypes()), flags(flag1 | flag2 | flag3) {
                const bool is_class = 0 != (expose::flags & asOBJ_APP_CLASS);
                const bool is_ref = 0 != (expose::flags & asOBJ_REF);
                const bool is_value = 0 != (expose::flags & asOBJ_VALUE);
                if (!is_class && !is_ref) expose::flags |= asOBJ_APP_CLASS;
                if (!is_value && !is_ref) expose::flags |= asOBJ_VALUE;
            }
            expose(asIScriptEngine& engine, const std::string& obj, int objSize, asEObjTypeFlags flag1, asEObjTypeFlags flag2)
                : engine(&engine), obj(obj), objSize(objSize), decl(), func(func), callConv(asECallConvTypes()), flags(flag1 | flag2) {
                const bool is_class = 0 != (expose::flags & asOBJ_APP_CLASS);
                const bool is_ref = 0 != (expose::flags & asOBJ_REF);
                const bool is_value = 0 != (expose::flags & asOBJ_VALUE);
                if (!is_class && !is_ref) expose::flags |= asOBJ_APP_CLASS;
                if (!is_value && !is_ref) expose::flags |= asOBJ_VALUE;
            }
            expose(asIScriptEngine& engine, const std::string& obj, int objSize, asEObjTypeFlags flags)
                : engine(&engine), obj(obj), objSize(objSize), decl()    , func(func), callConv(asECallConvTypes()), flags(flags) {
                const bool is_class = 0 != (expose::flags & asOBJ_APP_CLASS);
                const bool is_ref = 0 != (expose::flags & asOBJ_REF);
                const bool is_value = 0 != (expose::flags & asOBJ_VALUE);
                if (!is_class && !is_ref) expose::flags |= asOBJ_APP_CLASS;
                if (!is_value && !is_ref) expose::flags |= asOBJ_VALUE;
            }
            expose(asIScriptEngine& engine, const std::string& obj, const std::string& decl, asEBehaviours beh, asSFuncPtr func, asECallConvTypes callConv)
                : engine(&engine), obj(obj), objSize()       , decl(decl), func(func), callConv(callConv), flags(beh) {}

            expose(const expose& other)
                : engine(other.engine), obj(other.obj), objSize(other.objSize), decl(other.decl), func(other.func), callConv(other.callConv), flags(other.flags)
            {
                other.engine = 0;
            }


            void dtor() {
                if (!engine) return;

                struct lambdas {
                    static void throw_an_error(const std::string& message) {
                        throw(std::logic_error(message.c_str()));
                    }

                };

                if (obj.empty())
                {
                    if (0 > engine->RegisterGlobalFunction(decl.c_str(), func, callConv))
                        lambdas::throw_an_error("RegisterGlobalFunction");
                }
                else
                {
                    if (decl.empty())
                    {
                        if (asQWORD(-1) == flags) flags = 0;

                        if (0 != (flags & asOBJ_APP_CLASS) || 0 != (flags & asOBJ_REF))
                        {
                            if (0 > engine->RegisterObjectType(obj.c_str(), objSize, flags))
                                lambdas::throw_an_error("RegisterObjectType");
                        }
                        else
                            lambdas::throw_an_error("Not Implemented");
                    }
                    else
                    {
                        if (asQWORD(-1) == flags)
                        {
                            if (0 > engine->RegisterObjectMethod(obj.c_str(), decl.c_str(), func, callConv))
                                lambdas::throw_an_error("RegisterObjectMethod");
                        }
                        else
                        {
                            const asEBehaviours beh = static_cast<asEBehaviours>(flags);

                            if (0 > engine->RegisterObjectBehaviour(obj.c_str(), beh, decl.c_str(), func, callConv))
                                lambdas::throw_an_error("RegisterObjectBehaviour");
                        }
                    }
                }

                engine = 0;
            }

            ~expose() {
                dtor();
            }

        private:
            mutable asIScriptEngine* engine;
            std::string obj;
            int objSize;
            std::string decl;
            asSFuncPtr func;
            asECallConvTypes callConv;
            asQWORD flags;
        };
        
    }
    using namespace exposing;
}

#include <string>
#include <stdexcept>

// AngelScript SDK Introducing aka importing script interface to C++
namespace asdk {
    namespace introducing {

        struct introduce {

            typedef asdk::AngelScript::asECallConvTypes::type asECallConvTypes;
            typedef asdk::AngelScript::asEObjTypeFlags::type asEObjTypeFlags;
            typedef asdk::AngelScript::asEBehaviours::type asEBehaviours;
            typedef asdk::AngelScript::asSFuncPtr asSFuncPtr;
            typedef asdk::AngelScript::asIScriptEngine asIScriptEngine;
            typedef asdk::AngelScript::asITypeInfo asITypeInfo;
        };

    }
}

#include <string>
#include <vector>

// AngelScript SDK Reflection
namespace asdk {

    namespace reflection {


        namespace type_traits
        {
            template<class T1, class T2>
            struct is_same { static const bool value = false; };
            template<class T>
            struct is_same<T,T> { static const bool value = true; };
            struct true_type  :is_same<void, void> { char dummy[1]; };
            struct false_type :is_same<void, float> { char dummy[16]; };

            template<class>
            struct is_const : false_type {};
            template<class T>
            struct is_const<const T> : true_type {};

            template<class>
            struct is_reference : false_type {};
            template<class T>
            struct is_reference<T&> : true_type {};

            template<class IfTrueT, class IfFalseT, bool>
            struct conditional {  typedef IfTrueT type; };
            template<class IfTrueT, class IfFalseT>
            struct conditional<IfTrueT, IfFalseT, false> { typedef IfFalseT type; };

            template<class IfTrueT, class IfFalseT, class, class>
            struct conditional_is_same { typedef IfFalseT type; };
            template<class IfTrueT, class IfFalseT, class T>
            struct conditional_is_same<IfTrueT, IfFalseT, T, T> { typedef IfTrueT type; };

            template<class T>
            struct remove_reference { typedef T type; };
            template<class T>
            struct remove_reference<T&> { typedef T type; };
            template<class T>
            struct remove_reference<const T&> { typedef const T type; };
            template<class T>
            struct remove_reference<volatile T&> { typedef volatile T type; };

            template<class T>
            struct add_reference { typedef T& type; };
            template<>
            struct add_reference<void> { typedef void type; };


            template<class T>
            T declval();
            //{
            //    typename remove_reference<T>::type* result =
            //        reinterpret_cast<typename remove_reference<T>::type*>(0);
            //    if (result) return *result; else throw("");
            //}

            template<int> struct sfinae_size_check {};

            template<int LhsSize, int RhsSize>
            struct size_is_equal {
                static const bool value = bool(LhsSize == RhsSize);
            };


#           ifndef ASDK_FUNCTION_ARGS_TYPES
#           define   ASDK_FUNCTION_ARGS_TYPES_1(param_cb) class param_cb(1) ASDK_PARAM 
#           define    ASDK_FUNCTION_ARGS_LIST_1(param_cb)       param_cb(1)
#           define   ASDK_FUNCTION_ARGS_TYPES_2(param_cb) class param_cb(1) ASDK_PARAM , class param_cb(2) ASDK_PARAM 
#           define    ASDK_FUNCTION_ARGS_LIST_2(param_cb)       param_cb(1)            ,       param_cb(2)
#           define   ASDK_FUNCTION_ARGS_TYPES_3(param_cb) class param_cb(1) ASDK_PARAM , class param_cb(2) ASDK_PARAM , class param_cb(3) ASDK_PARAM 
#           define    ASDK_FUNCTION_ARGS_LIST_3(param_cb)       param_cb(1)            ,       param_cb(2)            ,       param_cb(3)
#           define   ASDK_FUNCTION_ARGS_TYPES_4(param_cb) class param_cb(1) ASDK_PARAM , class param_cb(2) ASDK_PARAM , class param_cb(3) ASDK_PARAM , class param_cb(4) ASDK_PARAM 
#           define    ASDK_FUNCTION_ARGS_LIST_4(param_cb)       param_cb(1)            ,       param_cb(2)            ,       param_cb(3)            ,       param_cb(4)
#           define   ASDK_FUNCTION_ARGS_TYPES_5(param_cb) class param_cb(1) ASDK_PARAM , class param_cb(2) ASDK_PARAM , class param_cb(3) ASDK_PARAM , class param_cb(4) ASDK_PARAM , class param_cb(5) ASDK_PARAM 
#           define    ASDK_FUNCTION_ARGS_LIST_5(param_cb)       param_cb(1)            ,       param_cb(2)            ,       param_cb(3)            ,       param_cb(4)            ,       param_cb(5)
#           define   ASDK_FUNCTION_ARGS_TYPES_6(param_cb) class param_cb(1) ASDK_PARAM , class param_cb(2) ASDK_PARAM , class param_cb(3) ASDK_PARAM , class param_cb(4) ASDK_PARAM , class param_cb(5) ASDK_PARAM , class param_cb(6) ASDK_PARAM 
#           define    ASDK_FUNCTION_ARGS_LIST_6(param_cb)       param_cb(1)            ,       param_cb(2)            ,       param_cb(3)            ,       param_cb(4)            ,       param_cb(5)            ,       param_cb(6)
#           define   ASDK_FUNCTION_ARGS_TYPES_7(param_cb) class param_cb(1) ASDK_PARAM , class param_cb(2) ASDK_PARAM , class param_cb(3) ASDK_PARAM , class param_cb(4) ASDK_PARAM , class param_cb(5) ASDK_PARAM , class param_cb(6) ASDK_PARAM , class param_cb(7) ASDK_PARAM 
#           define    ASDK_FUNCTION_ARGS_LIST_7(param_cb)       param_cb(1)            ,       param_cb(2)            ,       param_cb(3)            ,       param_cb(4)            ,       param_cb(5)            ,       param_cb(6)            ,       param_cb(7)
#           define   ASDK_FUNCTION_ARGS_TYPES_8(param_cb) class param_cb(1) ASDK_PARAM , class param_cb(2) ASDK_PARAM , class param_cb(3) ASDK_PARAM , class param_cb(4) ASDK_PARAM , class param_cb(5) ASDK_PARAM , class param_cb(6) ASDK_PARAM , class param_cb(7) ASDK_PARAM , class param_cb(8) ASDK_PARAM 
#           define    ASDK_FUNCTION_ARGS_LIST_8(param_cb)       param_cb(1)            ,       param_cb(2)            ,       param_cb(3)            ,       param_cb(4)            ,       param_cb(5)            ,       param_cb(6)            ,       param_cb(7)            ,       param_cb(8)
#           define   ASDK_FUNCTION_ARGS_TYPES_9(param_cb) class param_cb(1) ASDK_PARAM , class param_cb(2) ASDK_PARAM , class param_cb(3) ASDK_PARAM , class param_cb(4) ASDK_PARAM , class param_cb(5) ASDK_PARAM , class param_cb(6) ASDK_PARAM , class param_cb(7) ASDK_PARAM , class param_cb(8) ASDK_PARAM , class param_cb(9) ASDK_PARAM 
#           define    ASDK_FUNCTION_ARGS_LIST_9(param_cb)       param_cb(1)            ,       param_cb(2)            ,       param_cb(3)            ,       param_cb(4)            ,       param_cb(5)            ,       param_cb(6)            ,       param_cb(7)            ,       param_cb(8)            ,       param_cb(9)
#           define  ASDK_FUNCTION_ARGS_TYPES_10(param_cb) class param_cb(1) ASDK_PARAM , class param_cb(2) ASDK_PARAM , class param_cb(3) ASDK_PARAM , class param_cb(4) ASDK_PARAM , class param_cb(5) ASDK_PARAM , class param_cb(6) ASDK_PARAM , class param_cb(7) ASDK_PARAM , class param_cb(8) ASDK_PARAM , class param_cb(9) ASDK_PARAM , class param_cb(10) ASDK_PARAM 
#           define   ASDK_FUNCTION_ARGS_LIST_10(param_cb)       param_cb(1)            ,       param_cb(2)            ,       param_cb(3)            ,       param_cb(4)            ,       param_cb(5)            ,       param_cb(6)            ,       param_cb(7)            ,       param_cb(8)            ,       param_cb(9)            ,       param_cb(10)

#           define ASDK_FUNCTION_ARGS_TYPES_CB(N,param_cb) ASDK_CAT(ASDK_FUNCTION_ARGS_TYPES_, ASDK_WRAP(N))(param_cb)
#           define ASDK_FUNCTION_ARGS_LIST_CB(N,param_cb)  ASDK_CAT(ASDK_FUNCTION_ARGS_LIST_,  ASDK_WRAP(N))(param_cb)
#           define ASDK_FUNCTION_ARGS_TYPES(N) ASDK_FUNCTION_ARGS_TYPES_CB(N,ASDK_PARAM_T)
#           define ASDK_FUNCTION_ARGS_LIST(N)  ASDK_FUNCTION_ARGS_LIST_CB(N,ASDK_PARAM_T)
#           define ASDK_PARAM_T(N) Arg##N##T
#           define ASDK_PARAM
#           endif // ASDK_FUNCTION_ARGS_TYPES

            struct arg_type_ph;

            template<class ClassT, class ReturnT = void
#           undef ASDK_PARAM
#           define ASDK_PARAM = void
                , ASDK_FUNCTION_ARGS_TYPES(10)
#           undef ASDK_PARAM
#           define ASDK_PARAM
            >
            struct function_traits_storage {
                typedef function_traits_storage storage;
                typedef ReturnT return_type;
                typedef ClassT class_type;
                typedef Arg1T arg1_type; typedef Arg2T arg2_type; typedef Arg3T arg3_type; typedef Arg4T arg4_type; typedef Arg5T arg5_type;
                typedef Arg6T arg6_type; typedef Arg7T arg7_type; typedef Arg8T arg8_type; typedef Arg9T arg9_type; typedef Arg10T arg10_type;
            };

            template<class FunctionTraitsStorage>
            struct arg_last { typedef void type; };

#           ifndef ASDK_ARG_LAST_IMPL

#           define ASDK_ARG_LAST_IMPL(N)                                               \
            template<class ClassT, class ReturnT, ASDK_FUNCTION_ARGS_TYPES(N)>         \
            struct arg_last<                                                           \
                function_traits_storage< ClassT, ReturnT, ASDK_FUNCTION_ARGS_LIST(N) > \
            > { typedef Arg##N##T type; }

            ASDK_ARG_LAST_IMPL(10); ASDK_ARG_LAST_IMPL(9); ASDK_ARG_LAST_IMPL(8); ASDK_ARG_LAST_IMPL(7); ASDK_ARG_LAST_IMPL(6);
            ASDK_ARG_LAST_IMPL(5);  ASDK_ARG_LAST_IMPL(4); ASDK_ARG_LAST_IMPL(3); ASDK_ARG_LAST_IMPL(2); ASDK_ARG_LAST_IMPL(1);

#           undef ASDK_ARG_LAST_IMPL
#           endif

            template<class FunctionTraitsStorage1, class FunctionTraitsStorage2
            , class FunctionTraitsStorage3 = void>
            struct function_traits_storage_add;
#           ifndef ASDK_FUNCTION_TRAITS_STORAGE_ADD

#           define ASDK_FunctionTraitsStorage2_CB(N) typename FunctionTraitsStorage2::arg##N##_type
#           define ASDK_FUNCTION_TRAITS_STORAGE_ADD(LhsN,RhsN)                       \
            template<                                                                \
                ASDK_FUNCTION_ARGS_TYPES(LhsN),                                      \
                class FunctionTraitsStorage2                                         \
            >                                                                        \
            struct function_traits_storage_add <                                     \
                function_traits_storage<ASDK_FUNCTION_ARGS_LIST(LhsN)>,              \
                FunctionTraitsStorage2, void                                         \
            >                                                                        \
            {                                                                        \
                typedef function_traits_storage<                                     \
                    ASDK_FUNCTION_ARGS_LIST(LhsN),                                   \
                    ASDK_FUNCTION_ARGS_LIST_CB(RhsN, ASDK_FunctionTraitsStorage2_CB) \
                > type;                                                              \
            }

            ASDK_FUNCTION_TRAITS_STORAGE_ADD(5, 5);
            ASDK_FUNCTION_TRAITS_STORAGE_ADD(9, 1); ASDK_FUNCTION_TRAITS_STORAGE_ADD(8, 2); ASDK_FUNCTION_TRAITS_STORAGE_ADD(7, 3); ASDK_FUNCTION_TRAITS_STORAGE_ADD(6, 4);
            ASDK_FUNCTION_TRAITS_STORAGE_ADD(1, 9); ASDK_FUNCTION_TRAITS_STORAGE_ADD(2, 8); ASDK_FUNCTION_TRAITS_STORAGE_ADD(3, 7); ASDK_FUNCTION_TRAITS_STORAGE_ADD(4, 6);

#           undef ASDK_FunctionTraitsStorage2_CB
#           undef ASDK_FUNCTION_TRAITS_STORAGE_ADD

            template<class FunctionTraitsStorage1, class FunctionTraitsStorage2
                , class FunctionTraitsStorage3>
            struct function_traits_storage_add
            { 
                typedef typename function_traits_storage_add<FunctionTraitsStorage1, FunctionTraitsStorage2>::type add12;
                typedef typename function_traits_storage_add<add12, FunctionTraitsStorage3>::type type;
            };

            template<class FunctionTraitsStorage1, class FunctionTraitsStorage2>
            struct function_traits_storage_add<FunctionTraitsStorage1, FunctionTraitsStorage2>;

#           endif // ASDK_FUNCTION_TRAITS_STORAGE_ADD

            template<class FuncT>
            struct function_traits_impl : function_traits_storage<void> {};
            template<ASDK_FUNCTION_ARGS_TYPES(10)>
            struct function_traits_impl<
                function_traits_storage<ASDK_FUNCTION_ARGS_LIST(10)>*
            > : function_traits_storage<ASDK_FUNCTION_ARGS_LIST(10)> {};

            template<class ReturnT>
            struct function_traits_impl<ReturnT(**)()> : function_traits_storage<void, ReturnT>{};

#           ifndef ASDK_FUNCTION_TRAITS
#           if !defined(__BORLANDC__) // Borland C++ Builder has a bug of member function detection in template params
                template<class ClassT, class ReturnT>
                struct function_traits_impl<ReturnT(ClassT::**)()> : function_traits_storage<ClassT, ReturnT> {};
                template<class ClassT, class ReturnT>
                struct function_traits_impl<ReturnT(ClassT::**)() const> : function_traits_storage<ClassT, ReturnT> {};
#               define ASDK_FUNCTION_TRAITS                                                                                          \
                template<class ReturnT, ASDK_FUNCTION_ARGS_TYPES(ASDK_FUNCTION_ARGS_N)>                                              \
                struct function_traits_impl<ReturnT(**)(ASDK_FUNCTION_ARGS_LIST(ASDK_FUNCTION_ARGS_N))>                              \
                : function_traits_storage<void, ReturnT, ASDK_FUNCTION_ARGS_LIST(ASDK_FUNCTION_ARGS_N)> {};                          \
                template<class ClassT, class ReturnT, ASDK_FUNCTION_ARGS_TYPES(ASDK_FUNCTION_ARGS_N)>                                \
                struct function_traits_impl<ReturnT(ClassT::**)(ASDK_FUNCTION_ARGS_LIST(ASDK_FUNCTION_ARGS_N))>                      \
                    : function_traits_storage<ClassT, ReturnT, ASDK_FUNCTION_ARGS_LIST(ASDK_FUNCTION_ARGS_N)> {};                    \
                template<class ClassT, class ReturnT, ASDK_FUNCTION_ARGS_TYPES(ASDK_FUNCTION_ARGS_N)>                                \
                struct function_traits_impl<ReturnT(ClassT::**)(ASDK_FUNCTION_ARGS_LIST(ASDK_FUNCTION_ARGS_N)) const>                \
                    : function_traits_storage<const ClassT, ReturnT, ASDK_FUNCTION_ARGS_LIST(ASDK_FUNCTION_ARGS_N)> {};
#           else
#               define ASDK_FUNCTION_TRAITS                                                                           \
                template<class ReturnT, ASDK_FUNCTION_ARGS_TYPES(ASDK_FUNCTION_ARGS_N)>                               \
                struct function_traits_impl<ReturnT(**)(ASDK_FUNCTION_ARGS_LIST(ASDK_FUNCTION_ARGS_N))> \
                : function_traits_storage<void, ReturnT, ASDK_FUNCTION_ARGS_LIST(ASDK_FUNCTION_ARGS_N)> {};
#           endif

#           define ASDK_FUNCTION_ARGS_N 1
                ASDK_FUNCTION_TRAITS
#           undef ASDK_FUNCTION_ARGS_N
#           define ASDK_FUNCTION_ARGS_N 2
                ASDK_FUNCTION_TRAITS
#           undef ASDK_FUNCTION_ARGS_N
#           define ASDK_FUNCTION_ARGS_N 3
                ASDK_FUNCTION_TRAITS
#           undef ASDK_FUNCTION_ARGS_N
#           define ASDK_FUNCTION_ARGS_N 4
                ASDK_FUNCTION_TRAITS
#           undef ASDK_FUNCTION_ARGS_N
#           define ASDK_FUNCTION_ARGS_N 5
                ASDK_FUNCTION_TRAITS
#           undef ASDK_FUNCTION_ARGS_N
#           define ASDK_FUNCTION_ARGS_N 6
                ASDK_FUNCTION_TRAITS
#           undef ASDK_FUNCTION_ARGS_N
#           define ASDK_FUNCTION_ARGS_N 7
                ASDK_FUNCTION_TRAITS
#           undef ASDK_FUNCTION_ARGS_N
#           define ASDK_FUNCTION_ARGS_N 8
                ASDK_FUNCTION_TRAITS
#           undef ASDK_FUNCTION_ARGS_N
#           define ASDK_FUNCTION_ARGS_N 9
                ASDK_FUNCTION_TRAITS
#           undef ASDK_FUNCTION_ARGS_N
#           define ASDK_FUNCTION_ARGS_N 10
                ASDK_FUNCTION_TRAITS
#           undef ASDK_FUNCTION_ARGS_N

#           undef ASDK_FUNCTION_TRAITS
#           endif // ASDK_FUNCTION_TRAITS
            

#           ifdef ASDK_FUNCTION_ARGS_TYPES
#           undef ASDK_FUNCTION_ARGS_TYPES1 
#           undef ASDK_FUNCTION_ARGS_LIST1  
#           undef ASDK_FUNCTION_ARGS_TYPES2 
#           undef ASDK_FUNCTION_ARGS_LIST2  
#           undef ASDK_FUNCTION_ARGS_TYPES3 
#           undef ASDK_FUNCTION_ARGS_LIST3  
#           undef ASDK_FUNCTION_ARGS_TYPES4 
#           undef ASDK_FUNCTION_ARGS_LIST4  
#           undef ASDK_FUNCTION_ARGS_TYPES5 
#           undef ASDK_FUNCTION_ARGS_LIST5  
#           undef ASDK_FUNCTION_ARGS_TYPES6 
#           undef ASDK_FUNCTION_ARGS_LIST6  
#           undef ASDK_FUNCTION_ARGS_TYPES7 
#           undef ASDK_FUNCTION_ARGS_LIST7  
#           undef ASDK_FUNCTION_ARGS_TYPES8 
#           undef ASDK_FUNCTION_ARGS_LIST8  
#           undef ASDK_FUNCTION_ARGS_TYPES9 
#           undef ASDK_FUNCTION_ARGS_LIST9  
#           undef ASDK_FUNCTION_ARGS_TYPES10
#           undef ASDK_FUNCTION_ARGS_LIST10 

#           undef ASDK_FUNCTION_ARGS_TYPES
#           undef ASDK_FUNCTION_ARGS_LIST

#           undef ASDK_PARAM
#           endif // ASDK_FUNCTION_ARGS_TYPES


            template<class FuncT>
            struct function_traits : function_traits_impl<FuncT*> {};

            template<bool = true
                , bool = true, bool = true, bool = true, bool = true, bool = true
                , bool = true, bool = true, bool = true, bool = true, bool = true
                , bool = true, bool = true, bool = true, bool = true, bool = true
                , bool = true, bool = true, bool = true, bool = true, bool = true
            > struct is_all_same : false_type {};
            template<> struct is_all_same<true
                , true, true, true, true, true
                , true, true, true, true, true
                , true, true, true, true, true
                , true, true, true, true, true
            >: true_type {};

            template<class Func1T, class Func2T, bool>
            struct is_compatible_function_args_impl { typedef true_type is_same_type; };
            template<class Func1T, class Func2T>
            struct is_compatible_function_args_impl<Func1T, Func2T, false> {
                typedef function_traits<Func1T> func1_traits;
                typedef function_traits<Func2T> func2_traits;
                typedef is_all_same < 
                    is_same<typename func1_traits::return_type, typename func2_traits::return_type>::value == bool(true) 
                    || is_same<arg_type_ph, typename func2_traits::return_type>::value == bool(true)
#                   define ASDK_IS(N)                                                                                        \
                    is_same<typename func1_traits::arg##N##_type, typename func2_traits::arg##N##_type>::value == bool(true) \
                    || is_same<arg_type_ph, typename func2_traits::arg##N##_type>::value == bool(true)
                    , ASDK_IS(1), ASDK_IS(2), ASDK_IS(3), ASDK_IS(4), ASDK_IS(5)
                    , ASDK_IS(6), ASDK_IS(7), ASDK_IS(8), ASDK_IS(9), ASDK_IS(10)
#                   undef ASDK_IS
                > is_same_type;
            };

            template<class Func1T, class Func2T>
            struct is_compatible_function_args :
                is_compatible_function_args_impl<Func1T, Func2T, is_same<Func1T, Func2T>::value == bool(true)>::is_same_type {};
        }



        // template_callback
        namespace type_traits {
            template<class FuncT, class ReflectionT>
            struct template_callback {
                typedef is_compatible_function_args<FuncT, bool(*)(asITypeInfo&, bool&)> is_compatible_with1;
                typedef is_compatible_function_args<FuncT, bool(*)(asITypeInfo&, bool*)> is_compatible_with2;
                typedef is_compatible_function_args<FuncT, bool(*)(asITypeInfo&, bool*)> is_compatible_with3;
                typedef is_compatible_function_args<FuncT, bool(*)(asITypeInfo*, bool*)> is_compatible_with4;
                typedef 
                typename
                conditional<ReflectionT, arg_type_ph,
                    is_compatible_with1::value == bool(true) ||
                    is_compatible_with2::value == bool(true) ||
                    is_compatible_with3::value == bool(true) ||
                    is_compatible_with4::value == bool(true)
                >::type type;
            };
        }


        // constructor
        namespace type_traits {

            template<int ObjTypeT = 0
                , int ObjFlag1 = 0
                , int ObjFlag2 = 0
                , int ObjFlag3 = 0
                , int ObjFlag4 = 0
                , int ObjFlag5 = 0
            >
            struct reflect_flags{
                static const bool is_template =
                    (ObjTypeT & AngelScript::asEObjTypeFlags::asOBJ_TEMPLATE) ? true : (
                        (ObjFlag1 & AngelScript::asEObjTypeFlags::asOBJ_TEMPLATE) ? true : (
                            (ObjFlag2 & AngelScript::asEObjTypeFlags::asOBJ_TEMPLATE) ? true : (
                                (ObjFlag3 & AngelScript::asEObjTypeFlags::asOBJ_TEMPLATE) ? true : (
                                    (ObjFlag4 & AngelScript::asEObjTypeFlags::asOBJ_TEMPLATE) ? true : (
                                        (ObjFlag5 & AngelScript::asEObjTypeFlags::asOBJ_TEMPLATE) ? true : (
                                            false))))))
                    ;
                static const bool is_reference =
                    (ObjTypeT & AngelScript::asEObjTypeFlags::asOBJ_REF) ? true : (
                        (ObjFlag1 & AngelScript::asEObjTypeFlags::asOBJ_REF) ? true : (
                            (ObjFlag2 & AngelScript::asEObjTypeFlags::asOBJ_REF) ? true : (
                                (ObjFlag3 & AngelScript::asEObjTypeFlags::asOBJ_REF) ? true : (
                                    (ObjFlag4 & AngelScript::asEObjTypeFlags::asOBJ_REF) ? true : (
                                        (ObjFlag5 & AngelScript::asEObjTypeFlags::asOBJ_REF) ? true : (
                                            false))))))
                    ;
                static const bool is_class =
                    (ObjTypeT & AngelScript::asEObjTypeFlags::asOBJ_APP_CLASS) ? true : (
                        (ObjFlag1 & AngelScript::asEObjTypeFlags::asOBJ_APP_CLASS) ? true : (
                            (ObjFlag2 & AngelScript::asEObjTypeFlags::asOBJ_APP_CLASS) ? true : (
                                (ObjFlag3 & AngelScript::asEObjTypeFlags::asOBJ_APP_CLASS) ? true : (
                                    (ObjFlag4 & AngelScript::asEObjTypeFlags::asOBJ_APP_CLASS) ? true : (
                                        (ObjFlag5 & AngelScript::asEObjTypeFlags::asOBJ_APP_CLASS) ? true : (
                                            false))))))
                    ;

                typedef 
                typename
                type_traits::conditional<
                    void,
                    AngelScript::asEObjTypeFlags::type,
                    (reflect_flags::is_reference && reflect_flags::is_class) == bool(true)
                >::type asEObjTypeFlags;

                static const asEObjTypeFlags object_type = asEObjTypeFlags(ObjTypeT);
            };

            template<class Flags, class ClassT, class FuncT, class ReflectionT
                , class DeclT = void(*)(arg_type_ph, arg_type_ph, arg_type_ph, arg_type_ph, arg_type_ph)>
            struct constructor {
                typedef function_traits<DeclT> decl_traits_type;
                typedef typename decl_traits_type::storage decl_traits_storage;

                typedef Flags flags;

                
                typedef
                typename
                conditional<
                    function_traits_storage<void, void>,
                    function_traits_storage<void, ClassT*>,
                    flags::is_reference == bool(false)
                >::type return_pointer_storage;

                typedef
                typename
                conditional<
                    function_traits_storage<void, void>,
                    function_traits_storage<void, ClassT&>,
                    flags::is_reference == bool(false)
                >::type return_reference_storage;

                typedef
                typename
                conditional<
                    function_traits_storage<void, void>,
                    function_traits_storage<void, void, asITypeInfo&>,
                    flags::is_template == bool(false)
                >::type ti_reference_storage;
                typedef
                typename
                conditional<
                    function_traits_storage<void, void>,
                    function_traits_storage<void, void, asITypeInfo*>,
                    flags::is_template == bool(false)
                >::type ti_pointer_storage;
                typedef function_traits_storage<void, void, ClassT&>   class_reference_storage;
                typedef function_traits_storage<void, void, ClassT*>     class_pointer_storage;
                typedef typename function_traits_storage_add<
                    ti_reference_storage,
                    decl_traits_storage
                >::type ti_decl_reference_storage;
                typedef typename function_traits_storage_add<
                    ti_pointer_storage,
                    decl_traits_storage
                >::type ti_decl_pointer_storage;

                struct cdecl_objlast {
                    typedef typename function_traits_storage_add<
                        ti_decl_reference_storage,
                        class_reference_storage
                    >::type storage1;
                    typedef typename function_traits_storage_add<
                        ti_decl_reference_storage,
                        class_pointer_storage
                    >::type storage2;
                    typedef typename function_traits_storage_add<
                        ti_decl_pointer_storage,
                        class_reference_storage
                    >::type storage3;
                    typedef typename function_traits_storage_add<
                        ti_decl_pointer_storage,
                        class_pointer_storage
                    >::type storage4;

                    typedef is_compatible_function_args<FuncT, storage1> is_compatible_with1;
typedef is_compatible_function_args<FuncT, storage2> is_compatible_with2;
typedef is_compatible_function_args<FuncT, storage3> is_compatible_with3;
typedef is_compatible_function_args<FuncT, storage4> is_compatible_with4;
typedef typename conditional<
    typename conditional<true_type, false_type, flags::is_class == bool(true)>::type, false_type,
    is_compatible_with1::value == bool(true)
    || is_compatible_with2::value == bool(true)
    || is_compatible_with3::value == bool(true)
    || is_compatible_with4::value == bool(true)
>::type is_compatible_with;
                };
                typedef typename cdecl_objlast::is_compatible_with is_compatible_with_cdecl_objlast;

                struct cdecl_objfirst {
                    typedef typename function_traits_storage_add<
                        class_reference_storage,
                        ti_decl_reference_storage
                    >::type storage1;
                    typedef typename function_traits_storage_add<
                        class_reference_storage,
                        ti_decl_pointer_storage
                    >::type storage2;
                    typedef typename function_traits_storage_add<
                        class_pointer_storage,
                        ti_decl_reference_storage
                    >::type storage3;
                    typedef typename function_traits_storage_add<
                        class_pointer_storage,
                        ti_decl_pointer_storage
                    >::type storage4;

                    typedef is_compatible_function_args<FuncT, storage1> is_compatible_with1;
                    typedef is_compatible_function_args<FuncT, storage2> is_compatible_with2;
                    typedef is_compatible_function_args<FuncT, storage3> is_compatible_with3;
                    typedef is_compatible_function_args<FuncT, storage4> is_compatible_with4;
                    typedef typename conditional<
                        typename conditional<true_type, false_type, flags::is_class == bool(true)>::type, false_type,
                        is_compatible_with1::value == bool(true)
                        || is_compatible_with2::value == bool(true)
                        || is_compatible_with3::value == bool(true)
                        || is_compatible_with4::value == bool(true)
                    >::type is_compatible_with;
                };
                typedef typename cdecl_objfirst::is_compatible_with is_compatible_with_cdecl_objfirst;


                struct cdecl_factorycall {
                    typedef typename function_traits_storage_add<
                        return_reference_storage,
                        ti_decl_reference_storage
                    >::type storage1;
                    typedef typename function_traits_storage_add<
                        return_reference_storage,
                        ti_decl_pointer_storage
                    >::type storage2;
                    typedef typename function_traits_storage_add<
                        return_pointer_storage,
                        ti_decl_reference_storage
                    >::type storage3;
                    typedef typename function_traits_storage_add<
                        return_pointer_storage,
                        ti_decl_pointer_storage
                    >::type storage4;

                    typedef is_compatible_function_args<FuncT, storage1> is_compatible_with1;
                    typedef is_compatible_function_args<FuncT, storage2> is_compatible_with2;
                    typedef is_compatible_function_args<FuncT, storage3> is_compatible_with3;
                    typedef is_compatible_function_args<FuncT, storage4> is_compatible_with4;
                    typedef typename conditional<
                        typename conditional<true_type, false_type, flags::is_reference == bool(true)>::type, false_type,
                        is_compatible_with1::value == bool(true)
                        || is_compatible_with2::value == bool(true)
                        || is_compatible_with3::value == bool(true)
                        || is_compatible_with4::value == bool(true)
                    >::type is_compatible_with;
                };
                typedef typename cdecl_factorycall::is_compatible_with is_compatible_with_cdecl_factorycall;

                typedef
                    typename
                    conditional<ReflectionT, arg_type_ph,
                    is_compatible_with_cdecl_objlast::value == bool(true) ||
                    is_compatible_with_cdecl_objfirst::value == bool(true) ||
                    is_compatible_with_cdecl_factorycall::value == bool(true)
                    >::type type;

                typedef function_traits<FuncT> func_traits_type;
                typedef typename func_traits_type::class_type class_type;
                typedef typename func_traits_type::arg1_type arg1_type;
                typedef typename arg_last<func_traits_type>::type argN_type;

            };

            template<class Flags, class ClassT, class FuncT, class ReflectionT, class DeclT>
            struct constructor<Flags, ClassT, FuncT&, ReflectionT, DeclT>
                : constructor<Flags, ClassT, FuncT*, ReflectionT, DeclT>
            { };
        }

        // function
        namespace type_traits {

            template<class FuncT, class ClassT>
            struct func_ptr_converter {
                static AngelScript::asSFuncPtr call(FuncT func) throw() {
                    return asSMethodPtr<sizeof(void (ClassT::*)())>::Convert((void (ClassT::*)())(func));
                }
            };

            template<class FuncT>
            struct func_ptr_converter<FuncT, void> {
                static AngelScript::asSFuncPtr call(FuncT func) throw() {
                    return asFUNCTION(func);
                }
            };

            template<class Flags, class ClassT, class FuncT, class ReflectionT
                , class DeclT = arg_type_ph(*)(arg_type_ph, arg_type_ph, arg_type_ph, arg_type_ph, arg_type_ph)>
            struct function {
                typedef FuncT function_type;
                typedef function_traits<DeclT> decl_traits_type;
                typedef typename decl_traits_type::storage decl_traits_storage;
                typedef Flags flags;

                typedef function_traits<FuncT> func_traits_type;
                typedef typename func_traits_type::return_type ReturnT;
                typedef typename 
                conditional<
                    typename add_reference<ReturnT>::type,
                    ReturnT,
                    flags::is_reference == bool(true) && is_same<ReturnT, ClassT>::value == bool(true)
                >::type return_type;
                typedef typename func_traits_type::class_type class_type;
                typedef typename func_traits_type::arg1_type arg1_type;
                typedef typename arg_last<func_traits_type>::type argN_type;

                struct cdecl_or_thiscall {
                    typedef decl_traits_storage storage1;

                    typedef is_compatible_function_args<FuncT, storage1> is_compatible_with1;
                    typedef typename conditional<
                        true_type, false_type,
                           is_compatible_with1::value == bool(true)
                    >::type is_compatible_with;
                };
                typedef typename cdecl_or_thiscall::is_compatible_with is_compatible_with_cdecl_or_thiscall;



                struct cdecl_objlast {
                    typedef typename function_traits_storage_add<
                        decl_traits_storage,
                        function_traits_storage<class_type, return_type, ClassT&>
                    >::type storage1;
                    typedef typename function_traits_storage_add<
                        decl_traits_storage,
                        function_traits_storage<class_type, return_type, ClassT*>
                    >::type storage2;
                    typedef typename function_traits_storage_add<
                        decl_traits_storage,
                        function_traits_storage<class_type, return_type, const ClassT&>
                    >::type storage3;
                    typedef typename function_traits_storage_add<
                        decl_traits_storage,
                        function_traits_storage<class_type, return_type, const ClassT*>
                    >::type storage4;

                    typedef is_compatible_function_args<FuncT, storage1> is_compatible_with1;
                    typedef is_compatible_function_args<FuncT, storage2> is_compatible_with2;
                    typedef is_compatible_function_args<FuncT, storage3> is_compatible_with3;
                    typedef is_compatible_function_args<FuncT, storage4> is_compatible_with4;
                    typedef typename conditional<
                        true_type, false_type,
                              is_compatible_with1::value == bool(true)
                           || is_compatible_with2::value == bool(true)
                           || is_compatible_with3::value == bool(true)
                           || is_compatible_with4::value == bool(true)
                    >::type is_compatible_with;

                    typedef typename conditional<
                        true_type, false_type,
                              is_compatible_with1::value == bool(false) && is_compatible_with2::value == bool(false)
                           && (is_compatible_with3::value == bool(true) || is_compatible_with4::value == bool(true))
                    >::type is_const;
                }; 
                typedef typename cdecl_objlast::is_compatible_with is_compatible_with_cdecl_objlast;

                struct cdecl_objfirst {
                    typedef typename function_traits_storage_add<
                        function_traits_storage<class_type, return_type, ClassT&>,
                        decl_traits_storage
                    >::type storage1;
                    typedef typename function_traits_storage_add<
                        function_traits_storage<class_type, return_type, ClassT*>,
                        decl_traits_storage
                    >::type storage2;
                    typedef typename function_traits_storage_add<
                        function_traits_storage<class_type, return_type, const ClassT&>,
                        decl_traits_storage
                    >::type storage3;
                    typedef typename function_traits_storage_add<
                        function_traits_storage<class_type, return_type, const ClassT*>,
                        decl_traits_storage
                    >::type storage4;

                    typedef is_compatible_function_args<FuncT, storage1> is_compatible_with1;
                    typedef is_compatible_function_args<FuncT, storage2> is_compatible_with2;
                    typedef is_compatible_function_args<FuncT, storage3> is_compatible_with3;
                    typedef is_compatible_function_args<FuncT, storage4> is_compatible_with4;

                    typedef typename conditional<
                        true_type, false_type,
                              is_compatible_with1::value == bool(true)
                           || is_compatible_with2::value == bool(true)
                           || is_compatible_with3::value == bool(true)
                           || is_compatible_with4::value == bool(true)
                    >::type is_compatible_with;

                    typedef typename conditional<
                        true_type, false_type,
                              is_compatible_with1::value == bool(false) && is_compatible_with2::value == bool(false)
                           && (is_compatible_with3::value == bool(true) || is_compatible_with4::value == bool(true))
                    >::type is_const;
                }; 
                typedef typename cdecl_objfirst::is_compatible_with is_compatible_with_cdecl_objfirst;

                typedef 
                typename
                conditional<ReflectionT, arg_type_ph,
                    is_compatible_with_cdecl_or_thiscall::value == bool(true) ||
                    is_compatible_with_cdecl_objlast::value == bool(true) ||
                    is_compatible_with_cdecl_objfirst::value == bool(true)
                >::type type;



                typedef 
                typename
                conditional<is_same<class_type, void>, false_type,
                    is_compatible_with_cdecl_or_thiscall::value == bool(true)
                >::type is_compatible_with_thiscall;

                typedef 
                typename
                conditional<arg1_type, argN_type,
                    is_compatible_with_cdecl_objfirst::value == bool(true) &&
                    is_compatible_with_cdecl_or_thiscall::value == bool(false)
                >::type thiscall_obj_type;

                typedef 
                typename
                conditional<arg1_type, 
                    typename conditional<argN_type, void, is_compatible_with_cdecl_objlast::value == bool(true)>::type,
                    is_compatible_with_cdecl_objfirst::value == bool(true)
                >::type cdecl_obj_type;

                typedef 
                typename
                conditional<class_type, thiscall_obj_type,
                    is_compatible_with_thiscall::value == bool(true)
                >::type obj_type;

            };
        } // namespace type_traits

        // destructor
        namespace type_traits {
            template<class Flags, class ClassT, class FuncT, class ReflectionT
                , class DeclT = arg_type_ph(*)(arg_type_ph, arg_type_ph, arg_type_ph, arg_type_ph, arg_type_ph)>
            struct destructor:
                function <Flags, ClassT, FuncT, typename conditional<arg_type_ph, ReflectionT, Flags::is_reference>::type,
                DeclT>
            { };
        }

        // reference counting and GC
        namespace type_traits {
            template<class Flags, class ClassT, class FuncT, class ReflectionT>
            struct reference_counting :
                function <Flags, ClassT, FuncT, 
                typename conditional<ReflectionT, arg_type_ph, Flags::is_reference>::type,
                void(*)()>
            { };
        }

        // reflect_helper
        namespace type_traits {
            struct reflect_template_callback_tester
            {
                template<class UndrlyingT, class FuncT>
                static typename template_callback<FuncT, UndrlyingT&>::type
                template_callback_tester(FuncT func);
                template<class UnderlyingT>
                static char
                template_callback_result_tester(const UnderlyingT&);
                template<class UnderlyingT>
                static double
                template_callback_result_tester(const arg_type_ph&);
            };

            template<class UnderlyingT, int>
            struct reflect_helper_cond {
                typedef arg_type_ph type;
            };
            template<class UnderlyingT>
            struct reflect_helper_cond<UnderlyingT, 1> {
                typedef UnderlyingT& type;
            };

            template<class T, class UnderlyingT>
            struct reflect_helper
            {
                enum {
                    sizeof_array = sizeof(
                        reflect_template_callback_tester::template_callback_result_tester<UnderlyingT>(
                            reflect_template_callback_tester::template_callback_tester<UnderlyingT>(T::template_callback)
                    ))
                };
                typedef char(&sizeof_array_type)[sizeof(
                    reflect_template_callback_tester::template_callback_result_tester<UnderlyingT>(
                        reflect_template_callback_tester::template_callback_tester<UnderlyingT>(T::template_callback)
                        ))];
                typedef
                typename reflect_helper_cond<UnderlyingT, sizeof(sizeof_array_type )>::type type;
            };
        } // namespace type_traits


#       ifdef __BORLANDC__
#       define ASDK_SFINAE_DEFAULT_FUNCTION_ARG(expr) int(*)[1] = 0
#       else
#       define ASDK_SFINAE_DEFAULT_FUNCTION_ARG(expr) int(*)[sizeof expr] = 0
#       endif

        struct object_traits {
            struct {
                bool default_constructor;
                bool custom_destructor;
                bool custom_assigment_operator;
                bool custom_copy_constructor;
            } has;
            
            struct {
                bool floating_point;
                bool primitive_type;
                bool class_or_struct;
                bool ref;
                bool c_array;
                bool enum_class;
                bool handle;
            } is;
        };



        template<class T, AngelScript::asEObjTypeFlags::type ObjTypeT
            , AngelScript::asEObjTypeFlags::type ObjFlag1 = type_traits::reflect_flags<>::object_type
            , AngelScript::asEObjTypeFlags::type ObjFlag2 = type_traits::reflect_flags<>::object_type
            , AngelScript::asEObjTypeFlags::type ObjFlag3 = type_traits::reflect_flags<>::object_type
            , AngelScript::asEObjTypeFlags::type ObjFlag4 = type_traits::reflect_flags<>::object_type
            , AngelScript::asEObjTypeFlags::type ObjFlag5 = type_traits::reflect_flags<>::object_type
        >
        struct reflect
        {
            enum { sizeof_T = sizeof(T), sizeof_Tx2 = sizeof_T * 2 };
            typedef type_traits::reflect_flags<ObjTypeT, ObjFlag1, ObjFlag2, ObjFlag3, ObjFlag4, ObjFlag5> flags;

            typedef char(&type_can_be_reference_or_class)[(reflect::flags::is_reference && reflect::flags::is_class) ? -1 : 1];
            typedef char(&type_can_be_reference_or_class_assert)[sizeof(reflect::type_can_be_reference_or_class)];

            typedef AngelScript::asITypeInfo asITypeInfo;
            typedef AngelScript::asECallConvTypes::type asECallConvTypes;
            typedef AngelScript::asEBehaviours::type asEBehaviours;

            reflect(const std::string& name, AngelScript::asIScriptEngine& asIScriptEngine
                , const object_traits& object_traits) : asIScriptEngine(&asIScriptEngine), name(name) {
                init(object_traits);
            }

            reflect(AngelScript::asIScriptEngine& asIScriptEngine, const std::string& name
                , const object_traits& object_traits) : asIScriptEngine(&asIScriptEngine), name(name) {
                init(object_traits);
            }

            reflect(const std::string& name, AngelScript::asIScriptEngine& asIScriptEngine
                , bool has_default_constructor
                , bool has_custom_destructor
                , bool has_custom_assigment_operator
                , bool has_custom_copy_constructor
            ) : asIScriptEngine(&asIScriptEngine), name(name) {
                init(T_object_traits(has_default_constructor, has_custom_destructor, has_custom_assigment_operator, has_custom_copy_constructor));
            }

            reflect(AngelScript::asIScriptEngine& asIScriptEngine, const std::string& name
                , bool has_default_constructor
                , bool has_custom_destructor
                , bool has_custom_assigment_operator
                , bool has_custom_copy_constructor
            ) : asIScriptEngine(&asIScriptEngine), name(name) {
                init(T_object_traits(has_default_constructor, has_custom_destructor, has_custom_assigment_operator, has_custom_copy_constructor));
            }

            template<class FuncT>
            typename type_traits::constructor<flags, T, FuncT, reflect&, void(*)()>::type
            constructor(FuncT func) {
                const std::string return_str = flags::is_reference ? (name + "@") : "void";
                const std::string ctor_str = flags::is_template ? (return_str + " ctor(int& in)") : (return_str + " ctor()");

                typedef type_traits::constructor<flags, T, FuncT, reflect&, void(*)()> ctor_traits;
                typedef typename ctor_traits::class_type class_type;
                typedef type_traits::func_ptr_converter<FuncT, class_type> func_ptr_convert;
                const asECallConvTypes asCALL =
                    type_traits::is_same< class_type, void>::value ? (
                        ctor_traits::is_compatible_with_cdecl_objfirst::value ? asCALL_CDECL_OBJFIRST :
                        ctor_traits::is_compatible_with_cdecl_objlast::value ? asCALL_CDECL_OBJLAST :
                    asCALL_CDECL)
                    : (
                    asCALL_THISCALL);
                const asEBehaviours asBEHAVE = ctor_traits::is_compatible_with_cdecl_factorycall::value 
                    ? asBEHAVE_FACTORY 
                    : asBEHAVE_CONSTRUCT;
                const AngelScript::asSFuncPtr asFunc = func_ptr_convert::call(func);
                asdk::expose(*asIScriptEngine, name, ctor_str, asBEHAVE, asFunc, asCALL);
                return *this;
            }

            reflect&
            constructor(int(*)[sizeof(static_cast<T>(T())) == sizeof(T)] = 0) {
                typedef typename type_traits::conditional<
                    void(*)(T&, asITypeInfo&),
                    void(*)(T&),
                    reflect::flags::is_template == bool(true)
                >::type FuncT;
                FuncT ctor_func = &default_ctor;
                return constructor(ctor_func);
            }

            template<class Arg1T, class FuncT>
            typename type_traits::constructor<flags, T, FuncT, reflect&, void(*)(Arg1T)>::type
            constructor(const std::string& arg1_str, FuncT func) {
                const std::string return_str = flags::is_reference ? (name + "@") : "void";
                const std::string ctor_str = (flags::is_template ? (return_str + " ctor(int&in, ") : (return_str + " ctor(")) + format_function_argument<Arg1T>(arg1_str) + ")";

                typedef type_traits::constructor<flags, T, FuncT, reflect, void(*)(Arg1T)> ctor_traits;
                typedef typename ctor_traits::class_type class_type;
                typedef type_traits::func_ptr_converter<FuncT, class_type> func_ptr_convert;
                const asECallConvTypes asCALL =
                    type_traits::is_same< class_type, void>::value ? (
                        ctor_traits::is_compatible_with_cdecl_objfirst::value ? asCALL_CDECL_OBJFIRST :
                        ctor_traits::is_compatible_with_cdecl_objlast::value ? asCALL_CDECL_OBJLAST :
                    asCALL_CDECL)
                    : (
                    asCALL_THISCALL);
                const asEBehaviours asBEHAVE = ctor_traits::is_compatible_with_cdecl_factorycall::value
                    ? asBEHAVE_FACTORY
                    : asBEHAVE_CONSTRUCT;
                const AngelScript::asSFuncPtr asFunc = func_ptr_convert::call(func);
                asdk::expose(*asIScriptEngine, name, ctor_str, asBEHAVE, asFunc, asCALL);
                return *this;
            }
            template<class Arg1T>
            reflect&
            constructor(const std::string& arg1_str
                , ASDK_SFINAE_DEFAULT_FUNCTION_ARG(T(type_traits::declval<Arg1T>()))) {
                typedef typename type_traits::conditional<
                    void(*)(T&, asITypeInfo&, Arg1T),
                    void(*)(T&, Arg1T),
                    flags::is_template == bool(true)
                >::type FuncT;
                FuncT ctor_func = &ctor;
                return constructor<Arg1T>(arg1_str, ctor_func);
            }

            template<class Arg1T, class Arg2T, class FuncT>
            typename type_traits::constructor<flags, T, FuncT, reflect&, void(*)(Arg1T, Arg2T)>::type
            constructor(const std::string& arg1_str, const std::string& arg2_str, FuncT func) {
                const std::string return_str = flags::is_reference ? (name + "@") : "void";
                const std::string ctor_str = (flags::is_template ? (return_str + " ctor(int&in, ") : (return_str + " ctor("))
                    + format_function_argument<Arg1T>(arg1_str) 
                    + ", " 
                    + format_function_argument<Arg1T>(arg2_str) 
                    + ")";

                typedef type_traits::constructor<flags, T, FuncT, reflect, void(*)(Arg1T, Arg2T)> ctor_traits;
                typedef typename ctor_traits::class_type class_type;
                typedef type_traits::func_ptr_converter<FuncT, class_type> func_ptr_convert;
                const asECallConvTypes asCALL =
                    type_traits::is_same< class_type, void>::value ? (
                        ctor_traits::is_compatible_with_cdecl_objfirst::value ? asCALL_CDECL_OBJFIRST :
                        ctor_traits::is_compatible_with_cdecl_objlast::value ? asCALL_CDECL_OBJLAST :
                    asCALL_CDECL)
                    : (
                    asCALL_THISCALL);
                const asEBehaviours asBEHAVE = ctor_traits::is_compatible_with_cdecl_factorycall::value
                    ? asBEHAVE_FACTORY
                    : asBEHAVE_CONSTRUCT;
                const AngelScript::asSFuncPtr asFunc = func_ptr_convert::call(func);
                asdk::expose(*asIScriptEngine, name, ctor_str, asBEHAVE, asFunc, asCALL);
                return *this;
            }
            template<class Arg1T, class Arg2T>
            reflect&
            constructor(const std::string& arg1_str, const std::string& arg2_str
                , ASDK_SFINAE_DEFAULT_FUNCTION_ARG(T(type_traits::declval<Arg1T>(), type_traits::declval<Arg2T>()))) {
                typedef typename type_traits::conditional<
                    void(*)(T&, asITypeInfo&, Arg1T, Arg2T),
                    void(*)(T&, Arg1T, Arg2T),
                    reflect::flags::is_template == bool(true)
                >::type FuncT;
                return constructor<Arg1T>(arg1_str, arg2_str, static_cast<FuncT>(&ctor));
            }

            template<class FuncT>
            typename type_traits::function<flags, T, FuncT, reflect&>::type
            function(typename type_traits::function<flags, T, FuncT,
                typename type_traits::conditional<
                    const std::string&,
                    void, sizeof(FuncT) == sizeof(void*)
                >::type
            >::type func_str, FuncT func) {
                typedef type_traits::function<flags, T, FuncT, reflect&> func_traits;
                return function_with_traits<FuncT, func_traits, typename func_traits::class_type>(func_str, func);
            }

            template<class ReturnT, class ClassT>
            reflect&
            function(const std::string& func_str, ReturnT(ClassT::* func)()) {
                typedef type_traits::function<flags, T, ReturnT(*)(), reflect&> func_traits;
                return function_with_traits<func_traits, ClassT>(func_str, func);
            }

            template<class ReturnT, class ClassT>
            reflect&
            function(const std::string& func_str, ReturnT(ClassT::* func)() const) {
                typedef type_traits::function<flags, T, ReturnT(*)(), reflect&> func_traits;
                return function_with_traits<func_traits, ClassT>(func_str, func);
            }

            template<class ReturnT, class ClassT, class Arg0T>
            reflect&
            function(const std::string& func_str, ReturnT(ClassT::* func)(Arg0T)) {
                typedef type_traits::function<flags, T, ReturnT(*)(Arg0T), reflect&> func_traits;
                return function_with_traits<func_traits, ClassT>(func_str, func);
            }

            template<class ReturnT, class ClassT, class Arg0T>
            reflect&
            function(const std::string& func_str, ReturnT(ClassT::* func)(Arg0T) const) {
                typedef type_traits::function<flags, T, ReturnT(*)(Arg0T), reflect&> func_traits;
                return function_with_traits<func_traits, ClassT>(func_str, func);
            }

            template<class FuncT>
            typename type_traits::destructor<flags, T, FuncT, reflect&, void(*)()>::type
            destructor(FuncT func) {
                typedef type_traits::destructor<flags, T, FuncT, reflect&, void(*)()> func_traits;
                typedef typename func_traits::obj_type obj_type;
                typedef typename func_traits::class_type class_type;
                typedef type_traits::func_ptr_converter<FuncT, class_type> func_ptr_convert;
                const asECallConvTypes asCALL = 
                    type_traits::is_same<class_type, void>::value ? (
                        func_traits::is_compatible_with_cdecl_objfirst::value ? asCALL_CDECL_OBJFIRST :
                        func_traits::is_compatible_with_cdecl_objlast::value ? asCALL_CDECL_OBJLAST :
                    asCALL_CDECL)
                    : (
                    asCALL_THISCALL);
                const AngelScript::asSFuncPtr asFunc = func_ptr_convert::call(func);
                asdk::expose(*asIScriptEngine, name, "void dtor()", asBEHAVE_DESTRUCT, asFunc, asCALL);
                return *this;
            }

            typename type_traits::destructor<flags, T, void(*)(), reflect&, void(*)()>::type destructor() {
                return destructor(dtor);
            }

            template<class FuncT>
            typename type_traits::reference_counting<flags, T, FuncT, reflect&>::type
            add_reference(FuncT func) {
                typedef type_traits::reference_counting<flags, T, FuncT, reflect&> func_traits;
                typedef typename func_traits::obj_type obj_type;
                typedef typename func_traits::class_type class_type;
                typedef type_traits::func_ptr_converter<FuncT, class_type> func_ptr_convert;
                const asECallConvTypes asCALL = 
                    type_traits::is_same<class_type, void>::value ? (
                        func_traits::is_compatible_with_cdecl_objfirst::value ? asCALL_CDECL_OBJFIRST :
                        func_traits::is_compatible_with_cdecl_objlast::value ? asCALL_CDECL_OBJLAST :
                    asCALL_CDECL)
                    : (
                    asCALL_THISCALL);
                const AngelScript::asSFuncPtr asFunc = func_ptr_convert::call(func);
                asdk::expose(*asIScriptEngine, name, "void addref()", asBEHAVE_ADDREF, asFunc, asCALL);
                return *this;
            }

            template<class FuncT>
            typename type_traits::reference_counting<flags, T, FuncT, reflect&>::type
            release_reference(FuncT func) {
                typedef type_traits::reference_counting<flags, T, FuncT, reflect&> func_traits;
                typedef typename func_traits::obj_type obj_type;
                typedef typename func_traits::class_type class_type;
                typedef type_traits::func_ptr_converter<FuncT, class_type> func_ptr_convert;
                const asECallConvTypes asCALL =
                    type_traits::is_same<class_type, void>::value ? (
                        func_traits::is_compatible_with_cdecl_objfirst::value ? asCALL_CDECL_OBJFIRST :
                        func_traits::is_compatible_with_cdecl_objlast::value ? asCALL_CDECL_OBJLAST :
                        asCALL_CDECL)
                    : (
                        asCALL_THISCALL);
                const AngelScript::asSFuncPtr asFunc = func_ptr_convert::call(func);
                asdk::expose(*asIScriptEngine, name, "void release()", asBEHAVE_RELEASE, asFunc, asCALL);
                return *this;
            }

            template<class OtherT, class ReturnT, class FuncT>
            typename type_traits::function<flags, T, FuncT, reflect&, ReturnT(*)(OtherT)>::type
            operator_assign(typename type_traits::function<flags, T, FuncT, const std::string&, ReturnT(*)(OtherT)>::type other_str
                , typename type_traits::function<flags, T, FuncT, const std::string&, ReturnT(*)(OtherT)>::type return_str
                , FuncT func)
            {
                const std::string op_str = return_str + " opAssign(" + format_function_argument<const OtherT>(other_str) + ")";
            
                typedef type_traits::function<flags, T, FuncT, reflect&, ReturnT(*)(OtherT)> op_traits;
                typedef typename op_traits::class_type class_type;
                typedef type_traits::func_ptr_converter<FuncT, class_type> func_ptr_convert;
                const asECallConvTypes asCALL =
                    type_traits::is_same< class_type, void>::value ? (
                        op_traits::is_compatible_with_cdecl_objfirst::value ? asCALL_CDECL_OBJFIRST :
                        op_traits::is_compatible_with_cdecl_objlast::value ? asCALL_CDECL_OBJLAST :
                    asCALL_CDECL)
                    : (
                    asCALL_THISCALL);
                const AngelScript::asSFuncPtr asFunc = func_ptr_convert::call(func);
                asdk::expose(*asIScriptEngine, name, op_str, asFunc, asCALL);
                return *this;
            }

            template<class OtherT, class FuncT>
            typename type_traits::function<flags, T, FuncT, reflect&, T(*)(OtherT)>::type
            operator_assign(typename type_traits::function<flags, T, FuncT, const std::string&, T&(*)(OtherT)>::type other_str
                , FuncT func)
            {
                return operator_assign<OtherT, T, FuncT>(other_str, name + "&", func);
            }

            template<class FuncT>
            typename type_traits::function<flags, T, FuncT, reflect&, T&(*)(const T&)>::type
            operator_assign(FuncT func)
            {
                return operator_assign<const T&>(name + "&", func);
            }

            template<class OtherT>
            reflect&
            operator_assign(const std::string& other_str
                , ASDK_SFINAE_DEFAULT_FUNCTION_ARG(((*(T*)(0)) = (*(const OtherT*)(0)))))
            {
                return operator_assign<T, OtherT>(other_str, name + "&", static_cast<T & (*)(T&, const OtherT&)>(opAssign));
            }

            reflect&
            operator_assign(int(*)[sizeof((*(T*)(0)) = (*(const T*)(0)))] = 0)
            {
                T& (*op_func)(T&, const T&) = &opAssign;
                return operator_assign(op_func);
            }
            
            template<class OtherT, class FuncT>
            typename type_traits::function<flags, T, FuncT, reflect&, bool(*)(OtherT)>::type
            operator_equal_to(FuncT func
                , typename type_traits::function<flags, T, FuncT, const std::string&, bool(*)(OtherT)>::type other_str)
            {
                const std::string op_str = "bool opEquals(" + format_function_argument<OtherT>(other_str) + ") const";
            
                typedef type_traits::function<flags, T, FuncT, reflect&, bool(*)(OtherT)> op_traits;
                typedef typename op_traits::class_type class_type;
                typedef type_traits::func_ptr_converter<FuncT, class_type> func_ptr_convert;
                const asECallConvTypes asCALL =
                    type_traits::is_same< class_type, void>::value ? (
                        op_traits::is_compatible_with_cdecl_objfirst::value ? asCALL_CDECL_OBJFIRST :
                        op_traits::is_compatible_with_cdecl_objlast::value ? asCALL_CDECL_OBJLAST :
                    asCALL_CDECL)
                    : (
                    asCALL_THISCALL);
                const AngelScript::asSFuncPtr asFunc = func_ptr_convert::call(func);
                asdk::expose(*asIScriptEngine, name, op_str, asFunc, asCALL);
                return *this;
            }
            
            template<class FuncT>
            typename type_traits::function<flags, T, FuncT, reflect&, bool(*)(type_traits::arg_type_ph)>::type
            operator_equal_to(FuncT func
                , typename type_traits::function<flags, T, FuncT, const std::string&, bool(*)(type_traits::arg_type_ph)>::type other_str)
            {
                return operator_equal_to<type_traits::arg_type_ph, FuncT>(func, other_str);
            }
            
            reflect&
            operator_equal_to()
            {
                bool(*op_func)(const T&, const T&) = &opEquals;
                return operator_equal_to(op_func, "const " + name + "&in");
            }

            template<class OtherT>
            reflect&
            operator_equal_to(const std::string& other_str
                , ASDK_SFINAE_DEFAULT_FUNCTION_ARG(( (static_cast<T>(*(T*)(0))) == (static_cast<OtherT>(*(OtherT*)(0))) )))
            {
                bool(*op_func)(const T&, const OtherT&) = &opEquals;
                return operator_equal_to(op_func, other_str);
            }

            template<class OtherT>
            reflect&
            operator==(const std::string& other_str)
            {
                return operator_equal_to(other_str);
            }

            template<class OtherT, class FuncT>
            typename type_traits::function<flags, T, FuncT, reflect&, int(*)(OtherT)>::type
            operator_compare(FuncT func
                , typename type_traits::function<flags, T, FuncT, const std::string&, int(*)(OtherT)>::type other_str)
            {
                const std::string op_str = "int opCmp(" + format_function_argument<OtherT>(other_str) + ") const";
            
                typedef type_traits::function<flags, T, FuncT, reflect&, int(*)(OtherT)> op_traits;
                typedef typename op_traits::class_type class_type;
                typedef type_traits::func_ptr_converter<FuncT, class_type> func_ptr_convert;
                const asECallConvTypes asCALL =
                    type_traits::is_same< class_type, void>::value ? (
                        op_traits::is_compatible_with_cdecl_objfirst::value ? asCALL_CDECL_OBJFIRST :
                        op_traits::is_compatible_with_cdecl_objlast::value ? asCALL_CDECL_OBJLAST :
                    asCALL_CDECL)
                    : (
                    asCALL_THISCALL);
                const AngelScript::asSFuncPtr asFunc = func_ptr_convert::call(func);
                asdk::expose(*asIScriptEngine, name, op_str, asFunc, asCALL);
                return *this;
            }
            
            template<class FuncT>
            typename type_traits::function<flags, T, FuncT, reflect&, int(*)(type_traits::arg_type_ph)>::type
            operator_compare(FuncT func
                , typename type_traits::function<flags, T, FuncT, const std::string&, int(*)(type_traits::arg_type_ph)>::type other_str)
            {
                return operator_compare<type_traits::arg_type_ph, FuncT>(func, other_str);
            }
            
            reflect&
            operator_compare()
            {
                int(*op_func)(const T&, const T&) = &opCmp;
                return operator_compare(op_func, "const " + name + "&in");
            }

            template<class OtherT>
            reflect&
            operator_compare(const std::string &other_str
                , ASDK_SFINAE_DEFAULT_FUNCTION_ARG
                (
                    sizeof (static_cast<T>(*(T*)(0)) < static_cast<OtherT>(*(OtherT*)(0)))
                    +
                    sizeof (static_cast<T>(*(T*)(0)) > static_cast<OtherT>(*(OtherT*)(0)))
                ))
            {
                int(*op_func)(const T&, const OtherT&) = opCmp;
                return operator_compare(op_func, other_str);
            }

            template<class IndexT, class ReturnT, class FuncT>
            typename type_traits::function<flags, T, FuncT, reflect&, ReturnT(*)(IndexT)>::type
            operator_index(typename type_traits::function<flags, T, FuncT, const std::string&, ReturnT(*)(IndexT)>::type index_str
                , typename type_traits::function<flags, T, FuncT, const std::string&, ReturnT(*)(IndexT)>::type return_str
                , FuncT func)
            {
                typedef type_traits::function<flags, T, FuncT, reflect&, ReturnT(*)(IndexT)> op_traits;
                typedef typename op_traits::class_type class_type;
                typedef type_traits::func_ptr_converter<FuncT, class_type> func_ptr_convert;
                typedef typename op_traits::cdecl_obj_type cdecl_obj_type;
                typedef typename type_traits::remove_reference<cdecl_obj_type>::type cdecl_obj_type_clear;
                const std::string op_str = return_str + " opIndex(" + format_function_argument<const IndexT>(index_str) + ")" +
                    (type_traits::is_const<cdecl_obj_type_clear>::value ? " const" : "");
            
                const asECallConvTypes asCALL =
                    type_traits::is_same< class_type, void>::value ? (
                        op_traits::is_compatible_with_cdecl_objfirst::value ? asCALL_CDECL_OBJFIRST :
                        op_traits::is_compatible_with_cdecl_objlast::value ? asCALL_CDECL_OBJLAST :
                    asCALL_CDECL)
                    : (
                    asCALL_THISCALL);
                const AngelScript::asSFuncPtr asFunc = func_ptr_convert::call(func);
                asdk::expose(*asIScriptEngine, name, op_str, asFunc, asCALL);
                return *this;
            }

            template<class IndexT, class ReturnT>
            reflect&
            operator_index(const std::string& index_str,
                const std::string& return_str)
            {
                typedef 
                typename 
                type_traits::remove_reference<ReturnT>::type
                ReturnT_clear;

                typedef 
                typename
                type_traits::conditional<
                    const T&, T&,
                    type_traits::is_const<ReturnT_clear>::value
                >::type type;
                ReturnT(*op_func)(type, IndexT) = &opIndex;
                return operator_index<IndexT, ReturnT>(index_str, return_str, op_func);
            }

#           ifndef BINARY_OPERATOR_DEF
#           define BINARY_OPERATOR_DEF(operator_, opName, opSym)                                                                                   \
            template<class ReturnT, class OtherT, class FuncT>                                                                                     \
            typename type_traits::function<flags, T, FuncT, reflect&, ReturnT(*)(OtherT)>::type                                                    \
            operator_(FuncT func                                                                                                                   \
                , typename type_traits::function<flags, T, FuncT, const std::string&, ReturnT(*)(OtherT)>::type return_str                         \
                , typename type_traits::function<flags, T, FuncT, const std::string&, ReturnT(*)(OtherT)>::type other_str)                         \
            {                                                                                                                                      \
                const std::string op_str = return_str + " " ASDK_STRINGIFY(opName) "(" + format_function_argument<OtherT>(other_str) + ") const";  \
                                                                                                                                                   \
                typedef type_traits::function<flags, T, FuncT, reflect&, ReturnT(*)(OtherT)> op_traits;                                            \
                typedef typename op_traits::class_type class_type;                                                                                 \
                typedef type_traits::func_ptr_converter<FuncT, class_type> func_ptr_convert;                                                       \
                const asECallConvTypes asCALL =                                                                                                    \
                    type_traits::is_same< class_type, void>::value ? (                                                                             \
                        op_traits::is_compatible_with_cdecl_objfirst::value ? asCALL_CDECL_OBJFIRST :                                              \
                        op_traits::is_compatible_with_cdecl_objlast::value ? asCALL_CDECL_OBJLAST :                                                \
                    asCALL_CDECL)                                                                                                                  \
                    : (                                                                                                                            \
                    asCALL_THISCALL);                                                                                                              \
                const AngelScript::asSFuncPtr asFunc = func_ptr_convert::call(func);                                                               \
                asdk::expose(*asIScriptEngine, name, op_str, asFunc, asCALL);                                                                      \
                return *this;                                                                                                                      \
            }                                                                                                                                      \
                                                                                                                                                   \
            template<class OtherT, class FuncT>                                                                                                    \
            typename type_traits::function<flags, T, FuncT, reflect&, T(*)(OtherT)>::type                                                          \
            operator_(FuncT func                                                                                                                   \
                , typename type_traits::function<flags, T, FuncT, const std::string&, T(*)(OtherT)>::type other_str)                               \
            {                                                                                                                                      \
                return operator_<T, OtherT, FuncT>(func, name, other_str);                                                                         \
            }                                                                                                                                      \
                                                                                                                                                   \
            template<class FuncT>                                                                                                                  \
            typename type_traits::function<flags, T, FuncT, reflect&, T(*)(type_traits::arg_type_ph)>::type                                        \
            operator_(FuncT func                                                                                                                   \
                , typename type_traits::function<flags, T, FuncT, const std::string&, T(*)(type_traits::arg_type_ph)>::type other_str)             \
            {                                                                                                                                      \
                return operator_<T, type_traits::arg_type_ph, FuncT>(func, name, other_str);                                                       \
            }                                                                                                                                      \
                                                                                                                                                   \
            reflect&                                                                                                                               \
            operator_()                                                                                                                            \
            {                                                                                                                                      \
                T(*op_func)(const T&, const T&) = &opName; return operator_(op_func, "const " + name + "&in");                                     \
            }                                                                                                                                      \
                                                                                                                                                   \
            template<class OtherT>                                                                                                                 \
            reflect&                                                                                                                               \
            operator_(const std::string &other_str                                                                                                 \
                , ASDK_SFINAE_DEFAULT_FUNCTION_ARG( sizeof(static_cast<T>(*(T*)(0)) opSym static_cast<OtherT>(*(OtherT*)(0))) ))                   \
            {                                                                                                                                      \
                T(*op_func)(const T&, OtherT) = &opName; return operator_(op_func, other_str);                                                     \
            }                                                                                                                                      \
                                                                                                                                                   \
            reflect&                                                                                                                               \
            operator opSym(int)                                                                                                                    \
            {                                                                                                                                      \
                return operator_();                                                                                                                \
            }                                                                                                                                      \
                                                                                                                                                   \
            template<class OtherT>                                                                                                                 \
            reflect&                                                                                                                               \
            operator opSym(                                                                                                                        \
                typename type_traits::conditional<const std::string&, type_traits::arg_type_ph                                                     \
                , sizeof((T)(*((T*)(42))) opSym (OtherT)(*((OtherT*)(42)))) != sizeof_Tx2>::type other_str)                                        \
            {                                                                                                                                      \
                return operator_<OtherT>(other_str);                                                                                               \
            }                                                                                                                                      \
                                                                                                                                                   \
            template<class ReturnT, class OtherT, class ThisT, class FuncT>                                                                        \
            typename type_traits::function<flags, T, FuncT, reflect&, ReturnT(*)(OtherT)>::type                                                    \
            operator_(FuncT func                                                                                                                   \
                , typename type_traits::function<flags, T, FuncT, const std::string&, ReturnT(*)(OtherT)>::type return_str                         \
                , typename type_traits::conditional<const std::string&, void,                                                                      \
                    sizeof (typename type_traits::function<flags, T, FuncT, const std::string&, ReturnT(*)(OtherT)>::                              \
                        is_compatible_with_cdecl_objlast) == sizeof (type_traits::true_type)                                                       \
                >::type other_str)                                                                                                                 \
            {                                                                                                                                      \
                const std::string op_str = return_str + " " ASDK_STRINGIFY(opName) "_r(" + format_function_argument<OtherT>(other_str) + ") const";\
                                                                                                                                                   \
                typedef type_traits::function<flags, T, FuncT, reflect&, ReturnT(*)(OtherT)> op_traits;                                            \
                typedef typename op_traits::class_type class_type;                                                                                 \
                typedef type_traits::func_ptr_converter<FuncT, class_type> func_ptr_convert;                                                       \
                const asECallConvTypes asCALL = asCALL_CDECL_OBJLAST;                                                                              \
                const AngelScript::asSFuncPtr asFunc = func_ptr_convert::call(func);                                                               \
                asdk::expose(*asIScriptEngine, name, op_str, asFunc, asCALL);                                                                      \
                return *this;                                                                                                                      \
            }                                                                                                                                      \
                                                                                                                                                   \
            template<class ReturnT, class OtherT, class ThisT, class FuncT>                                                                        \
            typename type_traits::function<flags, T, FuncT, reflect&, ReturnT(*)(OtherT, ThisT)>::type                                             \
            operator_(typename type_traits::function<flags, T, FuncT, const std::string&, ReturnT(*)(OtherT, ThisT)>::type return_str              \
                , typename type_traits::function<flags, T, FuncT, const std::string&, ReturnT(*)(OtherT, ThisT)>::type other_str)                  \
            {                                                                                                                                      \
                ReturnT(*op_func)(const OtherT&, const ThisT&) = &opName; return operator_(op_func, return_str, other_str);                        \
            }                                                                                                                                      \
                                                                                                                                                   \
            template<class OtherT, class ThisT>                                                                                                    \
            reflect&                                                                                                                               \
            operator_(const std::string& other_str                                                                                                 \
                , ASDK_SFINAE_DEFAULT_FUNCTION_ARG((static_cast<OtherT>(*(OtherT*)(0)) opSym static_cast<ThisT>(*(ThisT*)(0)))))                   \
            {                                                                                                                                      \
                T(*op_func)(const OtherT&, const ThisT&) = &opName; return operator_<T, const OtherT&, const ThisT&>(op_func, name, other_str);    \
            }                                                                                                                                      \
                                                                                                                                                   \
            template<class OtherT, class ThisT>                                                                                                    \
            reflect&                                                                                                                               \
            operator opSym(                                                                                                                        \
                typename type_traits::conditional<                                                                                                 \
                  typename type_traits::conditional<const std::string&, type_traits::arg_type_ph, type_traits::is_same<ThisT, T>::value>::type     \
                , type_traits::arg_type_ph                                                                                                         \
                , sizeof((OtherT)(*((OtherT*)(42))) opSym (T)(*((T*)(42)))) != sizeof_Tx2>::type other_str)                                        \
            {                                                                                                                                      \
                return operator_<OtherT, ThisT>(other_str);                                                                                        \
            }
#           endif // BINARY_OPERATOR_DEF

#           if (defined(__GNUC__) && __GNUC__ < 8)
#           define ASDK_CONSTEXPR_BOOL_TMPL_ARG(expr) true
#           else
#           define ASDK_CONSTEXPR_BOOL_TMPL_ARG(expr) sizeof(expr) != sizeof_Tx2
#           endif
            
#           ifndef ASSIGNMENT_OPERATOR_DEF
#           define ASSIGNMENT_OPERATOR_DEF(operator_, opName, opSym)                                                                                   \
            template<class ReturnT, class OtherT, class FuncT>                                                                                         \
            typename type_traits::function<flags, T, FuncT, reflect&, ReturnT(*)(OtherT)>::type                                                        \
            operator_(FuncT func                                                                                                                       \
                , typename type_traits::function<flags, T, FuncT, const std::string&, ReturnT(*)(OtherT)>::type return_str                             \
                , typename type_traits::function<flags, T, FuncT, const std::string&, ReturnT(*)(OtherT)>::type other_str)                             \
            {                                                                                                                                          \
                const std::string op_str = return_str + " " ASDK_STRINGIFY(opName) "(" + format_function_argument<OtherT>(other_str) + ")";            \
                                                                                                                                                       \
                typedef type_traits::function<flags, T, FuncT, reflect&, ReturnT(*)(OtherT)> op_traits;                                                \
                typedef typename op_traits::class_type class_type;                                                                                     \
                typedef type_traits::func_ptr_converter<FuncT, class_type> func_ptr_convert;                                                           \
                const asECallConvTypes asCALL =                                                                                                        \
                    type_traits::is_same< class_type, void>::value ? (                                                                                 \
                        op_traits::is_compatible_with_cdecl_objfirst::value ? asCALL_CDECL_OBJFIRST :                                                  \
                        op_traits::is_compatible_with_cdecl_objlast::value ? asCALL_CDECL_OBJLAST :                                                    \
                    asCALL_CDECL)                                                                                                                      \
                    : (                                                                                                                                \
                    asCALL_THISCALL);                                                                                                                  \
                const AngelScript::asSFuncPtr asFunc = func_ptr_convert::call(func);                                                                   \
                asdk::expose(*asIScriptEngine, name, op_str, asFunc, asCALL);                                                                          \
                return *this;                                                                                                                          \
            }                                                                                                                                          \
                                                                                                                                                       \
            template<class OtherT, class FuncT>                                                                                                        \
            typename type_traits::function<flags, T, FuncT, reflect&, T(*)(OtherT)>::type                                                              \
            operator_(FuncT func                                                                                                                       \
                , typename type_traits::function<flags, T, FuncT, const std::string&, T(*)(OtherT)>::type other_str)                                   \
            {                                                                                                                                          \
                return operator_<T, OtherT, FuncT>(func, name + "&", other_str);                                                                       \
            }                                                                                                                                          \
                                                                                                                                                       \
            template<class FuncT>                                                                                                                      \
            typename type_traits::function<flags, T, FuncT, reflect&, T(*)(type_traits::arg_type_ph)>::type                                            \
            operator_(FuncT func                                                                                                                       \
                , typename type_traits::function<flags, T, FuncT, const std::string&, T(*)(type_traits::arg_type_ph)>::type other_str)                 \
            {                                                                                                                                          \
                return operator_<T, type_traits::arg_type_ph, FuncT>(func, name + "&", other_str);                                                     \
            }                                                                                                                                          \
                                                                                                                                                       \
            reflect&                                                                                                                                   \
            operator_()                                                                                                                                \
            {                                                                                                                                          \
                T&(*op_func)(T&, const T&) = &opName; return operator_(op_func, "const " + name + "&in");                                              \
            }                                                                                                                                          \
                                                                                                                                                       \
            template<class OtherT>                                                                                                                     \
            reflect&                                                                                                                                   \
            operator_(const std::string &other_str                                                                                                     \
                , ASDK_SFINAE_DEFAULT_FUNCTION_ARG( sizeof(static_cast<T>(*(T*)(0)) opSym static_cast<OtherT>(*(OtherT*)(0))) ))                       \
            {                                                                                                                                          \
                T&(*op_func)(T&, OtherT) = &opName; return operator_(op_func, other_str);                                                              \
            }                                                                                                                                          \
                                                                                                                                                       \
            reflect&                                                                                                                                   \
            operator opSym(int)                                                                                                                        \
            {                                                                                                                                          \
                return operator_();                                                                                                                    \
            }                                                                                                                                          \
                                                                                                                                                       \
            template<class OtherT>                                                                                                                     \
            reflect&                                                                                                                                   \
            operator opSym(                                                                                                                            \
                typename type_traits::conditional<const std::string&, type_traits::arg_type_ph                                                         \
                , ASDK_CONSTEXPR_BOOL_TMPL_ARG((T)(*((T*)(42))) opSym (OtherT)(*((OtherT*)(42))))>::type other_str)                                    \
            {                                                                                                                                          \
                return operator_<OtherT>(other_str);                                                                                                   \
            }
#           endif // ASSIGNMENT_OPERATOR_DEF

            // operator+
            BINARY_OPERATOR_DEF(operator_add, opAdd, +)

            // operator-
            BINARY_OPERATOR_DEF(operator_substract, opSub, -)
                
            // operator*
            BINARY_OPERATOR_DEF(operator_multiply, opMul, *)

            // operator/
            BINARY_OPERATOR_DEF(operator_divide, opDiv, /)

            // operator%
            BINARY_OPERATOR_DEF(operator_mod, opMod, %)

            // operator&
            BINARY_OPERATOR_DEF(operator_and, opAnd, &)

            // operator|
            BINARY_OPERATOR_DEF(operator_or, opOr, |)
                
            // operator+=
            ASSIGNMENT_OPERATOR_DEF(operator_add_assign, opAddAssign, +=)

            // operator-=
            ASSIGNMENT_OPERATOR_DEF(operator_substract_assign, opSubAssign, -=)

            // operator*=
            ASSIGNMENT_OPERATOR_DEF(operator_multiply_assign, opMulAssign, *=)

            // operator/=
            ASSIGNMENT_OPERATOR_DEF(operator_divide_assign, opDivAssign, /=)

            // operator%=
            ASSIGNMENT_OPERATOR_DEF(operator_mod_assign, opModAssign, %=)

            // operator&=
            ASSIGNMENT_OPERATOR_DEF(operator_and_assign, opAndAssign, &=)

            // operator|=
            ASSIGNMENT_OPERATOR_DEF(operator_or_assign, opOrAssign, |=)


#           undef BINARY_OPERATOR_DEF
#           undef ASSIGNMENT_OPERATOR_DEF

            
        protected:
            AngelScript::asIScriptEngine* asIScriptEngine;
            std::string name;
            std::vector<asdk::expose> entities;
            //void expose(const asdk::expose& entity) { entities.push_back(entity); }
            void init(const object_traits &object_traits)
            {
                using namespace AngelScript;

                asDWORD flags = ObjTypeT | ObjFlag1 | ObjFlag2 | ObjFlag3 | ObjFlag4 | ObjFlag5;
                const bool is_pod = (0 != (flags & asOBJ_POD));
                const bool is_enum = (0 != (flags & asOBJ_ENUM));
                const bool is_union = (0 != (flags & asOBJ_APP_CLASS_UNION));
                const bool is_template = (0 != (flags & asOBJ_TEMPLATE));
                const bool is_all_ints = (0 != (flags & asOBJ_APP_CLASS_ALLINTS));
                const bool is_all_floats = (0 != (flags & asOBJ_APP_CLASS_ALLFLOATS));
                const bool supports_handles = (0 != (flags & asOBJ_ASHANDLE));
                const bool supports_values = (0 != (flags & asOBJ_VALUE));
                const bool supports_GC = (0 != (flags & asOBJ_GC));

                if (object_traits.is.floating_point)
                    flags = asOBJ_APP_FLOAT;
                if (object_traits.is.primitive_type)
                    flags = asOBJ_APP_PRIMITIVE;

                if (object_traits.is.class_or_struct)
                {
                    if (object_traits.is.class_or_struct)
                        flags = asOBJ_APP_CLASS;

                    if (object_traits.has.default_constructor)
                        flags |= asOBJ_APP_CLASS_CONSTRUCTOR;
                    if (object_traits.has.custom_destructor)
                        flags |= asOBJ_APP_CLASS_DESTRUCTOR;
                    if (object_traits.has.custom_assigment_operator)
                        flags |= asOBJ_APP_CLASS_ASSIGNMENT;
                    if (object_traits.has.custom_copy_constructor)
                        flags |= asOBJ_APP_CLASS_COPY_CONSTRUCTOR;
                    if (is_all_ints)
                        flags |= asOBJ_APP_CLASS_ALLINTS;
                    if (is_all_floats)
                        flags |= asOBJ_APP_CLASS_ALLFLOATS;
                }
                else if (object_traits.is.ref)
                {
                    flags = asOBJ_REF;
                }

                if (object_traits.is.c_array)
                    flags = asOBJ_APP_ARRAY;

                if (is_pod) flags |= asOBJ_POD;
                if (is_enum) flags |= asOBJ_ENUM;
                if (is_template) flags |= asOBJ_TEMPLATE;

                if (supports_handles) flags |= asOBJ_ASHANDLE;
                if (supports_values) flags |= asOBJ_VALUE;
                if (supports_GC) flags |= asOBJ_GC;

                const AngelScript::asEObjTypeFlags::type all_flags32 =
                    AngelScript::asEObjTypeFlags::type(flags);

                if (is_union)//?????
                    asdk::expose(*asIScriptEngine, name, sizeof(T), all_flags32);
                else
                    asdk::expose(*asIScriptEngine, name, sizeof(T), all_flags32);
            }

            template<class FuncTraits, class ClassT, class FuncT>
            reflect&
            function_with_traits(const std::string& func_str, FuncT func) {
                typedef FuncTraits func_traits;
                typedef typename func_traits::obj_type obj_type;
                typedef ClassT class_type;
                typedef type_traits::func_ptr_converter<FuncT, class_type> func_ptr_convert;
                const asECallConvTypes asCALL = 
                    type_traits::is_same<class_type, void>::value ? (
                        func_traits::is_compatible_with_cdecl_objfirst::value ? asCALL_CDECL_OBJFIRST :
                        func_traits::is_compatible_with_cdecl_objlast::value ? asCALL_CDECL_OBJLAST :
                    asCALL_CDECL)
                    : (
                    asCALL_THISCALL);
                const AngelScript::asSFuncPtr asFunc = func_ptr_convert::call(func);
                asdk::expose(*asIScriptEngine, name, func_str, asFunc, asCALL);
                return *this;
            }

            template<class ThisT, class OtherT>
            inline static ThisT& opOrAssign(ThisT& lhs, OtherT rhs) // objfirst
            {
                return lhs |= rhs;
            }

            template<class ThisT, class OtherT>
            inline static T opOr(ThisT lhs, OtherT rhs) // objfirst
            {
                return lhs | rhs;
            }

            template<class ThisT, class OtherT>
            inline static ThisT& opAndAssign(ThisT& lhs, OtherT rhs) // objfirst
            {
                return lhs &= rhs;
            }

            template<class ThisT, class OtherT>
            inline static T opAnd(ThisT lhs, OtherT rhs) // objfirst
            {
                return lhs & rhs;
            }

            template<class ThisT, class OtherT>
            inline static ThisT& opModAssign(ThisT& lhs, OtherT rhs) // objfirst
            {
                return lhs %= rhs;
            }

            template<class ThisT, class OtherT>
            inline static T opMod(ThisT lhs, OtherT rhs) // objfirst
            {
                return lhs % rhs;
            }

            template<class ThisT, class OtherT>
            inline static ThisT& opDivAssign(ThisT& lhs, OtherT rhs) // objfirst
            {
                return lhs /= rhs;
            }

            template<class ThisT, class OtherT>
            inline static T opDiv(ThisT lhs, OtherT rhs) // objfirst
            {
                return lhs / rhs;
            }

            template<class ThisT, class OtherT>
            inline static ThisT& opMulAssign(ThisT& lhs, OtherT rhs) // objfirst
            {
                return lhs *= rhs;
            }

            template<class ThisT, class OtherT>
            inline static T opMul(ThisT lhs, OtherT rhs) // objfirst
            {
                return lhs * rhs;
            }

            template<class ThisT, class OtherT>
            inline static ThisT& opSubAssign(ThisT &lhs, OtherT rhs) // objfirst
            {
                return lhs -= rhs;
            }

            template<class ThisT, class OtherT>
            inline static T opSub(ThisT lhs, OtherT rhs) // objfirst
            {
                return lhs - rhs;
            }

            template<class ThisT, class OtherT>
            inline static ThisT& opAddAssign(ThisT &lhs, OtherT rhs) // objfirst
            {
                return lhs += rhs;
            }

            template<class ThisT, class OtherT>
            inline static T opAdd(ThisT lhs, OtherT rhs) // objfirst
            {
                return lhs + rhs;
            }

            template<class OtherT>
            inline static int opCmp(const T& lhs, OtherT rhs) // objfirst
            {
                if (lhs < rhs)
                    return -1;
                if (lhs > rhs)
                    return 1;
                return 0;
            }

            inline static int opCmp(const T& lhs, const T& rhs) // objfirst
            {
                if (std::less<T>()(lhs, rhs))
                    return -1;
                if (std::greater<T>()(lhs, rhs))
                    return 1;
                return 0;
            }


            template<class ReturnT, class IndexT>
            inline static ReturnT opIndex(const T& lhs, IndexT index) // objfirst
            {
                return lhs[index];
            }
            template<class ReturnT, class IndexT>
            inline static ReturnT opIndex(T& lhs, IndexT index) // objfirst
            {
                return lhs[index];
            }

            template<class OtherT>
            inline static bool opEquals(const T& lhs, OtherT rhs) // objfirst
            {
                return lhs == rhs;
            }

            inline static bool opEquals(const T& lhs, const T& rhs) // objfirst
            {
                return std::equal_to<T>()(lhs, rhs);
            }

            template<class ThisT, class OtherT>
            inline static T& opAssign(ThisT& lhs, const OtherT &rhs) // objfirst
            {
                return lhs = rhs;
            }

            inline static void dtor(T& that) // objfirst
            {
                that.~T();
            }

            inline static void default_ctor(T& that, asITypeInfo& ti) // objfirst
            {
                new (&that) T();
            }
            inline static void default_ctor(T& that) // objfirst
            {
                new (&that) T();
            }

            template<class Arg1T>
            static void ctor(T& that, asITypeInfo& ti, Arg1T arg1) // objfirst
            {
                new (&that) T(arg1);
            }
            template<class Arg1T>
            static void ctor(T& that, Arg1T arg1) // objfirst
            {
                new (&that) T(arg1);
            }

            template<class Arg1T, class Arg2T>
            static void ctor(T& that, asITypeInfo& ti, Arg1T arg1, Arg2T arg2) // objfirst
            {
                new (&that) T(arg1, arg2);
            }
            template<class Arg1T, class Arg2T>
            static void ctor(T& that, Arg1T arg1, Arg2T arg2) // objfirst
            {
                new (&that) T(arg1, arg2);
            }

            static object_traits T_object_traits(
                  bool has_default_constructor
                , bool has_custom_destructor
                , bool has_custom_assigment_operator
                , bool has_custom_copy_constructor
            ) {
                object_traits result;
                const asDWORD flags = ObjTypeT |ObjFlag1 | ObjFlag2 | ObjFlag3 | ObjFlag4 | ObjFlag5;

                result.has.default_constructor = has_default_constructor;
                result.has.custom_destructor = has_custom_destructor;
                result.has.custom_assigment_operator = has_custom_assigment_operator;
                result.has.custom_copy_constructor = has_custom_copy_constructor;

                result.is.handle = 0 != (flags & asOBJ_ASHANDLE);
                result.is.enum_class = 0 != (flags & asOBJ_ENUM);
                result.is.ref = 0 != (flags & asOBJ_REF);
                result.is.class_or_struct = !result.is.ref;
                result.is.c_array = false;
                result.is.floating_point = false;
                result.is.primitive_type = false;

                if (result.is.class_or_struct || result.is.ref)
                {
                    if (0 != (flags & asOBJ_APP_CLASS_CONSTRUCTOR)) result.has.default_constructor = true;
                    if (0 != (flags & asOBJ_APP_CLASS_DESTRUCTOR)) result.has.custom_destructor = true;
                    if (0 != (flags & asOBJ_APP_CLASS_ASSIGNMENT)) result.has.custom_assigment_operator = true;
                    if (0 != (flags & asOBJ_APP_CLASS_COPY_CONSTRUCTOR)) result.has.custom_copy_constructor = true;
                }

                return result;
            }

            template<class OtherT>
            static std::string format_function_argument(const std::string& other_str)
            {
                typedef type_traits::is_const<
                    typename type_traits::remove_reference<OtherT>::type
                > is_reference_to_const_or_const;
                std::string prefix, suffix;
                std::string::size_type pos;
                if (is_reference_to_const_or_const::value &&
                    (pos = other_str.find("const")) == std::string::npos)
                    prefix = "const ";
                if (type_traits::is_reference<OtherT>::value &&
                    (pos = other_str.find("&")) == std::string::npos)
                    suffix = " &";
                if (is_reference_to_const_or_const::value
                    && type_traits::is_reference<OtherT>::value
                    && (
                    (pos = other_str.find("in")) == std::string::npos
                        || (pos < other_str.length() - 2 && other_str[pos + 2] != ' ')
                    )
                    ) // if
                    suffix += " in";
                return prefix + other_str + suffix;
            }

        };



        template<class T
            , AngelScript::asEObjTypeFlags::type ObjFlag2
            , AngelScript::asEObjTypeFlags::type ObjFlag3
            , AngelScript::asEObjTypeFlags::type ObjFlag4
        >
        struct reflect<T, AngelScript::asEObjTypeFlags::asOBJ_TEMPLATE, ObjFlag2, ObjFlag3, ObjFlag4>
            : reflect<T, ObjFlag2, ObjFlag3, ObjFlag4, AngelScript::asEObjTypeFlags::asOBJ_TEMPLATE>
        {
            typedef reflect<T, ObjFlag2, ObjFlag3, ObjFlag4, AngelScript::asEObjTypeFlags::asOBJ_TEMPLATE> underlying_type;

            reflect(const std::string& name, AngelScript::asIScriptEngine& asIScriptEngine
                , const object_traits& object_traits) : underlying_type(name, asIScriptEngine, object_traits) {}

            reflect(AngelScript::asIScriptEngine& asIScriptEngine, const std::string& name
                , const object_traits& object_traits) : underlying_type(name, asIScriptEngine, object_traits) {}

            reflect(const std::string& name, AngelScript::asIScriptEngine& asIScriptEngine
                , bool has_default_constructor
                , bool has_custom_destructor
                , bool has_custom_assigment_operator
                , bool has_custom_copy_constructor
            ) : underlying_type(name, asIScriptEngine, has_default_constructor, has_custom_destructor, has_custom_assigment_operator, has_custom_copy_constructor) {}

            reflect(AngelScript::asIScriptEngine& asIScriptEngine, const std::string& name
                , bool has_default_constructor
                , bool has_custom_destructor
                , bool has_custom_assigment_operator
                , bool has_custom_copy_constructor
            ) : underlying_type(name, asIScriptEngine, has_default_constructor, has_custom_destructor, has_custom_assigment_operator, has_custom_copy_constructor) {}

            template<class FuncT> 
            typename type_traits::template_callback<FuncT, underlying_type&>::type
            template_callback(FuncT func) {

                const std::string tmpl_cb_str = "bool template_callback(int&in, bool&out)";

                typedef type_traits::template_callback<FuncT, underlying_type&> tmpl_cb_traits;
                typedef void class_type;
                typedef type_traits::func_ptr_converter<FuncT, class_type> func_ptr_convert;
                const asECallConvTypes asCALL =
                    asCALL_CDECL;
                const AngelScript::asSFuncPtr asFunc = func_ptr_convert::call(func);
                asdk::expose(*asIScriptEngine, name, tmpl_cb_str.c_str(), asBEHAVE_TEMPLATE_CALLBACK, asFunc, asCALL);
                return *this; 
            }

        private:
            using underlying_type::asIScriptEngine;
            using underlying_type::name;
            

        public:

            underlying_type&//typename type_traits::reflect_helper<T, underlying_type>::type
            template_callback() { 
                return template_callback(T::template_callback); 
            }


        };

        template<class T> struct reflect_template
            : reflect<T, AngelScript::asEObjTypeFlags::asOBJ_TEMPLATE>
        {
            typedef reflect<T, AngelScript::asEObjTypeFlags::asOBJ_TEMPLATE> underlying_type;

            reflect_template(const std::string& name, AngelScript::asIScriptEngine& asIScriptEngine
                , const object_traits& object_traits) : underlying_type(name, asIScriptEngine, object_traits) {}

            reflect_template(AngelScript::asIScriptEngine& asIScriptEngine, const std::string& name
                , const object_traits& object_traits) : underlying_type(name, asIScriptEngine, object_traits) {}

            reflect_template(const std::string& name, AngelScript::asIScriptEngine& asIScriptEngine
                , bool has_default_constructor
                , bool has_custom_destructor
                , bool has_custom_assigment_operator
                , bool has_custom_copy_constructor
            ) : underlying_type(name, asIScriptEngine, has_default_constructor, has_custom_destructor, has_custom_assigment_operator, has_custom_copy_constructor) {}

            reflect_template(AngelScript::asIScriptEngine& asIScriptEngine, const std::string& name
                , bool has_default_constructor
                , bool has_custom_destructor
                , bool has_custom_assigment_operator
                , bool has_custom_copy_constructor
            ) : underlying_type(name, asIScriptEngine, has_default_constructor, has_custom_destructor, has_custom_assigment_operator, has_custom_copy_constructor) {}
        };

    }

#   undef ASDK_SFINAE_DEFAULT_FUNCTION_ARG
#   undef ASDK_CONSTEXPR_BOOL_TMPL_ARG
}

namespace asdk {

    using namespace asdk::reflection;
    using namespace asdk::exposing;
    using namespace asdk::algorithm;
    namespace type_traits {
        using namespace asdk::reflection::type_traits;
        using namespace asdk::algorithm::type_traits;
    }
}

#undef ASDK_ARG
#undef ASDK_WRAP
#undef ASDK_CAT3
#undef ASDK_CAT2
#undef ASDK_CAT
#undef ASDK_STRINGIFY

#endif // ANGELSCRIPT_SOFTWARE_DEVELOPMENT_KIT_HPP

#ifndef ANGELSCRIPT_SOFTWARE_DEVELOPMENT_KIT_HPP
#define ANGELSCRIPT_SOFTWARE_DEVELOPMENT_KIT_HPP

#define ASDK_WRAP(a) a

#ifndef ASDK_ANGELSCRIPT_DIRECTORY
#   define ASDK_ANGELSCRIPT_DIRECTORY angelscript/sdk/angelscript/
#endif

#ifndef ASDK_ANGELSCRIPT_LIB_H_PATH
#   define ASDK_ANGELSCRIPT_LIB_H_PATH <ASDK_WRAP(ASDK_ANGELSCRIPT_DIRECTORY)include/angelscript.h>
#endif

#include ASDK_ANGELSCRIPT_LIB_H_PATH

#ifdef AS_NAMESPACE_QUALIFIER
#   ifndef ASDK_ANGELSCRIPT_NS_QUALIFIER
#       define ASDK_ANGELSCRIPT_NS_QUALIFIER AS_NAMESPACE_QUALIFIER
#   endif // ASDK_ANGELSCRIPT_NS_QUALIFIER
#else // ndef AS_NAMESPACE_QUALIFIER
#   ifndef ASDK_ANGELSCRIPT_NS_QUALIFIER
#       define ASDK_ANGELSCRIPT_NS_QUALIFIER AngelScript::
#   endif // ASDK_ANGELSCRIPT_NS_QUALIFIER
#endif // AS_NAMESPACE_QUALIFIER

// AngelScript functions, types etc.
namespace asdk {
    namespace AngelScript {
        using ASDK_ANGELSCRIPT_NS_QUALIFIER asSMessageInfo;
        using ASDK_ANGELSCRIPT_NS_QUALIFIER asDWORD;
        using ASDK_ANGELSCRIPT_NS_QUALIFIER asIScriptEngine;
        using ASDK_ANGELSCRIPT_NS_QUALIFIER asIScriptContext;
        using ASDK_ANGELSCRIPT_NS_QUALIFIER asSFuncPtr;
        using ASDK_ANGELSCRIPT_NS_QUALIFIER asITypeInfo;
        using ASDK_ANGELSCRIPT_NS_QUALIFIER asUINT;
        using ASDK_ANGELSCRIPT_NS_QUALIFIER asIScriptFunction;

        using ASDK_ANGELSCRIPT_NS_QUALIFIER asCreateScriptEngine;

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
    }

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
}

#include <string>

// AngelScript SDK Reflection
namespace asdk {

    namespace reflection {

        template<AngelScript::asEObjTypeFlags::type>
        struct reflect;

        // template_callback
        namespace type_traits {
            template<class FuncT, class ReflectionT>
            struct template_callback;

            template<class ReflectionT>
            struct template_callback<bool(*)(asITypeInfo&, bool&), ReflectionT> {
                typedef ReflectionT type;
                typedef void arg0_type;
            };
            template<class ReflectionT> struct template_callback<bool(*)(asITypeInfo&, bool&), ReflectionT> : template_callback<bool(*)(asITypeInfo&, bool&), ReflectionT> {};
            template<class ReflectionT> struct template_callback<bool(*)(asITypeInfo&, bool*), ReflectionT> : template_callback<bool(*)(asITypeInfo&, bool&), ReflectionT> {};
            template<class ReflectionT> struct template_callback<bool(*)(asITypeInfo*, bool*), ReflectionT> : template_callback<bool(*)(asITypeInfo&, bool&), ReflectionT> {};
            template<class T, class ReflectionT>
            struct template_callback<bool(T::*)(asITypeInfo&, bool&), ReflectionT> {
                typedef ReflectionT type;
                typedef T* arg0_type;
            };
            template<class T, class ReflectionT> struct template_callback<bool(T::*)(asITypeInfo&, bool&), ReflectionT> : template_callback<bool(T::*)(asITypeInfo&, bool&), ReflectionT> {};
            template<class T, class ReflectionT> struct template_callback<bool(T::*)(asITypeInfo&, bool*), ReflectionT> : template_callback<bool(T::*)(asITypeInfo&, bool&), ReflectionT> {};
            template<class T, class ReflectionT> struct template_callback<bool(T::*)(asITypeInfo*, bool*), ReflectionT> : template_callback<bool(T::*)(asITypeInfo&, bool&), ReflectionT> {};
            template<class T, class ReflectionT>
            struct template_callback<bool(T::*)(asITypeInfo&, bool&) const, ReflectionT> {
                typedef ReflectionT type;
                typedef const T* arg0_type;
            };
            template<class T, class ReflectionT> struct template_callback<bool(T::*)(asITypeInfo&, bool&) const, ReflectionT> : template_callback<bool(T::*)(asITypeInfo&, bool&) const, ReflectionT> {};
            template<class T, class ReflectionT> struct template_callback<bool(T::*)(asITypeInfo&, bool*) const, ReflectionT> : template_callback<bool(T::*)(asITypeInfo&, bool&) const, ReflectionT> {};
            template<class T, class ReflectionT> struct template_callback<bool(T::*)(asITypeInfo*, bool*) const, ReflectionT> : template_callback<bool(T::*)(asITypeInfo&, bool&) const, ReflectionT> {};
            template<class T, class ReflectionT>
            struct template_callback<bool(*)(T*, asITypeInfo&, bool&), ReflectionT> {
                typedef ReflectionT type;
                typedef T* arg0_type;
            };
            template<class T, class ReflectionT> struct template_callback<bool(*)(T*, asITypeInfo&, bool&), ReflectionT> : template_callback<bool(*)(T*, asITypeInfo&, bool&), ReflectionT> {};
            template<class T, class ReflectionT> struct template_callback<bool(*)(T*, asITypeInfo&, bool*), ReflectionT> : template_callback<bool(*)(T*, asITypeInfo&, bool&), ReflectionT> {};
            template<class T, class ReflectionT> struct template_callback<bool(*)(T*, asITypeInfo*, bool*), ReflectionT> : template_callback<bool(*)(T*, asITypeInfo&, bool&), ReflectionT> {};
            template<class T, class ReflectionT>
            struct template_callback<bool(*)(asITypeInfo&, bool&, T*), ReflectionT> {
                typedef ReflectionT type;
                typedef T* arg0_type;
            };
            template<class T, class ReflectionT> struct template_callback<bool(*)(asITypeInfo&, bool&, T*), ReflectionT> : template_callback<bool(*)(asITypeInfo&, bool&, T*), ReflectionT> {};
            template<class T, class ReflectionT> struct template_callback<bool(*)(asITypeInfo&, bool*, T*), ReflectionT> : template_callback<bool(*)(asITypeInfo&, bool&, T*), ReflectionT> {};
            template<class T, class ReflectionT> struct template_callback<bool(*)(asITypeInfo*, bool*, T*), ReflectionT> : template_callback<bool(*)(asITypeInfo&, bool&, T*), ReflectionT> {};
        }


        // constructor
        namespace type_traits {
            template<class FuncT, class ReflectionT>
            struct constructor;

            template<class ClassT, class ReflectionT>
            struct constructor<void(*)(asITypeInfo&, ClassT&), ReflectionT> {
                typedef ReflectionT type;
                typedef void arg0_type;
            };
            template<class ClassT, class ReflectionT> struct constructor<void(*)(asITypeInfo&, ClassT&), ReflectionT> : constructor<void(*)(asITypeInfo&, ClassT&), ReflectionT> {};
            template<class ClassT, class ReflectionT> struct constructor<void(*)(asITypeInfo&, ClassT*), ReflectionT> : constructor<void(*)(asITypeInfo&, ClassT&), ReflectionT> {};
            template<class ClassT, class ReflectionT> struct constructor<void(*)(asITypeInfo*, ClassT*), ReflectionT> : constructor<void(*)(asITypeInfo&, ClassT&), ReflectionT> {};
            template<class ClassT, class T, class ReflectionT>
            struct constructor<void(T::*)(asITypeInfo&, ClassT&), ReflectionT> {
                typedef ReflectionT type;
                typedef T* arg0_type;
            };
            template<class ClassT, class T, class ReflectionT> struct constructor<void(T::*)(asITypeInfo&, ClassT&), ReflectionT> : constructor<void(T::*)(asITypeInfo&, ClassT&), ReflectionT> {};
            template<class ClassT, class T, class ReflectionT> struct constructor<void(T::*)(asITypeInfo&, ClassT*), ReflectionT> : constructor<void(T::*)(asITypeInfo&, ClassT&), ReflectionT> {};
            template<class ClassT, class T, class ReflectionT> struct constructor<void(T::*)(asITypeInfo*, ClassT*), ReflectionT> : constructor<void(T::*)(asITypeInfo&, ClassT&), ReflectionT> {};
            template<class ClassT, class T, class ReflectionT>
            struct constructor<void(T::*)(asITypeInfo&, ClassT&) const, ReflectionT> {
                typedef ReflectionT type;
                typedef const T* arg0_type;
            };
            template<class ClassT, class T, class ReflectionT> struct constructor<void(T::*)(asITypeInfo&, ClassT&) const, ReflectionT> : constructor<void(T::*)(asITypeInfo&, ClassT&) const, ReflectionT> {};
            template<class ClassT, class T, class ReflectionT> struct constructor<void(T::*)(asITypeInfo&, ClassT*) const, ReflectionT> : constructor<void(T::*)(asITypeInfo&, ClassT&) const, ReflectionT> {};
            template<class ClassT, class T, class ReflectionT> struct constructor<void(T::*)(asITypeInfo*, ClassT*) const, ReflectionT> : constructor<void(T::*)(asITypeInfo&, ClassT&) const, ReflectionT> {};
            template<class ClassT, class T, class ReflectionT>
            struct constructor<void(*)(T*, asITypeInfo&, ClassT&), ReflectionT> {
                typedef ReflectionT type;
                typedef T* arg0_type;
            };
            template<class ClassT, class T, class ReflectionT> struct constructor<void(*)(T*, asITypeInfo&, ClassT&), ReflectionT> : constructor<void(*)(T*, asITypeInfo&, ClassT&), ReflectionT> {};
            template<class ClassT, class T, class ReflectionT> struct constructor<void(*)(T*, asITypeInfo&, ClassT*), ReflectionT> : constructor<void(*)(T*, asITypeInfo&, ClassT&), ReflectionT> {};
            template<class ClassT, class T, class ReflectionT> struct constructor<void(*)(T*, asITypeInfo*, ClassT*), ReflectionT> : constructor<void(*)(T*, asITypeInfo&, ClassT&), ReflectionT> {};
            template<class ClassT, class T, class ReflectionT>
            struct constructor<void(*)(asITypeInfo&, ClassT&, T*), ReflectionT> {
                typedef ReflectionT type;
                typedef T* arg0_type;
            };
            template<class ClassT, class T, class ReflectionT> struct constructor<void(*)(asITypeInfo&, ClassT&, T*), ReflectionT> : constructor<void(*)(asITypeInfo&, ClassT&, T*), ReflectionT> {};
            template<class ClassT, class T, class ReflectionT> struct constructor<void(*)(asITypeInfo&, ClassT*, T*), ReflectionT> : constructor<void(*)(asITypeInfo&, ClassT&, T*), ReflectionT> {};
            template<class ClassT, class T, class ReflectionT> struct constructor<void(*)(asITypeInfo*, ClassT*, T*), ReflectionT> : constructor<void(*)(asITypeInfo&, ClassT&, T*), ReflectionT> {};
        }

        template<>
        struct reflect<AngelScript::asEObjTypeFlags::asOBJ_TEMPLATE>
        {
            typedef AngelScript::asITypeInfo asITypeInfo;
            reflect(const std::string& name) {}
            
            template<class FuncT> 
            typename type_traits::template_callback<FuncT, reflect>::type
            template_callback(FuncT func) {}
            template<class FuncT> 
            typename type_traits::template_callback<FuncT, reflect>::type
            template_callback(FuncT func, type_traits::template_callback<FuncT, reflect>::arg0_type obj) {}
            
            template<class FuncT> 
            typename type_traits::constructor<FuncT, reflect>::type
            constructor(FuncT func) {}
            template<class FuncT> 
            typename type_traits::template_callback<FuncT, reflect>::type
            constructor(FuncT func, type_traits::constructor<FuncT, reflect>::arg0_type obj) {}

            
        };
        typedef reflect<AngelScript::asEObjTypeFlags::asOBJ_TEMPLATE> reflect_template;

    }
}

namespace asdk {

    using namespace asdk::reflection;
}

#endif // ANGELSCRIPT_SOFTWARE_DEVELOPMENT_KIT_HPP

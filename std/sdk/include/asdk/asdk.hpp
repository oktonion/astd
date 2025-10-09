#ifndef ANGELSCRIPT_SOFTWARE_DEVELOPMENT_KIT_HPP
#define ANGELSCRIPT_SOFTWARE_DEVELOPMENT_KIT_HPP

#define ASDK_WRAP(a) a
#define ASDK_CAT3(a,b) a##b
#define ASDK_CAT2(a,b) ASDK_CAT3(a,b)
#define ASDK_CAT(a,b) ASDK_CAT2(a,b)

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

        namespace type_traits
        {
            template<class T1, class T2>
            struct is_same { static const bool value = false; };
            template<class T>
            struct is_same<T,T> { static const bool value = true; };

            template<class IfTrueT, class IfFalseT, bool>
            struct conditional {  typedef IfTrueT type; };
            template<class IfTrueT, class IfFalseT>
            struct conditional<IfTrueT, IfFalseT, false> { typedef IfFalseT type; };


#           ifndef ASDK_FUNCTION_ARGS_TYPES
#           define ASDK_FUNCTION_ARGS_TYPES1  class Arg0T ASDK_PARAM 
#           define ASDK_FUNCTION_ARGS_LIST1         Arg0T
#           define ASDK_FUNCTION_ARGS_TYPES2  class Arg0T ASDK_PARAM , class Arg1T ASDK_PARAM 
#           define ASDK_FUNCTION_ARGS_LIST2         Arg0T            ,       Arg1T
#           define ASDK_FUNCTION_ARGS_TYPES3  class Arg0T ASDK_PARAM , class Arg1T ASDK_PARAM , class Arg2T ASDK_PARAM 
#           define ASDK_FUNCTION_ARGS_LIST3         Arg0T            ,       Arg1T            ,       Arg2T
#           define ASDK_FUNCTION_ARGS_TYPES4  class Arg0T ASDK_PARAM , class Arg1T ASDK_PARAM , class Arg2T ASDK_PARAM , class Arg3T ASDK_PARAM 
#           define ASDK_FUNCTION_ARGS_LIST4         Arg0T            ,       Arg1T            ,       Arg2T            ,       Arg3T
#           define ASDK_FUNCTION_ARGS_TYPES5  class Arg0T ASDK_PARAM , class Arg1T ASDK_PARAM , class Arg2T ASDK_PARAM , class Arg3T ASDK_PARAM , class Arg4T ASDK_PARAM 
#           define ASDK_FUNCTION_ARGS_LIST5         Arg0T            ,       Arg1T            ,       Arg2T            ,       Arg3T            ,       Arg4T
#           define ASDK_FUNCTION_ARGS_TYPES6  class Arg0T ASDK_PARAM , class Arg1T ASDK_PARAM , class Arg2T ASDK_PARAM , class Arg3T ASDK_PARAM , class Arg4T ASDK_PARAM , class Arg5T ASDK_PARAM 
#           define ASDK_FUNCTION_ARGS_LIST6         Arg0T            ,       Arg1T            ,       Arg2T            ,       Arg3T            ,       Arg4T            ,       Arg5T
#           define ASDK_FUNCTION_ARGS_TYPES7  class Arg0T ASDK_PARAM , class Arg1T ASDK_PARAM , class Arg2T ASDK_PARAM , class Arg3T ASDK_PARAM , class Arg4T ASDK_PARAM , class Arg5T ASDK_PARAM , class Arg6T ASDK_PARAM 
#           define ASDK_FUNCTION_ARGS_LIST7         Arg0T            ,       Arg1T            ,       Arg2T            ,       Arg3T            ,       Arg4T            ,       Arg5T            ,       Arg6T
#           define ASDK_FUNCTION_ARGS_TYPES8  class Arg0T ASDK_PARAM , class Arg1T ASDK_PARAM , class Arg2T ASDK_PARAM , class Arg3T ASDK_PARAM , class Arg4T ASDK_PARAM , class Arg5T ASDK_PARAM , class Arg6T ASDK_PARAM , class Arg7T ASDK_PARAM 
#           define ASDK_FUNCTION_ARGS_LIST8         Arg0T            ,       Arg1T            ,       Arg2T            ,       Arg3T            ,       Arg4T            ,       Arg5T            ,       Arg6T            ,       Arg7T
#           define ASDK_FUNCTION_ARGS_TYPES9  class Arg0T ASDK_PARAM , class Arg1T ASDK_PARAM , class Arg2T ASDK_PARAM , class Arg3T ASDK_PARAM , class Arg4T ASDK_PARAM , class Arg5T ASDK_PARAM , class Arg6T ASDK_PARAM , class Arg7T ASDK_PARAM , class Arg8T ASDK_PARAM 
#           define ASDK_FUNCTION_ARGS_LIST9         Arg0T            ,       Arg1T            ,       Arg2T            ,       Arg3T            ,       Arg4T            ,       Arg5T            ,       Arg6T            ,       Arg7T            ,       Arg8T
#           define ASDK_FUNCTION_ARGS_TYPES10 class Arg0T ASDK_PARAM , class Arg1T ASDK_PARAM , class Arg2T ASDK_PARAM , class Arg3T ASDK_PARAM , class Arg4T ASDK_PARAM , class Arg5T ASDK_PARAM , class Arg6T ASDK_PARAM , class Arg7T ASDK_PARAM , class Arg8T ASDK_PARAM , class Arg9T ASDK_PARAM 
#           define ASDK_FUNCTION_ARGS_LIST10        Arg0T            ,       Arg1T            ,       Arg2T            ,       Arg3T            ,       Arg4T            ,       Arg5T            ,       Arg6T            ,       Arg7T            ,       Arg8T            ,       Arg9T

#           define ASDK_FUNCTION_ARGS_TYPES(N) ASDK_CAT(ASDK_FUNCTION_ARGS_TYPES, ASDK_WRAP(N))
#           define ASDK_FUNCTION_ARGS_LIST(N) ASDK_CAT(ASDK_FUNCTION_ARGS_LIST, ASDK_WRAP(N))
#           define ASDK_PARAM
#           endif // ASDK_FUNCTION_ARGS_TYPES



            template<class ReturnT
                , class Arg0T = void, class Arg1T = void, class Arg2T = void, class Arg3T = void, class Arg4T = void
                , class Arg5T = void, class Arg6T = void, class Arg7T = void, class Arg8T = void, class Arg9T = void
            >
            struct function_traits_storage {
                typedef ReturnT return_type;
                typedef Arg0T arg0_type; typedef Arg1T arg1_type; typedef Arg2T arg2_type; typedef Arg3T arg3_type; typedef Arg4T arg4_type;
                typedef Arg5T arg5_type; typedef Arg6T arg6_type; typedef Arg7T arg7_type; typedef Arg8T arg8_type; typedef Arg9T arg9_type;
            };

            template<class FunctionTraitsStorage>
            struct arg_last { typedef void type; };

            template<
                  class Arg0T , class Arg1T , class Arg2T , class Arg3T , class Arg4T 
                , class Arg5T , class Arg6T , class Arg7T , class Arg8T , class Arg9T 
            >
            struct arg_last<
                function_traits_storage<
                      Arg0T, Arg1T, Arg2T, Arg3T, Arg4T
                    , Arg5T, Arg6T, Arg7T, Arg8T, Arg9T
                >
            > 
            { typedef Arg9T type; };

            template<class FuncT>
            struct function_traits : function_traits_storage<void> {};

            template<class ReturnT>
            struct function_traits<ReturnT(*)()> : function_traits_storage<ReturnT>{};
            template<class ClassT, class ReturnT>
            struct function_traits<ReturnT(ClassT::*)()> : function_traits_storage<ReturnT> {};
            template<class ClassT, class ReturnT>
            struct function_traits<ReturnT(ClassT::*)() const> : function_traits_storage<ReturnT> {};
#           ifndef ASDK_FUNCTION_TRAITS

#           define ASDK_FUNCTION_TRAITS                                                                    \
            template<class ReturnT, ASDK_FUNCTION_ARGS_TYPES(ASDK_FUNCTION_ARGS_N)>                        \
            struct function_traits<ReturnT(*)(ASDK_FUNCTION_ARGS_LIST(ASDK_FUNCTION_ARGS_N))>              \
            : function_traits_storage<ReturnT, ASDK_FUNCTION_ARGS_LIST(ASDK_FUNCTION_ARGS_N)> {};          \
            template<class ClassT, class ReturnT, ASDK_FUNCTION_ARGS_TYPES(ASDK_FUNCTION_ARGS_N)>          \
            struct function_traits<ReturnT(ClassT::*)(ASDK_FUNCTION_ARGS_LIST(ASDK_FUNCTION_ARGS_N))>      \
                : function_traits_storage<ReturnT, ASDK_FUNCTION_ARGS_LIST(ASDK_FUNCTION_ARGS_N)> {};      \
            template<class ClassT, class ReturnT, ASDK_FUNCTION_ARGS_TYPES(ASDK_FUNCTION_ARGS_N)>          \
            struct function_traits<ReturnT(ClassT::*)(ASDK_FUNCTION_ARGS_LIST(ASDK_FUNCTION_ARGS_N)) const>\
                : function_traits_storage<ReturnT, ASDK_FUNCTION_ARGS_LIST(ASDK_FUNCTION_ARGS_N)> {};     

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

            template<bool 
                , bool, bool, bool, bool, bool
                , bool, bool, bool, bool, bool
            > struct is_all_same : is_same<void, int> {};
            template<> struct is_all_same<true
                , true, true, true, true, true
                , true, true, true, true, true
            >: is_same<void, void> {};

            template<class Func1T, class Func2T, bool>
            struct is_compatible_function_impl { typedef is_same<Func1T, Func2T> is_same_type; };
            template<class Func1T, class Func2T>
            struct is_compatible_function_impl<Func1T, Func2T, false> {
                typedef function_traits<Func1T> func1_traits;
                typedef function_traits<Func2T> func2_traits;
                typedef is_all_same < is_same<typename func1_traits::return_type, typename func2_traits::return_type>::value == bool(true)
#                   define ASDK_IS(N) is_same<typename func1_traits::arg##N##_type, typename func2_traits::arg##N##_type>::value == bool(true)
                    , ASDK_IS(0), ASDK_IS(1), ASDK_IS(2), ASDK_IS(3), ASDK_IS(4)
                    , ASDK_IS(5), ASDK_IS(6), ASDK_IS(7), ASDK_IS(8), ASDK_IS(9)
#                   undef ASDK_IS
                > is_same_type;
            };

            template<class Func1T, class Func2T>
            struct is_compatible_function : 
                is_compatible_function_impl<Func1T, Func2T, is_same<Func1T, Func2T>::value == bool(true)>::is_same_type {};
        }

        // template_callback
        namespace type_traits {
            template<class FuncT, class ReflectionT>
            struct template_callback {
                typedef is_compatible_function<FuncT, bool(*)(asITypeInfo&, bool&)> is_compatible_with1;
                typedef is_compatible_function<FuncT, bool(*)(asITypeInfo&, bool*)> is_compatible_with2;
                typedef is_compatible_function<FuncT, bool(*)(asITypeInfo&, bool*)> is_compatible_with3;
                typedef is_compatible_function<FuncT, bool(*)(asITypeInfo*, bool*)> is_compatible_with4;
                typedef 
                typename
                conditional<ReflectionT, void,
                    is_compatible_with1::value == bool(true) ||
                    is_compatible_with2::value == bool(true) ||
                    is_compatible_with3::value == bool(true) ||
                    is_compatible_with4::value == bool(true)
                >::type type;
            };
        }


        // constructor
        namespace type_traits {
            template<class FuncT, class ReflectionT>
            struct constructor{
                typedef function_traits<FuncT> func_traits_type;
                typedef typename func_traits_type::arg0_type arg0_type;
                typedef typename func_traits_type::argN_type argN_type;
                typedef is_compatible_function<FuncT, bool(*)(asITypeInfo&, bool&)> is_compatible_with1;
                typedef is_compatible_function<FuncT, bool(*)(asITypeInfo&, bool*)> is_compatible_with2;
                typedef is_compatible_function<FuncT, bool(*)(asITypeInfo&, bool*)> is_compatible_with3;
                typedef is_compatible_function<FuncT, bool(*)(asITypeInfo*, bool*)> is_compatible_with4;
                typedef 
                typename
                conditional<ReflectionT, void,
                    is_compatible_with1::value == bool(true) ||
                    is_compatible_with2::value == bool(true) ||
                    is_compatible_with3::value == bool(true) ||
                    is_compatible_with4::value == bool(true)
                >::type type;
            };

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

#undef ASDK_WRAP
#undef ASDK_CAT3
#undef ASDK_CAT2
#undef ASDK_CAT

#endif // ANGELSCRIPT_SOFTWARE_DEVELOPMENT_KIT_HPP

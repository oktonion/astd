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
            
            expose(asIScriptEngine& engine, const std::string& decl, asSFuncPtr func, asECallConvTypes callConv)
                : engine(&engine), obj()   , objSize()       , decl(decl), func(func), callConv(callConv), flags(-1) {}
            expose(asIScriptEngine& engine, const std::string& obj, const std::string& decl, asSFuncPtr func, asECallConvTypes callConv)
                : engine(&engine), obj(obj), objSize()       , decl(decl), func(func), callConv(callConv), flags(-1) {}
            expose(asIScriptEngine& engine, const std::string& obj, int objSize, asEObjTypeFlags flags)
                : engine(&engine), obj(obj), objSize(objSize), decl()    , func(func), callConv()        , flags(flags) {
                if (0 == (expose::flags & asOBJ_APP_CLASS)) expose::flags |= asOBJ_APP_CLASS;
                if (0 == (expose::flags & asOBJ_VALUE) && 0 == (expose::flags & asOBJ_REF)) expose::flags |= asOBJ_VALUE;
            }
            expose(asIScriptEngine& engine, const std::string& obj, const std::string& decl, asEBehaviours beh, asSFuncPtr func, asECallConvTypes callConv)
                : engine(&engine), obj(obj), objSize()       , decl(decl), func(func), callConv(callConv), flags(beh) {}

            expose(const expose& other)
                : engine(other.engine), obj(other.obj), objSize(other.objSize), decl(other.decl), func(other.func), callConv(other.callConv), flags(other.flags)
            {
                other.engine = 0;
            }

            ~expose() {
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

                        if (0 != (flags & asOBJ_APP_CLASS))
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
            typedef is_same<void, void> true_type;
            typedef is_same<void, float> false_type;

            template<class IfTrueT, class IfFalseT, bool>
            struct conditional {  typedef IfTrueT type; };
            template<class IfTrueT, class IfFalseT>
            struct conditional<IfTrueT, IfFalseT, false> { typedef IfFalseT type; };

            template<class T>
            T declval();


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
            struct function_traits : function_traits_storage<void> {};
            template<ASDK_FUNCTION_ARGS_TYPES(10)>
            struct function_traits<
                function_traits_storage<ASDK_FUNCTION_ARGS_LIST(10)>
            > : function_traits_storage<ASDK_FUNCTION_ARGS_LIST(10)> {};

            template<class ReturnT>
            struct function_traits<ReturnT(*)()> : function_traits_storage<void, ReturnT>{};
            template<class ClassT, class ReturnT>
            struct function_traits<ReturnT(ClassT::*)()> : function_traits_storage<ClassT, ReturnT> {};
            template<class ClassT, class ReturnT>
            struct function_traits<ReturnT(ClassT::*)() const> : function_traits_storage<ClassT, ReturnT> {};
#           ifndef ASDK_FUNCTION_TRAITS

#           define ASDK_FUNCTION_TRAITS                                                                           \
            template<class ReturnT, ASDK_FUNCTION_ARGS_TYPES(ASDK_FUNCTION_ARGS_N)>                               \
            struct function_traits<ReturnT(*)(ASDK_FUNCTION_ARGS_LIST(ASDK_FUNCTION_ARGS_N))>                     \
            : function_traits_storage<void, ReturnT, ASDK_FUNCTION_ARGS_LIST(ASDK_FUNCTION_ARGS_N)> {};           \
            template<class ClassT, class ReturnT, ASDK_FUNCTION_ARGS_TYPES(ASDK_FUNCTION_ARGS_N)>                 \
            struct function_traits<ReturnT(ClassT::*)(ASDK_FUNCTION_ARGS_LIST(ASDK_FUNCTION_ARGS_N))>             \
                : function_traits_storage<ClassT, ReturnT, ASDK_FUNCTION_ARGS_LIST(ASDK_FUNCTION_ARGS_N)> {};     \
            template<class ClassT, class ReturnT, ASDK_FUNCTION_ARGS_TYPES(ASDK_FUNCTION_ARGS_N)>                 \
            struct function_traits<ReturnT(ClassT::*)(ASDK_FUNCTION_ARGS_LIST(ASDK_FUNCTION_ARGS_N)) const>       \
                : function_traits_storage<const ClassT, ReturnT, ASDK_FUNCTION_ARGS_LIST(ASDK_FUNCTION_ARGS_N)> {};     

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
            template<AngelScript::asEObjTypeFlags::type ObjType, class ClassT, class FuncT, class ReflectionT
                , class DeclT = void(*)(arg_type_ph, arg_type_ph, arg_type_ph, arg_type_ph, arg_type_ph)>
            struct constructor {
                typedef function_traits<DeclT> decl_traits_type;
                typedef typename decl_traits_type::storage decl_traits_storage;


                enum { isTemplate = (ObjType & AngelScript::asEObjTypeFlags::asOBJ_TEMPLATE) ? 1 : 0 };

                typedef 
                typename
                conditional<
                    function_traits_storage<void, void>,
                    function_traits_storage<void, void, asITypeInfo&>,
                    isTemplate == 0
                >::type ti_reference_storage;
                typedef 
                typename
                conditional<
                    function_traits_storage<void, void>,
                    function_traits_storage<void, void, asITypeInfo*>,
                    isTemplate == 0
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
                        true_type, false_type,
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
                        ti_decl_pointer_storage,
                        decl_traits_storage
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
                        true_type, false_type,
                           is_compatible_with1::value == bool(true)
                        || is_compatible_with2::value == bool(true)
                        || is_compatible_with3::value == bool(true)
                        || is_compatible_with4::value == bool(true)
                    >::type is_compatible_with;
                }; 
                typedef typename cdecl_objfirst::is_compatible_with is_compatible_with_cdecl_objfirst;

                typedef 
                typename
                conditional<ReflectionT, arg_type_ph,
                    is_compatible_with_cdecl_objlast::value == bool(true) ||
                    is_compatible_with_cdecl_objfirst::value == bool(true)
                >::type type;

                typedef function_traits<FuncT> func_traits_type;
                typedef typename func_traits_type::class_type class_type;
                typedef typename func_traits_type::arg1_type arg1_type;
                typedef typename arg_last<func_traits_type>::type argN_type;

            };
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

            template<AngelScript::asEObjTypeFlags::type, class ClassT, class FuncT, class ReflectionT
                , class DeclT = arg_type_ph(*)(arg_type_ph, arg_type_ph, arg_type_ph, arg_type_ph, arg_type_ph)>
            struct function {

                typedef function_traits<DeclT> decl_traits_type;
                typedef typename decl_traits_type::storage decl_traits_storage;

                typedef function_traits<FuncT> func_traits_type;
                typedef typename func_traits_type::return_type return_type;
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
                conditional<class_type, thiscall_obj_type,
                    is_compatible_with_thiscall::value == bool(true)
                >::type obj_type;

            };
        }
        
        template<class T, AngelScript::asEObjTypeFlags::type ObjType>
        struct reflect
        {
            typedef AngelScript::asITypeInfo asITypeInfo;
            typedef AngelScript::asECallConvTypes::type asECallConvTypes;
            enum { isTemplate = (ObjType & AngelScript::asEObjTypeFlags::asOBJ_TEMPLATE) ? 1 : 0 };

            reflect(const std::string& name, AngelScript::asIScriptEngine &asIScriptEngine) : asIScriptEngine(&asIScriptEngine), name(name) {
                init();
            }
            reflect(AngelScript::asIScriptEngine& asIScriptEngine, const std::string& name) : asIScriptEngine(&asIScriptEngine), name(name) {
                init();
            }
            template<class FuncT>
            typename type_traits::constructor<ObjType, T, FuncT, reflect&, void(*)()>::type
            constructor(FuncT func) {
                const char* ctor_cstr = isTemplate != 0 ? "void ctor(int&in)" : "void ctor()";

                typedef type_traits::constructor<ObjType, T, FuncT, reflect&, void(*)()> ctor_traits;
                typedef typename ctor_traits::class_type class_type;
                typedef type_traits::func_ptr_converter<FuncT, class_type> func_ptr_convert;
                const asECallConvTypes asCALL =
                    type_traits::is_same< class_type, void>::value ? (
                        ctor_traits::is_compatible_with_cdecl_objfirst::value ? asCALL_CDECL_OBJFIRST :
                        ctor_traits::is_compatible_with_cdecl_objlast::value ? asCALL_CDECL_OBJLAST :
                    asCALL_CDECL)
                    : (
                    asCALL_THISCALL);
                const AngelScript::asSFuncPtr asFunc = func_ptr_convert::call(func);
                asdk::expose(*asIScriptEngine, name, ctor_cstr, asBEHAVE_CONSTRUCT, asFunc, asCALL);
                return *this;
            }

            typename type_traits::conditional<reflect&, type_traits::arg_type_ph, sizeof(static_cast<T>(T())) == sizeof(T)>::type
            constructor() {
                typedef typename type_traits::conditional<
                    void(*)(T&, asITypeInfo&),
                    void(*)(T&),
                    isTemplate != 0
                >::type FuncT;
                return constructor(static_cast<FuncT>(&ctor));
            }

            template<class Arg1T, class FuncT>
            typename type_traits::constructor<ObjType, T, FuncT, reflect&, void(*)(Arg1T)>::type
            constructor(const std::string& arg1_str, FuncT func) {
                const std::string ctor_str = (isTemplate != 0 ? "void ctor(int&in, " : "void ctor(") + arg1_str + ")";

                typedef type_traits::constructor<ObjType, T, FuncT, reflect, void(*)(Arg1T)> ctor_traits;
                typedef typename ctor_traits::class_type class_type;
                typedef type_traits::func_ptr_converter<FuncT, class_type> func_ptr_convert;
                const asECallConvTypes asCALL =
                    type_traits::is_same< class_type, void>::value ? (
                        ctor_traits::is_compatible_with_cdecl_objfirst::value ? asCALL_CDECL_OBJFIRST :
                        ctor_traits::is_compatible_with_cdecl_objlast::value ? asCALL_CDECL_OBJLAST :
                    asCALL_CDECL)
                    : (
                    asCALL_THISCALL);
                const AngelScript::asSFuncPtr asFunc = func_ptr_convert::call(func);
                asdk::expose(*asIScriptEngine, name, ctor_str.c_str(), asBEHAVE_CONSTRUCT, asFunc, asCALL);
                return *this;
            }
            template<class Arg1T>
            typename type_traits::conditional<reflect&, type_traits::arg_type_ph, sizeof(T(type_traits::declval<Arg1T>())) == sizeof(T)>::type
            constructor(const std::string& arg1_str) {
                typedef typename type_traits::conditional<
                    void(*)(T&, asITypeInfo&, Arg1T),
                    void(*)(T&, Arg1T),
                    isTemplate != 0
                >::type FuncT;
                return constructor<Arg1T>(arg1_str, static_cast<FuncT>(&ctor));
            }

            template<class Arg1T, class Arg2T, class FuncT>
            typename type_traits::constructor<ObjType, T, FuncT, reflect&, void(*)(Arg1T, Arg2T)>::type
            constructor(const std::string& arg1_str, const std::string& arg2_str, FuncT func) {
                const std::string ctor_str = (isTemplate != 0 ? "void ctor(int&in, " : "void ctor(") + arg1_str + ", " + arg2_str + ")";

                typedef type_traits::constructor<ObjType, T, FuncT, reflect, void(*)(Arg1T, Arg2T)> ctor_traits;
                typedef typename ctor_traits::class_type class_type;
                typedef type_traits::func_ptr_converter<FuncT, class_type> func_ptr_convert;
                const asECallConvTypes asCALL =
                    type_traits::is_same< class_type, void>::value ? (
                        ctor_traits::is_compatible_with_cdecl_objfirst::value ? asCALL_CDECL_OBJFIRST :
                        ctor_traits::is_compatible_with_cdecl_objlast::value ? asCALL_CDECL_OBJLAST :
                    asCALL_CDECL)
                    : (
                    asCALL_THISCALL);
                const AngelScript::asSFuncPtr asFunc = func_ptr_convert::call(func);
                asdk::expose(*asIScriptEngine, name, ctor_str.c_str(), asBEHAVE_CONSTRUCT, asFunc, asCALL);
                return *this;
            }
            template<class Arg1T, class Arg2T>
            typename type_traits::conditional<reflect&, type_traits::arg_type_ph, sizeof(T(type_traits::declval<Arg1T>(), type_traits::declval<Arg2T>())) == sizeof(T)>::type
            constructor(const std::string& arg1_str, const std::string& arg2_str) {
                typedef typename type_traits::conditional<
                    void(*)(T&, asITypeInfo&, Arg1T, Arg2T),
                    void(*)(T&, Arg1T, Arg2T),
                    isTemplate != 0
                >::type FuncT;
                return constructor<Arg1T>(arg1_str, arg2_str, static_cast<FuncT>(&ctor));
            }

            template<class FuncT>
            typename type_traits::function<ObjType, T, FuncT, reflect&>::type
            function(typename type_traits::function<ObjType, T, FuncT, const std::string&>::type func_str, FuncT func) {
                typedef type_traits::function<ObjType, T, FuncT, reflect&> func_traits;
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
                asdk::expose(*asIScriptEngine, name, func_str, asFunc, asCALL);
                return *this;
            }

            reflect destructor() {                
                struct lambdas {
                    static void dtor(T& that) // objfirst
                    { that.~T(); }
                };
                asdk::expose(*asIScriptEngine, name, "void dtor()", asBEHAVE_DESTRUCT, asFUNCTION(lambdas::dtor), asCALL_CDECL_OBJFIRST);
                return *this; 
            }

            template<class OtherT, class FuncT>
            typename type_traits::function<ObjType, T, FuncT, reflect&, bool(*)(OtherT)>::type
            operator_equal_to(FuncT func
                , typename type_traits::function<ObjType, T, FuncT, const std::string&, bool(*)(OtherT)>::type other_str)
            {
                const std::string op_str = "bool opEquals(" + other_str + ") const";

                typedef type_traits::function<ObjType, T, FuncT, reflect&, bool(*)(OtherT)> op_traits;
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
                asdk::expose(*asIScriptEngine, name, op_str.c_str(), asFunc, asCALL);
                return *this;
            }

            template<class FuncT>
            typename type_traits::function<ObjType, T, FuncT, reflect&, bool(*)(type_traits::arg_type_ph)>::type
            operator_equal_to(FuncT func
                , typename type_traits::function<ObjType, T, FuncT, const std::string&, bool(*)(type_traits::arg_type_ph)>::type other_str)
            {
                return operator_equal_to<type_traits::arg_type_ph, FuncT>(func, other_str);
            }

            typename type_traits::conditional<reflect&, type_traits::arg_type_ph, sizeof(type_traits::declval<T>() == type_traits::declval<T>()) == sizeof(bool)>::type
            operator_equal_to()
            {
                return operator_equal_to(static_cast<bool(*)(const T&, const T&)>(opEquals), "const " + name + "&in");
            }

            template<class OtherT>
            typename type_traits::conditional<reflect&, type_traits::arg_type_ph, sizeof(type_traits::declval<T>() == type_traits::declval<OtherT>()) == sizeof(bool)>::type
            operator_equal_to(const std::string& other_str)
            {
                return operator_equal_to(static_cast<bool(*)(const T&, const OtherT&)>(opEquals), other_str);
            }

            template<class OtherT, class FuncT>
            typename type_traits::function<ObjType, T, FuncT, reflect&, int(*)(OtherT)>::type
            operator_compare(FuncT func
                , typename type_traits::function<ObjType, T, FuncT, const std::string&, int(*)(OtherT)>::type other_str)
            {
                const std::string op_str = "int opCmp(" + other_str + ") const";

                typedef type_traits::function<ObjType, T, FuncT, reflect&, int(*)(OtherT)> op_traits;
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
                asdk::expose(*asIScriptEngine, name, op_str.c_str(), asFunc, asCALL);
                return *this;
            }           

            template<class FuncT>
            typename type_traits::function<ObjType, T, FuncT, reflect&, int(*)(type_traits::arg_type_ph)>::type
            operator_compare(FuncT func
                , typename type_traits::function<ObjType, T, FuncT, const std::string&, int(*)(type_traits::arg_type_ph)>::type other_str)
            {
                return operator_compare<type_traits::arg_type_ph, FuncT>(func, other_str);
            }

            typename type_traits::conditional<reflect&, type_traits::arg_type_ph, 
                sizeof(type_traits::declval<T>() < type_traits::declval<T>()) == sizeof(type_traits::declval<T>() > type_traits::declval<T>())>::type
            operator_compare()
            {
                return operator_compare(static_cast<int(*)(const T&, const T&)>(opCmp), "const " + name + "&in");
            }

            template<class OtherT>
            typename type_traits::conditional<reflect&, type_traits::arg_type_ph,
                sizeof(type_traits::declval<T>() < type_traits::declval<OtherT>()) == sizeof(type_traits::declval<T>() > type_traits::declval<OtherT>())>::type
            operator_compare(const std::string& other_str)
            {
                return operator_compare(static_cast<int(*)(const T&, const OtherT&)>(opCmp), other_str);
            }

        protected:
            AngelScript::asIScriptEngine* asIScriptEngine;
            std::string name;
            std::vector<asdk::expose> entities;
            //void expose(const asdk::expose& entity) { entities.push_back(entity); }
            void init()
            {
                asdk::expose(*asIScriptEngine, name, sizeof(T), ObjType);
            }

            template<class OtherT>
            inline static int opCmp(const T& lhs, const OtherT& rhs) // objfirst
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

            template<class OtherT>
            inline static bool opEquals(const T& lhs, const OtherT& rhs) // objfirst
            {
                return lhs == rhs;
            }

            inline static bool opEquals(const T& lhs, const T& rhs) // objfirst
            {
                return std::equal_to<T>()(lhs, rhs);
            }

            inline static void ctor(T& that, asITypeInfo& ti) // objfirst
            {
                new (&that) T();
            }
            inline static void ctor(T& that) // objfirst
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
        };


        template<class T>
        struct reflect<T, AngelScript::asEObjTypeFlags::asOBJ_TEMPLATE>
            : reflect<T, AngelScript::asEObjTypeFlags::type (asDWORD(AngelScript::asEObjTypeFlags::asOBJ_APP_CLASS) | AngelScript::asEObjTypeFlags::asOBJ_TEMPLATE)>
        {
            typedef reflect<T, AngelScript::asEObjTypeFlags::type (asDWORD(AngelScript::asEObjTypeFlags::asOBJ_APP_CLASS) | AngelScript::asEObjTypeFlags::asOBJ_TEMPLATE)> underlying_type;
            
            reflect(const std::string& name, AngelScript::asIScriptEngine& asIScriptEngine) : underlying_type(name, asIScriptEngine) {}
            reflect(AngelScript::asIScriptEngine& asIScriptEngine, const std::string& name) : underlying_type(name, asIScriptEngine) {}
            
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
            template<class FuncT>
            static typename type_traits::template_callback<FuncT, underlying_type&>::type
            template_callback_tester(FuncT func);
            static char
            template_callback_result_tester(const underlying_type&);
            static int
            template_callback_result_tester(const type_traits::arg_type_ph&);

            typedef
            typename type_traits::conditional<
                underlying_type&, type_traits::arg_type_ph,
                sizeof(
                    template_callback_result_tester(
                        template_callback_tester(T::template_callback)
                    )
                ) == sizeof(char)
            >::type helper_type;

        public:

            helper_type
            template_callback() { return template_callback(T::template_callback); }


        };
        template<class T> struct reflect_template 
            : reflect<T, AngelScript::asEObjTypeFlags::asOBJ_TEMPLATE> 
        {
            typedef reflect<T, AngelScript::asEObjTypeFlags::asOBJ_TEMPLATE> underlying_type;
            reflect_template(const std::string& name, AngelScript::asIScriptEngine& asIScriptEngine): underlying_type(name, asIScriptEngine) {}
            reflect_template(AngelScript::asIScriptEngine& asIScriptEngine, const std::string& name) : underlying_type(name, asIScriptEngine) {}
        };

    }
}

namespace asdk {

    using namespace asdk::reflection;
    using namespace asdk::exposing;
}

#undef ASDK_ARG
#undef ASDK_WRAP
#undef ASDK_CAT3
#undef ASDK_CAT2
#undef ASDK_CAT

#endif // ANGELSCRIPT_SOFTWARE_DEVELOPMENT_KIT_HPP

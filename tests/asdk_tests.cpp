#include "service/testsuit.h"

#ifndef ASDK_H_PATH
#   define ASDK_H_PATH <SERVICE_WRAP(ASTD_DIRECTORY)sdk/include/asdk/asdk.hpp>
#endif // ASDK_H_PATH

#include ASDK_H_PATH

#include <string>
#include <cstring>
#include <fstream>


SERVICE_FILE_TRANSLATION_YYMMDD_DATE(TRANSLATION_YYMMDD_DATE);
SERVICE_FILE_TRANSLATION_HHMMSS_TIME(TRANSLATION_HHMMSS_TIME);

class my_value_class
{
public:
    my_value_class(): value(), another_value() {}

    explicit my_value_class(int val) : value(val), another_value(val-1) {}

    friend bool operator==(
        const my_value_class& lhs, const my_value_class& rhs
        )
    {
        return lhs.value == rhs.value;
    }

    bool operator<(
        const my_value_class& other
        ) const
    {
        return value < other.value;;
    }

    int get_val() const { return value; }
    void set_val(int new_val) { value = new_val; }

    // Interfaces which are designed to be found by ADL
    friend void process(my_value_class& val)
    {
        val = val;
    }

    // Operator overloads
    friend my_value_class operator+(const my_value_class& lhs, int rhs) {
        return my_value_class(lhs.value + rhs);
    }
    friend my_value_class operator+(int lhs, const my_value_class& rhs) {
        return my_value_class(lhs + rhs.value);
    }

    int value;
    int another_value;

    static bool template_callback(asITypeInfo& type_info, bool& dont_GC) {
        return true;
    }

    static void ctor(my_value_class& that) // objfirst
    {
        new (&that) my_value_class();
    }    
    
    static void ctor_tmpl(my_value_class& that, asITypeInfo& ti) // objfirst
    {
        new (&that) my_value_class();
    }

    static void ctor_int_tmpl(asITypeInfo& ti, int val, my_value_class& that) // objlast
    {
        new (&that) my_value_class(val);
    }
    static void ctor_int(int val, my_value_class& that) // objlast
    {
        new (&that) my_value_class(val);
    }

    static void ctor_float_tmpl(my_value_class& that, asITypeInfo& ti, float val) // objfirst
    {
        new (&that) my_value_class(int(val));
    }
    static void ctor_float(my_value_class& that, float val) // objfirst
    {
        new (&that) my_value_class(int(val));
    }
    static void dtor(my_value_class& that)
    {
        that.~my_value_class();
    }
};


TEST_CASE("asdk: reflection type traits")
{
    namespace type_traits = asdk::reflection::type_traits;
    namespace AngelScript = asdk::AngelScript;
    {
        DOCTEST_STATIC_ASSERT((
            type_traits::is_compatible_function_args<
                  int (my_value_class::*)() const
                , int (my_value_class::*)() const
            >::value == bool(true)
        ), fail);
        DOCTEST_STATIC_ASSERT((
            type_traits::is_compatible_function_args<
                  int (my_value_class::*)() const
                , int (my_value_class::*)()
            >::value == bool(true)
        ), fail);
        DOCTEST_STATIC_ASSERT((
            type_traits::is_compatible_function_args<
                  int (my_value_class::*)() const
                , int (*)()
            >::value == bool(true)
        ), fail);
        DOCTEST_STATIC_ASSERT((
            type_traits::is_compatible_function_args<
                  int (my_value_class::*)()
                , int (*)()
            >::value == bool(true)
        ), fail);
        DOCTEST_STATIC_ASSERT((
            type_traits::is_compatible_function_args<
                  int (my_value_class::*)()
                , float (*)()
            >::value == bool(false)
        ), fail);
        DOCTEST_STATIC_ASSERT((
            type_traits::is_compatible_function_args<
                  int (my_value_class::*)()
                , type_traits::arg_type_ph (*)()
            >::value == bool(true)
        ), fail);
        DOCTEST_STATIC_ASSERT((
            type_traits::is_compatible_function_args<
                  int (my_value_class::*)(float)
                , type_traits::arg_type_ph (*)(float)
            >::value == bool(true)
        ), fail);
        DOCTEST_STATIC_ASSERT((
            type_traits::is_compatible_function_args<
                  int (my_value_class::*)(float)
                , type_traits::arg_type_ph (*)(type_traits::arg_type_ph)
            >::value == bool(true)
        ), fail);
        DOCTEST_STATIC_ASSERT((
            type_traits::is_compatible_function_args<
                  int (*)()
                , type_traits::arg_type_ph (*)(type_traits::arg_type_ph)
            >::value == bool(true)
        ), fail);
    }
    {
        typedef type_traits::constructor <
            AngelScript::asEObjTypeFlags::asOBJ_TEMPLATE,
            my_value_class,
            void (*)(asITypeInfo&, my_value_class&), // my_value_class::ctor
            my_value_class,
            void(*)()
        > constructor_type_traits;

        typedef
        constructor_type_traits::cdecl_objfirst::storage1
        my_value_class_ctor_storage;

        DOCTEST_STATIC_ASSERT((
            type_traits::is_same<constructor_type_traits::type, my_value_class>::value
        ), fail);
    }
    {
        typedef type_traits::constructor <
            AngelScript::asEObjTypeFlags::asOBJ_TEMPLATE,
            my_value_class,
            void (*)(asITypeInfo&, float, my_value_class&), // my_value_class::ctor_float - objlast
            my_value_class,
            void (*)(float)
        > constructor_type_traits;
        
        
        {
            typedef
            constructor_type_traits::decl_traits_type
            my_value_class_ctor_storage;
            DOCTEST_STATIC_ASSERT((
                type_traits::is_same<my_value_class_ctor_storage::class_type, void>::value
            ), fail);
            DOCTEST_STATIC_ASSERT((
                type_traits::is_same<my_value_class_ctor_storage::arg1_type, float>::value
            ), fail);
            DOCTEST_STATIC_ASSERT((
                type_traits::is_same<my_value_class_ctor_storage::arg2_type, void>::value
            ), fail);
        }
        
        {
            typedef
            constructor_type_traits::decl_traits_storage
            my_value_class_ctor_storage;
            DOCTEST_STATIC_ASSERT((
                type_traits::is_same<my_value_class_ctor_storage::class_type, void>::value
            ), fail);
            DOCTEST_STATIC_ASSERT((
                type_traits::is_same<my_value_class_ctor_storage::arg1_type, float>::value
            ), fail);
            DOCTEST_STATIC_ASSERT((
                type_traits::is_same<my_value_class_ctor_storage::arg2_type, void>::value
            ), fail);
        }
        
        {
            typedef
            constructor_type_traits::cdecl_objlast::storage1
            my_value_class_ctor_storage;
            DOCTEST_STATIC_ASSERT((
                type_traits::is_same<my_value_class_ctor_storage::class_type, void>::value
            ), fail);
            DOCTEST_STATIC_ASSERT((
                type_traits::is_same<my_value_class_ctor_storage::arg1_type, asITypeInfo&>::value
            ), fail);
            DOCTEST_STATIC_ASSERT((
                type_traits::is_same<my_value_class_ctor_storage::arg2_type, float>::value
            ), fail);
            DOCTEST_STATIC_ASSERT((
                type_traits::is_same<my_value_class_ctor_storage::arg3_type, my_value_class&>::value
            ), fail);
        }
        

        DOCTEST_STATIC_ASSERT((
            type_traits::is_same<constructor_type_traits::type, my_value_class>::value
        ), fail);
    }
    {
        typedef type_traits::constructor <
            AngelScript::asEObjTypeFlags::asOBJ_TEMPLATE,
            my_value_class,
            void (*)(my_value_class&, asITypeInfo&, float), // my_value_class::ctor_float - objfirst
            my_value_class,
            void (*)(float)
        > constructor_type_traits;
        
        
        {
            typedef
            constructor_type_traits::decl_traits_type
            my_value_class_ctor_storage;
            DOCTEST_STATIC_ASSERT((
                type_traits::is_same<my_value_class_ctor_storage::class_type, void>::value
            ), fail);
            DOCTEST_STATIC_ASSERT((
                type_traits::is_same<my_value_class_ctor_storage::arg1_type, float>::value
            ), fail);
            DOCTEST_STATIC_ASSERT((
                type_traits::is_same<my_value_class_ctor_storage::arg2_type, void>::value
            ), fail);
        }
        
        {
            typedef
            constructor_type_traits::decl_traits_storage
            my_value_class_ctor_storage;
            DOCTEST_STATIC_ASSERT((
                type_traits::is_same<my_value_class_ctor_storage::class_type, void>::value
            ), fail);
            DOCTEST_STATIC_ASSERT((
                type_traits::is_same<my_value_class_ctor_storage::arg1_type, float>::value
            ), fail);
            DOCTEST_STATIC_ASSERT((
                type_traits::is_same<my_value_class_ctor_storage::arg2_type, void>::value
            ), fail);
        }
        
        {
            typedef
            constructor_type_traits::cdecl_objfirst::storage1
            my_value_class_ctor_storage;
            DOCTEST_STATIC_ASSERT((
                type_traits::is_same<my_value_class_ctor_storage::class_type, void>::value
            ), fail);
            DOCTEST_STATIC_ASSERT((
                type_traits::is_same<my_value_class_ctor_storage::arg1_type, my_value_class&>::value
            ), fail);
            DOCTEST_STATIC_ASSERT((
                type_traits::is_same<my_value_class_ctor_storage::arg2_type, asITypeInfo&>::value
            ), fail);
            DOCTEST_STATIC_ASSERT((
                type_traits::is_same<my_value_class_ctor_storage::arg3_type, float>::value
            ), fail);
        }
        

        DOCTEST_STATIC_ASSERT((
            type_traits::is_same<constructor_type_traits::type, my_value_class>::value
        ), fail);
    }
    {
        typedef type_traits::function <
            AngelScript::asEObjTypeFlags::asOBJ_TEMPLATE,
            my_value_class,
            int (my_value_class::*)() const, // my_value_class::get_val
            my_value_class,
            int(*)()
        > function_type_traits;

        typedef
        function_type_traits::cdecl_or_thiscall::storage1
        my_value_class_get_val_storage;

        DOCTEST_STATIC_ASSERT((
            type_traits::is_same<function_type_traits::type, my_value_class>::value
        ), fail);
    }
    {
        typedef type_traits::function <
            AngelScript::asEObjTypeFlags::asOBJ_TEMPLATE,
            my_value_class,
            void (my_value_class::*)(int), // my_value_class::set_val
            my_value_class
        > function_type_traits;

        typedef
        function_type_traits::cdecl_or_thiscall::storage1
        my_value_class_get_val_storage;

        DOCTEST_STATIC_ASSERT((
            type_traits::is_same<function_type_traits::type, my_value_class>::value
        ), fail);
    }
    {
        typedef type_traits::function <
            AngelScript::asEObjTypeFlags::asOBJ_APP_CLASS,
            my_value_class,
            bool (*)(const my_value_class&, const my_value_class&), // my_value_class::operator==
            my_value_class,
            bool(*)(const my_value_class&)
        > function_type_traits;

        typedef
        function_type_traits::cdecl_objfirst::storage1
        my_value_class_get_val_storage;

        DOCTEST_STATIC_ASSERT((
            type_traits::is_same<function_type_traits::type, my_value_class>::value
        ), fail);
    }
}

TEST_CASE("asdk: exposing and reflection")
{
    using namespace testsuite::AngelScript; // for all types of AngelScript
    const std::string script_path = "./../service/resources/asdk_exposing_and_reflection_script.as";
    const std::string script_tmpl_path = "./../service/resources/asdk_exposing_and_reflection_script_tmpl.as";

    SERVICE_INIT_ENGINE_RAII();
    SERVICE_REQUEST_CONTEXT_RAII(asIScriptContext & asIScriptContext);

    asIScriptEngine &asIScriptEngine = *asIScriptContext.GetEngine();
    

    const char my_value_class_tmpl_cstr[] = { "my_value_class<T>" };
    const char my_value_class_cstr[] = { "my_value_class" };
    SUBCASE("template: exposing and import of function 'int asdk_exposing_and_reflection_test()'")
    {
        REQUIRE_NOTHROW(
            asdk::expose(asIScriptEngine, my_value_class_tmpl_cstr, sizeof(my_value_class), asOBJ_TEMPLATE)
        );
        CHECK(asIScriptEngine.GetTypeInfoByDecl(my_value_class_tmpl_cstr));
        REQUIRE(asIScriptEngine.GetTypeInfoByDecl(my_value_class_tmpl_cstr));
        REQUIRE_NOTHROW(
            asdk::expose(asIScriptEngine, my_value_class_tmpl_cstr, "void ctor(int&in)", asBEHAVE_CONSTRUCT, asFUNCTION(my_value_class::ctor_tmpl), asCALL_CDECL_OBJFIRST)
        );
        CHECK(asIScriptEngine.GetTypeInfoByDecl(my_value_class_tmpl_cstr)->GetBehaviourCount() == 1);
        REQUIRE_NOTHROW(
            asdk::expose(asIScriptEngine, my_value_class_tmpl_cstr, "void ctor(int&in, int)", asBEHAVE_CONSTRUCT, asFUNCTION(my_value_class::ctor_int_tmpl), asCALL_CDECL_OBJLAST)
        );
        CHECK(asIScriptEngine.GetTypeInfoByDecl(my_value_class_tmpl_cstr)->GetBehaviourCount() == 2);
        REQUIRE_NOTHROW(
            asdk::expose(asIScriptEngine, my_value_class_tmpl_cstr, "void ctor(int&in, float)", asBEHAVE_CONSTRUCT, asFUNCTION(my_value_class::ctor_float_tmpl), asCALL_CDECL_OBJFIRST)
        );
        CHECK(asIScriptEngine.GetTypeInfoByDecl(my_value_class_tmpl_cstr)->GetBehaviourCount() == 3);
        REQUIRE_NOTHROW(
            asdk::expose(asIScriptEngine, my_value_class_tmpl_cstr, "void dtor()", asBEHAVE_DESTRUCT, asFUNCTION(my_value_class::dtor), asCALL_CDECL_OBJLAST)
        );
        CHECK(asIScriptEngine.GetTypeInfoByDecl(my_value_class_tmpl_cstr)->GetBehaviourCount() == 4);
        REQUIRE_NOTHROW(
            asdk::expose(asIScriptEngine, my_value_class_tmpl_cstr, "bool template_callback(int&in, bool&out)", asBEHAVE_TEMPLATE_CALLBACK, asFUNCTION(my_value_class::template_callback), asCALL_CDECL)
        );
        CHECK(asIScriptEngine.GetTypeInfoByDecl(my_value_class_tmpl_cstr)->GetBehaviourCount() == 5);
        REQUIRE_NOTHROW(
            asdk::expose(asIScriptEngine, my_value_class_tmpl_cstr, "int get_val() const", asMETHOD(my_value_class, get_val), asCALL_THISCALL)
        );
        REQUIRE_NOTHROW(
            asdk::expose(asIScriptEngine, my_value_class_tmpl_cstr, "void set_val(int)", asMETHOD(my_value_class, set_val), asCALL_THISCALL)
        );
        REQUIRE_NOTHROW(
            asdk::expose(asIScriptEngine, my_value_class_tmpl_cstr, std::string("bool opEquals(const ") + my_value_class_tmpl_cstr + " & in) const"
                , asFUNCTIONPR(operator==, (const my_value_class&, const my_value_class&), bool), asCALL_CDECL_OBJFIRST)
        );

        SERVICE_IMPORT_FUNCTION(reflection_test, script_tmpl_path, "int asdk_exposing_and_reflection_test()");

        CHECK(static_cast<int>(asSUCCESS) == asIScriptContext.Prepare(reflection_test));
        CHECK(static_cast<int>(asEXECUTION_FINISHED) == asIScriptContext.Execute());
        CHECK(*(asINT32*)(asIScriptContext.GetAddressOfReturnValue()) == 0);
    }

    SUBCASE("template: reflection and import of function 'int asdk_exposing_and_reflection_test()'")
    {
        typedef asdk::reflect<my_value_class, asOBJ_TEMPLATE> reflect;
        reflect(my_value_class_tmpl_cstr, asIScriptEngine)
            .template_callback()
            .constructor()
            .constructor(&my_value_class::ctor_tmpl)
            .constructor<int>("int val")
            .constructor<float>("float val", &my_value_class::ctor_float_tmpl)
            .destructor()
            .function("int get_val() const", &my_value_class::get_val)
            .function("void set_val(int)", &my_value_class::set_val)
            .operator_equal_to<const my_value_class&, bool(*)(const my_value_class&, const my_value_class&)>(operator==, "const my_value_class<T> & in")
            //.operator<()(&my_value_class::operator<)
            //.operator+<my_value_class, int>()
            //.operator+<int, my_value_class>()
            ;

        SERVICE_IMPORT_FUNCTION(reflection_test, script_tmpl_path, "int asdk_exposing_and_reflection_test()");

        CHECK(static_cast<int>(asSUCCESS) == asIScriptContext.Prepare(reflection_test));
        CHECK(static_cast<int>(asEXECUTION_FINISHED) == asIScriptContext.Execute());
        CHECK(asIScriptContext.GetReturnDWord() == 0);
    }

    SUBCASE("reflection and import of function 'int asdk_exposing_and_reflection_test()'")
    {
        typedef asdk::reflect<my_value_class, asOBJ_APP_CLASS> reflect;
        reflect(my_value_class_cstr, asIScriptEngine)
            .constructor()
            .constructor(&my_value_class::ctor)
            .constructor<int>("int val")
            .constructor<float>("float val", &my_value_class::ctor_float)
            .destructor()
            .function("int get_val() const", &my_value_class::get_val)
            .function("void set_val(int)", &my_value_class::set_val)
            .operator_equal_to()
            //.operator<()(&my_value_class::operator<)
            //.operator+<my_value_class, int>()
            //.operator+<int, my_value_class>()
            ;

        SERVICE_IMPORT_FUNCTION(reflection_test, script_path, "int asdk_exposing_and_reflection_test()");

        CHECK(static_cast<int>(asSUCCESS) == asIScriptContext.Prepare(reflection_test));
        CHECK(static_cast<int>(asEXECUTION_FINISHED) == asIScriptContext.Execute());
        CHECK(asIScriptContext.GetReturnDWord() == 0);
    }
}
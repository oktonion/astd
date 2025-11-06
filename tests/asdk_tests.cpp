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

    my_value_class& operator=(const my_value_class& other)
    {
        value = other.value;
        another_value = other.another_value;
        return *this;
    }

    friend bool operator==(
        const my_value_class& lhs, const my_value_class& rhs
        );

    bool operator<(
        const my_value_class& other
        ) const
    {
        return value < other.value;;
    }

    bool operator>(
        const my_value_class& other
        ) const
    {
        return value > other.value;;
    }

    int get_val() const { return value; }
    void set_val(int new_val) { value = new_val; }

    // Interfaces which are designed to be found by ADL
    friend void process(my_value_class& val)
    {
        val = val;
    }

    // Operator overloads
    friend my_value_class operator+(const my_value_class& lhs, int rhs);
    friend my_value_class operator+(int lhs, const my_value_class& rhs);
    friend my_value_class operator-(const my_value_class& lhs, int rhs);
    friend my_value_class operator-(int lhs, const my_value_class& rhs);

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

bool operator==(
    const my_value_class& lhs, const my_value_class& rhs
)
{
    return lhs.value == rhs.value;
}

my_value_class operator+(const my_value_class& lhs, int rhs) {
    return my_value_class(lhs.value + rhs);
}
my_value_class operator+(int lhs, const my_value_class& rhs) {
    return my_value_class(lhs + rhs.value);
}

my_value_class operator-(const my_value_class& lhs, int rhs) {
    return my_value_class(lhs.value - rhs);
}
my_value_class operator-(int lhs, const my_value_class& rhs) {
    return my_value_class(lhs - rhs.value);
}

int operator_compare(
    const my_value_class& lhs, const my_value_class& rhs
)
{
    if (lhs < rhs) return -1;
    if (lhs > rhs) return 1;
    return 0;
}

TEST_CASE("asdk: reflection type traits")
{
    namespace type_traits = asdk::reflection::type_traits;
    namespace AngelScript = asdk::AngelScript;
#   ifndef __BORLANDC__
    {
        typedef int (my_value_class::*member_function_const)() const;
        typedef int (my_value_class::*member_function)();
        DOCTEST_STATIC_ASSERT((
            type_traits::is_compatible_function_args<
                  member_function_const
                , member_function_const
            >::value == bool(true)
        ), fail);
        DOCTEST_STATIC_ASSERT((
            type_traits::is_compatible_function_args<
                  member_function_const
                , member_function
            >::value == bool(true)
        ), fail);
        DOCTEST_STATIC_ASSERT((
            type_traits::is_compatible_function_args<
                  member_function_const
                , int (*)()
            >::value == bool(true)
        ), fail);
        DOCTEST_STATIC_ASSERT((
            type_traits::is_compatible_function_args<
                  member_function
                , int (*)()
            >::value == bool(true)
        ), fail);
        DOCTEST_STATIC_ASSERT((
            type_traits::is_compatible_function_args<
                  member_function
                , float (*)()
            >::value == bool(false)
        ), fail);
        DOCTEST_STATIC_ASSERT((
            type_traits::is_compatible_function_args<
                  member_function
                , type_traits::arg_type_ph (*)()
            >::value == bool(true)
        ), fail);
    }
    {
        typedef int (my_value_class::* member_function)(float);
        DOCTEST_STATIC_ASSERT((
            type_traits::is_compatible_function_args<
                  member_function
                , type_traits::arg_type_ph (*)(float)
            >::value == bool(true)
        ), fail);
        DOCTEST_STATIC_ASSERT((
            type_traits::is_compatible_function_args<
                  member_function
                , type_traits::arg_type_ph (*)(type_traits::arg_type_ph)
            >::value == bool(true)
        ), fail);
    }
#   endif
    {
        DOCTEST_STATIC_ASSERT((
            type_traits::is_compatible_function_args<
                  int (*)()
                , type_traits::arg_type_ph (*)(type_traits::arg_type_ph)
            >::value == bool(true)
        ), fail);
    }

    {
        typedef type_traits::constructor <
            type_traits::reflect_flags<AngelScript::asEObjTypeFlags::asOBJ_TEMPLATE>,
            my_value_class,
            void (*)(asITypeInfo&, my_value_class&), // my_value_class::ctor_tmpl
            my_value_class,
            void(*)()
        > constructor_type_traits;

        {
            typedef int(*is_template_check_type)[constructor_type_traits::flags::is_template ? 1 : -1];
            int is_template_check[constructor_type_traits::flags::is_template ? 1 : -1];
        }

        {
            typedef constructor_type_traits::ti_reference_storage ti_reference_storage;

            sizeof type_traits::declval<ti_reference_storage::arg1_type>();
            sizeof type_traits::declval<ti_reference_storage::arg1_type>().GetEngine();

            sizeof (true ? type_traits::declval<ti_reference_storage::arg1_type>() :
                type_traits::declval<asITypeInfo&>());
        }

        {
            typedef constructor_type_traits::class_reference_storage class_reference_storage;
            typedef constructor_type_traits::ti_decl_reference_storage ti_decl_reference_storage;

            sizeof type_traits::declval<class_reference_storage::arg1_type>();
            sizeof type_traits::declval<ti_decl_reference_storage::arg1_type>();
            sizeof type_traits::declval<class_reference_storage::arg1_type>().value;
            sizeof type_traits::declval<ti_decl_reference_storage::arg1_type>().GetEngine();

            sizeof (true ? type_traits::declval<class_reference_storage::arg1_type>() :
                type_traits::declval<my_value_class&>());
            sizeof (true ? type_traits::declval<ti_decl_reference_storage::arg1_type>() :
                type_traits::declval<asITypeInfo&>());
        }

        
        DOCTEST_STATIC_ASSERT((
            constructor_type_traits::is_compatible_with_cdecl_objfirst::value == bool(false)
        ), fail);
        DOCTEST_STATIC_ASSERT((
            constructor_type_traits::is_compatible_with_cdecl_objlast::value == bool(true)
        ), fail);

        typedef
        constructor_type_traits::cdecl_objlast::storage1
        my_value_class_ctor_storage;
        
        {
            sizeof type_traits::declval<my_value_class_ctor_storage::arg2_type>();
            sizeof type_traits::declval<my_value_class_ctor_storage::arg1_type>();
            sizeof type_traits::declval<my_value_class_ctor_storage::arg2_type>().value;
            sizeof type_traits::declval<my_value_class_ctor_storage::arg1_type>().GetEngine();

            sizeof (true ? type_traits::declval<my_value_class_ctor_storage::arg2_type>() :
                type_traits::declval<my_value_class&>());
            sizeof (true ? type_traits::declval<my_value_class_ctor_storage::arg1_type>() :
                type_traits::declval<asITypeInfo&>());

            sizeof type_traits::declval<constructor_type_traits::type>();
            sizeof type_traits::declval<constructor_type_traits::type>().value;
        }
        
        DOCTEST_STATIC_ASSERT((
            type_traits::is_same<my_value_class_ctor_storage::arg1_type, asITypeInfo&>::value
        ), fail);

        DOCTEST_STATIC_ASSERT((
            type_traits::is_same<my_value_class_ctor_storage::arg2_type, my_value_class&>::value
        ), fail);

        DOCTEST_STATIC_ASSERT((
            type_traits::is_same<constructor_type_traits::type, my_value_class>::value
        ), fail);
    }
    {
        typedef type_traits::constructor <
            type_traits::reflect_flags<AngelScript::asEObjTypeFlags::asOBJ_TEMPLATE>,
            my_value_class,
            void (*)(my_value_class&, asITypeInfo&), // my_value_class::ctor_tmpl
            my_value_class,
            void(*)()
        > constructor_type_traits;

        {
            typedef int(*is_template_check_type)[constructor_type_traits::flags::is_template ? 1 : -1];
            int is_template_check[constructor_type_traits::flags::is_template ? 1 : -1];
        }

        {
            typedef constructor_type_traits::ti_reference_storage ti_reference_storage;

            sizeof type_traits::declval<ti_reference_storage::arg1_type>();
            sizeof type_traits::declval<ti_reference_storage::arg1_type>().GetEngine();

            sizeof(true ? type_traits::declval<ti_reference_storage::arg1_type>() :
                type_traits::declval<asITypeInfo&>());
        }

        {
            typedef constructor_type_traits::class_reference_storage class_reference_storage;
            typedef constructor_type_traits::ti_decl_reference_storage ti_decl_reference_storage;

            sizeof type_traits::declval<class_reference_storage::arg1_type>();
            sizeof type_traits::declval<ti_decl_reference_storage::arg1_type>();
            sizeof type_traits::declval<class_reference_storage::arg1_type>().value;
            sizeof type_traits::declval<ti_decl_reference_storage::arg1_type>().GetEngine();

            sizeof(true ? type_traits::declval<class_reference_storage::arg1_type>() :
                type_traits::declval<my_value_class&>());
            sizeof(true ? type_traits::declval<ti_decl_reference_storage::arg1_type>() :
                type_traits::declval<asITypeInfo&>());
        }

        DOCTEST_STATIC_ASSERT((
            constructor_type_traits::is_compatible_with_cdecl_objfirst::value == bool(true)
        ), fail);
        DOCTEST_STATIC_ASSERT((
            constructor_type_traits::is_compatible_with_cdecl_objlast::value == bool(false)
        ), fail);

        typedef
        constructor_type_traits::cdecl_objfirst::storage1
            my_value_class_ctor_storage;

        {
            sizeof type_traits::declval<my_value_class_ctor_storage::arg1_type>();
            sizeof type_traits::declval<my_value_class_ctor_storage::arg2_type>();
            sizeof type_traits::declval<my_value_class_ctor_storage::arg1_type>().value;
            sizeof type_traits::declval<my_value_class_ctor_storage::arg2_type>().GetEngine();

            sizeof(true ? type_traits::declval<my_value_class_ctor_storage::arg1_type>() :
                type_traits::declval<my_value_class&>());
            sizeof(true ? type_traits::declval<my_value_class_ctor_storage::arg2_type>() :
                type_traits::declval<asITypeInfo&>());

            sizeof type_traits::declval<constructor_type_traits::type>();
            sizeof type_traits::declval<constructor_type_traits::type>().value;
        }

        DOCTEST_STATIC_ASSERT((
            type_traits::is_same<my_value_class_ctor_storage::arg2_type, asITypeInfo&>::value
            ), fail);

        DOCTEST_STATIC_ASSERT((
            type_traits::is_same<my_value_class_ctor_storage::arg1_type, my_value_class&>::value
            ), fail);

        DOCTEST_STATIC_ASSERT((
            type_traits::is_same<constructor_type_traits::type, my_value_class>::value
            ), fail);
    }
    {
        typedef type_traits::constructor <
            type_traits::reflect_flags<AngelScript::asEObjTypeFlags::asOBJ_TEMPLATE>,
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
            type_traits::reflect_flags<AngelScript::asEObjTypeFlags::asOBJ_TEMPLATE>,
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
        {
            sizeof type_traits::declval<constructor_type_traits::type>();
            sizeof type_traits::declval<constructor_type_traits::type>().value;
        }

        DOCTEST_STATIC_ASSERT((
            type_traits::is_same<constructor_type_traits::type, my_value_class>::value
        ), fail);
    }
#   ifndef __BORLANDC__
    {
        typedef int (my_value_class::* get_val_type)() const;
        typedef type_traits::function <
            type_traits::reflect_flags<AngelScript::asEObjTypeFlags::asOBJ_TEMPLATE>,
            my_value_class,
            get_val_type, // my_value_class::get_val
            my_value_class,
            int(*)()
        > function_type_traits;


        {
            typedef function_type_traits::class_type class_type;

            sizeof type_traits::declval<class_type>();
            sizeof type_traits::declval<class_type>().value;

            sizeof (true ? type_traits::declval<class_type>() :
                type_traits::declval<my_value_class&>());
        }

        typedef
        function_type_traits::cdecl_or_thiscall::storage1
        my_value_class_get_val_storage;

        {
            sizeof type_traits::declval<function_type_traits::type>();
            sizeof type_traits::declval<function_type_traits::type>().value;
        }

        DOCTEST_STATIC_ASSERT((
            type_traits::is_same<function_type_traits::type, my_value_class>::value
        ), fail);
    }
    {
        typedef void (my_value_class::* set_val_type)(int);
        typedef type_traits::function <
            type_traits::reflect_flags<AngelScript::asEObjTypeFlags::asOBJ_TEMPLATE>,
            my_value_class,
            set_val_type, // my_value_class::set_val
            my_value_class
        > function_type_traits;

        typedef
        function_type_traits::cdecl_or_thiscall::storage1
        my_value_class_get_val_storage;

        {
            sizeof type_traits::declval<function_type_traits::type>();
            sizeof type_traits::declval<function_type_traits::type>().value;
        }

        DOCTEST_STATIC_ASSERT((
            type_traits::is_same<function_type_traits::type, my_value_class>::value
        ), fail);
    }
#   endif
    {
        typedef type_traits::function <
            type_traits::reflect_flags<AngelScript::asEObjTypeFlags::asOBJ_TEMPLATE>,
            my_value_class,
            bool (*)(const my_value_class&, const my_value_class&), // my_value_class::operator==
            my_value_class,
            bool(*)(const my_value_class&)
        > function_type_traits;

        typedef
        function_type_traits::cdecl_objfirst::storage1
        my_value_class_get_val_storage;

        {
            sizeof type_traits::declval<function_type_traits::type>();
            sizeof type_traits::declval<function_type_traits::type>().value;
        }

        DOCTEST_STATIC_ASSERT((
            function_type_traits::is_compatible_with_cdecl_objlast::value == bool(true)
        ), fail);

        DOCTEST_STATIC_ASSERT((
            function_type_traits::is_compatible_with_cdecl_objfirst::value == bool(true)
        ), fail);

        DOCTEST_STATIC_ASSERT((
            type_traits::is_same<function_type_traits::type, my_value_class>::value
        ), fail);
    }
    {
        typedef type_traits::function <
            type_traits::reflect_flags<AngelScript::asEObjTypeFlags::asOBJ_APP_CLASS>,
            my_value_class,
            my_value_class(*)(int, const my_value_class&), // opAdd_r
            my_value_class,
            my_value_class(*)(int)
        > function_type_traits;

        typedef
        function_type_traits::cdecl_objlast::storage1
        my_value_class_get_val_storage;

        {
            sizeof type_traits::declval<function_type_traits::type>();
            sizeof type_traits::declval<function_type_traits::type>().value;
        }

        DOCTEST_STATIC_ASSERT((
            function_type_traits::is_compatible_with_cdecl_objlast::value == bool(true)
        ), fail);

        DOCTEST_STATIC_ASSERT((
            function_type_traits::is_compatible_with_cdecl_objfirst::value == bool(false)
        ), fail);

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
            asdk::expose(asIScriptEngine, my_value_class_tmpl_cstr, sizeof(my_value_class), asOBJ_TEMPLATE, asOBJ_APP_CLASS_CONSTRUCTOR, asOBJ_APP_CLASS_ALLINTS)
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
        REQUIRE_NOTHROW(
            asdk::expose(asIScriptEngine, my_value_class_tmpl_cstr, std::string("int opCmp(const ") + my_value_class_tmpl_cstr + " & in) const"
                , asFUNCTIONPR(operator_compare, (const my_value_class&, const my_value_class&), int), asCALL_CDECL_OBJFIRST)
        );
        REQUIRE_NOTHROW(
            asdk::expose(asIScriptEngine, my_value_class_tmpl_cstr, my_value_class_tmpl_cstr + std::string(" opAdd(int) const")
                , asFUNCTIONPR(operator+, (const my_value_class&, int), my_value_class), asCALL_CDECL_OBJFIRST)
        );
        REQUIRE_NOTHROW(
            asdk::expose(asIScriptEngine, my_value_class_tmpl_cstr, my_value_class_tmpl_cstr + std::string(" opAdd_r(int) const")
                , asFUNCTIONPR(operator+, (int, const my_value_class&), my_value_class), asCALL_CDECL_OBJLAST)
        );
        REQUIRE_NOTHROW(
            asdk::expose(asIScriptEngine, my_value_class_tmpl_cstr, my_value_class_tmpl_cstr + std::string(" opSub(int) const")
                , asFUNCTIONPR(operator-, (const my_value_class&, int), my_value_class), asCALL_CDECL_OBJFIRST)
        );
        REQUIRE_NOTHROW(
            asdk::expose(asIScriptEngine, my_value_class_tmpl_cstr, my_value_class_tmpl_cstr + std::string(" opSub_r(int) const")
                , asFUNCTIONPR(operator-, (int, const my_value_class&), my_value_class), asCALL_CDECL_OBJLAST)
        );
        REQUIRE_NOTHROW(
            asdk::expose(asIScriptEngine, my_value_class_tmpl_cstr, my_value_class_tmpl_cstr + std::string("& opAssign(const ") + my_value_class_tmpl_cstr + " & in) const"
                , asMETHODPR(my_value_class, operator=, (const my_value_class&), my_value_class&), asCALL_THISCALL)
        );

        SERVICE_IMPORT_FUNCTION(reflection_test, script_tmpl_path, "int asdk_exposing_and_reflection_test()");

        CHECK(static_cast<int>(asSUCCESS) == asIScriptContext.Prepare(reflection_test));
        CHECK(static_cast<int>(asEXECUTION_FINISHED) == asIScriptContext.Execute());
        CHECK(*(asINT32*)(asIScriptContext.GetAddressOfReturnValue()) == 0);
    }

    SUBCASE("template: reflection and import of function 'int asdk_exposing_and_reflection_test()'")
    {
        typedef asdk::reflect<my_value_class, asOBJ_TEMPLATE, asOBJ_APP_CLASS_ALLINTS> reflect;
        {
            int is_template[reflect::flags::is_template ? 1 : -1];
            typedef 
            asdk::type_traits::constructor<
                  reflect::flags
                , my_value_class
                , void (&)(my_value_class&, asITypeInfo&)
                , int
                , void(*)()
            > constructor_traits;

            int is_template_traits[constructor_traits::flags::is_template ? 1 : -1];
            constructor_traits::type constructor_traits_type;

            int ctor_tmpl_is_constructor[sizeof(constructor_traits::type)];

            DOCTEST_STATIC_ASSERT((
                asdk::type_traits::is_same<constructor_traits::type, int>::value
            ), fail);
        }

        reflect(my_value_class_tmpl_cstr, asIScriptEngine, true, false, false, false)
            .template_callback()
            .constructor()
            .constructor(&my_value_class::ctor_tmpl)
            .constructor<int>("int val")
            .constructor<float>("float val", &my_value_class::ctor_float_tmpl)
            .destructor()
            .function("int get_val() const", &my_value_class::get_val)
            .function("void set_val(int)", &my_value_class::set_val)
            .operator_assign()
            .operator_equal_to<my_value_class>("const my_value_class<T> & in")
            .operator_compare()
            .operator+<int>("int")
            .operator+<int, my_value_class>("int")
            .operator-<int>("int")
            .operator-<int, my_value_class>("int")
            ;

        SERVICE_IMPORT_FUNCTION(reflection_test, script_tmpl_path, "int asdk_exposing_and_reflection_test()");

        CHECK(static_cast<int>(asSUCCESS) == asIScriptContext.Prepare(reflection_test));
        CHECK(static_cast<int>(asEXECUTION_FINISHED) == asIScriptContext.Execute());
        CHECK(asIScriptContext.GetReturnDWord() == 0);
    }

    SUBCASE("reflection and import of function 'int asdk_exposing_and_reflection_test()'")
    {
        typedef asdk::reflect<my_value_class, asOBJ_APP_CLASS_ALLINTS> reflect;
        reflect(my_value_class_cstr, asIScriptEngine, true, false, false, false)
            .constructor()
            .constructor(&my_value_class::ctor)
            .constructor<int>("int val")
            .constructor<float>("float val", &my_value_class::ctor_float)
            .destructor()
            .function("int get_val() const", &my_value_class::get_val)
            .function("void set_val(int)", &my_value_class::set_val)
            .operator_assign()
            .operator_equal_to()
            .operator_compare<my_value_class>("const my_value_class & in")
            .operator_add<int>("int")
            .operator_add<int, my_value_class>("int")
            .operator_substract<int>("int")
            .operator_substract<int, my_value_class>("int")
            ;

        SERVICE_IMPORT_FUNCTION(reflection_test, script_path, "int asdk_exposing_and_reflection_test()");

        CHECK(static_cast<int>(asSUCCESS) == asIScriptContext.Prepare(reflection_test));
        CHECK(static_cast<int>(asEXECUTION_FINISHED) == asIScriptContext.Execute());
        CHECK(asIScriptContext.GetReturnDWord() == 0);
    }
}
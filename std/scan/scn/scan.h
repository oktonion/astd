#ifndef SCN_SCAN_H_
#define SCN_SCAN_H_

#include <string>
#include <cstdlib>
#include <cwchar>
#include <errno.h>

#include "./error.h"

namespace scn
{    
    struct scan_errc
    {
        enum type
        {
            internal // internal scan error
            , invalid_format_string // Unexpected end of format string argument
            , end_of_range // EOF
            , invalid_encoding // Invalid code point
            , invalid_scanned_value // Invalid scanned value
            , buffer_overflow
        };
    };

    typedef error_code<scan_errc::type> scan_error_code;
    typedef error<scan_errc::type> scan_error;
    struct scan_error_category
        : error_category<scan_errc::type>
    {
        virtual const char* name() const throw() { return "scn::scan"; }

        std::string message(scan_errc::type errc) const
        {
            switch (errc)
            {
            case scan_errc::internal: return "Internal scn::scan error";
            case scan_errc::invalid_format_string: return "Unexpected end of format string argument";
            case scan_errc::end_of_range: return "EOF";
            case scan_errc::invalid_encoding: return "Invalid code point";
            case scan_errc::buffer_overflow: return "Buffer overflow";

            };

            return "";
        }
    };

    scan_error_code make_error_code(scan_errc::type code)
    {
        static const scan_error_category category;
        return scan_error_code(code, category);
    }

    typedef result<scan_error> scan_result;

    FMT_GCC_EXTENSION typedef long long LongLong;
    FMT_GCC_EXTENSION typedef unsigned long long ULongLong;

    /**
      \rst
      A string reference. It can be constructed from a C string or
      ``std::basic_string``.

      You can use one of the following typedefs for common character types:

      +------------+-------------------------+
      | Type       | Definition              |
      +============+=========================+
      | StringRef  | BasicStringRef<char>    |
      +------------+-------------------------+
      | WStringRef | BasicStringRef<wchar_t> |
      +------------+-------------------------+

      This class is most useful as a parameter type to allow passing
      different types of strings to a function, for example::

        template <typename... Args>
        std::string format(StringRef format_str, const Args & ... args);

        format("{}", 42);
        format(std::string("{}"), 42);
      \endrst
     */
    template <typename Char>
    class BasicStringRef {
    private:
        const Char* data_;
        std::size_t size_;

    public:
        /** Constructs a string reference object from a C string and a size. */
        BasicStringRef(const Char* s, std::size_t size) : data_(s), size_(size) {}

        /**
          \rst
          Constructs a string reference object from a C string computing
          the size with ``std::char_traits<Char>::length``.
          \endrst
         */
        BasicStringRef(const Char* s)
            : data_(s), size_(std::char_traits<Char>::length(s)) {}

        /**
          \rst
          Constructs a string reference from a ``std::basic_string`` object.
          \endrst
         */
        template <typename Allocator>
        BasicStringRef(
            const std::basic_string<Char, std::char_traits<Char>, Allocator>& s)
            : data_(s.c_str()), size_(s.size()) {}

#if SCN_HAS_STRING_VIEW
        /**
          \rst
          Constructs a string reference from a ``std::basic_string_view`` object.
          \endrst
         */
        BasicStringRef(
            const std::basic_string_view<Char, std::char_traits<Char>>& s)
            : data_(s.data()), size_(s.size()) {}

        /**
         \rst
         Converts a string reference to an ``std::string_view`` object.
         \endrst
        */
        explicit operator std::basic_string_view<Char>() const FMT_NOEXCEPT {
            return std::basic_string_view<Char>(data_, size_);
        }
#endif

#if SCN_HAS_EXPERIMENTAL_STRING_VIEW
        /**
        \rst
        Constructs a string reference from a ``std::experimental::basic_string_view`` object.
        \endrst
        */
        BasicStringRef(
            const std::experimental::basic_string_view<Char, std::char_traits<Char>>& s)
            : data_(s.data()), size_(s.size()) {}

        /**
        \rst
        Converts a string reference to an ``std::string_view`` object.
        \endrst
        */
        explicit operator std::experimental::basic_string_view<Char>() const FMT_NOEXCEPT {
            return std::experimental::basic_string_view<Char>(data_, size_);
        }
#endif

        /**
          \rst
          Converts a string reference to an ``std::string`` object.
          \endrst
         */
        std::basic_string<Char> to_string() const {
            return std::basic_string<Char>(data_, size_);
        }

        /** Returns a pointer to the string data. */
        const Char* data() const { return data_; }

        /** Returns the string size. */
        std::size_t size() const { return size_; }

        // Lexicographically compare this string reference to other.
        int compare(BasicStringRef other) const {
            std::size_t size = size_ < other.size_ ? size_ : other.size_;
            int result = std::char_traits<Char>::compare(data_, other.data_, size);
            if (result == 0)
                result = size_ == other.size_ ? 0 : (size_ < other.size_ ? -1 : 1);
            return result;
        }

        friend bool operator==(BasicStringRef lhs, BasicStringRef rhs) {
            return lhs.compare(rhs) == 0;
        }
        friend bool operator!=(BasicStringRef lhs, BasicStringRef rhs) {
            return lhs.compare(rhs) != 0;
        }
        friend bool operator<(BasicStringRef lhs, BasicStringRef rhs) {
            return lhs.compare(rhs) < 0;
        }
        friend bool operator<=(BasicStringRef lhs, BasicStringRef rhs) {
            return lhs.compare(rhs) <= 0;
        }
        friend bool operator>(BasicStringRef lhs, BasicStringRef rhs) {
            return lhs.compare(rhs) > 0;
        }
        friend bool operator>=(BasicStringRef lhs, BasicStringRef rhs) {
            return lhs.compare(rhs) >= 0;
        }
    };

    typedef BasicStringRef<char> StringRef;
    typedef BasicStringRef<wchar_t> WStringRef;

    template <typename Char>
    class BasicCStringRef {
    private:
        const Char* data_;

    public:
        /** Constructs a string reference object from a C string. */
        BasicCStringRef(const Char* s) : data_(s) {}

        /**
          \rst
          Constructs a string reference from a ``std::basic_string`` object.
          \endrst
         */
        template <typename Allocator>
        BasicCStringRef(
            const std::basic_string<Char, std::char_traits<Char>, Allocator>& s)
            : data_(s.c_str()) {}

        /** Returns the pointer to a C string. */
        const Char* c_str() const { return data_; }
    };

    typedef BasicCStringRef<char> CStringRef;
    typedef BasicCStringRef<wchar_t> WCStringRef;

    namespace internal
    {
        // A formatting argument reference to value.
        struct ValueRef {
            template <typename Char>
            struct StringValue {
                Char* value;
                std::size_t size;
            };

            union {
                void* value;
                StringValue<char> string;
                StringValue<signed char> sstring;
                StringValue<unsigned char> ustring;
                StringValue<wchar_t> wstring;
            };

            enum Type {
                NONE, NAMED_ARG,
                // Integer types should go first,
                INT, UINT, LONG_LONG, ULONG_LONG, BOOL, CHAR, LAST_INTEGER_TYPE = CHAR,
                // followed by floating-point types.
                DOUBLE, LONG_DOUBLE, LAST_NUMERIC_TYPE = LONG_DOUBLE,
                CSTRING, STRING, WSTRING, POINTER, CUSTOM
            };
        };


        // A formatting argument reference.
        struct ArgRef : ValueRef {
            Type type;
        };
    } // namespace internal

    namespace internal
    {
        template <typename T = void>
        struct Null {};

        // A helper class template to enable or disable overloads taking wide
        // characters and strings in MakeValue.
        template <typename T, typename Char>
        struct WCharHelper {
            typedef Null<T> Supported;
            typedef T Unsupported;
        };

        template <typename T>
        struct WCharHelper<T, wchar_t> {
            typedef T Supported;
            typedef Null<T> Unsupported;
        };
        
        // A helper function to suppress bogus "conditional expression is constant"
        // warnings.
        template <typename T>
        inline T const_check(T value) { return value; }

        // Makes an Arg object from any type.
        template <typename Formatter>
        class MakeValueRef : public ArgRef {
        public:
            typedef typename Formatter::Char Char;

        private:
            // The following two methods are private to disallow formatting of
            // arbitrary pointers. If you want to output a pointer cast it to
            // "void *" or "const void *". In particular, this forbids formatting
            // of "[const] volatile char *" which is printed as bool by iostreams.
            // Do not implement!
            template <typename T>
            MakeValueRef(const T* value);
            template <typename T>
            MakeValueRef(T* value);

            // The following methods are private to disallow formatting of wide
            // characters and strings into narrow strings as in
            //   fmt::format("{}", L"test");
            // To fix this, use a wide format string: fmt::format(L"{}", L"test").
#if !_MSC_VER || defined(_NATIVE_WCHAR_T_DEFINED)
            MakeValueRef(typename WCharHelper<wchar_t, Char>::Unsupported&);
#endif
            MakeValueRef(typename WCharHelper<wchar_t*, Char>::Unsupported&);
            MakeValueRef(typename WCharHelper<std::wstring&, Char>::Unsupported);
#if SCN_HAS_STRING_VIEW
            MakeValueRef(typename WCharHelper<std::wstring_view&, Char>::Unsupported);
#endif
#if SCN_HAS_EXPERIMENTAL_STRING_VIEW
            MakeValueRef(typename WCharHelper<std::experimental::wstring_view&, Char>::Unsupported);
#endif
            MakeValueRef(typename WCharHelper<WStringRef, Char>::Unsupported);

            void set_string(StringRef str) {
                string.value = str.data();
                string.size = str.size();
            }

            void set_string(WStringRef str) {
                wstring.value = str.data();
                wstring.size = str.size();
            }

            // Formats an argument of a custom type, such as a user-defined class.
            template <typename T>
            static void format_custom_arg(
                void* formatter, const void* arg, void* format_str_ptr) {
                format_arg(*static_cast<Formatter*>(formatter),
                    *static_cast<const Char**>(format_str_ptr),
                    *static_cast<const T*>(arg));
            }

        public:
            MakeValueRef() {}

#define SCN_MAKE_VALUE(Type, field, TYPE) \
  MakeValueRef(Type &value_ref) { field = &value_ref; } \
  static unsigned char type(Type&) { return ArgRef::TYPE; }


            SCN_MAKE_VALUE(bool, this->value, BOOL)
            SCN_MAKE_VALUE(short, this->value, INT)
            SCN_MAKE_VALUE(unsigned short, this->value, UINT)
            SCN_MAKE_VALUE(int, this->value, INT)
            SCN_MAKE_VALUE(unsigned, this->value, UINT)

            MakeValueRef(long &value) {
                // To minimize the number of types we need to deal with, long is
                // translated either to int or to long long depending on its size.
                if (const_check(sizeof(long) == sizeof(int)))
                    this->value = reinterpret_cast<int*>(&value);
                else
                    this->value = &value;
            }
            static unsigned char type(long&) {
                return sizeof(long) == sizeof(int) ? ArgRef::INT : ArgRef::LONG_LONG;
            }

            MakeValueRef(unsigned long &value) {
                if (const_check(sizeof(unsigned long) == sizeof(unsigned)))
                    this->value = reinterpret_cast<unsigned*>(&value);
                else
                    this->value = &value;
            }
            static unsigned char type(unsigned long&) {
                return sizeof(unsigned long) == sizeof(unsigned) ?
                    ArgRef::UINT : ArgRef::ULONG_LONG;
            }

            SCN_MAKE_VALUE(LongLong, this->value, LONG_LONG)
            SCN_MAKE_VALUE(ULongLong, this->value, ULONG_LONG)
            SCN_MAKE_VALUE(float, this->value, DOUBLE)
            SCN_MAKE_VALUE(double, this->value, DOUBLE)
            SCN_MAKE_VALUE(long double, this->value, LONG_DOUBLE)
            SCN_MAKE_VALUE(signed char, this->value, INT)
            SCN_MAKE_VALUE(unsigned char, this->value, UINT)
            SCN_MAKE_VALUE(char, this->value, CHAR)

#if !defined(_MSC_VER) || defined(_NATIVE_WCHAR_T_DEFINED)
            MakeValueRef(typename WCharHelper<wchar_t, Char>::Supported &value_ref) {
                this->value = &value_ref;
            }
            static unsigned char type(wchar_t) { return ArgRef::CHAR; }
#endif

#define SCN_MAKE_STR_VALUE(Type, TYPE) \
  MakeValueRef(Type value) { set_string(value); } \
  static unsigned char type(Type&) { return ArgRef::TYPE; }

#define SCN_MAKE_CSTRING_VALUE(Type, arg, TYPE) \
  MakeValueRef(Type value_ptr) { arg.value = value_ptr; arg.size = 0; } \
  static unsigned char type(Type) { return ArgRef::TYPE; }

            SCN_MAKE_CSTRING_VALUE(char*, string, CSTRING)
            SCN_MAKE_CSTRING_VALUE(const char*, string, CSTRING)
            SCN_MAKE_CSTRING_VALUE(signed char*, sstring, CSTRING)
            SCN_MAKE_CSTRING_VALUE(unsigned char*, ustring, CSTRING)
            SCN_MAKE_STR_VALUE(std::string, STRING)
#if SCN_HAS_STRING_VIEW
            SCN_MAKE_STR_VALUE(std::string_view, STRING)
#endif
#if SCN_HAS_EXPERIMENTAL_STRING_VIEW
            SCN_MAKE_STR_VALUE(std::experimental::string_view&, STRING)
#endif
            SCN_MAKE_STR_VALUE(StringRef, STRING)
            MakeValueRef(CStringRef value) { this->value = value.c_str(); }
            static unsigned char type(CStringRef) { return ArgRef::CSTRING; }

#define SCN_MAKE_WSTR_VALUE(Type, TYPE) \
  MakeValueRef(typename WCharHelper<Type, Char>::Supported &value_ref) { \
    set_string(value_ref); \
  } \
  static unsigned char type(Type) { return ArgRef::TYPE; }

            SCN_MAKE_WSTR_VALUE(wchar_t*, WSTRING)
            SCN_MAKE_WSTR_VALUE(std::wstring&, WSTRING)
#if SCN_HAS_STRING_VIEW
            SCN_MAKE_WSTR_VALUE(std::wstring_view&, WSTRING)
#endif
#if SCN_HAS_EXPERIMENTAL_STRING_VIEW
            SCN_MAKE_WSTR_VALUE(std::experimental::wstring_view&, WSTRING)
#endif
            SCN_MAKE_WSTR_VALUE(WStringRef, WSTRING)

            SCN_MAKE_VALUE(void*, this->value, POINTER)

            //template <typename T>
            //MakeValueRef(const T& value,
            //    typename EnableIf<Not<
            //        ConvertToInt<T>::value>::value, int>::type = 0) 
            //{
            //    custom.value = &value;
            //    custom.format = &format_custom_arg<T>;
            //}

            //template <typename T>
            //static typename EnableIf<Not<ConvertToInt<T>::value>::value, uint64_t>::type
            //    type(const T&) {
            //    return Arg::CUSTOM;
            //}
        };

#undef SCN_MAKE_VALUE
#undef SCN_MAKE_VALUE_
#undef SCN_MAKE_STR_VALUE
#undef SCN_MAKE_CSTRING_VALUE
#undef SCN_MAKE_WSTR_VALUE

        template <typename Formatter>
        class MakeArgRef : public ArgRef {
        public:
            MakeArgRef() {
                type = ArgRef::NONE;
            }

            template <typename T>
            MakeArgRef(const T& value)
                : ArgRef(MakeValueRef<Formatter>(value)) {
                type = static_cast<ArgRef::Type>(MakeValueRef<Formatter>::type(value));
            }
        };

    } // namespace internal

    /** An argument references list. */
    class ArgRefList {
    public:

        // Maximum number of arguments with packed types.
        enum { MAX_PACKED_ARGS = 16 };

        typedef unsigned char ArgPackedTypes[MAX_PACKED_ARGS];

    private:
        // To reduce compiled code size per formatting function call, types of first
        // MAX_PACKED_ARGS arguments are passed in the types_ field.
        unsigned char packed_types_[MAX_PACKED_ARGS];
        typedef const unsigned char(&packed_types_ref)[MAX_PACKED_ARGS];
        union {
            // If the number of arguments is less than MAX_PACKED_ARGS, the argument
            // values are stored in values_, otherwise they are stored in args_.
            // This is done to reduce compiled code size as storing larger objects
            // may require more code (at least on x86-64) even if the same amount of
            // data is actually copied to stack. It saves ~10% on the bloat test.
            const internal::ValueRef* values_;
            const internal::ArgRef* args_;
        };

        internal::ArgRef::Type type(unsigned index) const {
            return type(packed_types_, index);
        }


    public:

        ArgRefList() {}

        ArgRefList(packed_types_ref types, const internal::ValueRef* values)
            : values_(values) {
            std::memcpy(&packed_types_[0], &types[0], sizeof(packed_types_));
        }
        ArgRefList(packed_types_ref types, const internal::ArgRef* args)
            : args_(args) {
            std::memcpy(&packed_types_[0], &types[0], sizeof(packed_types_));
        }

        const packed_types_ref types() const { return packed_types_; }

        /** Returns the argument at specified index. */
        internal::ArgRef operator[](unsigned index) const {
            using internal::ArgRef;
            ArgRef arg;
            const bool use_values = type(MAX_PACKED_ARGS - 1) == ArgRef::NONE;
            if (index < MAX_PACKED_ARGS) {
                ArgRef::Type arg_type = type(index);
                internal::ValueRef& val = arg;
                if (arg_type != ArgRef::NONE)
                    val = use_values ? values_[index] : args_[index];
                arg.type = arg_type;
                return arg;
            }
            if (use_values) {
                // The index is greater than the number of arguments that can be stored
                // in values, so return a "none" argument.
                arg.type = ArgRef::NONE;
                return arg;
            }
            for (unsigned i = MAX_PACKED_ARGS; i <= index; ++i) {
                if (args_[i].type == ArgRef::NONE)
                    return args_[i];
            }
            return args_[index];
        }

        static internal::ArgRef::Type type(packed_types_ref types, unsigned index) {
            return static_cast<internal::ArgRef::Type>(types[index]);
        }
    };

    namespace internal
    {
        // MakeUnsigned<T>::Type gives an unsigned type corresponding to integer type T.
        template <typename T>
        struct MakeUnsigned { typedef T Type; };

#define SCN_SPECIALIZE_MAKE_UNSIGNED(T, U) \
  template <> \
  struct MakeUnsigned<T> { typedef U Type; }

        SCN_SPECIALIZE_MAKE_UNSIGNED(char, unsigned char);
        SCN_SPECIALIZE_MAKE_UNSIGNED(signed char, unsigned char);
        SCN_SPECIALIZE_MAKE_UNSIGNED(short, unsigned short);
        SCN_SPECIALIZE_MAKE_UNSIGNED(int, unsigned);
        SCN_SPECIALIZE_MAKE_UNSIGNED(long, unsigned long);
        SCN_SPECIALIZE_MAKE_UNSIGNED(LongLong, ULongLong);
#undef SCN_SPECIALIZE_MAKE_UNSIGNED

        // Casts nonnegative integer to unsigned.
        template <typename Int>
        inline typename MakeUnsigned<Int>::Type to_unsigned(Int value) {
            return static_cast<typename MakeUnsigned<Int>::Type>(value);
        }

        template <std::size_t N, bool/*IsPacked*/>
        struct ArgArrayImpl;

        template <std::size_t N>
        struct ArgArrayImpl<N, true/*IsPacked*/> {
            // '+' is used to silence GCC -Wduplicated-branches warning.
            typedef ValueRef Type[N > 0 ? N : +1];

            template <typename Formatter, typename T>
            static ValueRef make(T& value) {
#ifdef __clang__
                Value result = MakeValueRef<Formatter>(value);
                // Workaround a bug in Apple LLVM version 4.2 (clang-425.0.28) of clang:
                // https://github.com/fmtlib/fmt/issues/276
                (void)result.custom.format;
                return result;
#else
                return MakeValueRef<Formatter>(value);
#endif
            }
        };

        template <std::size_t N>
        struct ArgArrayImpl<N, false/*IsPacked*/> {
            typedef ArgRef Type[N + 1]; // +1 for the list end Arg::NONE

            template <typename Formatter, typename T>
            static ArgRef make(const T& value) { return MakeArgRef<Formatter>(value); }
        };

        template<std::size_t N1, std::size_t N2>
        struct ct_less
        {
            static const bool value = N1 < N2;
        };

        template <std::size_t N>
        struct ArgArray
            : ArgArrayImpl<N, ct_less<N, ArgRefList::MAX_PACKED_ARGS>::value>
        { };

        class FormatterBase {
        private:
            ArgRefList args_;
            int next_arg_index_;

            // Returns the argument with specified index.
            ArgRef do_get_arg(unsigned arg_index, const char*& error);

        protected:
            const ArgRefList& args() const { return args_; }

            explicit FormatterBase(const ArgRefList& args) {
                args_ = args;
                next_arg_index_ = 0;
            }

            // Returns the next argument.
            ArgRef next_arg(const char*& error) {
                if (next_arg_index_ >= 0)
                    return do_get_arg(internal::to_unsigned(next_arg_index_++), error);
                error = "cannot switch from manual to automatic argument indexing";
                return ArgRef();
            }

            // Checks if manual indexing is used and returns the argument with
            // specified index.
            ArgRef get_arg(unsigned arg_index, const char*& error) {
                return check_no_auto_index(error) ? do_get_arg(arg_index, error) : ArgRef();
            }

            bool check_no_auto_index(const char*& error) {
                if (next_arg_index_ > 0) {
                    error = "cannot switch from automatic to manual argument indexing";
                    return false;
                }
                next_arg_index_ = -1;
                return true;
            }
        };
    }  // namespace internal

    template <typename Char>
    class BasicReader {

    };

/** This template formats data and writes the output to a writer. */
    template <typename CharType>
    class BasicFormatter : private internal::FormatterBase {
    public:
        /** The character type for the output. */
        typedef CharType Char;

    private:
        BasicReader<Char>& reader_;
        //internal::ArgMap<Char> map_;

        BasicFormatter(const BasicFormatter&);
        BasicFormatter& operator=(const BasicFormatter&);

        using internal::FormatterBase::get_arg;

        // Checks if manual indexing is used and returns the argument with
        // specified name.
        internal::ArgRef get_arg(BasicStringRef<Char> arg_name, const char*& error);

        // Parses argument index and returns corresponding argument.
        internal::ArgRef parse_arg_index(const Char*& s);

        // Parses argument name and returns corresponding argument.
        internal::ArgRef parse_arg_name(const Char*& s);

    public:
        /**
         \rst
         Constructs a ``BasicFormatter`` object. References to the arguments and
         the reader are stored in the formatter object so make sure they have
         appropriate lifetimes.
         \endrst
         */
        BasicFormatter(const ArgRefList& args, BasicReader<Char>& r)
            : internal::FormatterBase(args), reader_(r) {}

        /** Returns a reference to the reader associated with this formatter. */
        BasicReader<Char>& reader() { return reader_; }

        /** Formats stored arguments. */
        void format(BasicCStringRef<Char> format_str);

        // Formats a single argument and advances format_str, a format string pointer.
        const Char* format(const Char*& format_str, const internal::ArgRef& arg);
    };

    namespace internal {

        struct scan_symbols
        {
            enum type {
                begin,
                opening_braket = begin, closing_braket, 
                colon, percent, 
                string, cstring,
                decimal_integer, integer, unsigned_decimal_integer, unsigned_octal_integer, unsigned_hexadecimal_integer, binary_integer, based_integer,
                number_of_characters_read_so_far,
                floating_point,
                pointer,
                long_length_mod,
                end,
                zero
            };
        };

        template<int N, class CharT>
        struct scan_symbol;

        template<class CharT>
        bool is_scan_symbol_impl(CharT ch, const scan_symbol<scan_symbols::end, CharT>&)
        {
            return false;
        }

        template<int N, class CharT>
        bool is_scan_symbol_impl(CharT ch, const scan_symbol<N, CharT>&)
        {
            if (scan_symbol<N, CharT>::value == ch) return true;
            return is_scan_symbol_impl(ch, scan_symbol<N + 1, CharT>());
        }

        template<class CharT>
        bool is_scan_symbol(CharT ch)
        {
            return is_scan_symbol_impl(ch, scan_symbol<scan_symbols::begin, CharT>());
        }

        template<class CharT>
        bool is_scan_type_symbol_impl(CharT ch, const scan_symbol<scan_symbols::end, CharT>&)
        {
            return false;
        }

        template<int N, class CharT>
        bool is_scan_type_symbol_impl(CharT ch, const scan_symbol<N, CharT>&)
        {
            if (scan_symbol<N, CharT>::value == ch) return true;
            return is_scan_type_symbol_impl(ch, scan_symbol<N + 1, CharT>());
        }

        template<class CharT>
        bool is_scan_type_symbol(CharT ch)
        {
            return is_scan_type_symbol_impl(ch, scan_symbol<scan_symbols::string, CharT>());
        }


#define SCN_DEFINE_SCAN_SYMBOL(N, SYMBOL) \
        template<class CharT> \
        struct scan_symbol< N, CharT> { static const CharT value = CharT(SYMBOL);}

        SCN_DEFINE_SCAN_SYMBOL(scan_symbols::opening_braket,                   '{');
        SCN_DEFINE_SCAN_SYMBOL(scan_symbols::closing_braket,                   '}');
        SCN_DEFINE_SCAN_SYMBOL(scan_symbols::colon,                            ':');
        SCN_DEFINE_SCAN_SYMBOL(scan_symbols::percent,                          '%');
        SCN_DEFINE_SCAN_SYMBOL(scan_symbols::string,                           'c');
        SCN_DEFINE_SCAN_SYMBOL(scan_symbols::cstring,                          's');
        SCN_DEFINE_SCAN_SYMBOL(scan_symbols::decimal_integer,                  'd');// base 10
        SCN_DEFINE_SCAN_SYMBOL(scan_symbols::integer,                          'i');// base any
        SCN_DEFINE_SCAN_SYMBOL(scan_symbols::unsigned_decimal_integer,         'u');// base 10
        SCN_DEFINE_SCAN_SYMBOL(scan_symbols::unsigned_octal_integer,           'o');// base 8
        SCN_DEFINE_SCAN_SYMBOL(scan_symbols::unsigned_hexadecimal_integer,     'x');// base 16
        SCN_DEFINE_SCAN_SYMBOL(scan_symbols::binary_integer,                   'b');// binary
        SCN_DEFINE_SCAN_SYMBOL(scan_symbols::based_integer,                    'B');// binary
        SCN_DEFINE_SCAN_SYMBOL(scan_symbols::number_of_characters_read_so_far, 'n');// No input is consumed. Does not increment the assignment count.
        SCN_DEFINE_SCAN_SYMBOL(scan_symbols::floating_point,                   'f');
        SCN_DEFINE_SCAN_SYMBOL(scan_symbols::pointer,                          'p');
        SCN_DEFINE_SCAN_SYMBOL(scan_symbols::long_length_mod,                  'l');
        SCN_DEFINE_SCAN_SYMBOL(scan_symbols::end,                              '\0');
        SCN_DEFINE_SCAN_SYMBOL(scan_symbols::zero,                             '0');

#undef SCN_DEFINE_SCAN_SYMBOL
        
        template<class CharType, class StringType>
        struct scan_helpers_base
        {
            typedef CharType char_type;
            typedef StringType string_type;
            typedef char_type* cstring_type;
            typedef const char_type* const_cstring_type;

            static const char_type opening_braket                    = scan_symbol<scan_symbols::opening_braket                  , char_type>::value;
            static const char_type closing_braket                    = scan_symbol<scan_symbols::closing_braket                  , char_type>::value;
            static const char_type colon                             = scan_symbol<scan_symbols::colon                           , char_type>::value;
            static const char_type percent                           = scan_symbol<scan_symbols::percent                         , char_type>::value;
            static const char_type string                            = scan_symbol<scan_symbols::string                          , char_type>::value;
            static const char_type cstring                           = scan_symbol<scan_symbols::cstring                         , char_type>::value;
            static const char_type decimal_integer                   = scan_symbol<scan_symbols::decimal_integer                 , char_type>::value; // base 10
            static const char_type integer                           = scan_symbol<scan_symbols::integer                         , char_type>::value; // base any
            static const char_type unsigned_decimal_integer          = scan_symbol<scan_symbols::unsigned_decimal_integer        , char_type>::value; // base 10
            static const char_type unsigned_octal_integer            = scan_symbol<scan_symbols::unsigned_octal_integer          , char_type>::value; // base 8
            static const char_type unsigned_hexadecimal_integer      = scan_symbol<scan_symbols::unsigned_hexadecimal_integer    , char_type>::value; // base 16
            static const char_type binary_integer                    = scan_symbol<scan_symbols::binary_integer                  , char_type>::value; // binary
            static const char_type based_integer                     = scan_symbol<scan_symbols::based_integer                   , char_type>::value; // based integer
            static const char_type number_of_characters_read_so_far  = scan_symbol<scan_symbols::number_of_characters_read_so_far, char_type>::value; // No input is consumed. Does not increment the assignment count.
            static const char_type floating_point                    = scan_symbol<scan_symbols::floating_point                  , char_type>::value;
            static const char_type pointer                           = scan_symbol<scan_symbols::pointer                         , char_type>::value;
            static const char_type long_length_mod                   = scan_symbol<scan_symbols::long_length_mod                 , char_type>::value;
            static const char_type zero                              = scan_symbol<scan_symbols::zero                            , char_type>::value;

        };

        template<class>
        struct scan_helpers;

        template<>
        struct scan_helpers<CStringRef>
            : scan_helpers_base<char, std::string>
        {
        };

        template<>
        struct scan_helpers<WCStringRef>
            : scan_helpers_base<wchar_t, std::wstring>
        {
        };

    }  // namespace internal

    template<class StringRefT, class sscanf_type, class strtoul_type, class strtol_type>
    scan_result scan_impl(sscanf_type sscanf, strtoul_type strtoul, strtol_type strtol, StringRefT range_str, StringRefT format_str, scn::ArgRefList args)
    {
        typedef internal::scan_helpers< StringRefT > scan_helpers;
        typedef typename scan_helpers::cstring_type cstring_type;
        typedef typename scan_helpers::const_cstring_type const_cstring_type;
        typedef typename scan_helpers::string_type string_type;
        typedef typename scan_helpers::char_type char_type;
        struct scan_result_acquaintance : scan_result { using scan_result::make; };

        const_cstring_type param_start = 0;
        std::size_t current_arg_n = 0;
        for (const char_type *range_str_it = range_str.c_str(), *format_str_it = format_str.c_str(); *range_str_it && *format_str_it; ++format_str_it)
        {
            if (!param_start)
            {
                if (scan_helpers::opening_braket == *format_str_it)
                {
                    if (scan_helpers::opening_braket == *(format_str_it + 1))
                        ++format_str_it;
                    else
                        param_start = format_str_it;
                }
                if (param_start == format_str_it) continue;

                if (*range_str_it != *format_str_it)
                    return scan_result_acquaintance::make(
                        scan_error(scan_errc::invalid_format_string, "range string differ from format string")
                    ).forward();

                ++range_str_it;
            }
            else
            {
                if (scan_helpers::closing_braket == *format_str_it)
                {
                    if (scan_helpers::closing_braket != *(format_str_it + 1))
                    {

                        std::size_t arg_n = current_arg_n;
                        string_type sscanf_format_str(param_start + 1, format_str_it);

                        {
                            typename string_type::size_type pos = sscanf_format_str.find(':');

                            if (0 == pos)
                                sscanf_format_str[0] = scan_helpers::percent;
                            else if(!sscanf_format_str.empty())
                            {
                                const std::size_t arg_n_invalid = static_cast<std::size_t>(-1);
                                arg_n = arg_n_invalid;
                                string_type format_str(2, scan_helpers::percent);
                                format_str[1] = scan_helpers::unsigned_decimal_integer;
                                if (1 != sscanf(sscanf_format_str.substr(0, pos).c_str(), format_str.c_str(), &arg_n) || arg_n_invalid == arg_n)
                                    return scan_result_acquaintance::make(
                                        scan_error(scan_errc::invalid_format_string, "argument number is not decimal value")
                                    ).forward();

                                if (string_type::npos != pos)
                                {
                                    string_type(param_start + pos, format_str_it).swap(sscanf_format_str);
                                    sscanf_format_str[0] = scan_helpers::percent;
                                }
                                else
                                    sscanf_format_str.clear();
                            }
                        }

                        internal::ArgRef arg_ref = args[arg_n];
                        void* arg_value = arg_ref.value;
                        std::size_t arg_width = 0;

                        param_start = 0;

                        char_type format_spec_type = scan_helpers::zero;

                        if (!sscanf_format_str.empty())
                        {
                            typename string_type::size_type sscanf_format_str_size =
                                sscanf_format_str.size();

                            enum { max_format_spec_type_chars_n = 3 };

                            format_spec_type = 
                                sscanf_format_str[sscanf_format_str_size - 1];

                            bool is_scan_type_symbol = 
                                internal::is_scan_symbol(format_spec_type);

                            if (!is_scan_type_symbol && sscanf_format_str_size > 1)
                            {
                                format_spec_type = 
                                    sscanf_format_str[sscanf_format_str_size - 2];
                                is_scan_type_symbol = 
                                    internal::is_scan_symbol(format_spec_type);
                            }

                            if (!is_scan_type_symbol && sscanf_format_str_size > 2)
                            {
                                format_spec_type = 
                                    sscanf_format_str[sscanf_format_str_size - max_format_spec_type_chars_n];
                                is_scan_type_symbol = 
                                    internal::is_scan_symbol(format_spec_type);
                            }

                            if (!is_scan_type_symbol)
                            {
                                return scan_result_acquaintance::make(
                                    scan_error(scan_errc::invalid_format_string, "unsupported format specifier type")
                                ).forward();
                            }
                        }
                        else
                        {
                            sscanf_format_str = scan_helpers::percent;
                        }

                        {
                            const bool is_scan_type_symbol = 
                                internal::is_scan_type_symbol(format_spec_type);
                            char_type arg_ref_format_spec_type =
                                format_spec_type;

                            const bool format_spec_type_is_integer =
                                   format_spec_type == scan_helpers::decimal_integer
                                || format_spec_type == scan_helpers::integer
                                || format_spec_type == scan_helpers::unsigned_decimal_integer
                                || format_spec_type == scan_helpers::unsigned_octal_integer
                                || format_spec_type == scan_helpers::unsigned_hexadecimal_integer
                                || format_spec_type == scan_helpers::binary_integer
                                || format_spec_type == scan_helpers::based_integer
                                || format_spec_type == scan_helpers::number_of_characters_read_so_far;

                            const bool format_spec_type_is_floating_point =
                                format_spec_type == scan_helpers::floating_point;

                            const bool format_spec_type_is_pointer =
                                format_spec_type == scan_helpers::pointer;

                            const bool format_spec_type_is_char =
                                   format_spec_type == scan_helpers::cstring
                                || format_spec_type == scan_helpers::string;

                            const bool format_spec_type_is_not_integer =
                                format_spec_type_is_char || format_spec_type_is_pointer || format_spec_type_is_floating_point;

                            const bool format_spec_type_is_not_floating_point =
                                format_spec_type_is_integer || format_spec_type_is_pointer || format_spec_type_is_floating_point;

                            const bool format_spec_type_is_not_pointer =
                                format_spec_type_is_integer || format_spec_type_is_char || format_spec_type_is_floating_point;

                            const bool format_spec_type_is_not_char =
                                format_spec_type_is_integer || format_spec_type_is_pointer || format_spec_type_is_floating_point;

                            switch (arg_ref.type)
                            {
                            case internal::ArgRef::BOOL:
                            {
                                arg_ref_format_spec_type = scan_helpers::integer; 
                                
                                if (format_spec_type_is_not_integer)
                                    return scan_result_acquaintance::make(
                                        scan_error(scan_errc::invalid_format_string, "format specifier type does not match argument type [boolean]")
                                    ).forward();

                                break;
                            }
                            case internal::ArgRef::CHAR:
                            {
                                arg_width = 1;
                                arg_ref_format_spec_type = scan_helpers::cstring;

                                if (format_spec_type_is_not_char)
                                    return scan_result_acquaintance::make(
                                        scan_error(scan_errc::invalid_format_string, "format specifier type does not match argument type [character]")
                                    ).forward();

                                break;
                            }
                            case internal::ArgRef::CSTRING:
                            {
                                arg_value = arg_ref.string.value;
                                arg_width = arg_ref.string.size;
                                arg_ref_format_spec_type = scan_helpers::cstring;

                                if (format_spec_type_is_not_char)
                                    return scan_result_acquaintance::make(
                                        scan_error(scan_errc::invalid_format_string, "format specifier type does not match argument type [null-terminated string]")
                                    ).forward();

                                break;
                            }
                            case internal::ArgRef::WSTRING:
                            {
                                char_type &sscanf_format_str_back = 
                                    *(--sscanf_format_str.end());
                                if (is_scan_type_symbol && scan_helpers::long_length_mod != sscanf_format_str[sscanf_format_str.size() - 2])
                                {
                                    sscanf_format_str_back = scan_helpers::long_length_mod;
                                    sscanf_format_str.resize(sscanf_format_str.size() + 1, format_spec_type);
                                }
                                else if (scan_helpers::long_length_mod != sscanf_format_str_back)
                                {
                                    sscanf_format_str_back = scan_helpers::long_length_mod;
                                }
                                arg_value = arg_ref.wstring.value;
                                arg_width = arg_ref.wstring.size;
                                arg_ref_format_spec_type = scan_helpers::string;

                                if (format_spec_type_is_not_char)
                                    return scan_result_acquaintance::make(
                                        scan_error(scan_errc::invalid_format_string, "format specifier type does not match argument type [wide string]")
                                    ).forward();

                                break;
                            }
                            case internal::ArgRef::STRING:
                            {
                                arg_value = arg_ref.sstring.value;
                                arg_width = arg_ref.sstring.size;
                                arg_ref_format_spec_type = scan_helpers::string;

                                if (format_spec_type_is_not_char)
                                    return scan_result_acquaintance::make(
                                        scan_error(scan_errc::invalid_format_string, "format specifier type does not match argument type [string]")
                                    ).forward();

                                break;
                            }
                            case internal::ArgRef::DOUBLE:
                            {
                                arg_ref_format_spec_type = scan_helpers::floating_point;

                                if (format_spec_type_is_not_floating_point)
                                    return scan_result_acquaintance::make(
                                        scan_error(scan_errc::invalid_format_string, "format specifier type does not match argument type [double floating point]")
                                    ).forward();

                                break;
                            }
                            case internal::ArgRef::INT:
                            {
                                arg_ref_format_spec_type = scan_helpers::integer;

                                if (format_spec_type_is_not_integer)
                                    return scan_result_acquaintance::make(
                                        scan_error(scan_errc::invalid_format_string, "format specifier type does not match argument type [integer]")
                                    ).forward();

                                break;
                            }
                            case internal::ArgRef::UINT:
                            {
                                arg_ref_format_spec_type = scan_helpers::unsigned_decimal_integer;

                                if (format_spec_type_is_not_integer)
                                    return scan_result_acquaintance::make(
                                        scan_error(scan_errc::invalid_format_string, "format specifier type does not match argument type [unsigned integer]")
                                    ).forward();

                                break;
                            }
                            case internal::ArgRef::POINTER:
                            {
                                arg_ref_format_spec_type = scan_helpers::pointer;

                                if (format_spec_type_is_not_pointer)
                                    return scan_result_acquaintance::make(
                                        scan_error(scan_errc::invalid_format_string, "format specifier type does not match argument type [pointer]")
                                    ).forward();

                                break;
                            }

                            case internal::ArgRef::NONE:
                                return scan_result_acquaintance::make(
                                    scan_error(scan_errc::invalid_format_string, "invalid argument type")
                                ).forward();
                            default:
                                return scan_result_acquaintance::make(
                                    scan_error(scan_errc::internal, "unsupported argument type")
                                ).forward();
                            }

                            if (!is_scan_type_symbol)
                            {
                                format_spec_type = arg_ref_format_spec_type;
                                sscanf_format_str.resize(sscanf_format_str.size() + 1, format_spec_type);
                            }
                        }

                        // skipping prefixes
                        if (scan_helpers::binary_integer == format_spec_type)
                        {
                            if (scan_helpers::zero  == *range_str_it &&
                                ( scan_helpers::binary_integer  == *(range_str_it + 1) ||
                                    scan_helpers::binary_integer - 32 == *(range_str_it + 1) )
                               )
                                range_str_it += 2;
                        }
                        else if (scan_helpers::unsigned_octal_integer == format_spec_type)
                        {
                            if (scan_helpers::zero == *range_str_it &&
                                ( scan_helpers::unsigned_octal_integer  == *(range_str_it + 1) ||
                                    scan_helpers::unsigned_octal_integer - 32 == *(range_str_it + 1) )
                               )
                                range_str_it += 2;
                        }
                        else if (scan_helpers::unsigned_hexadecimal_integer == format_spec_type)
                        {
                            if (*range_str_it == scan_helpers::zero && scan_helpers::unsigned_hexadecimal_integer == *(range_str_it + 1) )
                                range_str_it += 2;
                        }

                        // scanning values
                        if (scan_helpers::binary_integer == format_spec_type)
                        {
                            errno = 0;
                            const unsigned long value =
                                strtoul(range_str_it, NULL, 2);
                            if (errno == ERANGE)
                            {
                                errno = 0;
                                return scan_result_acquaintance::make(
                                    scan_error(scan_errc::invalid_format_string, "argument number is not binary value")
                                ).forward();
                            }
                            std::memcpy(arg_value, &value, sizeof(value));
                        }
                        else if (scan_helpers::based_integer == format_spec_type)
                        {
                            int base = -1;
                            {
                                string_type format_str(2, scan_helpers::percent);
                                format_str[1] = scan_helpers::integer;

                                if (*(sscanf_format_str.c_str() + 2) == scan_helpers::zero)
                                    return scan_result_acquaintance::make(
                                        scan_error(scan_errc::invalid_format_string, "argument base number cannot start with leading zero")
                                    ).forward();

                                if (1 != sscanf(sscanf_format_str.c_str() + 2, format_str.c_str(), &base) || -1 == base)
                                    return scan_result_acquaintance::make(
                                        scan_error(scan_errc::invalid_format_string, "argument base number is not decimal value")
                                    ).forward();

                                if (base > 36 || base == 1)
                                    return scan_result_acquaintance::make(
                                        scan_error(scan_errc::invalid_format_string, "argument base number cannot be 1 or over 36")
                                    ).forward();
                            }

                            errno = 0;
                            const long value =
                                strtol(range_str_it, NULL, base);
                            if (errno == ERANGE)
                            {
                                errno = 0;
                                return scan_result_acquaintance::make(
                                    scan_error(scan_errc::invalid_format_string, "argument number is not value of long type")
                                ).forward();
                            }
                            std::memcpy(arg_value, &value, sizeof(value));
                        }
                        else if (scan_helpers::number_of_characters_read_so_far == format_spec_type)
                        {
                            if (0 != sscanf(range_str_it, sscanf_format_str.c_str(), arg_value))
                                return scan_result_acquaintance::make(
                                    scan_error(scan_errc::invalid_format_string, "cannot scan number of characters read so far")
                                ).forward();
                        }
                        else
                        {
                            const unsigned int unsigned_int_invalid = static_cast<unsigned int>(-1);
                            unsigned int num_of_characters_read_so_far = unsigned_int_invalid;
                            
                            sscanf_format_str.resize(sscanf_format_str.size() + 2, scan_helpers::percent);
                            char_type &sscanf_format_str_back = *(--sscanf_format_str.end());
                            sscanf_format_str_back = scan_helpers::number_of_characters_read_so_far;

                            if (arg_width)
                            {
                                unsigned int defined_arg_width = unsigned_int_invalid;
                                string_type format_str(2, scan_helpers::percent);
                                format_str[1] = scan_helpers::integer;
                                sscanf(sscanf_format_str.c_str(), format_str.c_str(), &defined_arg_width);

                                if (defined_arg_width != unsigned_int_invalid)
                                {
                                    if (arg_width < defined_arg_width)
                                        return scan_result_acquaintance::make(
                                            scan_error(scan_errc::invalid_format_string, "defined format specifier width exceeds actual argument size")
                                        ).forward();
                                }
                            }

                            if (1 != sscanf(range_str_it, sscanf_format_str.c_str(), arg_value, &num_of_characters_read_so_far) ||
                                unsigned_int_invalid == num_of_characters_read_so_far)
                                return scan_result_acquaintance::make(
                                    scan_error(scan_errc::invalid_format_string, "cannot scan argument")
                                ).forward();

                            if (arg_width && num_of_characters_read_so_far > arg_width)
                                return scan_result_acquaintance::make(
                                    scan_error(scan_errc::buffer_overflow, "number of characters read exceeds actual argument size")
                                ).forward();

                            range_str_it += num_of_characters_read_so_far;
                        }

                    }
                }
            }
        }
        
        return scan_result_acquaintance::make(scan_error());
    }


    scan_result scan(scn::CStringRef range_str, scn::CStringRef format_str, scn::ArgRefList args)
    {
        return scan_impl(std::sscanf, std::strtoul, std::strtol, range_str, format_str, args).forward();
    }

    scan_result scan(scn::WCStringRef range_str, scn::WCStringRef format_str, scn::ArgRefList args)
    {
        return scan_impl(std::swscanf, std::wcstoul, std::wcstol, range_str, format_str, args).forward();
    }


#define  SCN_DEFINE_2_COMMA_SEPARATED_PARAMS_N(param) param(0), param(1)
#define  SCN_DEFINE_3_COMMA_SEPARATED_PARAMS_N(param) param(0), param(1), param(2)
#define  SCN_DEFINE_4_COMMA_SEPARATED_PARAMS_N(param) param(0), param(1), param(2), param(3)
#define  SCN_DEFINE_5_COMMA_SEPARATED_PARAMS_N(param) param(0), param(1), param(2), param(3), param(4)
#define  SCN_DEFINE_6_COMMA_SEPARATED_PARAMS_N(param) param(0), param(1), param(2), param(3), param(4), param(5)
#define  SCN_DEFINE_7_COMMA_SEPARATED_PARAMS_N(param) param(0), param(1), param(2), param(3), param(4), param(5), param(6)
#define  SCN_DEFINE_8_COMMA_SEPARATED_PARAMS_N(param) param(0), param(1), param(2), param(3), param(4), param(5), param(6), param(7)
#define  SCN_DEFINE_9_COMMA_SEPARATED_PARAMS_N(param) SCN_DEFINE_8_COMMA_SEPARATED_PARAMS_N(param), param(8)
#define SCN_DEFINE_10_COMMA_SEPARATED_PARAMS_N(param) SCN_DEFINE_8_COMMA_SEPARATED_PARAMS_N(param), param(8), param(9)
#define SCN_DEFINE_11_COMMA_SEPARATED_PARAMS_N(param) SCN_DEFINE_8_COMMA_SEPARATED_PARAMS_N(param), param(8), param(9), param(10)
#define SCN_DEFINE_12_COMMA_SEPARATED_PARAMS_N(param) SCN_DEFINE_8_COMMA_SEPARATED_PARAMS_N(param), param(8), param(9), param(10), param(11)
#define SCN_DEFINE_13_COMMA_SEPARATED_PARAMS_N(param) SCN_DEFINE_8_COMMA_SEPARATED_PARAMS_N(param), param(8), param(9), param(10), param(11), param(12)
#define SCN_DEFINE_14_COMMA_SEPARATED_PARAMS_N(param) SCN_DEFINE_8_COMMA_SEPARATED_PARAMS_N(param), param(8), param(9), param(10), param(11), param(12), param(13)
#define SCN_DEFINE_15_COMMA_SEPARATED_PARAMS_N(param) SCN_DEFINE_8_COMMA_SEPARATED_PARAMS_N(param), param(8), param(9), param(10), param(11), param(12), param(13), param(14)
#define SCN_DEFINE_16_COMMA_SEPARATED_PARAMS_N(param) SCN_DEFINE_8_COMMA_SEPARATED_PARAMS_N(param), param(8), param(9), param(10), param(11), param(12), param(13), param(14), param(15)

    template<class Arg0T>
    scan_result scan(scn::CStringRef range_str, scn::CStringRef format_str, Arg0T &arg0)
    {
        typedef internal::ArgArray<1> ArgArray;
        typedef BasicFormatter<char> Formatter;
        ArgArray::Type arg_array = {
            ArgArray::make<Formatter>(arg0)
        };
        ArgRefList::ArgPackedTypes arg_packed_types = {
            internal::MakeValueRef<Formatter>::type(arg0)
        };
        ArgRefList args(arg_packed_types, arg_array);
        return scan(range_str, format_str, args).forward();
    }

    template<class Arg0T>
    scan_result scan(scn::WCStringRef range_str, scn::WCStringRef format_str, Arg0T &arg0)
    {
        typedef internal::ArgArray<1> ArgArray;
        typedef BasicFormatter<wchar_t> Formatter;
        ArgArray::Type arg_array = {
            ArgArray::make<Formatter>(arg0)
        };
        ArgRefList::ArgPackedTypes arg_packed_types = {
            internal::MakeValueRef<Formatter>::type(arg0)
        };
        ArgRefList args(arg_packed_types, arg_array);
        return scan(range_str, format_str, args).forward();
    }

    template<class Arg0T>
    scan_result scan(scn::CStringRef range_str, scn::CStringRef format_str, Arg0T *arg0)
    {
        typedef internal::ArgArray<1> ArgArray;
        typedef BasicFormatter<char> Formatter;
        ArgArray::Type arg_array = {
            ArgArray::make<Formatter>(arg0)
        };
        ArgRefList::ArgPackedTypes arg_packed_types = {
            internal::MakeValueRef<Formatter>::type(arg0)
        };
        ArgRefList args(arg_packed_types, arg_array);
        return scan(range_str, format_str, args).forward();
    }

    template<class Arg0T>
    scan_result scan(scn::WCStringRef range_str, scn::WCStringRef format_str, Arg0T *arg0)
    {
        typedef internal::ArgArray<1> ArgArray;
        typedef BasicFormatter<wchar_t> Formatter;
        ArgArray::Type arg_array = {
            ArgArray::make<Formatter>(arg0)
        };
        ArgRefList::ArgPackedTypes arg_packed_types = {
            internal::MakeValueRef<Formatter>::type(arg0)
        };
        ArgRefList args(arg_packed_types, arg_array);
        return scan(range_str, format_str, args).forward();
    }


#define SCN_TMPL_ARG_TYPE(n) class Arg##n##T
#define SCN_ARG_ARRAY_MEMBER(n) ArgArray::make<Formatter>(arg##n)
#define SCN_ARG_PACKED_TYPES_MEMBER(n) internal::MakeValueRef<Formatter>::type(arg##n)

#define SCN_SCAN_FUNCTION(string_type, char_type, n) \
    template<SCN_DEFINE_##n##_COMMA_SEPARATED_PARAMS_N(SCN_TMPL_ARG_TYPE)>          \
    scan_result scan(string_type range_str, string_type format_str,                 \
        SCN_DEFINE_##n##_COMMA_SEPARATED_PARAMS_N(SCN_ARG_DEFINITION))              \
    {                                                                               \
        typedef internal::ArgArray< n > ArgArray;                                   \
        typedef BasicFormatter<char_type> Formatter;                                \
        ArgArray::Type arg_array = {                                                \
            SCN_DEFINE_##n##_COMMA_SEPARATED_PARAMS_N(SCN_ARG_ARRAY_MEMBER)         \
        };                                                                          \
        ArgRefList::ArgPackedTypes arg_packed_types = {                             \
            SCN_DEFINE_##n##_COMMA_SEPARATED_PARAMS_N(SCN_ARG_PACKED_TYPES_MEMBER)  \
        };                                                                          \
        ArgRefList args(arg_packed_types, arg_array);                               \
        return scan(range_str, format_str, args).forward();                         \
    }

#define SCN_SCAN_FUNCTIONS(n) \
    SCN_SCAN_FUNCTION(scn::CStringRef, char, n)     \
    SCN_SCAN_FUNCTION(scn::WCStringRef, wchar_t, n) \

#define SCN_SCAN_FUNCTIONS_SET \
    SCN_SCAN_FUNCTIONS(2) \
    SCN_SCAN_FUNCTIONS(3) \
    SCN_SCAN_FUNCTIONS(4) \
    SCN_SCAN_FUNCTIONS(5) \
    SCN_SCAN_FUNCTIONS(6) \
    SCN_SCAN_FUNCTIONS(7) \
    SCN_SCAN_FUNCTIONS(8) \
    SCN_SCAN_FUNCTIONS(9) \
    SCN_SCAN_FUNCTIONS(10) \
    SCN_SCAN_FUNCTIONS(11) \
    SCN_SCAN_FUNCTIONS(12) \
    SCN_SCAN_FUNCTIONS(13) \
    SCN_SCAN_FUNCTIONS(14) \
    SCN_SCAN_FUNCTIONS(15) \
    SCN_SCAN_FUNCTIONS(16)


#define SCN_ARG_DEFINITION(n) Arg##n##T &arg##n
    SCN_SCAN_FUNCTIONS_SET
#undef SCN_ARG_DEFINITION
#define SCN_ARG_DEFINITION(n) Arg##n##T *arg##n
        SCN_SCAN_FUNCTIONS_SET
#undef SCN_ARG_DEFINITION

#undef SCN_SCAN_FUNCTIONS
#undef SCN_SCAN_FUNCTION
#undef SCN_TMPL_ARG_TYPE
#undef SCN_ARG_ARRAY_MEMBER
#undef SCN_ARG_PACKED_TYPES_MEMBER

#undef SCN_DEFINE_2_COMMA_SEPARATED_PARAMS_N 
#undef SCN_DEFINE_3_COMMA_SEPARATED_PARAMS_N 
#undef SCN_DEFINE_4_COMMA_SEPARATED_PARAMS_N 
#undef SCN_DEFINE_5_COMMA_SEPARATED_PARAMS_N 
#undef SCN_DEFINE_6_COMMA_SEPARATED_PARAMS_N 
#undef SCN_DEFINE_7_COMMA_SEPARATED_PARAMS_N 
#undef SCN_DEFINE_8_COMMA_SEPARATED_PARAMS_N 
#undef SCN_DEFINE_9_COMMA_SEPARATED_PARAMS_N 
#undef SCN_DEFINE_10_COMMA_SEPARATED_PARAMS_N
#undef SCN_DEFINE_11_COMMA_SEPARATED_PARAMS_N
#undef SCN_DEFINE_12_COMMA_SEPARATED_PARAMS_N
#undef SCN_DEFINE_13_COMMA_SEPARATED_PARAMS_N
#undef SCN_DEFINE_14_COMMA_SEPARATED_PARAMS_N
#undef SCN_DEFINE_15_COMMA_SEPARATED_PARAMS_N
#undef SCN_DEFINE_16_COMMA_SEPARATED_PARAMS_N
}

#endif // SCN_SCAN_H_

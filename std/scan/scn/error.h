#ifndef SCN_ERROR_H_
#define SCN_ERROR_H_

#include <string>
#include <stdexcept>    // std::runtime_error
//#include <system_error> // std::error_category, std::error_code, std::system_error

namespace scn
{
    template<class ErrorCodeEnum>
    struct error_category
        // : std::error_category
    {
    protected:

        virtual std::string message(int ev) const
        {
            return message(static_cast<ErrorCodeEnum>(ev));
        }

    public:

        typedef ErrorCodeEnum enum_type;

        error_category() throw()
        {}

        virtual ~error_category() throw()
        {}

        virtual const char* name() const throw() = 0;

        // We need two different virtual functions here, one returning a
        // COW string and one returning an SSO string. Their positions in the
        // vtable must be consistent for dynamic dispatch to work, but which one
        // the name "message()" finds depends on which ABI the caller is using.


        virtual std::string message(ErrorCodeEnum code) const = 0;


    public:

        inline bool operator<(const error_category& other) const throw()
        {
            return std::less<const error_category*>()(this, &other);
        }

        inline bool operator==(const error_category& other) const throw()
        {
            return this == &other;
        }

        inline bool operator!=(const error_category& other) const throw()
        {
            return this != &other;
        }

    private:
        error_category(const error_category&);
        error_category& operator=(const error_category&);
    };

    template<class ErrorCodeEnum>
    struct error_code
        // : std::error_code
    {
    public:
        typedef ErrorCodeEnum enum_type;
        typedef error_category<ErrorCodeEnum> category_type;

    private:

        ErrorCodeEnum _value;
        const category_type* _cat;

        typedef void(*unspecified_bool_type)();
        static void unspecified_bool_true() {}

        static const category_type& unspecified_error_category() {
            struct default_error_category
                : error_category<ErrorCodeEnum>
            {
                std::string message(ErrorCodeEnum) const {
                    return "unspecified scn error code";
                }
                const char* name() const throw() { return "unspecified scn error category"; }
            };
            static default_error_category cat;
            return cat;
        }

    public:
        error_code() throw() :
            _value(),
            _cat(&unspecified_error_category())
        { }

        error_code(ErrorCodeEnum val, const category_type& cat) throw() :
            _value(val),
            _cat(&cat)
        { }

        error_code(const ErrorCodeEnum& val) throw()
            : _value(val)
        {
            *this = val;
        }

        void assign(ErrorCodeEnum val, const category_type& cat) throw()
        {
            _value = val;
            _cat = &cat;
        }

        void clear() throw()
        {
            _value = ErrorCodeEnum();
            _cat = &unspecified_error_category();
        }

        error_code& operator=(const ErrorCodeEnum& val) throw()
        {
            return (*this = make_error_code(val));
        }

        ErrorCodeEnum value() const throw() { return _value; }

        const category_type& category() const { return *_cat; }

        std::string message() const
        {
            return category().message(value());
        }

        operator unspecified_bool_type() const  throw() // true if error
        {
            const ErrorCodeEnum no_error = ErrorCodeEnum();
            return _value == no_error ? 0 : unspecified_bool_true;
        }

        bool operator!() const  throw() // true if no error
        {
            const ErrorCodeEnum no_error = ErrorCodeEnum();
            const bool result = (_value == no_error);
            return result;
        }
    };

    template<class ErrorCodeEnum>
    class error
        : public std::runtime_error
        // , std::system_error
    {
    public:
        typedef ErrorCodeEnum enum_type;
        typedef error_code<ErrorCodeEnum> code_type;
        
    private:
        code_type     _code;

    public:
        error(error_code<ErrorCodeEnum> ecode = ErrorCodeEnum())
            : std::runtime_error(ecode.message())
            , _code(ecode)
        {}

        error(error_code<ErrorCodeEnum> ecode, const std::string& what)
            : std::runtime_error(what + ": " + ecode.message())
            , _code(ecode)
        {}

        error(error_code<ErrorCodeEnum> ecode, const char* what)
            : std::runtime_error(std::string(what) + (": " + ecode.message()))
            , _code(ecode)
        {}

        error(ErrorCodeEnum val, const error_category<ErrorCodeEnum>& ecat, const char* what)
            : std::runtime_error(std::string(what) + (": " + error_code<ErrorCodeEnum>(val, ecat).message()))
            , _code(val, ecat)
        {}

        error(ErrorCodeEnum val, const error_category<ErrorCodeEnum>& ecat)
            : std::runtime_error(error_code<ErrorCodeEnum>(val, ecat).message())
            , _code(val, ecat)
        {}

        error(ErrorCodeEnum val, const error_category<ErrorCodeEnum>& ecat, const std::string& what)
            : std::runtime_error(what + ": " + error_code<ErrorCodeEnum>(val, ecat).message())
            , _code(val, ecat)
        {}

        const code_type& code() const throw() { return _code; }
    };

    template<class ErrorT>
    class result
    {
        struct rvalue_reference: result {};
        typedef void(*unspecified_bool_type)();
        static void unspecified_bool_true() {}

    public:
        typedef ErrorT error_type;

        result(rvalue_reference& other)
            : internal(reinterpret_cast<const result&>(other).internal)
        {
            reinterpret_cast<result&>(other).internal.throws = false;
        }

        result(const result& other)
            : internal(other.internal)
        {
            other.internal.throws = false;
            internal.throws = false;
        }

        result& operator=(const result& other)
        {
            internal = other.internal;
            other.internal.throws = false;
            internal.throws = false;

            return *this;
        }

        ~result() {
            struct lambdas {
                typedef error_type error_t;
                static
                void throw_error(error_t internal_error) { throw(internal_error); }
            };
            if (internal.throws)
                lambdas::throw_error(internal.error);
        }

        rvalue_reference& forward() {
            return reinterpret_cast<rvalue_reference&>(*this);
        }

        void discard() { 
            internal.throws = false; 
        }

        bool discarded() const {
            return !internal.throws; 
        }

        const error_type& error() const {
            return internal.error;
        }

        bool operator!() const {
            return !!internal.error.code();
        }

        operator unspecified_bool_type() const  throw() // true if success
        {
            return !internal.error.code() ? 0 : unspecified_bool_true;
        }

    private:
        struct internal_type {

            internal_type(bool throws = true) 
                : throws(throws) {}

            internal_type(bool throws, const error_type& error)
                : throws(throws), error(error) {}
            bool throws;
            error_type error;
        } mutable internal;

        result(bool throws, const error_type& error)
            : internal(throws, error)
        { }

    protected:
        static result make(const error_type& error)
        {
            return result(!!error.code(), error).forward();
        }
    };

} // namespace scn

#endif // SCN_ERROR_H_

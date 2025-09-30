
#ifndef SCRIPTSTD_RATIO_IMPL_HPP
#define SCRIPTSTD_RATIO_IMPL_HPP

#ifndef ANGELSCRIPT_H 
// Avoid having to inform include path if header is already include before
#include <angelscript.h>
#endif

#include <memory>
#include <cassert>
#include <exception>
#include <stdexcept>
#include <string>
#include <cstring>
#include <climits>
#include <ctime>


BEGIN_AS_NAMESPACE

namespace astd {

    
    typedef asINT64  asINTMAX;
    typedef asQWORD  asUINTMAX;

    struct ratio {
        const asINTMAX& num() const { return internal_num; };
        const asINTMAX& den() const { return internal_den; };

        void swap(ratio& other) throw() {
            asINTMAX tmp = internal_num;
            { internal_num = other.internal_num; other.internal_num = tmp; }
            tmp = internal_den;
            { internal_den = other.internal_den;  other.internal_den = tmp; }
        }

        bool operator==(const ratio& other) const throw() {
            if (0 == internal_den)
            {
                if (other.internal_den == 0) return true;
                return false;
            }

            if (0 == other.internal_den)
            {
                if (internal_den == 0) return true;
                return false;
            }

            return internal_num % internal_den ==
                other.internal_num % other.internal_den;
        }

        ratio(const asINTMAX& num, const asINTMAX& den)
            : internal_num(num), internal_den(den) {}

    private:
        asINTMAX internal_num, internal_den;
    };

    template<asINTMAX Num = 1, asINTMAX Den = 1>
    struct ratio_ct
        : ratio
    {
        ratio_ct() : ratio(Num, Den) {}
    };

    namespace detail
    {
        template<int MaxBitsN>
        struct ratio_ct_predefined_impl:
            ratio_ct_predefined_impl<MaxBitsN - 1>
        { };

        template<bool>
        struct detail_10_pow_01
        {
            static const asUINTMAX value = static_cast<asUINTMAX>(10);
        };

        template<>
        struct detail_10_pow_01<true>
        {
            static const asUINTMAX value = static_cast<asUINTMAX>(1);
        };

        enum {
            detail_10_pow_01_bit_n = 4,
            detail_10_pow_02_bit_n = 7,
            detail_10_pow_03_bit_n = 10,
            detail_10_pow_06_bit_n = 20,
            detail_10_pow_09_bit_n = 30,
            detail_10_pow_12_bit_n = 40,
            detail_10_pow_15_bit_n = 50,
            detail_10_pow_18_bit_n = 60,
            detail_10_pow_21_bit_n = 70,
            detail_10_pow_24_bit_n = 80
        };

        #define ASTD_10_POW(cond) detail_10_pow_01<(cond)>::value
        #define ASTD_INTMAX_BIT_COUNT (sizeof(asINTMAX) * CHAR_BIT)
        #define ASTD_10_POW_IMPL(pow_n) ASTD_10_POW(detail_10_pow_##pow_n##_bit_n > ASTD_INTMAX_BIT_COUNT)
        #define ASTD_10_POW_01_IMPL(pow_n) (ASTD_10_POW_IMPL(pow_n))
        #define ASTD_10_POW_02_IMPL(pow_n) (ASTD_10_POW_01_IMPL(pow_n) * ASTD_10_POW_01_IMPL(pow_n))
        #define ASTD_10_POW_03_IMPL(pow_n) (ASTD_10_POW_01_IMPL(pow_n) * ASTD_10_POW_02_IMPL(pow_n))
        #define ASTD_10_POW_06_IMPL(pow_n) (ASTD_10_POW_03_IMPL(pow_n) * ASTD_10_POW_03_IMPL(pow_n))
        #define ASTD_10_POW_09_IMPL(pow_n) (ASTD_10_POW_03_IMPL(pow_n) * ASTD_10_POW_06_IMPL(pow_n))
        #define ASTD_10_POW_12_IMPL(pow_n) (ASTD_10_POW_06_IMPL(pow_n) * ASTD_10_POW_06_IMPL(pow_n))
        #define ASTD_10_POW_15_IMPL(pow_n) (ASTD_10_POW_06_IMPL(pow_n) * ASTD_10_POW_09_IMPL(pow_n))
        #define ASTD_10_POW_18_IMPL(pow_n) (ASTD_10_POW_09_IMPL(pow_n) * ASTD_10_POW_09_IMPL(pow_n))
        #define ASTD_10_POW_21_IMPL(pow_n) (ASTD_10_POW_09_IMPL(pow_n) * ASTD_10_POW_12_IMPL(pow_n))
        #define ASTD_10_POW_24_IMPL(pow_n) (ASTD_10_POW_12_IMPL(pow_n) * ASTD_10_POW_12_IMPL(pow_n))

        #define ASTD_10_POW_01 ASTD_10_POW_01_IMPL(01)
        #define ASTD_10_POW_02 ASTD_10_POW_02_IMPL(02)
        #define ASTD_10_POW_03 ASTD_10_POW_03_IMPL(03)
        #define ASTD_10_POW_06 ASTD_10_POW_06_IMPL(06)
        #define ASTD_10_POW_09 ASTD_10_POW_09_IMPL(09)
        #define ASTD_10_POW_12 ASTD_10_POW_12_IMPL(12)
        #define ASTD_10_POW_15 ASTD_10_POW_15_IMPL(15)
        #define ASTD_10_POW_18 ASTD_10_POW_18_IMPL(18)
        #define ASTD_10_POW_21 ASTD_10_POW_21_IMPL(21)
        #define ASTD_10_POW_24 ASTD_10_POW_24_IMPL(24)

        

        template<>
        struct ratio_ct_predefined_impl<0>;

        template<>
        struct ratio_ct_predefined_impl<detail_10_pow_01_bit_n>;

        template<>
        struct ratio_ct_predefined_impl<detail_10_pow_02_bit_n>
        {
            struct type_cannot_be_implemented;

            typedef type_cannot_be_implemented yocto;
            typedef type_cannot_be_implemented zepto;
            typedef type_cannot_be_implemented atto;
            typedef type_cannot_be_implemented femto;
            typedef type_cannot_be_implemented pico;
            typedef type_cannot_be_implemented nano;
            typedef type_cannot_be_implemented micro;
            typedef type_cannot_be_implemented milli;
            typedef ratio_ct<static_cast<asINTMAX>(1), static_cast<asINTMAX>(ASTD_10_POW_02)> centi;
            typedef ratio_ct<static_cast<asINTMAX>(1), static_cast<asINTMAX>(ASTD_10_POW_01)> deci;
            typedef ratio_ct<static_cast<asINTMAX>(ASTD_10_POW_01), static_cast<asINTMAX>(1)> deca;
            typedef ratio_ct<static_cast<asINTMAX>(ASTD_10_POW_02), static_cast<asINTMAX>(1)> hecto;
            typedef type_cannot_be_implemented kilo;
            typedef type_cannot_be_implemented mega;
            typedef type_cannot_be_implemented giga;
            typedef type_cannot_be_implemented tera;
            typedef type_cannot_be_implemented peta;
            typedef type_cannot_be_implemented exa;
            typedef type_cannot_be_implemented zetta;
            typedef type_cannot_be_implemented yotta;
        };

        template<>
        struct ratio_ct_predefined_impl<detail_10_pow_03_bit_n>:
            ratio_ct_predefined_impl<detail_10_pow_02_bit_n>
        {
            typedef ratio_ct<static_cast<asINTMAX>(1), static_cast<asINTMAX>(ASTD_10_POW_03)> milli;
            typedef ratio_ct<static_cast<asINTMAX>(ASTD_10_POW_03), static_cast<asINTMAX>(1)> kilo;
        };

        template<>
        struct ratio_ct_predefined_impl<detail_10_pow_06_bit_n>:
            ratio_ct_predefined_impl<detail_10_pow_03_bit_n>
        {
            typedef ratio_ct<static_cast<asINTMAX>(1), static_cast<asINTMAX>(ASTD_10_POW_06)> micro;
            typedef ratio_ct<static_cast<asINTMAX>(ASTD_10_POW_06), static_cast<asINTMAX>(1)> mega;
        };

        template<>
        struct ratio_ct_predefined_impl<detail_10_pow_09_bit_n>:
            ratio_ct_predefined_impl<detail_10_pow_06_bit_n>
        {
            typedef ratio_ct<static_cast<asINTMAX>(1), static_cast<asINTMAX>(ASTD_10_POW_09)> nano;
            typedef ratio_ct<static_cast<asINTMAX>(ASTD_10_POW_09), static_cast<asINTMAX>(1)> giga;
        };

        template<>
        struct ratio_ct_predefined_impl<detail_10_pow_12_bit_n>:
            ratio_ct_predefined_impl<detail_10_pow_09_bit_n>
        {
            typedef ratio_ct<static_cast<asINTMAX>(1), static_cast<asINTMAX>(ASTD_10_POW_12)> pico;
            typedef ratio_ct<static_cast<asINTMAX>(ASTD_10_POW_12), static_cast<asINTMAX>(1)> tera;
        };

        template<>
        struct ratio_ct_predefined_impl<detail_10_pow_15_bit_n>:
            ratio_ct_predefined_impl<detail_10_pow_12_bit_n>
        {
            typedef ratio_ct<static_cast<asINTMAX>(1), static_cast<asINTMAX>(ASTD_10_POW_15)> femto;
            typedef ratio_ct<static_cast<asINTMAX>(ASTD_10_POW_15), static_cast<asINTMAX>(1)> peta;
        };

        template<>
        struct ratio_ct_predefined_impl<detail_10_pow_18_bit_n>:
            ratio_ct_predefined_impl<detail_10_pow_15_bit_n>
        {
            typedef ratio_ct<static_cast<asINTMAX>(1), static_cast<asINTMAX>(ASTD_10_POW_18)> atto;
            typedef ratio_ct<static_cast<asINTMAX>(ASTD_10_POW_18), static_cast<asINTMAX>(1)> exa;
        };

        template<>
        struct ratio_ct_predefined_impl<detail_10_pow_21_bit_n>:
            ratio_ct_predefined_impl<detail_10_pow_18_bit_n>
        {
            typedef ratio_ct<static_cast<asINTMAX>(1), static_cast<asINTMAX>(ASTD_10_POW_21)> zepto;
            typedef ratio_ct<static_cast<asINTMAX>(ASTD_10_POW_21), static_cast<asINTMAX>(1)> zetta;
        };

        template<>
        struct ratio_ct_predefined_impl<detail_10_pow_24_bit_n>:
            ratio_ct_predefined_impl<detail_10_pow_21_bit_n>
        {
            typedef ratio_ct<static_cast<asINTMAX>(1), static_cast<asINTMAX>(ASTD_10_POW_24)> yocto;
            typedef ratio_ct<static_cast<asINTMAX>(ASTD_10_POW_24), static_cast<asINTMAX>(1)> yotta;
        };

        #undef ASTD_10_POW
        #undef ASTD_INTMAX_BIT_COUNT
        #undef ASTD_10_POW_IMPL

        #undef ASTD_10_POW_01_IMPL
        #undef ASTD_10_POW_02_IMPL
        #undef ASTD_10_POW_03_IMPL
        #undef ASTD_10_POW_06_IMPL
        #undef ASTD_10_POW_09_IMPL
        #undef ASTD_10_POW_12_IMPL
        #undef ASTD_10_POW_15_IMPL
        #undef ASTD_10_POW_18_IMPL
        #undef ASTD_10_POW_21_IMPL
        #undef ASTD_10_POW_24_IMPL

        #undef ASTD_10_POW_01
        #undef ASTD_10_POW_02
        #undef ASTD_10_POW_03
        #undef ASTD_10_POW_06
        #undef ASTD_10_POW_09
        #undef ASTD_10_POW_12
        #undef ASTD_10_POW_15
        #undef ASTD_10_POW_18
        #undef ASTD_10_POW_21
        #undef ASTD_10_POW_24

        struct ratio_ct_predefined:
            ratio_ct_predefined_impl<(sizeof(asINTMAX) * CHAR_BIT)>
        { };
    } // namespace detail

    typedef detail::ratio_ct_predefined::yocto     yocto;
    typedef detail::ratio_ct_predefined::zepto     zepto;
    typedef detail::ratio_ct_predefined::atto      atto;
    typedef detail::ratio_ct_predefined::femto     femto;
    typedef detail::ratio_ct_predefined::pico      pico;
    typedef detail::ratio_ct_predefined::nano      nano;
    typedef detail::ratio_ct_predefined::micro     micro;
    typedef detail::ratio_ct_predefined::milli     milli;
    typedef detail::ratio_ct_predefined::centi     centi;
    typedef detail::ratio_ct_predefined::deci      deci;
    typedef detail::ratio_ct_predefined::deca      deca;
    typedef detail::ratio_ct_predefined::hecto     hecto;
    typedef detail::ratio_ct_predefined::kilo      kilo;
    typedef detail::ratio_ct_predefined::mega      mega;
    typedef detail::ratio_ct_predefined::giga      giga;
    typedef detail::ratio_ct_predefined::tera      tera;
    typedef detail::ratio_ct_predefined::peta      peta;
    typedef detail::ratio_ct_predefined::exa       exa;
    typedef detail::ratio_ct_predefined::zetta     zetta;
    typedef detail::ratio_ct_predefined::yotta     yotta;

}

namespace astd {
    namespace detail {
        static inline
        asINTMAX naive_gcd(asINTMAX n1, asINTMAX n2)
        {
            asINTMAX tmp;
            while (n2 != 0) {
                tmp = n1;
                n1 = n2;
                n2 = tmp % n2;
            }
            return n1;
        }

        static ratio ratio_multiply(const ratio &r1, const ratio &r2)
        {
            const asINTMAX gcd1 =
                naive_gcd(r1.num(), r2.den());
            const asINTMAX gcd2 =
                naive_gcd(r2.num(), r1.den());

            ratio result(
                  (asINTMAX(r1.num()) / gcd1) * (asINTMAX(r2.num()) / gcd2) // num
                , (asINTMAX(r1.den()) / gcd2) * (asINTMAX(r2.den()) / gcd1) // den
            );

            return result;
        }

        static ratio ratio_divide(const ratio& r1, const ratio& r2)
        {
            const ratio r2_inv(r2.den(), r2.num());
            return ratio_multiply(r1, r2_inv);
        }
    }
}

END_AS_NAMESPACE

#endif // SCRIPTSTD_RATIO_IMPL_HPP


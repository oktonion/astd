
#include "scriptstd_chrono.h"

#include "./../ratio/scriptstd_ratio.impl.hpp"

#include <memory>
#include <cassert>
#include <exception>
#include <stdexcept>
#include <string>
#include <cstring>
#include <climits>
#include <ctime>
#include <cstdio> // std::sprintf
#include <cstdlib> // std::abort

#include "scriptstd_chrono_os.h"

BEGIN_AS_NAMESPACE


namespace astd {

    namespace os {
        namespace system_time {
            static const bool has_nano = NULL != get_system_time[get_time_nanosec_callback];
            static const bool has_milli = NULL != get_system_time[get_time_millisec_callback];
            static const bool has_micro = NULL != get_system_time[get_time_microsec_callback];
            static const bool has_seconds = NULL != get_system_time[get_time_seconds_callback];
        }
        namespace steady_time {
            static const bool has_nano = NULL != get_steady_time[get_time_nanosec_callback];
            static const bool has_milli = NULL != get_steady_time[get_time_millisec_callback];
            static const bool has_micro = NULL != get_steady_time[get_time_microsec_callback];
            static const bool has_seconds = NULL != get_steady_time[get_time_seconds_callback];
        }
    }

    namespace {
        struct namespace_cstr {
            const char *cstr;
            explicit namespace_cstr(const char* cstr):cstr(cstr) {}
        };
        struct type_cstr {
            const char* cstr;
            explicit type_cstr(const char* cstr) :cstr(cstr) {}
        };
        struct subtype_cstr {
            const char* cstr;
            explicit subtype_cstr(const char* cstr) :cstr(cstr) {}
        };

        struct asType {
            asITypeInfo* type_info;
            int type_id;
            asType() : type_info(0), type_id(asETypeIdFlags::asTYPEID_APPOBJECT) {}
            bool is_class() const { return !!type_info; }
            bool is_void() const { return asTYPEID_VOID == type_id; }
            bool is_arithmetic() const { if (is_class()) return false; return type_id > asTYPEID_VOID && type_id < asTYPEID_DOUBLE; }

            bool operator!() const {
                return !type_info && (asETypeIdFlags::asTYPEID_APPOBJECT == type_id || type_id < 0) ;
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
        };
    }

    namespace chrono {



        static void throw_cannot_construct_error(asITypeInfo &type_info, asIScriptEngine &engine)
        {
            const int tid = type_info.GetTypeId();
            const char* type_decl = tid < 0 ? NULL : engine.GetTypeDeclaration(type_info.GetTypeId(), true);

            std::string message = "cannot construct '";
            message += type_decl ? type_decl : "{unknown type}";
            const unsigned subTypeCount = type_info.GetSubTypeCount();
            if (subTypeCount > 0)
            {
                message += "' with <";
                for (unsigned i = 0; i < subTypeCount; ++i)
                {
                    const int stid = type_info.GetSubTypeId();
                    const char* sub_type_decl = stid < 0 ? NULL : engine.GetTypeDeclaration(stid, true);
                    message += sub_type_decl ? sub_type_decl : "{unknown type}";
                    if (i + 1 < subTypeCount) message += ", ";
                }
                message += ">";
            }
            if (asIScriptContext* ctx = asGetActiveContext())
                ctx->SetException(message.c_str());
            throw(std::runtime_error(message.c_str()));
        }

        static void throw_cannot_construct_error(asITypeInfo& type_info)
        {
            return throw_cannot_construct_error(type_info, *type_info.GetEngine());
        }

        template<class RepT>
        struct duration 
        {
            struct meta
            {
#               define TYPE_NAME "%s"
#               define SCOPE_NAME "%s"
                static const char* type_cstr() throw() { return "duration<RepT, PeriodT>"; }
                static const char* type_with_default_params_cstr() throw() { return "duration<RepT>"; }
                static const char* template_callback_cstr() { return "bool template_callback(int&in, bool&out)"; }
                static const char* ctor_cstr() throw() { return "void ctor(int&in, const PeriodT&out=void)"; }
                static const char* ctor_rep_cstr() throw() { return "void ctor(int&in, const RepT &in, const PeriodT&out=void) explicit"; }
                static const char* copy_ctor_cstr() throw() { return "void cctor(int&in, const duration<RepT, PeriodT>& in, const PeriodT&out=void)"; }
                static const char* dtor_cstr() throw() { return "void dtor()"; }
                static const char* assign_cstr() throw() { return TYPE_NAME "& opAssign(const " TYPE_NAME "& in)"; }

                static const char* count_cstr() throw() { return "const RepT& count() const"; }

                static const char* equals_cstr() throw() { return "bool opEquals(const " TYPE_NAME "& in) const"; }
                static const char* cmp_cstr() throw() { return "int opCmp(const " TYPE_NAME "& in) const"; }
                static const char* add_cstr() throw() { return TYPE_NAME" opAdd(const " TYPE_NAME " & in) const"; }
                static const char* sub_cstr() throw() { return TYPE_NAME" opSub(const " TYPE_NAME " & in) const"; }
                static const char* add_assign_cstr() throw() { return TYPE_NAME "& opAddAssign(const " TYPE_NAME "&in)"; }
                static const char* sub_assign_cstr() throw() { return TYPE_NAME "& opSubAssign(const " TYPE_NAME "&in)"; }
                static const char* neg_cstr() throw() { return TYPE_NAME " opNeg() const"; }
                static const char* pos_cstr() throw() { return TYPE_NAME " opPos() const"; }
                static const char* pre_inc_cstr() throw() { return TYPE_NAME "& opPreInc()"; }
                static const char* post_inc_cstr() throw() { return TYPE_NAME " opPostInc()"; }
                static const char* pre_dec_cstr() throw() { return TYPE_NAME "& opPreDec()"; }
                static const char* post_dec_cstr() throw() { return TYPE_NAME " opPostDec()"; }

                static const char* duration_void_cast_const_cstr() throw() { return SCOPE_NAME "duration<void, void> opImplCast() const"; }
#               undef TYPE_NAME
#               undef SCOPE_NAME

                static bool& registering() throw() { static bool value = false; return value; }
            };

            static duration cast(const duration& from, const astd::ratio& to_ratio)
            {
                const astd::ratio cf =
                    astd::detail::ratio_divide(from.ratio, to_ratio);
                return duration(to_ratio, from.ticks_number * cf.num() / cf.den());
            }

            static duration& cast(const duration& from, duration& to)
            {
                const astd::ratio cf =
                    astd::detail::ratio_divide(from.ratio, to.ratio);
                to.ticks_number = from.ticks_number * cf.num() / cf.den();
                return to;
            }

            static duration duration_void_cast(duration& from)
            {
                return from;
            }

            static duration zero() {
                return duration(period(1,1));
            }

            typedef RepT rep;
            typedef astd::ratio period;

            duration(const period &period, rep ticks_number = rep())
                : ticks_number(ticks_number)
                , ratio(period)
            { }

            void swap(duration& other) throw() {
                { asUINTMAX tmp = ticks_number; ticks_number = other.ticks_number; other.ticks_number = tmp; }
                ratio.swap(other.ratio);
            }


            static bool template_callback(asITypeInfo& type_info, bool& dont_GC) {
                if (meta::registering()) return true;

                if (type_info.GetSubTypeCount() != 2)
                    return false;

                enum { RepT_TmplParam, PeriodT_TmplParam  };

                if (!type_info.GetSubType(RepT_TmplParam))
                {
                    const bool is_integral =
                        type_info.GetSubTypeId(RepT_TmplParam) >= asTYPEID_INT8 && type_info.GetSubTypeId(RepT_TmplParam) <= asTYPEID_UINT64;
                    return is_integral;
                }
                asITypeInfo& PeriodT_type_info = *type_info.GetSubType(PeriodT_TmplParam);

                const std::string name = PeriodT_type_info.GetName();

                const char ratio_cstr[] = "ratio<";

                const bool is_ratio = (name.find(ratio_cstr) == 0 && PeriodT_type_info.GetSubTypeCount() == 1);

                bool is_convertable_to_ratio = is_ratio;

                if (!is_convertable_to_ratio)
                {
                    for (asITypeInfo* parent_type_info = PeriodT_type_info.GetParentType(); NULL != parent_type_info; parent_type_info = parent_type_info->GetParentType())
                    {
                        const std::string parent_type_name = parent_type_info->GetName();
                        if (std::string::npos != parent_type_name.find(ratio_cstr)) {
                            is_convertable_to_ratio = true;
                            break;
                        }
                    }
                }

                if (!is_convertable_to_ratio)
                    return false;

                for (asUINT i = 0; i < PeriodT_type_info.GetBehaviourCount(); ++i)
                {
                    asEBehaviours beh;
                    asIScriptFunction* func = PeriodT_type_info.GetBehaviourByIndex(i, &beh);

                    if (!func) continue;

                    if (beh != asBEHAVE_CONSTRUCT) continue;

                    return true;
                }

                return false;
            }

            static void ctor(asITypeInfo& ratio_type_info, const period& ratio, duration& that)
            {
                if (!ratio_type_info.GetSubType())
                {
                    throw_cannot_construct_error(ratio_type_info);
                    return;
                }
                new(&that) duration(ratio);
            }
            static void ctor(asITypeInfo& ratio_type_info, const rep &ticks_number, const period& ratio,  duration& that)
            {
                if (!ratio_type_info.GetSubType())
                {
                    throw_cannot_construct_error(ratio_type_info);
                    return;
                }
                new(&that) duration(ratio, ticks_number);
            }
            static void copy_ctor(asITypeInfo& ratio_type_info, const duration& other, const period& ratio, duration& that)
            {
                if (!ratio_type_info.GetSubType())
                {
                    throw_cannot_construct_error(ratio_type_info);
                    return;
                }
                if (0 == std::memcmp(&other.ratio, &ratio, sizeof(period)))
                    new(&that) duration(other);
                else
                    new(&that) duration(cast(other, ratio));
            }

            static void dtor(duration& that) { that.~duration(); }

            duration& operator=(const duration& other) {
                return cast(other, *this);
            }

            static duration& assign(const duration& other, duration& that) {
                return that = other;
            }

            const rep& count() const {
                return ticks_number;
            }

            bool operator==(const duration& other) const {
                const rep other_ticks_number =
                    (other.ratio == ratio ? other.ticks_number : cast(other, ratio).ticks_number);
                return ticks_number == other_ticks_number;
            }

            int compare(const duration& other) const {
                const rep other_ticks_number =
                    (other.ratio == ratio ? other.ticks_number : cast(other, ratio).ticks_number);
                if (other_ticks_number > ticks_number) return -1;
                if (other_ticks_number == ticks_number) return 0;
                return 1;
            }

            duration operator+(const duration& other) const {
                return (other.ratio == ratio ? 
                    duration(ratio, ticks_number + other.ticks_number) :
                    duration(ratio, ticks_number + cast(other, ratio).ticks_number)
                    );
            }

            duration operator-(const duration& other) const {
                return (other.ratio == ratio ?
                    duration(ratio, ticks_number - other.ticks_number) :
                    duration(ratio, ticks_number - cast(other, ratio).ticks_number)
                    );
            }

            duration& operator+=(const duration& other) {
                ticks_number += 
                    (other.ratio == ratio ? other.ticks_number : cast(other, ratio).ticks_number);
                return *this;
            }

            duration& operator-=(const duration& other) {
                ticks_number -= 
                    (other.ratio == ratio ? other.ticks_number : cast(other, ratio).ticks_number);
                return *this;
            }

            duration operator-() const {
                
                return duration(-ratio, ticks_number);
            }

            duration operator+() const {
                return *this;
            }

            duration& operator++() {
                ++ticks_number; return *this;
            }

            duration operator++(int) {
                return duration(ratio, ticks_number++);
            }

            duration& operator--() {
                --ticks_number; return *this;
            }

            duration operator--(int) {
                return duration(ratio, ticks_number--);
            }

            template<class DurationT>
            static bool register_methods(asIScriptEngine& engine, const namespace_cstr& duration_tmpl_ns, const type_cstr& type_name)
            {
                const char* type_cstr = type_name.cstr;
                int r = 0;
                char buffer[1024] = { 0 };
                using namespace std;
                typedef duration type;
                typedef typename DurationT::meta meta;
                if (meta::count_cstr())
                r = engine.RegisterObjectMethod(
                    type_cstr,
                    meta::count_cstr(),
                    asMETHOD(type, count), asCALL_THISCALL
                ); if (r < 0) return false;

                // operators
                {
                    if (meta::assign_cstr())
                    r = engine.RegisterObjectMethod(
                        type_cstr,
                        (sprintf(buffer, meta::assign_cstr(), type_cstr, type_cstr), buffer),
                        asFUNCTIONPR(type::assign, (const type&, type&), type&), asCALL_CDECL_OBJLAST
                    ); if (r < 0) return false;

                    if (meta::equals_cstr())
                    r = engine.RegisterObjectMethod(
                        type_cstr,
                        (sprintf(buffer, meta::equals_cstr(), type_cstr), buffer),
                        asMETHODPR(type, operator==, (const type&) const, bool), asCALL_THISCALL
                    ); if (r < 0) return false;

                    if (meta::cmp_cstr())
                    r = engine.RegisterObjectMethod(
                        type_cstr,
                        (sprintf(buffer, meta::cmp_cstr(), type_cstr), buffer),
                        asMETHODPR(type, compare, (const type&) const, int), asCALL_THISCALL
                    ); if (r < 0) return false;

                    if (meta::add_cstr())
                    r = engine.RegisterObjectMethod(
                        type_cstr,
                        (sprintf(buffer, meta::add_cstr(), type_cstr, type_cstr), buffer),
                        asMETHODPR(type, operator+, (const type&) const, type), asCALL_THISCALL
                    ); if (r < 0) return false;

                    if (meta::sub_cstr())
                    r = engine.RegisterObjectMethod(
                        type_cstr,
                        (sprintf(buffer, meta::sub_cstr(), type_cstr, type_cstr), buffer),
                        asMETHODPR(type, operator-, (const type&) const, type), asCALL_THISCALL
                    ); if (r < 0) return false;

                    if (meta::add_assign_cstr())
                    r = engine.RegisterObjectMethod(
                        type_cstr,
                        (sprintf(buffer, meta::add_assign_cstr(), type_cstr, type_cstr), buffer),
                        asMETHODPR(type, operator+=, (const type&), type&), asCALL_THISCALL
                    ); if (r < 0) return false;

                    if (meta::sub_assign_cstr())
                    r = engine.RegisterObjectMethod(
                        type_cstr,
                        (sprintf(buffer, meta::sub_assign_cstr(), type_cstr, type_cstr), buffer),
                        asMETHODPR(type, operator-=, (const type&), type&), asCALL_THISCALL
                    ); if (r < 0) return false;

                    if (meta::neg_cstr())
                    r = engine.RegisterObjectMethod(
                        type_cstr, 
                        (sprintf(buffer, meta::neg_cstr(), type_cstr), buffer),
                        asMETHODPR(type, operator-, () const, type), asCALL_THISCALL
                    ); if (r < 0) return false;

                    if (meta::pos_cstr())
                    r = engine.RegisterObjectMethod(
                        type_cstr,
                        (sprintf(buffer, meta::pos_cstr(), type_cstr), buffer),
                        asMETHODPR(type, operator+, () const, type), asCALL_THISCALL
                    ); if (r < 0) return false;

                    if (meta::pre_inc_cstr())
                    r = engine.RegisterObjectMethod(
                        type_cstr,
                        (sprintf(buffer, meta::pre_inc_cstr(), type_cstr), buffer),
                        asMETHODPR(type, operator++, (), type&), asCALL_THISCALL
                    ); if (r < 0) return false;

                    if (meta::post_inc_cstr())
                    r = engine.RegisterObjectMethod(
                        type_cstr,
                        (sprintf(buffer, meta::post_inc_cstr(), type_cstr), buffer),
                        asMETHODPR(type, operator++, (int), type), asCALL_THISCALL
                    ); if (r < 0) return false;

                    if (meta::pre_dec_cstr())
                    r = engine.RegisterObjectMethod(
                        type_cstr,
                        (sprintf(buffer, meta::pre_dec_cstr(), type_cstr), buffer),
                        asMETHODPR(type, operator--, (), type&), asCALL_THISCALL
                    ); if (r < 0) return false;

                    if (meta::post_dec_cstr())
                    r = engine.RegisterObjectMethod(
                        type_cstr,
                        (sprintf(buffer, meta::post_dec_cstr(), type_cstr), buffer),
                        asMETHODPR(type, operator--, (int), type), asCALL_THISCALL
                    ); if (r < 0) return false;
                }

                // conversions
                {
                    if (meta::duration_void_cast_const_cstr())
                    r = engine.RegisterObjectMethod(
                        type_cstr, 
                        (sprintf(buffer, meta::duration_void_cast_const_cstr(), duration_tmpl_ns), buffer),
                        asFUNCTION(&type::duration_void_cast),
                        asCALL_CDECL_OBJFIRST
                    ); if (r < 0) return false;
                }

                return true;
            }

            static bool register_methods(asIScriptEngine& engine, 
                const namespace_cstr& duration_tmpl_ns, 
                const type_cstr& type_name = static_cast<type_cstr>(duration::meta::type_cstr())
            )
            {
                return register_methods<duration>(engine, duration_tmpl_ns, type_name);
            }

            static bool register_behaviours(asIScriptEngine& engine)
            {
                int r = 0;
                typedef duration type;
                r = engine.RegisterObjectBehaviour(
                    type::meta::type_cstr(),
                    asBEHAVE_CONSTRUCT,
                    type::meta::ctor_cstr(),
                    asFUNCTIONPR(type::ctor, (asITypeInfo &, const type::period&, type&), void), asCALL_CDECL_OBJLAST
                ); if (r < 0) return false;
                
                r = engine.RegisterObjectBehaviour(
                    type::meta::type_cstr(),
                    asBEHAVE_CONSTRUCT,
                    type::meta::ctor_rep_cstr(),
                    asFUNCTIONPR(type::ctor, (asITypeInfo&, const type::rep&, const type::period&, type&), void), asCALL_CDECL_OBJLAST
                ); if (r < 0) return false;

                r = engine.RegisterObjectBehaviour(
                    type::meta::type_cstr(),
                    asBEHAVE_CONSTRUCT,
                    type::meta::copy_ctor_cstr(),
                    asFUNCTIONPR(type::copy_ctor, (asITypeInfo&, const type&, const type::period&, type&), void), asCALL_CDECL_OBJLAST
                ); if (r < 0) return false;

                r = engine.RegisterObjectBehaviour(
                    type::meta::type_cstr(),
                    asBEHAVE_DESTRUCT,
                    type::meta::dtor_cstr(),
                    asFUNCTION(type::dtor), asCALL_CDECL_OBJLAST
                ); if (r < 0) return false;

                return true;
            }

        protected:
            rep ticks_number;
            period ratio;
            
            struct internal {
                inline
                static const period& ratio(const duration& that) throw() {
                    return that.ratio;
                }
                inline
                static const rep& ticks_number(const duration& that) throw() {
                    return that.ticks_number;
                }

                inline
                static int ratio_offset() throw() {
                    return asOFFSET(duration, ratio);
                }
            };
        };

        struct generic_clock {

        };

#       define ClockT generic_clock            // template param emulation
#       define DurationT duration<asUINTMAX>   // template param emulation
        struct time_point {
            struct meta
            {
#               define TYPE_NAME "%s"
#               define TMPL_T_NAME "%s"
                static const char* type_cstr() throw() { return "time_point<T>"; }
                static const char* ctor_cstr() throw() { return "void ctor(int&in)"; }
                static const char* ctor_duration_cstr() throw() { return "void ctor(int&in, const T &in) explicit"; }
                static const char* copy_ctor_cstr() throw() { return "void cctor(int&in, const T & in)"; }
                static const char* dtor_cstr() throw() { return "void dtor()"; }
                static const char* assign_cstr() throw() { return TYPE_NAME "& opAssign(const " TYPE_NAME " & in)"; }

                static const char* time_since_epoch_cstr() throw() { return "const " TMPL_T_NAME "& time_since_epoch() const"; }

                static const char* equals_cstr() throw() { return "bool opEquals(const " TYPE_NAME "&in) const"; }
                static const char* cmp_cstr() throw() { return "int opCmp(const " TYPE_NAME "&in) const"; }
                static const char* add_cstr() throw() { return  TYPE_NAME " opAdd(const " TMPL_T_NAME "&in) const"; }
                static const char* sub_cstr() throw() { return  "duration_cast<" TMPL_T_NAME "> opSub(const " TYPE_NAME "&in) const"; }
                static const char* add_assign_cstr() throw() { return TYPE_NAME "& opAddAssign(const " TMPL_T_NAME "&in)"; }
#               undef TYPE_NAME
#               undef TMPL_T_NAME
            };

            typedef ClockT clock;
#           ifndef ClockT
#           error "ClockT is not defined so code above should be refactored (remove this assert when all done)"
#           else
#           undef ClockT
#           endif

            typedef DurationT duration;
#           ifndef DurationT
#           error "DurationT is not defined so code above should be refactored (remove this assert when all done)"
#           else
#           undef DurationT
#           endif

            typedef duration::rep rep;
            typedef duration::period period;

            time_point(duration ticks_since_epoch = duration::zero())
                : ticks_since_epoch(ticks_since_epoch) {}
            static void ctor(asITypeInfo& duration_type_info, time_point& that)
            {
                asITypeInfo* subtype_info = duration_type_info.GetSubType();
                if (!subtype_info)
                {
                    throw_cannot_construct_error(duration_type_info);
                    return;
                }
                char memory[sizeof(duration)];
                duration &ticks_since_epoch = *reinterpret_cast<duration*>(memory);
                const std::string duration_type_name = duration_type_info.GetName();
                const std::string duration_type_ns = duration_type_info.GetNamespace();

                std::abort();

                new(&that) time_point(ticks_since_epoch);
            }
            static void ctor(asITypeInfo& duration_type_info, duration ticks_since_epoch,  time_point& that)
            {
                if (!duration_type_info.GetSubType())
                {
                    throw_cannot_construct_error(duration_type_info);
                    return;
                }
                new(&that) time_point(ticks_since_epoch);
            }

            static void copy_ctor(asITypeInfo& duration_type_info, const time_point& other,  time_point& that)
            {
                if (!duration_type_info.GetSubType())
                {
                    throw_cannot_construct_error(duration_type_info);
                    return;
                }
                new(&that) time_point(other);
            }

            static void dtor(time_point& that) { that.~time_point(); }

            static time_point& assign(const time_point& other, time_point& that) {
                that.ticks_since_epoch = other.ticks_since_epoch;
                return that;
            }

            const duration& time_since_epoch() const {
                return ticks_since_epoch;
            }

            bool operator==(const time_point& other) const {
                return ticks_since_epoch == other.ticks_since_epoch;
            }

            int compare(const time_point& other) const {
                return ticks_since_epoch.compare(other.ticks_since_epoch);
            }
            duration operator-(const time_point& other) const {
                return ticks_since_epoch - other.ticks_since_epoch;
            }
            time_point operator+(const duration& other) const {
                return ticks_since_epoch + other;
            }
            time_point& operator+=(const duration& other) {
                ticks_since_epoch += other;
                return *this;
            }

            static bool register_behaviours(asIScriptEngine& engine)
            {
                int r = 0;
                typedef time_point type;
                //r = engine.RegisterObjectBehaviour(
                //    meta::type_cstr(),
                //    asBEHAVE_CONSTRUCT,
                //    type::meta::ctor_cstr(),
                //    asFUNCTIONPR(type::ctor, (asITypeInfo&, type&), void), asCALL_CDECL_OBJLAST
                //); if (r < 0) return false;
                //
                //r = engine.RegisterObjectBehaviour(
                //    meta::type_cstr(),
                //    asBEHAVE_CONSTRUCT,
                //    type::meta::ctor_duration_cstr(),
                //    asFUNCTIONPR(type::ctor, (type::duration, asITypeInfo&, type&), void), asCALL_CDECL_OBJLAST
                //); if (r < 0) return false;

                r = engine.RegisterObjectBehaviour(
                    meta::type_cstr(),
                    asBEHAVE_CONSTRUCT,
                    type::meta::copy_ctor_cstr(),
                    asFUNCTIONPR(type::copy_ctor, (asITypeInfo&, const type&, type&), void), asCALL_CDECL_OBJLAST
                ); if (r < 0) return false;

                r = engine.RegisterObjectBehaviour(
                    meta::type_cstr(),
                    asBEHAVE_DESTRUCT,
                    type::meta::dtor_cstr(),
                    asFUNCTION(type::dtor), asCALL_CDECL_OBJLAST
                ); if (r < 0) return false;

                return true;
            }

            static bool register_methods(asIScriptEngine& engine, 
                const astd::type_cstr &type_name = static_cast<astd::type_cstr>(meta::type_cstr()), 
                const astd::subtype_cstr& subtype_name = static_cast<astd::subtype_cstr>("T")
            )
            {
                const char* type_cstr = type_name.cstr;
                const char* subtype_cstr = subtype_name.cstr;
                int r = 0;
                char buffer[1024] = { 0 };
                using namespace std;
                typedef time_point type;

                r = engine.RegisterObjectMethod(
                    type_cstr, 
                    (sprintf(buffer, type::meta::time_since_epoch_cstr(), subtype_cstr), buffer),
                    asMETHOD(type, time_since_epoch), asCALL_THISCALL
                ); if (r < 0) return false;

                // operators
                {
                    r = engine.RegisterObjectMethod(
                        type_cstr,
                        (sprintf(buffer, type::meta::assign_cstr(), type_cstr, type_cstr), buffer),
                        asFUNCTIONPR(type::assign, (const type&, type&), type&), asCALL_CDECL_OBJLAST
                    ); if (r < 0) return false;

                    r = engine.RegisterObjectMethod(
                        type_cstr,
                        (sprintf(buffer, type::meta::equals_cstr(), type_cstr), buffer),
                        asMETHODPR(type, operator==, (const type&) const, bool), asCALL_THISCALL
                    ); if (r < 0) return false;

                    r = engine.RegisterObjectMethod(
                        type_cstr,
                        (sprintf(buffer, type::meta::cmp_cstr(), type_cstr), buffer),
                        asMETHODPR(type, compare, (const type&) const, int), asCALL_THISCALL
                    ); if (r < 0) return false;

                    r = engine.RegisterObjectMethod(
                        type_cstr,
                        (sprintf(buffer, type::meta::add_cstr(), type_cstr, subtype_cstr), buffer),
                        asMETHODPR(type, operator+, (const type::duration&) const, type), asCALL_THISCALL
                    ); if (r < 0) return false;

                    r = engine.RegisterObjectMethod(
                        type_cstr,
                        (sprintf(buffer, type::meta::sub_cstr(), subtype_cstr, type_cstr), buffer),
                        asMETHODPR(type, operator-, (const type&) const, type::duration), asCALL_THISCALL
                    ); if (r < 0) return false;

                    r = engine.RegisterObjectMethod(
                        type_cstr,
                        (sprintf(buffer, type::meta::add_assign_cstr(), type_cstr, subtype_cstr), buffer),
                        asMETHODPR(type, operator+=, (const type::duration&), type&), asCALL_THISCALL
                    ); if (r < 0) return false;
                }

                return true;
            }


        private:
            duration ticks_since_epoch;

        };

        struct NamespaceRAII {
            NamespaceRAII(asIScriptEngine& engine) : engine(engine) {
                current_ns = engine.GetDefaultNamespace(); if (!current_ns.empty()) current_ns += "::";
            }
            void operator()() const {
                engine.SetDefaultNamespace(current_ns.c_str());
            }
            ~NamespaceRAII() {
                (*this)();
            }
            std::string current_ns;
            asIScriptEngine& engine;
        };

        template<
            class Period = ratio_ct<1, 1> 
        >
        struct duration_ct;

        template<asINTMAX Num, asINTMAX Den>
        struct duration_ct<
            ratio_ct<Num, Den>
        > : duration<asUINTMAX>
        {
            typedef duration<asUINTMAX> duration;
            struct meta
                : duration::meta
            {
#               define RepT "uintmax"
                typedef void type_cstr; // to block expicit usage of meta function

                static const char* ctor_cstr() throw() { return "void ctor()"; }
                static const char* ctor_duration_cstr() throw() { return "void ctor(const %sduration<" RepT ", %s>&in)"; }
                static const char* ctor_rep_cstr() throw() { return "void ctor(const " RepT " &in) explicit"; }
                static const char* copy_ctor_cstr() throw() { return "void cctor(const %s &in)"; }

                static const char* count_cstr() throw() { return "const " RepT "& count() const"; }

                static const char* duration_cast_cstr() throw() { return "%sduration<" RepT ", %s>& opImplCast()"; }
                static const char* duration_cast_const_cstr() throw() { return "const %sduration<" RepT ", %s>& opImplCast() const"; }
#               undef RepT
            };

            typedef ratio_ct<Num, Den> period;

            duration_ct(rep ticks_number = rep())
                : duration(period(), ticks_number)
            {}
            duration_ct(const duration& other)
                : duration(other)
            {}
            static void ctor(duration_ct& that)
            {
                new(&that) duration_ct();
            }
            static void ctor(const duration& other, duration_ct& that)
            {
                new(&that) duration_ct(other);
            }
            static void ctor(const rep &ticks_number, duration_ct& that)
            {
                new(&that) duration_ct(ticks_number);
            }
            static void copy_ctor(const duration_ct &other, duration_ct& that)
            {
                new(&that) duration_ct(other);
            }

            static void dtor(duration_ct& that) { that.~duration_ct(); }

            static duration* duration_cast(duration_ct& that) {
                return &that;
            }

            static bool register_methods(asIScriptEngine& engine, const namespace_cstr& duration_tmpl_ns, const type_cstr& type_name, const subtype_cstr& subtype_name)
            {
                const char* type_cstr = type_name.cstr;
                const char* subtype_cstr = subtype_name.cstr;
                typedef duration_ct type;
                int r = 0;

                if (!duration::register_methods<type>(engine, duration_tmpl_ns, type_name)) return false;

                // registering object relation functions (casting, inheritance etc.)
                {                    
                    char buffer[1024] = { 0 };
                    using namespace std;

                    r = engine.RegisterObjectMethod(
                        type_cstr, 
                        (sprintf(buffer, type::meta::duration_cast_cstr(), duration_tmpl_ns, subtype_cstr), buffer),
                        asFUNCTION(&type::duration_cast),
                        asCALL_CDECL_OBJFIRST
                    ); if (r < 0) return false;

                    r = engine.RegisterObjectMethod(
                        type_cstr,
                        (sprintf(buffer, type::meta::duration_cast_const_cstr(), duration_tmpl_ns, subtype_cstr), buffer),
                        asFUNCTION(&type::duration_cast),
                        asCALL_CDECL_OBJFIRST
                    ); if (r < 0) return false;
                }

                return true;
            }

            static bool register_behaviours(asIScriptEngine& engine, const namespace_cstr& duration_tmpl_ns, const type_cstr& type_name, const subtype_cstr& subtype_name)
            {
                const char* type_cstr = type_name.cstr;
                const char* subtype_cstr = subtype_name.cstr;
                int r = 0;
                typedef duration_ct type;
                r = engine.RegisterObjectBehaviour(
                    type_cstr,
                    asBEHAVE_CONSTRUCT,
                    type::meta::ctor_cstr(),
                    asFUNCTIONPR(type::ctor, (type&), void), asCALL_CDECL_OBJLAST
                ); if (r < 0) return false;

                r = engine.RegisterObjectBehaviour(
                    type_cstr,
                    asBEHAVE_CONSTRUCT,
                    type::meta::ctor_rep_cstr(),
                    asFUNCTIONPR(type::ctor, (const type::rep&, type&), void), asCALL_CDECL_OBJLAST
                ); if (r < 0) return false;

                {
                    char buffer[1024] = { 0 };
                    using namespace std;

                    r = engine.RegisterObjectBehaviour(
                        type_cstr,
                        asBEHAVE_CONSTRUCT, 
                        (sprintf(buffer, type::meta::ctor_duration_cstr(), duration_tmpl_ns, subtype_cstr), buffer),
                        asFUNCTIONPR(type::ctor, (const type::duration&, type&), void), asCALL_CDECL_OBJLAST
                    ); if (r < 0) return false;

                    r = engine.RegisterObjectBehaviour(
                        type_cstr,
                        asBEHAVE_CONSTRUCT,
                        (sprintf(buffer, type::meta::copy_ctor_cstr(), type_cstr), buffer),
                        asFUNCTIONPR(type::copy_ctor, (const type&, type&), void), asCALL_CDECL_OBJLAST
                    ); if (r < 0) return false;
                }

                r = engine.RegisterObjectBehaviour(
                    type_cstr,
                    asBEHAVE_DESTRUCT,
                    type::meta::dtor_cstr(),
                    asFUNCTION(type::dtor), asCALL_CDECL_OBJLAST
                ); if (r < 0) return false;

                return true;
            }

            static bool register_typedefs(asIScriptEngine& engine, const type_cstr& type_name)
            {
                const char* type_cstr = type_name.cstr;
                NamespaceRAII NamespaceRAII(engine);

                assert(engine.GetTypeInfoByName(type_cstr) != NULL);
                const char* type_namespace_cstr = engine.GetTypeInfoByName(type_cstr)->GetNamespace();

                const std::string ns = type_namespace_cstr ? type_namespace_cstr : "";
                const asQWORD flags = asOBJ_VALUE | asOBJ_APP_CLASS_CD;
                const std::string type_str = (ns.empty()? "": (ns + "::")) + type_cstr;

                int r = 0;

                // period typedef
                {
                    engine.SetDefaultNamespace(type_str.c_str());

                    struct type : period {
                        struct meta {
                            static const char* type_cstr() { return "period"; }
                            static const char* ctor_cstr() throw() { return "void ctor()"; }
                            static const char* copy_ctor_cstr() throw() { return "void cctor(const period&in)"; }
                            static const char* dtor_cstr() throw() { return "void dtor()"; }
                        };
                        static void ctor(period& that) { new(&that) period(); }
                        static void copy_ctor(const period& other, period& that) { new(&that) period(other); }
                        static void dtor(period& that) { that.~period(); }
                    };

                    r = engine.RegisterObjectType(
                        type::meta::type_cstr(),
                        sizeof(period),
                        flags
                    ); if (r < 0) return false;

                    r = engine.RegisterObjectBehaviour(
                        type::meta::type_cstr(),
                        asBEHAVE_CONSTRUCT,
                        type::meta::ctor_cstr(),
                        asFUNCTIONPR(type::ctor, (period&), void), asCALL_CDECL_OBJLAST
                    ); if (r < 0) return false;

                    r = engine.RegisterObjectBehaviour(
                        type::meta::type_cstr(),
                        asBEHAVE_CONSTRUCT,
                        type::meta::copy_ctor_cstr(),
                        asFUNCTIONPR(type::copy_ctor, (const period&, period&), void), asCALL_CDECL_OBJLAST
                    ); if (r < 0) return false;

                    r = engine.RegisterObjectBehaviour(
                        type::meta::type_cstr(),
                        asBEHAVE_DESTRUCT,
                        type::meta::dtor_cstr(),
                        asFUNCTIONPR(type::dtor, (period&), void), asCALL_CDECL_OBJLAST
                    ); if (r < 0) return false;
                }

                return true;
            }
        };

        namespace detail
        {

            template<bool, class Iftrue, class>
            struct conditional
            {
                typedef Iftrue type;
            };

            // Partial specialization for false.
            template<class Iftrue, class Iffalse>
            struct conditional<false, Iftrue, Iffalse>
            {
                typedef Iffalse type;
            };
            struct duration_predefined
            {
                template<class>
                struct is_ratio_ct
                {
                    static const bool value = false;
                };

                template<asINTMAX Num, asINTMAX Den>
                struct is_ratio_ct<
                    astd::ratio_ct<Num, Den>
                >
                {
                    static const bool value = true;
                };

                struct duration_cannot_be_implemented;

                typedef 
                conditional<
                    is_ratio_ct<nano>::value, 
                    duration_ct<nano>,
                    duration_cannot_be_implemented
                >::type nanoseconds;

                typedef 
                conditional<
                    is_ratio_ct<micro>::value,
                    duration_ct<micro>,
                    duration_cannot_be_implemented
                >::type microseconds;

                typedef
                conditional<
                    is_ratio_ct<milli>::value,
                    duration_ct<milli>,
                    duration_cannot_be_implemented
                >::type milliseconds;

                typedef duration_ct<> seconds;
                typedef duration_ct<ratio_ct<60>/**/> minutes;
                typedef duration_ct<ratio_ct<3600>/**/> hours;
            };
        }

        // Standard duration types.
        typedef detail::duration_predefined::nanoseconds  nanoseconds;  //!< Duration with the unit nanoseconds.
        typedef detail::duration_predefined::microseconds microseconds; //!< Duration with the unit microseconds.
        typedef detail::duration_predefined::milliseconds milliseconds; //!< Duration with the unit milliseconds.
        typedef detail::duration_predefined::seconds      seconds;      //!< Duration with the unit seconds.
        typedef detail::duration_predefined::minutes      minutes;      //!< Duration with the unit minutes.
        typedef detail::duration_predefined::hours        hours;        //!< Duration with the unit hours.

        namespace type_traits {
            template<class T>
            struct is_duration {
                static const bool value = false;
            };
            template<class RepT>
            struct is_duration<
                duration<RepT>
            > {
                static const bool value = true;
            };
            template<class Period>
            struct is_duration<
                duration_ct<Period>
            > {
                static const bool value = true;
            };
        }

        template<
            class Clock,
            class Duration = duration_ct<>
        >
        struct time_point_ct;

        template<class Clock, class Ratio>
        struct time_point_ct<
            Clock, duration_ct<Ratio>
        > : time_point
        {
            struct meta
                : duration::meta
            {
                typedef void type_cstr; // to block expicit usage of meta function

                static const char* ctor_cstr() throw() { return "void ctor()"; }
                static const char* ctor_time_point_cstr() throw() { return "void ctor(const %stime_point<%s>&in)"; }
                static const char* ctor_duration_cstr() throw() { return "void ctor(const %s&in)"; }
                static const char* copy_ctor_cstr() throw() { return "void cctor(const %s &in)"; }
                static const char* dtor_cstr() throw() { return "void dtor()"; }

                static const char* time_point_cast_cstr() throw() { return "%stime_point<%s>& opImplCast()"; }
                static const char* time_point_cast_const_cstr() throw() { return "const %stime_point<%s>& opImplCast() const"; }
            };

            typedef duration_ct<Ratio> duration;

            time_point_ct(duration ticks_since_epoch = duration::zero())
                : time_point(ticks_since_epoch)
            {}
            time_point_ct(const time_point &other)
                : time_point(other)
            {}
            static void ctor(time_point_ct& that)
            {
                new(&that) time_point_ct();
            }
            static void ctor(const time_point& other, time_point_ct& that)
            {
                new(&that) time_point_ct(other);
            }
            static void ctor(const duration& ticks_since_epoch, time_point_ct& that)
            {
                new(&that) time_point_ct(ticks_since_epoch);
            }
            static void copy_ctor(const time_point_ct& other, time_point_ct& that)
            {
                new(&that) time_point_ct(other);
            }

            static void dtor(time_point_ct& that) { that.~time_point_ct(); }

            static time_point* time_point_cast(time_point_ct& that) {
                return &that;
            }

            static bool register_methods(asIScriptEngine& engine, const type_cstr& type_name, const subtype_cstr& subtype_name)
            {
                const char* type_cstr = type_name.cstr;
                const char* subtype_cstr = subtype_name.cstr;
                typedef time_point_ct type;
                int r = 0;

                assert(engine.GetTypeInfoByName(type_cstr) != NULL);
                const char* type_namespace_cstr = engine.GetTypeInfoByName(type_cstr)->GetNamespace();
                const std::string type_ns = type_namespace_cstr ? type_namespace_cstr : "";
                const std::string::size_type ns_sep_pos = type_ns.find_last_of("::");
                const std::string time_point_ns = type_ns.substr(0, std::string::npos != ns_sep_pos ? ns_sep_pos - 1 : ns_sep_pos) + "::";
                const std::string subtype_with_ns = (time_point_ns + subtype_cstr);
                const astd::subtype_cstr subtype_with_ns_name = static_cast<astd::subtype_cstr>(subtype_with_ns.c_str());

                if (!time_point::register_methods(engine, type_name, subtype_with_ns_name)) return false;

                // registering object relation functions (casting, inheritance etc.)
                {
                    NamespaceRAII NamespaceRAII(engine);


                    const std::string type_with_ns = (type_ns + "::" + type_cstr);

                    char buffer[1024] = { 0 };
                    using namespace std;

                    r = engine.RegisterObjectMethod(
                        type_with_ns.c_str(),
                        (sprintf(buffer, type::meta::time_point_cast_cstr(), time_point_ns.c_str(), subtype_with_ns_name.cstr), buffer),
                        asFUNCTION(&type::time_point_cast),
                        asCALL_CDECL_OBJFIRST
                    ); if (r < 0) return false;

                    r = engine.RegisterObjectMethod(
                        type_with_ns.c_str(),
                        (sprintf(buffer, type::meta::time_point_cast_const_cstr(), time_point_ns.c_str(), subtype_with_ns_name.cstr), buffer),
                        asFUNCTION(&type::time_point_cast),
                        asCALL_CDECL_OBJFIRST
                    ); if (r < 0) return false;
                }

                return true;
            }

            static bool register_behaviours(asIScriptEngine& engine, const type_cstr& type_name, const subtype_cstr& subtype_name)
            {
                const char* type_cstr = type_name.cstr;
                const char* subtype_cstr = subtype_name.cstr;
                int r = 0;
                typedef time_point_ct type;
                r = engine.RegisterObjectBehaviour(
                    type_cstr,
                    asBEHAVE_CONSTRUCT,
                    type::meta::ctor_cstr(),
                    asFUNCTIONPR(type::ctor, (type&), void), asCALL_CDECL_OBJLAST
                ); if (r < 0) return false;

                {
                    NamespaceRAII NamespaceRAII(engine);

                    assert(engine.GetTypeInfoByName(type_cstr) != NULL);
                    const char* type_namespace_cstr = engine.GetTypeInfoByName(type_cstr)->GetNamespace();

                    const std::string type_ns = type_namespace_cstr ? type_namespace_cstr : "";
                    const std::string::size_type ns_sep_pos = type_ns.find_last_of("::");
                    const std::string time_point_ns = type_ns.substr(0, std::string::npos != ns_sep_pos ? ns_sep_pos - 1 : ns_sep_pos) + "::";
                    const std::string type_with_ns = (type_ns + "::" + type_cstr);
                    const std::string subtype_with_ns = (time_point_ns + subtype_cstr);

                    char buffer[1024] = { 0 };
                    using namespace std;
                    r = engine.RegisterObjectBehaviour(
                        type_with_ns.c_str(),
                        asBEHAVE_CONSTRUCT,
                        (sprintf(buffer, type::meta::ctor_time_point_cstr(), time_point_ns.c_str(), subtype_with_ns.c_str()), buffer),
                        asFUNCTIONPR(type::ctor, (const time_point&, type&), void), asCALL_CDECL_OBJLAST
                    ); if (r < 0) return false;

                    r = engine.RegisterObjectBehaviour(
                        type_with_ns.c_str(),
                        asBEHAVE_CONSTRUCT,
                        (sprintf(buffer, type::meta::ctor_duration_cstr(), subtype_with_ns.c_str()), buffer),
                        asFUNCTIONPR(type::ctor, (const type::duration&, type&), void), asCALL_CDECL_OBJLAST
                    ); if (r < 0) return false;

                    r = engine.RegisterObjectBehaviour(
                        type_with_ns.c_str(),
                        asBEHAVE_CONSTRUCT,
                        (sprintf(buffer, type::meta::copy_ctor_cstr(), type_cstr), buffer),
                        asFUNCTIONPR(type::copy_ctor, (const type&, type&), void), asCALL_CDECL_OBJLAST
                    ); if (r < 0) return false;
                }

                r = engine.RegisterObjectBehaviour(
                    type_cstr,
                    asBEHAVE_DESTRUCT,
                    type::meta::dtor_cstr(),
                    asFUNCTION(type::dtor), asCALL_CDECL_OBJLAST
                ); if (r < 0) return false;

                return true;
            }

            static bool register_typedefs(asIScriptEngine& engine, const type_cstr& type_name)
            {
                const char* type_cstr = type_name.cstr;
                NamespaceRAII NamespaceRAII(engine);


                assert(engine.GetTypeInfoByName(type_cstr) != NULL);
                const char* type_namespace_cstr = engine.GetTypeInfoByName(type_cstr)->GetNamespace();

                const std::string ns = type_namespace_cstr ? type_namespace_cstr : "";
                const asQWORD flags = asOBJ_VALUE;
                const std::string type_str = (ns.empty() ? "" : (ns + "::")) + type_cstr;

                int r = 0;

                // duration typedef
                {
                    engine.SetDefaultNamespace(type_str.c_str());
                    r = engine.RegisterObjectType(
                        "duration",
                        sizeof(duration),
                        flags
                    ); if (r < 0) return false;
                    NamespaceRAII();
                    const std::string duration_typedef_str = type_str + "::duration";
                    if (!register_behaviours(engine, static_cast<astd::type_cstr>(duration_typedef_str.c_str()), static_cast<astd::subtype_cstr>("period"))) return false;
                }

                return true;
            }
        };

        template<class RepT>
        struct duration_cast
            : duration<RepT>
        {
            typedef duration<RepT> duration;

            struct meta
                : duration::meta
            {
#               define TYPE_NAME "%s"
#               define NS_NAME "%s"
                static const char* func_cstr() throw() { return "duration_cast<T>"; }
                static const char* ctor_cstr() throw() { return "void call(int&in)"; }
                static const char* call_cstr() throw() { return "void call(int&in, const " NS_NAME "duration<void, void> &in, const " TYPE_NAME "&out=void)"; }
                static const char* copy_ctor_cstr() throw() { return "void cctor(int&in, const duration_cast<" TYPE_NAME "> &in)"; }
                static const char* end_cstr() throw() { return "void end()"; }
                static const char* template_callback_cstr() throw() { return "bool template_callback(int&in, bool&out)"; }

                static const char* count_cstr() throw() { return 0; }

                static const char* result_cstr() throw() { return TYPE_NAME "& opImplCast()"; }
                static const char* result_const_cstr() throw() { return "const " TYPE_NAME "& opImplCast() const"; }
#               undef TYPE_NAME
#               undef NS_NAME
            };
            static void ctor(asITypeInfo&, duration_cast& that)
            {
                new (&that) duration_cast(duration::zero());
            }
            static void call(asITypeInfo&, const duration& in, const duration& out, duration_cast& that) {

                const typename duration::period& out_ratio = duration::internal::ratio(out);
                const typename duration::period& in_ratio = duration::internal::ratio(in);

                new (&that) duration_cast(
                    (0 == std::memcmp(&out_ratio, &in_ratio, sizeof(typename duration::period))) ? in : duration::cast(in, out_ratio)
                );
            }
            static void copy_ctor(asITypeInfo&, const duration_cast& other, duration_cast& that)
            {
                new (&that) duration_cast(other);
            }
            static void end(duration_cast& that) {
                that.~duration_cast();
            }
            static duration& result(duration_cast& that) {
                return that;
            }
            static bool template_callback(asITypeInfo& type_info, bool& dont_GC) {
                if (!type_info.GetSubType()) return false;
                enum { DurationT };
                asITypeInfo& DurationT_type_info = *type_info.GetSubType(DurationT);

                const std::string name = DurationT_type_info.GetName();

                const char duration_cstr[] = "duration<";

                const bool is_duration = (name.find(duration_cstr) == 0 && DurationT_type_info.GetSubTypeCount() == 2);

                bool is_convertable_to_duration = is_duration;

                if (!is_convertable_to_duration)
                {
                    for (asITypeInfo* parent_type_info = DurationT_type_info.GetParentType(); NULL != parent_type_info; parent_type_info = parent_type_info->GetParentType())
                    {
                        const std::string parent_type_name = parent_type_info->GetName();
                        if (std::string::npos != parent_type_name.find(duration_cstr)) {
                            is_convertable_to_duration = true;
                            break;
                        }
                    }
                }

                if (!is_convertable_to_duration)
                {
                    for (asUINT i = 0; !is_convertable_to_duration && i < DurationT_type_info.GetMethodCount(); ++i)
                    {
                        asIScriptFunction* func = DurationT_type_info.GetMethodByIndex(i);

                        if (!func) continue;
                        const std::string func_decl = func->GetDeclaration();

                        const std::string::size_type opImplCast_pos = func_decl.find("opImplCast");

                        if (std::string::npos == opImplCast_pos) continue;

                        is_convertable_to_duration =
                            opImplCast_pos > func_decl.find(duration_cstr);

                    }
                }

                if (!is_convertable_to_duration)
                    return false;


                // registering generic duration interface
                {

                    static bool registering_generic_duration_interface = false;
                    struct lambdas {

                        static astd::asType RepT_type(const asITypeInfo& DurationT_type_info, bool is_duration)
                        {
                            astd::asType result;

                            if (!is_duration)
                            {
                                asIScriptEngine& engine = *DurationT_type_info.GetEngine();
                                
                                for (asUINT i = 0; i < DurationT_type_info.GetMethodCount(); ++i)
                                {
                                    asIScriptFunction* func = DurationT_type_info.GetMethodByIndex(i);

                                    if (!func) continue;
                                    const std::string func_decl = func->GetDeclaration();

                                    const std::string::size_type count_pos = func_decl.find("count() const");

                                    if (std::string::npos == count_pos) continue;

                                    const std::string::size_type count_with_scope_pos = func_decl.rfind(" ", count_pos);

                                    if (std::string::npos == count_with_scope_pos) continue;

                                    const std::string count_ret_type_with_specs = func_decl.substr(0, count_with_scope_pos);

                                    const std::string::size_type count_ret_type_pos = count_ret_type_with_specs.find(" ");

                                    if (std::string::npos == count_ret_type_pos) continue;

                                    const std::string count_ret_type_dirty = count_ret_type_with_specs.substr(count_ret_type_pos);

                                    const std::string count_ret_type = count_ret_type_dirty.substr(0, count_ret_type_dirty.find("&"));

                                    asITypeInfo* count_ret_type_info = engine.GetTypeInfoByDecl(count_ret_type.c_str());

                                    if (count_ret_type_info) {
                                        result.type_info = count_ret_type_info; break;
                                    }
                                    else
                                    {
                                        result.type_id = engine.GetTypeIdByDecl(count_ret_type.c_str());
                                    }

                                    if (!!result) break;
                                }
                            }
                            else
                            {
                                enum { RepT_TmplParam, PeriodT_TmplParam };
                                result.type_info = 
                                    DurationT_type_info.GetSubType(RepT_TmplParam);
                                result.type_id =
                                    DurationT_type_info.GetSubTypeId(RepT_TmplParam);
                            }

                            assert(!!result);

                            return result;
                        }
                    };
                    

                    asType RepT_type = lambdas::RepT_type(DurationT_type_info, is_duration);

                    char buffer[1024] = { 0 };
                    struct meta 
                    {
                        static const char* count_cstr(char *buffer, const astd::subtype_cstr &subtype_name) throw() {
                            using namespace std;
                            return (sprintf(buffer, "const %s& count() const", subtype_name.cstr), buffer);
                        }

                        static const char* type_cstr(char* buffer, const astd::subtype_cstr& subtype_name) {
                            using namespace std;
                            return (sprintf(buffer, "duration_cast<%s>", subtype_name.cstr), buffer);
                        }
                    };

                    asIScriptEngine& engine = *type_info.GetEngine();
                    const std::string subtype_str = DurationT_type_info.GetName();
                    const std::string subtype_ns_str = DurationT_type_info.GetNamespace();
                    const std::string subtype_with_ns_str = subtype_ns_str + (subtype_ns_str.empty() ? "" : "::") + subtype_str;
                    const subtype_cstr subtype = static_cast<subtype_cstr>(subtype_with_ns_str.c_str());
                    const std::string type_str = meta::type_cstr(buffer, subtype);

                    if (!registering_generic_duration_interface)
                    {
                        registering_generic_duration_interface = true;

                        struct duration_cast_ct
                            : duration_cast
                        {
                            struct meta : duration_cast::meta {
#                               define NS_NAME "%s"
#                               define TYPE_NAME "%s"
                                static const char* func_cstr() throw() { return "duration_cast<%s>"; }
                                static const char* ctor_cstr() throw() { return "void call()"; }
                                static const char* call_cstr() throw() { return "void call(const " NS_NAME "duration<void, void> &in, const " TYPE_NAME "&out=void)"; }
                                static const char* copy_ctor_cstr() throw() { return "void cctor(const duration_cast<" TYPE_NAME "> &in)"; }
#                               undef NS_NAME
#                               undef TYPE_NAME
                            };

                            static void ctor(duration_cast& that)
                            {
                                new (&that) duration_cast(duration::zero());
                            }
                            static void call(const duration& in, const duration& out, duration_cast& that) {

                                const typename duration::period& out_ratio = duration::internal::ratio(out);
                                const typename duration::period& in_ratio = duration::internal::ratio(in);

                                new (&that) duration_cast(
                                    (0 == std::memcmp(&out_ratio, &in_ratio, sizeof(typename duration::period))) ? in : duration::cast(in, out_ratio)
                                );
                            }
                            static void copy_ctor(const duration_cast& other, duration_cast& that)
                            {
                                new (&that) duration_cast(other);
                            }


                            static bool register_behaviours(asIScriptEngine& engine,
                                const namespace_cstr& ns_name,
                                const type_cstr& func_name = static_cast<type_cstr>(meta::func_cstr()),
                                const subtype_cstr& subtype_name = static_cast<subtype_cstr>("T")
                            )
                            {
                                typedef duration_cast_ct type;
                                int r = 0;
                                const char* func_cstr = func_name.cstr;
                                const char* subtype_cstr = subtype_name.cstr;
                                const char* namespace_cstr = ns_name.cstr;
                                char buffer[1024] = { 0 };
                                using namespace std;


                                r = engine.RegisterObjectBehaviour(
                                    func_cstr,
                                    asBEHAVE_CONSTRUCT,
                                    meta::ctor_cstr(),
                                    asFUNCTION(type::ctor),
                                    asCALL_CDECL_OBJLAST
                                ); if (r < 0) return false;

                                r = engine.RegisterObjectBehaviour(
                                    func_cstr,
                                    asBEHAVE_CONSTRUCT,
                                    (sprintf(buffer, meta::copy_ctor_cstr(), subtype_cstr), buffer),
                                    asFUNCTION(type::copy_ctor),
                                    asCALL_CDECL_OBJLAST
                                ); if (r < 0) return false;

                                r = engine.RegisterObjectBehaviour(
                                    func_cstr,
                                    asBEHAVE_CONSTRUCT,
                                    (sprintf(buffer, meta::call_cstr(), namespace_cstr, subtype_cstr), buffer),
                                    asFUNCTION(type::call),
                                    asCALL_CDECL_OBJLAST
                                ); if (r < 0) return false;

                                r = engine.RegisterObjectBehaviour(
                                    func_cstr,
                                    asBEHAVE_DESTRUCT,
                                    meta::end_cstr(),
                                    asFUNCTION(type::end),
                                    asCALL_CDECL_OBJLAST
                                ); if (r < 0) return false;

                                return true;
                            }
                        };
                        typedef duration_cast_ct type;
                        const asQWORD flags = asOBJ_VALUE | asOBJ_APP_CLASS_CD ;

                        std::string ns = DurationT_type_info.GetNamespace(); if (!ns.empty()) ns += "::";

                        NamespaceRAII NamespaceRAII(engine);

                        engine.SetDefaultNamespace(ns.c_str());

                        int r = engine.RegisterObjectType(
                            type_str.c_str(),
                            sizeof(type),
                            flags
                        );

                        if (asALREADY_REGISTERED != r)
                        {
                            assert(r >= 0);

                            r = !type::register_behaviours(engine,
                                static_cast<namespace_cstr>(ns.c_str()),
                                static_cast<type_cstr>(type_str.c_str()),
                                subtype
                            ) ? -1 : 0; assert(r >= 0);

                            r = !type::register_methods(engine,
                                static_cast<namespace_cstr>(ns.c_str()),
                                static_cast<type_cstr>(type_str.c_str()),
                                subtype
                            ) ? -1 : 0; assert(r >= 0);

                            r = engine.RegisterObjectMethod(
                                type_str.c_str(),
                                meta::count_cstr(buffer, static_cast<astd::subtype_cstr>(RepT_type.name())),
                                asMETHOD(type, count), asCALL_THISCALL
                            ); assert(r >= 0);
                        }
                    }

                    registering_generic_duration_interface = false;
                }

                for (asUINT i = 0; i < DurationT_type_info.GetBehaviourCount(); ++i)
                {
                    asEBehaviours beh;
                    asIScriptFunction* func = DurationT_type_info.GetBehaviourByIndex(i, &beh);

                    if (!func) continue;

                    if (beh != asBEHAVE_CONSTRUCT) continue;

                    return true;
                }

                return false;
            }

            duration_cast(const duration& value)
                : duration(value) {}

            template<class DurationCastT>
            static bool register_behaviours(asIScriptEngine& engine, const namespace_cstr& ns_name, const type_cstr& func_name, const subtype_cstr& subtype_name)
            {
                typedef duration_cast type;
                typedef typename DurationCastT::meta meta;
                int r = 0;
                const char* func_cstr = func_name.cstr;
                const char* subtype_cstr = subtype_name.cstr;
                const char* namespace_cstr = ns_name.cstr;
                char buffer[1024] = { 0 };
                using namespace std;


                r = engine.RegisterObjectBehaviour(
                    func_cstr,
                    asBEHAVE_CONSTRUCT,
                    meta::ctor_cstr(),
                    asFUNCTION(type::ctor),
                    asCALL_CDECL_OBJLAST
                ); if (r < 0) return false;

                r = engine.RegisterObjectBehaviour(
                    func_cstr,
                    asBEHAVE_CONSTRUCT, 
                    (sprintf(buffer, meta::copy_ctor_cstr(), subtype_cstr), buffer),
                    asFUNCTION(type::copy_ctor),
                    asCALL_CDECL_OBJLAST
                ); if (r < 0) return false;

                r = engine.RegisterObjectBehaviour(
                    func_cstr,
                    asBEHAVE_CONSTRUCT,
                    (sprintf(buffer, meta::call_cstr(), namespace_cstr, subtype_cstr), buffer),
                    asFUNCTION(type::call),
                    asCALL_CDECL_OBJLAST
                ); if (r < 0) return false;

                r = engine.RegisterObjectBehaviour(
                    func_cstr,
                    asBEHAVE_DESTRUCT,
                    meta::end_cstr(),
                    asFUNCTION(type::end),
                    asCALL_CDECL_OBJLAST
                ); if (r < 0) return false;

                return true;
            }

            static bool register_behaviours(asIScriptEngine& engine, 
                const namespace_cstr& ns_name,
                const type_cstr& func_name = static_cast<type_cstr>(meta::func_cstr()), 
                const subtype_cstr& subtype_name = static_cast<subtype_cstr>("T")
            )
            {
                return register_behaviours<duration_cast>(engine, ns_name, func_name, subtype_name);
            }

            template<class DurationCastT>
            static bool register_methods(asIScriptEngine& engine,
                const namespace_cstr& ns_name = static_cast<namespace_cstr>(""),
                const type_cstr& func_name = static_cast<type_cstr>(meta::func_cstr()),
                const subtype_cstr& subtype_name = static_cast<subtype_cstr>("T")
            )
            {
                typedef duration_cast type;
                typedef typename DurationCastT::meta meta;
                int r = 0;
                const char* func_cstr = func_name.cstr;
                const char* subtype_cstr = subtype_name.cstr;
                char buffer[1024] = { 0 };
                using namespace std;

                r = engine.RegisterObjectMethod(
                    func_cstr,
                    (sprintf(buffer, meta::result_cstr(), subtype_cstr), buffer),
                    asFUNCTION(type::result),
                    asCALL_CDECL_OBJLAST
                ); if (r < 0) return false;

                r = engine.RegisterObjectMethod(
                    func_cstr,
                    (sprintf(buffer, meta::result_const_cstr(), subtype_cstr), buffer),
                    asFUNCTION(type::result),
                    asCALL_CDECL_OBJLAST
                ); if (r < 0) return false;

                return duration::template register_methods<DurationCastT>(engine,
                    ns_name,
                    func_name
                );
            }

            static bool register_methods(asIScriptEngine& engine,
                const namespace_cstr& ns_name = static_cast<namespace_cstr>(""),
                const type_cstr& func_name = static_cast<type_cstr>(meta::func_cstr()),
                const subtype_cstr& subtype_name = static_cast<subtype_cstr>("T")
            )
            {
                return register_methods<duration_cast>(engine, ns_name, func_name, subtype_name);
            }
        };

        namespace os {
            typedef astd::os::get_time_callback (&get_time_callbacks)[astd::os::get_time_size];
            template<int>
            static astd::os::get_time_callback(&get_time())[astd::os::get_time_size];
            template<>
            get_time_callbacks get_time<0>()
            {
                return astd::os::get_system_time;
            }
            template<>
            get_time_callbacks get_time<1>()
            {
                return astd::os::get_steady_time;
            }

            using astd::os::get_time_nanosec_callback;
            using astd::os::get_time_microsec_callback;
            using astd::os::get_time_millisec_callback;
            using astd::os::get_time_seconds_callback;
            using astd::os::get_time_callback;
        }

        template<int ClockType, class T>
        struct clock;
        //enum {ClockType}; // left there for template debugging purposes only (comment template<int...> + uncomment enum{...})
        template<int ClockType>
        struct clock<ClockType, nanoseconds>
        {
            struct meta
            {
                static const char* duration_type_cstr() throw() { return "nanoseconds"; }
            };

            typedef nanoseconds duration;
            typedef chrono::time_point_ct<clock, duration> time_point;

            static time_point now() {

                static  os::get_time_callbacks get_time = os::get_time<ClockType>();
                static  os::get_time_callback callback =
                    get_time[os::get_time_nanosec_callback] ? get_time[os::get_time_nanosec_callback] :
                    get_time[os::get_time_microsec_callback] ? get_time[os::get_time_microsec_callback] :
                    get_time[os::get_time_millisec_callback] ? get_time[os::get_time_millisec_callback] :
                    get_time[os::get_time_seconds_callback];

                static  asUINTMAX div = 1;
                static  asUINTMAX num =
                    get_time[os::get_time_nanosec_callback] == callback ? 1 :
                    get_time[os::get_time_microsec_callback] == callback ? 1000 :
                    get_time[os::get_time_millisec_callback] == callback ? 1000 * 1000 :
                    get_time[os::get_time_seconds_callback] == callback ? 1000 * 1000 * 1000 : (std::abort(), 0);
                return time_point(callback()* num / div);
            }
        };

        template<int ClockType>
        struct clock<ClockType, microseconds>
        {
            struct meta
            {
                static const char* duration_type_cstr() throw() { return "microseconds"; }
            };

            typedef microseconds duration;
            typedef chrono::time_point_ct<clock, duration> time_point;

            static time_point now() {

                static  os::get_time_callbacks get_time = os::get_time<ClockType>();
                static  os::get_time_callback callback =
                    get_time[os::get_time_microsec_callback] ? get_time[os::get_time_microsec_callback] :
                    get_time[os::get_time_nanosec_callback] ? get_time[os::get_time_nanosec_callback] :
                    get_time[os::get_time_millisec_callback] ? get_time[os::get_time_millisec_callback] :
                    get_time[os::get_time_seconds_callback];

                static  asUINTMAX div =
                    get_time[os::get_time_nanosec_callback] == callback ? 1000 : 1;
                static  asUINTMAX num =
                    get_time[os::get_time_nanosec_callback] == callback ? 1 :
                    get_time[os::get_time_microsec_callback] == callback ? 1 :
                    get_time[os::get_time_millisec_callback] == callback ? 1000 :
                    get_time[os::get_time_seconds_callback] == callback ? 1000 * 1000 : (std::abort(), 0);
                return time_point(callback() * num / div);
            }
        };

        template<int ClockType>
        struct clock<ClockType, milliseconds>
        {
            struct meta
            {
                static const char* duration_type_cstr() throw() { return "milliseconds"; }
            };

            typedef milliseconds duration;
            typedef chrono::time_point_ct<clock, duration> time_point;

            static time_point now() {

                static  os::get_time_callbacks get_time = os::get_time<ClockType>();
                static  os::get_time_callback callback =
                    get_time[os::get_time_millisec_callback] ? get_time[os::get_time_millisec_callback] :
                    get_time[os::get_time_microsec_callback] ? get_time[os::get_time_microsec_callback] :
                    get_time[os::get_time_nanosec_callback] ? get_time[os::get_time_nanosec_callback] :
                    get_time[os::get_time_seconds_callback];

                static  asUINTMAX div =
                    get_time[os::get_time_microsec_callback] == callback ? 1000 :
                    get_time[os::get_time_nanosec_callback] == callback ? 1000 * 1000 : 1;
                static  asUINTMAX num =
                    get_time[os::get_time_nanosec_callback] == callback ? 1 :
                    get_time[os::get_time_microsec_callback] == callback ? 1 :
                    get_time[os::get_time_millisec_callback] == callback ? 1 :
                    get_time[os::get_time_seconds_callback] == callback ? 1000  : (std::abort(), 0);
                return time_point(callback() * num / div);
            }
        };

        template<int ClockType>
        struct clock<ClockType, seconds>
        {
            struct meta
            {
                static const char* duration_type_cstr() throw() { return "seconds"; }
            };

            typedef seconds duration;
            typedef chrono::time_point_ct<clock, duration> time_point;

            static time_point now() {

                static  os::get_time_callbacks get_time = os::get_time<ClockType>();
                static  os::get_time_callback callback =
                    get_time[os::get_time_seconds_callback] ? get_time[os::get_time_seconds_callback] :
                    get_time[os::get_time_millisec_callback] ? get_time[os::get_time_millisec_callback] :
                    get_time[os::get_time_microsec_callback] ? get_time[os::get_time_microsec_callback] :
                    get_time[os::get_time_nanosec_callback] ? get_time[os::get_time_nanosec_callback] :
                    NULL;

                static  asUINTMAX div =
                    get_time[os::get_time_millisec_callback] == callback ? 1000 :
                    get_time[os::get_time_microsec_callback] == callback ? 1000 * 1000 :
                    get_time[os::get_time_nanosec_callback] == callback ? 1000 * 1000 * 1000 : 1;
                static  asUINTMAX num =
                    get_time[os::get_time_nanosec_callback] == callback ? 1 :
                    get_time[os::get_time_microsec_callback] == callback ? 1 :
                    get_time[os::get_time_millisec_callback] == callback ? 1 :
                    get_time[os::get_time_seconds_callback] == callback ? 1 : (std::abort(),0);
                return time_point(callback() * num / div);
            }
        };

        struct system_clock {

            static const bool uintmax_can_be_nano = sizeof(asUINTMAX) > 8;
            static const bool time_t_can_be_nano = sizeof(static_cast<os::get_time_callback>(NULL)()) > 8;
            static const bool uintmax_can_be_micro = sizeof(asUINTMAX) > 5;
            static const bool time_t_can_be_micro = sizeof(static_cast<os::get_time_callback>(NULL)()) > 5;

            typedef
            detail::conditional< 
                uintmax_can_be_nano && time_t_can_be_nano,
                chrono::nanoseconds,
                detail::conditional <
                uintmax_can_be_micro && time_t_can_be_micro,
                chrono::microseconds,
                chrono::milliseconds>::type
            >::type duration_impl;

            typedef clock<0, duration_impl> implementation;
            typedef implementation::duration duration;
            typedef implementation::time_point time_point;

            struct meta
                : implementation::meta
            {
                static const char* type_cstr() throw() { return "system_clock"; }

                static const char* now_cstr() throw() { return "time_point now()"; }
            };

        };

        struct steady_clock {

            static const bool uintmax_can_be_nano = sizeof(asUINTMAX) >= 8;
            static const bool time_t_can_be_nano = sizeof(static_cast<os::get_time_callback>(NULL)()) >= 8;
            static const bool uintmax_can_be_micro = sizeof(asUINTMAX) > 4;
            static const bool time_t_can_be_micro = sizeof(static_cast<os::get_time_callback>(NULL)()) > 4;

            typedef
            detail::conditional< 
                uintmax_can_be_nano && time_t_can_be_nano,
                chrono::nanoseconds,
                detail::conditional <
                uintmax_can_be_micro && time_t_can_be_micro,
                chrono::microseconds,
                chrono::milliseconds>::type
            >::type duration_impl;

            typedef clock<1, duration_impl> implementation;
            typedef implementation::duration duration;
            typedef implementation::time_point time_point;

            struct meta
                : implementation::meta
            {
                static const char* type_cstr() throw() { return "steady_clock"; }

                static const char* now_cstr() throw() { return "time_point now()"; }
            };
        };
    }
}



namespace astd_script {
    using namespace astd;

    namespace {
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

#   define RegisterScriptStdFunction(N) \
        template<> struct RegisterScriptStdFunctionHelperN<N> \
        { static void call(asIScriptEngine * engine); static void call_next(asIScriptEngine * engine) { call(engine); RegisterScriptStdFunctionHelper<N+1>::call(engine); } }; void RegisterScriptStdFunctionHelperN<N>::call
    
    enum {
        duration, duration_cast, time_point, system_clock, steady_clock
    };

    template<class T, bool = chrono::type_traits::is_duration<T>::value>
    struct register_duration {
        int call(asIScriptEngine&, const std::string&, const std::string&)
        {
            return -1;
        }
    };

    template<class T>
    struct register_duration <T, true> {
        static int call(asIScriptEngine &engine, const std::string &type_str, const std::string &subtype_str, const std::string &ns)
        {
            typedef T type;

            int r = 0;

            const asQWORD flags = asOBJ_VALUE | asOBJ_APP_CLASS_CD;

            r = engine.RegisterObjectType(
                type_str.c_str(),
                sizeof(type),
                flags
            ); assert(r >= 0);

            // typedefs imitation
            r = !type::register_typedefs(engine, 
                static_cast<type_cstr>(type_str.c_str())
            ) ? -1 : 0; assert(r >= 0);

            // behaviour (ctor, dtor etc.)
            r = !type::register_behaviours(engine, 
                static_cast<namespace_cstr>(ns.c_str()), 
                static_cast<type_cstr>(type_str.c_str()), 
                static_cast<subtype_cstr>(subtype_str.c_str())
            ) ? -1 : 0; assert(r >= 0);

            // member functions
            r = !type::register_methods(engine, 
                static_cast<namespace_cstr>(ns.c_str()), 
                static_cast<type_cstr>(type_str.c_str()), 
                static_cast<subtype_cstr>(subtype_str.c_str())
            ) ? -1 : 0; assert(r >= 0);

            return r;
        }
    };

    RegisterScriptStdFunction(duration)(asIScriptEngine* engine)
    {
        int r = 0;
        std::string ns = engine->GetDefaultNamespace(); if (!ns.empty()) ns += "::";

        const asQWORD flags = asOBJ_VALUE | asOBJ_APP_CLASS_CD;

        astd::chrono::duration<asUINTMAX>::meta::registering() = true;

        // duration
        {
            typedef astd::chrono::duration<asUINTMAX> type;

            r = engine->RegisterObjectType(
                type::meta::type_cstr(),
                sizeof(type),
                flags | asOBJ_TEMPLATE
            ); assert(r >= 0);

            r = engine->RegisterObjectBehaviour(
                type::meta::type_cstr(),
                asBEHAVE_TEMPLATE_CALLBACK,
                type::meta::template_callback_cstr(),
                asFUNCTION(type::template_callback),
                asCALL_CDECL
            ); assert(r >= 0);

            // behaviour (ctor, dtor etc.)
            r = !type::register_behaviours(*engine
            ) ? -1 : 0; assert(r >= 0);

            // member functions
            r = !type::register_methods(*engine, 
                static_cast<namespace_cstr>(ns.c_str())
            ) ? -1 : 0; assert(r >= 0);
        }

        // ratio
        assert(engine->GetTypeInfoByDecl("ratio<intmax, intmax>") != NULL);

        // nanoseconds
        {
            typedef astd::chrono::nanoseconds type;
            const std::string type_str = "nanoseconds";
            const std::string subtype_str = ns + type_str + "::period";

            if (chrono::type_traits::is_duration<type>::value)
                r = register_duration<type>::call(*engine, type_str, subtype_str, ns); assert(r >= 0);
        }

        // microseconds
        {
            typedef astd::chrono::microseconds type;
            const std::string type_str = "microseconds";
            const std::string subtype_str = ns + type_str + "::period";

            if (chrono::type_traits::is_duration<type>::value)
                r = register_duration<type>::call(*engine, type_str, subtype_str, ns); assert(r >= 0);
        }

        // milliseconds
        {
            typedef astd::chrono::milliseconds type;
            const std::string type_str = "milliseconds";
            const std::string subtype_str = ns + type_str + "::period";

            if (chrono::type_traits::is_duration<type>::value)
                r = register_duration<type>::call(*engine, type_str, subtype_str, ns); assert(r >= 0);
        }

        // seconds
        {
            typedef astd::chrono::seconds type;
            const std::string type_str = "seconds";
            const std::string subtype_str = ns + type_str + "::period";

            if (chrono::type_traits::is_duration<type>::value)
                r = register_duration<type>::call(*engine, type_str, subtype_str, ns); assert(r >= 0);
        }

        // minutes
        {
            typedef astd::chrono::minutes type;
            const std::string type_str = "minutes";
            const std::string subtype_str = ns + type_str + "::period";

            if (chrono::type_traits::is_duration<type>::value)
                r = register_duration<type>::call(*engine, type_str, subtype_str, ns); assert(r >= 0);
        }

        // hours
        {
            typedef astd::chrono::hours type;
            const std::string type_str = "hours";
            const std::string subtype_str = ns + type_str + "::period";

            if (chrono::type_traits::is_duration<type>::value)
                r = register_duration<type>::call(*engine, type_str, subtype_str, ns); assert(r >= 0);
        }


        astd::chrono::duration<asUINTMAX>::meta::registering() = false;
        r = engine->SetDefaultNamespace(ns.c_str()); assert(r >= 0);
    }

    RegisterScriptStdFunction(time_point)(asIScriptEngine* engine)
    {
        int r = 0;
        std::string ns = engine->GetDefaultNamespace(); if (!ns.empty()) ns += "::";

        typedef astd::chrono::time_point type;

        r = engine->RegisterObjectType(
            type::meta::type_cstr(),
            sizeof(type),
            asOBJ_VALUE | asOBJ_APP_CLASS_CD | asOBJ_TEMPLATE
        ); assert(r >= 0);

        // behaviour (ctor, dtor etc.)
        r = !type::register_behaviours(*engine) ? -1 : 0; assert(r >= 0);

        // member functions
        r = !type::register_methods(*engine) ? -1 : 0; assert(r >= 0);

        r = engine->SetDefaultNamespace(ns.c_str()); assert(r >= 0);
    }

    RegisterScriptStdFunction(system_clock)(asIScriptEngine* engine)
    {
        int r = 0;
        std::string ns = engine->GetDefaultNamespace(); if (!ns.empty()) ns += "::";

        typedef astd::chrono::system_clock type;

        r = engine->SetDefaultNamespace((ns + type::meta::type_cstr() + "::").c_str()); assert(r >= 0);

        const std::string duration_type_str = type::meta::duration_type_cstr();

        // time_point typedef
        {
            r = engine->RegisterObjectType(
                "time_point",
                sizeof(type::time_point),
                asOBJ_VALUE | asOBJ_APP_CLASS_CD
            ); assert(r >= 0);


            r = !type::time_point::register_behaviours(*engine, 
                static_cast<type_cstr>("time_point"), 
                static_cast<subtype_cstr>(duration_type_str.c_str())
            ) ? -1 : 0; assert(r >= 0);
            r = !type::time_point::register_methods(*engine, 
                static_cast<type_cstr>("time_point"),
                static_cast<subtype_cstr>(duration_type_str.c_str())
            ) ? -1 : 0; assert(r >= 0);
        }

        // duration typedef
        {
            const char *type_cstr = "duration";
            const std::string subtype_str = ns + duration_type_str + "::period";
            r = engine->RegisterObjectType(
                type_cstr,
                sizeof(type::duration),
                asOBJ_VALUE | asOBJ_APP_CLASS_CD
            ); assert(r >= 0);


            {
                char buffer[1024] = { 0 };
                using namespace std;
                typedef type::duration type;

                r = engine->RegisterObjectBehaviour(
                    type_cstr,
                    asBEHAVE_CONSTRUCT,
                    (sprintf(buffer, type::meta::copy_ctor_cstr(), duration_type_str.c_str()), buffer),
                    asFUNCTIONPR(type::copy_ctor, (const type&, type&), void), asCALL_CDECL_OBJLAST
                ); assert(r >= 0);

                r = engine->RegisterObjectMethod(
                    type_cstr,
                    ("const " + duration_type_str + " & opImplCast() const").c_str(),
                    asFUNCTIONPR(type::duration_cast, (type&), astd::chrono::duration<asUINTMAX>*), asCALL_CDECL_OBJLAST
                ); assert(r >= 0);
            }

            r = !type::duration::register_behaviours(*engine, 
                static_cast<namespace_cstr>(ns.c_str()), 
                static_cast<astd::type_cstr>(type_cstr),
                static_cast<astd::subtype_cstr>(subtype_str.c_str())
            ) ? -1 : 0; assert(r >= 0);
            r = !type::duration::register_methods(*engine, 
                static_cast<namespace_cstr>(ns.c_str()), 
                static_cast<astd::type_cstr>(type_cstr),
                static_cast<astd::subtype_cstr>(subtype_str.c_str())
            ) ? -1 : 0; assert(r >= 0);
        }

        r = engine->RegisterGlobalFunction(
            type::meta::now_cstr(),
            asFUNCTION(type::implementation::now),
            asCALL_CDECL
        ); assert(r >= 0);



        r = engine->SetDefaultNamespace(ns.c_str()); assert(r >= 0);
    }


    RegisterScriptStdFunction(steady_clock)(asIScriptEngine* engine)
    {
        int r = 0;
        std::string ns = engine->GetDefaultNamespace(); if (!ns.empty()) ns += "::";

        typedef astd::chrono::steady_clock type;

        r = engine->SetDefaultNamespace((ns + type::meta::type_cstr() + "::").c_str()); assert(r >= 0);

        const std::string duration_type_str = type::meta::duration_type_cstr();

        // time_point typedef
        {
            r = engine->RegisterObjectType(
                "time_point",
                sizeof(type::time_point),
                asOBJ_VALUE | asOBJ_APP_CLASS_CD
            ); assert(r >= 0);


            r = !type::time_point::register_behaviours(*engine, 
                static_cast<type_cstr>("time_point"), 
                static_cast<subtype_cstr>(duration_type_str.c_str())
            ) ? -1 : 0; assert(r >= 0);
            r = !type::time_point::register_methods(*engine, 
                static_cast<type_cstr>("time_point"),
                static_cast<subtype_cstr>(duration_type_str.c_str())
            ) ? -1 : 0; assert(r >= 0);
        }

        // duration typedef
        {
            const char* type_cstr = "duration";
            const std::string subtype_str = ns + duration_type_str + "::period";
            r = engine->RegisterObjectType(
                "duration",
                sizeof(type::duration),
                asOBJ_VALUE | asOBJ_APP_CLASS_CD
            ); assert(r >= 0);


            {
                char buffer[1024] = { 0 };
                using namespace std;
                typedef type::duration type;

                r = engine->RegisterObjectBehaviour(
                    type_cstr,
                    asBEHAVE_CONSTRUCT,
                    (sprintf(buffer, type::meta::copy_ctor_cstr(), duration_type_str.c_str()), buffer),
                    asFUNCTIONPR(type::copy_ctor, (const type&, type&), void), asCALL_CDECL_OBJLAST
                ); assert(r >= 0);

                r = engine->RegisterObjectMethod(
                    type_cstr,
                    ("const " + duration_type_str + " & opImplCast() const").c_str(),
                    asFUNCTIONPR(type::duration_cast, (type&), astd::chrono::duration<asUINTMAX>*), asCALL_CDECL_OBJLAST
                ); assert(r >= 0);
            }

            r = !type::duration::register_behaviours(*engine, 
                static_cast<namespace_cstr>(ns.c_str()), 
                static_cast<astd::type_cstr>(type_cstr),
                static_cast<astd::subtype_cstr>(subtype_str.c_str())
            ) ? -1 : 0; assert(r >= 0);
            r = !type::duration::register_methods(*engine, 
                static_cast<namespace_cstr>(ns.c_str()), 
                static_cast<astd::type_cstr>(type_cstr),
                static_cast<astd::subtype_cstr>(subtype_str.c_str())
            ) ? -1 : 0; assert(r >= 0);
        }

        r = engine->RegisterGlobalFunction(
            type::meta::now_cstr(),
            asFUNCTION(type::implementation::now),
            asCALL_CDECL
        ); assert(r >= 0);



        r = engine->SetDefaultNamespace(ns.c_str()); assert(r >= 0);
    }


    RegisterScriptStdFunction(duration_cast)(asIScriptEngine* engine)
    {
        int r = 0;
        std::string ns = engine->GetDefaultNamespace(); if (!ns.empty()) ns += "::";

        const asQWORD flags = asOBJ_VALUE | asOBJ_APP_CLASS_CD | asOBJ_TEMPLATE;


        typedef astd::chrono::duration_cast<asUINTMAX> type;
        typedef type::meta meta;

        r = engine->RegisterObjectType(
            meta::func_cstr(),
            sizeof(type),
            flags
        ); assert(r >= 0);


        r = engine->RegisterObjectBehaviour(
            meta::func_cstr(),
            asBEHAVE_TEMPLATE_CALLBACK,
            meta::template_callback_cstr(),
            asFUNCTION(type::template_callback),
            asCALL_CDECL
        ); assert(r >= 0);

        r = !type::register_behaviours(*engine,
            static_cast<namespace_cstr>(ns.c_str())
        ) ? -1 : 0; assert(r >= 0);

        r = !type::register_methods(*engine, 
            static_cast<namespace_cstr>(ns.c_str())
        ) ? -1 : 0; assert(r >= 0);

        r = engine->SetDefaultNamespace(ns.c_str()); assert(r >= 0);
    }

#   undef RegisterScriptStdFunction


    }

    static void RegisterScriptStdFunctions(asIScriptEngine* engine)
    {
        typedef RegisterScriptStdFunctionHelper<0> functions;
        functions::call(engine);
    }
}

int RegisterScriptStd_Chrono_Native(asIScriptEngine *engine)
{
    int r;  

    const std::string ns = engine->GetDefaultNamespace();

    r = engine->SetDefaultNamespace("std::chrono"); assert(r >= 0); if (r < 0) return r;

    astd_script::RegisterScriptStdFunctions(engine);

    r = engine->SetDefaultNamespace("chrono"); assert(r >= 0); if (r < 0) return r;

    astd_script::RegisterScriptStdFunctions(engine);

    r = engine->SetDefaultNamespace(ns.c_str()); assert(r >= 0); if (r < 0) return r;

    return r;
}


int RegisterScriptStd_Chrono_Generic(asIScriptEngine *engine)
{
    int r = 0;

    // double versions of the same
    //r = engine->RegisterGlobalFunction("double cos(double)", asFUNCTION(cos_generic), asCALL_GENERIC); assert( r >= 0 );

    return r;
}

int RegisterScriptStd_Chrono(asIScriptEngine *engine)
{
    if( strstr(asGetLibraryOptions(), "AS_MAX_PORTABILITY") )
        return RegisterScriptStd_Chrono_Generic(engine);
    else
        return RegisterScriptStd_Chrono_Native(engine);
}

END_AS_NAMESPACE



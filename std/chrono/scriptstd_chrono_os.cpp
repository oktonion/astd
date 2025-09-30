#include "scriptstd_chrono_os.h"

#include <cstring>

namespace astd { namespace os
{
    namespace horrible_fallback {
        static std::time_t get_time_mcs()
        {
            using namespace std;
            clock_t time = clock();
            return (double(time) / double(CLOCKS_PER_SEC) * 1000.0 * 1000.0) + 0.5;
        }
        static std::time_t get_time_ms()
        {
            using namespace std;
            clock_t time = clock();
            return (double(time) / double(CLOCKS_PER_SEC) * 1000.0) + 0.5;
        }
        static std::time_t get_time_s()
        {
            using namespace std;
            clock_t time = clock();
            return (double(time) / double(CLOCKS_PER_SEC) ) + 0.5;
        }
    }

}}

#if defined(WIN32) || defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// errno
#include <errno.h>



namespace astd { namespace os {namespace
{
    static LONGLONG GetPerformanceTicksInSecond()
    {
        LARGE_INTEGER nFreq;

        ::QueryPerformanceFrequency(&nFreq);

        return nFreq.QuadPart;
    }

    static LONGLONG GetPerformanceTicks()
    {
        LONGLONG start = 0;
        LARGE_INTEGER nValue;
        ::QueryPerformanceCounter(&nValue);

        {
            static LONGLONG GetPerformanceTicks = nValue.QuadPart;

            if (GetPerformanceTicks > nValue.QuadPart)
                GetPerformanceTicks = nValue.QuadPart;
            start = GetPerformanceTicks;
        }

        return nValue.QuadPart - start;
    }

    static LONGLONG GetPrecisionMultiplier(LONGLONG nTicks)
    {
        const LONGLONG result =
            nTicks < (ULONGLONG(-1) / 2) / 1000000
            ? 1000000
            : nTicks < (ULONGLONG(-1) / 2) / 100000
            ? 100000
            : nTicks < (ULONGLONG(-1) / 2) / 10000
            ? 10000
            : nTicks < (ULONGLONG(-1) / 2) / 1000
            ? 1000
            : nTicks < (ULONGLONG(-1) / 2) / 100
            ? 100
            : nTicks < (ULONGLONG(-1) / 2) / 10
            ? 10
            : 1;

        return result;
    }

    static const LONGLONG PerformanceTicksInSecond = GetPerformanceTicksInSecond();
    static LONGLONG PrecisionMultiplier = GetPrecisionMultiplier(GetPerformanceTicks());
    static LONGLONG PerformanceTicksMax = (ULONGLONG(-1) / 2) / PrecisionMultiplier;

    static LONGLONG GetTickNanoseconds(const LONGLONG& nTicks, const LONGLONG& nFreq)
    {
        // nTicks              - elapsed ticks
        // nTicks * 1000000000 - elapsed ticks nanoseconds
        // nFreq               - ticks-per-second
        // nFreq / 1000000000  - ticks-per-nanoseconds

        const LONGLONG precision_multp =
            nTicks < PerformanceTicksMax
            ? PrecisionMultiplier
            : (PrecisionMultiplier = GetPrecisionMultiplier(nTicks),
                (PerformanceTicksMax = (ULONGLONG(-1) / 2) / PrecisionMultiplier), PrecisionMultiplier);

        const LONGLONG precision_div = 1000000000 / precision_multp;

        return (nTicks * precision_multp) / (nFreq / precision_div);
    }

    static LONGLONG GetTickMicroseconds(const LONGLONG& nTicks, const LONGLONG& nFreq)
    {
        // nTicks           - elapsed ticks
        // nTicks * 1000000 - elapsed ticks microseconds
        // nFreq            - ticks-per-second
        // nFreq / 1000000  - ticks-per-microsecond

        const LONGLONG precision_multp =
            nTicks < PerformanceTicksMax
            ? PrecisionMultiplier
            : (PrecisionMultiplier = GetPrecisionMultiplier(nTicks),
                (PerformanceTicksMax = (ULONGLONG(-1) / 2) / PrecisionMultiplier), PrecisionMultiplier);

        const LONGLONG precision_div = 1000000 / precision_multp;

        return (nTicks * precision_multp) / (nFreq / precision_div);
    }


    static ULONGLONG GetSystemTimeMicroseconds()
    {
        SYSTEMTIME time;
        GetSystemTime(&time);

        SYSTEMTIME time_epoch;
        if (sizeof(std::time_t) > 4)
        {
            time_epoch.wYear = 1970;
        }
        else
        {
            time_epoch.wYear = 2000;
        }
        time_epoch.wMonth = 1;
        time_epoch.wDay = 1;
        time_epoch.wHour = 1;
        time_epoch.wMinute = 1;
        time_epoch.wSecond = 1;
        time_epoch.wMilliseconds = 0;

        FILETIME file_time, file_time_epoch;

        if (!SystemTimeToFileTime(&time_epoch, &file_time_epoch))
            return 0;

        if (!SystemTimeToFileTime(&time, &file_time))
            return 0;

        ULARGE_INTEGER uint_time, uint_time_epoch;
        std::memcpy(&uint_time, &file_time, sizeof(file_time));
        std::memcpy(&uint_time_epoch, &file_time_epoch, sizeof(file_time_epoch));

        if (uint_time.QuadPart > uint_time_epoch.QuadPart)
            return (uint_time.QuadPart - uint_time_epoch.QuadPart) / 10;

        return 0;
    }

    static std::time_t get_steady_time_nanos()
    {
        return GetTickNanoseconds(GetPerformanceTicks(), PerformanceTicksInSecond);
    }
    static os::get_time_callback get_system_time_nanos = NULL;

    static std::time_t get_steady_time_micros()
    {
        return GetTickMicroseconds(GetPerformanceTicks(), PerformanceTicksInSecond);
    }

    static std::time_t get_system_time_micros()
    {
        return GetSystemTimeMicroseconds();
    }

    static std::time_t get_steady_time_millis()
    {
        return get_steady_time_micros() / 1000;
    }
    static std::time_t get_system_time_millis()
    {
        return GetSystemTimeMicroseconds() / 1000;
    }

    static std::time_t get_steady_time_sec()
    {
        return get_system_time_millis() / 1000;
    }
    static std::time_t get_system_time_sec()
    {
        return get_system_time_millis() / 1000;
    }
}}} 

#else
#include <sys/time.h>

namespace astd { namespace os { namespace
{
    static struct timeval gettimeofday() {
        struct timeval time_now;
        time_now.tv_sec = 0;
        time_now.tv_usec = 0;
        gettimeofday(&time_now, 0);
        return time_now;
    }

    static os::get_time_callback get_steady_time_nanos = NULL;
    static os::get_time_callback get_system_time_nanos = NULL;

    static std::time_t get_steady_time_micros()
    {
        struct timeval time_now = gettimeofday();
        struct timeval start;
        {
            static struct timeval start_time = time_now;

            if (start_time.tv_sec > time_now.tv_sec)
                start_time = time_now;
            start = start_time;
        }
        const time_t msecs_time =
            ((time_now.tv_sec - start.tv_sec) * 1000 * 1000) + ((time_now.tv_usec - start.tv_usec) );

        return msecs_time;
    }
    static std::time_t get_system_time_micros()
    {
        struct timeval time_now = gettimeofday();
        const time_t msecs_time =
            ((time_now.tv_sec) * 1000 * 1000) + ((time_now.tv_usec));

        return msecs_time;
    }

    static std::time_t get_steady_time_millis()
    {
        struct timeval time_now = gettimeofday();
        struct timeval start;
        {
            static struct timeval start_time = time_now;

            if (start_time.tv_sec > time_now.tv_sec)
                start_time = time_now;
            start = start_time;
        }
        const time_t msecs_time =
            ((time_now.tv_sec - start.tv_sec) * 1000) + ((time_now.tv_usec - start.tv_usec) / 1000);

        return msecs_time;
    }
    static std::time_t get_system_time_millis()
    {
        struct timeval time_now = gettimeofday();
        const time_t msecs_time =
            ((time_now.tv_sec) * 1000) + ((time_now.tv_usec) / 1000);

        return msecs_time;
    }

    static std::time_t get_steady_time_sec()
    {
        return get_system_time_millis() / 1000;
    }
    static std::time_t get_system_time_sec()
    {
        return get_system_time_millis() / 1000;
    }
}}}
#endif

namespace astd { namespace os {

    get_time_callback get_system_time[] = {
        sizeof(std::time_t) > 4 ? get_system_time_nanos : NULL,
        sizeof(std::time_t) > 2 ? get_system_time_micros : NULL,
        sizeof(std::time_t) > 2 ? get_system_time_millis : NULL,
        get_system_time_sec
    };
    get_time_callback get_steady_time[] = {
        sizeof(std::time_t) > 3 ? get_steady_time_nanos : NULL,
        sizeof(std::time_t) > 2 ? get_steady_time_micros : NULL,
        sizeof(std::time_t) > 2 ? get_steady_time_millis : NULL,
        get_steady_time_sec
    };
}}
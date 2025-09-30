#include <ctime>

namespace astd {
    namespace os {

        typedef std::time_t(*get_time_callback)();

        enum {
            get_time_nanosec_callback,
            get_time_microsec_callback,
            get_time_millisec_callback,
            get_time_seconds_callback,
            get_time_size
        };
        extern get_time_callback get_system_time[get_time_size];
        extern get_time_callback get_steady_time[get_time_size];
    }
}
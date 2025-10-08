
#include "./print_and_math_script.as"
#include "./co_script.as"
#include "./chrono_script.as"

int chrono_and_print_test() {
      std::chrono::system_clock::time_point begin_sys = std::chrono::system_clock::now();
      std::chrono::steady_clock::time_point begin_st = std::chrono::steady_clock::now();
      auto end_sys = std::chrono::system_clock::now();
      auto end_st = std::chrono::steady_clock::now();
      std::chrono::system_clock::duration period_sys = end_sys - begin_sys;
      std::chrono::steady_clock::duration period_st = end_st - begin_st;
	  
      auto period_mcs_sys = std::chrono::duration_cast<std::chrono::microseconds>(period_sys);
      auto period_mcs_st = std::chrono::duration_cast<std::chrono::microseconds>(period_st);
	  
      auto period_auto_sys = end_sys - begin_sys;
      auto period_auto_st = end_st - begin_st;
      std::chrono::milliseconds period_ms_sys = std::chrono::duration_cast<std::chrono::milliseconds>(period_sys);
      std::chrono::milliseconds period_ms_st = std::chrono::duration_cast<std::chrono::milliseconds>(period_st);
      std::chrono::seconds period_s_sys = std::chrono::duration_cast<std::chrono::seconds>(period_sys);
      std::chrono::seconds period_s_st = std::chrono::duration_cast<std::chrono::seconds>(period_st);
      auto time_since_sys = begin_sys.time_since_epoch();
      auto time_since_st = begin_st.time_since_epoch();
      
      period_sys += period_sys;
	  
	  {
	      auto count = period_mcs_sys.count();
	  }
	  
      std::print("system clock: period_mcs := {:d}, period_ms := {:d}, period_s := {:d}, begin.time_since := {:d}, end.time_since := {:d}, now.time_since := {:d}\n", 
        period_mcs_sys.count(), period_ms_sys.count(), std::chrono::duration_cast<std::chrono::seconds>(period_sys).count(), time_since_sys.count(), end_sys.time_since_epoch().count(), std::chrono::system_clock::now().time_since_epoch().count()
	  );
      std::print("steady clock: period_mcs := {:d}, period_ms := {:d}, period_s := {:d}, begin.time_since := {:d}, end.time_since := {:d}, now.time_since := {:d}\n", 
        period_mcs_st.count(), period_ms_st.count(), std::chrono::duration_cast<std::chrono::seconds>(period_st).count(), time_since_st.count(), end_st.time_since_epoch().count(), std::chrono::steady_clock::now().time_since_epoch().count()
	  );
      
	  return 0;
}
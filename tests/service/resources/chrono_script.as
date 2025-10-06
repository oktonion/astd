

int chrono_test()
{
  // chrono
  {
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
  } 
  
  return 0;
}
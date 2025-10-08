

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

//int chrono_duration() 
//{
//    // duration
//    {
//        std::chrono::duration<int> d0(3);
//        std::chrono::duration<int> d1 = -d0;
//        if(!(d0.count() == 3)) return -1;
//        if(!(d1.count() == -3)) return -1;
//
//        std::chrono::duration<int> d2 = d0; // illigal operation on this data type (+d0);
//        if(!(d2.count() == 3)) return -1;
//
//        std::chrono::duration<int> d3(++d2);
//        if(!(d2.count() == 4)) return -1;
//        if(!(d3.count() == 4)) return -1;
//
//        std::chrono::duration<int> d4(d3++);
//        if(!(d3.count() == 5)) return -1;
//        if(!(d4.count() == 4)) return -1;
//
//        std::chrono::duration<int> d5(--d4);
//        if(!(d4.count() == 3)) return -1;
//        if(!(d5.count() == 3)) return -1;
//
//        std::chrono::duration<int> d6(d5--);
//        if(!(d5.count() == 2)) return -1;
//        if(!(d6.count() == 3)) return -1;
//    }    
//	
//	{
//        std::chrono::duration<int> d0(12);
//        std::chrono::duration<int> d1(3);
//        int i = 3;
//
//        std::chrono::duration<int> d2 = d0 + d1;
//        if(!(d2.count() == 15)) return -1;
//
//        std::chrono::duration<int> d3 = d0 - d1;
//        if(!(d3.count() == 9)) return -1;
//
//        std::chrono::duration<int> d4 = d0 * i;
//        if(!(d4.count() == 36)) return -1;
//
//        std::chrono::duration<int> d5 = i * d0;
//        if(!(d5.count() == 36)) return -1;
//
//        std::chrono::duration<int> d6 = d0 / i;
//        if(!(d6.count() == 4)) return -1;
//
//        int j = d0 / d1;
//        if(!(j == 4)) return -1;
//    } 
//	
//	
//	return 0;
//}
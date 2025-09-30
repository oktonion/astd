
class Timer {
    void opCall()
    { co_routine ();
    std::print("Timer::opCall 5\n");
        //promise_v().yield().unwrap(); // co_yield
        co_yield();
        
    std::print("Timer::opCall 8\n");
        
        co_await (async_wait_for(timeout_));
    std::print("Timer::opCall 11\n");
    }
    
    bool run_;
    int timeout_;
    
    Timer(int timeout, bool start_running) {
        run_ = start_running;
        timeout_ = timeout;
    }
};


class A { 
    void print_hello() { 
    printf("Hello World!\n");
        string result = format("answer is '{:d}', test", 11, 12); 
        std::print(result + "{:f}\n", cos(42));
        std::printf(result + "%f\n", std::cos(42));
        print(result + "{:d}\n", 42+11);
        printf(result + "%d\n", 43+11);
    } 
};

bool print_time = true;

int co_test()
{
    Timer t(1000, true);
	t();
	
	return 0;
}

int print_and_math_test()
{
    A a;
	a.print_hello();
	
	return 0;
}

int chrono_test()
{
  // chrono
  if (print_time)
  {
      print_time = false;
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
      
      std::print("system clock: period_mcs := {:d}, period_ms := {:d}, period_s := {:d}, begin.time_since := {:d}, end.time_since := {:d}, now.time_since := {:d}\n", 
        period_mcs_sys.count(), period_ms_sys.count(), std::chrono::duration_cast<std::chrono::seconds>(period_sys).count(), time_since_sys.count(), end_sys.time_since_epoch().count(), std::chrono::system_clock::now().time_since_epoch().count());
      std::print("steady clock: period_mcs := {:d}, period_ms := {:d}, period_s := {:d}, begin.time_since := {:d}, end.time_since := {:d}, now.time_since := {:d}\n", 
        period_mcs_st.count(), period_ms_st.count(), std::chrono::duration_cast<std::chrono::seconds>(period_st).count(), time_since_st.count(), end_st.time_since_epoch().count(), std::chrono::steady_clock::now().time_since_epoch().count());
      
      period_sys += period_sys;
  } 
  
  return 0;
}
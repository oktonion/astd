
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

int co_test()
{
    Timer t(1000, true);
	t();
	
	return 0;
}
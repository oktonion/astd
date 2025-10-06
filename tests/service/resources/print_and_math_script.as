
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


int print_and_math_test()
{
    A a;
	a.print_hello();
	
	return 0;
}
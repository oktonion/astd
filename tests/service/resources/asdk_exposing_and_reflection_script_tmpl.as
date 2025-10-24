

int asdk_exposing_and_reflection_test()
{
    {
        my_value_class<float> value;
        
        value.set_val(42);
        int ival = value.get_val();
        if (ival != 42) return -1;
    }
    
    {
        my_value_class<int> value(42);
        
        int ival = value.get_val();
        if (ival != 42) return -2;
    }
    
    {
        my_value_class<float> value(5.3);
        
        int ival = value.get_val();
        if (ival != 5) return -3;
    }
    
    return 0;
}


int asdk_exposing_and_reflection_test()
{
    {
        my_value_class value;
        
        value.set_val(42);
        int ival = value.get_val();
        if (ival != 42) return -1;
    }
    
    {
        my_value_class value(42);
        
        int ival = value.get_val();
        if (ival != 42) return -2;
    }
    
    {
        my_value_class value(5.3);
        
        int ival = value.get_val();
        if (ival != 5) return -3;
    }
    
    {
        my_value_class value1(5.3);
        my_value_class value2(5.2);
        
        if (!(value1 == value2)) return -4;
    }
    
    {
        my_value_class value1(5.3);
        my_value_class value2(4.2);
        
        if (value1 == value2) return -4;
    }
    
    {
        my_value_class value1(3.3);
        my_value_class value2(33);
        
        if (value1 == value2) return -4;
    }
    
    return 0;
}
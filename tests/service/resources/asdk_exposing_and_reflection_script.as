

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
        if (value1 != value2) return -5;
    }
    
    {
        my_value_class value1(5.3);
        my_value_class value2(4.2);
        
        if (value1 == value2) return -6;
    }
    
    {
        my_value_class value1(3.3);
        my_value_class value2(33);
        
        if (value1 == value2) return -7;
    }
    
    {
        my_value_class value1(2);
        my_value_class value2(3);
        
        if (value1 > value2) return -8;
        if (value2 < value1) return -9;
    }
    
    return 0;
}
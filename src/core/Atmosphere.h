/*
---------------------------------------
Inputs:
    - Altitude (m)

Process:
    if h > 25000 (Upper Stratosphere)
        T = -131.21 + 0.00299 h
        P = 2.488 * ((T+273.1)/216.6) ^ -11.388
    if h > 11000 and < 25000 (Lower Stratosphere)
        T = -56.46
        P = 22.65 * e^(1.73 - 0.000157 h)
    if h < 11000 (Troposphere)
        T = 15.04 - 0.00649 h
        P = 101.29 * ((T+273.1) / 288.08) ^ 5.256

    
Outputs:
    - Temperature
    - Pressure

*/

#pragma once

#include "./Station.h"
#include <cmath>

class Atmosphere
{
    public:
    int altitude;
    float T;
    float P;

    Atmosphere(int a):altitude(a)
    {


        if (altitude >= 25000)
        {
            T = -131.21 + 0.00299 * altitude;
            P = 2.488 * pow(((T+273.1)/216.6), -11.388);
        }
        else if (altitude >= 11000 && altitude < 25000)
        {
            T = -56.46;
            P = 22.65 * exp(1.73 - 0.000157 * altitude); 
        }
        else if (altitude <= 11000)
        {
            T = 15.04 - 0.00649 * altitude;
            P = 101.29 * pow(((T+273.1) / 288.08), 5.256);
        }

        
    }
};
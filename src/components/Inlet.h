/*
--------------------------------------------------
INLET

Input:
    - Inlet pressure
    - Inlet temperature
    - Mass flow rate

Process:
    1. Recieve air from atmosphere.
    2. Send the air without any changes to the outlet

Output:
    - Outlet pressure
    - Outlet temperature

Purpose:
    Takes air from atmosphere and sends through for
    the engine.
--------------------------------------------------
*/

#pragma once

#include "../core/Component.h"

class Inlet : public Component
{
    public:

    Inlet()
    {}

    void solve(
        const Station& inlet,
        Station& outlet) override
        {
            outlet.pressure = inlet.pressure;

            outlet.temperature = inlet.temperature;

            outlet.massFlow = inlet.massFlow;
        }
};
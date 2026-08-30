/*
--------------------------------------------------
COMPRESSOR

Input:
    - Inlet pressure
    - Inlet temperature
    - Mass flow rate
    - Pressure ratio
    - Compressor efficiency

Process:
    1. Receive air from the previous station.
    2. Increase the air pressure according to the
       specified pressure ratio.
    3. Calculate the temperature rise caused by
       compression.
    4. Account for compressor efficiency losses.
    5. Assume mass flow is conserved.

Output:
    - Outlet pressure
    - Outlet temperature
    - Outlet mass flow rate

Purpose:
    Adds energy to the airflow by increasing its
    pressure, preparing it for combustion.
--------------------------------------------------
*/

#pragma once

#include "../core/Component.h"

class Compressor : public Component
{
    public:
    double pressureRatio;
    double efficiency;

    Compressor(
        double pr,
        double eta)
        : pressureRatio(pr),
        efficiency(eta)

        {}

    void solve(
        const Station& inlet,
        Station& outlet) override
        {
            outlet.pressure = inlet.pressure * pressureRatio;

            outlet.temperature = inlet.temperature * (1.0 + (pressureRatio - 1.0) / efficiency); // Placeholder

            outlet.massFlow = inlet.massFlow;
        }
};
/*
--------------------------------------------------
COMBUSTOR

Input:
    - Inlet pressure
    - Inlet temperature
    - Air mass flow rate
    - Fuel flow rate
    - Combustion efficiency
    - Desired turbine inlet temperature

Process:
    1. Receive compressed air from the compressor.
    2. Inject fuel into the airflow.
    3. Burn the fuel and release heat energy.
    4. Increase the gas temperature based on the
       energy added by combustion.
    5. Apply combustion efficiency losses.
    6. Account for pressure losses through the
       combustor.
    7. Add fuel mass to the total mass flow rate.

Output:
    - Outlet pressure
    - Outlet temperature
    - Outlet mass flow rate

Purpose:
    Adds thermal energy to the compressed air by
    burning fuel, creating high-temperature gases
    that drive the turbine.
--------------------------------------------------
*/

#pragma once

#include "../core/Component.h"
#include "../core/Constants.h"


class Combustor : Component
{
    public:
    float m_dot;
    float m_dot_fuel;
    float AFR; //Air-fuel ratio
    float fuelHeatingValue;
    float combustionEfficiency;
    float Cp = Constants::Cp;
    float pressureLoss;
    float TIT;
    float throttle = 1.0;
    const float IDLE_TIT = 900;
    const float MAX_TIT = 1600;

    Combustor(
        double fuelHeatingValue,
        double combustionEfficiency,
        double pressureLoss,
        double throttle
    )
        : fuelHeatingValue(fuelHeatingValue),
          combustionEfficiency(combustionEfficiency),
          pressureLoss(pressureLoss),
          throttle(throttle)
    {}

    void solve(const Station& inlet, Station& outlet) override
    {
        TIT = IDLE_TIT + throttle * (MAX_TIT - IDLE_TIT);
        m_dot = inlet.massFlow;
        m_dot_fuel = (m_dot * Cp * (TIT - inlet.temperature))/(fuelHeatingValue * combustionEfficiency);

        outlet.temperature = 
        inlet.temperature + 
        (m_dot_fuel * fuelHeatingValue * combustionEfficiency) / 
        (m_dot * Cp);
        outlet.pressure = inlet.pressure * (1.0 - pressureLoss);
        outlet.massFlow = m_dot + m_dot_fuel;
        AFR = m_dot/m_dot_fuel;
    }
};
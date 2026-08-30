/* --------------------------------------------------
NOZZLE

Input:
    - Inlet pressure
    - Inlet temperature
    - Mass flow rate
    - Ambient pressure
    - Nozzle efficiency

Process:
    1. Receive hot, high-pressure gas from the turbine.

    2. Compare the nozzle inlet pressure with the
       ambient pressure.

    3. Calculate the ideal exit temperature using
       the isentropic expansion equation.

    4. Account for nozzle efficiency to calculate
       the actual exit temperature.

    5. Calculate the exit velocity from the
       temperature drop across the nozzle.

    6. Calculate the nozzle pressure at the exit.

    7. Pass the mass flow rate through unchanged.

Output:
    - Exit pressure
    - Exit temperature
    - Exit velocity
    - Mass flow rate

Purpose:
    Expands the high-pressure gas from the turbine
    and converts thermal/pressure energy into
    exhaust velocity to produce thrust.
--------------------------------------------------
*/

#pragma once

#include <cmath>
#include "../core/Component.h"
#include "../core/Constants.h"

class Nozzle : public Component
{
public:

    double ambientPressure;
    double efficiency;

    Nozzle(
        double ambientP,
        double eta)
        : ambientPressure(ambientP),
          efficiency(eta)
    {}

    void solve(
        const Station& inlet,
        Station& outlet) override
    {
        // ------------------------------------------
        // 1. Pass mass flow through unchanged
        // ------------------------------------------

        outlet.massFlow = inlet.massFlow;


        // ------------------------------------------
        // 2. Check whether the nozzle can expand
        // ------------------------------------------

        if (inlet.pressure <= ambientPressure)
        {
            outlet.pressure = inlet.pressure;
            outlet.temperature = inlet.temperature;
            outlet.velocity = 0.0;

            return;
        }


        // ------------------------------------------
        // 3. Calculate ideal exit temperature
        // ------------------------------------------

        double pressureRatio =
            ambientPressure / inlet.pressure;

        double idealExitTemperature =
            inlet.temperature *
            std::pow(
                pressureRatio,
                (Constants::gamma - 1.0) / Constants::gamma
            );


        // ------------------------------------------
        // 4. Account for nozzle efficiency
        //
        // eta_n = (T_in - T_actual) /
        //         (T_in - T_ideal)
        // ------------------------------------------

        double actualExitTemperature =
            inlet.temperature -
            efficiency *
            (inlet.temperature - idealExitTemperature);


        outlet.temperature = actualExitTemperature;


        // ------------------------------------------
        // 5. Calculate exit velocity
        // ------------------------------------------

        outlet.velocity =
            std::sqrt(
                2.0 *
                Constants::Cp *
                (inlet.temperature -
                 actualExitTemperature)
            );


        // ------------------------------------------
        // 6. Set exit pressure
        //
        // For a simple perfectly expanded nozzle,
        // assume exit pressure equals ambient.
        // ------------------------------------------

        outlet.pressure = ambientPressure;
    }
};
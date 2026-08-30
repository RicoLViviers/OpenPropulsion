#pragma once

#include <cmath>
#include "../core/Component.h"
#include "../core/Constants.h"

class Turbine : public Component
{
public:

    float turbine_efficiency;
    float compressor_power;

    Turbine(float eta)
        : turbine_efficiency(eta),
          compressor_power(0.0f)
    {}

    void solve(
        const Station& inlet,
        Station& outlet) override
    {

        // --------------------------------------------------
        // 1. Calculate ideal turbine temperature drop
        // --------------------------------------------------

        float ideal_temp_drop =
            compressor_power /
            (inlet.massFlow * Constants::Cp);


        // --------------------------------------------------
        // 2. Calculate ideal turbine outlet temperature
        // --------------------------------------------------

        float ideal_outlet_temperature =
            inlet.temperature -
            ideal_temp_drop;


        // --------------------------------------------------
        // 3. Account for turbine efficiency
        // --------------------------------------------------

        float actual_temp_drop =
            compressor_power /
            (inlet.massFlow * Constants::Cp);


        // --------------------------------------------------
        // 4. Calculate actual turbine outlet temperature
        // --------------------------------------------------

        outlet.temperature =
            inlet.temperature -
            actual_temp_drop;


        // --------------------------------------------------
        // 5. Calculate turbine pressure ratio
        // --------------------------------------------------

        float temperature_ratio =
            ideal_outlet_temperature /
            inlet.temperature;

        float pressure_ratio =
            pow(
                temperature_ratio,
                Constants::gamma /
                (Constants::gamma - 1.0f)
            );


        // --------------------------------------------------
        // 6. Calculate turbine outlet pressure
        // --------------------------------------------------

        outlet.pressure =
            inlet.pressure *
            pressure_ratio;


        // --------------------------------------------------
        // 7. Mass flow is conserved
        // --------------------------------------------------

        outlet.massFlow =
            inlet.massFlow;


        // --------------------------------------------------
        // 8. Calculate turbine power
        // --------------------------------------------------

        float turbine_power =
            inlet.massFlow *
            Constants::Cp *
            (inlet.temperature -
             outlet.temperature);
    }
};
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

        float ideal_temp_drop =
            compressor_power /
            (inlet.massFlow * Constants::Cp);

        float ideal_outlet_temperature =
            inlet.temperature -
            ideal_temp_drop;

        float actual_temp_drop =
            compressor_power /
            (inlet.massFlow * Constants::Cp);

        outlet.temperature =
            inlet.temperature -
            actual_temp_drop;

        float temperature_ratio =
            ideal_outlet_temperature /
            inlet.temperature;

        float pressure_ratio =
            pow(
                temperature_ratio,
                Constants::gamma /
                (Constants::gamma - 1.0f)
            );

        outlet.pressure =
            inlet.pressure *
            pressure_ratio;

        outlet.massFlow =
            inlet.massFlow;

        float turbine_power =
            inlet.massFlow *
            Constants::Cp *
            (inlet.temperature -
             outlet.temperature);
    }
};
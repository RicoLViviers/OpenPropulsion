#include "Performance.h"
#include <cmath>


Performance::Performance()
{
}

Performance::~Performance()
{
}

float Performance::CalculateThrust(float massFlow, float exitVelocity, float exitPressure, float ambientPressure, float exitArea)
{
    return (massFlow * exitVelocity) + ((exitPressure - ambientPressure) * exitArea);
}

float Performance::CalculateNetThrust(float massFlow, float exitVelocity, float flightVelocity, float exitPressure, float ambientPressure, float exitArea)
{
    return (massFlow * (exitVelocity - flightVelocity)) + ((exitPressure - ambientPressure) * exitArea);
}

float Performance::CalculateTSFC(float fuelFlow, float thrust)
{
    return fuelFlow / thrust;
}

float Performance::CalculateFuelFlow(float tsfc, float thrust)
{
    return tsfc * thrust;
}

float Performance::CalculateSpecificImpulse(float thrust, float fuelFlow)
{
    return thrust / (fuelFlow * 9.80665f);
}

float Performance::CalculateExitVelocity(float totalTemperature, float exitTemperature, float specificHeat)
{
    return sqrt(2.0f * specificHeat * (totalTemperature - exitTemperature));
}

float Performance::CalculateExitTemperature(float totalTemperature, float exitMach, float specificHeatRatio)
{
    return totalTemperature / (1.0f + ((specificHeatRatio - 1.0f) / 2.0f) * exitMach * exitMach);
}

float Performance::CalculateExitMach(float exitVelocity, float exitTemperature, float specificHeatRatio, float gasConstant)
{
    float speedOfSound = sqrt(specificHeatRatio * gasConstant * exitTemperature);
    return exitVelocity / speedOfSound;
}

float Performance::CalculateExitPressure(float totalPressure, float exitMach, float specificHeatRatio)
{
    return totalPressure * pow(1.0f + ((specificHeatRatio - 1.0f) / 2.0f) * exitMach * exitMach, -specificHeatRatio / (specificHeatRatio - 1.0f));
}

float Performance::CalculateMassFlow(float density, float velocity, float area)
{
    return density * velocity * area;
}

float Performance::CalculateDensity(float pressure, float temperature, float gasConstant)
{
    return pressure / (gasConstant * temperature);
}

float Performance::CalculateSpeedOfSound(float temperature, float specificHeatRatio, float gasConstant)
{
    return sqrt(specificHeatRatio * gasConstant * temperature);
}
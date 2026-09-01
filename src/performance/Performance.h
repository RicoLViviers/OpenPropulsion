#pragma once

class Performance
{
    public:
        Performance();
        ~Performance();
        static float CalculateThrust(float massFlow, float exitVelocity, float exitPressure, float ambientPressure, float exitArea);
        static float CalculateNetThrust(float massFlow, float exitVelocity, float flightVelocity, float exitPressure, float ambientPressure, float exitArea);
        static float CalculateTSFC(float fuelFlow, float thrust);
        static float CalculateFuelFlow(float tsfc, float thrust);
        static float CalculateSpecificImpulse(float thrust, float fuelFlow);
        static float CalculateExitVelocity(float totalTemperature, float exitTemperature, float specificHeat);
        static float CalculateExitPressure(float totalPressure, float exitMach, float specificHeatRatio);
        static float CalculateExitTemperature(float totalTemperature, float exitMach, float specificHeatRatio);
        static float CalculateExitMach(float exitVelocity, float exitTemperature, float specificHeatRatio, float gasConstant);
        static float CalculateMassFlow(float density, float velocity, float area);
        static float CalculateDensity(float pressure, float temperature, float gasConstant);
        static float CalculateSpeedOfSound(float temperature, float specificHeatRatio, float gasConstant);
    
};
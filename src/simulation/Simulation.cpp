#include "Simulation.h"
#include "iostream"
#include "../core/Constants.h"
#include "../performance/Performance.h"

Simulation::Simulation(int altitude, float mach, int throttle)
    : altitude(altitude),
      mach(mach),
      throttle(throttle),
      atmosphere(altitude),
      compressor(10.0, 0.9),
      combustor(43e6, 0.98, 0.05, throttle/100.0),
      turbine(0.89),
      nozzle(101325.0, 0.95)
{
}

void Simulation::Run()
{
    Performance performance;

    atmosphere = Atmosphere(altitude);
    std::cout << "Running simulation at altitude: "
              << altitude << " m" << std::endl;

    s0.temperature = atmosphere.T;
    s0.pressure = atmosphere.P;
    s0.massFlow = 50.0;
    nozzle.ambientPressure = atmosphere.P;

    inlet.solve(s0, s1);

    compressor.solve(s1, s2);

    float compressorPower =
        s2.massFlow *
        Constants::Cp *
        (s2.temperature - s1.temperature);

    combustor.throttle = throttle / 100.0f;
    std::cout << "Combustor throttle: " << combustor.throttle << "\n";    
    combustor.solve(s2, s3);

    turbine.compressor_power = compressorPower;
    turbine.solve(s3, s4);

    nozzle.solve(s4, s5);

    exitVelocity = performance.CalculateExitVelocity(
        s4.temperature,
        s5.temperature,
        Constants::Cp
    );

    thrust = performance.CalculateThrust(
        s5.massFlow,
        exitVelocity,
        s5.pressure,
        atmosphere.P,
        1.0 // Assuming exit area of 1 m^2 for simplicity
    );

    netThrust = performance.CalculateNetThrust(
        s5.massFlow,
        exitVelocity,
        mach * performance.CalculateSpeedOfSound(atmosphere.T, Constants::gamma, Constants::R),
        s5.pressure,
        atmosphere.P,
        1.0 // Assuming exit area of 1 m^2 for simplicity
    );

    fuelFlow = combustor.m_dot_fuel;

    tsfc = performance.CalculateTSFC(
        fuelFlow,
        thrust
    );

    specificImpulse = performance.CalculateSpecificImpulse(
        thrust,
        fuelFlow
    );


    exitPressure = s5.pressure;

    exitTemperature = s5.temperature;

    exitMach = performance.CalculateExitMach(
        exitVelocity,
        exitTemperature,
        Constants::gamma,
        Constants::R
    );

    massFlow = s5.massFlow;

    density = performance.CalculateDensity(
        exitPressure * 1000.0, // Convert kPa to Pa
        exitTemperature,
        Constants::R
    );

    speedOfSound = performance.CalculateSpeedOfSound(
        exitTemperature,
        Constants::gamma,
        Constants::R
    );




}


#include "Simulation.h"

#include "../core/Constants.h"

Simulation::Simulation()
    : atmosphere(1100),
      compressor(10.0, 0.9),
      combustor(43e6, 0.98, 0.05, 1.0),
      turbine(0.89),
      nozzle(101325.0, 0.95)
{
}

void Simulation::Run()
{
    // ========================================================
    // Station 0 - Ambient
    // ========================================================

    s0.temperature = atmosphere.T;
    s0.pressure = atmosphere.P;
    s0.massFlow = 50.0;

    // ========================================================
    // Station 1 - Inlet
    // ========================================================

    inlet.solve(s0, s1);

    // ========================================================
    // Station 2 - Compressor
    // ========================================================

    compressor.solve(s1, s2);

    // ========================================================
    // Compressor power
    // ========================================================

    float compressorPower =
        s2.massFlow *
        Constants::Cp *
        (s2.temperature - s1.temperature);

    // ========================================================
    // Station 3 - Combustor
    // ========================================================

    combustor.solve(s2, s3);

    // ========================================================
    // Station 4 - Turbine
    // ========================================================

    turbine.compressor_power = compressorPower;
    turbine.solve(s3, s4);

    // ========================================================
    // Station 5 - Nozzle
    // ========================================================

    nozzle.solve(s4, s5);
}
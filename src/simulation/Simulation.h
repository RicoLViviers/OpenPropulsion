#pragma once

#include "../core/Station.h"
#include "../core/Atmosphere.h"

#include "../components/Inlet.h"
#include "../components/Compressor.h"
#include "../components/Combustor.h"
#include "../components/Turbine.h"
#include "../components/Nozzle.h"

class Simulation
{
public:
    Simulation();

    void Run();

    // Results
    Station& GetS0() { return s0; }
    Station& GetS1() { return s1; }
    Station& GetS2() { return s2; }
    Station& GetS3() { return s3; }
    Station& GetS4() { return s4; }
    Station& GetS5() { return s5; }

private:
    Station s0;
    Station s1;
    Station s2;
    Station s3;
    Station s4;
    Station s5;

    Atmosphere atmosphere;

    Inlet inlet;
    Compressor compressor;
    Combustor combustor;
    Turbine turbine;
    Nozzle nozzle;
};
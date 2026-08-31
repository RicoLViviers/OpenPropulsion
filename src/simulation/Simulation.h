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
    const Station& GetS0() const { return s0; }
    const Station& GetS1() const { return s1; }
    const Station& GetS2() const { return s2; }
    const Station& GetS3() const { return s3; }
    const Station& GetS4() const { return s4; }
    const Station& GetS5() const { return s5; }

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
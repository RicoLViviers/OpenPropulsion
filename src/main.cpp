#include <iostream>
#include "./core/Station.h"
#include "./components/Inlet.h"
#include "./components/Compressor.h"
#include "./components/Combustor.h"
#include "./components/Turbine.h"
#include "./core/Atmosphere.h"
using namespace std;

int main()
{
    Station s0;
    Station s1;
    Station s2;
    Station s3;
    Station s4;
    Station s5;
    Station s6;
    Station s7;
    Station s8;
    Station s9;

    Atmosphere atmosphere(1100);

    s0.temperature = atmosphere.T;
    s0.pressure = atmosphere.P;

    cout << "S0 temperature: " << s0.temperature << endl;
    cout << "S0 pressure: " << s0.pressure << endl;
    

    Inlet inlet;
    inlet.solve(s0, s1);
    cout << "Inlet temp out: " << s1.temperature << endl;
    cout << "Inlet pres out: " << s1.pressure << endl;
    Compressor comp(10.0, 0.9);
    comp.solve(s1, s2);
    cout << "Comp temp out: " << s2.temperature << endl;
    cout << "Comp pres out: " << s2.pressure << endl;

    return 0;
}

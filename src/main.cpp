/* #include <iostream>
#include "./core/Station.h"
#include "./components/Inlet.h"
#include "./components/Compressor.h"
#include "./components/Combustor.h"
#include "./components/Turbine.h"
#include "./components/Nozzle.h"
#include "./core/Atmosphere.h"

using namespace std;

int main()
{
    Station s0;  //Ambient air 
    Station s1;  //Inlet
    Station s2;  //Compressor
    Station s3;  //Combustor
    Station s4;  //Turbine
    Station s5;  //Nozzle

    Atmosphere atmosphere(1100);

    s0.temperature = atmosphere.T;
    s0.pressure = atmosphere.P;
    s0.massFlow = 50.0;

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
    Combustor comb(43e6, 0.98, 0.05, 1.0);
    comb.solve(s2, s3);
    cout << "Comb temp out: " << s3.temperature << endl;
    cout << "Comb pres out: " << s3.pressure << endl;

    float compressor_power = s2.massFlow * Constants::Cp * (s2.temperature - s1.temperature);

    Turbine turb(0.89);
    turb.compressor_power = compressor_power;
    turb.solve(s3, s4);
    cout << "Turb temp out: " << s4.temperature << endl;
    cout << "Turb pres out: " << s4.pressure << endl;

    Nozzle nozzle(s0.pressure, 0.95);
    nozzle.solve(s4, s5);
    cout << "Nozzle temp out: " << s5.temperature << endl;
    cout << "Nozzle pres out: " << s5.pressure << endl;
    cout << "Velocity out: " << s5.velocity << endl;

    string m = "asd";
    cin >> m;


    return 0;
};
 */


#include "app/Application.h"

int main()
{
    Application app;
    return app.Run();
}
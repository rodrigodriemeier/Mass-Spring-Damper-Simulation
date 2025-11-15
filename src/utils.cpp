#include "utils.h"
#include "constants.h" // For pi and e
#include "MassSpringDamper.h" // Need the full class def here
#include <iostream>
#include <fstream>      // For ofstream
#include <iomanip>      // For setprecision
#include <limits>       // For numeric_limits
#include <cstdlib>      // For system("cls") / system("clear")
#include <cmath>

using namespace std;

void export_parameters(const MassSpringDamper& s) {
    ofstream file("system_parameters.csv");
    if (!file.is_open()) {
        cout << "Error: could not create 'system_parameters.csv'" << endl;
        return;
    }

    double wn = s.get_wn();
    double zeta = s.get_zeta();
    double ccrit = s.get_c_crit();
    double T = s.get_T();
    double Ts = s.get_Ts();

    file << "Parameter,Value,Unit,Observation\n";
    file << "Mass (m)," << s.get_m() << ",kg,\n";
    file << "Damping coefficient (c)," << s.get_c() << ",N·s/m,\n";
    file << "Spring constant (k)," << s.get_k() << ",N/m,\n";
    file << "Initial position (x0)," << s.get_xo() << ",m,\n";
    file << "Initial velocity (v0)," << s.get_vo() << ",m/s,\n";
    file << "Natural frequency (wn)," << wn << ",rad/s,\n";
    file << "Natural period (T)," << T << ",s,\n";
    file << "Critical damping (c_crit)," << ccrit << ",N·s/m,\n";
    file << "Damping ratio (zeta)," << zeta << ",-,";
    
    if (zeta < 1) file << "Underdamped system\n";
    else if (zeta == 1) file << "Critically damped system\n";
    else file << "Overdamped system\n";
    
    file << "Settling time (2%)," << Ts << ",s,\n";

    // Damped/Overshoot parameters only exist for underdamped systems.
    if (zeta < 1) {
        double wd = wn * sqrt(1 - pow(zeta, 2));
        double Td = 2 * pi / wd;
        double Mp = 100 * pow(e, (-zeta * pi) / sqrt(1 - pow(zeta, 2)));
        double delta = (2 * pi * zeta) / sqrt(1 - pow(zeta, 2));
        file << "Damped frequency (wd)," << wd << ",rad/s,\n";
        file << "Damped period (Td)," << Td << ",s,\n";
        file << "Overshoot (Mp)," << Mp << ",%,\n";
        file << "Logarithmic decrement (delta)," << delta << ",-,\n";
    } else {
        file << "Damped frequency (wd),N/A,,Not applicable\n";
        file << "Damped period (Td),N/A,,Not applicable\n";
        file << "Overshoot (Mp),0,%," << "No oscillation\n";
        file << "Logarithmic decrement (delta),N/A,,Not applicable\n";
    }

    file.close();
    cout << "'system_parameters.csv' successfully exported!" << endl;
}


void export_results(const vector<double>& t, const vector<double>& x, const vector<double>& v, const vector<double>& a){
    ofstream file("results.csv");
    if (!file.is_open()) {
        cout << "Error: could not create 'results.csv'" << endl;
        return;
    }

    file << "time(s),position(m),velocity(m/s),acceleration(m/s^2)\n";

    for (size_t i = 0; i < t.size(); i++) {
        file << t[i] << "," << x[i] << "," << v[i] << "," << a[i] << "\n";
    }

    file.close();
    cout << "'results.csv' file successfully exported!" << endl;
}

void pauseAndClear() {
    cout << "Press ENTER to continue" << endl;
    
    // Clear the input buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    
    // Cross-platform screen clear
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <limits>
#include <iomanip>

// Project headers
#include "constants.h"
#include "MassSpringDamper.h"
#include "simulation.h"
#include "utils.h"

using namespace std;

// Prototypes for functions local to main.cpp
MassSpringDamper manual_sys_creation();
void menu();

// Main entry point
int main(){
    menu();
    return 0;
}

// Handles the user input loop for creating a new system.
MassSpringDamper manual_sys_creation(){
    MassSpringDamper ms;
    double m_, c_, k_, xo_, vo_;
    int cont = 0;
    int e[5] = {0,0,0,0,0}; // Error flags

    // Loop until all 5 inputs are valid
    while(true){
        // Only re-ask for inputs that are currently invalid (flag == 0)
        if(e[0]==0){
            if(cont>0){ cout << "(INVALID INSERTION) Be aware: 1e-6 <= m <= 1e+3" << endl; }
            cout << "Insert the mass value (kg): " << endl;
            cin >> m_;
        }
        if(e[1]==0){
            if(cont>0){ cout << "(INVALID INSERTION) Be aware: 0 <= c <= 1e+5" << endl; }
            cout << "Insert the damping coeficient value (N.s/m): " << endl;
            cin >> c_;
        }
        if(e[2]==0){
            if(cont>0){ cout << "(INVALID INSERTION) Be aware: 0 <= k <= 1e+7" << endl; }
            cout << "Insert the spring constant value (N/m): " << endl;
            cin >> k_;
        }
        if(e[3]==0){
            if(cont>0){ cout << "(INVALID INSERTION) Be aware: |x0| <= 5" << endl; }
            cout << "Insert the initial X position (m): " << endl;
            cin >> xo_;
        }
        if(e[4]==0){
            if(cont>0){ cout << "(INVALID INSERTION) Be aware: |v0| <= 20" << endl; }
            cout << "Insert the initial V velocity (m/s): " << endl;
            cin >> vo_;
        }
        
        // Basic cin validation to prevent infinite loop on non-numeric input
        if(cin.fail()) {
            cout << "--- Invalid input. Please enter numbers only. ---" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cont = 0; 
            for(int &err : e) { err = 0; } // Reset all flags
            pauseAndClear();
            continue; // Restart the loop
        }

        ms.validate_parameters(e, m_, c_, k_, xo_, vo_);

        if(e[0]==1 && e[1] ==1 && e[2]==1 && e[3] ==1 && e[4] ==1){
            cout << "All the parameters inserted were valid, system created!" << endl;
            ms.set_parameters(m_, c_, k_, xo_, vo_ );
            break; // Exit while(true)
        }
        else{
            cont = 1; // Flag that we've failed validation at least once
        }
    }
    return ms;
}

// The main application loop. Handles all user navigation.
void menu(){
    int creation = 0; // Flag to check if a system exists
    int opt_menu = 0, opt_sim = 0, opt_par = 0;
    MassSpringDamper s; // The main system object

    while(opt_menu != 4){ // Loop until user selects "4 - Finish"
        opt_menu = 0;
        opt_sim = 0;
        opt_par = 0;
        cout << endl << " # Numerical Analysis of a Mass Spring Damper System #" << endl;
        cout << "______________________________________________________" << endl;
        cout << "                       MENU" << endl;
        cout << "1 - Create your system" << endl
             << "2 - Parameters from your system" << endl
             << "3 - Simulate" << endl
             << "4 - Finish" << endl 
             << "______________________________________________________" << endl;
        
        if (!(cin >> opt_menu)) {
            cout << "Invalid selection. Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pauseAndClear();
            continue; 
        }
        
        system("cls");

        switch(opt_menu){
            case 1: // --- Create System ---
                cout << "______________________________________________________" << endl;
                cout << "                   Create your system" << endl << endl;
                s = manual_sys_creation();
                pauseAndClear();
                creation++;
                break;

            case 2: // --- Show Parameters ---
                if(creation == 0){
                    cout << "You must create your system first" << endl;
                    pauseAndClear();
                    break;
                }
                while(opt_par != 17){ // Parameter sub-menu
                    cout << "______________________________________________________" << endl;
                    cout << "                   Show Parameters" << endl;
                    cout << "1 -  All parameters" << endl;
                    cout << "2 -  Mass m" << endl;
                    cout << "3 -  Damp constant c" << endl;
                    cout << "4 -  Spring constant k" << endl;
                    cout << "5 -  Initial position xo" << endl;
                    cout << "6 -  Initial velocity vo" << endl;
                    cout << "7 -  Natural frequency Wn" << endl;
                    cout << "8 -  Natural period T" << endl;
                    cout << "9 -  Critical damping c_crit" << endl;
                    cout << "10 - Settling time Ts - 2%" << endl;
                    cout << "11 - Damping ratio zeta" << endl;
                    cout << "12 - Damped frequency Wd (zeta < 1)" << endl;
                    cout << "13 - Damped period Td (zeta < 1)" << endl;
                    cout << "14 - Overshoot Mp % (zeta < 1)" << endl;
                    cout << "15 - Logarithmic decay delta (zeta < 1)" << endl;
                    cout << "16 - Export all parameters" << endl;
                    cout << "17 - Back" << endl;
                    
                    if (!(cin >> opt_par)) {
                        cout << "Invalid selection. Please enter a number." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        pauseAndClear();
                        continue;
                    }
                    system("cls");
                    
                    // This is long, but a 'switch' is more complex with the pause
                    if(opt_par == 1){
                        cout << "All Parameters" << endl;
                        cout << "Mass: " << fixed << setprecision(2) << s.get_m() << " kg" << endl;
                        cout << "Damp Constant: " << fixed << setprecision(2) << s.get_c() << " N.s/m" << endl;
                        cout << "Spring Constant: " << fixed << setprecision(2) << s.get_k() << " N/m" << endl;
                        cout << "Initial Position: " << fixed << setprecision(2) << s.get_xo() << " m" << endl;
                        cout << "Initial Velocity: " << fixed << setprecision(2) << s.get_vo() << " m/s" << endl;
                        cout << "Natural Frequency: " << fixed << setprecision(2) << s.get_wn() << " s^-1" << endl;
                        cout << "Natrural Period: " << fixed << setprecision(2) << s.get_T() << " s" << endl;
                        cout << "Critical Damping: " << fixed << setprecision(2) << s.get_c_crit() << " kg/s" << endl;
                        cout << "Settling Time: " << fixed << setprecision(2) << s.get_Ts() << " s" << endl;
                        cout << "Damping Ratio: " << fixed << setprecision(2) << s.get_zeta();
                        if(s.get_zeta() == 1){
                            cout << " (Critically Damped System)" << endl << endl << "No other parameter available for this type of system" << endl;
                        }
                        else if(s.get_zeta() > 1){
                            cout << " (Overdamped System)" << endl << endl << "No other parameter available for this type of system" << endl;
                        }
                        else if(s.get_zeta() < 1){
                            cout << " (Underdamped System)" << endl;
                            cout << "Damped Frequency: " << fixed << setprecision(2) << s.get_wn()*sqrt(1-pow(s.get_zeta(), 2)) << " s^-1" << endl;
                            cout << "Damped Period: " << fixed << setprecision(2) << 2*pi/(s.get_wn()*sqrt(1-pow(s.get_zeta(), 2))) << " s" << endl;
                            cout << "Overshoot (%): " << fixed << setprecision(2) << 100*pow(e, (-s.get_zeta()*pi)/(sqrt(1-s.get_zeta()*s.get_zeta()))) << " %" << endl;
                            cout << "Logarithmic Decay: " << fixed << setprecision(2) << 2*pi*s.get_zeta()/(sqrt(1-s.get_zeta()*s.get_zeta())) << endl;
                        }
                        pauseAndClear();
                    }
                    else if(opt_par == 2){ cout << "Mass: " << fixed << setprecision(2) << s.get_m() << " kg" << endl; pauseAndClear(); }
                    else if(opt_par == 3){ cout << "Damp Constant: " << fixed << setprecision(2) << s.get_c() << " N.s/m" << endl; pauseAndClear(); }
                    else if(opt_par == 4){ cout << "Spring Constant: " << fixed << setprecision(2) << s.get_k() << " N/m" << endl; pauseAndClear(); }
                    else if(opt_par == 5){ cout << "Initial Position: " << fixed << setprecision(2) << s.get_xo() << " m" << endl; pauseAndClear(); }
                    else if(opt_par == 6){ cout << "Initial Velocity: " << fixed << setprecision(2) << s.get_vo() << " m/s" << endl; pauseAndClear(); }
                    else if(opt_par == 7){ cout << "Natural Frequency: " << fixed << setprecision(2) << s.get_wn() << " s^-1" << endl; pauseAndClear(); }
                    else if(opt_par == 8){ cout << "Natrural Period: " << fixed << setprecision(2) << s.get_T() << " s" << endl; pauseAndClear(); }
                    else if(opt_par == 9){ cout << "Critical Damping: " << fixed << setprecision(2) << s.get_c_crit() << " kg/s" << endl; pauseAndClear(); }
                    else if(opt_par == 10){ cout << "Settling Time: " << fixed << setprecision(2) << s.get_Ts() << " s" << endl; pauseAndClear(); }
                    else if(opt_par == 11){ 
                        cout << "Damping Ratio: " << fixed << setprecision(2) << s.get_zeta();
                        if(s.get_zeta() == 1) cout << " (Critically Damped System)" << endl;
                        else if(s.get_zeta() > 1) cout << " (Overdamped System)" << endl;
                        else if(s.get_zeta() < 1) cout << " (Underdamped System)" << endl;
                        pauseAndClear(); 
                    }
                    else if(opt_par == 12){
                        if(s.get_zeta() >= 1) cout << "Parameter not available for this type of system" << endl;
                        else cout << "Damped Frequency: " << fixed << setprecision(2) << s.get_wn()*sqrt(1-pow(s.get_zeta(), 2)) << " s^-1" << endl;
                        pauseAndClear();
                    }
                    else if(opt_par == 13){
                        if(s.get_zeta() >= 1) cout << "Parameter not available for this type of system" << endl;
                        else cout << "Damped Period: " << fixed << setprecision(2) << 2*pi/(s.get_wn()*sqrt(1-pow(s.get_zeta(), 2))) << " s" << endl;
                        pauseAndClear();
                    }
                    else if(opt_par == 14){
                        if(s.get_zeta() >= 1) cout << "Parameter not available for this type of system" << endl;
                        else cout << "Overshoot (%): " << fixed << setprecision(2) << 100*pow(e, (-s.get_zeta()*pi)/(sqrt(1-s.get_zeta()*s.get_zeta()))) << " %" << endl;
                        pauseAndClear();
                    }
                    else if(opt_par == 15){
                        if(s.get_zeta() >= 1) cout << "Parameter not available for this type of system" << endl;
                        else cout << "Logarithmic Decay: " << fixed << setprecision(2) << 2*pi*s.get_zeta()/(sqrt(1-s.get_zeta()*s.get_zeta())) << endl;
                        pauseAndClear();
                    }
                    else if(opt_par == 16){ export_parameters(s); pauseAndClear(); }
                    else if(opt_par == 17){ system("cls"); break; } // Exit sub-menu
                    else { cout << "Invalid option." << endl; pauseAndClear(); }
                }
                break;

            case 3: // --- Simulate ---
                if(creation == 0){
                    cout << "You must create your system first" << endl;
                    pauseAndClear();
                    break;
                }
                while(opt_sim != 3){ // Simulation sub-menu
                    cout << "______________________________________________________" << endl;
                    cout << "                       Simulate" << endl;
                    cout << "(your simulation will be exported as a .csv file)" << endl << endl;
                    cout << "1 - Euler's Method" << endl
                         << "2 - Range-Kutta's Method" << endl
                         << "3 - Back" << endl 
                         << "______________________________________________________" << endl;
                    
                    if (!(cin >> opt_sim)) {
                        cout << "Invalid selection. Please enter a number." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        pauseAndClear();
                        continue;
                    }

                    if(opt_sim == 1){
                        euler(s);
                        pauseAndClear();
                        opt_sim = 3; // Go back after running
                    }
                    else if(opt_sim == 2){
                        rk4(s);
                        pauseAndClear();
                        opt_sim = 3; // Go back after running
                    }
                    else if(opt_sim == 3){
                        system("cls");
                        break; // Exit sub-menu
                    }
                    else { cout << "Invalid option." << endl; pauseAndClear(); }
                }
                break;

            case 4: // --- Finish ---
                cout << "Finishing program." << endl;
                break;
            
            default:
                cout << "Invalid option, please try again." << endl;
                pauseAndClear();
                break;
        }
    }
}
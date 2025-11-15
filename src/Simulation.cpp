#include "simulation.h"
#include "utils.h"      // For export_results()
#include <vector>
#include <cmath>
#include <algorithm>    // std::min

using namespace std; 

void euler(const MassSpringDamper& s){
    vector<double> a, v, x, t;
    double dt;

    // Robust dt logic: scale dt to system frequency, but cap at 0.01s.
    dt = min(0.1 / s.get_wn(), 0.01);

    // Set initial conditions [t=0]
    v.push_back(s.get_vo());
    x.push_back(s.get_xo());
    t.push_back(0);
    a.push_back(-(s.get_c()/s.get_m())*v[0] - (s.get_k()/s.get_m())*x[0]);

    int first_peak = 0, second_peak = 0, ref_peak = 0, count = 0;

    // Main integration loop (max 100 natural periods)
    for(int i = 1; i < int((100 * s.get_T())/dt); i++){

        // --- Semi-Implicit Euler (a -> v -> x) ---
        // More stable for oscillators than explicit Euler.
        a.push_back(-(s.get_c()/s.get_m())*v[i-1] - (s.get_k()/s.get_m())*x[i-1]); 
        v.push_back(v[i-1] + a[i]*dt); // v[i] uses new a[i]
        x.push_back(x[i-1] + v[i]*dt); // x[i] uses new v[i]
        t.push_back(i*dt);

        // --- Optimized Stop Logic ---
        if(s.get_zeta() <= 1){ // Oscillating systems
            // Find peaks and break if amplitude is < 2% of first peak.
            if(i > 2 && abs(x[i-2]) < abs(x[i-1]) && abs(x[i-1]) > abs(x[i])){
                if(count == 0) { first_peak = i-1; ref_peak = i-1; }
                if(count == 1) { second_peak = i-1; }
                if(count > 1)  { first_peak = second_peak; second_peak = i - 1; }
                if(count > 0 && abs(x[first_peak]) < 0.02*abs(x[ref_peak]) && abs(x[second_peak]) < 0.02*abs(x[ref_peak])){
                    break; 
                }
                count++;
            }
        }
        else { // Overdamped systems
            // No peaks. Just stop after 2 periods.
            if(i == int(2*s.get_T()/dt)){
                break;
            }
        }
    }
    export_results(t, x, v, a);
}

void rk4(const MassSpringDamper& s){
    vector<double> a, v, x, t;
    double dt, avgx, avgv,newx, newv, newa;
    double kx1, kx2, kx3, kx4, xmid, xmidbett, xfin;
    double kv1, kv2, kv3, kv4, vmid, vmidbett, vfin;

    dt = min(0.1 / s.get_wn(), 0.01); 

    // Set initial conditions [t=0]
    v.push_back(s.get_vo());
    x.push_back(s.get_xo());
    t.push_back(0);
    a.push_back(-(s.get_c()/s.get_m())*v[0] - (s.get_k()/s.get_m())*x[0]);

    int first_peak = 0, second_peak = 0, ref_peak = 0, count = 0;

    for(int i = 1; i < int((100 * s.get_T())/dt); i++){
        // --- RK4 2nd-Order ODE Implementation ---
        // Solves dx/dt = v AND dv/dt = a

        // k1: Slopes at start
        kx1 = v[i-1];
        kv1 = -(s.get_c()/s.get_m())*v[i-1] - (s.get_k()/s.get_m())*x[i-1];

        // k2: Slopes at midpoint (using k1)
        xmid = x[i-1] + kx1*dt/2.0;
        vmid = v[i-1] + kv1*dt/2.0;
        kx2 = vmid;
        kv2 = -(s.get_c()/s.get_m())*vmid - (s.get_k()/s.get_m())*xmid;

        // k3: Slopes at midpoint (using k2)
        xmidbett = x[i-1] + kx2*dt/2.0;
        vmidbett = v[i-1] + kv2*dt/2.0;
        kx3 = vmidbett;
        kv3 = -(s.get_c()/s.get_m())*vmidbett - (s.get_k()/s.get_m())*xmidbett;

        // k4: Slopes at end (using k3)
        xfin = x[i-1] + kx3*dt;
        vfin = v[i-1] + kv3*dt;
        kx4 = vfin; // kx4 is the velocity 'v' at the end point
        kv4 = -(s.get_c()/s.get_m())*kx4 - (s.get_k()/s.get_m())*xfin; // (using kx4 here is correct since kx4=vfin)

        // Weighted average (Simpson's rule)
        avgx = (kx1 + 2.0*kx2 + 2.0*kx3 + kx4) / 6.0;
        avgv = (kv1 + 2.0*kv2 + 2.0*kv3 + kv4) / 6.0;

        // Calculate final new state
        newx = x[i-1] + avgx*dt;
        newv = v[i-1] + avgv*dt;
        newa = -(s.get_c()/s.get_m())*newv - (s.get_k()/s.get_m())*newx;

        // Store new state
        v.push_back(newv);
        x.push_back(newx);
        a.push_back(newa);
        t.push_back(i*dt);

        // --- Smart Break Logic (same as Euler) ---
        if(s.get_zeta() <= 1){
            if(i > 2 && abs(x[i-2]) < abs(x[i-1]) && abs(x[i-1]) > abs(x[i])){
                if(count == 0) { first_peak = i-1; ref_peak = i-1; }
                if(count == 1) { second_peak = i-1; }
                if(count > 1)  { first_peak = second_peak; second_peak = i - 1; }
                if(count > 0 && abs(x[first_peak]) < 0.02*abs(x[ref_peak]) && abs(x[second_peak]) < 0.02*abs(x[ref_peak])){
                    break;
                }
                count++;
            }
        }
        else {
            if(i == int(2*s.get_T()/dt)){
                break;
            }
        }
    }
    export_results(t, x, v, a);
}
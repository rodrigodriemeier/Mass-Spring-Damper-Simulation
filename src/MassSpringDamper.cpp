#include "MassSpringDamper.h"
#include "constants.h" // For 'pi'
#include <cmath>       // For 'sqrt' and 'abs'

// Note: This function modifies the 'erro' array in-place.
void MassSpringDamper::validate_parameters(int* erro, double m_, double c_, double k_, double xo_, double vo_){
    // 0 = fail, 1 = pass
    (m_ <= 1e-6 || m_ >= 1e3) ? *erro = 0 : *erro = 1;
    (c_ <= 0 || c_ > 1e5) ? *(erro + 1) = 0 : *(erro + 1) = 1;
    (k_ <= 0 || k_ > 1e7) ? *(erro + 2) = 0 : *(erro + 2) = 1;
    (std::abs(xo_) > 5) ? *(erro + 3) = 0 : *(erro + 3) = 1;
    (std::abs(vo_) > 20) ? *(erro + 4) = 0 : *(erro + 4) = 1;
}

// Should only be called *after* validation.
void MassSpringDamper::set_parameters(double m_, double c_, double k_, double xo_, double vo_){
    m = m_;
    c = c_;
    k = k_;
    xo = xo_;
    vo = vo_;
    
    // Calculate all derived physical properties at once
    // to ensure the object is always in a consistent state.
    wn = std::sqrt(k_/m_);
    T = 2*pi/wn;
    c_crit = 2*std::sqrt(k*m);
    zeta = c/c_crit;
    Ts = 4/(zeta*wn); // 2% Settling Time
}
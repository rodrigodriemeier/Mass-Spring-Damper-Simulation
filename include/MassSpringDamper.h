#pragma once
#include <cmath>

/**
 * @class MassSpringDamper
 * @brief Holds all the state and calculated physics properties of a single system.
 * This class *is* the system, it doesn't *run* the simulation.
 */
class MassSpringDamper{
private:
    // m, c, k, xo, vo are the primary inputs.
    // The rest (wn, T, zeta...) are derived properties.
    double m, c, k, xo, vo, wn, T, c_crit, Ts, zeta;

public:
    // Validates user inputs against project-defined "sane" limits.
    // Uses a C-style int array as an error flag (0=fail, 1=pass).
    void validate_parameters(int* erro, double m_, double c_, double k_, double xo_, double vo_);

    // Sets the primary values and calculates all derived properties (wn, zeta, etc.)
    void set_parameters(double m_, double c_, double k_, double xo_, double vo_);

    // --- Getters (all 'const' and inlined) ---
    double get_m() const { return m; }
    double get_c() const { return c; }
    double get_k() const { return k; }
    double get_xo() const { return xo; }
    double get_vo() const { return vo; }
    double get_wn() const { return wn; }
    double get_T() const { return T; }
    double get_c_crit() const { return c_crit; }
    double get_zeta() const { return zeta; }
    double get_Ts() const { return Ts; }
};
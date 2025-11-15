#pragma once
#include "MassSpringDamper.h" 

// --- Numerical Solver Prototypes ---

// Semi-Implicit Euler solver.
void euler(const MassSpringDamper& s);

// 4th Order Runge-Kutta solver.
void rk4(const MassSpringDamper& s);
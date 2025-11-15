#pragma once
#include <vector>

// Forward-declaration to avoid including the full header.
class MassSpringDamper; 

// --- Utility Function Prototypes ---

// Writes time-series data to "results.csv".
void export_results(const std::vector<double>& t, const std::vector<double>& x, const std::vector<double>& v, const std::vector<double>& a);

// Writes system parameters to "system_parameters.csv".
void export_parameters(const MassSpringDamper& s);

// Cross-platform pause and screen clear.
void pauseAndClear();
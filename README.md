MASS SPRING DAMPER SIMULATION 
A C++ program where you can define a mass-spring-damper system, view/export its parameters and simulate it by Euler's or Range-Kutta's method (export a .csv file with x,v,a,t values at each iteration)

FEATURES
  - Dual Numerical Solvers: Choose between the fast 'Semi-Implicit Euler' method or the highly accurate '4th Order Runge-Kutta (RK4)' method.
  - Physics Engine: Automatically calculates all key derived parameters, including:
    - Natural Frequency (wn) & Period (T)
    - Damping Ratio (zeta) & System Type (Under, Over, Critically Damped)
    - Critical Damping (c_crit)
    - 2% Settling Time (Ts)
    - Damped Frequency (wd), Overshoot (Mp%), and more (for underdamped systems).
  - Smart Simulation Logic:
    - Uses a robust, adaptive time-step (`dt`) logic to ensure stability.
    - Features an optimized stop condition: it auto-detects when an oscillating system has settled (amplitude < 2% of first peak) or stops non-oscillating systems after 2 periods, saving computation time.  - Data     - Export: Generates two clean `.csv` files:
    1.  `system_parameters.csv`: A summary of all system parameters.
    2.  `results.csv`: The full time-series data (time, position, velocity, acceleration).
  - Clean Code Structure: The project is organized into `include/` and `src/` directories, separating the class/function declarations from their implementations.

TECH STACK

  - C++: The core simulation engine and console interface.
  - Python (for visualization): The `/plotting` folder contains a simple Python script using `pandas` and `matplotlib` to visualize the `results.csv` output.
  - Git & GitHub: For version control.

PROJECT STRUCTURE

*Main directories*
  src/ 
    → main.cpp
    → MassSpringDamper.cpp
    → Simulation.cpp
    → utils.cpp
  include/
    → main.h
    → MassSpringDamper.h
    → Simulation.h
    → utils.h
  plot/
    → plot_sim.py
  examples/
    → Creating_System.jpg
    → Exporting_Parameters.jpg
    → Parameters_File.jpg
    → Plot_Simulation.jpg
    → Simulating_And_Exporting.jpg
    → Viewing_Parameters.jpg

HOW TO USE THE PROGRAM

  The application is driven by a simple text menu:
    - Create your system: A wizard that guides you through setting the 5 base parameters (m, c, k, x0, v0). It includes input validation to ensure the values are within a sane range.
    - Parameters from your system: Displays all primary and derived physics parameters. It also gives you the option to export this list to system_parameters.csv.
    - Simulate: Asks you to choose your solver (Euler or RK4). It then runs the simulation and automatically exports the time-series data to results.csv.
    - Finish: Exits the program.

VISUALIZING THE RESULTS
  
  After you run a simulation, you can easily plot the output.

  1. Make sure you have pandas and matplotlib installed for Python:
     pip install pandas matplotlib
  
  2. Navigate to the plotting directory
     Run the script:
     python plot_sim.py
     This will read the results.csv from the root folder and display a chart of the system's position over time.


AUTHOR
Rodrigo Driemeier dos Santos
EESC - University of São Paulo (USP), São Carlos, Brazil — Mechatronics Engineering
École Centrale de Lille, France — Generalist Engineering

rodrigodriemeier@usp.br https://www.linkedin.com/in/rodrigo-driemeier-dos-santos-a7698633b/

Thanks for checking out the project :)
 

 
  

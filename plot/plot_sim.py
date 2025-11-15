import pandas as pd
import matplotlib.pyplot as plt

# Read CSV file
data = pd.read_csv("results.csv")

# Extract columns
t = data["time(s)"]
x = data["position(m)"]
v = data["velocity(m/s)"]
a = data["acceleration(m/s^2)"]

# Plot position
plt.figure(figsize=(10, 6))
plt.plot(t, x, label="Position (m)", color='b')
plt.title("Mass-Spring-Damper System - Position vs Time")
plt.xlabel("Time (s)")
plt.ylabel("Position (m)")
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()

# Plot velocity
plt.figure(figsize=(10, 6))
plt.plot(t, v, label="Velocity (m/s)", color='r')
plt.title("Velocity vs Time")
plt.xlabel("Time (s)")
plt.ylabel("Velocity (m/s)")
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()

# Plot acceleration
plt.figure(figsize=(10, 6))
plt.plot(t, a, label="Acceleration (m/s²)", color='g')
plt.title("Acceleration vs Time")
plt.xlabel("Time (s)")
plt.ylabel("Acceleration (m/s²)")
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()

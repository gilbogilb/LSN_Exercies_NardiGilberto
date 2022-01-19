import matplotlib.pyplot as plt
import numpy as np

T = np.loadtxt('raw.dat')
steps = np.arange(T.size)
T0 = 1.1 + np.zeros(T.size)

plt.plot(steps,T)
plt.grid(True)
plt.xlabel('steps')
plt.ylabel('Temperature (*)')
plt.plot(steps,T0)
plt.show()
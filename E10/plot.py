import matplotlib.pyplot as plt
import numpy as np

T0 = 5.
T, cost = np.loadtxt('circle.dat',unpack=True)
plt.plot(T0-T,cost)
plt.xlabel('$T_0-T$')
plt.ylabel('final permutation cost')
plt.grid(True)

x,y = np.loadtxt("bestpath.dat", unpack=True)
x = np.append(x, x[0])
y = np.append(y, y[0])

plt.figure()

plt.plot(x,y)
plt.plot(x,y,'r^',label='cities')
plt.grid(True)
plt.title('Cities distribution & best path',fontweight='bold')

plt.legend()
plt.show()

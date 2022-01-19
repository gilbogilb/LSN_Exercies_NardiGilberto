import matplotlib.pyplot as plt
import numpy as np

def fscema(x,y):
    return np.exp(-x*x-y*y)

matr = np.loadtxt('output/matrix.dat')
steps = matr[0].size
mu = np.linspace(0.5,1.5,steps)
sigma = np.linspace(0.2,1.2,steps)
M,S = np.meshgrid(mu,sigma)

print('M=',M)
print('S=',S)
print('matr=',matr)

Z = fscema(M,S)

plt.figure()
plt.pcolormesh(S,M,Z,shading='auto')
plt.xlabel('$\sigma$')
plt.ylabel('$\mu$')

plt.figure()
ax = plt.axes(projection='3d')
ax.plot_surface(M, S, matr,cmap='viridis', edgecolor='none')
ax.set_title('$ E_T $')


plt.show()
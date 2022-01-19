import matplotlib.pyplot as plt
import numpy as np

def f(x, y):
    return np.sin(np.sqrt(x ** 2 + y ** 2))

x = np.linspace(-6, 6, 5)
y = np.linspace(-6, 6, 5)

X, Y = np.meshgrid(x, y)
Z = f(X, Y)

print('X=',X)
print('Y=',Y)
print('Z=',Z)

plt.figure()
ax = plt.axes(projection='3d')
ax.plot_surface(X, Y, Z, rstride=1, cstride=1, cmap='viridis', edgecolor='none')
ax.set_title('surface');

plt.show()
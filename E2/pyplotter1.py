import matplotlib
import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit

def f (x,k):
    return k*(x**0.5)


y, err = np.loadtxt("data/discreteRW.dat", usecols=(0,1), delimiter=' ', unpack=True)
x      = np.arange(y.size)

plt.errorbar(x,y,err)
plt.grid(True)
plt.xlabel('passi')
plt.ylabel('sqrt(<|r|^2>)')
plt.title('Random Walk su reticolo discreto - a=1')

p_opt, p_cov = curve_fit(f, x, y)
y_fit = f(x,p_opt[0])
plt.plot(x,y_fit,'r--') # plotting fitted function

print( ' --- Random Walk over a discrete lattice --- ')
print('fit with k*sqrt(x): k = '+str(p_opt))
print('confidence over k : +- '+str(np.sqrt(np.diagonal(p_cov))))

plt.figure()

y,err = np.loadtxt("data/continuousRW.dat", usecols=(0,1), delimiter=' ', unpack=True)

plt.errorbar(x,y,err)
plt.grid(True)
plt.xlabel('passi')
plt.ylabel('sqrt(<|r|^2>)')
plt.title('Random Walk su reticolo continuo - a=1')

p_opt, p_cov = curve_fit(f, x, y)
y_fit = f(x,p_opt[0])
plt.plot(x,y_fit,'r--') # plotting fitted function

print( ' --- Random Walk in a continuum space --- ')
print('fit with k*sqrt(x): k = '+str(p_opt))
print('confidence over k : +- '+str(np.sqrt(np.diagonal(p_cov))))

plt.show()

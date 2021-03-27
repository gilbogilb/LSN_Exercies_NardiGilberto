import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import math

#graf
expected = math.pi
f, error = np.loadtxt("data/03.dat", usecols=(0,1), delimiter=' ', unpack='true')
x = np.arange(f.size)
plt.errorbar(x,f-expected,yerr=error)
plt.xlabel('#throws')
plt.ylabel('calcpi-math.pi')
plt.grid(True)


#isto
plt.figure()
chi = np.loadtxt('data/1Chi.dat')
nbins = 30

n, bins, patches = plt.hist(chi, nbins, range=(65,135) )
#plt.xlabel('Valori di Chi^2')
plt.title('Distribuzione di Chi^2')

plt.show()

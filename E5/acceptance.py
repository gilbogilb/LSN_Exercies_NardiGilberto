#view statistic about acceptance
import matplotlib.pyplot as plt
import numpy as np

#u100, u210, g100, g210 = np.loadtxt('mean_acceptance.dat',unpack=True)
#x = np.arange(u100.size)

#plt.figure(figsize=(15,10))
#plt.title('Mean acceptance automatically set')
#plt.xlabel('sample')
#plt.ylabel('acceptance')
#plt.plot(x,u100,label='Uniform 100')
#plt.plot(x,u210,label='Uniform 210')
#plt.plot(x,g100,label='Gaussian 100')
#plt.plot(x,g210,label='Gaussian 210')
#plt.legend()
#plt.grid(True)
#plt.show()

delta, uexp, gexp, u1, g1, u2, g2 = np.loadtxt('acceptance-delta.dat',unpack=True)

plt.figure(figsize=(15,7))

plt.subplot(131)
plt.plot(delta,uexp,label='uniform')
plt.plot(delta,gexp,label='gaussian')
plt.legend()
plt.xlabel('delta')
plt.ylabel('acceptance')
plt.title('expo')

plt.subplot(132)
plt.plot(delta,u1,label='uniform')
plt.plot(delta,g1,label='gaussian')
plt.legend()
plt.xlabel('delta')
plt.ylabel('acceptance')
plt.title('Psi100')

plt.subplot(133)
plt.plot(delta,u2,label='uniform')
plt.plot(delta,g2,label='gaussian')
plt.legend()
plt.xlabel('delta')
plt.ylabel('acceptance')
plt.title('psi200')

plt.show()
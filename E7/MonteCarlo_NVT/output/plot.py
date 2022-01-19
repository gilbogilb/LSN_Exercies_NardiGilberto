import matplotlib.pyplot as plt
import numpy as np

U, P = np.loadtxt('solid/solidraw.dat',unpack=True,max_rows=500)
steps = np.arange(U.size)

plt.figure()
plt.subplot(121)
plt.plot(steps,U)
plt.title('U/N raw')

plt.subplot(122)
plt.plot(steps,P)
plt.title('P raw')

plt.show()

import matplotlib.pyplot as plt
import numpy as np

x0,y0 = np.loadtxt("parallel_data/bestpath0.dat", unpack=True)
x0 = np.append(x0, x0[0])
y0 = np.append(y0, y0[0])

plt.figure(figsize=(16,8))
plt.subplot(221)
plt.plot(x0,y0)
plt.plot(x0,y0,'r^',label='cities')
plt.plot(x0[0],y0[0],'g^',label='start-end')
plt.grid(True)
plt.title('Cities distribution & best path',fontweight='bold',fontsize=15)
plt.legend()

x1,y1 = np.loadtxt("parallel_data/bestpath1.dat", unpack=True)
x1 = np.append(x1, x1[0])
y1 = np.append(y1, y1[0])

plt.subplot(222)
plt.plot(x1,y1)
plt.plot(x1,y1,'r^',label='cities')
plt.plot(x1[0],y1[0],'g^',label='start-end')
plt.grid(True)
plt.title('Cities distribution & best path',fontweight='bold',fontsize=15)
plt.legend()

x2,y2 = np.loadtxt("parallel_data/bestpath2.dat", unpack=True)
x2 = np.append(x2, x2[0])
y2 = np.append(y2, y2[0])

plt.subplot(223)
plt.plot(x2,y2)
plt.plot(x2,y2,'r^',label='cities')
plt.plot(x2[0],y2[0],'g^',label='start-end')
plt.grid(True)
plt.title('Cities distribution & best path',fontweight='bold',fontsize=15)
plt.legend()

x3,y3 = np.loadtxt("parallel_data/bestpath3.dat", unpack=True)
x3 = np.append(x3, x3[0])
y3 = np.append(y3, y3[0])

plt.subplot(224)
plt.plot(x3,y3)
plt.plot(x3,y3,'r^',label='cities')
plt.plot(x3[0],y3[0],'g^',label='start-end')
plt.grid(True)
plt.title('Cities distribution & best path',fontweight='bold',fontsize=15)
plt.legend()

c0=np.loadtxt('parallel_data/best0.dat')
c1=np.loadtxt('parallel_data/best1.dat')
c2=np.loadtxt('parallel_data/best2.dat')
c3=np.loadtxt('parallel_data/best3.dat')
steps = np.arange(c0.size)

plt.figure()
plt.plot(np.arange(c0.size),c0,label='continent 0')
plt.plot(np.arange(c1.size),c1,label='continent 1')
plt.plot(np.arange(c2.size),c2,label='continent 2')
plt.plot(np.arange(c3.size),c3,label='continent 3')
plt.legend()


plt.show()
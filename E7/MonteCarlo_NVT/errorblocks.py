# study the relation between blocks size and final error
import matplotlib.pyplot as plt
import numpy as np


class DataBlockingTool:
    
    def __init__(self,blocksize):
        self.blk_size=blocksize
        self.blk_sum=0.     #sum of the elements of this block
        self.blk_num=0      #number of blocks
        self.err=0.         #statistical error
        self.progmean=0.    #progressive mean of blocks
        self.progmean2=0.   #progressive squares mean of blocks
        self.blk_val_num=0. #number of values in a block
    
    def AppendVal(self,val):
        self.blk_sum+=val
        self.blk_val_num+=1.0
        if(self.blk_val_num==self.blk_size): #the block is full
            av=self.blk_sum/float(self.blk_size)
            self.progmean  = (self.progmean*self.blk_num+av)/(1.+self.blk_num)
            self.progmean2 = (self.progmean2*self.blk_num+av*av)/(1.+self.blk_num)
            self.blk_num+=1.0
            if(self.blk_num>1):
                self.err=np.sqrt((self.progmean2-(self.progmean**2.))/(self.blk_num-1))
            #reinitialization
            self.blk_sum=0.
            self.blk_val_num=0
            
    def flush(self):     #only keeps block size
        self.blk_sum=0.
        self.blk_num=0
        self.err=0.
        self.progmean=0.
        self.progmean2=0.
        self.blk_val_num=0.

            
#create an array of tools
tools = []
blocksizes = []
linsizes = np.linspace(10,5000,245)
for l in linsizes:
    blocksizes.append(int(l))

for s in blocksizes:
    t = DataBlockingTool(s)
    tools.append(t)

#load data and analyze
U, P = np.loadtxt("output/solidraw.dat",unpack=True,usecols=(0,1))

Uerr = np.array([])
Perr = np.array([])

for t in tools:
    #Internal energy
    for u in U:
        t.AppendVal(u)
    Uerr=np.append(Uerr,t.err)
    #print(t.err,t.blk_size,t.blk_num,t.progmean)
    t.flush()
    #Pressure
    for p in P:
        t.AppendVal(p)
    Perr=np.append(Perr,t.err)
    #print(t.err,t.blk_num,t.progmean)
    t.flush
    
plt.figure()
plt.suptitle('Block sizes and errors - Solid phase',fontweight='bold')
plt.subplot(121)
plt.plot(blocksizes,Uerr)
plt.xlabel('block size')
plt.ylabel('error [$\sigma_{U/N}$]')
plt.title('Internal energy per particle errors')
plt.grid(True)
plt.subplot(122)
plt.plot(blocksizes,Perr)
plt.xlabel('block size')
plt.ylabel('error [$\sigma_P$]')
plt.title('Pressure errors')
plt.grid(True)
plt.show()
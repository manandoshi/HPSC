
# coding: utf-8

# In[1]:


import pandas as pd
import numpy as np
import matplotlib.pyplot as plt


# In[2]:


tm = pd.read_csv('mpi/timing.csv',header = None, names=['method','error','val','threads','numpoints','time'])
tr = tm.loc[tm['method']=='Trapezoidal']
mc = tm.loc[tm['method']=='Monte-Carlo']


# In[3]:


print "Data - Trapezoidal \n"
tr = tr.groupby(['threads']).mean()
print tr['time']
print "\nData - Monte Carlo\n"
mc = mc.groupby(['threads']).mean()
print mc['time']


# In[4]:


fig, axs = plt.subplots(1,2, figsize=(12,5))

axs[0].loglog(tr.index,tr.time*1e3, 'b-x');
axs[0].set_xlabel('Number of threads');
axs[0].set_ylabel(r'Time (in $\mu$sec)');
axs[0].set_title('Timing study for Integration using Trapezoidal Rule')

axs[1].loglog(mc.index,mc.time*1e3, 'b-x');
axs[1].set_xlabel('Number of threads');
axs[1].set_ylabel(r'Time (in $\mu$sec)');
axs[1].set_title('Timing study for Integration using Monte-Carlo Method')

plt.tight_layout()
plt.savefig('timing_mpi.png')
plt.show()


# In[5]:


conv = pd.read_csv('mpi/conv.csv',header = None, names=['method','error','val','threads','numpoints','time'])
tr = conv.loc[conv['method']=='Trapezoidal']
mc = conv.loc[conv['method']=='Monte-Carlo']
mc = mc.groupby(['numpoints']).mean()

tx = tr.numpoints
mx = list(mc.index)
ty = tr.error
my = mc.error

fig, axs = plt.subplots(1,2, figsize=(12,5))

axs[0].loglog(tx,ty,'-o');
axs[0].set_xlabel('Number of points');
axs[0].set_ylabel('Error');
axs[0].set_title('Covergence study for Integration using Trapezoidal Rule')

axs[1].loglog(mx,my,'-o');
axs[1].set_xlabel('Number of points');
axs[1].set_ylabel('Average Absolute Error over 50 runs');
axs[1].set_title('Covergence study for Integration using Monte-Carlo Method')

plt.savefig('conv_mpi.png')
plt.show()


# In[6]:


conv = pd.read_csv('cuda/conv.csv',header = None, names=['method','error','val','threads','numpoints','time'])
tr = conv.loc[conv['method']=='Trapezoidal']
mc = conv.loc[conv['method']=='Monte-Carlo']
mc = mc.groupby(['numpoints']).mean()

tx = tr.numpoints
mx = list(mc.index)
ty = tr.error
my = mc.error

fig, axs = plt.subplots(1,2, figsize=(12,5))

axs[0].loglog(tx,ty,'-o');
axs[0].set_xlabel('Number of points');
axs[0].set_ylabel('Error');
axs[0].set_title('Covergence study for Integration using Trapezoidal Rule')

axs[1].loglog(mx,my,'-o');
axs[1].set_xlabel('Number of points');
axs[1].set_ylabel('Average Absolute Error over 50 runs');
axs[1].set_title('Covergence study for Integration using Monte-Carlo Method')

plt.savefig('conv_cuda.png')
plt.show()


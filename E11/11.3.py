import numpy as np
import matplotlib.pyplot as plt

def sinsq(x,y): #target function
    return np.sin(x*x+y*y)

x = np.linspace(-1.5,1.5,50)
y = x
X,Y = np.meshgrid(x,y)
Z = sinsq(X,Y)

# generate a Dataset
#we need a vector of 2D points: represented as a ntrainX2 matrix ((x,y) for each element)

n_train = 20000
n_valid = int(n_train/10)
sigma = 0.1

np.random.seed(1)
#training data
x0_train = np.random.uniform(-1.5,1.5,n_train)
x1_train = np.random.uniform(-1.5,1.5,n_train)

x_train = np.column_stack((x0_train,x1_train))

y_train = np.random.normal(sinsq(x0_train,x1_train),sigma)

#validation data
x0_valid = np.random.uniform(-1.5,1.5,n_valid)
x1_valid = np.random.uniform(-1.5,1.5,n_valid)

x_valid = np.column_stack((x0_valid,x1_valid))

y_valid = np.random.normal(sinsq(x0_valid,x1_valid),sigma)


#skipping graphing the target function


#building the model
import tensorflow as tf
from tensorflow import keras

from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Activation
from tensorflow.keras import backend as K
from tensorflow.keras.utils import get_custom_objects

model = Sequential()
model.add(Dense(10,input_shape=(2,),activation='relu'))
model.add(Dense(40, input_shape=(2,), activation='relu'))
model.add(Dense(35, activation='relu'))
model.add(Dense(30, activation='relu'))
model.add(Dense(1))

# compile the model choosing optimizer, loss and metrics objects
model.compile(optimizer='sgd', loss='mse', metrics=['mse'])
model.summary()


# fit the model using training dataset
# over 10 epochs of 32 batch size each
# report training progress against validation data
history = model.fit(x=x_train, y=y_train,
          batch_size=500, epochs=100,
          shuffle=True, # a good idea is to shuffle input before at each epoch
          validation_data=(x_valid, y_valid))


# Plot training & validation loss values over time
plt.figure(figsize=(9,6))
plt.title('Loss function over time')
plt.plot(history.history['loss'])
plt.plot(history.history['val_loss'])
plt.title('Model loss')
plt.ylabel('Loss')
plt.xlabel('Epoch')
plt.legend(['Train', 'Test'], loc='best')
plt.show()

#make and plot prediction
x0_pred = np.random.uniform(-1.5,1.5,n_valid)
x1_pred = np.random.uniform(-1.5,1.5,n_valid)

x_pred = np.column_stack((x0_pred,x1_pred))
y_pred = model.predict(x_pred)
y_target = sinsq(x0_pred,x1_pred)

delta = np.resize(y_pred,(n_valid,))-y_target
print(y_pred.shape,y_target.shape,delta.shape)

fig=plt.figure(figsize=(12,8))
ax = plt.axes(projection='3d')
ax.scatter3D(x0_pred, x1_pred, y_pred, color='green',marker='o')
ax.set_title('predicted points')
ax.view_init(5, 20)

plt.figure(figsize=(12,8))
ax = plt.axes(projection='3d')
ax.scatter3D(x0_pred, x1_pred, y_target, color='green',marker='o')
ax.set_title('target points')
ax.view_init(5, 20)

plt.figure(figsize=(12,8))
ax = plt.axes(projection='3d')
ax.scatter3D(x0_pred, x1_pred, delta, color='green',marker='o')
ax.set_title('Difference between predicted points and target function')
ax.view_init(5, 20)

plt.show()


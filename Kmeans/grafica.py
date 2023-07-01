import numpy as np
import matplotlib.pyplot as plt

w, z=np.loadtxt('resultados.txt',skiprows=1,usecols=[0,1],unpack=True)
x, y=np.loadtxt('centroides3.txt',skiprows=1,usecols=[0,1],unpack=True)
x2, y2=np.loadtxt('datos.txt',skiprows=1,usecols=[0,1],unpack=True)
print(x,y)
plt.title("Datos de los centroides")
plt.xlabel("x")
plt.ylabel("y")
plt.grid(True)
plt.plot(w,z,"r*",x2,y2,"^g",x,y,"bo")
plt.show()

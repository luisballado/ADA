import time
import matplotlib.pyplot as plt
import numpy as np

def graficar(xs, ys):
    
    xs = np.array(xs)
    ys = np.array(ys)
    
    
    plt.plot(xs, ys, lw=2, marker="o",linestyle='--',color="#ff3333",label='32 ROBOTS')
    
    plt.xticks(xs)
    plt.yticks(ys)
    
    plt.title("EBW - Evaluación clásica")
    plt.xlabel("Tamaño de grafo bipartito completo Kn,n")
    plt.ylabel("Tiempo de ejecución (ns)")
    plt.grid()
    #plt.legend()
    plt.savefig('ebw_clasica.png')
    plt.show()
    
xs = ["10","20","30","40","50","60","70","80","90","100"]
ys = [2870,23270,80750,173530,442890,1241580,1366080,1644909,2222419,3280289]
    
# create data
#graficar(xc1,yc1,xc2,yc2,xc4,yc4,xc8,yc8,xc16,yc16)
graficar(xs, ys)
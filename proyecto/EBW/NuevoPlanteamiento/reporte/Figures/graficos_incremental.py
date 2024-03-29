import time
import matplotlib.pyplot as plt
import numpy as np

def graficar(xs, ys):
    
    xs = np.array(xs)
    ys = np.array(ys)

    x = np.linspace(0,10)
    y = np.linspace(0,3880)
    
    plt.plot(x, y)
    plt.plot(xs, ys, lw=2, marker="o",linestyle='--',color="#ff3333")
    
    plt.xticks(xs)
    plt.yticks(ys)
    
    plt.title("EBW - Evaluación incremental")
    plt.xlabel("Tamaño de grafo bipartito completo Kn,n")
    plt.ylabel("Tiempo de ejecución (ns)")
    plt.grid()
    #plt.legend()
    plt.savefig('ebw_incremental.png')

    plt.show()
    
xs = ["10","20","30","40","50","60","70","80","90","100"]
ys = [540,590,1630,1609,1720,2860,3010,2510,3880,3020]



# create data
#graficar(xc1,yc1,xc2,yc2,xc4,yc4,xc8,yc8,xc16,yc16)
graficar(xs, ys)

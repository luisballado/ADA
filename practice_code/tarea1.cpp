#include <iostream>
#include <vector>

//Funcion dummy para revisar si un
//elemento esta dentro de un vector
//Al tener un for con entrada n,
//la funcion tiene complejidad O(n)
bool existe(std::vector<int> _vector_, int valor){
  for(int i = 0; i < _vector_.size(); i++){ // n
    if (_vector_[i] == valor){              // 1
      return true;
    }
  }
  return false;
}

//Complejidad funcion principal O(n²)
//por el doble for que recorre los arreglos
int main(){

  int a[] = {2,5,5,5};                     // 1
  int b[] = {2,2,3,5,5,7};                 // 1

  //vector de resultados
  std::vector<int>arr;                     // 1

  //Solucion tomada del ejemplo 3
  //https://www.digitalocean.com/community/tutorials/find-array-length-in-c-plus-plus
  //longitud array1
  int a_length = sizeof(a)/sizeof(a[0]);   // 1
  //longitud array2
  int b_length = sizeof(b)/sizeof(b[0]);   // 1
  
  //Usando fuerza bruta                    // O(n²)
  for (int i = 0; i < a_length; i++){      
    for (int j = 0; j < b_length; j++){    
      std::cout << "comp\n";       // 1
      if (a[i] == b[j]){                   // 1
	//revisar si ya existe en el array donde se guarda
	if (!existe(arr,a[i])){            // 1
	  arr.push_back(a[i]);             
	}
	break;
      }
    }
  }

  //--------------------
  // Imprimir resultado
  //--------------------
  
  std::cout << "El resultado es: \n";       // 1
  for(int i = 0; i<arr.size(); i++){        // n
    std::cout << arr[i] << "\n";            // 1
  }
  
}

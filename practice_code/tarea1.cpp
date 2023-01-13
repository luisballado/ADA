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

  std::vector<int>::iterator it;
  
  std::vector<int> a;
  a.push_back(2);
  a.push_back(5);
  a.push_back(5);
  a.push_back(5);

  std::vector<int> b;
  b.push_back(2);
  b.push_back(2);
  b.push_back(3);
  b.push_back(5);
  b.push_back(5);
  b.push_back(7);

  //vector de resultados
  std::vector<int>arr;                     // 1
  
  //Usando fuerza bruta                    // O(n²)
  for (int i = 0; i < a.size(); i++){      
    for (int j = 0; j < b.size(); j++){    
      std::cout << j << "comparacion \n";       // 1
      if (a[i] == b[j]){                   // 1
	//revisar si ya existe en el array donde se guarda
	//if (!existe(arr,a[i])){            // 1
	  arr.push_back(a[i]);
	  //}
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

#include <iostream>
#include <vector>

//NO USADA
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
  std::vector<int>arr;

  int last_index = 0;

  //Usando fuerza bruta                    // O(n²)
  for (int i = 0; i < a.size(); i++){      // O(n)
    for (int j = i; j < b.size(); j++){    // O(n)
      
      std::cout << a[i] << "<-a comparacion b->"<< b[last_index] << "\n";
      
      if (a[i] == b[last_index]){
	arr.push_back(a[i]);
	break; // romper ciclo cuando sean iguales
      }
      
      last_index = i+1; //indice auxiliar para avanzar 
      
    }
  }
  
  //--------------------
  // Imprimir resultado
  //--------------------
  
  std::cout << "El resultado es: \n";       // 1
  for(int i = 0; i<arr.size(); i++){        // n
    std::cout << arr[i] << "\n";
  }
  
}

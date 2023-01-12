#include <iostream>
#include <vector>

//Funcion dummy para revisar si un elemento esta dentro del arr
bool existe(std::vector<int> _vector_, int valor){
  
  int v_length = _vector_.size();
  
  for(int i = 0; i < v_length; i++){
    if (_vector_[i] == valor){
      //std::cout << "Elemento encontrado";
      return true;
    }
  }

  return false;
}

int main(){

  int a[] = {2,5,5,5}; //array 1
  int b[] = {2,2,3,5,5,7}; //array 2
  
  std::vector<int>arr; //vector de resultados

  int a_length = sizeof(a)/sizeof(a[0]); //longitud array1
  int b_length = sizeof(b)/sizeof(b[0]); //longitud array2

  int arr_length;

  //Usando fuerza bruta
  for (int i = 0; i < a_length; i++){
    for (int j = 0; j < b_length; j++){
      if (a[i] == b[j]){
	//revisar si ya existe en el array donde se guarda
	if (!existe(arr,a[i])){
	  arr.push_back(a[i]);
	}
	break;
      }
    }
  }
  
  std::cout << "El resultado es: \n";
  for(int i = 0; i<arr.size(); i++){
    std::cout << arr[i] << "\n";
  }
  
}

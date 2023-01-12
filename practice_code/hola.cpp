//Comentarios
/*Comentarios*/
//Ejemplo de un hola mundo
#include <iostream> //Libreria Input Output Stream

//Main function
int main(){
  char variable_char; //Character type
  int variable_int; //Integer type
  float variable_float; //Float type
  double variable_double; //Double_type
  bool variable_bool = false;

  std::string firstName = "Luis";
  std::string lastName = "Ballado";
  
  if(variable_bool){
    std::cout<<"\a"; //Alarm or Beep
    std::cout << "Hola Mundo\n";
    std::string fullName = firstName.append(lastName);
    std::cout << fullName+"\n";
    std::cout << "La longitud de tu nombre es: " << fullName.length();
  }else if (variable_bool == false){
    std::cout<<"Es falso";
  }else{
    std::cout<<"Algo raro";
  }
  return 0;
}

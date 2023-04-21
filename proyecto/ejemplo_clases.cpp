#include <iostream>
#include <string>
#include <list>

using namespace std;

class BankAccount{
public:
  string nombre;
  int saldo;
  list<int> movimientos;

  //Constructor
  BankAccount(string name, int balance){
    nombre = name;
    saldo = balance;
  }
  
  //funciones aqui dentro pueden accesar a las variables
  //método
  void withdraw(int amount){
    saldo = saldo - amount;
  }

  //método
  void print(){
    cout << nombre << " has " << saldo << endl;
  }
  
};

int main(){

  BankAccount account1("Luis",10000000);
  account1.movimientos.push_back(1);
  account1.movimientos.push_back(7);
  
  account1.print();
  account1.withdraw(10);
  account1.print();

  for(int mov : account1.movimientos){
    cout << mov << endl;
  }
  
  return 0;
}

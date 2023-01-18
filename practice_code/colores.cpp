#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include <chrono>
#include <thread>

#include <unistd.h>
#include <cstdlib>

int main(){

  /**
  for(int counter=1;counter<=5;counter++){
    system("clear");
    printf("\033[31mred text\n");
    printf("\033[33;44myellow on blue\n");
    printf("\033[0mdefault colors\n");
    }**/

  //std::cout << std::endl; //salto de linea

  int size_x = 10;
  int size_y = 15;
  char a[size_x][size_y];
  int x = 0;

  //robot position
  int robot_x = 6;
  int robot_y = 6;

  //goal position
  int goal_x = 8;
  int goal_y = 13;

  for(int i=0; i<10;i++){
    
    system("clear");
    //std::cout << std::endl; //salto de linea
    
    //cargar la matriz
    for(int i = 0; i < size_x; i++){
      for(int j = 0; j < size_y; j++){
	a[i][j] = 'o';
      }
    }

    //IMPRIMIR-IMPRIMIR-IMPRIMIR-IMPRIMIR-IMPRIMIR-
    for(int i = 0; i < size_x; i++){
      for(int j = 0; j < size_y; j++){
	std::cout << a[i][j] << " ";
      }
      //salto de linea
      std::cout << std::endl;
    }

    sleep(1);
    system("clear");
    
    //Superficies poner una X
    for(int i = 0; i < size_x; ++i){
      for(int j = 0; j < size_y; ++j){
	if(i == 0 || i == size_x - 1 || j == 0 || j == size_y - 1){
	  a[i][j] = 'X';
	}
      }
    }
    
    //IMPRIMIR-IMPRIMIR-IMPRIMIR-IMPRIMIR-IMPRIMIR-

    //std::cout << std::endl; //salto de linea
    //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    
    
    
    //xx
    for(int i = 0; i < size_x; i++){
      for(int j = 0; j < size_y; j++){
	/**
	   if(a[i][j] == 'o'){
	   a[i][j] = 'o';
	   }
	**/
	//std::cout << '\a'; //hacer un sonido de beep
	
	if(i == robot_x and j == robot_y){
	  a[i][j] = 'R';
	}else if(i == goal_x and j == goal_y) {
	  a[i][j] = 'G';
	}
	
	std::cout << a[i][j] << " ";
      }
      //salto de linea
      std::cout << std::endl;
    }
    
    std::cout << std::endl; //salto de linea
    
  }
  
  
  
  return 0;
}

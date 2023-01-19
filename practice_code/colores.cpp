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

  int ccc;
  
  for(ccc=1; ccc<=10;ccc++){
    
    system("clear");
    std::cout << '\a'; //hacer un sonido de beep
    printf("steps: %d\n",ccc);
    //std::cout << std::endl; //salto de linea
    
    //crear la matriz
    for(int i = 0; i < size_x; i++){
      for(int j = 0; j < size_y; j++){
	//Superficies poner una X si no una o
	if(i == 0 || i == size_x - 1 || j == 0 || j == size_y - 1){
	  a[i][j] = 'X';
	}else{
	  a[i][j] = 'o';
	}
      }
    }
    
    //IMPRIMIR-IMPRIMIR-IMPRIMIR-IMPRIMIR-IMPRIMIR-
    for(int i = 0; i < size_x; i++){
      for(int j = 0; j < size_y; j++){
	std::cout << a[i][j] << " ";
      }
      //imprimir todo cout con la matriz
      std::cout << std::endl;
    }
    
    //IMPRIMIR-IMPRIMIR-IMPRIMIR-IMPRIMIR-IMPRIMIR-
    
    //std::cout << std::endl; //salto de linea
    //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    
    sleep(1);
    system("clear");
    
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

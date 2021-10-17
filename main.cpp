#include "grid.h"
#include <iostream>
//#include <string>

// Check if no more tokens can be placed
bool isGridFull() {
    for (int row = 0; row < 2; ++row) {
        for (int col = 0; col < 2; ++col) {
            if (grid.fields(row, col) == ' ') {
                return false;
            }
        }
    }
    return true;
}


//Check if move is valid and place line
bool drawLine(int row, int col, char direction) {
  if (row >= 0 && row <= 2 && col >= 0 && col <= 2){

    if (direction == 'u'){
      if (row != 0 && !grid.vertical(row - 1, col)){
        grid.vertical(row - 1, col) = true;
        return true;
      }
    }else if (direction == 'd'){
      if (row != 2 && !grid.vertical(row, col)){
        grid.vertical(row, col) = true;
        return true;
      }
    }else if (direction == 'l'){
      if (col != 0 && !grid.horizontal(row, col - 1) ){
        grid.horizontal(row, col - 1) = true;
        return true;
      }
    }else if (direction == 'r'){
      if (col != 2 && !grid.horizontal(row, col) ){
        grid.horizontal(row, col) = true;
        return true;
      }
    }
    
  }  
  
  std::cout << "Invalid move!" << std::endl;
  return false;
}


//Does adding a line result in drawing an unclaimed box?
bool shouldPlaceToken(int row, int col) {
  if (grid.horizontal(row, col) && grid.vertical(row, col) && grid.horizontal(row + 1, col) && grid.vertical(row, col + 1)){
    if (grid.fields(row, col) == ' '){
      return true;  
    }
  }
  return false;
}

void AnnounceWinner(unsigned int FieldsA, unsigned int FieldsB){
  if (FieldsA == FieldsB){
    std::cout << "Draw!" << std::endl;
    return;
  }
  
  if (FieldsA > FieldsB){
    std::cout << "A ";
  }else{
    std::cout << "B ";
  }
  
  std::cout << "won!" << std::endl;
  return;
}


int main() {
  int input1;
  int input2;
  char input3;
  unsigned int FieldsA = 0;
  unsigned int FieldsB = 0;
  unsigned int Round = 1;
  bool PlayAgain;
  
  while (!isGridFull()){
    PlayAgain = true;
        while (PlayAgain){
          grid.printGrid(); 
          PlayAgain = false;
            do{
              std::cin >> input1 >> input2 >> input3;
              }while(!drawLine(input1, input2, input3));
                for (int row = 0; row < 2; ++row) {
              for (int col = 0; col < 2; ++col) {
                  if (shouldPlaceToken(row, col)) {
                     if (Round % 2 == 1){
                       grid.fields(row, col) = 'A';
                       FieldsA++;
                       PlayAgain = true;
                     }else{
                       grid.fields(row, col) = 'B';
                       FieldsB++;
                       PlayAgain = true;
                     }
                  }
              }
            }
         if (isGridFull()) break;   
        }
        
      
    Round++;    
  }
  grid.printGrid();
  AnnounceWinner(FieldsA, FieldsB);
  return 0;
}
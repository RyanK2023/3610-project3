/*
  Name: Ryan Kilkenney
  Date: 10/25/2020
  Purpose: It's the implementation for the knights_tour class
*/
#include <iostream>
#include <iomanip>
#include "knights_tour.h"
using namespace std;

//It's just a constructor that's used to make a board object
KnightsTour::KnightsTour(int board_size) {
  this->board_size = board_size;

  this->board.resize(board_size);
  for (int i = 0; i < board_size; ++i) {
    this->board[i].resize(board_size);
  }
}

//outputs everything in the board object
void KnightsTour::print() {
  for (int i = 0; i < this->board_size; i++) {
    for (int j = 0; j < this->board_size; j++)
      cout << setw(4) << this->board[i][j] << " ";
    cout << endl;
  }
  cout << endl << endl;
}

// Function: get_moves()
//    Desc: Get the row and column indices of all valid
//          knight moves reachable from position row, col.
//          An invalid move would be one that sends the
//          knight off the edge of the board or
//          to a position that has already been visited.
//          
//    int row         - Current row position of knight.
//    int col         - Current column position of knight.
//    int row_moves[] - Array to store row indices
//                      of all valid new moves reachable from
//                      the current position row, col.
//    int col_moves[] - Array to store column indices
//                      of all valid new moves reachable from
//                      the current position row, col.
//    int num_moves -   Number of valid moves found. Corresponds
//                      to the sizes of row_moves and col_moves.

void KnightsTour::get_moves(int row, int col, int row_moves[], int col_moves[], int& num_moves) {
  //check 8 positions for valididity
  //First if statement checks if each row, col are on the board
  //to check if off board, check if new row/col are between 0 and 4
  //Then it checks if the postion in board[row][col] is empty
  //the "return value" is num_moves, its the number of valid moves from a spot 

  //checks right 2, up 1
  if(((row - 1 < 5) && (row - 1 > -1)) && ((col + 2 < 5) && (col + 2 > -1)) ) {
     if(board[row-1][col+2] == 0) {
       row_moves[num_moves] = row - 1;
       col_moves[num_moves] = col + 2;
       num_moves++;
     }
  }

  //checks right 2, down 1
  if(((row + 1 < 5) && (row + 1 > -1)) && ((col + 2 < 5) && (col + 2 > -1)) ) {    
      if(board[row+1][col+2] == 0) {
        row_moves[num_moves] = row + 1;
        col_moves[num_moves] = col + 2;
        num_moves++;
      }
  }

  //checks right 1, down 2
  if(((row + 2 < 5) && (row + 2 > -1)) && ((col + 1 < 5) && (col + 1 > -1)) ) {
      if(board[row+2][col+1] == 0) {
        row_moves[num_moves] = row + 2;
        col_moves[num_moves] = col + 1;
        num_moves++;
      }
  }

  //checks left 1, down 2
  if(((row + 2 < 5) && (row + 2 > -1)) && ((col - 1 < 5) && (col - 1 > -1)) ) {
      if(board[row+2][col-1] == 0) {
        row_moves[num_moves] = row + 2;
        col_moves[num_moves] = col - 1;
        num_moves++;
      }
  }

  //checks left 2, down 1
  if(((row + 1 < 5) && (row + 1 > -1)) && ((col - 2 < 5) && (col - 2 > -1)) ) {
      if(board[row+1][col-2] == 0) {
        row_moves[num_moves] = row + 1;
        col_moves[num_moves] = col - 2;
        num_moves++;
         
      }
  }

  //checks left 2, up 1
  if(((row - 1 < 5) && (row - 1 > -1)) && ((col - 2 < 5) && (col - 2 > -1)) ) {
      if(board[row-1][col-2] == 0) {
        row_moves[num_moves] = row - 1;
        col_moves[num_moves] = col - 2;
        num_moves++;
      }
  }

  //checks left 1, up 2
  if(((row - 2 < 5) && (row - 2 > -1)) && ((col - 1 < 5) && (col - 1 > -1)) ) {
      if(board[row-2][col-1] == 0) {
        row_moves[num_moves] = row - 2;
        col_moves[num_moves] = col - 1;
        num_moves++;
      }
  }
  
  //checks right 1, up 2
  if(((row - 2 < 5) && (row - 2 > -1)) && ((col + 1 < 5) && (col + 1 > -1)) ) {
      if(board[row-2][col+1] == 0) {
        row_moves[num_moves] = row - 2;
        col_moves[num_moves] = col + 1;
        num_moves++;
      }
  }
}

// Function: move() --> Recursive
//     int row        - Current row position of knight.
//     int col        - Current column position of knight.
//     int& m         - Current move id in tour.
//                      Stored in board at position
//                      row, col.
//     int& num_tours - Total number of tours found

void KnightsTour::move(int row, int col, int& m, int& num_tours) {
  //increment move
  m++; //its the number of moves made so far

  //record m at row, col in board
  board[row][col] = m; 

  //use get_moves() to find all valid moves from row, col
  int row_moves[8]; //its an array that holds the x/row value of all valid moves
  int col_moves[8]; //its an array that holds the y/row value of all valid moves
  int num_moves = 0; //its the number of valid moves from a spot 
  get_moves(row, col, row_moves, col_moves, num_moves);

  //this whole next section is for backtracking

  //this runs when the board has been completely filled and outputs the results 
  //it also backtracks so it can go and find other tours 
  if(m >= 25) {
    print();
    num_tours++;
    m--;
    board[row][col] = 0;
    return;
  }

  //this runs if no valid moves are found from get_moves() and backtracks to find other solutions 
  if(num_moves == 0) {
    m--;
    board[row][col] = 0;
    return;
  }

  //it recursively calls move() for every valid move from get_moves()
  for(int i = 0; i < num_moves; i++) {
    move(row_moves[i], col_moves[i], m, num_tours);
  }
  m--;
  board[row][col] = 0;
  return;
}

int KnightsTour::generate(int row, int col) {
  int m = 0;
  int num_tours = 0;
  move(row, col, m, num_tours);

  return num_tours;
}

/* COMP2011 Spring 2019
 * Assignment 2
 * File: pa2.cpp
 * Function definitions
 *
 * Student name: Bryan Suryaraso Gani
 * Student ID: 20558912
 * Student email: bsgani@connect.ust.hk
 * Student lab section: LA2
 */

#include <iostream>
#include "func.h"
using namespace std;

// This function is used for printing out the Canvas
void printCanvas(char canvas[MAX_ROW][MAX_COL])
{
   cout << "The current canvas: " << endl;
   cout << "   " ;
   for (int i=0; i<MAX_COL; i++)
      cout << i % 10;
   cout << endl;
   cout << " //" ;
   for (int i=0; i<MAX_COL; i++)
      cout << "=";
   cout << "\\\\" << endl;
   for (int i=0; i<MAX_ROW; i++){
      cout << i % 10 << "||";
      for (int j=0; j<MAX_COL; j++){
         if (canvas[i][j] == NULL_CHAR)
            cout << ' ';
         else
            cout << canvas[i][j];
      }
      cout << "||" << endl;
   }
   cout << " \\\\";
   for (int i=0; i<MAX_COL; i++)
      cout << "=";
   cout << "//" << endl;
}

// TODO: Please implemement the required recursive functions stated in the header file (func.h) below.
// Recursive function for making lines
int makeHorizontalLine(char canvas[MAX_ROW][MAX_COL], int row, int col, int length){
  if(row < MAX_ROW && col < MAX_COL && length && row >= 0 && col >= 0){
    if(canvas[row][col] == BAR) canvas[row][col] = PLUS;
    else canvas[row][col] = HYPHEN;
    return 1 + makeHorizontalLine(canvas, row, ++col, --length);
  }
  return 0;
}

int makeVerticalLine(char canvas[MAX_ROW][MAX_COL], int row, int col, int length){
  if(row < MAX_ROW && col < MAX_COL && length && row >= 0 && col >= 0){
    if(canvas[row][col] == HYPHEN) canvas[row][col] = PLUS;
    else canvas[row][col] = BAR;
    return 1 + makeVerticalLine(canvas, ++row, col, --length);
  }
  return 0;
}

int makeUpwardSlantingLine(char canvas[MAX_ROW][MAX_COL], int row, int col, int length){
  if(row < MAX_ROW && col < MAX_COL && length && row >= 0 && col >= 0){
    if(canvas[row][col] == BACKSLASH) canvas[row][col] = CROSS;
    else canvas[row][col] = SLASH;
    return 1 + makeUpwardSlantingLine(canvas, --row, ++col, --length);
  }
  return 0;
}

int makeDownwardSlantingLine(char canvas[MAX_ROW][MAX_COL], int row, int col, int length){
  if(row < MAX_ROW && col < MAX_COL && length && row >= 0 && col >= 0){
    if(canvas[row][col] == SLASH) canvas[row][col] = CROSS;
    else canvas[row][col] = BACKSLASH;
    return 1 + makeDownwardSlantingLine(canvas, ++row, ++col, --length);
  }
  return 0;
}

//Recursive functions for making patterns
void makeHive(char canvas[MAX_ROW][MAX_COL], int row, int col, int depth){
  if(row < MAX_ROW && col < MAX_COL && depth > 0 && row >= 0 && col >= 0){
    canvas[row][col] = UNDERSCORE;
    canvas[row][col + 1] = SLASH;
    canvas[row + 1][col + 1] = BACKSLASH;
    for(int i = -2; i <= 2; i += 4) for(int j = -1; j <= 1;  j += 2)
    makeHive(canvas, row + j, col + i, depth - 1);
  }
  else return;
}

void makeTriangle(char canvas[MAX_ROW][MAX_COL], int row, int col, int layer){
  if(row < 0 || col < 0 || row >= MAX_ROW || col >= MAX_COL) return;
  if(layer == 0) canvas[row][col] = DOT;
  else{
    for(int i = 1 - layer; i <= layer - 1; i++){
      if((col + i) < MAX_COL && (col + i) >= 0) canvas[row][col + i] = HYPHEN;
    }
    if((col - layer) < MAX_COL && (col - layer) >= 0) canvas[row][col - layer] = SLASH;
    if((col + layer) < MAX_COL && (col + layer) >= 0) canvas[row][col + layer] = BACKSLASH;
    makeTriangle(canvas, --row, col, --layer);
  }
}

int fill(char canvas[MAX_ROW][MAX_COL], int row, int col, char fillChar){
  if(canvas[row][col] != NULL_CHAR || row < 0 || col < 0 || row >= MAX_ROW || col >= MAX_COL) return 0;
  canvas[row][col] = fillChar;
  return 1 + fill(canvas, row + 1, col, fillChar) + fill(canvas, row - 1, col, fillChar) + fill(canvas, row, col + 1, fillChar) + fill(canvas, row, col - 1, fillChar);
}

void repeatPattern(char canvas[MAX_ROW][MAX_COL], int row, int col, int interval_row, int interval_col, Shape choice,
        int patternParameter, int times){
          if(!times) return;
          switch(choice){
            case TRIANGLE:
            makeTriangle(canvas, row, col, patternParameter);
            break;
            case HIVE:
            makeHive(canvas, row, col, patternParameter);
            break;
            case VERTICAL:
            makeVerticalLine(canvas, row, col, patternParameter);
            break;
            case HORIZONTAL:
            makeHorizontalLine(canvas, row, col, patternParameter);
            break;
            case UPWARD_SLANTING_LINE:
            makeUpwardSlantingLine(canvas, row, col, patternParameter);
            break;
            case DOWNWARD_SLANTING_LINE:
            makeDownwardSlantingLine(canvas, row, col, patternParameter);
            break;
          }
          for(int i = col - interval_col; i <= col + interval_col; i += (2 * interval_col)){
            for(int j = row - interval_row; j <= row + interval_row; j += (2 * interval_row)) repeatPattern(canvas, j, i, interval_row, interval_col, choice, patternParameter, times - 1);
          }
        }

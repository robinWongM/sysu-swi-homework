//
// snake_move.c
// a moving snake
//
// Created by Robin Wong on 18-12-5
// Based on the work by Maolin Pan on 12-12-6
// Copyright (c) 2018 Sun Yat-sen Univerisity. All rights reserved.
// 

#include <stdio.h>
#include <stdlib.h>

#define SNAKE_MAX_LENGTH 20
#define SNAKE_HEAD 'H'
#define SNAKE_BODY 'X'
#define BLANK_CELL ' '
#define SNAKE_FOOD '$'
#define WALL_CELL '*'

//snake stepping: dy = -1(up), 1(down); dx = -1(left), 1(right), 0(no move)
void snake_move(int, int);
// out cells of the grid
void output(void);

char map[12][13] = {
  "************", // 初始状态
  "*XXXXH     *", // 直接打表
  "*          *",
  "*          *",
  "*          *",
  "*          *",
  "*          *",
  "*          *",
  "*          *",
  "*          *",
  "*          *",
  "************"
};

// define vars for snake
int snakeX[SNAKE_MAX_LENGTH] = {1, 2, 3, 4, 5}; // 蛇身和蛇头的坐标
int snakeY[SNAKE_MAX_LENGTH] = {1, 1, 1, 1, 1};
int snakeLength = 5;
int isGameEnd = 0;

void output() {
  // Clear the map & Put the snake
  for (int i = 1; i < 11; i++) {
    for (int j = 1; j < 11; j++) {
      map[i][j] = BLANK_CELL;
      for (int k = 0; k < snakeLength - 1; k++) {
        if (snakeX[k] == j && snakeY[k] == i) {
          map[i][j] = SNAKE_BODY;
          break;
        }
      }
      if (snakeX[snakeLength - 1] == j && snakeY[snakeLength - 1] == i) {
        map[i][j] = SNAKE_HEAD;
      }
    }
  }
  // Clear screen
  system("clear");
  // Output the map
  for (int i = 0; i < 12; i++) {
    printf("%s\n", map[i]);
  }
}

void snake_move(int dy, int dx) {
  // snake[x, y] = snake[x + 1, y + 1]
  for (int i = 0; i < 4; i++) {
    snakeX[i] = snakeX[i + 1];
    snakeY[i] = snakeY[i + 1];
  }
  // Detect the direction & move the snake
  if (dy == 0 && dx == -1) { // Go left
    snakeX[snakeLength - 1]--;
  } else if (dy == 0 && dx == 1) { // Go right
    snakeX[snakeLength - 1]++;
  } else if (dy == -1) { // Go up
    snakeY[snakeLength - 1]--;
  } else if (dy == 1) { // Go down
    snakeY[snakeLength - 1]++;
  }
}

int main() {
  output();
  while (!isGameEnd) {
    char ch;
    scanf("%s", &ch);
    switch (ch) {
      case 'A': 
        snake_move(0, -1); // Go left
        break;
      case 'D':
        snake_move(0, 1); // Go right
        break;
      case 'W':
        snake_move(-1, 0); // Go up
        break;
      case 'S':
        snake_move(1, 0); // Go down
    }
    output();
  }
  printf("Game Over!!!\n");
}
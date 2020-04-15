#include <stdio.h>

#define BOARD_SIZE 5
#define MAX_STEPS 20

int countNeighbors(int board[BOARD_SIZE][BOARD_SIZE],
		   int row,
		   int col) {

  int numNeighbors = 0;
  
  for (int row_offset = -1; row_offset <= 1; row_offset++) {
    for (int col_offset = -1; col_offset <= 1; col_offset++) {
      int i = row + row_offset;
      int j = col + col_offset;
      if ((i >= 0) && (i < BOARD_SIZE) &&
	  (j >= 0) && (j < BOARD_SIZE)) {
	if (board[i][j] == 1) {
	  numNeighbors += 1;
	}
      }
    }
  }

  numNeighbors = numNeighbors - board[row][col];
  return numNeighbors;
}

void copyBoardToBoard(int srcBoard[BOARD_SIZE][BOARD_SIZE],
		      int dstBoard[BOARD_SIZE][BOARD_SIZE]) {
  // for each row
  for (int i = 0; i < BOARD_SIZE; i++) {
    // for each column
    for (int j = 0; j < BOARD_SIZE; j++) {
      dstBoard[i][j] = srcBoard[i][j];
    }
  }
}

void changeBoard(int board[BOARD_SIZE][BOARD_SIZE]) {
  int oldBoard[BOARD_SIZE][BOARD_SIZE];
  copyBoardToBoard(board, oldBoard);
  // for each row
  for (int i = 0; i < BOARD_SIZE; i++) {
    // for each column
    for (int j = 0; j < BOARD_SIZE; j++) {
      int oldValue = oldBoard[i][j];
      int numNeighbors = countNeighbors(oldBoard, i, j);

      // Game of Life rules copied verbatim from:
      // https://blogs-images.forbes.com/startswithabang/files/2017/09/population-dynamics-in-conways-game-of-life-and-its-variants-9-728.jpg

      if ((oldValue == 1) && ((numNeighbors < 2) || (numNeighbors > 3))) {
	// 1. Living cells die if they have fewer than 2 neighbors
	//                     and
	// 2. Living cells die if they have more than 3 neighbors
	board[i][j] = 0;
      } else if ((oldValue == 0) && (numNeighbors == 3)) {
	// 3. Dead cells that have 3 neighbors become alive
	board[i][j] = 1;
      } else {
	// 4. Otherwise there is no change (whether cell is alive or dead)
	// do nothing!
	// #stayHome
      }
    }
  }  
}

void printBoard(int board[BOARD_SIZE][BOARD_SIZE]) {
  // for each row
  for (int i = 0; i < BOARD_SIZE; i++) {
    // for each column
    for (int j = 0; j < BOARD_SIZE; j++) {
      if (board[i][j] == 1) {
	printf("|*");
      } else {
	printf("| ");
      }
    }
    printf("|\n");
  }
  printf("\n");
}

void gameOfLife() {

  int board[BOARD_SIZE][BOARD_SIZE] = {{0, 1, 0, 0, 1},
				       {0, 0, 0, 0, 0},
				       {0, 1, 0, 1, 0},
				       {0, 0, 0, 1, 0},
				       {1, 0, 0, 0, 0}};

  printBoard(board);

  for (int i = 0; i < MAX_STEPS; i++) {
    changeBoard(board);
    printBoard(board);
  }
}

int main(int argc, char *argv[]) {  
  printf("Game of Life!\n\n");
  gameOfLife();
  return 0;
}

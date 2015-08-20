#define MIN_VAL 1
#define MAX_VAL 9
#define EMPTY 0
#define NUM_VALUES 9
#define GRID_SIZE 81
#define MAX_CELL 80

#define TRUE 1
#define FALSE 0

typedef int value;
typedef int cell;
typedef value sudokuGrid[GRID_SIZE];

int hasSolution(sudokuGrid game);
int isLegal(sudokuGrid game, cell location, value candidateDigit);
int isFull(sudokuGrid game);
void clearCell(sudokuGrid game, cell location);
void setCell(sudokuGrid game, cell location, value digit);
cell getEmptyCell(sudokuGrid game);
void printLines();
void showGame(sudokuGrid game);
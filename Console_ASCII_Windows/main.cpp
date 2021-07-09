#include <unordered_map>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <stack>

#define NOMINMAN
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

enum Wall {
  TOP = 0,
  RIGHT,
  BOTTOM,
  LEFT,
};

struct Cell {
  int row;
  int col;
  bool visited = false;
  bool walls[4] = { true, true, true, true };

  Cell(int x, int y)
  {
    col = x;
    row = y;
  }
};

const int HEIGHT = 15;
const int WIDTH = 20;

const std::unordered_map<std::string, std::string> WALLS = {
  { "0000", "   " },
  { "0001", "|  " },
  { "0010", " _ " },
  { "0011", "|_ " },
  { "0100", "  |" },
  { "0101", "| |" },
  { "0110", " _|" },
  { "0111", "|_|" },
  { "1000", " ‾ " },
  { "1001", "|‾ " },
  { "1010", " = " },
  { "1011", "|= " },
  { "1100", " ‾|" },
  { "1101", "|‾|" },
  { "1110", " =|" },
  { "1111", "|=|" }
};

std::vector<Cell> getMaze()
{
  std::vector<Cell> maze;
 
  for (int i = 0; i < HEIGHT; ++i) {
    for (int j = 0; j < WIDTH; ++j) {
      maze.push_back(Cell(i, j));
    }
  }

  return maze;
}

std::vector<Cell> maze = getMaze();

int get2Dindex(int x, int y);
std::string getWalls(Cell& cell);
std::vector<Cell> getNeighbours(Cell& cell);
void generateMaze();
void drawMaze();

int main(int argc, char* argv[])
{
  srand(time(NULL));
  SetConsoleOutputCP(CP_UTF8);

  generateMaze();
  drawMaze();

  system("pause");
  return 0;
}

int get2Dindex(int x, int y)
{
  return x + WIDTH * y;
}

std::string getWalls(Cell& cell)
{
  std::string cellWalls = "";
  
  for (const bool& b : cell.walls) {
    cellWalls += b ? "1" : "0";
  }

  return WALLS.at(cellWalls);
}

void drawMaze()
{
  for (int i = 0; i < HEIGHT; ++i) {
    for (int j = 0; j < WIDTH; ++j) {
      std::cout << getWalls(maze[get2Dindex(j, i)]);
    }

    std::cout << '\n';
  }
}


std::vector<Cell> getNeighbours(Cell& cell)
{
  std::vector<Cell> neighbours;

  if (cell.row - 1 >= 0 && cell.row - 1 < WIDTH && !maze[get2Dindex(cell.row - 1, cell.col)].visited) 
    neighbours.push_back(maze[get2Dindex(cell.row - 1, cell.col)]);
  if (cell.row + 1 >= 0 && cell.row + 1 < WIDTH && !maze[get2Dindex(cell.row + 1, cell.col)].visited) 
    neighbours.push_back(maze[get2Dindex(cell.row + 1, cell.col)]);
  
  if (cell.col - 1 >= 0 && cell.col - 1 < HEIGHT && !maze[get2Dindex(cell.row, cell.col - 1)].visited) 
    neighbours.push_back(maze[get2Dindex(cell.row, cell.col - 1)]);
  if (cell.col + 1 >= 0 && cell.col + 1 < HEIGHT && !maze[get2Dindex(cell.row, cell.col + 1)].visited) 
    neighbours.push_back(maze[get2Dindex(cell.row, cell.col + 1)]);

  return neighbours;
}

void generateMaze()
{
  std::stack<Cell> stack;

  Cell initial = maze[get2Dindex(0, 0)];
  maze[get2Dindex(initial.row, initial.col)].visited = true;
  stack.push(initial);

  while (!stack.empty()) {
    Cell currentCell = stack.top();
    stack.pop();

    std::vector<Cell> neighbours = getNeighbours(currentCell);

    if (neighbours.size() > 0) {
      stack.push(currentCell);
      Cell randomNeighbour = neighbours[rand() % neighbours.size()];
      
      int diffRow = currentCell.row - randomNeighbour.row;
      int diffCol = currentCell.col - randomNeighbour.col;

      if (diffRow == 1) {
        maze[get2Dindex(currentCell.row, currentCell.col)].walls[LEFT] = false;
        maze[get2Dindex(randomNeighbour.row, randomNeighbour.col)].walls[RIGHT] = false;
      } else if (diffRow == -1) {
        maze[get2Dindex(currentCell.row, currentCell.col)].walls[RIGHT] = false;
        maze[get2Dindex(randomNeighbour.row, randomNeighbour.col)].walls[LEFT] = false;
      }

      if (diffCol == 1) {
        maze[get2Dindex(currentCell.row, currentCell.col)].walls[TOP] = false;
        maze[get2Dindex(randomNeighbour.row, randomNeighbour.col)].walls[BOTTOM] = false;
      } else if (diffCol == -1) {
        maze[get2Dindex(currentCell.row, currentCell.col)].walls[BOTTOM] = false;
        maze[get2Dindex(randomNeighbour.row, randomNeighbour.col)].walls[TOP] = false;
      }

      maze[get2Dindex(randomNeighbour.row, randomNeighbour.col)].visited = true;
      stack.push(randomNeighbour);
    }
  }
}

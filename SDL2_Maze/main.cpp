#include <iostream>
#include <cstdlib>
#include <vector>
#include <memory>
#include <ctime>
#include <stack>

#include "src/Window.h"
#include "src/Line.h"

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

  Cell(int x, int y) : col(x), row(y) {}
};

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int CELL_SIZE = 20;

const int MAZE_HEIGHT = WINDOW_HEIGHT / CELL_SIZE;
const int MAZE_WIDTH = WINDOW_WIDTH / CELL_SIZE;

std::vector<Cell> getMaze()
{
  std::vector<Cell> maze;

  for (int i = 0; i < MAZE_HEIGHT; ++i) {
    for (int j = 0; j < MAZE_WIDTH; ++j) {
      maze.push_back(Cell(i, j));
    }
  }

  return maze;
}

inline int get2Dindex(int x, int y) { return x + MAZE_WIDTH * y; }
std::vector<Cell> getNeighbours(const Cell& cell);
void generateMaze();
void getMazeLines();

std::vector<Cell> maze = getMaze();
Window window("SDL -- Maze Generator", 800, 600);
std::vector<std::unique_ptr<Line>> lines;

int main(int argc, char* argv[])
{
  srand(time(NULL));
 
  generateMaze();
  getMazeLines();

  while (window.isOpen()) {
    for (const auto& line : lines) {
      line->draw();
    }

    window.getEvents();
    window.render();
  }

  lines.clear();
  maze.clear();

  return 0;
}

void getMazeLines()
{
  for (int i = 0; i < MAZE_HEIGHT; ++i) {
    for (int j = 0; j < MAZE_WIDTH; ++j) {
      Cell cell = maze[get2Dindex(j, i)];

      int x = cell.row * CELL_SIZE;
      int y = cell.col * CELL_SIZE;

      if (cell.walls[TOP]) {
        lines.push_back(std::make_unique<Line>(
          window,
          x, y,
          x + CELL_SIZE, y)
        );
      }

      if (cell.walls[RIGHT]) {
        lines.push_back(std::make_unique<Line>(
          window,
          x + CELL_SIZE, y,
          x + CELL_SIZE, y + CELL_SIZE)
        );
      }

      if (cell.walls[BOTTOM]) {
        lines.push_back(std::make_unique<Line>(
          window,
          x, y + CELL_SIZE,
          x + CELL_SIZE, y + CELL_SIZE)
        );
      }

      if (cell.walls[LEFT]) {
        lines.push_back(std::make_unique<Line>(
          window,
          x, y,
          x, y + CELL_SIZE)
        );
      }
    }
  }
}

std::vector<Cell> getNeighbours(const Cell& cell)
{
  std::vector<Cell> neighbours;

  if (cell.row - 1 >= 0 && cell.row - 1 < MAZE_WIDTH && !maze[get2Dindex(cell.row - 1, cell.col)].visited)
    neighbours.push_back(maze[get2Dindex(cell.row - 1, cell.col)]);
  if (cell.row + 1 >= 0 && cell.row + 1 < MAZE_WIDTH && !maze[get2Dindex(cell.row + 1, cell.col)].visited)
    neighbours.push_back(maze[get2Dindex(cell.row + 1, cell.col)]);

  if (cell.col - 1 >= 0 && cell.col - 1 < MAZE_HEIGHT && !maze[get2Dindex(cell.row, cell.col - 1)].visited)
    neighbours.push_back(maze[get2Dindex(cell.row, cell.col - 1)]);
  if (cell.col + 1 >= 0 && cell.col + 1 < MAZE_HEIGHT && !maze[get2Dindex(cell.row, cell.col + 1)].visited)
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
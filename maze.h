#ifndef MAZE_H
#define MAZE_H

struct Cell
{
  int row;
  int col;
  char caracter = '$';
  bool visited = false;
  bool wall = false;
  bool fixed = false;

  public:
    void setCell(const int i, const int j)
    {
      this->row = i;
      this->col = j;
    }
};


class Maze
{
    public:
        //Construtor da classe
        Maze(const int, const int);
        //Destrutor
        ~Maze();

        void path();
        void waySolve();
        void show();
        void doors(const int);

        int index(const int, const int);

        Cell* checkNeighbors(Cell&);
        Cell* checkSolveNeighbors(Cell&);


    protected:
        int rows;
        int cols;

        int indx;
        int contNeighBors = 0;
        int push = 0;
        int pop = 0;

        bool isWall = false;

        Cell *current;
        Cell *next;
        Cell **stack;
        Cell **neighbors;
        Cell **grid;

};

/*
class SolverMaze : protected Maze
{
    public:
        SolverMaze()
        {
            std::cout << " oi";
        };
        //~SolverMaze();

        void a();

    protected:




};
*/


#endif // MAZE_H

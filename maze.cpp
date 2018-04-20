#include <iostream>
#include <ctime>
#include <cstdlib>

#include "maze.h"

//Construtor da classe
Maze::Maze(const int l, const int c)
{

    this->grid = new Cell* [l];
    this->neighbors = new Cell* [4];
    this->stack = new Cell* [l * c];

    this->rows = l;
    this->cols = c;

  for(int i = 0; i < l; ++i)
  {
    this->grid[i] = new Cell [c];

    for(int j = 0; j < c; ++j)
    {
      this->grid[i][j].setCell(i, j);
    }
  }
  srand(time(NULL));

}

Maze::~Maze()
{

  for(int i = 0; i < rows; ++i)
  {
    delete [] grid[i];
    //std::cout << i << std::endl;
  }

    delete [] this->grid;
    delete [] this->neighbors;
    delete [] this->stack;


    //grid = NULL;
    //neighbors = NULL;
    //stack == NULL;
}


void Maze::path()
{
    int door = rand()%rows;
    current = &grid[door][0];
    stack[push] = &(*current);

  do
  {
    current->visited = true;
    next = this->checkNeighbors(*current);

    if(next != NULL)
    {
      ++push;
      //++retro;
      pop = push;

      //current->caracter = '#';

      next->visited = true;

      //Torna a proxima celula a atual
      current = next;

      //Adiciona a celula autal a pilha de visitados
      stack[push] = current;


    }
    else if(push > 0 && contNeighBors > 0)
    {

      //std::cout << "é verdadeira" << std::endl;

      current->caracter = '#';
      current->wall = true;
      current->fixed = true;
      current->visited = true;

      //Apaga a celula atual visitada
      stack[push] = NULL;

      --push;
      --pop;


      //Retorna uma celula da pilha
      current = stack[pop];

    }
    //Caso a célula não tiver nenhum caminho posterior e não for uma parede
    //Retorna a célula anterior da pilha
    else if(push > 0 && !current->wall)
    {
      current->caracter = '.';
      current->visited = true;
      current->fixed = true;

      //Apaga a celula atual visitada
      stack[push] = NULL;


      --push;
      --pop;

      //Torna a cécula atual a penúltima da pilha
      current = stack[pop];
    }

  } while(push > 0);

  this->doors(door);

}


void Maze::doors(const int port)
{
    int psdRand;
    grid[port][0].caracter = 'E';

    //Decide se existe saída
    if(rand()%2) { return; }

    do
    {

        psdRand = rand()%rows;
        if(!grid[psdRand][cols - 1].wall)
        {
            grid[psdRand][cols - 1].caracter = 'S';
            return;
        }
    } while(true);
}

Cell* Maze::checkNeighbors(Cell& actualCell)
{
  contNeighBors = 0;
  int indx;
  int retro = push;
  int cellPositionX;
  int cellPositionY;


  if(push > 0) { --retro; }

  for(int k = -1; k < 2; ++k)
  {
    for(int y = -1; y < 2; ++y)
    {
        cellPositionX = actualCell.row + k;
        cellPositionY = actualCell.col + y;

      indx = this->index(cellPositionX, cellPositionY);

      if(indx >= 0 && (k != y && k != -y))
      {

        if(!grid[cellPositionX][cellPositionY].visited)
        {

          neighbors[contNeighBors] = &grid[cellPositionX][cellPositionY];
          ++contNeighBors;

        }
        else if(&grid[cellPositionX][cellPositionY] != &(*stack[retro]) && !grid[cellPositionX][cellPositionY].fixed)
        {
            ++contNeighBors;
            return NULL;
        }
      }
    }
  }

  //std::cout << contNeighBors << " :contNeighBors" << std::endl;

  if(contNeighBors > 0)
  {
    //std::cout << contNeighBors << std::endl;
    //Retorna o proximo visinho caso houver
    return neighbors[rand()%contNeighBors];
  }
  else
  {
    return NULL;
  }

}



int Maze::index(const int i, const int j)
{
  if(i < 0 || j < 0 || i > rows - 1 || j > cols - 1)
  {
    return -1;
  }
  else
  {
    return (i * cols + j);
  }
}

void Maze::show()
{
    for(int i = 0; i < rows; ++i)
    {
        for(int j = 0; j < cols; ++j)
        {
            std::cout << grid[i][j].caracter << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    return;
}
















void Maze::waySolve()
{
    for(int i = 0; i < rows; ++i)
    {
        for(int j = 0; j < cols; ++j)
        {
            grid[i][j].visited = false;
        }
    }

    //std::cout << current->caracter <<  '\t' << stack[push]->caracter << std::endl;
  do
  {
    //std::cout << stack[push]->row << '\t' << stack[push]->col << std::endl;
    current->visited = true;
    next = this->checkSolveNeighbors(*current);


    if(next != NULL)
    {
      ++push;
      //++retro;
      pop = push;

      //Indica o trajeto correto
      if(push > 1) { current->caracter = '>'; }

      next->visited = true;

      //Torna a proxima celula a atual
      current = next;

      //Adiciona a celula autal a pilha de visitados
      stack[push] = current;


    }

    //Caso a célula não tiver nenhum caminho posterior e não for uma parede
    //Retorna a célula anterior da pilha
    else if(push > 0)
    {

      //Sinaliza o caminho sem saida
      current->caracter = '.';

      current->visited = true;
      //current->fixed = true;

      //Apaga a celula atual visitada
      stack[push] = NULL;


      --push;
      --pop;

      //Torna a cécula atual a penúltima da pilha
      current = stack[pop];
      //return;
    }

    if(current->caracter == 'S') { std::cout << "Saida Encontrada!" << std::endl ; return; }

  } while(push > 0);

    if(push == 0) { std::cout << "Saida não Encontrada!" << std::endl; }

    return;

}


Cell* Maze::checkSolveNeighbors(Cell& actualCell)
{
  contNeighBors = 0;
  int indx;
  int retro = push;
  int cellPositionX;
  int cellPositionY;


  if(push > 0) { --retro; }

  for(int k = -1; k < 2; ++k)
  {
    for(int y = -1; y < 2; ++y)
    {
        cellPositionX = actualCell.row + k;
        cellPositionY = actualCell.col + y;

      indx = this->index(cellPositionX, cellPositionY);

      if(indx >= 0 && (k != y && k != -y))
      {

        if(!grid[cellPositionX][cellPositionY].visited && !grid[cellPositionX][cellPositionY].wall)
        {

          neighbors[contNeighBors] = &grid[cellPositionX][cellPositionY];
          ++contNeighBors;

        }
      }
    }
  }

  if(contNeighBors > 0)
  {
    //std::cout << contNeighBors << std::endl;
    //Retorna o proximo visinho caso houver
    return neighbors[rand()%contNeighBors];
  }
  else
  {
    return NULL;
  }

}

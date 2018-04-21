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

      current->caracter = '*';
      next->caracter = '+';

      //next->visited = true;

      //Adiciona a celula autal a pilha de visitados
        stack[push] = current;

      //Torna a proxima celula a atual
      current = next;

      ++push;

      //++retro;
      //pop = push;


    }

    //Caso a célula nao tiver nenhum caminho posterior e não for uma parede
    //Retorna a célula anterior da pilha
    else
    {
          if(!current->wall) { current->caracter = '.'; }
          //current->visited = true;
          current->fixed = true;


        --push;
        //Torna a ultima cécula visitada na atual
        current = stack[push];

        //Apaga a ultima celula visitada
        //stack[push] = NULL;


    }
    //std::cout << push << std::endl;
    //std::cout << push << '\t' << contNeighBors << '\t' << stack[push]->fixed << std::endl;

    //this->show();

  } while(!stack[0]->fixed);

  this->doors(door);

}


void Maze::doors(const int port)
{
    int psdRand = rand()%9 ;
    grid[port][0].caracter = 'E';
    std::cout << psdRand << std::endl;
    //Decide se existe saída
    if(!psdRand) { return; }

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
  int retro = push > 0 ? (push - 1) : 0;
  int cellPositionX;
  int cellPositionY;

  //if(push > 0) { --retro; }

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
        //*
        else if((push - 1) > 0)
        {
            if(&grid[cellPositionX][cellPositionY] != &(*stack[push - 1]) && !grid[cellPositionX][cellPositionY].fixed)
            {
                //std::cout << cellPositionX << '\t' << cellPositionY << std::endl;
                //std::cout << "por algum motivo ele entrou aqu" << '\t' << push << std::endl;
                //std::cout<< &(*stack[push]) << std::endl;
                //std::cout << &grid[cellPositionX][cellPositionY] << '\t' << &(*stack[push - 1]) << std::endl;

                actualCell.caracter = '#';
                actualCell.wall = true;
                actualCell.fixed = true;

                return NULL;


            }
        }
        //*/
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
            grid[i][j].fixed = false;
        }
    }

    //std::cout << current->caracter <<  '\t' << stack[push]->caracter << std::endl;
    //stack[0] = &grid[0][0];

    current = stack[0];
    push = 0;
    //std::cout << current->row << '\t' << current->col << std::endl;
  do
  {
    current->visited = true;
    next = this->checkSolveNeighbors(*current);


    if(next != NULL)
    {

      //Indica o trajeto correto
        //std::cout << current->caracter << std::endl;
        if(push > 0) { current->caracter = '>'; }
        if(next->caracter == 'S') { std::cout << "Saida Encontrada!" << std::endl ; return; }

      //next->visited = true;

      //Adiciona a celula autal a pilha de visitados
      stack[push] = current;

      //Torna a proxima celula a atual
      current = next;

      ++push;

    }

    //Caso a célula nao tiver nenhum caminho posterior e nao for uma parede
    //Retorna a célula anterior da pilha
    else
    {

      //Sinaliza o caminho sem saida
      current->caracter = '.';
      current->fixed = true;

      //current->visited = true;
      //current->fixed = true;

      //Apaga a celula atual visitada
      //stack[push] = NULL;


      --push;

      //Torna a cécula atual a penúltima da pilha
      current = stack[push];

    }


  } while(!stack[0]->fixed);

    if(push < 0) { std::cout << "Saida nao Encontrada!" << std::endl; }

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

        if(!grid[cellPositionX][cellPositionY].visited && !grid[cellPositionX][cellPositionY].wall )
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

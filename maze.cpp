#include <iostream>
#include <ctime>
#include <cstdlib>

#include "maze.h"

//Construtor da classe
Maze::Maze(const int l, const int c)
{
    rows = (l * 2) - 1;
    cols = (c * 2) - 1;

    grid = new Cell* [rows];
    neighbors = new Cell* [4];
    stack = new Cell* [l * c];


    for(int i = 0; i < rows; ++i)
    {
        grid[i] = new Cell [cols];

        for(int j = 0; j < cols; ++j)
        {
          grid[i][j].setCell(i, j);
        }
    }

    srand(time(NULL));
}

Maze::~Maze()
{
    for(int i = 0; i < rows; ++i)
    {
        delete [] grid[i];
    }

    delete [] grid;
    delete [] neighbors;
    delete [] stack;

}


void Maze::path()
{

    int dirX = 0;
    int dirY = 0;

    int randDoor = rand()%((rows + 1) / 2 - 1);
    int door = randDoor == 0 ? 0 : (randDoor + 2);

    current = &grid[door][0];

    stack[push] = &(*current);

    do
    {
        current->caracter = '.';
        current->visited = true;
        current->wall = false;

        next = this->checkNeighbors(*current);


        if(next != NULL)
        {


            current->caracter = '.';
            next->caracter = '+';

            //*
            dirX = next->row - current->row;
            dirY = next->col - current->col;

            if(dirX > 0) { --dirX; dirX = current->row + dirX; }
            else if (dirX < 0) { ++dirX; dirX = current->row + dirX;}
            else { dirX = current->row; }

            if(dirY > 0) { --dirY; dirY = current->col + dirY; }
            else if(dirY < 0) { ++dirY; dirY = current->col + dirY; }
            else { dirY = current->col; }

            grid[dirX][dirY].caracter = current->caracter;
            grid[dirX][dirY].wall = false;

            //*/

            //Adiciona a celula autal a pilha de visitados
            stack[push] = current;

            //Torna a proxima celula a atual
            current = next;

            ++push;

        }

        //Caso a célula nao tiver nenhum caminho posterior e não for uma parede
        //Retorna a célula anterior da pilha
        else
        {
            //current->caracter = '.';

            current->fixed = true;

            --push;

            //Torna a ultima cécula visitada na atual
            current = stack[push];

        }

        //system("cls");
        //this->show();

      } while(!stack[0]->fixed);

      this->doors(door);

}


Cell* Maze::checkNeighbors(Cell& actualCell)
{
    contNeighBors = 0;
    int indx;
    int cellPositionX;
    int cellPositionY;

    //int contWall = 0;

    for(int k = -2; k < 4; k += 2)
    {

        for(int y = -2; y < 4; y += 2)
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


void Maze::doors(const int port)
{
    int randDoor = rand()%9 ;

    grid[port][0].caracter = 'E';


    //Decide se existe saída
    if(!randDoor) { return; }

    do
    {

        randDoor = rand()%((rows + 1) / 2 - 1);
        randDoor = randDoor == 0 ? 0 : (randDoor + 2);
        //psdRand = rand()%rows;

        if(!grid[randDoor][cols - 1].wall)
        {
            grid[randDoor][cols - 1].caracter = 'S';
            return;

        }

    } while(true);
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


    current = stack[0];
    push = 0;

    do
    {
        current->visited = true;
        next = this->checkSolveNeighbors(*current);


        if(next != NULL)
        {

            //Indica o trajeto correto
            if(push > 0) { current->caracter = 254; }

            if(next->caracter == 'S') { std::cout << "Saida Encontrada!" << std::endl ; return; }

            next->caracter = '+';

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
              current->caracter = 178;
              current->fixed = true;

              --push;

              //Torna a cécula atual a penúltima da pilha
              current = stack[push];

        }

        //system("cls");

        //this->show();


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

        //Retorna o proximo visinho caso houver
        return neighbors[rand()%contNeighBors];
    }
    else
    {
        return NULL;
    }

}

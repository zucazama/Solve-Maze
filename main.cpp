#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>

#include "maze.h"

void start(const int line, const int column)
{
    Maze maze(line, column);
    maze.path();
    maze.show();
    maze.waySolve();
    maze.show();
}

int main() {

  int line;
  int column;
  char caracter;


    do
    {
        std::cout << "I - Criar e Resolver Labirinto\tE - Sair" << std::endl;
        std::cin >> caracter;
        caracter = toupper(caracter);

        switch(caracter)
        {
            case 'I':
                system("cls");

                std::cin >> line;
                std::cin >> column;

                start(line, column);
                break;
            case 'E':
                break;

            default:
                std::cout << "Opção Inválida" << std::endl;
                break;
        }
    } while(caracter != 'S');

  //maze.~Maze();


  return 0;
}

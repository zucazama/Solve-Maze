#include <iostream>
#include <string>

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
        std::cout << "I - Criar e resolver labirinto automaticamente\tE - Sair" << std::endl;
        std::cin >> caracter;
        caracter = toupper(caracter);

        switch(caracter)
        {
            case 'I':
                system("cls");

                std::cout << "Informe o numero de linhas e colunas respectivamente:" << std::endl;
                std::cin >> line;
                std::cin >> column;

                start(line, column);
                break;
            case 'E':
                break;

            default:
                std::cout << "Opçao Invalida! Tente novamente" << std::endl;
                break;
        }
    } while(caracter != 'E');

  //maze.~Maze();


  return 0;
}

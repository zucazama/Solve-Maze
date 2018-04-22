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
	//maze.~Maze();
}

int main() {

	int line;
	int column;
	char caracter;


	do
	{
		std::cout << "I - CRIAR E RESOLVER O LABIRINTO AUTOMATICAMENTE\tE - SAIR" << std::endl;
		std::cin >> caracter;
		caracter = toupper(caracter);

		switch(caracter)
		{
			case 'I':
				system("cls");

				std::cout << "INFORME O NUMERO DE LINHAS E COLUNAS RESPECTIVAMENTE:" << std::endl;
				std::cin >> line;
				std::cin >> column;

				start(line, column);
				break;
			case 'E':
				break;

			default:
				std::cout << "OPCAO INVALIDA! TENTE NOVAMENTE" << std::endl;
				break;
		}
	} while(caracter != 'E');

	//maze.~Maze();


	return 0;
}

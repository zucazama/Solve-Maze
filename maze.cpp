#include <iostream>
#include <ctime>
#include <cstdlib>

#include "maze.h"

//Construtor da classe
Maze::Maze(const int l, const int c)
{
   //int addRows = l % 2 == 0 ? 2 : 1;
   //int addCols = c % 2 == 0? 2 : 1;

   rows = (l * 2) + 1;
   cols = (c * 2) + 1;

   grid = new Cell* [rows];
   neighbors = new Cell* [4];
   stack = new Cell* [rows * cols];
   stringMaze = new char [rows * ( 2 * cols) + 1];


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

	//std::cout << "Destuiu objeto" << std::endl;
	for(int i = 0; i < rows; ++i)
	{
		delete [] grid[i];
	}

	delete [] grid;
	delete [] neighbors;
	delete [] stack;
	delete [] stringMaze;


	grid = NULL;
	neighbors = NULL;
	stack = NULL;

}


void Maze::path()
{

	int dirX = 0;
	int dirY = 0;

	int randDoor = rand()%((rows + 1) / 2 - 1) + 1;
	int door = (randDoor %2  == 0) ? (randDoor + 1) : ((randDoor == 1) ? 1 :(randDoor + 2));

	current = &grid[door][1];

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


			//Sentido do movimento de deslocamento da celula atual à proxima

			dirX = next->row - current->row;
			dirY = next->col - current->col;

			if(dirX > 0) { --dirX; dirX = current->row + dirX; }
			else if (dirX < 0) { ++dirX; dirX = current->row + dirX;}
			else { dirX = current->row; }

			if(dirY > 0) { --dirY; dirY = current->col + dirY; }
			else if(dirY < 0) { ++dirY; dirY = current->col + dirY; }
			else { dirY = current->col; }

			//Retira a parende entre a celula atual e a subsequente
			grid[dirX][dirY].caracter = current->caracter;
			grid[dirX][dirY].wall = false;


			//Adiciona a célula atual a pilha de visitados
			//Faz o pos-incremento de 'push'
			stack[push++] = current;

			//Torna a próxima célula a atual
			current = next;

	}

		//Caso a célula não tiver nenhum caminho posterior e não for uma parede
		//Retorna a célula anterior da pilha
		else
		{
				//current->caracter = '.';

				current->fixed = true;


				//Torna a ultima célula visitada na atual
				current = stack[--push];

		}

		//Exibi a criação do labirinto passo a passo
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
				current->caracter = 254;

				if(next->caracter == 'S')
				{
					std::cout << "SAIDA ENCONTRADA!" << std::endl;
					return;
				}

				next->caracter = '+';

				//Adiciona a célula atual a pilha de visitados
				stack[push] = current;

				//Torna a proxima célula a atual
				current = next;

				++push;

			}

		//Caso a célula nao tiver nenhum caminho posterior e nao for uma parede
		//Retorna a célula anterior da pilha
		else
		{
		//Sinaliza o caminho sem saída
		current->caracter = 178;
		current->fixed = true;


		//Torna a penúltima célula da pilha a atual
		current = stack[--push];

		}

		//Exibe a criação do trajeto passo a passo
		//system("cls");
		//this->show();


	} while(!stack[0]->fixed);


	if(push < 0) { std::cout << "SAIDA NAO ENCONTRADA!" << std::endl; }


	return;

}

/*
 * Busca os vizinhos da célula atual na resolução do labirinto.
 *
 */

Cell* Maze::checkSolveNeighbors(Cell& actualCell)
{
	int cellPositionX;
	int cellPositionY;

	int indx;
	int pop = push;

	contNeighBors = 0;


	if(push > 0) { --pop; }

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
					//Caso uma das células que circuda a posição atual seja a sáida marcada será imediatamente a escolhida
					//Evita que ocorra a escolha de um caminho qualquer sem saída tento assim que retorna a posição preliminar
					if(grid[cellPositionX][cellPositionY].caracter == 'S')
					{
						return &grid[cellPositionX][cellPositionY];
					}

					neighbors[contNeighBors] = &grid[cellPositionX][cellPositionY];
					++contNeighBors;

				}
			}
		}
	}

	if(contNeighBors > 0)
	{

		//Retorna o próximo visinho caso houver
		return neighbors[rand()%contNeighBors];

	}
	else
	{
		return NULL;
	}
}




int Maze::index(const int i, const int j)
{
	if(i < 0 || j < 0 || i > rows - 1 || j > cols - 1){ return -1; }
	else { return 1; }
}

void Maze::show()
{
	int k = 0;

	for(int i = 0; i < rows; ++i)
	{
		for(int j = 0; j < cols; ++j)
		{
			stringMaze[k] = grid[i][j].caracter;
			stringMaze[++k] = ' ';
			++k;

			//std::cout << grid[i][j].caracter << ' ';
		}

		stringMaze[--k] = '\n';
		++k;
		//std::cout << std::endl;
	}

	stringMaze[k] = '\0';
	//std::cout << std::endl;

	std::cout << stringMaze;

	return;
}


void Maze::doors(const int port)
{
	int randDoor = rand()%9 ;

	grid[port][0].caracter = 'E';
	//grid[port][0].wall = false;
	//grid[port][0].visited = true;



	//Decide se existe saída
	if(!randDoor) { return; }

	do
	{
		//Gera uma porta qualquer na ultima coluna valida
		randDoor = rand()%((rows + 1) / 2 - 1);
		randDoor = randDoor == 0 ? 0 : (randDoor + 2);

		//Verifica se na posicao sorteada não é uma parede
		if(!grid[randDoor][cols - 2].wall)
		{
			grid[randDoor][cols - 1].caracter = 'S';
			grid[randDoor][cols - 1].wall = false;
			return;

		}

	} while(true);
}

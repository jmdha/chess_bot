#include "./Headers/zobrist.h"
#include <stdlib.h>
#include <math.h>
#include <random>
#include <limits>

Zobrist::Zobrist(Board* board)
{
	this->board = board;
	/*
	std::mt19937 gen(0);
	std::uniform_int_distribution<unsigned long int> distribution(0, ULONG_MAX);
	for (int y = 0; y < HEIGHT; y++)
	{
		printf("{");
		for (int x = 0; x < WIDTH; x++)
		{
			printf("{");
			for (int i = 0; i < 6; i++)
			{
				printf("{");
				for (int j = 0; j < 2; j++)
				{
					this->valueBoard[x][y][i][j] = distribution(gen);
					printf("%lu", this->valueBoard[x][y][i][j]);
					if (j == 0)
						printf(", ");
				}
				printf("}");
				if (i != 6 - 1)
					printf(",");
			}
			printf("}");
			if (x != 8 - 1)
				printf(",");
		}
		printf("}");
		if (y != 8 - 1)
			printf(",");
	}
	*/
}

unsigned long int Zobrist::getHash()
{
	return this->currentHash;
}

void Zobrist::flipSquare(int x, int y, int index, int color)
{
	unsigned long int value = ZOBRISTVALUEBOARD[x][y][index][color];
	this->currentHash = this->currentHash ^ value;
}

void Zobrist::initializeHash()
{
	this->currentHash = 0;
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			for (int i = 0; i < 6; i++)
			{
				for (int j = 0; j < 2; j++)
				{
					flipSquare(x, y, this->board->getPiece(x, y)->getIndex(), j);
				}
			}
		}
	}
}

void Zobrist::incrementCurrentHash()
{
	if (this->priorInstanceCount.find(this->getHash()) == this->priorInstanceCount.end())
		this->priorInstanceCount.emplace(this->getHash(), 1);
	else
		this->priorInstanceCount.at(this->getHash()) += 1;
}

void Zobrist::decrementCurrentHash()
{
	//if (this->priorInstanceCount.find(this->getHash()) != this->priorInstanceCount.end())
	//{
	this->priorInstanceCount.at(this->getHash()) -= 1;
	if (this->priorInstanceCount.at(this->getHash()) == 0)
		this->priorInstanceCount.erase(this->getHash());
	//}
}
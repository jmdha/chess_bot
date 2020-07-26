#include "./Headers/zobrist.h"
#include <stdlib.h>
#include <math.h>
#include <random>
#include <limits>

Zobrist::Zobrist(Board *board)
{
    this->board = board;
    std::mt19937 gen(0);
    std::uniform_int_distribution<unsigned long int> distribution(0, ULONG_MAX);
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            for (int i = 0; i < 6; i++)
            {
                for (int j = 0; j < 2; j++)
                {
                    this->valueBoard[x][y][i][j] = distribution(gen);
                }
            }
        }
    }
}

unsigned long int Zobrist::getHash()
{
    return this->currentHash;
}

void Zobrist::flipSquare(int x, int y, int index, int color)
{
    unsigned long int value = this->valueBoard[x][y][index][color];
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
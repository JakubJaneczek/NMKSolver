#include <iostream>
#include "Board.h"

int main()
{
    int sizeX, sizeY, inRow;
    char currentPlayer;
    char command[100] = {};

    while (std::cin.good())
    {
        std::cin >> command;
        std::cin >> sizeY;
        std::cin >> sizeX;
        std::cin >> inRow;
        std::cin >> currentPlayer;
        Board a(sizeX, sizeY, inRow, currentPlayer);
        for (int i = 0; i < sizeY; i++)
        {
            for (int j = 0; j < sizeX; j++)
            {
                std::cin >> a.board[i][j];
            }
        }
        if (strcmp(command, "GEN_ALL_POS_MOV") == 0)
        {
            a.GenerateAllMoves();
        }
        else if (strcmp(command, "GEN_ALL_POS_MOV_CUT_IF_GAME_OVER") == 0)
        {
            a.GenerateAllMovesAndEndIfNecessary();
        }
        else if (strcmp(command, "SOLVE_GAME_STATE") == 0)
        {
            a.SolveGame();
        }

    }
}
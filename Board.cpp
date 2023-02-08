
#include "Board.h"
#include <iostream>
#include <algorithm>
#define PLAYER1 '1'
#define PLAYER2 '2'


Board::Board(int x, int y, int inRow, char currentPlayer)
{
	this->sizeX = x;
	this->sizeY = y;
	this->boardSize = x * y;
	this->inRow = inRow;
	this->currentPlayer = currentPlayer;
	board = new char* [y];
	for (int i = 0; i < y; i++)
	{
		board[i] = new char[x];
	}
}

Board::~Board()
{
	for (int i = 0; i < sizeY; i++)
	{
		delete[] board[i];
	}
	delete[] board;
	board = nullptr;
}

int Board::CheckWin() const
{
	for (int i = 0; i < sizeY; i++)
	{
		for (int j = 0; j < sizeX; j++)
		{	
			//VAERTICAL AND DIAGONALS
			if (i < sizeY - inRow + 1)
			{
				if (board[i][j] != '0')
				{
					//VERTICAL
					for (int k = 1; k < inRow; k++)
					{
						if (board[i + k][j] != board[i][j])
						{
							break;
						}
						if (k == inRow - 1)
							return  Winner(i, j);
					}
					//LEFT DIAGONAL

					if (j >= inRow - 1)
					{
						for (int k = 1; k < inRow; k++)
						{
							if (board[i + k][j - k] != board[i][j])
							{
								break;
							}
							if (k == inRow - 1)
								return  Winner(i, j);
						}
					}

					//RIGHT DIAGONAL 

					if (j < sizeX - inRow + 1)
					{
						for (int k = 1; k < inRow; k++)
						{
							if (board[i + k][j + k] != board[i][j])
							{
								break;
							}
							if (k == inRow - 1)
								return  Winner(i, j);
						}
					}
				}
			}
			//if (i < sizeY - inRow)
			//{
			//	if(board[i][j] == '0')
			//	{
			//		//VERTICAL
			//		if (board[i + 1][j] != '0')
			//		{
			//			for (int k = 1; k < inRow; k++)
			//			{
			//				if (board[i + k][j] != board[i + 1][j])
			//				{
			//					break;
			//				}
			//				if (k == inRow - 1)
			//					if(board[i+inRow][j] == '0')
			//						return  Winner(i + 1, j);
			//			}
			//		}
			//	}
			//}

			if (j < sizeX - inRow + 1)
			{
				if (board[i][j] != '0')
				{
					for (int k = 1; k < inRow; k++)
					{
						if (board[i][j + k] != board[i][j])
						{
							break;
						}
						if (k == inRow - 1)
							return  Winner(i, j);
					}
				}
			}
		}
	}
	return 0;
}

int Board::Winner(int i, int j) const
{
	int value = 0;
	if (board[i][j] == PLAYER1)
	{

		value = 10;
	}
	else if (board[i][j] == PLAYER2)
	{

		value = -10;
	}

	return value;
}

int Board::CountMoves()
{
	movesPossible = 0;
	for (int i = 0; i < sizeY; i++)
	{
		for (int j = 0; j < sizeX; j++)
		{
			if (board[i][j] == '0')
			{
				movesPossible++;
			}
		}
	}
	return movesPossible;
}

void Board::GenerateAllMoves()
{
	if (CheckWin())
	{
		std::cout << "0\n";
	}
	else
	{
		CountMoves();
		std::cout << movesPossible << "\n";
		for (int i = 0; i < sizeY; i++)
		{
			for (int j = 0; j < sizeX; j++)
			{
				if (board[i][j] == '0')
				{
					board[i][j] = currentPlayer;
					Print();
					board[i][j] = '0';
				}
			}
		}
	}
}

void Board::Print() const
{
	for (int i = 0; i < sizeY; i++)
	{
		for (int j = 0; j < sizeX; j++)
		{
			std::cout << board[i][j] << " ";
		}
		std::cout << "\n";
	}
}

void Board::GenerateAllMovesAndEndIfNecessary()
{
	if (CheckWin())
	{
		std::cout << "0\n";
	}
	else
	{
		for (int i = 0; i < sizeY; i++)
		{
			for (int j = 0; j < sizeX; j++)
			{
				if (board[i][j] == '0')
				{
					board[i][j] = currentPlayer;
					if (CheckWin() != 0)
					{
						std::cout << "1\n";
						Print();
						return;
					}
					board[i][j] = '0';
				}
			}
		}
		GenerateAllMoves();
	}
}

void Board::SolveGame()
{
	int movesCounter = CountMoves();
	int winner = CheckWin();
	while (winner == 0 && movesCounter > 0)
	{
		Position move = BestMove(0, false, currentPlayer);
		board[move.y][move.x] = currentPlayer;
		movesCounter--;
		currentPlayer = NextPlayer(currentPlayer);
		winner = CheckWin();
	}

	if (winner == 10)
	{
		std::cout << "FIRST_PLAYER_WINS \n";
	}
	else if(winner == -10)
	{
		std::cout << "SECOND_PLAYER_WINS \n";
	}
	else
	{
	std::cout << "BOTH_PLAYERS_TIE \n";
	}
}

Board::Position Board::BestMove(int depth, bool isMax, char player)
{
	Position move = { -1, -1 };
	int bestScoreMax = -999;
	for (int i = 0; i < sizeY; i++)
	{
		for (int j = 0; j < sizeX; j++)
		{
			if (board[i][j] == '0')
			{
				board[i][j] = player;

				int score = MinMax(depth, isMax, player, -9999, 9999);

				board[i][j] = '0';

				if (score > bestScoreMax)
				{
					bestScoreMax = score;
					move.y = i;
					move.x = j;
				}				
			}
		}
	}
	return move;
}

int Board::MinMax(int depth, bool isMax, char player, int alpha, int beta)
{
	int score = CheckWin();

	if (score == 10)
	{
		if (!isMax)
		{
			return score - depth;
		}
		else return -score + depth;
	}

	if (score == -10)
	{
		if (isMax)
		{
			return score + depth;
		}
		else return -score - depth;

	}

	if (CountMoves() == 0)
	{
		return 0;
	}

	if (isMax)
	{
		int maxScore = -9999;

		for (int i = 0; i < sizeY; i++)
		{
			for (int j = 0; j < sizeX; j++)
			{
				if (board[i][j] == '0')
				{
					board[i][j] = NextPlayer(player);

					int value = MinMax(depth + 1, false, NextPlayer(player), alpha, beta);
					maxScore = Max(maxScore, value);
					alpha = Max(alpha, maxScore);

					board[i][j] = '0';

					if (beta <= alpha)
					{
						break;
					}
				}
			}
		}
		return maxScore;
	}
	else
	{
		int maxScore = 9999;
		for (int i = 0; i < sizeY; i++)
		{
			for (int j = 0; j < sizeX; j++)
			{
				if (board[i][j] == '0')
				{
					board[i][j] = NextPlayer(player);

					int value = MinMax(depth + 1, true, NextPlayer(player), alpha, beta);
					maxScore = Min(maxScore, value);
					beta = Min(beta, maxScore);

					board[i][j] = '0';

					if (beta <= alpha)
					{
						break;
					}
				}
			}
		}
		return maxScore;
	}
}

char Board::NextPlayer(char player)
{
	if (player == PLAYER1)
	{
		return PLAYER2;
	}
	else
		return PLAYER1;
}

int Board::Min(int a, int b)
{
	if (a < b)
	{
		return a;
	}
	else
		return b;
}

int Board::Max(int a, int b)
{
	if (a > b)
	{
		return a;
	}
	else
		return b;
}

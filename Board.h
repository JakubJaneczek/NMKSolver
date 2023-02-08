class Board {
public:
	int sizeX;
	int sizeY;
	int inRow;
	int moveIndex = 0;
	int boardSize = 0;
	char** board = nullptr;
	char currentPlayer;
	int movesPossible = 0;

	struct Position
	{
		int x, y;
	};
	Board(int x, int y, int inRow, char currentPlayer);
	~Board();
	int CheckWin() const;
	int Winner(int i, int j) const;
	void Print() const;
	/////////////////////////////////////////////////////////////
	void GenerateAllMoves();
	int CountMoves();
	/////////////////////////////////////////////////////////////
	void GenerateAllMovesAndEndIfNecessary();
	/////////////////////////////////////////////////////////////
	void SolveGame();
	Position BestMove(int depth, bool isMax, char player);
	int MinMax(int depth, bool isMax, char player, int alpha, int beta);
	static char NextPlayer(char player);
	static int Min(int a, int b);
	static int Max(int a, int b);
};
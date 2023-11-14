
#ifndef MINIMAXPLAYER_H_
#define MINIMAXPLAYER_H_

class Minimax: public Player {
	int playerSymbol;
	int steps;

public:
	Minimax(int t) : Player("Minimax", t) {
		playerSymbol = t;
		steps = 1000;
	}

    void getMove(Board board, int& x, int& y) {

	vector<int> emptyCells = board.getEmptyPositions();
	if (emptyCells.empty())
		return;
	random_shuffle(emptyCells.begin(), emptyCells.end());


	priority_queue < Cell > moves;

	for (int index : emptyCells) {
		steps = 10000;
		int i = index / board.getCol();
		int j = index % board.getCol();
		Board tempBoard(board);
		tempBoard.addMove(playerSymbol, i, j);
		if (tempBoard.isBoardFull()) {
			if (tempBoard.checkWinningStatus() == playerSymbol) {
				x = i;
				y = j;
				return;
			} else {
				continue;
			}
		}
		double minUtility = minMove(tempBoard);
		Cell c(i, j, minUtility);
		moves.push(c);
	}

	
	if (moves.size() > 0) {
		x = moves.top().x;
		y = moves.top().y;

		cout << moves.size() << " MiniMax Utility = " << moves.top().heuristic
				<< " at (" << (x + 1) << "," << (y + 1) << ")" << endl;
	}

	return;
}

double maxMove(Board board) {
	vector<int> emptyCells = board.getEmptyPositions();
	if (emptyCells.empty() || steps <= 0)
		return 0.01;

	random_shuffle(emptyCells.begin(), emptyCells.end());

	double maxUtility = -2;
	for (int index : emptyCells) {
		int i = index / board.getCol();
		int j = index % board.getCol();
		Board tempBoard(board);
		tempBoard.addMove(board.getTurn(), i, j);
		int gameStatus = tempBoard.checkWinningStatus();
		if (gameStatus != -2) {
			if (gameStatus == board.getTurn())
				return 1; //score 1 if wins
			else if (gameStatus == 0)
				return 0; //score 0 if tie
			else
				return -1; //score -1 if lose
		}

		double utility;
		utility = minMove(tempBoard);

		if (utility > maxUtility) {
			maxUtility = utility;
		}
	steps--;
	}
	// steps--;
	return maxUtility;
}

double minMove(Board board) {

	vector<int> emptyCells = board.getEmptyPositions();
	if (emptyCells.empty() || steps <= 0)
		return -0.01;

	random_shuffle(emptyCells.begin(), emptyCells.end());
	double minUtility = 2;
	for (int index : emptyCells) {
		int i = index / board.getCol();
		int j = index % board.getCol();
		Board tempBoard(board);
		tempBoard.addMove(board.getTurn(), i, j);
		int gameStatus = tempBoard.checkWinningStatus();
		if (gameStatus != -2) {
			if (gameStatus == board.getTurn())
				return 1; //score 1 if wins
			else if (gameStatus == 0)
				return 0; //score 0 if tie
			else
				return -1; //score -1 if lose
		}

		double utility = maxMove(board);

		if (utility < minUtility) {
			minUtility = utility;
		}
	steps--;
	}
	// steps--;
	return minUtility;
}

};


#endif /* MINIMAXPLAYER_H_ */

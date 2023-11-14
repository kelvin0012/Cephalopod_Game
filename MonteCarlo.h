#ifndef MONTECARLOPLAYER_H_
#define MONTECARLOPLAYER_H_

const int simulation_times = 100; // default - 100

class MonteCarlo: public Player {
	int playerSymbol;
public:
	MonteCarlo(int t) : Player("MonteCarlo", t) {
		playerSymbol = t;
	}

	void getMove(Board board, int& x, int& y) {

		vector<int> emptyCells = board.getEmptyPositions();
		if (emptyCells.empty())
			return;

		priority_queue<Cell> moves;

		for (int index : emptyCells) {
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

			double utility = simulation(tempBoard);
			utility *= simulation_times;
			Cell c(i, j, utility);
			moves.push(c);
		}

		if (moves.size() > 0) {
			x = moves.top().x;
			y = moves.top().y;

			cout << moves.size() << " Monte Carlo Utility = " << moves.top().heuristic << " at ("
					<< x << "," << y << ")" << endl;
		}

		return;
	}

	double simulation(Board board) {

		int winning = 0;

		for (int i = 0; i < simulation_times; i++) {
			Board tempBoard(board);
			winning += expansion(tempBoard);
		}

		return ((double) winning / (double) simulation_times);
	}

	int expansion(Board board) {
        int gameStatus = board.checkWinningStatus();
		if (gameStatus != -2) {
			if ( gameStatus == playerSymbol)
				return  1; //score 1 if wins
			else if (gameStatus == 0)
				return 0; //score 0 if tie
			else
				return -1; //score -1 if lose
		}
		else
			gameStatus = 0;

		int x, y;
		board.getaRandomMove(x, y);
		board.addMove(board.getTurn(), x, y);
		return expansion(board);
	}

};

#endif /* MONTECARLOPLAYER_H_ */

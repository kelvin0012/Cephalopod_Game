#ifndef RANDOMPLAYER_H_
#define RANDOMPLAYER_H_

class RandomPlayer: public Player {
private:
    vector<int> emptyBoard;
public:
	RandomPlayer(int t):Player("Random", t){}
	void getMove(Board board, int&, int&);
};

void RandomPlayer::getMove(Board board, int& x, int& y)
{
	if(board.isBoardFull())
		return;

	do {
        if (emptyBoard.empty()) {
            for (int i = 0; i < board.getRow()*board.getCol(); i++) {
				emptyBoard.push_back(i);
			}
        }
        
		srand(time(NULL));
        int index, value;			
        index = rand() % emptyBoard.size();
        value = emptyBoard[index];
        emptyBoard.erase(emptyBoard.begin()+index);
        x = value / board.getCol();
        y = value % board.getCol();
	} while (!board.validMove(x,y));
}

#endif /* RANDOMPLAYER_H_ */

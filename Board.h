#ifndef BOARD_H_
#define BOARD_H_

class Board {
private:
	int row, col;
	int player; //1 = white; -1 = black
	int **grid; // 0 = empty; other values for pip count; positive for white; negative for black
public:
	Board(int r, int c) :
			row(r), col(c) {
		grid = new int*[row];
		for (int i = 0; i < row; i++)
			grid[i] = new int[col];

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				grid[i][j] = 0;
			}
		}
		player = 1; // white has the first turn
	}

	~Board() {
		for (int i = 0; i < row; i++)
			delete[] grid[i];

		delete[] grid;
	}

	Board(const Board &cboard) {//Copy constructor
		row = cboard.row;
		col = cboard.col;

		grid = new int*[row];
		for (int i = 0; i < row; i++)
			grid[i] = new int[col];

		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++) {
				grid[i][j] = cboard.grid[i][j];
			}

		player = cboard.getTurn();
	}

	bool isBoardFull() {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if(grid[i][j] == 0)
					return false;
			}
		}
		return true;
	}

	int getTurn() const {
		return player;
	}

	int getRow() const {
		return row;
	}

	int getCol() const {
		return col;
	}

	int getGrid() const {
		return **grid;
	}

	vector<int> getEmptyPositions();

	void getaRandomMove(int& x, int& y);

	bool validMove(int x, int y);

	bool addMove(int player, int x, int y);

	int checkWinningStatus();

	void printBoard();

	int capturingPlacement(int, int);
};

vector<int> Board:: getEmptyPositions() {
	vector<int> emptyCells;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (grid[i][j] == 0)	
				emptyCells.push_back(i * col + j);
		}
	}
    return emptyCells;
}

void Board::getaRandomMove(int& x, int& y) {
	
		vector<int> emptyCells = getEmptyPositions();
		// srand(time(NULL));
        int index, value;			
        index = rand() % emptyCells.size();
		x = emptyCells[index] / col;
		y = emptyCells[index] % col;


        // if (emptyBoardRandom.empty()) {
        //     for (int i = 0; i < row*col; i++) {
		// 		emptyBoardRandom.push_back(i);
		// 	}
        // }
		// srand(time(NULL));
        // int index, value;			
        // index = rand() % emptyBoardRandom.size();
        // value = emptyBoardRandom[index];
        // emptyBoardRandom.erase(emptyBoardRandom.begin()+index);
        // x = value / col;
        // y = value % col;
	

}

int Board::capturingPlacement(int x, int y) { 
	//Sum of neighbours   
	queue<int> neighbourCells; // Queue is used for fast insertion and doesn't need random access to elements like a vector, nor a list to use in a middle of the sequence
	unordered_map<string, int> neighbourPositions; // Hash Map
	int sum = 0;
	int numberOfNeighbours = 0;

	neighbourPositions.insert(make_pair("Top", 0));
	neighbourPositions.insert(make_pair("Bottom", 0));
	neighbourPositions.insert(make_pair("Left", 0));
	neighbourPositions.insert(make_pair("Right", 0));

	if (x > 0) { //top
		
		neighbourCells.push(abs(grid[x-1][y]));
		neighbourPositions["Top"] = abs(grid[x-1][y]);
		if (grid[x-1][y] != 0)
			numberOfNeighbours++;
	}

	if (x < row - 1) { //bottom
		
		neighbourCells.push(abs(grid[x+1][y]));
		neighbourPositions["Bottom"] = abs(grid[x+1][y]);
		if (grid[x+1][y] != 0)
			numberOfNeighbours++;
	}

	if (y > 0) { //left
	
		neighbourCells.push(abs(grid[x][y-1]));
		neighbourPositions["Left"] = abs(grid[x][y-1]);
		if (grid[x][y-1] != 0)
			numberOfNeighbours++;
	}

	if (y < col - 1) { //right
	
		neighbourCells.push(abs(grid[x][y+1]));
		neighbourPositions["Right"] = abs(grid[x][y+1]);
		if (grid[x][y+1] != 0)
			numberOfNeighbours++;
	}
	
	while (!neighbourCells.empty())
	{
		sum += neighbourCells.front();
		neighbourCells.pop();
	}

	// if (sum <= 6 && sum != NULL) 
	// 	return sum;
	// else	
	// 	return 1;

	//Capturing
	if (numberOfNeighbours < 2) //Case 1
		return 1;

	if (numberOfNeighbours == 2) { //Case 2
		if (sum <= 6) { // sum less than equal to 6
			if (neighbourPositions["Top"] != 0 && neighbourPositions["Bottom"] != 0) {
				grid[x-1][y] = 0;
				grid[x+1][y] = 0;
			}
			else if (neighbourPositions["Top"] != 0 && neighbourPositions["Left"] != 0)
			{
				grid[x-1][y] = 0;
				grid[x][y-1] = 0;
			}
			else if (neighbourPositions["Top"] != 0 && neighbourPositions["Right"] != 0) 
			{
				grid[x-1][y] = 0;
				grid[x][y+1] = 0;
			}
			else if (neighbourPositions["Bottom"] != 0 && neighbourPositions["Left"] != 0) // bottom and left
			{
				grid[x+1][y] = 0;
				grid[x][y-1] = 0;
			}
			else if (neighbourPositions["Bottom"] != 0 && neighbourPositions["Right"] != 0) // bottom and right
			{
				grid[x+1][y] = 0;
				grid[x][y+1] = 0;
			}
			else if (neighbourPositions["Left"] != 0 && neighbourPositions["Right"] != 0) // left and right
			{
				grid[x][y-1] = 0;
				grid[x][y+1] = 0;
			}
			return sum;
		}
		else // sum more than 6
			return 1;
	}

	if (numberOfNeighbours > 2) { //Case 3
		if (sum <= 6) { // All neighbours less than 6
			if (x > 0) 
				grid[x-1][y] = 0;
			if (x < row - 1) 
				grid[x+1][y] = 0;
			if (y > 0) 	
				grid[x][y-1] = 0;
			if (y < col - 1) 
				grid[x][y+1] = 0;
			return sum;
		}
		
		// All neighbours more than 6 but at least 2 neightbours less than 6 (Capture 3)
		if (neighbourPositions["Left"] + neighbourPositions["Top"] + neighbourPositions["Right"] <= 6 && neighbourPositions["Left"] != 0 && neighbourPositions["Top"] != 0 && neighbourPositions["Right"] != 0)  {
			grid[x][y-1] = 0;
			grid[x-1][y] = 0;
			grid[x][y+1] = 0;
			return neighbourPositions["Left"] + neighbourPositions["Top"] + neighbourPositions["Right"];
		}

		if (neighbourPositions["Top"] + neighbourPositions["Left"] + neighbourPositions["Bottom"] <= 6 && neighbourPositions["Top"] != 0 && neighbourPositions["Left"] != 0 && neighbourPositions["Bottom"] != 0) {
			grid[x-1][y] = 0;
			grid[x][y-1] = 0;
			grid[x+1][y] = 0;
			return neighbourPositions["Top"] + neighbourPositions["Left"] + neighbourPositions["Bottom"];
		}

		if (neighbourPositions["Top"] + neighbourPositions["Right"] + neighbourPositions["Bottom"] <= 6 && neighbourPositions["Top"] != 0 && neighbourPositions["Right"] != 0 && neighbourPositions["Bottom"] != 0) {
			grid[x-1][y] = 0;
			grid[x][y+1] = 0;
			grid[x+1][y] = 0;
			return neighbourPositions["Top"] + neighbourPositions["Right"] + neighbourPositions["Bottom"];
		}
		
		if (neighbourPositions["Left"] + neighbourPositions["Bottom"] + neighbourPositions["Right"] <= 6 && neighbourPositions["Left"] != 0 && neighbourPositions["Bottom"] != 0 && neighbourPositions["Right"] != 0) {
			grid[x][y-1] = 0;
			grid[x+1][y] = 0;
			grid[x][y+1] = 0;
			return neighbourPositions["Left"] + neighbourPositions["Bottom"] + neighbourPositions["Right"];
		}
		// Capture 2
		if (neighbourPositions["Top"] + neighbourPositions["Bottom"] <= 6 && neighbourPositions["Top"] != 0 && neighbourPositions["Bottom"] != 0) {
			grid[x+1][y] = 0;
			grid[x-1][y] = 0;
			return neighbourPositions["Top"] + neighbourPositions["Bottom"];
		}

		if (neighbourPositions["Top"] + neighbourPositions["Left"] <= 6 && neighbourPositions["Top"] != 0 && neighbourPositions["Left"] != 0) {
			grid[x-1][y] = 0;
			grid[x][y-1] = 0;
			return neighbourPositions["Top"] + neighbourPositions["Left"];
		}

		if (neighbourPositions["Top"] + neighbourPositions["Right"] <= 6 && neighbourPositions["Top"] != 0 && neighbourPositions["Right"] != 0) {
			grid[x-1][y] = 0;
			grid[x][y+1] = 0;
			return neighbourPositions["Top"] + neighbourPositions["Right"];
		}

		if (neighbourPositions["Bottom"] + neighbourPositions["Left"] <= 6 && neighbourPositions["Bottom"] != 0 && neighbourPositions["Left"] != 0) {
			grid[x+1][y] = 0;
			grid[x][y-1] = 0;
			return neighbourPositions["Bottom"] + neighbourPositions["Left"];
		}

		if (neighbourPositions["Bottom"] + neighbourPositions["Right"] <= 6 && neighbourPositions["Bottom"] != 0 && neighbourPositions["Right"] != 0) {
			grid[x+1][y] = 0;
			grid[x][y+1] = 0;
			return neighbourPositions["Bottom"] + neighbourPositions["Right"];
 		}
		
		if (neighbourPositions["Left"] + neighbourPositions["Right"] <= 6 && neighbourPositions["Left"] != 0 && neighbourPositions["Right"] != 0) {
			grid[x][y-1] = 0;
			grid[x][y+1] = 0;
			return neighbourPositions["Left"] + neighbourPositions["Right"];
		}

		// Any two more than 6
		if (neighbourPositions["Top"] + neighbourPositions["Bottom"] > 6 || neighbourPositions["Top"] + neighbourPositions["Bottom"] > 6 || neighbourPositions["Top"] + neighbourPositions["Left"] > 6 || neighbourPositions["Top"] + neighbourPositions["Right"] > 6 || neighbourPositions["Bottom"] + neighbourPositions["Left"] > 6 || neighbourPositions["Bottom"] + neighbourPositions["Right"] > 6 || neighbourPositions["Left"] + neighbourPositions["Right"] > 6)
			return 1;
	}
	return 0;
}

int Board::checkWinningStatus() {
	if (!isBoardFull())
		return -2; //error message

	int counter = 0;

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (grid[i][j] > 0)
				counter++;
		}
	}

	if (counter * 2 > row * col)
		return 1; //white player won
	else if (counter * 2 < row * col)
		return -1; //black player won
	else
		return 0;//draw
}

bool Board::validMove(int x, int y) {

	if (x < 0 || y < 0 || x > row - 1 || y > col - 1) {
		return false;
	}

	if (grid[x][y] != 0) {
		return false;
	}

	return true;
}

bool Board::addMove(int p, int x, int y) {
	if (p != player) {
		cout << "It is not the player's turn!" << endl;
		return false;
	}

	if (!validMove(x, y))
		return false;

	grid[x][y] = player * capturingPlacement(x, y);

	player = -1 * player;

	return true;
}

void Board::printBoard() {
	cout << "    ";
	for (int j = 0; j < col; j++) {
		cout << j + 1 << "   ";
	}
	cout << endl;

	for (int i = 0; i < row; i++) {
		cout << "  ";
		for (int j = 0; j < col; j++) {
			cout << " ---";
		}
		cout << endl;

		cout << (i + 1) << " |";

		for (int j = 0; j < col; j++) {
			if (grid[i][j] == 0) {
				cout << "   |";
			} else if (grid[i][j] > 0) {
				cout << " " << grid[i][j] << " |";
			} else if (grid[i][j] < 0) {
				cout << "" << grid[i][j] << " |";
			}
		}
		cout << endl;
	}
	cout << "  ";

	for (int j = 0; j < col; j++) {
		cout << " ---";
	}
	cout << endl << endl;
}

#endif /* BOARD_H_ */

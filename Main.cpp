#include<iostream>
#include<iomanip>
#include<time.h>
#include<algorithm>
#include<unordered_map>
#include<sstream>
#include<vector>
#include<set>
#include<queue>

using namespace std;

#include "Cell.h"
#include "Board.h"
#include "Player.h"
#include "CephalopodGame.h"
#include "HumanPlayer.h"
#include "RandomPlayer.h"
#include "MonteCarlo.h"
#include "Minimax.h"


int main() {
	srand(time(0));
	Player *players[2];
	char letter;
	cout << "======== MENU ========\n"
		 << "A: Human Player vs Human Player\n"
		 << "B: Human Player vs Random Player\n"
		 << "C: Random Player vs Random Player\n"
		 << "D: Human Player vs MonteCarlo\n"
		 << "E: Human Player vs Minimax\n"
		 << "F: Random Player vs Minimax\n"
		 << "G: Random Player vs MonteCarlo\n"
		 << "H: Minimax vs MonteCarlo\n"
		 << "======================\n" << endl;

	cout << "Enter your choice: ";
	cin >> letter;

	while (letter != 'a' && letter != 'A' && letter != 'b' && letter != 'B' && letter != 'c' && letter != 'C' && letter !='d' && letter != 'D' && letter != 'e' && letter != 'E' && letter !='f' && letter !='F' && letter != 'g' && letter !='G' && letter !='h' && letter != 'H')
	{
		cout << "Invalid Choice\n"
			 << "Please try again: ";
		cin >> letter;
	}

	switch (letter)
	{
	case 'a':
		players[0] = new HumanPlayer(1);
		players[1] = new HumanPlayer(-1);
		break;
	case 'b':
		players[0] = new HumanPlayer(1);
		players[1] = new RandomPlayer(-1);
		break;
	case 'c':
		players[0] = new RandomPlayer(1);
		players[1] = new RandomPlayer(-1);
		break;
	case 'd':
		players[0] = new HumanPlayer(1);
		players[1] = new MonteCarlo(-1);
		break;
	case 'e':
		players[0] = new HumanPlayer(1);
		players[1] = new Minimax(-1);
		break;
	case 'f':
		players[0] = new RandomPlayer(1);
		players[1] = new Minimax(-1);
		break;
	case 'g':
		players[0] = new RandomPlayer(1);
		players[1] = new MonteCarlo(-1);
		break;
	case 'h':
		players[0] = new Minimax(1);
		players[1] = new MonteCarlo(-1);
		break;
	case 'A':
		players[0] = new HumanPlayer(1);
		players[1] = new HumanPlayer(-1);
		break;
	case 'B':
		players[0] = new HumanPlayer(1);
		players[1] = new RandomPlayer(-1);
		break;
	case 'C':
		players[0] = new RandomPlayer(1);
		players[1] = new RandomPlayer(-1);
		break;
	case 'D':
		players[0] = new HumanPlayer(1);
		players[1] = new MonteCarlo(-1);
		break;
	case 'E':
		players[0] = new HumanPlayer(1);
		players[1] = new Minimax(-1);
		break;
	case 'F':
		players[0] = new RandomPlayer(1);
		players[1] = new Minimax(-1);
		break;
	case 'G':
		players[0] = new RandomPlayer(1);
		players[1] = new MonteCarlo(-1);
		break;
	case 'H':
		players[0] = new Minimax(1);
		players[1] = new MonteCarlo(-1);
		break;
	default:
		break;
	}

	cout << "Input size of the board (say (2,2), (2,3), (3,3), (3,5), (5,5) ... " << endl;

	int row, col;
	cin >> row >> col;

	Board board(row, col);
	CephalopodGame game(board, players);
	game.play();

	delete players[0];
	delete players[1];

	return 0;
}

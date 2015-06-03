#include <bits/stdc++.h>

using namespace std;

class Game {
	public:
		int toPlay;
		int winner;
		bool isDone;
		void humanTurn();
		void aiTurn();
		void printState();
		Game();
		Game(int current[3][3]);

	private:
		int state[3][3];
		void checkIfDone(int i, int j);
		void simulate();
};

// State 1 is a human placed counter, -1 is computer placed, 0 is empty
void Game::humanTurn() {
	int i,j;
	while(true) {
		cout << "Enter your move: ";
		cin >> i >> j;
		if(state[i][j])
			cout << "Invalid move. Try again.\n";
		else
			break;
	}
	state[i][j] = 1;
	toPlay = -toPlay;
	printState();
	checkIfDone(i, j);
}

void Game::aiTurn() {
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			if(!state[i][j]) {
				state[i][j] = -1;
				toPlay = -toPlay;
				printState();
				checkIfDone(i, j);
				return;
			}
}

void Game::checkIfDone(int i, int j) {
	if(state[i][0] == state[i][1] && state[i][1] == state[i][2] && state[i][0]) {
		winner=state[i][0];
		isDone=1;
		cout << "m1\n";
		return;
	}
	if(state[0][j] == state[1][j] && state[1][j] == state[2][j] && state[0][j]) {
		winner=state[0][j];
		isDone=1;
		cout << "m2\n";
		return;
	}
	if(i==j && state[0][0] == state[1][1] && state[1][1] == state[2][2] && state[0][0]) {
		winner=state[0][0];
		isDone=1;
		cout << "m3\n";
		return;
	}
	if(i+j==2 && state[0][2] == state[1][1] && state[1][1] == state[2][0] && state[0][2]) {
		winner=state[0][2];
		isDone=1;
		cout << "m4\n";
		return;
	}
	return;
}

void Game::printState() {
	cout << "###########################\n";
	for(int i=0;i<3;i++) {
		cout << " | ";
		for(int j=0;j<3;j++)
			cout << state[i][j] << " | ";
		cout << "\n---------------\n";
	}
	cout << "###########################\n";
}

Game::Game() {
	toPlay=1;
	isDone=0;
	winner=0;
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			state[i][j]=0;
}

Game::Game(int current[3][3]) {
	toPlay=1;
	isDone=0;
	winner=0;
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			state[i][j]=current[i][j];
}

// toPlay == 1 means knot's turn, toPlay == -1 means cross's turn
int main() {
	Game game;
	game.printState();
	while(!game.isDone) {
		(game.toPlay==1) ? game.humanTurn() : game.aiTurn();
	}
	cout << "And the winner is........... " << game.winner << endl;
}

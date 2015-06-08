#include <bits/stdc++.h>

using namespace std;

class Game {
	public:
		int toPlay;
		int winner;
		int depth;
		bool isDone;
		int humanTurn();
		int aiTurn();
		void printState();
		Game();
		Game(int current[3][3], int CurToPlay, int CurDepth);

	private:
		int state[3][3];
		void checkIfDone(int i, int j);
		bool toPrint;
};

// State 1 is a human placed counter, -1 is computer placed, 0 is empty
int Game::humanTurn() {
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
	checkIfDone(i, j);
}

int Game::aiTurn() {
	if(isDone) {
		if(winner == 1) return 10;
		else if(winner == -1) return -10;
		else return 0;
	}

	int imax=-1, jmax=-1, scorec=-100*(toPlay);
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			if(!state[i][j]) {
				state[i][j]=toPlay;
				Game sim(state, -toPlay, depth);
				sim.checkIfDone(i,j);
				int score = sim.aiTurn();
				if((toPlay==1 && score>scorec) || (toPlay==-1 && score<scorec)) {
					scorec=score;
					imax=i;
					jmax=j;
				}
				state[i][j]=0;
			}
	state[imax][jmax]=toPlay;
	toPlay=-toPlay;
	checkIfDone(imax, jmax);
	if(toPrint) printState();
	return scorec;
}

// Checks if game has a result yet and allots the winner.
void Game::checkIfDone(int i, int j) {
	if(state[i][0] == state[i][1] && state[i][1] == state[i][2] && state[i][0]) {
		winner=state[i][0];
		isDone=1;
		return;
	}
	if(state[0][j] == state[1][j] && state[1][j] == state[2][j] && state[0][j]) {
		winner=state[0][j];
		isDone=1;
		return;
	}
	if(i==j && state[0][0] == state[1][1] && state[1][1] == state[2][2] && state[0][0]) {
		winner=state[0][0];
		isDone=1;
		return;
	}
	if(i+j==2 && state[0][2] == state[1][1] && state[1][1] == state[2][0] && state[0][2]) {
		winner=state[0][2];
		isDone=1;
		return;
	}
	
	bool allFull = 1;
	for(int a=0;a<3;a++)
		for(int b=0;b<3;b++)
			if(state[a][b] == 0)
				allFull = 0;

	if(allFull) {
		winner = 0;
		isDone = 1;
		return;
	}
	return;
}

// To print the current state every move
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

// Constructor for the top-level game
Game::Game() {
	toPlay=1;
	isDone=0;
	winner=0;
	depth=0;
	toPrint=1;
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			state[i][j]=0;
}

// Constructor for the simulated games
Game::Game(int current[3][3], int CurToPlay, int CurDepth) {
	toPlay=CurToPlay;
	isDone=0;
	winner=0;
	depth=CurDepth+1;
	toPrint=0;
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			state[i][j]=current[i][j];
}

// toPlay == 1 means human's turn, toPlay == -1 means ai's turn
int main() {
	Game game;
	game.printState();
	while(!game.isDone) {
		(game.toPlay==1) ? game.humanTurn() : game.aiTurn();
	}
	cout << "And the winner is........... " << game.winner << endl;
}

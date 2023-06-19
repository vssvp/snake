#include <iostream>
#include <unistd.h> 
#include <cstdio>  
using namespace std;

bool gameover; 
const int cols = 40;
const int rows = 20;
int x, y, fx, fy;
int score;

typedef enum {STOP , LEFT, RIGHT, UP, DOWN} direction; 
direction d;

char board[rows][cols]; 

int tailX[100]; 
int tailY[100]; 
int ntail = 0; 

void food() {
	fx = rand() % cols; 
	fy = rand() % rows;
	if (fx == 0) fx = 1;
	if (fy == 0) fy = 1;
	if (fx == cols - 1) fx--;
	if (fy == rows - 1) fy--;
}


void setup() {
	system("clear");
	gameover = false; 
	d  = STOP; 
	x = cols / 2; 
	y = rows / 2; 
	food(); 
	score = 0;

}
void draw() {

	for (int i = 0; i < cols; i++) {
		board[0][i] =  '#';
		board[rows -1][i] = '#';
	}

	for (int i = 1; i < rows - 1; i++) {
		for (int j = 0 ; j < cols ; j++) {
			
			if (i == fy && j == fx) board[i][j]= '~';
			else if  (i == y && j == x) board[i][j] = 'O';
			else {
				bool print = false; 
				for(int k = 0; k < ntail; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						if (board[i][j] == '~') food();
						board[i][j] = 'o'; 
						print = true; 
					}
				}

				if (!print) {
					board[i][j] = ' ';
				}
			}

			if (j == 0 || j == cols - 1) board[i][j] = '#';

			

			if (i == fy && j == fx) board[i][j]= '~';
		}
	
	}


	printf("\033[%d;%dH", 0, 0);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << board[i][j];
		}
		cout << endl;
	}

	
	cout << "Score : " << score << endl; 



}




void input() {
	system("/bin/stty raw");
	char ch = getchar();

	
	switch(ch){
		case 'a' :
			d = LEFT;
			break;
		case 'd' :
			d = RIGHT; 
			break;
		case 'w':
			d = UP;
			break;
		case 's' :
			d = DOWN;
			break;
		case 'x' :
			gameover = true;
			break; 
		default :
			break; 
	}

	system("/bin/stty cooked");
}


void logic() {

	// incremented ntails is incremented by 1 when ate 
	for (int i = ntail; i > 0; i--) {

		tailX[i] = tailX[i - 1];
		tailY[i] = tailY[i - 1];
	
	}
	
	tailX[0] = x; 
	tailY[0] = y;


	switch(d) {

		case LEFT:
			x--; 
			break;
		case RIGHT : 
			x++;
			break;
		case DOWN :
			y++;
			break;
		case UP: 
			y--;
			break;
		default : 
			break;
	}

	if (x >= cols || x<= 0 || y >= rows || y <= 0) {
		gameover = true;
	}

	for (int i = 0; i < ntail; i++) {
		if (tailX[i] == x && tailY[i] == y) {
			gameover = true; 
		}
	}

	if ( x == fx && y == fy) { 
		ntail++; 
		score++;  
		food(); 
	}
}


int main() {
	setup();
	while (!gameover) {
		draw();
		input();
		logic(); 
		sleep(0.01); 
	}
	cout << endl; 

}

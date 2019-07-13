// snek.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>	//consol input ouput
#include <windows.h>
#include <MMSystem.h>
#pragma comment(lib,"Winmm.lib")


using namespace std;

/* Global Variables */
bool gameOver = false;
const int width = 20;
const int height = 20;
int x, y;				//snake position
int tailX[400], tailY[400];	//tail
int nTail = 0;				//size of the tail
int fruitX, fruitY;		//fruit position
int score;				//game score
enum eDirection { STOP, LEFT, RIGHT, UP, DOWN };
eDirection dir;			//direction

/* Fonctions */
void setup() {
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

void draw() {	//for the graphic
	Sleep(5);
	system("cls");	//system command to clear the screen

	//upper border
	for (int i = 0; i < width+2; i++) 
		cout << "#";
	cout << endl;

	//in between
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			if (i == 0)
				cout << "#";
			if (i == x && j == y)
				cout << "O";
			else if (i == fruitX && j == fruitY)
				cout << "F";
			else {
				bool print = false;
				for (int k = 0; k < nTail; k++) {
					if (tailX[k] == i && tailY[k] == j) {
						cout << "o";
						print = true;
					}
				}
				if(!print)
					cout << " ";
			}
			
			if (i == width - 1)
				cout << "#";
		}
		cout << endl;
	}

	//bottom border
	for (int i = 0; i < width+2; i++) {
		cout << "#";
	}
	cout << endl;
}

void input() {	//for controls

	if (_kbhit()) {
		switch(_getch()){
		case'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'r':
			gameOver = true;
			break;
		}
	}
}

void logic() {
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++) {
		prev2X = tailX[i];	//saved coordinate
		prev2Y = tailY[i];
		tailX[i] = prevX;	
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case LEFT:
		if (x > -1) {
			x--;
		}
		break;
	case RIGHT:
		if (x < width) {
			x++;
		}
		break;
	case UP:
		if (y > -1) {
			y--;
		}
		break;
	case DOWN:
		if (y < height) {
			y++;
		}
		break;
	default:
		break;
	}
	if (x == -1 || x == width || y == -1 || y == height ) 
		gameOver = true;
	for (int i = 0; i < nTail; i++) {	//if sneak eat else, game over
		if (tailX[i] == x && tailY[i] == y) 
			gameOver = true;
	}
	if (x == fruitX && y == fruitY) {	//if eat fruit
		score += 10;
		do
		{
			fruitX = rand() % width;
			fruitY = rand() % height;
		} while (fruitX == x || fruitY == y)
		nTail++;
	}
	if (gameOver) {
		cout << "GAME OVER" << endl;
	}
	cout << "SCORE: " << score << endl;
	
}

//add music??
/* Main */
int main(){
	setup();
	PlaySound(TEXT("Snake_Runner_Soundtrack.wav"), NULL, SND_ASYNC | SND_LOOP);
	while (!gameOver) {
		draw();
		input();
		logic();
		if (dir == LEFT || dir == RIGHT) {
			Sleep(15);
		}
		Sleep(10);
		if (dir == UP || dir == DOWN) {
			Sleep(70);
		}
		Sleep(5);
	}
}


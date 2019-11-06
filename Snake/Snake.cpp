#include "Snake.h"
#include <iostream>
#include <conio.h>
#include <chrono>
#include <thread>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>

using namespace std;

void Snake::Setup()
{
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
	tailL = 0;
}

void Snake::Intro()
{
	cout << R"(
   _________         _________
  /         \       /         \   
 /  /~~~~~\  \     /  /~~~~~\  \  
 |  |     |  |     |  |     |  |
 |  |     |  |     |  |     |  |
 |  |     |  |     |  |     |  |         /
 |  |     |  |     |  |     |  |       //
(o  o)    \  \_____/  /     \  \_____/ /
 \__/      \         /       \        /
  |         ~~~~~~~~~         ~~~~~~~~
			 _        
			| |       
	 ___ _ __   __ _| | _____ 
	/ __| '_ \ / _` | |/ / _ \
	\__ \ | | | (_| |   <  __/
	|___/_| |_|\__,_|_|\_\___|
)" << '\n';

	cout << R"(
	Rules:
		1, Eat the fruits
		2, Dont eat your tail
		3, Dont touch the walls 
)" << '\n';

	cout << "\tPress any button to continue";
	_getch();
}

void Snake::Draw()
{
	system("cls"); // Clear the console

	for (int i = 0; i < width + 1; i++)
	{
		cout << "#";
	}
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
			{
				cout << "#";
			}

			if (i == y && j == x)
			{
				cout << "O";
			}
			else if (i == fruitY && j == fruitX)
			{
				cout << "F";
			}
			else
			{
				bool printTail = false;

				for (int k = 0; k < tailL; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						printTail = true;
					}
				}
				if (!printTail)
				{
					cout << " ";
				}

			}

			if (j == width - 1)
			{
				cout << "#";
			}
		}
		cout << endl;
	}

	for (int i = 0; i < width + 1; i++)
	{
		cout << "#";
	}
	cout << endl;
	cout << "Score: " << score << endl;
}


void Snake::Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 'x':
			gameOver = true;
			break;
		default:
			break;
		}
	}
}

void Snake::Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;

	tailX[0] = x;
	tailY[0] = y;

	for (int i = 1; i < tailL; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];

		tailX[i] = prevX;
		tailY[i] = prevY;

		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}

	if (x > width || x < 0 || y > height || y < 0)
	{
		gameOver = true;
	}

	for (int i = 0; i < tailL; i++)
	{
		if (tailX[i] == x && tailY[i] == y)
		{
			gameOver = true;
		}
	}

	if (x == fruitX && y == fruitY)
	{
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		tailL++;
	}
}

void Snake::Run()
{
	Setup();
	Intro();

	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	SaveScore();
	HighlightScore();
}

void Snake::SaveScore()
{
	ofstream myfile;
	string name;

	cout << "Please enter your name" << endl;
	getline(cin, name);
	
	myfile.open("highscore.txt", ios_base::app);
	myfile << name << " " << score << endl;
	myfile.close();
}

void Snake::HighlightScore()
{
	system("CLS");
	ifstream file("highscore.txt");
	string line;

	cout << "Highscores:" << endl;
	if (file.is_open()) 
	{
		while (getline(file, line)) 
		{
			// using printf() in all tests for consistency
			printf("%s\n", line.c_str());
		}
		file.close();
	}
}

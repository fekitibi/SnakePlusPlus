#pragma once
class Snake
{
private:
	const int width = 20;
	const int height = 20;

	enum Direction
	{
		STOP = 0, LEFT, RIGHT, UP, DOWN
	};

	int x, y, fruitX, fruitY, tailL, score;
	int tailX[200], tailY[200];
	bool gameOver;
	Direction dir;

	void Setup();
	void Intro();
	void Draw();
	void Input();
	void Logic();
	void SaveScore();
	void HighlightScore();

public:
	void Run();
};


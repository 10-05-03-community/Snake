#include <iostream>
#include <conio.h> //CONInptutOutput позволяет нам взят функцию, которая будет отслеживать ВСЕ то что нажал пользователь и не будет закрываться консоль, -kbhit()   название функции
#include <vector>
#include<ctime>
#include<windows.h>
using namespace std;

bool gameOver;//игра окончена?
const int width = 40;   //ширина игрового поля
const int height = 20;  //высота игрвого поля
int x, y;//координаты головы змейки
vector <int> tallX; //координаты хвоста
vector <int> tallY; 
int fruitX, fruitY; //координаты фруктика
int score; //счет 
int tallSize ;//длина хвоста
int slaw=50;//медленность змейки по умолчанию стоит 50 милисекунд
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN }; //это перечисления. инициализирован только СТОП тк все остальные инициализируются автоматически на 1 больше

eDirection dir;
void setcur(int x, int y) //всегда перемещает курсор в координату (0;0)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};

void Setup() //вызываем только при старте игры. Настраивает параметры игры
{
	gameOver = false;
	dir = STOP; // в начале игры змейка никуда не двигается

	x = width / 2-1; //змейка в середине поля
	y = height / 2-1;

	fruitX = rand() % (width-2); //генерятся рандомно
	fruitY = rand() % (height-2);

	score = 0;
	tallSize = 0;
}

void Draw()  //Рисует нашу карту
{

	Sleep(slaw);
	
	//system("cls");  //постоянно очищает консоль
	setcur(0, 0);
	for (int i = 0; i < width+1; i++)    //рисуем поля карты
	{
		cout << "#";
	}
	cout << endl;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0 || j == width-1)
			{
				cout << "#";
			}
			if (i == y && j == x)//рисуем змейку
			{
				cout << "O";
			}
			
			else if (i == fruitY && j == fruitX)
			{
				cout << "f"; //рисуем фрукт
			}
			else
			{
				bool print = false;
					for (int k = 0; k < tallX.size(); k++)
					{
						if (tallX[k] == j && tallY[k] == i)
						{
							cout << "o";
							print = true;
						}
					}
					if (!print)
					{
						cout << " ";
					}
			}
			
			
		}
		cout << endl;
	}
	for (int i = 0; i < width+1; i++)
	{
		cout << "#";
	}
	cout << endl << "Score: " << score;
}

void Input() //Отслеживает все нажатия 
{
	if (_kbhit())   //_kbhit() возвращает true, если пользователь нажал кнопку на клаве
	{
		switch (_getch()) //_getch() отслеживает какую кнопку нажали
		{
		case 'a':
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
		case 'x':
			gameOver = true;
			break;
		case 'o':
			cout << endl<<"Options: " << endl;
			cout << "Slaw (milliseconds) : ";
			cin >> slaw;
			break;
		
		}
	}
}

void Logic()//вся логика игры
{
	switch (dir) //если нажаты определенные клавишы, то перемещяем 
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
	}
	
	if (x > width-2 || x<0 || y>height-1 || y < 0)//если змейка вышла за пределы поля
	{
		gameOver = true;
	}

	if (x == fruitX && y == fruitY) //если съели фрукт
	{
		score+=10;
		fruitX = rand() % width; //генерятся рандомно
		fruitY = rand() % height;
		
		tallSize++;
		tallX.insert(tallX.begin(), x);
		tallY.insert(tallY.begin(), y);
		
		if (tallSize == 1)
		{
			tallX.insert(tallX.begin(), x);
			tallY.insert(tallY.begin(), y);
		}
	}
	
	if (tallSize > 0 )
	{
		tallX.insert(tallX.begin(), x);
		tallY.insert(tallY.begin(), y);

		tallX.erase(tallX.end()-1);
		tallY.erase(tallY.end()-1);

	}
}

int main()
{
	srand(time(NULL));
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
	}
	return 0;
}

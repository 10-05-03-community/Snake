#include <iostream>
#include <conio.h> //CONInptutOutput ��������� ��� ���� �������, ������� ����� ����������� ��� �� ��� ����� ������������ � �� ����� ����������� �������, -kbhit()   �������� �������
#include <vector>
#include<ctime>
#include<windows.h>
using namespace std;

bool gameOver;//���� ��������?
const int width = 40;   //������ �������� ����
const int height = 20;  //������ ������� ����
int x, y;//���������� ������ ������
vector <int> tallX; //���������� ������
vector <int> tallY; 
int fruitX, fruitY; //���������� ��������
int score; //���� 
int tallSize ;//����� ������
int slaw=50;//����������� ������ �� ��������� ����� 50 ����������
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN }; //��� ������������. ��������������� ������ ���� �� ��� ��������� ���������������� ������������� �� 1 ������

eDirection dir;
void setcur(int x, int y) //������ ���������� ������ � ���������� (0;0)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};

void Setup() //�������� ������ ��� ������ ����. ����������� ��������� ����
{
	gameOver = false;
	dir = STOP; // � ������ ���� ������ ������ �� ���������

	x = width / 2-1; //������ � �������� ����
	y = height / 2-1;

	fruitX = rand() % (width-2); //��������� ��������
	fruitY = rand() % (height-2);

	score = 0;
	tallSize = 0;
}

void Draw()  //������ ���� �����
{

	Sleep(slaw);
	
	//system("cls");  //��������� ������� �������
	setcur(0, 0);
	for (int i = 0; i < width+1; i++)    //������ ���� �����
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
			if (i == y && j == x)//������ ������
			{
				cout << "O";
			}
			
			else if (i == fruitY && j == fruitX)
			{
				cout << "f"; //������ �����
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

void Input() //����������� ��� ������� 
{
	if (_kbhit())   //_kbhit() ���������� true, ���� ������������ ����� ������ �� �����
	{
		switch (_getch()) //_getch() ����������� ����� ������ ������
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

void Logic()//��� ������ ����
{
	switch (dir) //���� ������ ������������ �������, �� ���������� 
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
	
	if (x > width-2 || x<0 || y>height-1 || y < 0)//���� ������ ����� �� ������� ����
	{
		gameOver = true;
	}

	if (x == fruitX && y == fruitY) //���� ����� �����
	{
		score+=10;
		fruitX = rand() % width; //��������� ��������
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

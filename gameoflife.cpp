#include <iostream>
#include <time.h>
#include <Windows.h>
#include <conio.h>

using namespace std;

char backgroundMap[25][32];

char Stage[25][32] =
{
	"++++++++++++++++++++++++++++++",
	"++++++++++++++++++++++++++++++",
	"++++++++++++++++++++++++++++++",
	"++++++++++++++++++++++++++++++",
	"+++++++++++++++@++++++++++++++",
	"++++++++++++++@@@+++++++++++++",
	"+++++++++++++++@++++++++++++++",
	"++++++++++++++++++++++++++++++",
	"++++++++++++++++++++++++++++++",
	"++++++++++++++++++++++++++++++"
};

void gotoXY(int x, int y)
{
	HANDLE hOut;
	COORD Cur;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(hOut, Cur);
}

void clrscr()
{
	system("cls");
}

void InitScreen()
{
	for (int y = 0; y < 25; y++)
	{
		for (int x = 0; x < 32; x++)
		{
			gotoXY(x * 2, y);
			if (Stage[y][x] == '+')
			{
				cout << "□";
			}
			else if (Stage[y][x] == '@')
			{
				cout << "■";
			}
		}
	}



}

bool CheckLiveOrDeath(int x, int y, bool isLive)
{
	int liveCnt = 0;

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0) continue;
			if (backgroundMap[x + j][y + i] == '@')
			{
				liveCnt++;
			}
		}
	}

	if (isLive)
	{
		if (liveCnt == 2 || liveCnt == 3)
		{
			return true;
		}
	}
	else
	{
		if (liveCnt == 3)
		{
			return true;
		}
	}

	return false;
}

int main()
{
	Sleep(5000);
	while (true)
	{
		memcpy(backgroundMap, Stage, sizeof(backgroundMap));

		for (int i = 0; i < 25; i++)
		{
			for (int j = 0; j < 32; j++)
			{
				if (backgroundMap[i][j] == '@')
				{
					if (CheckLiveOrDeath(i, j, true))
					{
						Stage[i][j] = '@';
					}
					else
					{
						Stage[i][j] = '+';
					}
				}
				else
				{
					if (CheckLiveOrDeath(i, j, false))
					{
						Stage[i][j] = '@';
					}
					else
					{
						Stage[i][j] = '+';
					}
				}
			}
		}

		InitScreen();
		Sleep(500);
	}
	return 0;
}

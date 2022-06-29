#pragma once

#include "Header.h"

const int c_HEIGHT_MAP = 25;//������ ����� ������
const int c_WIDTH_MAP = 40;//������ ����� ������ 


sf::String TileMap[c_HEIGHT_MAP] = {
	"0000000000000000000000000000000000000000",
	"0                                      0",
	"0                                      0",
	"0                f                     0",
	"0                        h             0",
	"0                                      0",
	"0                                      0",
	"0                                f     0",
	"0                                      0",
	"0            h                         0",
	"0                                      0",
	"0    f                                 0",
	"0                                      0",
	"0                    h                 0",
	"0                                      0",
	"0                                      0",
	"0             f               f        0",
	"0                                      0",
	"0      f                               0",
	"0                                      0",
	"0                                      0",
	"0           f                 f        0",
	"0                                      0",
	"0                                      0",
	"0000000000000000000000000000000000000000",
};

void randomMapGenerator()
{
	int randomElementX(0);		// ��������� ���������� �� �
	int randomElementY(0);		// ��������� ���������� �� y

	srand(time(0));
	int countStoun(10);			// ������� ����� ����� �������������� ������

	while (countStoun > 0)
	{
		randomElementX = 1 + rand() % (c_WIDTH_MAP - 1);		// ������ �� 1 �� ������ ����� ����� 1, ���� ��������� ������
		randomElementY = 1 + rand() % (c_HEIGHT_MAP - 1);		// ������ �� 1 �� ������ ����� ����� 1, ���� ��������� ������
		if (TileMap[randomElementY][randomElementX] == ' ')
		{
			TileMap[randomElementY][randomElementX] = 's';
			std::cout << "Coordinate of stoun: x = " << randomElementX << " | y = " << randomElementY << '\n';
			--countStoun;
		}
	}
}
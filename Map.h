#pragma once

#include "Header.h"

const int c_HEIGHT_MAP = 25;//размер карты высота
const int c_WIDTH_MAP = 40;//размер карты ширина 


sf::String TileMap[c_HEIGHT_MAP] = {
	"0000000000000000000000000000000000000000",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0000000000000000000000000000000000000000",
};

void randomMapGenerator()
{
	int randomElementX(0);		// Случайная координата по х
	int randomElementY(0);		// Случайная координата по y

	srand(static_cast<unsigned>(time(0)));
	int countStoun(10);			// Сколько всего будет сгенерированно камней
	int countHearth(4);			// Всего сердец
	int countFlower(6);			// Всего цветов

	// Разбрасываем камни
	while (countStoun > 0)
	{
		randomElementX = 1 + rand() % (c_WIDTH_MAP - 1);		// Рандом от 1 до ширины карты минус 1, чтоб нетрогать бордюр
		randomElementY = 1 + rand() % (c_HEIGHT_MAP - 1);		// Рандом от 1 до высоты карты минус 1, чтоб нетрогать бордюр
		if (TileMap[randomElementY][randomElementX] == ' ')
		{
			TileMap[randomElementY][randomElementX] = 's';
			--countStoun;
		}
	}

	// Разбрасываем сердца
	while (countHearth > 0)
	{
		randomElementX = 1 + rand() % (c_WIDTH_MAP - 1);		// Рандом от 1 до ширины карты минус 1, чтоб нетрогать бордюр
		randomElementY = 1 + rand() % (c_HEIGHT_MAP - 1);		// Рандом от 1 до высоты карты минус 1, чтоб нетрогать бордюр
		if (TileMap[randomElementY][randomElementX] == ' ')
		{
			TileMap[randomElementY][randomElementX] = 'h';
			--countHearth;
		}
	}

	// Разбрасываем сердца
	while (countFlower > 0)
	{
		randomElementX = 1 + rand() % (c_WIDTH_MAP - 1);		// Рандом от 1 до ширины карты минус 1, чтоб нетрогать бордюр
		randomElementY = 1 + rand() % (c_HEIGHT_MAP - 1);		// Рандом от 1 до высоты карты минус 1, чтоб нетрогать бордюр
		if (TileMap[randomElementY][randomElementX] == ' ')
		{
			TileMap[randomElementY][randomElementX] = 'f';
			--countFlower;
		}
	}
}
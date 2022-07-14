#pragma once

const int HEIGHT_MAP(25);
const int WIDTH_MAP(40);

std::string TileMap[HEIGHT_MAP] = {
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
	"00000000000                           00",
	"0                                      0",
	"0                   00000              0",
	"0                00000000              0",
	"0              0000000000              0",
	"0000000000000000000000000000000000000000",
};

void randomMapGenerator()
{
	srand(static_cast<unsigned>(time(0)));
	int randomCoordinateX(0);
	int randomCoordinateY(0);
	int countStone(9);
	int countHeart(5);
	int countFlower(4);

	while (countStone > 0)
	{
		randomCoordinateX = 1 + (rand() % (WIDTH_MAP - 1));
		randomCoordinateY = 1 + (rand() % (HEIGHT_MAP - 1));
		if (TileMap[randomCoordinateY][randomCoordinateX] == ' ')
		{
			TileMap[randomCoordinateY][randomCoordinateX] = 's';
			--countStone;
		}
	}
	while (countHeart > 0)
	{
		randomCoordinateX = 1 + (rand() % (WIDTH_MAP - 1));
		randomCoordinateY = 1 + (rand() % (HEIGHT_MAP - 1));
		if (TileMap[randomCoordinateY][randomCoordinateX] == ' ')
		{
			TileMap[randomCoordinateY][randomCoordinateX] = 'h';
			--countHeart;
		}
	}
	while (countFlower > 0)
	{
		randomCoordinateX = 1 + (rand() % (WIDTH_MAP - 1));
		randomCoordinateY = 1 + (rand() % (HEIGHT_MAP - 1));
		if (TileMap[randomCoordinateY][randomCoordinateX] == ' ')
		{
			TileMap[randomCoordinateY][randomCoordinateX] = 'f';
			--countFlower;
		}
	}
}
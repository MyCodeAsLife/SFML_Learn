#pragma once

#include "Header.h"

extern sf::String TileMap[];		// Объявляем что бы не словить ошибку многократного включения

class Player
{
protected:
	float m_x, m_y;				//Координаты игрока

public:
	float m_width, m_height;	//Высота и ширина
	float m_dx, m_dy;			//Ускорение по х и по у
	float m_speed = 0;			//Скорость
	int m_dir = 0;				//Направление
	String m_fileName;			//Имя файла и его расширение
	Image m_image;				//Изображение
	Texture m_texture;			//Текстура
	Sprite m_sprite;			//Спрайт

public:
	Player(String fileName, float x, float y, float width, float height);
	void update(float time);
	void moveUp(float speed, float time);
	void moveDown(float speed, float time);
	void moveLeft(float speed, float time);
	void moveRight(float speed, float time);
	float getX() { return m_x; }
	float getY() { return m_y; }
	void interactionWithMap();
};
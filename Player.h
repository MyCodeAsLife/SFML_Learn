#pragma once
#include "Header.h"

class Player
{
public:
	float m_x, m_y;				//Координаты игрока
	float m_width, m_height;	//Высота и ширина
	float m_dx, m_dy;			//Ускорение по х и по у
	float m_speed = 0;			//Скорость
	int m_dir = 0;				//Направление
	int m_currentFrame = 0;		//Текущий фрейм анимации
	String m_fileName;			//Имя файла и его расширение
	Image m_image;				//Изображение
	Texture m_texture;			//Текстура
	Sprite m_sprite;			//Спрайт

public:
	Player(String fileName, float x, float y, float width, float height);
	void update(float time);
	void moveUp(int dir, float speed, float time);
	void moveDown(int dir, float speed, float time);
	void moveLeft(int dir, float speed, float time);
	void moveRight(int dir, float speed, float time);
		
};
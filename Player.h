#pragma once

#include "Header.h"


extern sf::String TileMap[];				// Объявляем что бы не словить ошибку многократного включения
extern void moveCamera(float x, float y);	// Объявляем что бы не словить ошибку многократного включения
extern View camera;							// Объявляем что бы не словить ошибку многократного включения

class Player
{
protected:
	float m_x, m_y;				// Координаты игрока

public:
	float m_width, m_height;	// Высота и ширина кализии спрайта
	float m_dx, m_dy;			// Ускорение по х и по у
	float m_speed = 0;			// Скорость
	int m_score = 0;			// Собранно камней
	int m_health;				// Жизни
	bool m_life;				// Состояние "жив\мертв"
	bool m_isMove;				// Состояние персонажа (двигается\стоит)
	bool m_isSelect;			// Состояние персонажа (выделен\нет)
	bool m_onGround;			// Состояние персонажа (стоит на поверхности\нет)
	String m_fileName;			// Имя файла и его расширение
	Image m_image;				// Изображение
	Texture m_texture;			// Текстура
	Sprite m_sprite;			// Спрайт
	enum stateObject { left, right, up, down, jump, stay };
	stateObject m_state;

public:
	Player(String fileName, float x, float y, float width, float height);
	void update(float time);
	float getX() { return m_x; }
	float getY() { return m_y; }
	void setX(float x) { m_x = x; }
	void setY(float y) { m_y = y; }
	void interactionWithMap();
	void control(float time);
};
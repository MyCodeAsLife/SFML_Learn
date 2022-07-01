#pragma once

#include "Header.h"


extern sf::String TileMap[];				// Объявляем что бы не словить ошибку многократного включения
extern void moveCamera(const float x, const float y);	// Объявляем что бы не словить ошибку многократного включения
extern View camera;							// Объявляем что бы не словить ошибку многократного включения

//	Родительский класс для юнитов
class Entity
{
public:
	int m_width, m_height;
	float m_dx, m_dy;		// Ускорение по осям
	float m_x, m_y;			// Положение юнита
	float m_speed;			// Скорость юнита
	float m_moveTimer;		// Таймер для различных действий
	int m_health;			// Здоровье юнита
	bool m_life, m_isMove, m_onGround; // Переменные состояния персонажа
	String m_name;
	Texture m_texture;
	Sprite m_sprite;

public:
	Entity(Image& image, float X, float Y, int width, int height, const String& name);

};

//	Класс игрового персонажа
class Player: public Entity
{
public:
	int m_score;
	enum { left, right, up, down, jump, stay } m_state;//добавляем тип перечисления - состояние объекта

public:
	Player(Image& image, float X, float Y, int W, int H, const String& name);
	void control(const float time);
	void update(const float time);
	float getplayercoordinateX() { return m_x; }
	float getplayercoordinateY() { return m_y; }
	void checkCollisionWithMap(float Dx, float Dy);	//ф ция проверки столкновений с картой

};

class SpriteManager {//это задел на следующие уроки,прошу не обращать внимания на эти изменения)
public:
	Image m_image;
	Texture m_texture;
	Sprite m_sprite;
	String m_name;
	String m_file;
	int m_widthOfSprite;
	int m_heightOfSprite;
	SpriteManager(String file, String Name) {
		m_file = file;
		m_name = Name;
		m_image.loadFromFile("images/" + m_file);
		m_texture.loadFromImage(m_image);
		m_sprite.setTexture(m_texture);
	}
};

// Класс противника
class Enemy :public Entity
{
public:
	Enemy(Image& image, float X, float Y, int W, int H, const String& name);
	void checkCollisionWithMap(const float Dx, const float Dy);
	void update(const float time);

};
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

class Player: public Entity
{
public:
	//float m_width, m_height, m_dx, m_dy, m_x, m_y, m_speed;
	int m_score;
	//bool m_life, m_isMove, m_isSelect, m_onGround;//добавили переменные состояния нахождения на земле
	enum { left, right, up, down, jump, stay } m_state;//добавляем тип перечисления - состояние объекта
	//String m_file;
	//Image m_image;
	//Texture m_texture;
	//Sprite m_sprite;

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
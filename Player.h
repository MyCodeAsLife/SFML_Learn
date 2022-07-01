#pragma once

#include "Header.h"


extern sf::String TileMap[];				// ��������� ��� �� �� ������� ������ ������������� ���������
extern void moveCamera(const float x, const float y);	// ��������� ��� �� �� ������� ������ ������������� ���������
extern View camera;							// ��������� ��� �� �� ������� ������ ������������� ���������

//	������������ ����� ��� ������
class Entity
{
public:
	int m_width, m_height;
	float m_dx, m_dy;		// ��������� �� ����
	float m_x, m_y;			// ��������� �����
	float m_speed;			// �������� �����
	float m_moveTimer;		// ������ ��� ��������� ��������
	int m_health;			// �������� �����
	bool m_life, m_isMove, m_onGround; // ���������� ��������� ���������
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
	//bool m_life, m_isMove, m_isSelect, m_onGround;//�������� ���������� ��������� ���������� �� �����
	enum { left, right, up, down, jump, stay } m_state;//��������� ��� ������������ - ��������� �������
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
	void checkCollisionWithMap(float Dx, float Dy);	//� ��� �������� ������������ � ������

};

class SpriteManager {//��� ����� �� ��������� �����,����� �� �������� �������� �� ��� ���������)
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
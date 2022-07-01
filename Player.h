#pragma once

#include "Header.h"


extern sf::String TileMap[];				// ��������� ��� �� �� ������� ������ ������������� ���������
extern void moveCamera(const float x, const float y);	// ��������� ��� �� �� ������� ������ ������������� ���������
extern View camera;							// ��������� ��� �� �� ������� ������ ������������� ���������

class Player {

public:
	float m_width, m_height, m_dx, m_dy, m_x, m_y, m_speed;
	int m_score, m_health;
	bool m_life, m_isMove, m_isSelect, m_onGround;//�������� ���������� ��������� ���������� �� �����
	enum { left, right, up, down, jump, stay } m_state;//��������� ��� ������������ - ��������� �������
	String m_file;
	Image m_image;
	Texture m_texture;
	Sprite m_sprite;
	Player(String F, float X, float Y, float W, float H);
	void control(const float time);
	void update(const float time);

	float getplayercoordinateX() {
		return m_x;
	}
	float getplayercoordinateY() {
		return m_y;
	}

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
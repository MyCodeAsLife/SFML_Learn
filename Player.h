#pragma once

#include "Header.h"

extern sf::String TileMap[];		// ��������� ��� �� �� ������� ������ ������������� ���������

class Player
{
protected:
	float m_x, m_y;				//���������� ������

public:
	float m_width, m_height;	//������ � ������
	float m_dx, m_dy;			//��������� �� � � �� �
	float m_speed = 0;			//��������
	int m_dir = 0;				//�����������
	String m_fileName;			//��� ����� � ��� ����������
	Image m_image;				//�����������
	Texture m_texture;			//��������
	Sprite m_sprite;			//������

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
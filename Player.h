#pragma once

#include "Header.h"


extern sf::String TileMap[];				// ��������� ��� �� �� ������� ������ ������������� ���������
extern void moveCamera(float x, float y);	// ��������� ��� �� �� ������� ������ ������������� ���������
extern View camera;							// ��������� ��� �� �� ������� ������ ������������� ���������

class Player
{
protected:
	float m_x, m_y;				// ���������� ������

public:
	float m_width, m_height;	// ������ � ������ ������� �������
	float m_dx, m_dy;			// ��������� �� � � �� �
	float m_speed = 0;			// ��������
	int m_score = 0;			// �������� ������
	int m_health;				// �����
	bool m_life;				// ��������� "���\�����"
	bool m_isMove;				// ��������� ��������� (���������\�����)
	bool m_isSelect;			// ��������� ��������� (�������\���)
	bool m_onGround;			// ��������� ��������� (����� �� �����������\���)
	String m_fileName;			// ��� ����� � ��� ����������
	Image m_image;				// �����������
	Texture m_texture;			// ��������
	Sprite m_sprite;			// ������
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
#pragma once
#include "Header.h"

class Player
{
public:
	float m_x, m_y;				//���������� ������
	float m_width, m_height;	//������ � ������
	float m_dx, m_dy;			//��������� �� � � �� �
	float m_speed = 0;			//��������
	int m_dir = 0;				//�����������
	int m_currentFrame = 0;		//������� ����� ��������
	String m_fileName;			//��� ����� � ��� ����������
	Image m_image;				//�����������
	Texture m_texture;			//��������
	Sprite m_sprite;			//������

public:
	Player(String fileName, float x, float y, float width, float height);
	void update(float time);
	void moveUp(int dir, float speed, float time);
	void moveDown(int dir, float speed, float time);
	void moveLeft(int dir, float speed, float time);
	void moveRight(int dir, float speed, float time);
		
};
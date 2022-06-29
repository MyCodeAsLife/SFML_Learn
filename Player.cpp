#include "Player.h"


Player::Player(String fileName, float x, float y, float width, float height) :
	m_fileName(fileName), m_x(x), m_y(y), m_width(width), m_height(height),
	m_dx(0), m_dy(0), m_score(0), m_health(100), m_life(true)
{
	m_image.loadFromFile("images/" + m_fileName);
	m_image.createMaskFromColor(Color(41, 33, 59));		//������� ���� ��� �����
	m_texture.loadFromImage(m_image);
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(IntRect(static_cast<int>(m_width), static_cast<int>(m_height), static_cast<int>(m_width),
		static_cast<int>(m_height)));
}

void Player::update(float time)
{
	switch (m_dir)
	{
	case 0:
		m_dx = m_speed;		//�������� ������
		m_dy = 0;
		break;
	case 1:
		m_dx = -m_speed;	//�������� �����
		m_dy = 0;
		break;
	case 2:
		m_dx = 0;
		m_dy = m_speed;		//�������� ����
		break;
	case 3:
		m_dx = 0;
		m_dy = -m_speed;	//�������� �����
		break;
	}

	m_x += m_dx * time;		//�������� �� �
	m_y += m_dy * time;		//�������� �� y

	m_speed = 0;					//�������� ��������, ���� �������� �������������� ���� �� ������ ������� ��������
	m_sprite.setPosition(m_x, m_y);	//������������� ������� �������
	interactionWithMap();

	if (m_health <= 0)
	{
		m_health = 0;
		m_life = false;
	}
}

void Player::moveUp(float speed, float time)
{
	m_dir = 3;
	m_speed = speed;
	static float currentFrame(0);		//� ������� ������ ���� ���� �� ������������� ��� ������� ���������� ������
	currentFrame += 0.005f * time;
	if (currentFrame > 3)
		currentFrame -= 3;
	m_sprite.setTextureRect(IntRect(96 * static_cast<int>(currentFrame), 288, 96, 96));
}

void Player::moveDown(float speed, float time)
{
	m_dir = 2;
	m_speed = speed;
	static float currentFrame(0);
	currentFrame += 0.005f * time;
	if (currentFrame > 3) currentFrame -= 3;
	m_sprite.setTextureRect(IntRect(96 * static_cast<int>(currentFrame), 0, 96, 96));
}

void Player::moveLeft(float speed, float time)
{
	m_dir = 1;
	m_speed = speed;
	static float currentFrame(0);
	currentFrame += 0.005f * time;
	if (currentFrame > 3) currentFrame -= 3;
	m_sprite.setTextureRect(IntRect(96 * static_cast<int>(currentFrame), 96, 96, 96));
}

void Player::moveRight(float speed, float time)
{
	m_dir = 0;
	m_speed = speed;
	static float currentFrame(0);
	currentFrame += 0.005f * time;
	if (currentFrame > 3) currentFrame -= 3;
	m_sprite.setTextureRect(IntRect(96 * static_cast<int>(currentFrame), 192, 96, 96));
}

void Player::interactionWithMap()
{
	for (int i = m_y / 32; i < (m_y + m_height) / 32; i++)//���������� �� ��������, �������������� � �������, �� ���� �� ���� ����������� ������� 32*32, ������� �� ���������� � 9 �����. ��� ������� ������� ����.
		for (int j = m_x / 32; j < (m_x + m_width) / 32; j++)//��� ����� �� 32, ��� ����� �������� ����� ���������, � ������� �������� �������������. (�� ���� ������ ������� 32*32, ������� ����� ������������ ������ �� ���������� ���������). � j<(x + w) / 32 - ������� ����������� ��������� �� ����. �� ���� ���������� ������ ������� ��������, ������� ������������� � ����������. ����� ������� ���� � ����� ����� ������� �� ����, ������� �� �� ������ �������� (���������������� � ������), �� ������� �������� (���������������� � ������)
		{
			if (TileMap[i][j] == '0')//���� ��� ��������� ������������� ������� 0 (�����), �� ��������� "����������� ��������" ���������:
			{
				if (m_dy > 0)//���� �� ��� ����,
				{
					m_y = i * 32 - m_height;//�� �������� ���������� ����� ���������. ������� �������� ���������� ������ ���������� �� �����(�����) � ����� �������� �� ������ ������� ���������.
				}
				if (m_dy < 0)
				{
					m_y = i * 32 + 32;//���������� � ������� �����. dy<0, ������ �� ���� ����� (���������� ���������� ������)
				}
				if (m_dx > 0)
				{
					m_x = j * 32 - m_width;//���� ���� ������, �� ���������� � ����� ����� (������ 0) ����� ������ ���������
				}
				if (m_dx < 0)
				{
					m_x = j * 32 + 32;	//���������� ���� �����
				}
			}

			//if (TileMap[i][j] == 's')	//���� ������ ����� 's' (������)
			//{ 
			//	++m_score;
			//	//m_x = 300; m_y = 300;//����� �� ��������... �������� ������������ �����
			//	TileMap[i][j] = ' ';//������� ������, ���� ����� �����. ����� � �� �������, ������.
			//}
			if (TileMap[i][j] != ' ')
				switch (TileMap[i][j])
				{
				case 's':
					++m_score;
					TileMap[i][j] = ' ';
					break;
				case 'f':
					m_health -= 40;
					TileMap[i][j] = ' ';
					break;
				case 'h':
					m_health += 20;
					TileMap[i][j] = ' ';
					break;
				}
		}
}

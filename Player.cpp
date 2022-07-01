#include "Player.h"


Player::Player(String fileName, float x, float y, float width, float height) :
	m_fileName(fileName), m_x(x), m_y(y), m_width(width), m_height(height), m_isSelect(false), m_state(stay),
	m_dx(0), m_dy(0), m_score(0), m_health(100), m_life(true), m_isMove(false), m_onGround(false)
{
	m_image.loadFromFile("images/" + m_fileName);
	m_image.createMaskFromColor(Color(41, 33, 59));		//������� ���� ��� �����
	m_texture.loadFromImage(m_image);
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(IntRect(0, 134, 96, 96));
}

void Player::update(float time)
{
	control(time);		// ������� ���������� ����������
	////////////////////////////////����������� ���////////////////////////////////
	switch (m_state)
	{
	case right:
		m_dx = m_speed;		//�������� ������
		m_dy = 0;
		break;
	case left:
		m_dx = -m_speed;	//�������� �����
		m_dy = 0;
		break;
	case down:
		m_dx = 0;
		m_dy = m_speed;		//�������� ����
		break;
	case up:
		m_dx = 0;
		m_dy = -m_speed;	//�������� �����
		break;
	}

	m_x += m_dx * time;		//�������� �� �
	m_y += m_dy * time;		//�������� �� y

	m_speed = 0;					//�������� ��������, ���� �������� �������������� ���� �� ������ ������� ��������
	m_sprite.setPosition(m_x , m_y );	//������������� ������� �������
	// ������������� ��������� ���������� ������� � ��� ������
	// ����� ���������� ���������� � ������� setPosition � ��������
	// �� �� ����� ������� ���� �������, � �� ��� �����
	m_sprite.setOrigin(m_width / 2, m_height / 2);
	interactionWithMap();

	if (m_health <= 0)
	{
		m_health = 0;
		m_life = false;
	}
}

void Player::interactionWithMap()
{
	for (int i = static_cast<int>(m_y / 32); i < (m_y + m_height) / 32; i++)//���������� �� ��������, �������������� � �������, �� ���� �� ���� ����������� ������� 32*32, ������� �� ���������� � 9 �����. ��� ������� ������� ����.
		for (int j = static_cast<int>(m_x / 32); j < (m_x + m_width) / 32; j++)//��� ����� �� 32, ��� ����� �������� ����� ���������, � ������� �������� �������������. (�� ���� ������ ������� 32*32, ������� ����� ������������ ������ �� ���������� ���������). � j<(x + w) / 32 - ������� ����������� ��������� �� ����. �� ���� ���������� ������ ������� ��������, ������� ������������� � ����������. ����� ������� ���� � ����� ����� ������� �� ����, ������� �� �� ������ �������� (���������������� � ������), �� ������� �������� (���������������� � ������)
		{
			if (TileMap[i][j] == '0')//���� ��� ��������� ������������� ������� 0 (�����), �� ��������� "����������� ��������" ���������:
			{
				if (m_dy > 0)//���� �� ��� ����,
				{
					m_y = i * 32 - m_height;//�� �������� ���������� ����� ���������. ������� �������� ���������� ������ ���������� �� �����(�����) � ����� �������� �� ������ ������� ���������.
				}
				if (m_dy < 0)
				{
					m_y = static_cast<float>(i * 32 + 32);//���������� � ������� �����. dy<0, ������ �� ���� ����� (���������� ���������� ������)
				}
				if (m_dx > 0)
				{
					m_x = j * 32 - m_width;//���� ���� ������, �� ���������� � ����� ����� (������ 0) ����� ������ ���������
				}
				if (m_dx < 0)
				{
					m_x = static_cast<float>(j * 32 + 32);	//���������� ���� �����
				}
			}

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

// �������� � �������� ��������
void Player::control(float time)
{
	if (m_life)
	{
		// ���������� ����������, ���� ������ ������
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			m_state = up;
			m_speed = 0.1f;
			moveCamera(getX(), getY());
			static float currentFrame(0);		//� ������� ������ ���� ���� �� ������������� ��� ������� ���������� ������
			currentFrame += 0.005f * time;
			if (currentFrame > 3)
				currentFrame -= 3;
			m_sprite.setTextureRect(IntRect(96 * static_cast<int>(currentFrame) + 5, 288 + 5, 90, 90));	// ����� ������ ��������
		}
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			m_state = down;
			m_speed = 0.1f;
			moveCamera(getX(), getY());
			static float currentFrame(0);
			currentFrame += 0.005f * time;
			if (currentFrame > 3) currentFrame -= 3;
			m_sprite.setTextureRect(IntRect(96 * static_cast<int>(currentFrame) + 5, 0 + 5, 90, 90));
		}
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			m_state = left;
			m_speed = 0.1f;
			moveCamera(getX(), getY());
			static float currentFrame(0);
			currentFrame += 0.005f * time;
			if (currentFrame > 3) currentFrame -= 3;
			m_sprite.setTextureRect(IntRect(96 * static_cast<int>(currentFrame) + 5, 96 +5, 90, 90));
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			m_state = right;
			m_speed = 0.1f;
			moveCamera(getX(), getY());
			static float currentFrame(0);
			currentFrame += 0.005f * time;
			if (currentFrame > 3) currentFrame -= 3;
			m_sprite.setTextureRect(IntRect(96 * static_cast<int>(currentFrame) + 5, 192 + 5, 90, 90));
		}
	}
}

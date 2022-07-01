#include "Player.h"

Player::Player(Image& image, float X, float Y, int W, int H, const String& name) : Entity(image, X, Y, W, H, name)
{
	m_score = 0;
	m_state = stay;
	if (name == "Player1")
	m_sprite.setTextureRect(IntRect(4, 19, m_width, m_height));
}

void Player::control(const float time)
{
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		m_state = left;
		m_speed = 0.1f;
		moveCamera(m_x, m_y);
		//static float currentFrame(0);
		//currentFrame += 0.005*time;
		//if (currentFrame > 3) currentFrame -= 3;
		//m_sprite.setTextureRect(IntRect(295 * int(currentFrame), 103, 46, 30));
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		m_state = right;
		m_speed = 0.1f;
		moveCamera(m_x, m_y);
		//static float currentFrame(1);
		//currentFrame += 0.005f * time;
		//if (currentFrame > 5)
		//	currentFrame -= 4;
		//m_sprite.setTextureRect(IntRect(296 * int(currentFrame), 103, 40, 30));
	}

	if ((Keyboard::isKeyPressed(Keyboard::Up)) && (m_onGround)) {
		m_state = jump;
		m_dy = -0.4f;
		m_onGround = false;	// �� ��������� ����� ������,�������� � ��������, ��� �� �� �� �����
		moveCamera(m_x, m_y);
		//currentFrame += 0.005*time;
		//if (currentFrame > 3) currentFrame -= 3;
		//p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 307, 96, 96));
	}

	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		m_state = down;
		m_speed = 0.1f;
		moveCamera(m_x, m_y);
		//currentFrame += 0.005*time;
		//if (currentFrame > 3) currentFrame -= 3;
		//p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 0, 96, 96));
	}
}

void Player::update(const float time)
{
	control(time);//������� ���������� ����������
	switch (m_state)//��� �������� ��������� �������� � ����������� �� ���������
	{
	case right:
		m_dx = m_speed;
		break;//��������� ���� ������
	case left:
		m_dx = -m_speed;
		break;//��������� ���� �����
	case up:
		break;//����� ��������� �������� ������ (�������� �� ��������)
	case down:
		break;//����� ��������� �� ����� ������ ��������� (�������� �� ��������)
	case jump:
		break;//����� ����� ���� ����� ��������
	case stay:
		break;//� ����� ����		
	}

	m_x += m_dx * time;
	checkCollisionWithMap(m_dx, 0);//������������ ������������ �� �
	m_y += m_dy * time;
	checkCollisionWithMap(0, m_dy);//������������ ������������ �� Y
	if (!m_isMove)
		m_speed = 0;
	m_sprite.setPosition(m_x + m_width / 2, m_y + m_height / 2); //������ ������� ������� � ����� ��� ������
	if (m_health <= 0)
		m_life = false;
	m_dy = m_dy + 0.0005f * time;//������ ���������� � �����
	if (!m_onGround)	// ���� �� � ������, ������ ������ �� ����������
		moveCamera(m_x, m_y);
}

void Player::checkCollisionWithMap(float Dx, float Dy)
{
	for (int i = static_cast<int>(m_y / 32); i < (m_y + m_height) / 32; i++)//���������� �� ��������� �����
		for (int j = static_cast<int>(m_x / 32); j < (m_x + m_width) / 32; j++)
		{
			if (TileMap[i][j] == '0')//���� ������� ��� ������ �����? ��
			{
				if (Dy > 0)	// �� Y ����=>���� � ���(����� �� �����) ��� ������. � ���� ������ ���� ���������� ...
				{			//... ��������� � ��������� ��� �� �����, ��� ���� ������� ��� �� �� ����� ��� ����� ����� ����� �������
					m_y = static_cast<float>(i * 32 - m_height);
					m_dy = 0.f;
					m_onGround = true;
				}
				if (Dy < 0)	//������������ � �������� ������ �����(����� � �� �����������)
				{
					m_y = static_cast<float>(i * 32 + 32);
					m_dy = 0.f;
				}
				if (Dx > 0)	//� ������ ����� �����
					m_x = static_cast<float>(j * 32 - m_width);
				if (Dx < 0)	// � ����� ����� �����
					m_x = static_cast<float>(j * 32 + 32);
			}
		}
}

Entity::Entity(Image& image, float X, float Y, int width, int height, const String& name) :
	m_width(width), m_height(height), m_dx(0), m_dy(0), m_x(X), m_y(Y), m_speed(0), m_name(name),
	m_moveTimer(0), m_health(100), m_life(true), m_isMove(false), m_onGround(false)
{
	m_texture.loadFromImage(image);
	m_sprite.setTexture(m_texture);
	//���������� ����� ������� ��������� �������, �� ������ �������� ���� � �������� 
	m_sprite.setOrigin(static_cast<float>(m_width / 2), static_cast<float>(m_height / 2));
}

Enemy::Enemy(Image& image, float X, float Y, int W, int H, const String& name) : Entity(image, X, Y, W, H, name)
{
	if (name == "EasyEnemy")
		m_sprite.setTextureRect(IntRect(0, 0, m_width, m_height));
	m_dx = 0.1f;	// ���� ��������� (���� ������ ������ ���������)
}

void Enemy::checkCollisionWithMap(const float Dx, const float Dy)
{
	for (int i = static_cast<int>(m_y / 32); i < (m_y + m_height) / 32; i++)//���������� �� ��������� �����
		for (int j = static_cast<int>(m_x / 32); j < (m_x + m_width) / 32; j++)
		{
			if (TileMap[i][j] == '0')//���� ������� ��� ������ �����? ��
			{
				if (Dy > 0)	// �� Y ����=>���� � ���(����� �� �����) ��� ������. � ���� ������ ���� ���������� ...
				{			//... ��������� � ��������� ��� �� �����, ��� ���� ������� ��� �� �� ����� ��� ����� ����� ����� �������
					m_y = static_cast<float>(i * 32 - m_height);
					m_dy = 0.f;
					m_onGround = true;
				}
				if (Dy < 0)	//������������ � �������� ������ �����(����� � �� �����������)
				{
					m_y = static_cast<float>(i * 32 + 32);
					m_dy = 0.f;
				}
				if (Dx > 0)	//� ������ ����� �����
				{
					m_x = static_cast<float>(j * 32 - m_width);
					m_dx = -0.1f;
					m_sprite.scale(-1, 1);
				}
				if (Dx < 0)	// � ����� ����� �����
				{
					m_x = static_cast<float>(j * 32 + 32);
					m_dx = 0.1f;
					m_sprite.scale(-1, 1);
				}
			}
		}
}

void Enemy::update(const float time)
{
	if (m_name == "EasyEnemy")
	{
		m_x += m_dx * time;
		checkCollisionWithMap(m_dx, 0);//������������ ������������ �� �
		m_y += m_dy * time;
		checkCollisionWithMap(0, m_dy);//������������ ������������ �� Y
		m_sprite.setPosition(m_x + m_width / 2, m_y + m_height / 2); //������ ������� ������� � ����� ��� ������
		if (m_health <= 0)
			m_life = false;
		m_dy = m_dy + 0.0005f * time;//������ ���������� � �����
	}
}

#include "Player.h"

Player::Player(String fileName, float x, float y, float width, float height) :
	m_fileName(fileName), m_x(x), m_y(y), m_width(width), m_height(height)
{
	m_image.loadFromFile("images/" + m_fileName);
	m_image.createMaskFromColor(Color(41, 33, 59));		//Удаляем тень под львом
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
		m_dx = m_speed;		//Смещение вправо
		m_dy = 0;
		break;
	case 1:
		m_dx = -m_speed;	//Смещение влево
		m_dy = 0;
		break;
	case 2:
		m_dx = 0;
		m_dy = m_speed;		//Смещение вниз
		break;
	case 3:
		m_dx = 0;
		m_dy = -m_speed;	//Смещение вверх
		break;
	}

	m_x += m_dx * time;		//Смещение по х
	m_y += m_dy * time;		//Смещение по y

	m_speed = 0;					//Зануляем скорость, чтоб персонаж останавливался если не нажаты клавиши движения
	m_sprite.setPosition(m_x, m_y);	//Устанавливаем позицию спрайта
}

void Player::moveUp(int dir, float speed, float time)
{
	m_dir = dir;
	m_speed = speed;
	//static int currentFrame(0);
	m_currentFrame += 0.08f * time;
	if (m_currentFrame > 3)
		m_currentFrame -= 3;
	std::cout << m_currentFrame << '\n';
	m_sprite.setTextureRect(IntRect(96 * static_cast<int>(m_currentFrame), 288, 96, 96));
}

void Player::moveDown(int dir, float speed, float time)
{
	m_dir = dir;
	m_speed = speed;
	static int currentFrame(0);
	currentFrame += 0.005f * time;
	if (currentFrame > 3) currentFrame -= 3;
	m_sprite.setTextureRect(IntRect(96 * static_cast<int>(currentFrame), 0, 96, 96));
}

void Player::moveLeft(int dir, float speed, float time)
{
	m_dir = dir;
	m_speed = speed;
	int currentFrame(0);
	currentFrame += 0.005f * time;
	if (currentFrame > 3) currentFrame -= 3;
	m_sprite.setTextureRect(IntRect(96 * static_cast<int>(currentFrame), 96, 96, 96));
}

void Player::moveRight(int dir, float speed, float time)
{
	m_dir = dir;
	m_speed = speed;
	int currentFrame(0);
	currentFrame += 0.005f * time;
	if (currentFrame > 3) currentFrame -= 3;
	m_sprite.setTextureRect(IntRect(96 * static_cast<int>(currentFrame), 192, 96, 96));
}

#include "Player.h"


Player::Player(String fileName, float x, float y, float width, float height) :
	m_fileName(fileName), m_x(x), m_y(y), m_width(width), m_height(height)
{
	m_dx = 0;
	m_dy = 0;
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

void Player::moveUp(float speed, float time)
{
	m_dir = 3;
	m_speed = speed;
	static float currentFrame(0);		//У каждого метода свой дабы не суммировались при нажатии нескольких клавиш
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
	int tile_x(m_x / 32);
	int tile_y(m_y / 32);
	if (m_dx > 0)
		if (TileMap[tile_x][tile_y] == '0')
			m_x = tile_x * 32 - m_height;
	if (m_dx < 0)
		if (TileMap[tile_x][tile_y] == '0')
			m_x = tile_x * 32 + m_height;
	if (m_dy > 0)
		if (TileMap[tile_x][tile_y] == '0')
			m_y = tile_y * 32 - m_width;
	if (m_dy > 0)
		if (TileMap[tile_x][tile_y] == '0')
			m_y = tile_y * 32 + m_width;
}

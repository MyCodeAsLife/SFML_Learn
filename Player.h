#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Player
{
public:
	float m_x, m_y;
	float m_dx, m_dy;
	float m_width, m_height;
	float m_speed;
	int m_dir = 0;
	std::string m_file;
	Image m_image;
	Texture m_texture;
	Sprite m_sprite;

public:
	Player(const std::string& file, int x, int y, float width, float height);
	void update(float time);

};

Player::Player(const std::string& file, int x, int y, float width, float height) :
	m_file(file), m_x(x), m_y(y), m_width(width), m_height(height), m_dx(0), m_dy(0),
	m_speed(0), m_dir(0)
{
	m_image.loadFromFile("resources/images/" + m_file);
	m_image.createMaskFromColor(Color(41, 33, 59));
	m_texture.loadFromImage(m_image);
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(IntRect(m_width, m_height, m_width, m_height));
}

inline void Player::update(float time)
{
	switch (m_dir)
	{
	case 0:
		m_dx = m_speed;
		m_dy = 0;
		break;
	case 1:
		m_dx = -m_speed;
		m_dy = 0;
		break;
	case 2:
		m_dx = 0;
		m_dy = m_speed;
		break;
	case 3:
		m_dx = 0;
		m_dy = -m_speed;
		break;
	}

	m_x += m_dx * time;
	m_y += m_dy * time;
	m_speed = 0;
	m_sprite.setPosition(m_x, m_y);
}

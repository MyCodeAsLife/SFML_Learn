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
	int m_score = 0;
	int m_health;
	std::string m_file;
	Image m_image;
	Texture m_texture;
	Sprite m_sprite;

public:
	Player(const std::string& file, int x, int y, float width, float height, int health);
	void update(float time);
	void collision(int dir);
	float getX() { return m_x; }
	float getY() { return m_y; }

};

Player::Player(const std::string& file, int x, int y, float width, float height, int health = 100) :
	m_file(file), m_x(static_cast<float>(x)), m_y(static_cast<float>(y)), m_width(width),
	m_height(height), m_dx(0), m_dy(0), m_speed(0), m_dir(0), m_score(0), m_health(health)
{
	m_image.loadFromFile("resources/images/" + m_file);
	m_image.createMaskFromColor(Color(41, 33, 59));
	m_texture.loadFromImage(m_image);
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(IntRect(static_cast<int>(m_width), static_cast<int>(m_height),
		static_cast<int>(m_width), static_cast<int>(m_height)));
	m_sprite.setOrigin(m_width / 2, m_height / 2);
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
	collision(0);

	m_y += m_dy * time;
	collision(1);

	m_speed = 0;
	m_sprite.setPosition(m_x, m_y);
}

inline void Player::collision(int dir)
{
	for (int i((m_y /*- (m_height /4)*/) / 32); i < (m_y + (m_height / 2)) / 32; ++i)
		for (int j((m_x - (m_width / 4)) / 32); j < (m_x + (m_width / 4)) / 32; ++j)
		{
			if (TileMap[i][j] == '0')
			{
				if (m_dy > 0 && dir)
				{
					m_y = i * 32 - (m_height/2);
				}
				if (m_dy < 0 && dir)
				{
					m_y = i * 32 + 32 /*+ (m_height /4)*/;
				}
				if (m_dx > 0 && !dir)
				{
					m_x = j * 32 - (m_width / 4);
				}
				if (m_dx < 0 && !dir)
				{
					m_x = j * 32 + 32 + (m_width / 4);
				}
			}
			if (TileMap[i][j] == 's')
			{
				TileMap[i][j] = ' ';
				++m_score;
			}
			if (TileMap[i][j] == 'h')
			{
				TileMap[i][j] = ' ';
				m_health += 20;
			}
			if (TileMap[i][j] == 'f')
			{
				TileMap[i][j] = ' ';
				m_health -= 40;
			}
		}
}

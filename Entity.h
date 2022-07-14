#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

extern const unsigned SPRITE_HEIGHT;
extern const unsigned SPRITE_WIDTH;

class Entity
{
public:
	float m_x, m_y;
	float m_dx, m_dy;
	float m_width, m_height;
	float m_speed;
	float m_moveTimer;
	int m_health;
	bool m_life;
	std::string m_name;
	Image m_image;
	Texture m_texture;
	Sprite m_sprite;
	bool m_onGround;
	float m_currentFrame;
	enum class State {
		left,
		right,
		up,
		down,
		jump,
		stay,
	} m_state;

public:
	Entity(const std::string& name, const Image& image, int x, int y, float width, float height, int health);
	virtual void update(float time);
	virtual void collision(int dir);
	float getX() { return m_x; }
	float getY() { return m_y; }
};

Entity::Entity(const std::string& name, const Image& image, int x, int y, float width, float height, int health) :
	m_image(image), m_name(name), m_x(static_cast<float>(x)), m_y(static_cast<float>(y)), m_width(width),
	m_height(height), m_health(health), m_life(true), m_speed(0), m_onGround(false), m_currentFrame(0),
	m_state(State::stay), m_dx(0), m_dy(0), m_moveTimer(0)
{
	if (m_name == "Hero")
		m_image.createMaskFromColor(Color(41, 33, 59));
	m_texture.loadFromImage(m_image);
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_width / 2, m_height / 2);
}

inline void Entity::update(float time)
{
	switch (m_state)
	{
	case State::right:
		m_dx = m_speed;
		break;
	case State::left:
		m_dx = -m_speed;
		break;
	case State::up:
		break;
	case State::down:
		break;
	case State::jump:
		break;
	case State::stay:
		m_dx = 0;
		break;
	}

	m_x += m_dx * time;
	collision(0);

	m_dy += 0.001f * time;
	m_y += m_dy * time;
	collision(1);

	m_speed = 0;
	m_sprite.setPosition(m_x, m_y);
}

inline void Entity::collision(int dir)
{
	for (int i(static_cast<int>((m_y - m_height / 2) / SPRITE_HEIGHT)); i < (m_y + m_height / 2) / SPRITE_HEIGHT; ++i)
		for (int j(static_cast<int>((m_x - m_width / 2) / SPRITE_WIDTH)); j < (m_x + m_width / 2) / SPRITE_WIDTH; ++j)
		{
			if (TileMap[i][j] == '0')
			{
				if (m_dy > 0 && dir)	// Под ногами
				{
					m_y = i * SPRITE_HEIGHT - m_height / 2;
					m_dy = 0;
					m_state = State::stay;
					m_onGround = true;
				}
				if (m_dy < 0 && dir)	// Над головой
				{
					m_y = i * SPRITE_HEIGHT + SPRITE_HEIGHT + (m_height / 2);
					m_dy = 0;
				}
				if (m_dx > 0 && !dir)
				{
					m_x = j * SPRITE_WIDTH - (m_width / 2);
					m_dx = 0;
				}
				if (m_dx < 0 && !dir)
				{
					m_x = j * SPRITE_WIDTH + SPRITE_WIDTH + (m_width / 2);
					m_dx = 0;
				}
			}
		}
}

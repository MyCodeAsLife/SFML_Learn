#pragma once
#include "Entity.h"

extern const unsigned SPRITE_HEIGHT;
extern const unsigned SPRITE_WIDTH;

using namespace sf;

class Player : public Entity
{
public:
	int m_score = 0;

public:
	Player(const std::string& name, const Image& image, int x, int y, float width, float height, int health);
	void update(float time) override;
	void collision(int dir) override;
	void control(float time);

};

Player::Player(const std::string& name, const Image& image, int x, int y, float width, float height, int health = 100) :
	Entity(name, image, x, y, width, height, health), m_score(0)
{
	m_sprite.setTextureRect(IntRect(0, 135, static_cast<int>(m_width), static_cast<int>(m_height)));
}

inline void Player::update(float time)
{
	control(time);

	this->Entity::update(time);
}

inline void Player::collision(int dir)
{
	for (int i(static_cast<int>((m_y - m_height / 2) / SPRITE_HEIGHT)); i < (m_y + m_height / 2) / SPRITE_HEIGHT; ++i)
		for (int j(static_cast<int>((m_x - m_width / 2) / SPRITE_WIDTH)); j < (m_x + m_width / 2) / SPRITE_WIDTH; ++j)
		{
			if (TileMap[i][j] == '0')
			{
				if (m_dy > 0 && dir)	// Под ногами
				{
					m_y = i * SPRITE_HEIGHT - m_height/2;
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

inline void Player::control(float time)
{
	//// Управление с клавиатуры
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		m_state = State::right;
		m_speed = 0.2f;
		m_currentFrame += 0.008f * time;
		if (m_currentFrame > 3)
			m_currentFrame = 0;
		m_sprite.setTextureRect(IntRect(96 * static_cast<int>(m_currentFrame), 232, 96, 56));
	}
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		m_state = State::left;
		m_speed = 0.2f;
		m_currentFrame += 0.008f * time;
		if (m_currentFrame > 3)
			m_currentFrame = 0;
		m_sprite.setTextureRect(IntRect(96 * static_cast<int>(m_currentFrame), 135, 96, 56));
	}
	if (Keyboard::isKeyPressed(Keyboard::Up) && m_onGround)
	{
		m_state = State::jump;
		m_dy = -0.6f;
		m_onGround = false;
	}
	if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		m_state = State::down;
		m_speed = 0.1f;
	}
}

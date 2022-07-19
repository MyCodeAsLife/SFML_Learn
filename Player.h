#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
	int m_score = 0;
	bool m_onControl;

public:
	Player(const std::string& name, const Image& image, Level& lvl, int x, int y, int width, int height, int health);
	void update(float time) override;
	void collision(int dir) override;
	void control(float time);

};

Player::Player(const std::string& name, const Image& image, Level& lvl, int x, int y, int width, int height, int health = 100) :
	Entity(name, image, x, y, width, height, health), m_score(0), m_onControl(true)
{
	m_obj = lvl.GetAllObjects();
	m_sprite.setTextureRect(IntRect(5, 18, m_rect.width, m_rect.height));
	m_sprite.setPosition(m_rect.left, m_rect.top);
}

inline void Player::update(float time)
{
	if (m_onControl)
		control(time);
	else
	{
		m_moveTimer += time;
		if ((m_moveTimer / 1000) > 0.5)
		{
			m_onControl = true;
			m_moveTimer = 0;
		}
	}

	switch (m_state)
	{
	case State::right:
		m_dx = m_speed;
		if (m_flip)
		{
			m_flip = false;
			m_sprite.scale(-1, 1);
		}
		break;
	case State::left:
		m_dx = -m_speed;
		if (!m_flip)
		{
			m_sprite.scale(-1, 1);
			m_flip = true;
		}
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

	m_rect.left += m_dx * time;
	collision(0);

	m_dy += 0.0015f * time;
	m_rect.top += m_dy * time;
	collision(1);

	if (m_dy > 0)
		m_onGround = false;
	if (m_onGround)
		m_speed = 0;
	m_sprite.setPosition(m_rect.left + m_sprite.getTextureRect().width/2, m_rect.top + m_sprite.getTextureRect().height/2);
}

inline void Player::collision(int dir)
{
	for (int i(0); i < m_obj.size(); ++i)
		if (getRect().intersects(m_obj[i].rect))
		{
			if (m_obj[i].name == "solid")
			{
				if (m_dy > 0 && dir)	// Под ногами
				{
					m_rect.top = static_cast<float>(m_obj[i].rect.top - m_sprite.getTextureRect().height/* / 2*/);
					m_dy = 0;
					m_state = State::stay;
					m_onGround = true;
				}
				else if (m_dy < 0 && dir)	// Над головой
				{
					m_rect.top = static_cast<float>(m_obj[i].rect.top + m_obj[i].rect.height /*+ (m_sprite.getTextureRect().height / 2)*/);
					m_dy = 0;
				}
				if (m_dx > 0 && !dir)
				{
					m_rect.left = static_cast<float>(m_obj[i].rect.left - (m_sprite.getTextureRect().width/* / 2*/));
					m_dx = 0;
				}
				else if (m_dx < 0 && !dir)
				{
					m_rect.left = static_cast<float>(m_obj[i].rect.left + m_obj[i].rect.width /*+ (m_sprite.getTextureRect().width / 2)*/);
					m_dx = 0;
				}
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
		m_currentFrame += 0.013f * time;
		if (m_currentFrame > 11)
			m_currentFrame = 0;
		m_sprite.setTextureRect(IntRect(45 * static_cast<int>(m_currentFrame) + 295, 102, 43, 30));
	}
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		m_state = State::left;
		m_speed = 0.2f;
		m_currentFrame += 0.013f * time;
		if (m_currentFrame > 11)
			m_currentFrame = 0;
		m_sprite.setTextureRect(IntRect(45 * static_cast<int>(m_currentFrame) + 295, 102, 43, 30));
	}
	if (Keyboard::isKeyPressed(Keyboard::Up) && m_onGround)
	{
		m_state = State::jump;
		m_dy = -0.7f;
		m_onGround = false;
	}
	if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		m_state = State::down;
		m_speed = 0.1f;
	}
}

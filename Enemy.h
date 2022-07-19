#pragma once

#include "Entity.h"

class Enemy : public Entity
{
public:
	Enemy(const std::string& name, const Image& image, Level& lvl, int x, int y, int width, int height, int health);
	void update(float time) override;
	void collision(int dir) override;
};

Enemy::Enemy(const std::string& name, const Image& image, Level& lvl, int x, int y, int width, int height, int health = 100) :
	Entity(name, image, x, y, width, height, health)
{
	m_obj = lvl.GetObjects("solid");
	m_sprite.setTextureRect(IntRect(0, 0, width, height));
	m_dx = 0.1f;
	m_sprite.setPosition(m_rect.left, m_rect.top);
}

inline void Enemy::update(float time)
{
	m_rect.left += m_dx * time;
	collision(0);

	m_dy += 0.001f * time;
	m_rect.top += m_dy * time;
	collision(1);

	m_speed = 0;
	m_sprite.setPosition(m_rect.left + m_sprite.getTextureRect().width / 2, m_rect.top + m_sprite.getTextureRect().height / 2);
}

inline void Enemy::collision(int dir)
{
	for (int i(0); i < m_obj.size(); ++i)
		if (getRect().intersects(m_obj[i].rect))
		{
				if (m_dy > 0 && dir)	// Под ногами
				{
					m_rect.top = static_cast<float>(m_obj[i].rect.top - m_sprite.getTextureRect().height);
					m_dy = 0;
					m_state = State::stay;
					m_onGround = true;
				}
				else if (m_dy < 0 && dir)	// Над головой
				{
					m_rect.top = static_cast<float>(m_obj[i].rect.top + m_obj[i].rect.height);
					m_dy = 0;
				}
				if (m_dx > 0 && !dir)
				{
					m_rect.left = static_cast<float>(m_obj[i].rect.left - (m_sprite.getTextureRect().width));
					m_dx = -m_dx;
					m_sprite.scale(-1, 1);
				}
				else if (m_dx < 0 && !dir)
				{
					m_rect.left = static_cast<float>(m_obj[i].rect.left + m_obj[i].rect.width);
					m_dx = -m_dx;
					m_sprite.scale(-1, 1);
				}
		}
}

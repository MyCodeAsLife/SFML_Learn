#pragma once

class Bullet : public Entity
{
private:
	void collision(int dir) override {}

public:
	int m_direction;


public:
	Bullet(const std::string& name, const Image& image, Level& lvl, float x, float y, float width, float height, int direction);
	void update(float time) override;

};

Bullet::Bullet(const std::string& name, const Image& image, Level& lvl, float x, float y, float width, float height, int direction) :
	Entity(name, image, x, y, width, height), m_direction(direction)
{
	m_obj = lvl.GetObjects("solid");
	m_speed = 0.8f;
}

inline void Bullet::update(float time)
{
	switch (m_direction)
	{
	case 0:
		m_dx = -m_speed;
		m_dy = 0;
		break;
	case 1:
		m_dx = m_speed;
		m_dy = 0;
		break;
	case 2:
		m_dx = 0;
		m_dy = -m_speed;
		break;
	case 3:	// -------------------Заглушка
		m_dx = 0;
		m_dy = -m_speed;
		break;
	case 4:	// -------------------Заглушка
		m_dx = 0;
		m_dy = -m_speed;
		break;
	case 5:	// -------------------Заглушка
		m_dx = 0;
		m_dy = -m_speed;
		break;
	case 6:
		m_dx = m_speed;
		m_dy = -m_speed;
		break;
	}

	m_rect.left += m_dx * time;
	m_rect.top += m_dy * time;

	// --------------------------Дописать правый и нижний
	// Следующие проверки, чтобы пули несмогли случайно покинуть пределы карты (левый и верхний)
	if (m_rect.left <= 0)
	{
		m_rect.left = 1;
		m_life = false;
	}
	if (m_rect.top <= 0)
	{
		m_rect.top = 1;
		m_life = false;
	}

	for (int i(0); i < m_obj.size(); ++i)
	{
		if (getRect().intersects(m_obj[i].rect))
		{
			m_life = false;
		}
	}

	m_sprite.setPosition(m_rect.left + m_rect.width, m_rect.top + m_rect.height / 2);
}

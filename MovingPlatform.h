#pragma once

class MovingPlatform : public Entity
{
private:
	void collision(int dir) override {}

public:
	MovingPlatform(const std::string& name, const Image& image, float x, float y, float width, float height);
	void update(float time) override;
	
};

MovingPlatform::MovingPlatform(const std::string& name, const Image& image, float x, float y, float width, float height) :
	Entity(name, image, x, y, width, height)
{
	m_sprite.setTextureRect(IntRect(0, 0, static_cast<int>(width), static_cast<int>(height)));
	m_dx = 0.08f;
}

inline void MovingPlatform::update(float time)
{
	m_rect.left += m_dx * time;
	m_moveTimer += time;
	if (m_moveTimer > 2000)
	{
		m_dx = -m_dx;
		m_moveTimer = 0;
	}
	m_sprite.setPosition(m_rect.left + m_rect.width / 2, m_rect.top + m_rect.height / 2);
}

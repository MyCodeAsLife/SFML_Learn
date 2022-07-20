#pragma once

class LifeBar
{
public:
	Image m_image;
	Texture m_texture;
	Sprite m_sprite;
	int m_max;
	RectangleShape m_bar;

public:
	LifeBar();
	void update(int health);
	void draw(RenderWindow& window);

};

LifeBar::LifeBar()
{
	m_image.loadFromFile("resources/images/life.png");
	m_image.createMaskFromColor(Color(50, 96, 166));
	m_texture.loadFromImage(m_image);
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(IntRect(783, 2, 15, 84));

	m_bar.setFillColor(Color(0, 0, 0));
	m_max = 100;
}

inline void LifeBar::update(int health)
{
	if (health > 0)
		if (health < m_max)
			m_bar.setSize(Vector2f(10, (m_max - health) * 70 / m_max));
}

inline void LifeBar::draw(RenderWindow& window)
{
	Vector2f center = window.getView().getCenter();
	Vector2f size = window.getView().getSize();

	m_sprite.setPosition(center.x - size.x / 2 + 10, center.y - size.y / 2 + 30);
	m_bar.setPosition(center.x - size.x / 2 + 14, center.y - size.y / 2 + 34);

	window.draw(m_sprite);
	window.draw(m_bar);
}

#pragma once

class Entity
{
public:
	FloatRect m_rect;
	float m_dx, m_dy;
	float m_speed;
	float m_moveTimer;
	bool m_life;
	bool m_flip;
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
		right_top,
	} m_state;
	std::vector<Object> m_obj;

public:
	Entity(const std::string& name, const Image& image, float x, float y, float width, float height);
	virtual void update(float time) = 0;
	virtual void collision(int dir) = 0;
	FloatRect getRect() { return m_rect; }
};

Entity::Entity(const std::string& name, const Image& image, float x, float y, float width, float height) :
	m_image(image), m_name(name), m_flip(false), m_life(true),m_speed(0), m_onGround(false),
	m_currentFrame(0), m_state(State::stay), m_dx(0), m_dy(0), m_moveTimer(0)
{
	m_rect.left = x;
	m_rect.top = y;
	m_rect.width = width;
	m_rect.height = height;

	if (m_name == "Hero")
		m_image.createMaskFromColor(Color(41, 33, 59));
	m_texture.loadFromImage(m_image);
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(width / 2, height / 2);
}

//inline void Entity::update(float time)
//{
//	switch (m_state)
//	{
//	case State::right:
//		m_dx = m_speed;
//		if (m_flip)
//		{
//			m_flip = false;
//			m_sprite.scale(-1, 1);
//		}
//		break;
//	case State::left:
//		m_dx = -m_speed;
//		if (!m_flip)
//		{
//			m_sprite.scale(-1, 1);
//			m_flip = true;
//		}
//		break;
//	case State::up:
//		break;
//	case State::down:
//		break;
//	case State::jump:
//		break;
//	case State::stay:
//		m_dx = 0;
//		break;
//	}
//
//	m_x += m_dx * time;
//	collision(0);
//
//	m_dy += 0.001f * time;
//	m_y += m_dy * time;
//	collision(1);
//
//	m_speed = 0;
//	m_sprite.setPosition(m_x, m_y);
//}

//inline void Entity::collision(int dir)
//{
//	for (int i(static_cast<int>((m_y - m_sprite.getTextureRect().height / 2) / SPRITE_HEIGHT)); i < (m_y + m_sprite.getTextureRect().height / 2) / SPRITE_HEIGHT; ++i)
//		for (int j(static_cast<int>((m_x - m_sprite.getTextureRect().width / 2) / SPRITE_WIDTH)); j < (m_x + m_sprite.getTextureRect().width / 2) / SPRITE_WIDTH; ++j)
//		{
//			if (TileMap[i][j] == '0')
//			{
//				if (m_dy > 0 && dir)	// Под ногами
//				{
//					m_y = static_cast<float>(i * SPRITE_HEIGHT - m_sprite.getTextureRect().height / 2);
//					m_dy = 0;
//					m_state = State::stay;
//					m_onGround = true;
//				}
//				else if (m_dy < 0 && dir)	// Над головой
//				{
//					m_y = static_cast<float>(i * SPRITE_HEIGHT + SPRITE_HEIGHT + (m_sprite.getTextureRect().height / 2));
//					m_dy = 0;
//				}
//				if (m_dx > 0 && !dir)
//				{
//					m_x = static_cast<float>(j * SPRITE_WIDTH - (m_sprite.getTextureRect().width / 2));
//					m_dx = 0;
//				}
//				else if (m_dx < 0 && !dir)
//				{
//					m_x = static_cast<float>(j * SPRITE_WIDTH + SPRITE_WIDTH + (m_sprite.getTextureRect().width / 2));
//					m_dx = 0;
//				}
//			}
//		}
//}

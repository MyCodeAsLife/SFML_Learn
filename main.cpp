#include "Header.h"
#include "View.h"
#include "Level.h"
#include <list>

const unsigned c_wWidth(960);		// ������ ���� (640)
const unsigned c_wHeight(480);		// ������ ���� (480)
const unsigned c_wFPS(120);			// ��������� ������ � ������� (FPS)
const unsigned c_Speed(600);		// �������� ���� (��� ������ �����, ��� ���� ��������)

//	������������ ����� ��� ������
class Entity
{
public:
	std::vector<Object> m_obj;	// ������ �������� ����� (���������� ������ ����� ���������, ����� ������ ������ ������� �� ����������� �������)
	int m_width, m_height;
	float m_dx, m_dy;		// ��������� �� ����
	float m_x, m_y;			// ��������� �����
	float m_speed;			// �������� �����
	float m_moveTimer;		// ������ ��� ��������� ��������
	int m_health;			// �������� �����
	bool m_life, m_isMove, m_onGround; // ���������� ��������� ���������
	String m_name;
	Texture m_texture;
	Sprite m_sprite;

public:
	Entity(Image& image, const String& name, float X, float Y, int width, int height);
	FloatRect getRect() { return FloatRect(m_x, m_y, m_width, m_height); } // ��� ������� ����� ��� �������� ������������
	virtual void update(const float time) = 0;
};

//	����� �������� ���������
class Player : public Entity
{
public:
	int m_score;
	enum { left, right, up, down, jump, stay } m_state;//��������� ��� ������������ - ��������� �������

public:
	Player(Image& image, const String& name, Level& lev, float X, float Y, int W, int H);
	void control(const float time);
	void update(const float time);
	float getplayercoordinateX() { return m_x; }
	float getplayercoordinateY() { return m_y; }
	void checkCollisionWithMap(float Dx, float Dy);	//� ��� �������� ������������ � ������

};

// ����� ����������
class Enemy :public Entity
{
public:
	Enemy(Image& image, const String& name, Level& lvl, float X, float Y, int W, int H);
	void checkCollisionWithMap(const float Dx, const float Dy);
	void update(const float time);

};

class SpriteManager {//��� ����� �� ��������� �����,����� �� �������� �������� �� ��� ���������)
public:
	Image m_image;
	Texture m_texture;
	Sprite m_sprite;
	String m_name;
	String m_file;
	int m_widthOfSprite;
	int m_heightOfSprite;
	SpriteManager(String file, String Name) {
		m_file = file;
		m_name = Name;
		m_image.loadFromFile("images/" + m_file);
		m_texture.loadFromImage(m_image);
		m_sprite.setTexture(m_texture);
	}
};

////////////////////////////////////////////START MAIN///////////////////////////////////////////////////////////////
int main()
{
	RenderWindow window(VideoMode(c_wWidth, c_wHeight), "SFML-Learn");
	window.setFramerateLimit(c_wFPS);
	// ������������� ������ (������ �������� ������ ��� ������� ����)
	camera.reset(FloatRect(0, 0, c_wWidth, c_wHeight));

	//��� ������ � ������
	Level lvl;
	lvl.LoadFromFile("map.tmx");

	Clock clock;
	// ��������/������������� ��������� ���������� ���������
	Object player_obj = lvl.GetObject("player");		// �������� ���������� ������� player
	// �����
	Image player_image;
	player_image.loadFromFile("images/MilesTailsPrower.gif");
	Player p1(player_image, "Player1", lvl, player_obj.rect.left, player_obj.rect.top, 40, 30);	// �������� � �������������� ���������� ���������
	moveCamera(p1.m_x, p1.m_y);		// ��������� ��������� ������� ������ �� ����������� ���������
	// �����
	Image easyEnemy_Image;
	easyEnemy_Image.loadFromFile("images/shamaich.png");
	easyEnemy_Image.createMaskFromColor(Color(255, 0, 0)); // ������� ��� ��������
	std::vector<Object> easyEnemy_obj_array = lvl.GetObjects("easyEnemy");	// �������� ���������� ������(��) easeEnemy
	std::list<Entity*> entity_array;		// ������ ��� ������
	std::list<Entity*>::iterator it_enemy;	// �������� ��� ����������� �� ������� ������
	for (int i(0); i < easyEnemy_obj_array.size(); ++i)	// ������� ������� ������, ������� �������� �� �����
		entity_array.push_back(new Enemy(easyEnemy_Image, "easyEnemy", lvl, easyEnemy_obj_array[i].rect.left,
			easyEnemy_obj_array[i].rect.top, 200, 97));	// �������������� ������

	// ������� ���� ����������: �����������, ���� ������� ����
	while (window.isOpen())
	{
		float time = static_cast<float>(clock.getElapsedTime().asMicroseconds());
		clock.restart();
		time /= c_Speed;		//�������� ����

		Vector2i pixelPos = Mouse::getPosition(window);		// ���������� ��������� ������������ ����
		Vector2f pos = window.mapPixelToCoords(pixelPos);	// ����������� ��������� ��������� ����, � ������� ����������

		// ������������ ������� ������� � �����
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		// ��������� ����� ����
		window.clear(Color(70, 70, 70, 0));

		// ��������� �����
		lvl.Draw(window);



		 // ��������� � �������� ����������(��)
		if (!entity_array.empty())	// ���� ���� ���������� �� ��������� ��� ���� ��������
			for (auto it = entity_array.begin(); it != entity_array.end();)
		{
			// ������������ � �����������
			if ((*it)->getRect().intersects(p1.getRect()))	//���� ������ ���������� ������������ � �������
			{
				if ((*it)->m_name == "easyEnemy")	// ���� ��������� �������� ���� "easyEnemy"
				{
					// ������� �� ����������
					if ((p1.m_dy > 0) && (p1.m_onGround == false))	// ���� �������� ������
					{
						(*it)->m_dx = 0.f;		// ������������� ����������
						p1.m_dy = -0.2f;		// ����� �����������
						(*it)->m_health = 0;	// �������� ���-�� �������� ����������
					}
					else
						p1.m_health -= 5;		// ����� �������� �����������
					// ������������ ���������� � ������� (���� ���, ���������� ������� ������)

					if ((*it)->m_dx < 0 || p1.m_dx > 0)	// ��������� ������, ����� �����
					{
						(*it)->m_x = p1.m_x + p1.m_width;
						(*it)->m_dx = -((*it)->m_dx);
						(*it)->m_sprite.scale(-1, 1);
					}
					if ((*it)->m_dx > 0 || p1.m_dx < 0)			// ��������� �����, ����� ������
					{
						(*it)->m_x = p1.m_x - (*it)->m_width;
						(*it)->m_dx = -((*it)->m_dx);
						(*it)->m_sprite.scale(-1, 1);
					}
					//if (p1.m_dx < 0)
					//	p1.m_x = (*it)->m_x + (*it)->m_width;
					//if (p1.m_dx > 0)
					//	p1.m_x = (*it)->m_x - p1.m_width;
				}
			}
			//// ��������� ������������ ����������� ����� �����
			//for (auto it2 = entity_array.begin(); it2 != entity_array.end(); ++it2)
			//{
			//	if ((*it2) != (*it))
			//		if ((*it2)->getRect().intersects((*it)->getRect()))
			//		{
			//			(*it2)->m_dx = -((*it2)->m_dx);
			//			(*it2)->m_sprite.scale(-1, 1);
			//		}
			//}
			// ��������/��������� ����������
			(*it)->update(time);
			if ((*it)->m_life == false)				// ��������� ��� �� ������
			{
				delete* it;							// ������� �� ������
				it = entity_array.erase(it);		// ������� �� ������
				continue;
			}
			else
			{
				window.draw((*it)->m_sprite);		// ���� ���, ������������
			}
			++it;
		}

		// ��������� ��������� ������
		p1.update(time);

		// ��������� ������
		window.draw(p1.m_sprite);

		// ��������� ������
		window.setView(camera);
		// ��������� ����
		window.display();
	}

	return 0;
}
////////////////////////////////////////////END MAIN///////////////////////////////////////////////////////////////

Player::Player(Image& image, const String& name, Level& lev, float X, float Y, int W, int H) : Entity(image, name, X, Y, W, H)
{
	m_score = 0;
	m_state = stay;
	m_obj = lev.GetAllObjects();	// ��������������. �������� ��� ������� ��� ��������������� ��������� � ������
	if (name == "Player1")
		m_sprite.setTextureRect(IntRect(4, 19, m_width, m_height));
}

void Player::control(const float time)
{
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		m_state = left;
		m_speed = 0.1f;
		//static float currentFrame(0);
		//currentFrame += 0.005*time;
		//if (currentFrame > 3) currentFrame -= 3;
		//m_sprite.setTextureRect(IntRect(295 * int(currentFrame), 103, 46, 30));
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		m_state = right;
		m_speed = 0.1f;
		//static float currentFrame(1);
		//currentFrame += 0.005f * time;
		//if (currentFrame > 5)
		//	currentFrame -= 4;
		//m_sprite.setTextureRect(IntRect(296 * int(currentFrame), 103, 40, 30));
	}

	if ((Keyboard::isKeyPressed(Keyboard::Up)) && (m_onGround)) {
		m_state = jump;
		m_dy = -0.4f;
		//m_onGround = false;	// �� ��������� ����� ������,�������� � ��������, ��� �� �� �� �����
		//currentFrame += 0.005*time;
		//if (currentFrame > 3) currentFrame -= 3;
		//p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 307, 96, 96));
	}

	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		m_state = down;
		m_speed = 0.1f;
		//currentFrame += 0.005*time;
		//if (currentFrame > 3) currentFrame -= 3;
		//p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 0, 96, 96));
	}
}

void Player::update(const float time)
{
	control(time);//������� ���������� ����������
	switch (m_state)//��� �������� ��������� �������� � ����������� �� ���������
	{
	case right:
		m_dx = m_speed;
		break;//��������� ���� ������
	case left:
		m_dx = -m_speed;
		break;//��������� ���� �����
	case up:
		break;//����� ��������� �������� ������ (�������� �� ��������)
	case down:
		break;//����� ��������� �� ����� ������ ��������� (�������� �� ��������)
	case jump:
		break;//����� ����� ���� ����� ��������
	case stay:
		break;//� ����� ����		
	}

	m_x += m_dx * time;
	checkCollisionWithMap(m_dx, 0);//������������ ������������ �� �
	m_y += m_dy * time;
	checkCollisionWithMap(0, m_dy);//������������ ������������ �� Y
	if (!m_isMove)
		m_speed = 0;
	m_sprite.setPosition(m_x + m_width / 2, m_y + m_height / 2); //������ ������� ������� � ����� ��� ������
	if (m_health <= 0)
		m_life = false;
	m_dy = m_dy + 0.0005f * time;		// ������ ���������� � �����
	if ((m_dy > 0.1) || (m_dy < -0.1))	// ��� ���� ����� ��������� ������� � ����� ��� �����/������
		m_onGround = false;
	moveCamera(m_x, m_y);
}

void Player::checkCollisionWithMap(float Dx, float Dy)
{
	for (int i(0); i < m_obj.size(); ++i)		// ���������� ��� ������� �����
		if (getRect().intersects(m_obj[i].rect))	// ��������� � ����� �� �������� ����� ������������ ������ ��������
		{
			if (m_obj[i].name == "solid")			// ���� ��������� �����������
			{
				// ��������� � ����� �� ������ ����������� (� ����� ������� �� ���������)
				if (Dy > 0)	// �����
				{
					m_y = m_obj[i].rect.top - m_height;
					m_dy = 0;
					m_onGround = true;
				}
				if (Dy < 0)	// ������
				{
					m_y = m_obj[i].rect.top + m_obj[i].rect.height;
					m_dy = 0;
				}
				if (Dx > 0)	// ������
				{ 
					m_x = m_obj[i].rect.left - m_width;
				}
				if (Dx < 0)	// �����
				{
					m_x = m_obj[i].rect.left + m_obj[i].rect.width;
				}
			}
		}
}

Entity::Entity(Image& image, const String& name, float X, float Y, int width, int height) :
	m_width(width), m_height(height), m_dx(0), m_dy(0), m_x(X), m_y(Y), m_speed(0), m_name(name),
	m_moveTimer(0), m_health(100), m_life(true), m_isMove(false), m_onGround(false)
{
	m_texture.loadFromImage(image);
	m_sprite.setTexture(m_texture);
	//���������� ����� ������� ��������� �������, �� ������ �������� ���� � �������� 
	m_sprite.setOrigin(static_cast<float>(m_width / 2), static_cast<float>(m_height / 2));
}

Enemy::Enemy(Image& image, const String& name, Level& lvl, float X, float Y, int W, int H) : Entity(image, name, X, Y, W, H)
{
	m_obj = lvl.GetObjects("solid");	// ��������������. �������� ������ ������� ��� �������������� ����� � ������
	if (name == "easyEnemy")
		m_sprite.setTextureRect(IntRect(0, 0, m_width, m_height));
	m_dx = 0.1f;	// ���� ��������� (���� ������ ������ ���������)
}

void Enemy::checkCollisionWithMap(const float Dx, const float Dy)
{
	for (int i(0); i < m_obj.size(); ++i)		// ���������� ��� ������� �����
		if (getRect().intersects(m_obj[i].rect))	// ��������� � ����� �� �������� ����� ������������ ������ ��������
		{
			// ��������� � ����� �� ������ ����������� (� ����� ������� �� ���������)
			if (Dy > 0)	// ����
			{
				m_y = m_obj[i].rect.top - m_height;
				m_dy = 0;
				m_onGround = true;
			}
			if (Dy < 0)	// �����
			{
				m_y = m_obj[i].rect.top + m_obj[i].rect.height;
				m_dy = 0;
			}
			if (Dx > 0)	// ������
			{
				m_x = m_obj[i].rect.left - m_width;
				m_dx = -0.1f;
				m_sprite.scale(-1, 1);
			}
			if (Dx < 0)	// �����
			{
				m_x = m_obj[i].rect.left + m_obj[i].rect.width;
				m_dx = 0.1f;
				m_sprite.scale(-1, 1);
			}
		}
}

void Enemy::update(const float time)
{
	if (m_name == "easyEnemy")
	{
		m_x += m_dx * time;
		checkCollisionWithMap(m_dx, 0);//������������ ������������ �� �
		m_y += m_dy * time;
		checkCollisionWithMap(0, m_dy);//������������ ������������ �� Y
		m_sprite.setPosition(m_x + m_width / 2, m_y + m_height / 2); //������ ������� ������� � ����� ��� ������
		if (m_health <= 0)
			m_life = false;
		m_dy = m_dy + 0.0005f * time;//������ ���������� � �����
	}
}

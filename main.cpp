#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;

#include <list>
#include "Level.h"
#include "View.h"
#include "Player.h"
#include "Mission.h"
#include "Enemy.h"
#include "MovingPlatform.h"
#include "Bullet.h"
#include "LifeBar.h"
#include "Game.h"


const unsigned c_wWidth(960);		// ������ ���� (640)
const unsigned c_wHeight(480);		// ������ ���� (480)
const unsigned c_wFPS(240);			// ��������� ������ � ������� (FPS)

////////////////////////////////////////////START MAIN///////////////////////////////////////////////////////////////
int main()
{
	RenderWindow window(VideoMode(c_wWidth, c_wHeight), "SFML-Learn");
	window.setFramerateLimit(c_wFPS);
	window.setVerticalSyncEnabled(true);
	
	//// ������������� ������
	camera.reset(FloatRect(0, 0, c_wWidth, c_wHeight));

	//// ��� �����
	Level lvl;
	lvl.LoadFromFile("resources/map/lvl-1.tmx");

	//// ��� ������ � ����� ������
	RectangleShape board_shape(Vector2f(c_wWidth, c_wHeight / 15));	// ���������� ������
	board_shape.setFillColor(Color(100, 100, 100, 200));

	//// ��� �����
	SoundBuffer shoot_soundBuffer;
	Sound shoot_sound;
	shoot_soundBuffer.loadFromFile("resources/sound/shoot.ogg");
	shoot_sound.setBuffer(shoot_soundBuffer);

	///////// ��� ������
	Font font;
	font.loadFromFile("resources/CyrilicOld.TTF");
	// Score
	Text score_text("", font, 24);
	score_text.setFillColor(Color::Cyan);	// ���� ������
	score_text.setStyle(Text::Bold);		// ������ �����
	// Heath
	Text health_text("", font, 20);
	health_text.setFillColor(Color::Green);	// ���� ������
	health_text.setStyle(Text::Bold);		// ������ �����
	// Time
	Text time_text("", font, 24);
	time_text.setStyle(Text::Bold);		// ������ �����

	//// ��� ������ ������
	bool showMissionText(false);
	Image mission_image;
	mission_image.loadFromFile("resources/images/missionbg.jpg");
	Texture mission_texture;
	mission_texture.loadFromImage(mission_image);
	Sprite mission_sprite;
	mission_sprite.setTexture(mission_texture);
	mission_sprite.setTextureRect(IntRect(0, 0, 340, 510));
	mission_sprite.setScale(0.8f, 0.8f);		// ��������� ��������
	mission_sprite.setOrigin(340 / 2, 510 / 2);
	Text mission_text("", font, 26);
	mission_text.setFillColor(Color::Black);
	mission_text.setStyle(Text::Bold);

	//// ��� ��������
	LifeBar life_bar;

	//// ��� ����������
	Object place_player = lvl.GetObject("player");
	Object place_enemy = lvl.GetObject("easyEnemy");

	//// ��������
	Image hero_image;
	hero_image.loadFromFile("resources/images/MilesTailsPrower.gif");
	Player p1("Hero",hero_image, lvl, place_player.rect.left, place_player.rect.top, 43.f, 30.f);

	//// ���
	Image enemy_image;
	enemy_image.loadFromFile("resources/images/shamaich.png");
	enemy_image.createMaskFromColor(Color(255, 0, 0));
	std::list<Entity*> entities;				// ������������ ������ ������
	std::list<Entity*>::iterator it_entities;	// ��� ������� �� ��������� ������
	std::list<Entity*>::iterator it_entities2;
	std::vector<Object> place_enemies = lvl.GetObjects("easyEnemy");	// ���������� ������ �� �����
	for (int i(0); i < place_enemies.size(); ++i)
		entities.push_back(new Enemy("easyEnemy", enemy_image, lvl, place_enemies[i].rect.left,
			place_enemies[i].rect.top, 200.f, 97.f));

	//// ��� ���������� ���������
	Image platform_image;
	platform_image.loadFromFile("resources/images/movingPlatform.png");
	std::vector<Object> place_movingPlatform = lvl.GetObjects("movingPlatform");
	for (int i(0); i < place_movingPlatform.size(); ++i)
	{
		entities.push_back(new MovingPlatform("movingPlatform", platform_image,
			place_movingPlatform[i].rect.left,place_movingPlatform[i].rect.top, 95.f, 22.f));
	}

	//// ��� ����
	Image bullet_image;
	bullet_image.loadFromFile("resources/images/bullet.png");
	bullet_image.createMaskFromColor(Color(0, 0, 0));

	//// ��� ��������
	Clock clock;
	int game_time(0);

	// ������� ���� ����������: �����������, ���� ������� ����
	while (window.isOpen())
	{
		//// �������
		float time = static_cast<float>(clock.getElapsedTime().asMilliseconds());
		game_time += clock.getElapsedTime().asMilliseconds();
		clock.restart();

		// ������������ ������� ������� � �����
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			//// ���-���� ����������� ���� �����
			if (event.type == Event::KeyReleased)
			{
				if (event.key.code == Keyboard::Tab)
					if (showMissionText)
						showMissionText = false;
					else
						showMissionText = true;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			if (p1.m_isShoot)
			{
				p1.m_isShoot = false;
				entities.push_back(new Bullet("bullet", bullet_image, lvl, p1.m_rect.left,
					p1.m_rect.top, 16.f, 16.f, static_cast<int>(p1.m_state)));
				shoot_sound.play();
			}
		}

		// ������� ������ � ��������� ����� ����
		window.clear(Color(70, 70, 70, 0));

		// ��������� �����
		lvl.Draw(window);

		// ��������� ������������ �������� (�����, ��������� � �.�.)
		for (it_entities = entities.begin(); it_entities != entities.end();)
		{
			(*it_entities)->update(time);
			if (!(*it_entities)->m_life)
			{
				delete* it_entities;
				entities.erase(it_entities++);
			}
			else
			{
				window.draw((*it_entities)->m_sprite);
				++it_entities;
			}
		}

		// ��������� ���������
		p1.update(time);
		window.draw(p1.m_sprite);
		// ��������� heatlh-bar
		life_bar.update(p1.m_health);
		life_bar.draw(window);

		for (it_entities = entities.begin(); it_entities != entities.end(); ++it_entities)
		{
			// ��������� ������������ ��������� � ������������� ���������
			if (p1.getRect().intersects((*it_entities)->getRect()))
			{
				if ((*it_entities)->m_name == "movingPlatform")	// ��������� ������������ ��������� � �����������
				{
					if (p1.m_dy > 0 && !(p1.m_onGround))	// ��� ������
					{
						p1.m_rect.top = (*it_entities)->m_rect.top - p1.m_rect.height;
						p1.m_dy = 0;
						p1.m_rect.left += (*it_entities)->m_dx * time;	// ���������� � ���������
						p1.m_state = Player::State::stay;
						p1.m_onGround = true;
					}
				}
				if ((*it_entities)->m_name == "easyEnemy")	// ��������� ������������ ��������� � ������
				{
					if (p1.m_dy > 0 && !(p1.m_onGround))
					{
						p1.m_dy = -0.3f;
						(*it_entities)->m_life = false;
					}
					else
						p1.m_health -= 5;
					if ((*it_entities)->m_dx > 0) // ���� ���� ���� ������
					{
						if (p1.m_dx > 0 && p1.m_onGround)
						{
							p1.m_speed = 0.15f;
							p1.m_dy = -0.6f;
							p1.m_onGround = false;
							p1.m_state = Player::State::left;
							p1.m_onControl = false;
						}
						if ((p1.m_dx < 0 && p1.m_onGround) || (p1.m_dx == 0 && p1.m_onGround))
						{
							p1.m_speed = 0.15f;
							p1.m_dy = -0.6f;
							p1.m_onGround = false;
							p1.m_state = Player::State::right;
							p1.m_onControl = false;

							(*it_entities)->m_rect.left = p1.m_rect.left -
								(*it_entities)->m_rect.width;
							(*it_entities)->m_dx = -(*it_entities)->m_dx;
							(*it_entities)->m_sprite.scale(-1, 1);
						}
					}
					else if ((*it_entities)->m_dx < 0)	// ���� ���� ���� �����
					{
						if ((p1.m_dx > 0 && p1.m_onGround) || (p1.m_dx == 0 && p1.m_onGround))
						{
							p1.m_speed = 0.15f;
							p1.m_dy = -0.6f;
							p1.m_onGround = false;
							p1.m_state = Player::State::left;
							p1.m_onControl = false;

							(*it_entities)->m_rect.left = p1.m_rect.left +
								p1.m_rect.width;
							(*it_entities)->m_dx = -(*it_entities)->m_dx;
							(*it_entities)->m_sprite.scale(-1, 1);
						}
						if (p1.m_dx < 0 && p1.m_onGround)
						{
							p1.m_speed = 0.15f;
							p1.m_dy = -0.6f;
							p1.m_onGround = false;
							p1.m_state = Player::State::right;
							p1.m_onControl = false;
						}
					}
				}
			}
			for (it_entities2 = entities.begin(); it_entities2 != entities.end(); ++it_entities2)	// ������������ ����� �������������
			{
				if (it_entities != it_entities2)
				{
					if ((*it_entities)->m_rect.intersects((*it_entities2)->m_rect))
					{
						(*it_entities)->m_dx = -(*it_entities)->m_dx;
						(*it_entities)->m_sprite.scale(-1, 1);
					}
				}
			}
		}

		// ��������� ���������� ������
		board_shape.setPosition(camera.getCenter().x-(c_wWidth/2), camera.getCenter().y-(c_wHeight/2));
		window.draw(board_shape);

		// ��������� ������
		score_text.setString("Score: " + std::to_string(p1.m_score));	// ���������� ������
		score_text.setPosition(camera.getCenter().x - (c_wWidth / 2.5f), camera.getCenter().y
			- (c_wHeight / 2));	// ������� ������
		window.draw(score_text);

		time_text.setString("Time: " + std::to_string(game_time / 1000));
		time_text.setPosition(camera.getCenter().x + (c_wWidth / 3.f), camera.getCenter().y
			- (c_wHeight / 2));
		window.draw(time_text);

		health_text.setString("Healt " + std::to_string(p1.m_health));
		health_text.setPosition(p1.m_sprite.getPosition().x - p1.m_sprite.getTextureRect().width,
			(p1.m_sprite.getPosition().y - p1.m_sprite.getTextureRect().height) - 7);
		window.draw(health_text);

		// ��������� ���� ������
		if (showMissionText)
		{
			mission_text.setString(getTextMission(getCurrentMission(5)));
			mission_sprite.setPosition(camera.getCenter().x, camera.getCenter().y);
			mission_text.setPosition(camera.getCenter().x-110, camera.getCenter().y-50);
			window.draw(mission_sprite);
			window.draw(mission_text);
		}

		// ������
		moveCamera(p1.m_sprite.getPosition().x, p1.m_sprite.getPosition().y);
		window.setView(camera);

		// ��������� ����
		window.display();
	}

	return 0;
}
////////////////////////////////////////////END MAIN///////////////////////////////////////////////////////////////
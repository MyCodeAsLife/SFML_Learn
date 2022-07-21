#pragma once

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


const unsigned c_wWidth(960);		// Ширина окна (640)
const unsigned c_wHeight(480);		// Высота окна (480)
const unsigned c_wFPS(240);			// Отрисовка кадров в секунду (FPS)
						// Текущий уровень

bool startGame(RenderWindow& window, Event& event, int& lvlNum);

void mainMenu()
{
	RenderWindow window(VideoMode(c_wWidth, c_wHeight), "SFML-Learn");
	window.setFramerateLimit(c_wFPS);
	window.setVerticalSyncEnabled(true);


	Texture menu1_texture, menu2_texture, menu3_texture;
	Texture about_texture, menuBackground_texture;
	menu1_texture.loadFromFile("resources/images/111.png");
	menu2_texture.loadFromFile("resources/images/222.png");
	menu3_texture.loadFromFile("resources/images/333.png");
	menuBackground_texture.loadFromFile("resources/images/about.png");
	about_texture.loadFromFile("resources/images/Penguins.jpg");
	Sprite menu1_sprite(menu1_texture), menu2_sprite(menu2_texture), menu3_sprite(menu3_texture);
	Sprite about_sprite(about_texture), menuBg_sprite(menuBackground_texture);

	int menuNum(0);
	int lvlNum(1);
	menu1_sprite.setPosition(100.f, 30.f);
	menu2_sprite.setPosition(100.f, 90.f);
	menu3_sprite.setPosition(100.f, 150.f);
	menuBg_sprite.setPosition(345.f, 0.f);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		menu1_sprite.setColor(Color::White);
		menu2_sprite.setColor(Color::White);
		menu3_sprite.setColor(Color::White);
			menuNum = 0;
			window.clear(Color(129, 181, 221));

		if (IntRect(100, 30, 300, 50).contains(Mouse::getPosition(window)))
		{
			menu1_sprite.setColor(Color::Blue);
			menuNum = 1;
		}
		if (IntRect(100, 90, 300, 50).contains(Mouse::getPosition(window)))
		{
			menu2_sprite.setColor(Color::Blue);
			menuNum = 2;
		}
		if (IntRect(100, 150, 300, 50).contains(Mouse::getPosition(window)))
		{
			menu3_sprite.setColor(Color::Blue);
			menuNum = 3;
		}

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			switch (menuNum)
			{
			case 1:
				if (!(startGame(window, event, lvlNum)))
					window.close();
				break;
			case 2:
				window.draw(about_sprite);
				window.display();
				while (!Keyboard::isKeyPressed(Keyboard::Escape));
				break;
			case 3:
				window.close();
				break;
			}
		}

		window.draw(menuBg_sprite);
		window.draw(menu1_sprite);
		window.draw(menu2_sprite);
		window.draw(menu3_sprite);

		window.display();
	}
}

bool startGame(RenderWindow& window, Event& event, int& lvlNum)
{
	//// Инициализация камеры
	camera.reset(FloatRect(0, 0, c_wWidth, c_wHeight));

	//// Для карты
	Level lvl;
	std::string lvl_path("resources/map/lvl-" + std::to_string(lvlNum) + ".tmx");
	lvl.LoadFromFile(lvl_path);

	//// Для плашки в верху экрана
	RectangleShape board_shape(Vector2f(c_wWidth, c_wHeight / 15));	// Прозрачная плашка
	board_shape.setFillColor(Color(100, 100, 100, 200));

	//// Для звука
	SoundBuffer shoot_soundBuffer;
	Sound shoot_sound;
	shoot_soundBuffer.loadFromFile("resources/sound/shoot.ogg");
	shoot_sound.setBuffer(shoot_soundBuffer);
	shoot_sound.setVolume(20);

	///////// Для текста
	Font font;
	font.loadFromFile("resources/CyrilicOld.TTF");
	// Score
	Text score_text("", font, 24);
	score_text.setFillColor(Color::Cyan);	// Цвет текста
	score_text.setStyle(Text::Bold);		// Жирный текст
	// Heath
	Text health_text("", font, 20);
	health_text.setFillColor(Color::Green);	// Цвет текста
	health_text.setStyle(Text::Bold);		// Жирный текст
	// Time
	Text time_text("", font, 24);
	time_text.setStyle(Text::Bold);		// Жирный текст

	//// Для экрана миссии
	bool showMissionText(false);
	Image mission_image;
	mission_image.loadFromFile("resources/images/missionbg.jpg");
	Texture mission_texture;
	mission_texture.loadFromImage(mission_image);
	Sprite mission_sprite;
	mission_sprite.setTexture(mission_texture);
	mission_sprite.setTextureRect(IntRect(0, 0, 340, 510));
	mission_sprite.setScale(0.8f, 0.8f);		// Уменьшаем картинку
	mission_sprite.setOrigin(340 / 2, 510 / 2);
	Text mission_text("", font, 26);
	mission_text.setFillColor(Color::Black);
	mission_text.setStyle(Text::Bold);

	//// Для хелсбара
	LifeBar life_bar;

	//// Для персонажей
	Object place_player = lvl.GetObject("player");
	Object place_enemy = lvl.GetObject("easyEnemy");

	//// Персонаж
	Image hero_image;
	hero_image.loadFromFile("resources/images/MilesTailsPrower.gif");
	Player p1("Hero", hero_image, lvl, place_player.rect.left, place_player.rect.top, 43.f, 30.f);

	//// Моб
	Image enemy_image;
	enemy_image.loadFromFile("resources/images/shamaich.png");
	enemy_image.createMaskFromColor(Color(255, 0, 0));
	std::list<Entity*> entities;				// Динамический список врагов
	std::list<Entity*>::iterator it_entities;	// Для прохода по элементам списка
	std::list<Entity*>::iterator it_entities2;
	std::vector<Object> place_enemies = lvl.GetObjects("easyEnemy");	// Координаты врагов на карте
	for (int i(0); i < place_enemies.size(); ++i)
		entities.push_back(new Enemy("easyEnemy", enemy_image, lvl, place_enemies[i].rect.left,
			place_enemies[i].rect.top, 200.f, 97.f));

	//// Для движущейся платформы
	Image platform_image;
	platform_image.loadFromFile("resources/images/movingPlatform.png");
	std::vector<Object> place_movingPlatform = lvl.GetObjects("movingPlatform");
	for (int i(0); i < place_movingPlatform.size(); ++i)
	{
		entities.push_back(new MovingPlatform("movingPlatform", platform_image,
			place_movingPlatform[i].rect.left, place_movingPlatform[i].rect.top, 95.f, 22.f));
	}

	//// Для пуль
	Image bullet_image;
	bullet_image.loadFromFile("resources/images/bullet.png");
	bullet_image.createMaskFromColor(Color(0, 0, 0));

	//// Для анимации
	Clock clock;
	int game_time(0);

	// Главный цикл приложения: выполняется, пока открыто окно
	while (window.isOpen())
	{
		//// Таймеры
		float time = static_cast<float>(clock.getElapsedTime().asMilliseconds());
		game_time += clock.getElapsedTime().asMilliseconds();
		clock.restart();

		// Обрабатываем очередь событий в цикле
		//Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			//// Вкл-Выкл отображения окна мисии
			if (event.type == Event::KeyReleased)
			{
				if (event.key.code == Keyboard::M)
					if (showMissionText)
						showMissionText = false;
					else
						showMissionText = true;
				if (event.key.code == Keyboard::Tab)
				{
					camera.reset(FloatRect(0, 0, c_wWidth, c_wHeight));
					window.setView(camera);
					// Освобождение динамической памяти
					for (it_entities = entities.begin(); it_entities != entities.end();)
					{
							delete* it_entities;
							entities.erase(it_entities++);
					}
					return true;
				}
				if (event.key.code == Keyboard::Escape)
					return false;
				if (event.key.code == Keyboard::N)
				{
					if (lvlNum > 3)
						lvlNum = 1;
					else
						++lvlNum;
				}
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

		// Очистка экрана и установка цвета фона
		window.clear(Color(70, 70, 70, 0));

		// Отрисовка карты
		lvl.Draw(window);

		// Отрисовка динамических объектов (враги, платформы и т.д.)
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

		// Отрисовка персонажа
		p1.update(time);
		window.draw(p1.m_sprite);
		// Отрисовка heatlh-bar
		life_bar.update(p1.m_health);
		life_bar.draw(window);

		for (it_entities = entities.begin(); it_entities != entities.end(); ++it_entities)
		{
			// Обработка столкновения персонажа с динамическими объектами
			if (p1.getRect().intersects((*it_entities)->getRect()))
			{
				if ((*it_entities)->m_name == "movingPlatform")	// Обработка столкновения персонажа с платформами
				{
					if (p1.m_dy > 0 && !(p1.m_onGround))	// Под ногами
					{
						p1.m_rect.top = (*it_entities)->m_rect.top - p1.m_rect.height;
						p1.m_dy = 0;
						p1.m_rect.left += (*it_entities)->m_dx * time;	// Прилипание к платформе
						p1.m_state = Player::State::stay;				// Прилипание к платформе
						p1.m_onGround = true;
					}
				}
				if ((*it_entities)->m_name == "easyEnemy")	// Обработка столкновения персонажа с врагом
				{
					if (p1.m_dy > 0 && !(p1.m_onGround))
					{
						p1.m_dy = -0.3f;
						(*it_entities)->m_life = false;
					}
					else
						p1.m_health -= 5;
					if ((*it_entities)->m_dx > 0) // Если враг идет вправо
					{
						if (p1.m_dx > 0 && p1.m_onGround)
						{
							p1.m_speed = 0.15f;
							p1.m_dy = -0.6f;
							p1.m_onGround = false;
							p1.m_state = Player::State::left;
							p1.m_onControl = false;

							(*it_entities)->m_rect.left = p1.m_rect.left + p1.m_rect.width;
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
					else if ((*it_entities)->m_dx < 0)	// Если враг идет влево
					{
						if ((p1.m_dx > 0 && p1.m_onGround) || (p1.m_dx == 0 && p1.m_onGround))
						{
							p1.m_speed = 0.15f;
							p1.m_dy = -0.6f;
							p1.m_onGround = false;
							p1.m_state = Player::State::left;
							p1.m_onControl = false;

							// Выталкивание персонажа
							p1.m_rect.left = (*it_entities)->m_rect.left - p1.m_rect.width;
							// Выталкивание врага
							(*it_entities)->m_rect.left = p1.m_rect.left + p1.m_rect.width;
							// Смена направления движения врага
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

							// Выталкивание персонажа
							p1.m_rect.left = (*it_entities)->m_rect.left + (*it_entities)->m_rect.width;
							// Выталкивание врага
							(*it_entities)->m_rect.left = p1.m_rect.left -
								(*it_entities)->m_rect.width;
						}
					}
				}
			}
			for (it_entities2 = entities.begin(); it_entities2 != entities.end(); ++it_entities2)	// Столкновение между протитвниками
			{
				if ((*it_entities)->m_rect.intersects((*it_entities2)->m_rect) && it_entities != it_entities2)
				{
					if ((*it_entities2)->m_name == "easyEnemy" && (*it_entities)->m_name == "easyEnemy")
					{
						if ((*it_entities2)->m_dx > 0)	// Если идет вправо
						{
							(*it_entities2)->m_rect.left = (*it_entities)->m_rect.left - (*it_entities2)->m_rect.width;
						}
						else if ((*it_entities2)->m_dx < 0)	// Если идет влево
						{
							(*it_entities2)->m_rect.left = (*it_entities)->m_rect.left + (*it_entities)->m_rect.width;
						}
						// Меняем направление движения обои столкнувшимся
						(*it_entities)->m_dx = -(*it_entities)->m_dx;
						(*it_entities)->m_sprite.scale(-1, 1);

						(*it_entities2)->m_dx = -(*it_entities2)->m_dx;
						(*it_entities2)->m_sprite.scale(-1, 1);
					}
					if ((*it_entities2)->m_name == "easyEnemy" && (*it_entities)->m_name == "bullet")
					{
						(*it_entities2)->m_life = false;
						(*it_entities)->m_life = false;
					}
				}
			}
		}

		// Отрисовка прозрачной плашки
		board_shape.setPosition(camera.getCenter().x - (c_wWidth / 2), camera.getCenter().y - (c_wHeight / 2));
		window.draw(board_shape);

		// Отрисовка текста
		score_text.setString("Score: " + std::to_string(p1.m_score));	// Содержание текста
		score_text.setPosition(camera.getCenter().x - (c_wWidth / 2.5f), camera.getCenter().y
			- (c_wHeight / 2));	// Позиция текста
		window.draw(score_text);

		time_text.setString("Time: " + std::to_string(game_time / 1000));
		time_text.setPosition(camera.getCenter().x + (c_wWidth / 3.f), camera.getCenter().y
			- (c_wHeight / 2));
		window.draw(time_text);

		health_text.setString("Healt " + std::to_string(p1.m_health));
		health_text.setPosition(p1.m_sprite.getPosition().x - p1.m_sprite.getTextureRect().width,
			(p1.m_sprite.getPosition().y - p1.m_sprite.getTextureRect().height) - 7);
		window.draw(health_text);

		// Отрисовка окна миссии
		if (showMissionText)
		{
			mission_text.setString(getTextMission(getCurrentMission(5)));
			mission_sprite.setPosition(camera.getCenter().x, camera.getCenter().y);
			mission_text.setPosition(camera.getCenter().x - 110, camera.getCenter().y - 50);
			window.draw(mission_sprite);
			window.draw(mission_text);
		}

		// Камера
		moveCamera(p1.m_sprite.getPosition().x, p1.m_sprite.getPosition().y);
		window.setView(camera);

		// Отрисовка окна
		window.display();
	}

	return 0;
}
#include "Level.h"
#include "View.h"
#include "Map.h"
#include "Player.h"
#include "Mission.h"
#include <list>

const unsigned c_wWidth(960);		// Ширина окна (640)
const unsigned c_wHeight(480);		// Высота окна (480)
const unsigned c_wFPS(240);			// Отрисовка кадров в секунду (FPS)
const unsigned SPRITE_WIDTH(32);
const unsigned SPRITE_HEIGHT(32);

using namespace sf;
////////////////////////////////////////////START MAIN///////////////////////////////////////////////////////////////
int main()
{
	RenderWindow window(VideoMode(c_wWidth, c_wHeight), "SFML-Learn");
	window.setFramerateLimit(c_wFPS);
	window.setVerticalSyncEnabled(true);
	
	//// Инициализация камеры
	camera.reset(FloatRect(0, 0, c_wWidth, c_wHeight));

	//// Для карты
	Image map_image;
	map_image.loadFromFile("resources/images/map.png");
	Texture map_texture;
	map_texture.loadFromImage(map_image);
	Sprite map_sprite;
	map_sprite.setTexture(map_texture);
	randomMapGenerator();

	//// Для плашки в верху экрана
	RectangleShape board_shape(Vector2f(c_wWidth, c_wHeight / 15));	// Прозрачная плашка
	board_shape.setFillColor(Color(100, 100, 100, 200));

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

	//// Персонаж
	Image hero_image;
	hero_image.loadFromFile("resources/images/hero.png");
	Player p1("Hero",hero_image, 250, 250, 96.f, 56.f);

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
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			//// Вкл-Выкл отображения окна мисии
			if (event.type == Event::KeyReleased)
				if (event.key.code == Keyboard::Tab)
					if (showMissionText)
						showMissionText = false;
					else
						showMissionText = true;

		}

		// Очистка экрана и установка цвета фона
		window.clear(Color(70, 70, 70, 0));

		// Отрисовка карты
		for (int i(0); i < HEIGHT_MAP; ++i)
			for (int j(0); j < WIDTH_MAP; ++j)
			{
				if (TileMap[i][j] == ' ')
					map_sprite.setTextureRect(IntRect(0, 0, SPRITE_WIDTH, SPRITE_HEIGHT));
				if (TileMap[i][j] == 's')
					map_sprite.setTextureRect(IntRect(32, 0, SPRITE_WIDTH, SPRITE_HEIGHT));
				if (TileMap[i][j] == '0')
					map_sprite.setTextureRect(IntRect(64, 0, SPRITE_WIDTH, SPRITE_HEIGHT));
				if (TileMap[i][j] == 'f')
					map_sprite.setTextureRect(IntRect(96, 0, SPRITE_WIDTH, SPRITE_HEIGHT));
				if (TileMap[i][j] == 'h')
					map_sprite.setTextureRect(IntRect(128, 0, SPRITE_WIDTH, SPRITE_HEIGHT));

				map_sprite.setPosition(static_cast<float>(j * SPRITE_WIDTH), static_cast<float>(i * SPRITE_HEIGHT));
				window.draw(map_sprite);
			}

		// Отрисовка персонажа
		p1.update(time);
		window.draw(p1.m_sprite);

		// Отрисовка прозрачной плашки
		board_shape.setPosition(camera.getCenter().x-(c_wWidth/2), camera.getCenter().y-(c_wHeight/2));
		window.draw(board_shape);

		// Отрисовка текста
		score_text.setString("Score: " + std::to_string(p1.m_score));	// Содержание текста
		score_text.setPosition(camera.getCenter().x - (c_wWidth / 2.5f), camera.getCenter().y - (c_wHeight / 2));	// Позиция текста
		window.draw(score_text);

		time_text.setString("Time: " + std::to_string(game_time / 1000));
		time_text.setPosition(camera.getCenter().x + (c_wWidth / 3.f), camera.getCenter().y - (c_wHeight / 2));
		window.draw(time_text);

		health_text.setString("Healt " + std::to_string(p1.m_health));
		health_text.setPosition(p1.getX() - (p1.m_width / 2.f) + 2, p1.getY() - (p1.m_height));
		window.draw(health_text);

		// Отрисовка окна миссии
		if (showMissionText)
		{
			mission_text.setString(getTextMission(getCurrentMission(5)));
			mission_sprite.setPosition(camera.getCenter().x, camera.getCenter().y);
			mission_text.setPosition(camera.getCenter().x-110, camera.getCenter().y-50);
			window.draw(mission_sprite);
			window.draw(mission_text);
		}

		// Камера
		moveCamera(p1.m_x, p1.m_y);
		window.setView(camera);

		// Отрисовка окна
		window.display();
	}

	return 0;
}
////////////////////////////////////////////END MAIN///////////////////////////////////////////////////////////////
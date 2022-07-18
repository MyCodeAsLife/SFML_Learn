#include "Level.h"
#include "View.h"
#include "Player.h"
#include "Mission.h"
#include "Enemy.h"
#include <list>

const unsigned c_wWidth(960);		// ������ ���� (640)
const unsigned c_wHeight(480);		// ������ ���� (480)
const unsigned c_wFPS(240);			// ��������� ������ � ������� (FPS)

using namespace sf;
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
	Enemy en1("easyEnemy", enemy_image, lvl, place_enemy.rect.left, place_enemy.rect.top, 200.f, 97.f);

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
				if (event.key.code == Keyboard::Tab)
					if (showMissionText)
						showMissionText = false;
					else
						showMissionText = true;

		}

		// ������� ������ � ��������� ����� ����
		window.clear(Color(70, 70, 70, 0));

		// ��������� �����
		lvl.Draw(window);

		// ��������� �����
		en1.update(time);
		window.draw(en1.m_sprite);

		// ��������� ���������
		p1.update(time);
		window.draw(p1.m_sprite);

		// ��������� ���������� ������
		board_shape.setPosition(camera.getCenter().x-(c_wWidth/2), camera.getCenter().y-(c_wHeight/2));
		window.draw(board_shape);

		// ��������� ������
		score_text.setString("Score: " + std::to_string(p1.m_score));	// ���������� ������
		score_text.setPosition(camera.getCenter().x - (c_wWidth / 2.5f), camera.getCenter().y - (c_wHeight / 2));	// ������� ������
		window.draw(score_text);

		time_text.setString("Time: " + std::to_string(game_time / 1000));
		time_text.setPosition(camera.getCenter().x + (c_wWidth / 3.f), camera.getCenter().y - (c_wHeight / 2));
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
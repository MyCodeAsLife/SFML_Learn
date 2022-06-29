
#include "Header.h"
#include "Map.h"
#include "Player.h"
#include "View.h"
#include "Mission.h"
#include <iostream>



const unsigned c_wWidth(1340);		// ������ ���� (640)
const unsigned c_wHeight(780);		// ������ ���� (480)
const unsigned c_wFPS(120);			// ��������� ������ � ������� (FPS)
const unsigned c_Speed(600);		// �������� ���� (��� ������ �����, ��� ���� ��������)

int main()
{
	RenderWindow window(VideoMode(c_wWidth, c_wHeight), "SFML-Learn");
	window.setFramerateLimit(c_wFPS);
	// ������������� ������ (������ �������� ������ ��� ������� ����)
	camera.reset(FloatRect(0, 0, c_wWidth, c_wHeight));

	// �����
	Font font;
	font.loadFromFile("images/CyrilicOld.TTF");
	// ����� ������� ������
	Text text_score("", font, 20);				// ��������, �����, ������ ������
	//text_score.setFillColor(Color::Red);		// ���� ������
	text_score.setOutlineColor(Color::Black);	// ���� ������� ������
	text_score.setStyle(Text::Bold);			// ������ �����
	// ����� ��������� ��������
	Text text_health("", font, 30);
	text_health.setFillColor(Color::Green);
	text_health.setStyle(Text::Bold);
	// ����� �����������
	Text text_timer("", font, 30);
	text_timer.setOutlineColor(Color::Red);
	text_timer.setStyle(Text::Bold);
	// ����� ������
	Text text_mission("", font, 30);
	text_mission.setFillColor(Color::Black);

	// �������� �����
	Texture textute_map;
	textute_map.loadFromFile("images/map.png");
	Sprite sprite_map;
	sprite_map.setTexture(textute_map);
	// �������� ���� �������� �����
	Texture texture_missionWindow;
	texture_missionWindow.loadFromFile("images/missionbg.jpg");
	Sprite sprite_missionWindow;
	sprite_missionWindow.setTexture(texture_missionWindow);
	sprite_missionWindow.setTextureRect(IntRect(0, 0, 340, 510));
	sprite_missionWindow.setScale(0.85f, 0.6f);	// ��������� ������ �������/��������

	float currentFrame(0);		//������� ����
	Clock clock;

	Clock clock_gameTime;
	int gameTime(0);			// ������� ����� ����

	Player p1("hero.png", 96, 96, 96, 96);	// �������� � �������������� ���������� ���������
	moveCamera(p1.getX(), p1.getY());		// ��������� ��������� ������� ������ �� ����������� ���������

	bool showMissionText = false;	// �������� �� ��������� ������ �� ������

	// �������� ��������� ������
	randomMapGenerator();

	// ������� ���� ����������: �����������, ���� ������� ����
	while (window.isOpen())
	{
		float time = static_cast<float>(clock.getElapsedTime().asMicroseconds());

		if (p1.m_life)
			gameTime = static_cast<int>(clock_gameTime.getElapsedTime().asSeconds());		// ������� �������� ������� ����
		else
			camera.rotate(0.5f);	// ��� ��������� ������� ������

		clock.restart();
		time /= c_Speed;		//�������� ����


		// ������������ ������� ������� � �����
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if (p1.m_life)
		{
			// ���������� ����������
			if (Keyboard::isKeyPressed(Keyboard::Up))
			{
				p1.moveUp(0.1f, time);
				moveCamera(p1.getX(), p1.getY());
			}
			if (Keyboard::isKeyPressed(Keyboard::Down))
			{
				p1.moveDown(0.1f, time);
				moveCamera(p1.getX(), p1.getY());
			}
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				p1.moveLeft(0.1f, time);
				moveCamera(p1.getX(), p1.getY());
			}
			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				p1.moveRight(0.1f, time);
				moveCamera(p1.getX(), p1.getY());
			}
		}

		// ����������� �����
		if (Keyboard::isKeyPressed(Keyboard::W))
			camera.move(0.f, -0.3f * time);
		if(Keyboard::isKeyPressed(Keyboard::S))
			camera.move(0.f, 0.3f * time);
		if(Keyboard::isKeyPressed(Keyboard::A))
			camera.move(-0.3f * time, 0);
		if (Keyboard::isKeyPressed(Keyboard::D))
			camera.move(0.3f * time, 0);

		// ������� �������� ������
		if (Keyboard::isKeyPressed(Keyboard::Tab))
			if (showMissionText)
				showMissionText = false;
			else
				showMissionText = true;

		// �������� ������
		//changeCamera();

		// ��������� ����� ����
		window.clear(Color(70, 70, 70, 0));

		// ��������� ����� (load map)
		for (int i(0); i < c_HEIGHT_MAP; ++i)
			for (int j(0); j < c_WIDTH_MAP; ++j)
			{
				// ����� �������� ����� � ������������ � "������"
				if (TileMap[i][j] == ' ')
					sprite_map.setTextureRect(IntRect(0, 0, 32, 32));
				if (TileMap[i][j] == 's')
					sprite_map.setTextureRect(IntRect(32, 0, 32, 32));
				if (TileMap[i][j] == '0')
					sprite_map.setTextureRect(IntRect(64, 0, 32, 32));
				if (TileMap[i][j] == 'f')
					sprite_map.setTextureRect(IntRect(96, 0, 32, 32));
				if (TileMap[i][j] == 'h')
					sprite_map.setTextureRect(IntRect(128, 0, 32, 32));

				sprite_map.setPosition(static_cast<float>(j * 32), static_cast<float>(i * 32));		// ����� ������� ����� �����
				window.draw(sprite_map);					// ��������� ����� �����
			}



		// ����������� ������ �����, �������� ���� ��� � �������� ���� (�������� ��� ������ ������� ����)
		sf::Vector2i localPosition = Mouse::getPosition(window);	// �������� ���������� ��������� ���� ������������ ����
		if ((localPosition.x < 10) && (localPosition.x > 0))
			camera.move(-0.2 * time, 0);
		if ((localPosition.x > window.getSize().x - 10) && (localPosition.x < window.getSize().x))
			camera.move(0.2 * time, 0);
		if ((localPosition.y < 10) && (localPosition.y > 0))
			camera.move(0, -0.2 * time);
		if ((localPosition.y > window.getSize().y - 10) && (localPosition.y < window.getSize().y))
			camera.move(0, 0.2 * time);
		
		// ��������� ����
		p1.update(time);
		window.draw(p1.m_sprite);

		// ��������� ������ �������� ������
		text_score.setString("������� ������: " + std::to_string(p1.m_score));
		text_score.setPosition(p1.getX() - 32, p1.getY());	// ����������� ����� ������ � ���������
		window.draw(text_score);

		// ��������� ������ ���������� ��������
		text_health.setString("HP " + std::to_string(p1.m_health));
		text_health.setPosition(camera.getCenter().x - 600, camera.getCenter().y - 380);
		window.draw(text_health);

		//��������� �����������
		text_timer.setString("Timer " + std::to_string(gameTime));
		text_timer.setPosition(camera.getCenter().x + 420, camera.getCenter().y - 380);
		window.draw(text_timer);

		if (showMissionText)
		{
			text_mission.setString(getTextMission(1));
			text_mission.setPosition(camera.getCenter().x - 120, camera.getCenter().y - 120);
			sprite_missionWindow.setPosition(camera.getCenter().x - 135, camera.getCenter().y - 120);
			window.draw(sprite_missionWindow);
			window.draw(text_mission);
		}

		// ��������� ������
		window.setView(camera);

		// ��������� ����
		window.display();
	}

	return 0;
}
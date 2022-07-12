//#include <SFML/Graphics.hpp>
#include "Header.h"
#include "View.h"
//#include "Level.h"
#include "Player.h"
#include <list>

const unsigned c_wWidth(960);		// ������ ���� (640)
const unsigned c_wHeight(480);		// ������ ���� (480)
const unsigned c_wFPS(240);			// ��������� ������ � ������� (FPS)
//const unsigned c_Speed(600);		// �������� ���� (��� ������ �����, ��� ���� ��������)

using namespace sf;
////////////////////////////////////////////START MAIN///////////////////////////////////////////////////////////////
int main()
{
	RenderWindow window(VideoMode(c_wWidth, c_wHeight), "SFML-Learn");
	window.setFramerateLimit(c_wFPS);
	window.setVerticalSyncEnabled(true);

	// ��������
	Player p1("hero.png", 250, 250, 96.f, 96.f);

	// ��� ��������
	float currentFrame(0);

	Clock clock;
	// ������� ���� ����������: �����������, ���� ������� ����
	while (window.isOpen())
	{
		float time = static_cast<float>(clock.getElapsedTime().asMilliseconds());
		clock.restart();

		// ������������ ������� ������� � �����
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
		{ 
			p1.m_dir = 0;
			p1.m_speed = 0.2f;
			currentFrame += 0.008f * time;
			if (currentFrame > 3)
				currentFrame = 0;
			p1.m_sprite.setTextureRect(IntRect(96 * static_cast<int>(currentFrame), 192, 96, 96));
		}
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			p1.m_dir = 1;
			p1.m_speed = 0.2f;
			currentFrame += 0.008f * time;
			if (currentFrame > 3)
				currentFrame = 0;
			p1.m_sprite.setTextureRect(IntRect(96 * static_cast<int>(currentFrame), 96, 96, 96));
		}
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			p1.m_dir = 3;
			p1.m_speed = 0.2f;
			currentFrame += 0.008f * time;
			if (currentFrame > 3)
				currentFrame = 0;
			p1.m_sprite.setTextureRect(IntRect(96 * static_cast<int>(currentFrame), 288, 96, 96));
		}
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			p1.m_dir = 2;
			p1.m_speed = 0.2f;
			currentFrame += 0.008f * time;
			if (currentFrame > 3)
				currentFrame = 0;
			p1.m_sprite.setTextureRect(IntRect(96 * static_cast<int>(currentFrame), 0, 96, 96));
		}

		// ��������� ����� ����
		window.clear(Color(70, 70, 70, 0));

		// ��������� ���������
		p1.update(time);
		window.draw(p1.m_sprite);

		// ��������� ����
		window.display();
	}

	return 0;
}
////////////////////////////////////////////END MAIN///////////////////////////////////////////////////////////////
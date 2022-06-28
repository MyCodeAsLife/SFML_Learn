
#include "Header.h"
#include "Map.h"
#include "Player.h"
#include "View.h"



const unsigned c_wWidth(640);		// ������ ����
const unsigned c_wHeight(480);		// ������ ����
const unsigned c_wFPS(120);			// ��������� ������ � ������� (FPS)
const unsigned c_Speed(600);		// �������� ���� (��� ������ �����, ��� ���� ��������)

int main()
{
	RenderWindow window(VideoMode(c_wWidth, c_wHeight), "SFML-Learn");
	window.setFramerateLimit(c_wFPS);
	// ������������� ������ (������ �������� ������ ��� ������� ����)
	camera.reset(FloatRect(0, 0, c_wWidth, c_wHeight));

	// �������� �����
	Texture textute_map;
	textute_map.loadFromFile("images/map.png");
	Sprite sprite_map;
	sprite_map.setTexture(textute_map);

	float currentFrame(0);		//������� ����
	Clock clock;

	Player p1("hero.png", 96, 96, 96, 96);	// �������� � �������������� ���������� ���������
	moveCamera(p1.getX(), p1.getY());		// ��������� ��������� ������� ������ �� ����������� ���������

	// ������� ���� ����������: �����������, ���� ������� ����
	while (window.isOpen())
	{
		float time = static_cast<float>(clock.getElapsedTime().asMicroseconds());
		clock.restart();
		time /= c_Speed;		//�������� ����


		// ������������ ������� ������� � �����
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		// ���������� ����������
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			p1.moveUp(0.1f, time);
			moveCamera(p1.getX(), p1.getY());
			p1.interactionWithMap();
		}
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			p1.moveDown(0.1f, time);
			moveCamera(p1.getX(), p1.getY());
			p1.interactionWithMap();
		}
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			p1.moveLeft(0.1f, time);
			moveCamera(p1.getX(), p1.getY());
			p1.interactionWithMap();
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			p1.moveRight(0.1f, time);
			moveCamera(p1.getX(), p1.getY());
			p1.interactionWithMap();
		}

		// ����������� �����
		if (Keyboard::isKeyPressed(Keyboard::W))
			camera.move(0.f, -0.1f * time);
		if(Keyboard::isKeyPressed(Keyboard::S))
			camera.move(0.f, 0.1f * time);
		if(Keyboard::isKeyPressed(Keyboard::A))
			camera.move(-0.1f * time, 0);
		if (Keyboard::isKeyPressed(Keyboard::D))
			camera.move(0.1f * time, 0);

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

				sprite_map.setPosition(static_cast<float>(j * 32), static_cast<float>(i * 32));		// ����� ������� ����� �����
				window.draw(sprite_map);					// ��������� ����� �����
			}
		
		// ��������� ����
		p1.update(time);
		window.draw(p1.m_sprite);

		// ��������� ������
		window.setView(camera);
		
		

		// ��������� ����
		window.display();
	}

	return 0;
}
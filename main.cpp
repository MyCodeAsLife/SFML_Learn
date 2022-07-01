
#include "Header.h"
#include "Map.h"
#include "Player.h"
#include "View.h"
#include "Level.h"



const unsigned c_wWidth(1340);		// ������ ���� (640)
const unsigned c_wHeight(780);		// ������ ���� (480)
const unsigned c_wFPS(120);			// ��������� ������ � ������� (FPS)
const unsigned c_Speed(600);		// �������� ���� (��� ������ �����, ��� ���� ��������)
extern void moveCamera(const float x, const float y);


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
	// �������� ��������� �����, �����, ������
	randomMapGenerator();

	Clock clock;
	// �����
	Image player_image;
	player_image.loadFromFile("images/MilesTailsPrower.gif");
	Player p1(player_image, 250, 500, 43, 30, "Player1");	// �������� � �������������� ���������� ���������
	moveCamera(p1.m_x, p1.m_y);		// ��������� ��������� ������� ������ �� ����������� ���������
	// ����
	Image easeEnemyEmage;
	easeEnemyEmage.loadFromFile("images/shamaich.png");
	easeEnemyEmage.createMaskFromColor(Color(255, 0, 0)); // ������� ��� ��������
	Enemy en1(easeEnemyEmage, 250, 500, 200, 97, "EasyEnemy");

	//// �����
	//Font font;
	//font.loadFromFile("images/CyrilicOld.TTF");
	//// ����� ������� ������
	//Text text_score("", font, 20);				// ��������, �����, ������ ������
	////text_score.setFillColor(Color::Red);		// ���� ������
	//text_score.setOutlineColor(Color::Black);	// ���� ������� ������
	//text_score.setStyle(Text::Bold);			// ������ �����
	//// ����� ��������� ��������
	//Text text_health("", font, 30);
	//text_health.setFillColor(Color::Green);
	//text_health.setStyle(Text::Bold);
	//// ��� �����������
	//Clock clock_gameTime;
	//int gameTime(0);			// ������� ����� ����
	//Text text_timer("", font, 30);
	//text_timer.setOutlineColor(Color::Red);
	//text_timer.setStyle(Text::Bold);
	//// ����� ������
	//Text text_mission("", font, 30);
	//text_mission.setFillColor(Color::Black);
	//// �������� ���� �������� �����
	//Texture texture_missionWindow;
	//texture_missionWindow.loadFromFile("images/missionbg.jpg");
	//Sprite sprite_missionWindow;
	//sprite_missionWindow.setTexture(texture_missionWindow);
	//sprite_missionWindow.setTextureRect(IntRect(0, 0, 340, 510));
	//sprite_missionWindow.setScale(0.85f, 0.6f);	// ��������� ������ �������/��������
	//bool showMissionText = false;	// �������� �� ��������� ������ �� ������
	//// ��� �������������� �������, �����
	//bool isMove(false);	// ��� ������ ���� �� �������
	//float dx(0);		// ������������� �������� �� x
	//float dy(0);		// ������������� �������� �� y
	//// ���������� ��� �������� ����������� ������� �� ������ ����
	//int tempX(0);	// ���������� ���������� x �� ������ ����
	//int tempY(0);	// ���������� ���������� y �� ������ ����
	//float distance(0);	// ���������� �� ����������� ������� �� ����� ������ ����

	// ������� ���� ����������: �����������, ���� ������� ����
	while (window.isOpen())
	{
		//// ��� �����������
		//if (p1.m_life)
		//	gameTime = static_cast<int>(clock_gameTime.getElapsedTime().asSeconds());	// ������� �������� ������� ����
		//else
		//	camera.rotate(0.5f);	// ��� ��������� ������� ������

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

			//if (event.type == Event::MouseButtonPressed)	// ���� ���� ������ ������ ����
			//{
			//	if (event.key.code == Mouse::Left)			// ���� ������ ���� ���� �����
			//		// ���� ������� ���������� ���� ������ � ������� ������� ����
			//		if (p1.m_sprite.getGlobalBounds().contains(pos.x, pos.y))
			//		{
			//			std::cout << "Is clicked on Leon!\n";
			//			// �������� �������� ����� �������� ������� � ������� �� x
			//			dx = pos.x - p1.m_sprite.getPosition().x;
			//			// �������� �������� ����� �������� ������� � ������� �� y
			//			dy = pos.y - p1.m_sprite.getPosition().y;
			//			isMove = true;	// ��������� ����������� �������
			//			p1.m_sprite.setColor(Color::Green);
			//			p1.m_isSelect = true;
			//		}
			//		else
			//			if (p1.m_isSelect)
			//			{
			//				p1.m_isSelect = false;
			//				p1.m_sprite.setColor(Color::White);
			//			}
			//	// ���� �������� ������� � ������� ������ ������� ����
			//	if (event.key.code == Mouse::Right && p1.m_isSelect)
			//	{
			//		p1.m_isMove = true;
			//		tempX = static_cast<int>(pos.x);
			//		tempY = static_cast<int>(pos.y);
			//		//��� ������������� ��������� ��� ���������� ��������
			//		float d_x = pos.x - p1.m_x;	// ������, ����������� ������, ������� ���������� ������ � ������
			//		float d_y = pos.y - p1.m_y;	// ���� ����� �� ��� y
			//		// �������� ���� � �������� � ��������� ��� � �������
			//		float rotation = static_cast<float>((atan2(d_y, d_x)) * 180 / 3.14159265);
			//		std::cout << rotation << '\n';
			//		p1.m_sprite.setRotation(rotation);	// ������������ ������ �� ���������� �������
			//	}
			//}		
			//// ����� ���������� ������� ����� ������ ���� (��� ��������������)
			//if (event.type == Event::MouseButtonReleased)
			//	if (event.key.code == Mouse::Left)
			//		isMove = false;
			//if (isMove)		// ���� ��������������
			//{
			//	// �������� ��������(dx � dy), ����� "������" ������ �� �� ����� ���� �������� �����
			//	p1.m_x = (pos.x - dx);
			//	p1.m_y = (pos.y - dy);
			//}
			//// ��������� ��������� ����� �������
			//if (event.type == Event::KeyReleased)
			//	if (event.key.code == Keyboard::Tab)
			//		if (showMissionText)
			//			showMissionText = false;
			//		else
			//			showMissionText = true;
		}

		//// ���������� ����������� ����������� ��������� � ��������� �����������
		//if (p1.m_isMove)
		//{
		//	// ����������� ���������� �� ��������� �� ����� ��������
		//	distance = sqrt(((tempX - p1.m_x) * (tempX - p1.m_x)) + ((tempY - p1.m_x) * (tempY - p1.m_x)));
		//	if (distance > 5)	// ���� �������� ������� �������� ������� � �������� ����� ��������
		//	{
		//		p1.m_x = (p1.m_x + (0.2f * time * (tempX - p1.m_x) / distance)); // �������� �� �, � ������� ������� �������
		//		p1.m_y = (p1.m_y + (0.2f * time * (tempY - p1.m_y) / distance));	// �������� �� y, � ������� ������� �������
		//	}
		//	else
		//	{
		//		p1.m_isMove = false;
		//		std::cout << "Priehali!\n";
		//	}
		//}
		//// ����������� �����, ���� ������ ������
		//if (Keyboard::isKeyPressed(Keyboard::W))
		//	camera.move(0.f, -0.3f * time);
		//if(Keyboard::isKeyPressed(Keyboard::S))
		//	camera.move(0.f, 0.3f * time);
		//if(Keyboard::isKeyPressed(Keyboard::A))
		//	camera.move(-0.3f * time, 0);
		//if (Keyboard::isKeyPressed(Keyboard::D))
		//	camera.move(0.3f * time, 0);
		//// ����������� ������ �����, �������� ���� ��� � �������� ���� (�������� ��� ������ ������� ����)
		//sf::Vector2i localPosition = Mouse::getPosition(window);	// �������� ���������� ��������� ���� ������������ ����
		//if ((localPosition.x < 10) && (localPosition.x > 0))
		//	camera.move(-0.2f * time, 0);
		//if ((localPosition.x > static_cast<int>(window.getSize().x - 10)) &&
		//	(localPosition.x < static_cast<int>(window.getSize().x)))
		//	camera.move(0.2f * time, 0);
		//if ((localPosition.y < 10) && (localPosition.y > 0))
		//	camera.move(0, -0.2f * time);
		//if ((localPosition.y > static_cast<int>(window.getSize().y - 10)) &&
		//	(localPosition.y < static_cast<int>(window.getSize().y)))
		//	camera.move(0, 0.2f * time);
		//// ��������� ������ �������� ������
		//text_score.setString("������� ������: " + std::to_string(p1.m_score));
		//text_score.setPosition(p1.m_x - p1.m_sprite.getOrigin().y, p1.m_y - p1.m_sprite.getOrigin().y);	// ����������� ����� ������ � ���������
		//window.draw(text_score);
		//// ��������� ������ ���������� ��������
		//text_health.setString("HP " + std::to_string(p1.m_health));
		//text_health.setPosition(camera.getCenter().x - 600, camera.getCenter().y - 380);
		//window.draw(text_health);
		////��������� �����������
		//text_timer.setString("Timer " + std::to_string(gameTime));
		//text_timer.setPosition(camera.getCenter().x + 420, camera.getCenter().y - 380);
		//window.draw(text_timer);
		//// ��������� ����� ������
		//if (showMissionText)
		//{
		//	text_mission.setString(getTextMission(1));
		//	text_mission.setPosition(camera.getCenter().x - 120, camera.getCenter().y - 120);
		//	sprite_missionWindow.setPosition(camera.getCenter().x - 135, camera.getCenter().y - 120);
		//	window.draw(sprite_missionWindow);
		//	window.draw(text_mission);
		//}

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

				// ����� ������� ����� �����
				sprite_map.setPosition(static_cast<float>(j * 32), static_cast<float>(i * 32));
				window.draw(sprite_map);	// ��������� ����� �����
			}

		// ��������� ����������
		en1.update(time);
		window.draw(en1.m_sprite);
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
#include "Header.h"
#include "Player.h"



const unsigned c_wWidth(900);		//Ширина окна
const unsigned c_wHeight(600);		//Высота окна
const unsigned c_wFPS(120);			
const unsigned c_Speed(600);		//Скорость игры (Чем меньше число, тем выше скорость)

int main()
{
	RenderWindow window(VideoMode(c_wWidth, c_wHeight), "SFML-Learn");
	window.setFramerateLimit(c_wFPS);

	Texture texture;
	texture.loadFromFile("images/hero.png");
	Sprite sprite;
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 192, 96, 96));
	sprite.setPosition(30.f, 40.f);

	float currentFrame(0);		//Текущий кадр
	Clock clock;

	Player p1("hero.png", 0, 96, 96, 96);

	// Главный цикл приложения: выполняется, пока открыто окно
	while (window.isOpen())
	{
		float time = static_cast<float>(clock.getElapsedTime().asMicroseconds());
		clock.restart();
		time /= c_Speed;		//Скорость игры


		// Обрабатываем очередь событий в цикле
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up))
		{
			p1.moveUp(3, 0.1f, time);
			//p1.m_dir = 3;
			//p1.m_speed = 0.1f;
			//currentFrame += 0.005f * time;
			//if (currentFrame > 3) currentFrame -= 3;
			//p1.m_sprite.setTextureRect(IntRect(96 * static_cast<int>(currentFrame), 288, 96, 96));
		}
		if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down))
		{
			p1.m_dir = 2;
			p1.m_speed = 0.1f;
			currentFrame += 0.005f * time;
			if (currentFrame > 3) currentFrame -= 3;
			p1.m_sprite.setTextureRect(IntRect(96 * static_cast<int>(currentFrame), 0, 96, 96));
		}
		if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left))
		{
			p1.m_dir = 1;
			p1.m_speed = 0.1f;
			currentFrame += 0.005f * time;
			if (currentFrame > 3) currentFrame -= 3;
			p1.m_sprite.setTextureRect(IntRect(96 * static_cast<int>(currentFrame), 96, 96, 96));
		}
		if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right))
		{
			p1.m_dir = 0;
			p1.m_speed = 0.1f;
			currentFrame += 0.005f * time;
			if (currentFrame > 3) currentFrame -= 3;
			p1.m_sprite.setTextureRect(IntRect(96 * static_cast<int>(currentFrame), 192, 96, 96));
		}

		// Установка цвета фона
		window.clear(Color(70, 70, 70, 0));
		
		p1.update(time);
		window.draw(p1.m_sprite);

		// Отрисовка окна
		window.display();
	}

	return 0;
}

#include "Header.h"
#include "Map.h"
#include "Player.h"
#include "View.h"
#include "Level.h"



const unsigned c_wWidth(1340);		// Ширина окна (640)
const unsigned c_wHeight(780);		// Высота окна (480)
const unsigned c_wFPS(120);			// Отрисовка кадров в секунду (FPS)
const unsigned c_Speed(600);		// Скорость игры (Чем меньше число, тем выше скорость)
extern void moveCamera(const float x, const float y);


int main()
{
	RenderWindow window(VideoMode(c_wWidth, c_wHeight), "SFML-Learn");
	window.setFramerateLimit(c_wFPS);
	// Инициализация камеры (Подгон масштаба камеры под размеры окна)
	camera.reset(FloatRect(0, 0, c_wWidth, c_wHeight));

	// Текстуры карты
	Texture textute_map;
	textute_map.loadFromFile("images/map.png");
	Sprite sprite_map;
	sprite_map.setTexture(textute_map);
	// Рандомно добавляем камни, цветы, сердца
	randomMapGenerator();

	Clock clock;
	// Игрок
	Image player_image;
	player_image.loadFromFile("images/MilesTailsPrower.gif");
	Player p1(player_image, 250, 500, 43, 30, "Player1");	// Создание и первоначальное размещение персонажа
	moveCamera(p1.m_x, p1.m_y);		// Установка начальной позиции камеры на управляемом персонаже
	// Враг
	Image easeEnemyEmage;
	easeEnemyEmage.loadFromFile("images/shamaich.png");
	easeEnemyEmage.createMaskFromColor(Color(255, 0, 0)); // Удаляем фон картинки
	Enemy en1(easeEnemyEmage, 250, 500, 200, 97, "EasyEnemy");

	//// Шрифт
	//Font font;
	//font.loadFromFile("images/CyrilicOld.TTF");
	//// Текст счетчик камней
	//Text text_score("", font, 20);				// Надписть, шрифт, размер шрифта
	////text_score.setFillColor(Color::Red);		// Цвет текста
	//text_score.setOutlineColor(Color::Black);	// Цвет контура текста
	//text_score.setStyle(Text::Bold);			// Жирный текст
	//// Текст индикатор здоровья
	//Text text_health("", font, 30);
	//text_health.setFillColor(Color::Green);
	//text_health.setStyle(Text::Bold);
	//// Для секундомера
	//Clock clock_gameTime;
	//int gameTime(0);			// Считает время игры
	//Text text_timer("", font, 30);
	//text_timer.setOutlineColor(Color::Red);
	//text_timer.setStyle(Text::Bold);
	//// Текст миссии
	//Text text_mission("", font, 30);
	//text_mission.setFillColor(Color::Black);
	//// Текстура окна описания мисии
	//Texture texture_missionWindow;
	//texture_missionWindow.loadFromFile("images/missionbg.jpg");
	//Sprite sprite_missionWindow;
	//sprite_missionWindow.setTexture(texture_missionWindow);
	//sprite_missionWindow.setTextureRect(IntRect(0, 0, 340, 510));
	//sprite_missionWindow.setScale(0.85f, 0.6f);	// Уменьшаем размер спрайта/картинки
	//bool showMissionText = false;	// Отвечает за появление текста на экране
	//// Для перетаскивания объекта, мыщью
	//bool isMove(false);	// Для шелчка мыши по спрайту
	//float dx(0);		// корректировка движения по x
	//float dy(0);		// корректировка движения по y
	//// Переменные для движения выделенного объекта по щелчку мыши
	//int tempX(0);	// Запоминаем координату x по щелчку мыши
	//int tempY(0);	// Запоминаем координату y по щелчку мыши
	//float distance(0);	// Расстояние от выделенного объекта до места щелчка мыши

	// Главный цикл приложения: выполняется, пока открыто окно
	while (window.isOpen())
	{
		//// Для секундомера
		//if (p1.m_life)
		//	gameTime = static_cast<int>(clock_gameTime.getElapsedTime().asSeconds());	// Процесс подсчета времени игры
		//else
		//	camera.rotate(0.5f);	// При проиграше вращать камеру

		float time = static_cast<float>(clock.getElapsedTime().asMicroseconds());
		clock.restart();
		time /= c_Speed;		//Скорость игры

		Vector2i pixelPos = Mouse::getPosition(window);		// Координаты указателя относительно окна
		Vector2f pos = window.mapPixelToCoords(pixelPos);	// Конвертиция координат указателя мыши, в игровые координаты

		// Обрабатываем очередь событий в цикле
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			//if (event.type == Event::MouseButtonPressed)	// Если была нажата кнопка мыши
			//{
			//	if (event.key.code == Mouse::Left)			// Если кнопка мыши была левая
			//		// Если игровые координаты мыши входят в область спрайта льва
			//		if (p1.m_sprite.getGlobalBounds().contains(pos.x, pos.y))
			//		{
			//			std::cout << "Is clicked on Leon!\n";
			//			// Получаем разность между позицией курсора и спрайта по x
			//			dx = pos.x - p1.m_sprite.getPosition().x;
			//			// Получаем разность между позицией курсора и спрайта по y
			//			dy = pos.y - p1.m_sprite.getPosition().y;
			//			isMove = true;	// Разрешаем перемещение спрайта
			//			p1.m_sprite.setColor(Color::Green);
			//			p1.m_isSelect = true;
			//		}
			//		else
			//			if (p1.m_isSelect)
			//			{
			//				p1.m_isSelect = false;
			//				p1.m_sprite.setColor(Color::White);
			//			}
			//	// Если персонаж выделен и щелкаем правой кнопкой мыши
			//	if (event.key.code == Mouse::Right && p1.m_isSelect)
			//	{
			//		p1.m_isMove = true;
			//		tempX = static_cast<int>(pos.x);
			//		tempY = static_cast<int>(pos.y);
			//		//Для поворачивания персонажа при автономном движении
			//		float d_x = pos.x - p1.m_x;	// вектор, колинеарной прямой, которая пересекает спрайт и курсор
			//		float d_y = pos.y - p1.m_y;	// тоже самое по оси y
			//		// Получаем угол в радианах и переводим его в градусы
			//		float rotation = static_cast<float>((atan2(d_y, d_x)) * 180 / 3.14159265);
			//		std::cout << rotation << '\n';
			//		p1.m_sprite.setRotation(rotation);	// Поворачиваем спрайт на полученный градусы
			//	}
			//}		
			//// После отпускания нажатия левой кнопки мыши (для перетаскивания)
			//if (event.type == Event::MouseButtonReleased)
			//	if (event.key.code == Mouse::Left)
			//		isMove = false;
			//if (isMove)		// Если перетаскивание
			//{
			//	// Отнимаем разность(dx и dy), чтобы "тащить" спрайт за то место куда кликнули мышью
			//	p1.m_x = (pos.x - dx);
			//	p1.m_y = (pos.y - dy);
			//}
			//// Включение отрисовки листа заданий
			//if (event.type == Event::KeyReleased)
			//	if (event.key.code == Keyboard::Tab)
			//		if (showMissionText)
			//			showMissionText = false;
			//		else
			//			showMissionText = true;
		}

		//// Автономное перемещение выделенного персонажа к указанным координатам
		//if (p1.m_isMove)
		//{
		//	// Высчитываем расстояние от персонажа до точки движения
		//	distance = sqrt(((tempX - p1.m_x) * (tempX - p1.m_x)) + ((tempY - p1.m_x) * (tempY - p1.m_x)));
		//	if (distance > 5)	// Этим условием убираем дерганье спрайта в конейной точке движения
		//	{
		//		p1.m_x = (p1.m_x + (0.2f * time * (tempX - p1.m_x) / distance)); // Движение по х, с помощбю вектора нормали
		//		p1.m_y = (p1.m_y + (0.2f * time * (tempY - p1.m_y) / distance));	// Движение по y, с помощбю вектора нормали
		//	}
		//	else
		//	{
		//		p1.m_isMove = false;
		//		std::cout << "Priehali!\n";
		//	}
		//}
		//// Перемещение карты, пока кнопка нажата
		//if (Keyboard::isKeyPressed(Keyboard::W))
		//	camera.move(0.f, -0.3f * time);
		//if(Keyboard::isKeyPressed(Keyboard::S))
		//	camera.move(0.f, 0.3f * time);
		//if(Keyboard::isKeyPressed(Keyboard::A))
		//	camera.move(-0.3f * time, 0);
		//if (Keyboard::isKeyPressed(Keyboard::D))
		//	camera.move(0.3f * time, 0);
		//// Перемещение камеры мыщью, работает пока мыш в пределах окна (подойдет для любого размера окна)
		//sf::Vector2i localPosition = Mouse::getPosition(window);	// Получаем координаты указателя мыши относительно окна
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
		//// Отрисовка текста счетчика камней
		//text_score.setString("Собрано камней: " + std::to_string(p1.m_score));
		//text_score.setPosition(p1.m_x - p1.m_sprite.getOrigin().y, p1.m_y - p1.m_sprite.getOrigin().y);	// Прикрепляем вывод текста к персонажу
		//window.draw(text_score);
		//// Отрисовка текста индикатора здоровья
		//text_health.setString("HP " + std::to_string(p1.m_health));
		//text_health.setPosition(camera.getCenter().x - 600, camera.getCenter().y - 380);
		//window.draw(text_health);
		////Отрисовка секундомера
		//text_timer.setString("Timer " + std::to_string(gameTime));
		//text_timer.setPosition(camera.getCenter().x + 420, camera.getCenter().y - 380);
		//window.draw(text_timer);
		//// Отрисовка листа миссий
		//if (showMissionText)
		//{
		//	text_mission.setString(getTextMission(1));
		//	text_mission.setPosition(camera.getCenter().x - 120, camera.getCenter().y - 120);
		//	sprite_missionWindow.setPosition(camera.getCenter().x - 135, camera.getCenter().y - 120);
		//	window.draw(sprite_missionWindow);
		//	window.draw(text_mission);
		//}

		// Установка цвета фона
		window.clear(Color(70, 70, 70, 0));

		// Отрисовка карты (load map)
		for (int i(0); i < c_HEIGHT_MAP; ++i)
			for (int j(0); j < c_WIDTH_MAP; ++j)
			{
				// Выбор текстуры тайла в соответствии с "картой"
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

				// Выбор позиции тайла карты
				sprite_map.setPosition(static_cast<float>(j * 32), static_cast<float>(i * 32));
				window.draw(sprite_map);	// Отрисовка тайла карты
			}

		// Отрисовка противника
		en1.update(time);
		window.draw(en1.m_sprite);
		// Отрисовка льва
		p1.update(time);
		window.draw(p1.m_sprite);

		// Установка камеры
		window.setView(camera);
		// Отрисовка окна
		window.display();
	}

	return 0;
}
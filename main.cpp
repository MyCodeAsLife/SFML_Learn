#include "Header.h"
#include "View.h"
#include "Level.h"
#include <list>

const unsigned c_wWidth(960);		// Ширина окна (640)
const unsigned c_wHeight(480);		// Высота окна (480)
const unsigned c_wFPS(120);			// Отрисовка кадров в секунду (FPS)
const unsigned c_Speed(600);		// Скорость игры (Чем меньше число, тем выше скорость)

//	Родительский класс для юнитов
class Entity
{
public:
	std::vector<Object> m_obj;	// Массив объектов карты (получилось только через указатели, иначе ошибка метода вектора по определению размера)
	int m_width, m_height;
	float m_dx, m_dy;		// Ускорение по осям
	float m_x, m_y;			// Положение юнита
	float m_speed;			// Скорость юнита
	float m_moveTimer;		// Таймер для различных действий
	int m_health;			// Здоровье юнита
	bool m_life, m_isMove, m_onGround; // Переменные состояния персонажа
	String m_name;
	Texture m_texture;
	Sprite m_sprite;

public:
	Entity(Image& image, const String& name, float X, float Y, int width, int height);
	FloatRect getRect() { return FloatRect(m_x, m_y, m_width, m_height); } // Эта функция нужна для проверки столкновения
	virtual void update(const float time) = 0;
};

//	Класс игрового персонажа
class Player : public Entity
{
public:
	int m_score;
	enum { left, right, up, down, jump, stay } m_state;//добавляем тип перечисления - состояние объекта

public:
	Player(Image& image, const String& name, Level& lev, float X, float Y, int W, int H);
	void control(const float time);
	void update(const float time);
	float getplayercoordinateX() { return m_x; }
	float getplayercoordinateY() { return m_y; }
	void checkCollisionWithMap(float Dx, float Dy);	//ф ция проверки столкновений с картой

};

// Класс противника
class Enemy :public Entity
{
public:
	Enemy(Image& image, const String& name, Level& lvl, float X, float Y, int W, int H);
	void checkCollisionWithMap(const float Dx, const float Dy);
	void update(const float time);

};

class SpriteManager {//это задел на следующие уроки,прошу не обращать внимания на эти изменения)
public:
	Image m_image;
	Texture m_texture;
	Sprite m_sprite;
	String m_name;
	String m_file;
	int m_widthOfSprite;
	int m_heightOfSprite;
	SpriteManager(String file, String Name) {
		m_file = file;
		m_name = Name;
		m_image.loadFromFile("images/" + m_file);
		m_texture.loadFromImage(m_image);
		m_sprite.setTexture(m_texture);
	}
};

////////////////////////////////////////////START MAIN///////////////////////////////////////////////////////////////
int main()
{
	RenderWindow window(VideoMode(c_wWidth, c_wHeight), "SFML-Learn");
	window.setFramerateLimit(c_wFPS);
	// Инициализация камеры (Подгон масштаба камеры под размеры окна)
	camera.reset(FloatRect(0, 0, c_wWidth, c_wHeight));

	//Для работы с картой
	Level lvl;
	lvl.LoadFromFile("map.tmx");

	Clock clock;
	// Получаем/устанавливаем начальные координаты песонажей
	Object player_obj = lvl.GetObject("player");		// Получаем координаты объекта player
	// Игрок
	Image player_image;
	player_image.loadFromFile("images/MilesTailsPrower.gif");
	Player p1(player_image, "Player1", lvl, player_obj.rect.left, player_obj.rect.top, 40, 30);	// Создание и первоначальное размещение персонажа
	moveCamera(p1.m_x, p1.m_y);		// Установка начальной позиции камеры на управляемом персонаже
	// Враги
	Image easyEnemy_Image;
	easyEnemy_Image.loadFromFile("images/shamaich.png");
	easyEnemy_Image.createMaskFromColor(Color(255, 0, 0)); // Удаляем фон картинки
	std::vector<Object> easyEnemy_obj_array = lvl.GetObjects("easyEnemy");	// Получаем координаты объект(ов) easeEnemy
	std::list<Entity*> entity_array;		// Массив для врагов
	std::list<Entity*>::iterator it_enemy;	// Итератор для перемещения по массиву врагов
	for (int i(0); i < easyEnemy_obj_array.size(); ++i)	// Создаем столько врагов, сколько указанно на карте
		entity_array.push_back(new Enemy(easyEnemy_Image, "easyEnemy", lvl, easyEnemy_obj_array[i].rect.left,
			easyEnemy_obj_array[i].rect.top, 200, 97));	// Инициализируем врагов

	// Главный цикл приложения: выполняется, пока открыто окно
	while (window.isOpen())
	{
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
		}

		// Установка цвета фона
		window.clear(Color(70, 70, 70, 0));

		// Отрисовка карты
		lvl.Draw(window);



		 // Отрисовка и удаление противника(ов)
		if (!entity_array.empty())	// Если есть противники то выполняем над ними действия
			for (auto it = entity_array.begin(); it != entity_array.end();)
		{
			// Столкновение с противником
			if ((*it)->getRect().intersects(p1.getRect()))	//Если объект противника пересекается с игроком
			{
				if ((*it)->m_name == "easyEnemy")	// Если противник является типа "easyEnemy"
				{
					// Падение на противника
					if ((p1.m_dy > 0) && (p1.m_onGround == false))	// Если персонаж падает
					{
						(*it)->m_dx = 0.f;		// Останавливаем противника
						p1.m_dy = -0.2f;		// Игрок отскакивает
						(*it)->m_health = 0;	// Зануляем кол-во здоровья противника
					}
					else
						p1.m_health -= 5;		// иначе получаем повреждения
					// Столкновение противника с игроком (есть баг, потихоньку толкает игрока)

					if ((*it)->m_dx < 0 || p1.m_dx > 0)	// Противник справа, игрок слева
					{
						(*it)->m_x = p1.m_x + p1.m_width;
						(*it)->m_dx = -((*it)->m_dx);
						(*it)->m_sprite.scale(-1, 1);
					}
					if ((*it)->m_dx > 0 || p1.m_dx < 0)			// Противник слева, игрок справа
					{
						(*it)->m_x = p1.m_x - (*it)->m_width;
						(*it)->m_dx = -((*it)->m_dx);
						(*it)->m_sprite.scale(-1, 1);
					}
					//if (p1.m_dx < 0)
					//	p1.m_x = (*it)->m_x + (*it)->m_width;
					//if (p1.m_dx > 0)
					//	p1.m_x = (*it)->m_x - p1.m_width;
				}
			}
			//// Обработка столкновений противников между собой
			//for (auto it2 = entity_array.begin(); it2 != entity_array.end(); ++it2)
			//{
			//	if ((*it2) != (*it))
			//		if ((*it2)->getRect().intersects((*it)->getRect()))
			//		{
			//			(*it2)->m_dx = -((*it2)->m_dx);
			//			(*it2)->m_sprite.scale(-1, 1);
			//		}
			//}
			// Удаление/отрисовка противника
			(*it)->update(time);
			if ((*it)->m_life == false)				// Проверяем жив ли объект
			{
				delete* it;							// Удаляем из памяти
				it = entity_array.erase(it);		// Удаляем из списка
				continue;
			}
			else
			{
				window.draw((*it)->m_sprite);		// Если жив, отрисовываем
			}
			++it;
		}

		// Отрисовка персонажа игрока
		p1.update(time);

		// Отрисовка игрока
		window.draw(p1.m_sprite);

		// Установка камеры
		window.setView(camera);
		// Отрисовка окна
		window.display();
	}

	return 0;
}
////////////////////////////////////////////END MAIN///////////////////////////////////////////////////////////////

Player::Player(Image& image, const String& name, Level& lev, float X, float Y, int W, int H) : Entity(image, name, X, Y, W, H)
{
	m_score = 0;
	m_state = stay;
	m_obj = lev.GetAllObjects();	// Инициализируем. Получаем все объекты для взаимодеййствия персонажа с картой
	if (name == "Player1")
		m_sprite.setTextureRect(IntRect(4, 19, m_width, m_height));
}

void Player::control(const float time)
{
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		m_state = left;
		m_speed = 0.1f;
		//static float currentFrame(0);
		//currentFrame += 0.005*time;
		//if (currentFrame > 3) currentFrame -= 3;
		//m_sprite.setTextureRect(IntRect(295 * int(currentFrame), 103, 46, 30));
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		m_state = right;
		m_speed = 0.1f;
		//static float currentFrame(1);
		//currentFrame += 0.005f * time;
		//if (currentFrame > 5)
		//	currentFrame -= 4;
		//m_sprite.setTextureRect(IntRect(296 * int(currentFrame), 103, 40, 30));
	}

	if ((Keyboard::isKeyPressed(Keyboard::Up)) && (m_onGround)) {
		m_state = jump;
		m_dy = -0.4f;
		//m_onGround = false;	// то состояние равно прыжок,прыгнули и сообщили, что мы не на земле
		//currentFrame += 0.005*time;
		//if (currentFrame > 3) currentFrame -= 3;
		//p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 307, 96, 96));
	}

	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		m_state = down;
		m_speed = 0.1f;
		//currentFrame += 0.005*time;
		//if (currentFrame > 3) currentFrame -= 3;
		//p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 0, 96, 96));
	}
}

void Player::update(const float time)
{
	control(time);//функция управления персонажем
	switch (m_state)//тут делаются различные действия в зависимости от состояния
	{
	case right:
		m_dx = m_speed;
		break;//состояние идти вправо
	case left:
		m_dx = -m_speed;
		break;//состояние идти влево
	case up:
		break;//будет состояние поднятия наверх (например по лестнице)
	case down:
		break;//будет состояние во время спуска персонажа (например по лестнице)
	case jump:
		break;//здесь может быть вызов анимации
	case stay:
		break;//и здесь тоже		
	}

	m_x += m_dx * time;
	checkCollisionWithMap(m_dx, 0);//обрабатываем столкновение по Х
	m_y += m_dy * time;
	checkCollisionWithMap(0, m_dy);//обрабатываем столкновение по Y
	if (!m_isMove)
		m_speed = 0;
	m_sprite.setPosition(m_x + m_width / 2, m_y + m_height / 2); //задаем позицию спрайта в место его центра
	if (m_health <= 0)
		m_life = false;
	m_dy = m_dy + 0.0005f * time;		// Делаем притяжение к земле
	if ((m_dy > 0.1) || (m_dy < -0.1))	// Для того чтобы учитывать падение с краев или взлет/прыжок
		m_onGround = false;
	moveCamera(m_x, m_y);
}

void Player::checkCollisionWithMap(float Dx, float Dy)
{
	for (int i(0); i < m_obj.size(); ++i)		// Перебераем все объекты карты
		if (getRect().intersects(m_obj[i].rect))	// Проверяем с каким из объектов карты контактирует данный персонаж
		{
			if (m_obj[i].name == "solid")			// Если встретили препятствие
			{
				// Проверяем с какой из сторон препятствие (в какую сторону мы двигаемся)
				if (Dy > 0)	// Снизу
				{
					m_y = m_obj[i].rect.top - m_height;
					m_dy = 0;
					m_onGround = true;
				}
				if (Dy < 0)	// Сверху
				{
					m_y = m_obj[i].rect.top + m_obj[i].rect.height;
					m_dy = 0;
				}
				if (Dx > 0)	// Справа
				{ 
					m_x = m_obj[i].rect.left - m_width;
				}
				if (Dx < 0)	// Слева
				{
					m_x = m_obj[i].rect.left + m_obj[i].rect.width;
				}
			}
		}
}

Entity::Entity(Image& image, const String& name, float X, float Y, int width, int height) :
	m_width(width), m_height(height), m_dx(0), m_dy(0), m_x(X), m_y(Y), m_speed(0), m_name(name),
	m_moveTimer(0), m_health(100), m_life(true), m_isMove(false), m_onGround(false)
{
	m_texture.loadFromImage(image);
	m_sprite.setTexture(m_texture);
	//Перемещаем точку отсчета координат спрайта, из левого верхнего угла в середину 
	m_sprite.setOrigin(static_cast<float>(m_width / 2), static_cast<float>(m_height / 2));
}

Enemy::Enemy(Image& image, const String& name, Level& lvl, float X, float Y, int W, int H) : Entity(image, name, X, Y, W, H)
{
	m_obj = lvl.GetObjects("solid");	// Инициализируем. Получаем нужные объекты для взаимодействия врага с картой
	if (name == "easyEnemy")
		m_sprite.setTextureRect(IntRect(0, 0, m_width, m_height));
	m_dx = 0.1f;	// Даем ускорение (этот объект всегда двигается)
}

void Enemy::checkCollisionWithMap(const float Dx, const float Dy)
{
	for (int i(0); i < m_obj.size(); ++i)		// Перебераем все объекты карты
		if (getRect().intersects(m_obj[i].rect))	// Проверяем с каким из объектов карты контактирует данный персонаж
		{
			// Проверяем с какой из сторон препятствие (в какую сторону мы двигаемся)
			if (Dy > 0)	// Вниз
			{
				m_y = m_obj[i].rect.top - m_height;
				m_dy = 0;
				m_onGround = true;
			}
			if (Dy < 0)	// Вверх
			{
				m_y = m_obj[i].rect.top + m_obj[i].rect.height;
				m_dy = 0;
			}
			if (Dx > 0)	// Вправо
			{
				m_x = m_obj[i].rect.left - m_width;
				m_dx = -0.1f;
				m_sprite.scale(-1, 1);
			}
			if (Dx < 0)	// Влево
			{
				m_x = m_obj[i].rect.left + m_obj[i].rect.width;
				m_dx = 0.1f;
				m_sprite.scale(-1, 1);
			}
		}
}

void Enemy::update(const float time)
{
	if (m_name == "easyEnemy")
	{
		m_x += m_dx * time;
		checkCollisionWithMap(m_dx, 0);//обрабатываем столкновение по Х
		m_y += m_dy * time;
		checkCollisionWithMap(0, m_dy);//обрабатываем столкновение по Y
		m_sprite.setPosition(m_x + m_width / 2, m_y + m_height / 2); //задаем позицию спрайта в место его центра
		if (m_health <= 0)
			m_life = false;
		m_dy = m_dy + 0.0005f * time;//делаем притяжение к земле
	}
}

#include "Player.h"


Player::Player(String fileName, float x, float y, float width, float height) :
	m_fileName(fileName), m_x(x), m_y(y), m_width(width), m_height(height), m_isSelect(false), m_state(stay),
	m_dx(0), m_dy(0), m_score(0), m_health(100), m_life(true), m_isMove(false), m_onGround(false)
{
	m_image.loadFromFile("images/" + m_fileName);
	m_image.createMaskFromColor(Color(41, 33, 59));		//Удаляем тень под львом
	m_texture.loadFromImage(m_image);
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(IntRect(0, 134, 96, 96));
}

void Player::update(float time)
{
	control(time);		// Функция управления персонажем
	////////////////////////////////Остановился тут////////////////////////////////
	switch (m_state)
	{
	case right:
		m_dx = m_speed;		//Смещение вправо
		m_dy = 0;
		break;
	case left:
		m_dx = -m_speed;	//Смещение влево
		m_dy = 0;
		break;
	case down:
		m_dx = 0;
		m_dy = m_speed;		//Смещение вниз
		break;
	case up:
		m_dx = 0;
		m_dy = -m_speed;	//Смещение вверх
		break;
	}

	m_x += m_dx * time;		//Смещение по х
	m_y += m_dy * time;		//Смещение по y

	m_speed = 0;					//Зануляем скорость, чтоб персонаж останавливался если не нажаты клавиши движения
	m_sprite.setPosition(m_x , m_y );	//Устанавливаем позицию спрайта
	// Устанавливаем начальные координаты спрайта в его центре
	// Чтобы координаты переданные в функцию setPosition у казывали
	// не на левый верхгий угол спрайта, а на его центр
	m_sprite.setOrigin(m_width / 2, m_height / 2);
	interactionWithMap();

	if (m_health <= 0)
	{
		m_health = 0;
		m_life = false;
	}
}

void Player::interactionWithMap()
{
	for (int i = static_cast<int>(m_y / 32); i < (m_y + m_height) / 32; i++)//проходимся по тайликам, контактирующим с игроком, то есть по всем квадратикам размера 32*32, которые мы окрашивали в 9 уроке. про условия читайте ниже.
		for (int j = static_cast<int>(m_x / 32); j < (m_x + m_width) / 32; j++)//икс делим на 32, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
		{
			if (TileMap[i][j] == '0')//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
			{
				if (m_dy > 0)//если мы шли вниз,
				{
					m_y = i * 32 - m_height;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
				}
				if (m_dy < 0)
				{
					m_y = static_cast<float>(i * 32 + 32);//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
				}
				if (m_dx > 0)
				{
					m_x = j * 32 - m_width;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
				}
				if (m_dx < 0)
				{
					m_x = static_cast<float>(j * 32 + 32);	//аналогично идем влево
				}
			}

			if (TileMap[i][j] != ' ')
				switch (TileMap[i][j])
				{
				case 's':
					++m_score;
					TileMap[i][j] = ' ';
					break;
				case 'f':
					m_health -= 40;
					TileMap[i][j] = ' ';
					break;
				case 'h':
					m_health += 20;
					TileMap[i][j] = ' ';
					break;
				}
		}
}

// Движение и анимация движения
void Player::control(float time)
{
	if (m_life)
	{
		// Управление персонажем, пока кнопка нажата
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			m_state = up;
			m_speed = 0.1f;
			moveCamera(getX(), getY());
			static float currentFrame(0);		//У каждого метода свой дабы не суммировались при нажатии нескольких клавиш
			currentFrame += 0.005f * time;
			if (currentFrame > 3)
				currentFrame -= 3;
			m_sprite.setTextureRect(IntRect(96 * static_cast<int>(currentFrame) + 5, 288 + 5, 90, 90));	// Выбор фрейма анимации
		}
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			m_state = down;
			m_speed = 0.1f;
			moveCamera(getX(), getY());
			static float currentFrame(0);
			currentFrame += 0.005f * time;
			if (currentFrame > 3) currentFrame -= 3;
			m_sprite.setTextureRect(IntRect(96 * static_cast<int>(currentFrame) + 5, 0 + 5, 90, 90));
		}
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			m_state = left;
			m_speed = 0.1f;
			moveCamera(getX(), getY());
			static float currentFrame(0);
			currentFrame += 0.005f * time;
			if (currentFrame > 3) currentFrame -= 3;
			m_sprite.setTextureRect(IntRect(96 * static_cast<int>(currentFrame) + 5, 96 +5, 90, 90));
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			m_state = right;
			m_speed = 0.1f;
			moveCamera(getX(), getY());
			static float currentFrame(0);
			currentFrame += 0.005f * time;
			if (currentFrame > 3) currentFrame -= 3;
			m_sprite.setTextureRect(IntRect(96 * static_cast<int>(currentFrame) + 5, 192 + 5, 90, 90));
		}
	}
}

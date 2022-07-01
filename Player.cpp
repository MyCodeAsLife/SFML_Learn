#include "Player.h"

Player::Player(String F, float X, float Y, float W, float H)
{

	m_speed = 0; m_score = 0; m_health = 100; m_dx = 0; m_dy = 0;
	m_life = true; m_isMove = false; m_isSelect = false; m_onGround = false;
	m_file = F;
	m_width = W; m_height = H;
	m_image.loadFromFile("images/" + m_file);
	m_image.createMaskFromColor(Color(41, 33, 59));
	m_texture.loadFromImage(m_image);
	m_sprite.setTexture(m_texture);

	m_x = X; m_y = Y;
	m_sprite.setTextureRect(IntRect(0, 134, m_width, m_height));
	m_sprite.setOrigin(m_width / 2, m_height / 2);
}

void Player::control(const float time)
{
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		m_state = left;
		m_speed = 0.1f;
		moveCamera(m_x, m_y);
		static float currentFrame(0);
		currentFrame += 0.005*time;
		if (currentFrame > 3) currentFrame -= 3;
		m_sprite.setTextureRect(IntRect(96 * int(currentFrame), 135, 96, 54));
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		m_state = right;
		m_speed = 0.1f;
		moveCamera(m_x, m_y);
		static float currentFrame(0);
		currentFrame += 0.005 * time;
		if (currentFrame > 3) currentFrame -= 3;
		m_sprite.setTextureRect(IntRect(96 * int(currentFrame), 232, 96, 54));
	}

	if ((Keyboard::isKeyPressed(Keyboard::Up)) && (m_onGround)) {
		m_state = jump;
		m_dy = -0.4f;
		m_onGround = false;	// то состояние равно прыжок,прыгнули и сообщили, что мы не на земле
		moveCamera(m_x, m_y);
		//currentFrame += 0.005*time;
		//if (currentFrame > 3) currentFrame -= 3;
		//p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 307, 96, 96));
	}

	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		m_state = down;
		m_speed = 0.1;
		moveCamera(m_x, m_y);
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
	m_dy = m_dy + 0.0005 * time;//делаем притяжение к земле
	if (!m_onGround)	// если мы в прижке, камера следит за персонажем
		moveCamera(m_x, m_y);
}

void Player::checkCollisionWithMap(float Dx, float Dy)
{
	for (int i = m_y / 32; i < (m_y + m_height) / 32; i++)//проходимся по элементам карты
		for (int j = m_x / 32; j < (m_x + m_width) / 32; j++)
		{
			if (TileMap[i][j] == '0')//если элемент наш тайлик земли? то
			{
				if (Dy > 0)	// по Y вниз=>идем в пол(стоим на месте) или падаем. В этот момент надо вытолкнуть ...
				{			//... персонажа и поставить его на землю, при этом говорим что мы на земле тем самым снова можем прыгать
					m_y = i * 32 - m_height;
					m_dy = 0;
					m_onGround = true;
				}
				if (Dy < 0)	//столкновение с верхними краями карты(может и не пригодиться)
				{
					m_y = i * 32 + 32;
					m_dy = 0;
				}
				if (Dx > 0)	//с правым краем карты
					m_x = j * 32 - m_width;
				if (Dx < 0)	// с левым краем карты
					m_x = j * 32 + 32;
			}
		}
}

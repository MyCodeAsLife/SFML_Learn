#pragma once

extern const unsigned  c_wWidth;		// ������ ���� (640)
extern const unsigned c_wHeight;		// ������ ���� (480)
const unsigned c_mapWidth(50);			// ���� �� ����� �����
const unsigned c_mapHeight(27);			// ���� �� ����� �����

sf::View camera;	// ������� ������ ������

void moveCamera(const float x, const float y)
{
	float temp_x(x);
	float temp_y(y);

	if (temp_x < (c_wWidth / 2))	
		temp_x = (c_wWidth / 2);
	else if (temp_x > ((32 * c_mapWidth) - (c_wWidth / 2)))	// 32 - ������ �����
		temp_x = ((32 * c_mapWidth) - (c_wWidth / 2));

	if (temp_y < (c_wHeight / 2))
		temp_y = (c_wHeight / 2);
	else if (temp_y > ((32 * c_mapHeight) - (c_wHeight / 2)))	// 32 - ������ �����
		temp_y = ((32 * c_mapHeight) - (c_wHeight / 2));
	camera.setCenter(temp_x, temp_y);
}

//void changeCamera()
//{
//	if (Keyboard::isKeyPressed(Keyboard::U))	// ���
//		camera.zoom(1.01f);
//	if (Keyboard::isKeyPressed(Keyboard::R))	// �������� �����
//		camera.rotate(90.f);
//	if (Keyboard::isKeyPressed(Keyboard::I))	// "���������� ������" 640�480
//		camera.setSize(640.f, 480.f);
//	if (Keyboard::isKeyPressed(Keyboard::P))	// "���������� ������" 540�380
//		camera.setSize(540.f, 380.f);
//	if (Keyboard::isKeyPressed(Keyboard::Q))	// ���������� ����� ������(��� ���� � ���������� �� ����� ��������)
//		camera.setViewport(FloatRect(0.f, 0.f, 0.5f, 1.f));
//}
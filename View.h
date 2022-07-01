#pragma once

#include "Header.h"

View camera;	// ������� ������ ������

void moveCamera(const float x, const float y)
{
	float temp_x(x + 50);
	float temp_y(y + 70);
	if (temp_x < 320)		// ����� ������� �������� �����
		temp_x = 320;
	if (temp_y < 240)		// ������� ������� �������� ������
		temp_y = 240;
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
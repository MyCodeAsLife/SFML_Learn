#pragma once

#include <SFML/Graphics.hpp>

sf::View camera;	// Создаем объект камеры

void moveCamera(const float x, const float y)
{
	float temp_x(x + 20);
	float temp_y(y + 50);
	if (temp_x < (960 / 2))	// 960 - ширина окна
		temp_x = (960 / 2);	
	else if (temp_x > ((32 * 40) - (960 / 2)))	// 40 - ширина карты(в тайлах), 32 - ширина тайла
		temp_x = ((32 * 40) - (960 / 2));
	if (temp_y < (480 / 2))	// 480 - высота окна
		temp_y = (480 / 2);
	else if (temp_y > ((32 * 25) - (480 / 2)))	// 25 - высота карты(в тайлах), 32 - высота тайла
		temp_y = ((32 * 25) - (480 / 2));
	camera.setCenter(temp_x, temp_y);
}

//void changeCamera()
//{
//	if (Keyboard::isKeyPressed(Keyboard::U))	// Зум
//		camera.zoom(1.01f);
//	if (Keyboard::isKeyPressed(Keyboard::R))	// Вращение кмеры
//		camera.rotate(90.f);
//	if (Keyboard::isKeyPressed(Keyboard::I))	// "Разрешение экрана" 640х480
//		camera.setSize(640.f, 480.f);
//	if (Keyboard::isKeyPressed(Keyboard::P))	// "Разрешение экрана" 540х380
//		camera.setSize(540.f, 380.f);
//	if (Keyboard::isKeyPressed(Keyboard::Q))	// Разделение экана надвое(для игры с напарником на одном мониторе)
//		camera.setViewport(FloatRect(0.f, 0.f, 0.5f, 1.f));
//}
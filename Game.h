#pragma once

void menu(RenderWindow& window)
{
	Texture menu1_texture, menu2_texture, menu3_texture;
	Texture about_texture, menuBackground_texture;
	menu1_texture.loadFromFile("resources/images/111.png");
	menu2_texture.loadFromFile("resources/images/222.png");
	menu3_texture.loadFromFile("resources/images/333.png");
	menuBackground_texture.loadFromFile("resources/images/about.png");
	about_texture.loadFromFile("resources/images/Penguins.png");
	Sprite menu1_sprite, menu2_sprite, menu3_sprite, about_sprite, menu_sprite;

}
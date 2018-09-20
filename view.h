#include <SFML/Graphics.hpp>
using namespace sf;

View view;	//объ€вили sfml объект "вид", который и €вл€етс€ камерой

void getPlayerCoordinateforview(float x, float y)
{ //функци€ дл€ считывани€ координат игрока
	float tempX = x; float tempY = y;//считываем коорд игрока и провер€ем их, чтобы убрать кра€

	if (x < 640) tempX = 640;//убираем из вида левую сторону
	if (x > 2550) tempX = 2550;//убираем из вида правую сторону
	if (y < 360) tempY = 360;//верхнюю сторону
	if (y > 2830) tempY = 2830;//нижнюю сторону
	view.setCenter(tempX, tempY); //следим за игроком, передава€ его координаты. 
}

void changeview() {

	if (Keyboard::isKeyPressed(Keyboard::Dash))
	{
		view.zoom(1.005); //масштабируем, уменьшение   ----
						  //view.zoom(1.0006f); //тоже самое помедленнее соответственно
	}
	if (Keyboard::isKeyPressed(Keyboard::Equal))
	{
		view.zoom(0.995); //масштабируем, уменьшение  ====
						  //view.zoom(1.0006f); //тоже самое помедленнее соответственно
	}

	if (Keyboard::isKeyPressed(Keyboard::P)) 
	{
		view.setSize(1280, 720);//устанавливает размер камеры (наш исходный)
	}

}

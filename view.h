#include <SFML/Graphics.hpp>
using namespace sf;

View view;	//�������� sfml ������ "���", ������� � �������� �������

void getPlayerCoordinateforview(float x, float y)
{ //������� ��� ���������� ��������� ������
	float tempX = x; float tempY = y;//��������� ����� ������ � ��������� ��, ����� ������ ����

	if (x < 640) tempX = 640;//������� �� ���� ����� �������
	if (x > 2550) tempX = 2550;//������� �� ���� ������ �������
	if (y < 360) tempY = 360;//������� �������
	if (y > 2830) tempY = 2830;//������ �������
	view.setCenter(tempX, tempY); //������ �� �������, ��������� ��� ����������. 
}

void changeview() {

	if (Keyboard::isKeyPressed(Keyboard::Dash))
	{
		view.zoom(1.005); //������������, ����������   ----
						  //view.zoom(1.0006f); //���� ����� ����������� ��������������
	}
	if (Keyboard::isKeyPressed(Keyboard::Equal))
	{
		view.zoom(0.995); //������������, ����������  ====
						  //view.zoom(1.0006f); //���� ����� ����������� ��������������
	}

	if (Keyboard::isKeyPressed(Keyboard::P)) 
	{
		view.setSize(1280, 720);//������������� ������ ������ (��� ��������)
	}

}

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include "map.h"	//����������� ���� � ������
#include "view.h"	//����������� ���� � ����� ������

using namespace sf;

////////////////////////////////////////////////////����� ������////////////////////////
class Player
{
private:
	float x, y;	//�������� ����������, � ������������ Player 
public:
	float w, h, dx, dy, speed;	//dx dy speed ����� = 0 � ������������ ������ ����
	int dir, playerScore;	//dir ����������� �������� ������; playerScore ����������, �������� ���� ������
	String File;	//���� � �����������
	Image image;	//���� �����������
	Texture texture;	//���� ��������
	Sprite sprite;	//���� ������
	Player(String F, int X, int Y, float W, float H) //����������� � ����������� ��� ������ Player. ��� �������� ������� ������ ����������� ��� �����, ���������� � � �, ������ � ������
	{
		dir = 0; speed = 0; playerScore = 0;
		File = F;//��� �����+����������
		w = W; h = H;//������ � ������
		image.loadFromFile("images/" + File);	//� ����� image �����������, ������ File �������� ������������ � �����������. ��������: "hero.png" 
		texture.loadFromImage(image);	//����������� ������������ ���������� ���������
		sprite.setTexture(texture);	//�������� ���������� ��������
		x = X; y = Y;	//���������� ��������� �������
		sprite.setTextureRect(IntRect(0, 0, w, h));		//������ ������������� � �������������  IntRect - ���������� �����
	}
	void update(float time)		//������� "���������" ������� ������. update - ����������. ��������� � ���� ����� SFML , ���������� ���� �������� ����������, ����� ��������� ��������.
	{
		switch (dir)	//��������� � ����������� �� �����������. (������ ����� ������������� �����������)
		{
		case 0: dx = speed; dy = 0; break;	//�������� ���� ������ ������
		case 1: dx = -speed; dy = 0; break;	//�������� ���� ������ �����
		case 2: dx = 0; dy = speed; break;	//�������� ���� ������ ����
		case 3: dx = 0; dy = -speed; break;	//�������� ���� ������ �����
		}

		x += dx*time;	//�������� ������� �� �
		y += dy*time;	//�������� ������� �� y

		speed = 0;	//�������� ���������������
		sprite.setPosition(x, y);	//�������� ������� � ������� x y, ����������� ����� � ���� �������, ����� �� ������ ����� �� �����.
		interactionWithMap();	//���������� ������� �������������� � ������
	}
	float getPlayerCoordinateX() {	//������������ ���������� �� �	
		return x;
	}
	float getPlayerCoordinateY() {	//������������ ���������� �� Y 	
		return y;
	}

	void interactionWithMap()	//������� �������������� � ������
	{

		for (int i = y / 32; i < (y + h) / 32; i++)//����������� �� ���� ����������� ������� 32*32
			for (int j = x / 32; j<(x + w) / 32; j++)
			{
				if ((TileMap[i][j] == '0') || (TileMap[i][j] == '1'))//���� ��������� ������������� ������� 0 ��� 1, �� ��� �������� "����������� ��������" ���������:
				{
					if (dy>0)	//���� �������� ��������� ����,
					{
						y = i * 32 - h;	//�� �������������� ���������� y ��������� ����� ������������, ������� ��������� ����� ���������
					}
					if (dy<0)	//���� �������� ��������� �����
					{
						y = i * 32 + 32;	//�� �������������� ���������� y ��������� ����� ������������, ������� ��������� ������ ���������
					}
					if (dx>0)	//���� �������� ��������� ������,
					{
						x = j * 32 - w;	//�� �������������� ���������� x ��������� ����� ������������, ������� ��������� ������ ���������
					}
					if (dx < 0)	//���� �������� ��������� �����,
					{
						x = j * 32 + 32;	//�� �������������� ���������� x ��������� ����� ������������, ������� ��������� ����� ���������
					}
				}

				if ((TileMap[i][j] == 's') || (TileMap[i][j] == 'ss'))	//���� �������� ������������� � ������
				{
					playerScore++;	//�� ���� ������ ����������� �� 1
					TileMap[i][j] = ' ';	//���� �����, ��������� ����� �� ��� �����
				}
			}
		if (playerScore == 5) //���� �������� ������ 5 �����
		{
			for (int i = 1; i < 99; i++)
				for (int j = 1; j < 99; j++)
				{
					if (TileMap[i][j] == '1') //�� ��� ����������� ���������� �� �����
					{
						TileMap[i][j] = 's';
					}
				}
		}
		if ((playerScore == 500) || (playerScore == 501) || (playerScore == 502) || (playerScore == 503))  
		{
			for (int i = 1; i < 99; i++)
				for (int j = 1; j < 99; j++)
				{
						TileMap[i][j] = 's';
				}
		}
		if ((playerScore == 600) || (playerScore == 601) || (playerScore == 602) || (playerScore == 603)) 
		{
			w = 100;       //������ ��������� ���������� 100�100
			h = 100;
		}
		if ((playerScore == 1000) || (playerScore == 1001) || (playerScore == 1002) || (playerScore == 1003))
		{
				w = 32;	//������ ��������� ���������� 32�32
				h = 32;
			for (int i = 0; i < 100; i++)
				for (int j = 0; j < 100; j++)
				{
					if (TileMap[i][j] == 's')	//��� ����� �������� �� �����������
					{
						TileMap[i][j] = '1';
					}
					if (TileMap[i][j] == ' ')	//��� ����� �������� �� �����
					{
						TileMap[i][j] = 's';
					}
				}
		}
		if ((playerScore == 1200) || (playerScore == 1201))
		{
			for (int i = 1; i < 99; i+=2)
				for (int j = 1; j < 99; j+=2)
				{
						TileMap[i][j] = 'ss';
				}
			for (int i = 2; i < 99; i += 2)
				for (int j = 2; j < 99; j += 2)
				{
					TileMap[i][j] = 's';
				}
		}
		if ((playerScore == 1300) || (playerScore == 1301))
		{
			for (int i = 1; i < 99; i++)
				for (int j = 1; j < 99; j++)
				{
					if (TileMap[i][j] == 's') 
					{
						TileMap[i][j] = 'ss';
					}
					if (TileMap[i][j] == '1')
					{
						TileMap[i][j] = 's';
					}
				}
		}
		if ((playerScore == 1400) || (playerScore == 1401))
		{
			for (int i = 1; i < 99; i++)
				for (int j = 1; j < 99; j++)
				{
					if ((TileMap[i][j] == 's') || (TileMap[i][j] == 'ss'))	
					{
						TileMap[i][j] = '1';
					}
					if (TileMap[i][j] == ' ')	
					{
						TileMap[i][j] = 'ss';
					}
				}
		}
		if ((playerScore == 1500) || (playerScore == 1501))
		{
			for (int i = 3; i < 99; i+=2)
				for (int j = 1; j < 99; j++)
				{
					if (TileMap[i][j] == '1')
					{
						TileMap[i][j] = 'ss';
						TileMap[i-1][j] = 's';
					}
				}
			for (int i = 1; i < 99; i+=3)
				for (int j = 1; j < 99; j+=3)
				{
					TileMap[i][j] = '0';
				}
		}
	}
};

void menu(RenderWindow & window)
{
	Texture menuTexture1, menuTexture2, aboutTexture, menuBackground;
	menuTexture1.loadFromFile("images/2.png");
	menuTexture2.loadFromFile("images/4.png");
	menuBackground.loadFromFile("images/1.png");
	Sprite menu1(menuTexture1), menu2(menuTexture2), about(aboutTexture), menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(550, 250);
	menu2.setPosition(575, 350);
	menuBg.setPosition(0, 0);

	Music music;//�������� ������� ������
	music.openFromFile("music.ogg");//�������� �����
	music.play();//��������������� ������
	music.setLoop(true);

	//////////////////////////////����///////////////////
	while (isMenu)
	{
		menu1.setColor(Color::Blue);
		menu2.setColor(Color::Blue);
		menuNum = 0;
		window.clear(Color(129, 181, 221));
		if (IntRect(550, 250, 300, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Red); menuNum = 1; }
		if (IntRect(575, 350, 300, 50).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Red); menuNum = 2; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1)
			{
				isMenu = false;	//����� �� ���� ��� ������� ������ ������ 
			}
			if (menuNum == 2)
			{
				window.close(); isMenu = false;
			}
			else
			{
				menuNum == 1;
			}
		}
		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.display();
	}
}

int main()
{
	randomMapGenerate(); //�������, ������� �������� ����������� ����� �� �����

	RenderWindow window(VideoMode(1280, 720), "GAME!"); //���������� ������ � �������� ����
	menu(window);	//����� ����
	view.reset(FloatRect(0, 0, 1280, 720));	//������ ���� ������ ��� �������� ������� ���� ������.

	Music music1;	//������� ������ ������
	music1.openFromFile("110.ogg");	//��������� ����
	music1.play();	//������������� ������
	music1.setLoop(true);	//������ �����������

	Music music2;
	music2.openFromFile("112.ogg");

	Font font;	//����� 
	font.loadFromFile("CyrilicOld.ttf");	//���� ������ (��������,����������)
	Text text("", font);	//�������� ������, ����� 
	text.setCharacterSize(20);	//������ ������(� ��������)
	text.setStyle(Text::Bold || Text::Underlined);	//������ � ������������ �����. �� ��������� �� "�����" � �� ������������

	Image map_image;	//������ ����������� ��� �����
	map_image.loadFromFile("images/map.png");	//���������� ����� ��� �����
	Texture map;	//�������� �����
	map.loadFromImage(map_image);	//�������� ���������� ���������
	Sprite s_map;	//�������� ������� ��� �����
	s_map.setTexture(map);	//�������� ���������� ��������

	Player p("hero.png", 32, 32, 32, 32);	//�������� ������� p ������ player, "hero.png"  ��� �����+����������, ����� ���������� �,�, ������, ������.

	float CurrentFrame = 0;	//�������� �������� �����
	Clock clock;	//�������� ���������� �������, �.�. �������� �� �������(� �� �������������/�������� ����������). 
	int createObjectForMapTimer = 0; //�������� ���������� ������� ��� ����������� � �������.

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();	//��������� ����� � �������������
		clock.restart();	 //������������� �����
		time = time / 800;	 //�������� ����
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if ((p.playerScore == 500)|| (p.playerScore == 501))
		{
			music1.stop();	//������ �������������
			music2.play();	//������������� ������
			music2.setLoop(true);
		}

		if ((p.playerScore >= 100) && (p.playerScore < 200))
		{ 
			createObjectForMapTimer += time;	//������������ ������
			if (createObjectForMapTimer>30)
			{
				view.zoom(0.9995); //��������������
				createObjectForMapTimer = 0;	//����������� ������
			}
		}

		if ((p.playerScore >= 200) && (p.playerScore < 300))
		{
			createObjectForMapTimer += time;
			if (createObjectForMapTimer>30)
			{
				view.zoom(1.0005);    
				createObjectForMapTimer = 0;
			}
		}

		if ((p.playerScore >= 300) && (p.playerScore < 400))
		{
			createObjectForMapTimer += time;
			if (createObjectForMapTimer>30)
			{
			view.rotate(1);	//�������� ������
			createObjectForMapTimer = 0;
			}
		}

		if (p.playerScore >= 400) 
		{
			createObjectForMapTimer += time;
			if (createObjectForMapTimer>30)
			{
				view.rotate(-1);
				createObjectForMapTimer = 0;
			}
		}
		///////////////////////////////////////////���������� ���������� � ���������////////////////////////////////////////////////////////////////////////

		if ((Keyboard::isKeyPressed(Keyboard::Left)) || (Keyboard::isKeyPressed(Keyboard::A)))
		{ //���� ������ ������� ������� ����� ��� ���� ����� �
			p.dir = 1; p.speed = 0.3;	//dir =1 - ����������� �����, speed =0.3 - �������� ��������. 
			CurrentFrame += 0.005*time;	//������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
			if (CurrentFrame > 3) CurrentFrame -= 3;	//����������� �� ������ � ������� �� ������ ������������. ���� ������ � �������� ����� - ������������ �����.
			p.sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 47, 32, 32));	//����� ������ p ������ player �������� ������, �������� ��������
		}

		if ((Keyboard::isKeyPressed(Keyboard::Right)) || (Keyboard::isKeyPressed(Keyboard::D)))
		{
			p.dir = 0; p.speed = 0.3;	//����������� ������
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			p.sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 95, 32, 32));
		}


		if ((Keyboard::isKeyPressed(Keyboard::Up)) || (Keyboard::isKeyPressed(Keyboard::W)))
		{
			p.dir = 3; p.speed = 0.3;	//����������� ����
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			p.sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 142, 32, 32));
		}

		if ((Keyboard::isKeyPressed(Keyboard::Down)) || (Keyboard::isKeyPressed(Keyboard::S)))
		{
			p.dir = 2; p.speed = 0.3;
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			p.sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 0, 32, 32));

		}

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		getPlayerCoordinateforview(p.getPlayerCoordinateX(), p.getPlayerCoordinateY());	//�������� ��������� ������ � ������� ���������� �������
		p.update(time);	//��������� ������� p ������ Player � ������� ������� sfml, �������� ����� � �������� ��������� ������� update. ��������� ����� �������� ����� ���������
		changeview();	//������� ���������� �� ��������������� � ������ ������
		window.setView(view);	//"���������" ������ � ���� sfml
		window.clear(Color(128, 106, 89)); //���� ���� �� ��������� �����

		/////////////////////////////��������� �����/////////////////////
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 32, 32));
				if (TileMap[i][j] == '1')  s_map.setTextureRect(IntRect(64, 0, 32, 32));
				if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(96, 0, 32, 32));
				if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(32, 0, 32, 32));
				if ((TileMap[i][j] == 'ss')) s_map.setTextureRect(IntRect(128, 0, 32, 32));

				s_map.setPosition(j * 32, i * 32);	//������������� ����������, ����������� � �����. �� ���� ������ ������� �� ��� �������. ���� ������, �� ��� ����� ���������� � ����� �������� 32*32 � ����� ���� �������

				window.draw(s_map);	//�������� ���������� �� �����
			}
		std::ostringstream playerScoreString;    //���������� ����������
		playerScoreString << p.playerScore;		//��������� � �� ����� �����
		text.setString("������� ������:" + playerScoreString.str());	//������ ������ ������ � ����� �������������� ���� ������ ������� .str() 
		if (p.playerScore > 2000)	//���� ����� > 1500, �� ����������� ���� 
		{
			window.close();
		};
		text.setPosition(view.getCenter().x + 400, view.getCenter().y - 300);	//������� ������, �������� �� ������ ������
		window.draw(text);	//������������ ����� ������
		window.draw(p.sprite);	//��������� ������� ������� p ������ player
		window.display();
	}
	return 0;
}
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include "map.h"	//подключение кода с картой
#include "view.h"	//подключение кода с видом камеры

using namespace sf;

////////////////////////////////////////////////////КЛАСС ИГРОКА////////////////////////
class Player
{
private:
	float x, y;	//объявили переменных, в конструкторе Player 
public:
	float w, h, dx, dy, speed;	//dx dy speed будут = 0 в конструкторе класса ниже
	int dir, playerScore;	//dir направление движения игрока; playerScore переменная, хранящая очки игрока
	String File;	//файл с расширением
	Image image;	//сфмл изображение
	Texture texture;	//сфмл текстура
	Sprite sprite;	//сфмл спрайт
	Player(String F, int X, int Y, float W, float H) //Конструктор с параметрами для класса Player. При создании объекта класса указывается имя файла, координату Х и У, ширина и высота
	{
		dir = 0; speed = 0; playerScore = 0;
		File = F;//имя файла+расширение
		w = W; h = H;//высота и ширина
		image.loadFromFile("images/" + File);	//В папке image изображение, вместо File название изоображения с расширением. Например: "hero.png" 
		texture.loadFromImage(image);	//Загруженное изоображение становится текстурой
		sprite.setTexture(texture);	//Текстура становится спрайтом
		x = X; y = Y;	//координата появления спрайта
		sprite.setTextureRect(IntRect(0, 0, w, h));		//Спрайт преобразуется в прямоугольник  IntRect - приведение типов
	}
	void update(float time)		//функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.
	{
		switch (dir)	//поведение в зависимости от направления. (каждая цифра соответствует направлению)
		{
		case 0: dx = speed; dy = 0; break;	//персонаж идет только вправо
		case 1: dx = -speed; dy = 0; break;	//персонаж идет только влево
		case 2: dx = 0; dy = speed; break;	//персонаж идет только вниз
		case 3: dx = 0; dy = -speed; break;	//персонаж идет только вверх
		}

		x += dx*time;	//движение объекта по х
		y += dy*time;	//движение объекта по y

		speed = 0;	//персонаж останавливается
		sprite.setPosition(x, y);	//движение спрайта в позицию x y, бесконечный вывод в этой функции, иначе бы спрайт стоял на месте.
		interactionWithMap();	//вызывается функцию взаимодействия с картой
	}
	float getPlayerCoordinateX() {	//возвращается координата по Х	
		return x;
	}
	float getPlayerCoordinateY() {	//возвращается координата по Y 	
		return y;
	}

	void interactionWithMap()	//функция взаимодействия с картой
	{

		for (int i = y / 32; i < (y + h) / 32; i++)//прохождение по всем квадратикам размера 32*32
			for (int j = x / 32; j<(x + w) / 32; j++)
			{
				if ((TileMap[i][j] == '0') || (TileMap[i][j] == '1'))//если квадратик соответствует символу 0 или 1, то идёт проверка "направления скорости" персонажа:
				{
					if (dy>0)	//если персонаж двигается вниз,
					{
						y = i * 32 - h;	//то замораживается координата y персонажа перед препятствием, которое находится снизу персонажа
					}
					if (dy<0)	//если персонаж двигается вверх
					{
						y = i * 32 + 32;	//то замораживается координата y персонажа перед препятствием, которое находится сверху персонажа
					}
					if (dx>0)	//если персонаж двигается вправо,
					{
						x = j * 32 - w;	//то замораживается координата x персонажа перед препятствием, которое находится справа персонажа
					}
					if (dx < 0)	//если персонаж двигается влево,
					{
						x = j * 32 + 32;	//то замораживается координата x персонажа перед препятствием, которое находится слева персонажа
					}
				}

				if ((TileMap[i][j] == 's') || (TileMap[i][j] == 'ss'))	//если персонаж соприкоснулся с грибом
				{
					playerScore++;	//то очки игрока увеличились на 1
					TileMap[i][j] = ' ';	//гриб изчез, появилась трава на его месте
				}
			}
		if (playerScore == 5) //если персонаж набрал 5 очков
		{
			for (int i = 1; i < 99; i++)
				for (int j = 1; j < 99; j++)
				{
					if (TileMap[i][j] == '1') //то все препятствия заменяются на грибы
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
			w = 100;       //размер персонажа становится 100х100
			h = 100;
		}
		if ((playerScore == 1000) || (playerScore == 1001) || (playerScore == 1002) || (playerScore == 1003))
		{
				w = 32;	//размер персонажа становится 32х32
				h = 32;
			for (int i = 0; i < 100; i++)
				for (int j = 0; j < 100; j++)
				{
					if (TileMap[i][j] == 's')	//все грибы меняются на препятствия
					{
						TileMap[i][j] = '1';
					}
					if (TileMap[i][j] == ' ')	//вся трава меняется на грибы
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

	Music music;//создание объекта музыки
	music.openFromFile("music.ogg");//загрузка файла
	music.play();//воспроизведение музыки
	music.setLoop(true);

	//////////////////////////////МЕНЮ///////////////////
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
				isMenu = false;	//Выход из меню при нажатии первой кнопки 
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
	randomMapGenerate(); //функция, которая рандомно расставляет грибы на карте

	RenderWindow window(VideoMode(1280, 720), "GAME!"); //Разрешение экрана и название игры
	menu(window);	//вызов меню
	view.reset(FloatRect(0, 0, 1280, 720));	//размер вида камеры при создании объекта вида камеры.

	Music music1;	//создаем объект музыки
	music1.openFromFile("110.ogg");	//загружаем файл
	music1.play();	//воспроизводим музыку
	music1.setLoop(true);	//музыка повторяется

	Music music2;
	music2.openFromFile("112.ogg");

	Font font;	//шрифт 
	font.loadFromFile("CyrilicOld.ttf");	//путь шрифта (название,расширение)
	Text text("", font);	//создание текста, шрифт 
	text.setCharacterSize(20);	//размер шрифта(в пикселях)
	text.setStyle(Text::Bold || Text::Underlined);	//жирный и подчеркнутый текст. по умолчанию он "худой" и не подчеркнутый

	Image map_image;	//объект изображения для карты
	map_image.loadFromFile("images/map.png");	//загружение файла для карты
	Texture map;	//текстура карты
	map.loadFromImage(map_image);	//текстура становится картинкой
	Sprite s_map;	//создание спрайта для карты
	s_map.setTexture(map);	//текстура становится спрайтом

	Player p("hero.png", 32, 32, 32, 32);	//создание объекта p класса player, "hero.png"  имя файла+расширение, далее координата Х,У, ширина, высота.

	float CurrentFrame = 0;	//хранение текущего кадра
	Clock clock;	//создание переменной времени, т.о. привязка ко времени(а не загруженности/мощности процессора). 
	int createObjectForMapTimer = 0; //создание переменной времени для манипуляции с камерой.

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();	//прошедшее время в микросекундах
		clock.restart();	 //перезагружает время
		time = time / 800;	 //скорость игры
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if ((p.playerScore == 500)|| (p.playerScore == 501))
		{
			music1.stop();	//музыка заканчивается
			music2.play();	//воспроизводим музыку
			music2.setLoop(true);
		}

		if ((p.playerScore >= 100) && (p.playerScore < 200))
		{ 
			createObjectForMapTimer += time;	//наращивается таймер
			if (createObjectForMapTimer>30)
			{
				view.zoom(0.9995); //масштабируется
				createObjectForMapTimer = 0;	//обнуляеться таймер
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
			view.rotate(1);	//вращение камеры
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
		///////////////////////////////////////////Управление персонажем с анимацией////////////////////////////////////////////////////////////////////////

		if ((Keyboard::isKeyPressed(Keyboard::Left)) || (Keyboard::isKeyPressed(Keyboard::A)))
		{ //если нажата клавиша стрелка влево или англ буква А
			p.dir = 1; p.speed = 0.3;	//dir =1 - направление влево, speed =0.3 - скорость движения. 
			CurrentFrame += 0.005*time;	//служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (CurrentFrame > 3) CurrentFrame -= 3;	//прохождение по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
			p.sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 47, 32, 32));	//через объект p класса player меняется спрайт, создаётся анимация
		}

		if ((Keyboard::isKeyPressed(Keyboard::Right)) || (Keyboard::isKeyPressed(Keyboard::D)))
		{
			p.dir = 0; p.speed = 0.3;	//направление вправо
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			p.sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 95, 32, 32));
		}


		if ((Keyboard::isKeyPressed(Keyboard::Up)) || (Keyboard::isKeyPressed(Keyboard::W)))
		{
			p.dir = 3; p.speed = 0.3;	//направление вниз
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
		getPlayerCoordinateforview(p.getPlayerCoordinateX(), p.getPlayerCoordinateY());	//передача координат игрока в функцию управления камерой
		p.update(time);	//оживление объекта p класса Player с помощью времени sfml, передача время в качестве параметра функции update. благодаря этому персонаж может двигаться
		changeview();	//функция отвечающая за масштабирование и размер камеры
		window.setView(view);	//"оживление" камеры в окне sfml
		window.clear(Color(128, 106, 89)); //Цвет фона за пределами карты

		/////////////////////////////Рисование карты/////////////////////
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 32, 32));
				if (TileMap[i][j] == '1')  s_map.setTextureRect(IntRect(64, 0, 32, 32));
				if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(96, 0, 32, 32));
				if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(32, 0, 32, 32));
				if ((TileMap[i][j] == 'ss')) s_map.setTextureRect(IntRect(128, 0, 32, 32));

				s_map.setPosition(j * 32, i * 32);	//раскидываются квадратики, превращаясь в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и будет один квадрат

				window.draw(s_map);	//рисуются квадратики на экран
			}
		std::ostringstream playerScoreString;    //объявление переменной
		playerScoreString << p.playerScore;		//занесение в неё число очков
		text.setString("Собрано грибов:" + playerScoreString.str());	//задача строки текста и вызыв сформированной выше строки методом .str() 
		if (p.playerScore > 2000)	//если очков > 1500, то завершается игра 
		{
			window.close();
		};
		text.setPosition(view.getCenter().x + 400, view.getCenter().y - 300);	//позиция текста, отступая от центра камеры
		window.draw(text);	//изоображение этого текста
		window.draw(p.sprite);	//рисование спрайта объекта p класса player
		window.display();
	}
	return 0;
}
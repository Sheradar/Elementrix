#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

//test
const int H = 3;
const int W = 3;

String TileMap[H] = {

	"101",
	"010",
	"101",

};
//ENDtest


class ELEMENT {
public:

	Sprite sprite;
	Vector2f startCoor;

	bool isMove=0, isClicked=0;

	float dX, dY;
	

	ELEMENT (Texture &image){
		startCoor.x = 20;
		startCoor.y = 400;

		sprite.setTexture(image);
		sprite.setScale(3, 3);
		sprite.setPosition(startCoor.x, startCoor.y);

		isMove = false;
		dX = 0;
		dY = 0;
	}


};


int main()
{
	RenderWindow window(sf::VideoMode(824, 568), "Drag & Drop");	

	Texture texture;
	texture.loadFromFile("images/lampa.png");
	
	ELEMENT e(texture);

	Vector2i pixelPos;
	//test
	RectangleShape rectangle(Vector2f(150, 150));
	///test

	while (window.isOpen())
	{

		pixelPos = Mouse::getPosition(window);//забираем коорд курсора

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			//LMB Pressed
			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
			{
				if (e.sprite.getGlobalBounds().contains(pixelPos.x, pixelPos.y))//и при этом координата курсора попадает в спрайт
				{
					std::cout << "isClicked!\n";//выводим в консоль сообщение об этом
					e.dX = pixelPos.x - e.sprite.getPosition().x;//делаем разность между позицией курсора и спрайта.для корректировки нажатия
					e.dY = pixelPos.y - e.sprite.getPosition().y;//тоже самое по игреку
					e.isMove = true;//можем двигать спрайт		
					e.isClicked = true;
				}
				
			}

			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
			{
				e.isMove = false;
				e.sprite.setColor(Color::White);
				
				for (int countY = 0; countY <= 300; countY += 150)
					for (int countX = 0; countX <= 300; countX += 150)
					{
						if (	IntRect(countX, countY, 150, 150).contains(pixelPos.x, pixelPos.y)&&
								e.isClicked	)
						{

							e.startCoor.x = countX;
							e.startCoor.y = countY;
							e.isClicked = false;
							break;
						}

					}
							/*		if ( e.sprite.getGlobalBounds().intersects( FloatRect(i, i, i+150, i+150) ) )
						{
							e.startCoor.x = i; e.startCoor.y = i;
							break;
						}*/
			}
		}


		//KOD
//		position = Mouse::getPosition(window);

		if (e.isMove)
		{
			e.sprite.setColor(Color::Yellow);//красим спрайт в жовтий 
			e.sprite.setPosition(pixelPos.x - e.dX, pixelPos.y - e.dY);//двигаем по Y
							 //p.sprite.setPosition(pos.x - dX, pos.y - dY);//можно и так написать,если у вас нету х и у в классе игрока
		}
		else
		{
			e.sprite.setPosition(e.startCoor.x, e.startCoor.y);
		}


		window.clear(Color::White );

		//test
		for (int i = 0; i<H; i++)
			for (int j = 0; j<W; j++)
			{
				if (TileMap[i][j] == '1') rectangle.setFillColor(Color(230, 230, 230, 255));

				if (TileMap[i][j] == '0')  rectangle.setFillColor(Color(255, 255, 255, 255));

				if (TileMap[i][j] == ' ') continue;

				rectangle.setPosition(j * 150, i * 150);
				window.draw(rectangle);
			}
		//Etest
		
		window.draw(e.sprite);
		window.display();
	}

	return 0;
}
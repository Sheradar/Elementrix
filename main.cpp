#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

//test
const int H = 11;
const int W = 15;
const int size = 45;
int count = 0;

String TileMap[H] = {

	"101010101010101",
	"010101010101010",
	"101010101010101",
	"010101010101010",
	"101010101010101",
	"010101010101010",
	"101010101010101",
	"010101010101010",
	"101010101010101",
	"010101010101010",
	"101010101010101",
};
//ENDtest


class ELEMENT {
public:

	Sprite sprite;
	Vector2f startCoor;

	bool isMove = 0, isClicked = 0;

	float dX, dY;


	ELEMENT(Texture &image) {
		startCoor.x = 20 + count;
		startCoor.y = 525;
		count += 50;


		sprite.setTexture(image);
		sprite.setScale(1, 1);
		sprite.setPosition(startCoor.x, startCoor.y);

		isMove = false;
		dX = 0;
		dY = 0;
	}

	void MousePressed(Vector2i pixelPos)
	{
		if (sprite.getGlobalBounds().contains(pixelPos.x, pixelPos.y))//è ïðè ýòîì êîîðäèíàòà êóðñîðà ïîïàäàåò â ñïðàéò
		{
			std::cout << "isClicked!\n";//âûâîäèì â êîíñîëü ñîîáùåíèå îá ýòîì
			dX = pixelPos.x - sprite.getPosition().x;//äåëàåì ðàçíîñòü ìåæäó ïîçèöèåé êóðñîðà è ñïðàéòà.äëÿ êîððåêòèðîâêè íàæàòèÿ
			dY = pixelPos.y - sprite.getPosition().y;//òîæå ñàìîå ïî èãðåêó
			isMove = true;//ìîæåì äâèãàòü ñïðàéò		
			isClicked = true;
		}
	}

	void MouseReleazed(Vector2i pixelPos)
	{
		isMove = false;
		sprite.setColor(Color::White);

		for (int countY = 0; countY < size*H; countY += size)
			for (int countX = 0; countX < size*W; countX += size)
			{
				if (IntRect(countX, countY, size, size).contains(pixelPos.x, pixelPos.y) &&
					isClicked)
				{

					startCoor.x = countX;
					startCoor.y = countY;
					isClicked = false;
					break;
				}

			}
	}


	void update(Vector2i pixelPos)
	{
		if (isMove)
		{
			sprite.setColor(Color::Yellow);//êðàñèì ñïðàéò â æîâòèé 
			sprite.setPosition(pixelPos.x - dX, pixelPos.y - dY);//äâèãàåì ïî Y
																 //p.sprite.setPosition(pos.x - dX, pos.y - dY);//ìîæíî è òàê íàïèñàòü,åñëè ó âàñ íåòó õ è ó â êëàññå èãðîêà
		}
		else
		{
			sprite.setPosition(startCoor.x, startCoor.y);
		}
	}
};


int main()
{
	RenderWindow window(sf::VideoMode(800, 600), "Drag & Drop");

	Texture texture, TecRezustor, WireTex;
	texture.loadFromFile("images/lampa1.png");
	TecRezustor.loadFromFile("images/rezustor.png");
	WireTex.loadFromFile("images/providG.png");

	ELEMENT lampa(texture);
	ELEMENT rezustor(TecRezustor);
	ELEMENT wire(WireTex);

	Vector2i pixelPos;
	//test
	RectangleShape rectangle(Vector2f(45, 45));
	///test

	while (window.isOpen())
	{

		pixelPos = Mouse::getPosition(window);

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			//LMB Pressed
			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
			{
				lampa.MousePressed(pixelPos);
				rezustor.MousePressed(pixelPos);
				wire.MousePressed(pixelPos);
			}

			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
			{

				lampa.MouseReleazed(pixelPos);
				rezustor.MouseReleazed(pixelPos);
				wire.MouseReleazed(pixelPos);
			}
		}


		//KOD
		//		position = Mouse::getPosition(window);

		lampa.update(pixelPos);
		rezustor.update(pixelPos);
		wire.update(pixelPos);


		window.clear(Color::White);

		//test
		for (int i = 0; i<H; i++)
			for (int j = 0; j<W; j++)
			{
				if (TileMap[i][j] == '1') rectangle.setFillColor(Color(230, 230, 230, 255));

				if (TileMap[i][j] == '0')  rectangle.setFillColor(Color(255, 255, 255, 255));

				if (TileMap[i][j] == ' ') continue;

				rectangle.setPosition(j * size, i * size);
				window.draw(rectangle);
			}
		//Etest
		window.draw(rezustor.sprite);
		window.draw(lampa.sprite);
		window.draw(wire.sprite);
		window.display();
	}

	return 0;
}

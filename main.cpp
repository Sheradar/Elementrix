#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

//test
const int H = 11;
const int W = 15;
const int size = 45;
int count = 0;
int i[3]{ 0 };
bool isObjectTransportToSetka[3]{ false };
bool isBuferEmpty[3]{ true };


Texture texture, TecRezustor, WireTex;

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

void initialization()
{
	texture.loadFromFile("images/lampa1.png");
	TecRezustor.loadFromFile("images/rezustor.png");
	WireTex.loadFromFile("images/providG.png");
}



class ELEMENT {
public:

	Sprite sprite[H*W];
	Vector2f startCoor[H*W];// = new Vector2f[H*W];

	bool isMove[H*W], isClicked[H*W];

	float dX[H*W], dY[H*W];


	ELEMENT(int index) {// schob vidriznyatu elementu
		//switch (index) {///Debug
		//case 0:
		int kdist;
		if (index == 0) { kdist = 0; }
		else if (index == 1) { kdist = 50; }
		else if (index == 2) kdist = 100;
			for (int j = 0; j <= 165; j++)		//-----------------
			{									//-----------------
				startCoor[j].x = 20+kdist;			//initializatio 
				startCoor[j].y = 525;			//start position
												//		count += 50;			//-----------------
			}									//-----------------

			if (index == 0) sprite[i[index]].setTexture(texture);
			else if(index == 1) sprite[i[index]].setTexture(TecRezustor);
			else if (index == 2) sprite[i[index]].setTexture(WireTex);
			sprite[i[index]].setScale(1, 1);
			sprite[i[index]].setPosition(startCoor[i[index]].x, startCoor[i[index]].y);
			isBuferEmpty[index] = false;

			for (int j = 0; j <= 165; j++)
			{
				isMove[j] = false;
			}

	}

	void MousePressed(Vector2i pixelPos, int index)
	{
		for (int j = 0; j <= i[index]; j++)
		{
			if (sprite[j].getGlobalBounds().contains(pixelPos.x, pixelPos.y))//
			{
				//		std::cout << "isClicked!\t";//auaiaei a eiinieu niiauaiea ia yoii
				dX[j] = pixelPos.x - sprite[j].getPosition().x;//aaeaai ?aciinou ia?ao iiceoeae eo?ni?a e ni?aeoa.aey ei??aeoe?iaee ia?aoey
				dY[j] = pixelPos.y - sprite[j].getPosition().y;//oi?a naiia ii ea?aeo
				isMove[j] = true;//ii?ai aaeaaou ni?aeo		
				isClicked[j] = true;
			}
		}
	}

	void MouseReleazed(Vector2i pixelPos, int index)
	{
		for (int j = 0; j <= i[index]; j++)
		{
			isMove[j] = false;

			sprite[j].setColor(Color::White);

			for (int countY = 0; countY < size*H; countY += size)
				for (int countX = 0; countX < size*W; countX += size)
				{
					if (IntRect(countX, countY, size, size).contains(pixelPos.x, pixelPos.y) &&
						isClicked[j]&& sprite[j].getGlobalBounds().contains(pixelPos.x, pixelPos.y))
					{
						if ( (startCoor[j].x == 20 && startCoor[j].y == 525) || (startCoor[j].x == 20+50 && startCoor[j].y == 525) || (startCoor[j].x == 20+100 && startCoor[j].y == 525) ) 
							isBuferEmpty[index] = true; //bufer pusteyet
						else isBuferEmpty[index] = false;

						startCoor[j].x = countX;
						startCoor[j].y = countY;
						isClicked[j] = false;
						isObjectTransportToSetka[index] = true; //yakcho sprite peremistuvsya z bufera

						break;
					}

				}
		}
	}


	void update(Vector2i pixelPos, int index)
	{
		//std::cout << i;
		for (int j = 0; j <= i[index]; j++)
		{
			if (isMove[j])
			{

				sprite[j].setColor(Color::Yellow);
				sprite[j].setPosition(pixelPos.x - dX[j] , pixelPos.y - dY[j] );
				//p.sprite.setPosition(pos.x - dX, pos.y - dY);//ii?ii e oae iaienaou,anee o aan iaoo o e o a eeanna ea?iea
			}

			else
			{
				sprite[j].setPosition(startCoor[j].x, startCoor[j].y);
			}
		}
	}
};
/*
struct elementS{
elementS(Texture &image)
{
ELEMENT lampa(image);
}
};
*/

int main()
{
	RenderWindow window(sf::VideoMode(800, 600), "Drag & Drop");//create window

	initialization(); // initi. texture


	ELEMENT lampa(0);// = new ELEMENT[300]; ///
	ELEMENT rezustor(1);
	ELEMENT wire(2);
	//	ELEMENT wire(WireTex);

	Vector2i pixelPos;		// mouse Position
							//test
	RectangleShape rectangle(Vector2f(45, 45));		//setka dlya krasotu
													///test

	while (window.isOpen())							//main cukl
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
				lampa.MousePressed(pixelPos, 0);				//call F in class
				rezustor.MousePressed(pixelPos, 1);
				wire.MousePressed(pixelPos, 2);
				//				rezustor.MousePressed(pixelPos);
				//				wire.MousePressed(pixelPos);
			}

			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
			{


				lampa.MouseReleazed(pixelPos, 0);				//call F in class
				rezustor.MouseReleazed(pixelPos, 1);
				wire.MouseReleazed(pixelPos, 2);

				if (isObjectTransportToSetka[0] && isBuferEmpty[0]) // Create new sprite if peremistuvsya z bufera	///Debug
				{
					i[0]++;										//dodayem new element
																//X += 50;
					lampa.sprite[i[0]].setTexture(texture);
					lampa.sprite[i[0]].setPosition(lampa.startCoor[i[0]].x, lampa.startCoor[i[0]].y);// 20 525

					isBuferEmpty[0] = false;
					isObjectTransportToSetka[0] = false;
				}
				if (isObjectTransportToSetka[1] && isBuferEmpty[1]) // Create new sprite if peremistuvsya z bufera	///Debug
				{
					i[1]++;										//dodayem new element
																//X += 50;
					rezustor.sprite[i[1]].setTexture(TecRezustor);
					rezustor.sprite[i[1]].setPosition(rezustor.startCoor[i[1]].x, rezustor.startCoor[i[1]].y);// 20 525

					isBuferEmpty[1] = false;
					isObjectTransportToSetka[1] = false;
				}

				if (isObjectTransportToSetka[2] && isBuferEmpty[2]) // Create new sprite if peremistuvsya z bufera	///Debug
				{
					i[2]++;										//dodayem new element
																//X += 50;
					wire.sprite[i[2]].setTexture(WireTex);
					wire.sprite[i[2]].setPosition(wire.startCoor[i[2]].x, wire.startCoor[i[2]].y);// 20 525

					isBuferEmpty[2] = false;
					isObjectTransportToSetka[2] = false;
				}
				//				rezustor.MouseReleazed(pixelPos);
				//				wire.MouseReleazed(pixelPos);
			}
		}


		//KOD
		//		position = Mouse::getPosition(window);

		lampa.update(pixelPos, 0);//peremichae object za mushkoy
		rezustor.update(pixelPos, 1);
		wire.update(pixelPos, 2);
		//		wire.update(pixelPos);


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

		for (int j = 0; j <= i[0]; j++)
		{
			window.draw(lampa.sprite[j]);
		}
		for (int j = 0; j <= i[1]; j++)
		{
			window.draw(rezustor.sprite[j]);
		}
		for (int j = 0; j <= i[2]; j++)
		{
			window.draw(wire.sprite[j]);
		}


		window.display();
	}

	return 0;
}

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Time.hpp>
#include "ResourcePath.hpp"
using namespace std;
using namespace sf;

class bloque
{
	public:
		bloque(){};
		bloque(int type)
		{
			/*
			Different Type categories
			0 = normal floor
			1 = normal box
			*/
			switch (type)
			{
			case 0:
				texture.loadFromFile(resourcePath() + "TNormal.jpg", IntRect(0, 0, 340, 340));
				sprite.setTexture(texture);
				sprite.scale(0.1, 0.1);
				break;
			case 1:
				texture.loadFromFile(resourcePath() + "TNormal.jpg", IntRect(340, 0, 340, 340));
				sprite.setTexture(texture);
				sprite.scale(0.1, 0.1);
				sprite.setColor(Color(116, 70, 25, 255));
				break;
			default:
				break;
			}
		};
		~bloque(){};
		Sprite getSprite()
		{
			return sprite;
		};
		void positionOnMap(Vector2f *posiciones)
		{
			sprite.setPosition(position);
			position.x = posiciones->x * 34;
			position.y = posiciones->y * 34;
		};
	private:
		Sprite sprite;
		Texture texture;
		Vector2f position;
};

class AnimationBySprites
{
	public:
		AnimationBySprites(){};
		~AnimationBySprites(){};
	
		void addSprite(int d1, int d2, int d3, int d4)
		{
			px.push_back(d1);
			py.push_back(d2);
			cx.push_back(d3);
			cy.push_back(d4);
		};
		void play(Sprite *AquienAnimar, float FrameSpeed)
		{
			if (NoF >= px.size())
			{
				NoF = 0;
			}
			else
			{
				AquienAnimar->setTextureRect(IntRect(px[floor(NoF)], py[floor(NoF)], cx[floor(NoF)], cy[floor(NoF)]));
				NoF += FrameSpeed;
			};
		};
	private:
		vector <int> px, py, cx, cy;
		float NoF = 0;
};

class jugador
{
	public:
		jugador(int cordenadaX, int cordenadaY)
		{
			CharTexture.loadFromFile(resourcePath() + "Character1.png");
			Character1.setTexture(CharTexture);
			Character1.setTextureRect(IntRect(0, 0, 265, 265));
			Character1.scale(0.1, 0.1);
			Character1.setOrigin(Vector2f(Character1.getTexture()->getSize().x/3 * 0.5, Character1.getTexture()->getSize().y/2 * 0.5));
			coordenadas.x = (cordenadaX * 34) + 17;
			coordenadas.y = (cordenadaY * 34) + 17;
			Character1.setPosition(coordenadas);
			//Animacion de caminar
			walk1.addSprite(0, 0, 265, 265);
			walk1.addSprite(265, 0, 265, 265);
			walk1.addSprite(0, 0, 265, 265);
			walk1.addSprite(530, 0, 265, 265);
		};
		~jugador(){};
	
		Sprite getCharSprite(){ Character1.setPosition(coordenadas); return Character1; };
    
		//Que movimiento quieres hacer?
		void checkMove()
		{
			if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))//Arriba
			{
				nextMove = 'W';
			}
            else if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))//Izquierda
			{
				nextMove = 'A';
			}
			else if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))//Abajo
			{
				nextMove = 'S';
			}
			else if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))//Izquierda
			{
				nextMove = 'D';
			}
            else if (Keyboard::isKeyPressed(Keyboard::Space))//Barra espaciadora es igual a 'G' Grab o aGarrar
            {
                nextMove = 'G';
            }
			else
				nextMove = 'V';
		};
		//Hay un bloque en esa direccion?
		bool IsPossible(Vector2f checkingObject, Vector2f *Posiciones)
		{
			if (nextMove == 'W' && checkingObject.x == Posiciones->x && checkingObject.y == Posiciones->y + 1 && !moving)
			{
				return true;
			}
			else if (nextMove == 'A' && checkingObject.x == Posiciones->x + 1 && checkingObject.y == Posiciones->y && !moving)
			{
				return true;
			}
			else if (nextMove == 'S' && checkingObject.x == Posiciones->x && checkingObject.y == Posiciones->y - 1 && !moving)
			{
				return true;
			}
			else if (nextMove == 'D' && checkingObject.x == Posiciones->x - 1 && checkingObject.y == Posiciones->y && !moving)
			{
				return true;
			}
			else
			{
				return false;
			};
		};
    
        void movementGrabbing()//Este será el movimiento del jugador mientras este agarrando una caja, movera la caja y el jugador de ser posible
        {
        
        };
		//Muevete
		void movement(char moveDirection)
		{
			if (moveDirection == 'W')
			{
				coordenadas.y--;
				walk1.play(&Character1, 0.15);
				Character1.setRotation(0);
				if (coordenadas.y == goalPosition)
				{
					moving = false;
					goalPosition = 0;
					Character1.setTextureRect(IntRect(0, 0, 265, 265));
				}
			}
			else if (moveDirection == 'S')
			{
				walk1.play(&Character1, 0.15);
				coordenadas.y++;
				Character1.setRotation(180);
				if (coordenadas.y == goalPosition)
				{
					moving = false;
					goalPosition = 0;
					Character1.setTextureRect(IntRect(0, 0, 265, 265));
				}
			}
			else if (moveDirection == 'A')
			{
				walk1.play(&Character1, 0.15);
				coordenadas.x--;
				Character1.setRotation(270);
				if (coordenadas.x == goalPosition)
				{
					moving = false;
					goalPosition = 0;
					Character1.setTextureRect(IntRect(0, 0, 265, 265));
				}
			}
			else if (moveDirection == 'D')
			{
				walk1.play(&Character1, 0.15);
				coordenadas.x++;
				Character1.setRotation(90);
				if (coordenadas.x == goalPosition)
				{
					moving = false;
					goalPosition = 0;
					Character1.setTextureRect(IntRect(0, 0, 265, 265));
				}
			};
		};

		Vector2f getPosition(){ return coordenadas; };
		bool getMovingState(){ return moving; };
		char getNextMove(){ return nextMove; };
		void actMoving(){ moving = true; };
		void setGoalPosition(int pointGoal){ goalPosition = pointGoal; };
		void setIfMove(bool setCondition){ CanIMove = setCondition; };	//Nueva funcion
		bool getIfMove() { return CanIMove; }							//Nueva funcion
        void setGrabing(bool input){grabing = input;};
        void setGrabBox(Vector2f box){ grabedBox = box; };
	private:
		Sprite Character1;
		Texture CharTexture;
		AnimationBySprites walk1 = AnimationBySprites(); //Animacion de caminar
		float MovementSpeed = 1.0;
		char nextMove = 'V';
		Vector2f coordenadas;
		bool moving = false, CanIMove = true;
		int goalPosition = 0;
        bool grabing = false;//nuevo
        Vector2f grabedBox;
};

int main()
{
	int nivel = 1;
    jugador yo = jugador(10, 13);
    //Posicion del jugador entre 34 y aplicando la función floor
    
	bloque box = bloque(1);
	vector <Vector2f> contenedorDeCajas; //Contenedor de posiciones (Ya estan todas)
	//contenedorDeCajas.push_back(Vector2f(8, 13));
	contenedorDeCajas.push_back(Vector2f(10, 9));
	contenedorDeCajas.push_back(Vector2f(8, 7));
	contenedorDeCajas.push_back(Vector2f(8, 4));
	contenedorDeCajas.push_back(Vector2f(11, 2));
	contenedorDeCajas.push_back(Vector2f(2, 7));
	contenedorDeCajas.push_back(Vector2f(4, 2));

	bloque Tile1 = bloque(0);
	vector <Vector2f> contenedorDeSuelo; //Contenedor de posiciones
	//fila 1
	contenedorDeSuelo.push_back(Vector2f(4, 1));
	contenedorDeSuelo.push_back(Vector2f(7, 1));
	contenedorDeSuelo.push_back(Vector2f(8, 1));
	contenedorDeSuelo.push_back(Vector2f(9, 1));
	contenedorDeSuelo.push_back(Vector2f(11, 1));
	//fila 2
	contenedorDeSuelo.push_back(Vector2f(4, 2));
	contenedorDeSuelo.push_back(Vector2f(6, 2));
	contenedorDeSuelo.push_back(Vector2f(7, 2));
	contenedorDeSuelo.push_back(Vector2f(9, 2));
	contenedorDeSuelo.push_back(Vector2f(10, 2));
	contenedorDeSuelo.push_back(Vector2f(11, 2));
	//fila 3
	contenedorDeSuelo.push_back(Vector2f(1, 3));
	contenedorDeSuelo.push_back(Vector2f(2, 3));
	contenedorDeSuelo.push_back(Vector2f(3, 3));
	contenedorDeSuelo.push_back(Vector2f(4, 3));
	contenedorDeSuelo.push_back(Vector2f(6, 3));
	contenedorDeSuelo.push_back(Vector2f(8, 3));
	contenedorDeSuelo.push_back(Vector2f(11, 3));
	//fila 4
	contenedorDeSuelo.push_back(Vector2f(1, 4));
	for (int i = 4; i <= 11; i++)
	{
		contenedorDeSuelo.push_back(Vector2f(i, 4));
	};
	//fila 5
	contenedorDeSuelo.push_back(Vector2f(1, 5));
	contenedorDeSuelo.push_back(Vector2f(4, 5));
	contenedorDeSuelo.push_back(Vector2f(8, 5));
	//fila 6
	contenedorDeSuelo.push_back(Vector2f(1, 6));
	contenedorDeSuelo.push_back(Vector2f(3, 6));
	contenedorDeSuelo.push_back(Vector2f(4, 6));
	contenedorDeSuelo.push_back(Vector2f(8, 6));
	//fila 7
	contenedorDeSuelo.push_back(Vector2f(1, 7));
	contenedorDeSuelo.push_back(Vector2f(2, 7));
	contenedorDeSuelo.push_back(Vector2f(3, 7));
	contenedorDeSuelo.push_back(Vector2f(4, 7));
	contenedorDeSuelo.push_back(Vector2f(8, 7));
	contenedorDeSuelo.push_back(Vector2f(9, 7));
	contenedorDeSuelo.push_back(Vector2f(10, 7));
	//fila 8
	contenedorDeSuelo.push_back(Vector2f(3, 8));
	contenedorDeSuelo.push_back(Vector2f(8, 8));
	contenedorDeSuelo.push_back(Vector2f(10, 8));
	//fila 9
	contenedorDeSuelo.push_back(Vector2f(8, 9));
	contenedorDeSuelo.push_back(Vector2f(9, 9));
	contenedorDeSuelo.push_back(Vector2f(10, 9));
	contenedorDeSuelo.push_back(Vector2f(11, 9));
	//fila 10
	contenedorDeSuelo.push_back(Vector2f(9, 10));
	//fila 11
	contenedorDeSuelo.push_back(Vector2f(8, 11));
	contenedorDeSuelo.push_back(Vector2f(9, 11));
	contenedorDeSuelo.push_back(Vector2f(10, 11));
	//fila 12
	contenedorDeSuelo.push_back(Vector2f(8, 12));
	//fila 13
	contenedorDeSuelo.push_back(Vector2f(7, 13));
	contenedorDeSuelo.push_back(Vector2f(8, 13));
	contenedorDeSuelo.push_back(Vector2f(9, 13));
	contenedorDeSuelo.push_back(Vector2f(10, 13));

	RenderWindow window(VideoMode(800, 600), "Las vacas son chidas");
	window.setFramerateLimit(60);

	//Gameloop
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		//Si la aplicacion esta seleccionada
		if (event.type != Event::LostFocus)
		{
			window.clear();

			switch (nivel)
			{
				case 1:
                    
                    
					//Dibujar escenario
					for (int i = 0; i < contenedorDeSuelo.size(); i++)
					{
						Tile1.positionOnMap(&contenedorDeSuelo[i]);
						window.draw(Tile1.getSprite());
					};
					//Dibujar cajas
					for (int i = 0; i < contenedorDeCajas.size(); i++)
					{
						box.positionOnMap(&contenedorDeCajas[i]);
						window.draw(box.getSprite());
					}
	
					//Revisar que accion quieres hacer (Solo si no te estas moviendo).
					if (!yo.getMovingState())
					{
						yo.checkMove();
					};

                    
					//Comprobar que tu accion es posible
					for (int i = 0; i < contenedorDeSuelo.size(); i++)
					{
						if (yo.IsPossible(Vector2f(floor(yo.getPosition().x / 34), floor(yo.getPosition().y / 34)), &contenedorDeSuelo[i])) //Hay suelo en la direccion a la que quieres ir?
						{
							for (int c = 0; c < contenedorDeCajas.size(); c++)
							{
								if (yo.IsPossible(Vector2f(floor(yo.getPosition().x / 34), floor(yo.getPosition().y / 34)), &contenedorDeCajas[c])) //Hay una caja en la direccion a la que quieres ir?
								{
                                    if(yo.getNextMove() == 'G'){
                                        yo.setGrabing(true);
                                        yo.setGrabBox(contenedorDeCajas[c]);
                                    }else{
                                        yo.setGrabing(false);
                                    };
									yo.setIfMove(false); //Si hay caja -> no te puedes mover y rompe el bucle para no soobrescribir
									break;
								}
								else
								{
									yo.setIfMove(true); //Si no hay caja -> puedes moverte a donde quieres ir
								}
							}
							if (yo.getIfMove()) //Si te puedes mover...
							{
								if (yo.getNextMove() == 'W') //y presionas W
								{
									yo.setGoalPosition(yo.getPosition().y - 34);
								}
								else if (yo.getNextMove() == 'A') //y presionas A
								{
									yo.setGoalPosition(yo.getPosition().x - 34);
								}
								else if (yo.getNextMove() == 'S') //y presionas S
								{
									yo.setGoalPosition(yo.getPosition().y + 34);
								}
								else if (yo.getNextMove() == 'D') //y presionas D
								{
									yo.setGoalPosition(yo.getPosition().x + 34);
								};
								yo.actMoving(); //Activar movimiento
							};
						};
                        
					};

					//Moverse a la direccion que quieres (Solo si te estas moviendo), una vez que llegues ya no te moveras
					if (yo.getMovingState())
					{
						yo.movement(yo.getNextMove());
					};

					window.draw(yo.getCharSprite());

					break;
				default:
					break;
			};

			window.display();
		};
	};
};
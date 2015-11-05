#include <SFML/Graphics.hpp>
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
		bloque()
		{
			
		};
    
        bloque(int type){
            
            /*
            Different Type categories
             
             0 = normal floor
             1 = normal box 
             
            */
            
            switch (type) {
                case 0:
                    texture.loadFromFile(resourcePath() + "TNormal.jpg", IntRect(0, 0, 340, 340));
                    sprite.setTexture(texture);
                    sprite.scale(0.1, 0.1);
                    break;
                case 1:
                    texture.loadFromFile(resourcePath() + "TNormal.jpg", IntRect(0, 0, 340, 340));
                    sprite.setTexture(texture);
                    sprite.scale(0.1, 0.1);
                    sprite.setColor(Color(200 , 30 , 10 , 150));
                    
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
			position.x = posiciones -> x * 34;
			position.y = posiciones -> y * 34;
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
			if (NoF > px.size())
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
			CharTexture.loadFromFile(resourcePath() + "Character1.png",IntRect(0,0,266,266));
            Character1.setTexture(CharTexture);
			Character1.scale(0.1,0.1);
            //Cambios
            Character1.setOrigin(Vector2f(Character1.getTexture()->getSize().x * 0.5, Character1.getTexture()->getSize().y * 0.5));
			coordenadas.x = (cordenadaX * 34) +17;
			coordenadas.y = (cordenadaY * 34) +17;
            
			Character1.setPosition(coordenadas);
		};
		~jugador(){};

		Sprite getCharSprite()
		{
    
			Character1.setPosition(coordenadas);
			return Character1;
		};
		
		void checkMove()
		{
			if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))//Izquierda
			{
				nextMove = 'A';
			}
			else if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))//Izquierda
			{
				nextMove = 'D';
			}
			else if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))//Arriba
			{
				nextMove = 'W';
			}
			else if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))//Abajo
			{
				nextMove = 'S';
			}
			else
				nextMove = 'V';
		};

		char getMove(){ return nextMove; };

		void looop()
		{
			if (moving)
			{
				this->movimiento(nextMove);
			}
		};
    
		void movimiento(char moveDirection)
		{
			if (moveDirection == 'W')
			{
				coordenadas.y--;
				if (coordenadas.y == goalPosition)
				{
					moving = false;
					goalPosition = 0;
				}
			}
			else if (moveDirection == 'S')
			{
				coordenadas.y++;
				if (coordenadas.y == goalPosition)
				{
					moving = false;
					goalPosition = 0;
				}
			}
			else if (moveDirection == 'A')
			{
				coordenadas.x--;
				if (coordenadas.x == goalPosition)
				{
					moving = false;
					goalPosition = 0;
				}
			}
			else if (moveDirection == 'D')
			{
				coordenadas.x++;
				if (coordenadas.x == goalPosition)
				{
					moving = false;
					goalPosition = 0;
				}
			};
		};

		Vector2f getPosition()
		{
			return coordenadas;
		};

		void actMoving(){ moving = true; };
		bool getMovingState(){ return moving; };

		void setGoalPosition(int pointGoal){ goalPosition = pointGoal; };

        //Cambio nueva funcion
        void rotatePlayer(char direction){
        
            
            switch (direction) {
                
                case 'W':
                    Character1.setRotation(0);
                    break;
                case 'A':
                    Character1.setRotation(180);
                    break;
                    
                case 'S':
                    Character1.setRotation(270);
                    break;
                    
                case 'D':
                    Character1.setRotation(90);
                    break;
                    
                    
                default:
                    break;
            }
        
        };
    
	private:
    
    ;
        char nextMove = 'V';
		Vector2f coordenadas;
		Sprite Character1;
		Texture CharTexture;
		float MovementSpeed = 1.0;
		bool moving = false;
		int goalPosition = 0;
};

int main()
{
	int nivel = 1;

	jugador yo = jugador(10, 13);
    bloque Tile1 = bloque(0);
    bloque box = bloque(1);
    Vector2f testCoordinates;
    

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

	RenderWindow window(VideoMode(800, 600), "nuevo titulo");

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
                    
                    testCoordinates = Vector2f(7, 1);
                    box.positionOnMap(&testCoordinates);
                    window.draw(box.getSprite());

					//Revisar que accion quieres hacer
					if (!yo.getMovingState())
					{
						yo.checkMove();
					};

					//Comprobar que accion es posible
					for (int i = 0; i < contenedorDeSuelo.size(); i++)
					{
						if (yo.getMove() == 'W' && floor(yo.getPosition().x / 34) == contenedorDeSuelo[i].x && floor(yo.getPosition().y / 34) == contenedorDeSuelo[i].y + 1 && !yo.getMovingState())
						{
                            //Comprobar que no hay una caja en esa direccion
                            if(floor(yo.getPosition().x / 34) == testCoordinates.x && floor(yo.getPosition().y / 34) - 1 == testCoordinates.y ){
                                
                            }else{
                                yo.setGoalPosition(yo.getPosition().y - 34);
                                yo.actMoving();
                            };
                            
                            yo.rotatePlayer('W');
							
							break;
						}
						else if (yo.getMove() == 'S' && floor(yo.getPosition().x / 34) == contenedorDeSuelo[i].x && floor(yo.getPosition().y / 34) == contenedorDeSuelo[i].y - 1 && !yo.getMovingState())
						{
                            yo.rotatePlayer('A');
							yo.setGoalPosition(yo.getPosition().y + 34);
							yo.actMoving();
							//yo.movimiento("Down");
							break;
						}
						else if (yo.getMove() == 'A' && floor(yo.getPosition().x / 34) == contenedorDeSuelo[i].x + 1 && floor(yo.getPosition().y / 34) == contenedorDeSuelo[i].y  && !yo.getMovingState())
						{
                            yo.rotatePlayer('S');
                            yo.setGoalPosition(yo.getPosition().x - 34);
							yo.actMoving();
							//yo.movimiento("Left");
							break;
						}
						else if (yo.getMove() == 'D' && floor(yo.getPosition().x / 34) == contenedorDeSuelo[i].x - 1 && floor(yo.getPosition().y / 34) == contenedorDeSuelo[i].y  && !yo.getMovingState())
						{
                            yo.rotatePlayer('D');
							yo.setGoalPosition(yo.getPosition().x + 34);
							yo.actMoving();
							//yo.movimiento("Right");
							break;
						};
                        
					};
					yo.looop();

					window.draw(yo.getCharSprite());
					break;
				default:
					break;
			}


			window.display();
		};
	}
}

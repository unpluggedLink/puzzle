#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Time.hpp>
using namespace std;
using namespace sf;
#include "ResourcePath.hpp"
#include "Jugador.h"
#include "Bloque.h"
#include "Animation.h"
#include "Item.h"

int main()
{
	int nivel = 1;

	jugador yo = jugador(10, 13);
    
    int counter;                //Nueva variable auxiliar
    int score = 0;   
    Font sansation;
    sansation.loadFromFile(resourcePath() + "sansation.ttf");
    Text scoreLabel(to_string(score),sansation);
    scoreLabel.setColor(Color::White);
    scoreLabel.setPosition(2 * 34, 15 * 34);
    Sprite player = yo.getCharSprite();
    
    Item lata = Item(1);
    Vector2f testPosition = Vector2f(8 , 11);
    
	bloque box = bloque(1);
    
    vector <Item>::const_iterator iter1; //Nuevo - iterador :3 si lo estudias bien ser‡s un dios :: nota personal
    vector <Item> contenedorDeLatas;   // Nuevo - estudiar el tipo vector :: nota personal
    lata.setPosition(1,5);
    contenedorDeLatas.push_back(lata);
    lata.setPosition(11, 1);
    contenedorDeLatas.push_back(lata);
    lata.setPosition(10, 11);
    contenedorDeLatas.push_back(lata);
    
	vector <Vector2f> contenedorDeCajas; //Contenedor de posiciones (Ya estan todas)
	contenedorDeCajas.push_back(Vector2f(8, 13));
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
                    window.draw(scoreLabel);
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
                    };
                    //Dibujar Latas
                    counter=0;
                    for (iter1=contenedorDeLatas.begin(); iter1 != contenedorDeLatas.end(); iter1++) {
                        window.draw(contenedorDeLatas[counter].sprite);
                        counter++;
                    }
                    //Borrar Latas
                    counter=0;
                    for(iter1 = contenedorDeLatas.begin(); iter1 != contenedorDeLatas.end();iter1++)
                    {
                        if( contenedorDeLatas[counter].destroy == true){
                            contenedorDeLatas.erase(iter1);
                            break;
                        };
                        counter++;
                    };
                    //Colision con latas
                    counter=0;
                    for(iter1 = contenedorDeLatas.begin(); iter1 != contenedorDeLatas.end();iter1++)
                    {
                        if(yo.getPosition() == contenedorDeLatas[counter].getPosition()){
                            contenedorDeLatas[counter].destroy = true;
                            score += 100;
                            scoreLabel.setString(to_string(score));
                            break;
                        };
                        counter++;
                    };

					//Revisar que accion quieres hacer (Solo si no te estas moviendo).
					if (!yo.getMovingState()) { yo.checkMove(); };
                    
                    
					//Comprobar que tu accion es posible
					for (int a = 0; a < contenedorDeSuelo.size(); a++) //For suelo
					{
						//¿Hay suelo a 1 de distancia de mi direccion?
						if (yo.IsPossible(&contenedorDeSuelo[a], 1)) //Si (Hay suelo a 1 de distancia de mi direccion)
						{
							for (int b = 0; b < contenedorDeCajas.size(); b++) //For caja
							{
								//¿Hay caja a 1 de distancia de mi direccion?
								if (yo.IsPossible(&contenedorDeCajas[b], 1)) //Si (Hay caja a 1 de distancia de mi direccion)
								{
									yo.setBoxID(b);
									//¿Estas empujando la caja?
									if (yo.getIfHoldingBox()) //Si (Estoy empujando la caja)
									{
										for (int c = 0; c < contenedorDeSuelo.size(); c++) //For suelo
										{
											//¿Hay suelo a 2 de distancia de mi direccion?
											if (yo.IsPossible(&contenedorDeSuelo[c], 2)) //Si (Hay suelo a 2 de distancia de mi direccion)
											{
												//For caja
												for (int d = 0; d < contenedorDeCajas.size(); d++)
												{
													//¿Hay una caja a 2 de mi direccion?
													if (yo.IsPossible(&contenedorDeCajas[d],2)) //Si (Hay caja a 2 de mi direccion)
													{
														yo.setIfMove(false);
														break;
													}
													else //No (No hay caja a 2 de mi direccion)
													{
														yo.setIfMove(true);
													};
                                                    //Hay una lata a 2 de mi direcci—n
                                                    
												};
												if (yo.getIfMove()) //Si te puedes mover
												{
													yo.setGoalByKey(); //Marcar a donde ir segun la tecla que oprimas
												};
												break;
											}
											else //No (No hay suelo a 2 de distancia de mi direccion)
											{
												yo.setIfMove(false);
											};
										};
										break;
									}
									else //No (No estoy empujando la caja)
									{
										yo.setIfMove(false);
										break;
									};
								}
								else //No (No hay caja a 1 de distancia de mi direccion)
								{
									yo.setIfMove(true);
								};
							};
						}
						else //No (No hay suelo a 1 de distancia de mi direccion)
						{
							yo.setIfMove(false);
						};

						if (yo.getIfMove()) //Si te puedes mover
						{
							yo.setGoalByKey(); //Marcar a donde ir segun la tecla que oprimas
						};
					};

					//Si la caja esta cerca
					if (yo.getPosition().x - 34 <= contenedorDeCajas[yo.getBoxID()].x * 34 && yo.getPosition().x + 34 >= contenedorDeCajas[yo.getBoxID()].x * 34 && yo.getPosition().y - 34 <= contenedorDeCajas[yo.getBoxID()].y * 34 && yo.getPosition().y + 34 >= contenedorDeCajas[yo.getBoxID()].y * 34 )
					{
						yo.setIfBoxNear(true); //Puedes empujarla/jalarla
					}
					else
					{
						yo.setIfBoxNear(false); //No puedes empujarla/jalarla
					};

					//Moverse a la direccion que quieres (Solo si te estas moviendo), una vez que llegues ya no te moveras
					if (yo.getMovingState())
					{
						yo.movimiento(yo.getNextMove());
						if (yo.getIfHoldingBox() && yo.getIfBoxNear())//Si estas agarrando una caja y si esta cerca...
						{
							if (yo.getNextMove() == 'W' && contenedorDeCajas[yo.getBoxID()].x == yo.getPosition().x/34)
							{
								if (yo.getPosition().y/34 > contenedorDeCajas[yo.getBoxID()].y) //Si la caja esta arriba de ti
									contenedorDeCajas[yo.getBoxID()].y = (yo.getPosition().y - 34) / 34;//empujar caja arriba
								else
									contenedorDeCajas[yo.getBoxID()].y = (yo.getPosition().y + 34) / 34;//jalar caja arriba
							}

							else if (yo.getNextMove() == 'S' && contenedorDeCajas[yo.getBoxID()].x == yo.getPosition().x / 34)
							{
								if (yo.getPosition().y / 34 > contenedorDeCajas[yo.getBoxID()].y) //Si la caja esta arriba de ti
									contenedorDeCajas[yo.getBoxID()].y = (yo.getPosition().y - 34) / 34;//empujar caja abajo
								else
									contenedorDeCajas[yo.getBoxID()].y = (yo.getPosition().y + 34) / 34;//jalar caja bajo
							}

							else if (yo.getNextMove() == 'A' && contenedorDeCajas[yo.getBoxID()].y == yo.getPosition().y / 34)
							{
								if (yo.getPosition().x / 34 > contenedorDeCajas[yo.getBoxID()].x) //Si la caja esta a tu izquierda
									contenedorDeCajas[yo.getBoxID()].x = (yo.getPosition().x - 34) / 34;//empujar caa izquierda
								else
									contenedorDeCajas[yo.getBoxID()].x = (yo.getPosition().x + 34) / 34;//empujar caja derecha
							}

							else if (yo.getNextMove() == 'D' && contenedorDeCajas[yo.getBoxID()].y == yo.getPosition().y / 34)
							{

								if (yo.getPosition().x/ 34 < contenedorDeCajas[yo.getBoxID()].x) //Si la caja esta a tu derecha
									contenedorDeCajas[yo.getBoxID()].x = (yo.getPosition().x + 34) / 34;//empujar caja derecha
								else
									contenedorDeCajas[yo.getBoxID()].x = (yo.getPosition().x - 34) / 34;//empujar caja derecha
							};
						};
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
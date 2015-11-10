#ifndef JUGADOR_H
#define JUGADOR_H

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
using namespace sf;

#include "Animation.h"

class jugador
{
public:
	jugador(int cordenadaX, int cordenadaY)
	{
		CharTexture.loadFromFile(resourcePath() + "Character1.png");
		Character1.setTexture(CharTexture);
		Character1.setTextureRect(IntRect(0, 0, 265, 265));
		Character1.scale(0.1, 0.1);
		Character1.setOrigin(Vector2f(Character1.getTexture()->getSize().x / 3 * 0.5, Character1.getTexture()->getSize().y / 2 * 0.5));
		coordenadas.x = (cordenadaX * 34);
		coordenadas.y = (cordenadaY * 34);
		Character1.setPosition(coordenadas);
		//Animacion de caminar
		walk1.addSprite(0, 0, 265, 265);
		walk1.addSprite(265, 0, 265, 265);
		walk1.addSprite(0, 0, 265, 265);
		walk1.addSprite(530, 0, 265, 265);
	};
	~jugador(){};

	//Que movimiento quieres hacer?
	void checkMove()
	{
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			holdingBox = true;
		}
		else
		{
			holdingBox = false;
		};
		if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))//Arriba
		{
			nextMove = 'W';
			Character1.setRotation(0);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))//Izquierda
		{
			nextMove = 'A';
			Character1.setRotation(270);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))//Abajo
		{
			nextMove = 'S';
			Character1.setRotation(180);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))//Izquierda
		{
			nextMove = 'D';
			Character1.setRotation(90);
		}
		else
			nextMove = 'V';
	};
	//Hay un bloque en esa direccion?
	bool IsPossible(Vector2f *Posiciones, int distance)
	{
		if (nextMove == 'W' && floor(coordenadas.x / 34) == Posiciones->x && floor(coordenadas.y / 34) == Posiciones->y + distance && !moving)
		{
			return true;
		}
		else if (nextMove == 'A' && floor(coordenadas.x / 34) == Posiciones->x + distance && floor(coordenadas.y / 34) == Posiciones->y && !moving)
		{
			return true;
		}
		else if (nextMove == 'S' && floor(coordenadas.x / 34) == Posiciones->x && floor(coordenadas.y / 34) == Posiciones->y - distance && !moving)
		{
			return true;
		}
		else if (nextMove == 'D' && floor(coordenadas.x / 34) == Posiciones->x - distance && floor(coordenadas.y / 34) == Posiciones->y && !moving)
		{
			return true;
		}
		else
		{
			return false;
		};
	};
	//Muevete
	void movimiento(char moveDirection)
	{
		if (moveDirection == 'W')
		{
			coordenadas.y--;
			Character1.setRotation(0);
			walk1.play(&Character1, 0.15);
			if (coordenadas.y == goalPosition)
			{
				moving = false;
				goalPosition = 0;
				Character1.setTextureRect(IntRect(0, 0, 265, 265));
			};
		}
		else if (moveDirection == 'S')
		{
			coordenadas.y++;
			Character1.setRotation(180);
			walk1.play(&Character1, 0.15);
			if (coordenadas.y == goalPosition)
			{
				moving = false;
				goalPosition = 0;
				Character1.setTextureRect(IntRect(0, 0, 265, 265));
			};
		}
		else if (moveDirection == 'A')
		{
			coordenadas.x--;
			Character1.setRotation(270);
			walk1.play(&Character1, 0.15);
			if (coordenadas.x == goalPosition)
			{
				moving = false;
				goalPosition = 0;
				Character1.setTextureRect(IntRect(0, 0, 265, 265));
			};
		}
		else if (moveDirection == 'D')
		{
			coordenadas.x++;
			Character1.setRotation(90);
			walk1.play(&Character1, 0.15);
			if (coordenadas.x == goalPosition)
			{
				moving = false;
				goalPosition = 0;
				Character1.setTextureRect(IntRect(0, 0, 265, 265));
			};
		};
	};
	void setGoalByKey()
	{
		if (nextMove == 'W')
		{
			goalPosition = coordenadas.y - 34;
		}
		else if (nextMove == 'A')
		{
			goalPosition = coordenadas.x - 34;
		}
		else if (nextMove == 'S')
		{
			goalPosition = coordenadas.y + 34;
		}
		else if (nextMove == 'D')
		{
			goalPosition = coordenadas.x + 34;
		};
		moving = true;
	};

	void actMoving(){ moving = true; };
	void setIfMove(bool setCondition){ CanIMove = setCondition; };
	void setBoxID(int BoxID) { boxNumber = BoxID; };
	void setIfBoxNear(bool data){ boxNear = data; };

	Sprite getCharSprite(){ Character1.setPosition(coordenadas); return Character1; };
	Vector2f getPosition(){ return coordenadas; };
	bool getMovingState(){ return moving; };
	char getNextMove(){ return nextMove; };
	int getBoxID(){ return boxNumber; };
	bool getIfMove() { return CanIMove; };
	bool getIfHoldingBox() { return holdingBox; };
	bool getIfBoxNear() { return boxNear; }

private:
	Sprite Character1;
	Texture CharTexture;
	AnimationBySprites walk1 = AnimationBySprites(); //Animacion de caminar
	Vector2f coordenadas;
	char nextMove = 'V';
	bool CanIMove = true, boxNear = false, holdingBox = false, moving = false;
	int goalPosition = 0, boxNumber = 0;
	float MovementSpeed = 1.0;
};

#endif
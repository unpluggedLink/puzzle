#ifndef BLOQUE_H
#define BLOQUE_H

#include <SFML/Graphics.hpp>
using namespace sf;

class bloque
{
	public:
		bloque(){};
		bloque(int type)
		{
			//Different Type categories
			//0 = normal floor
			//1 = normal box
			if (type == 0)
			{
				texture.loadFromFile(resourcePath() + "TNormal.jpg", IntRect(0, 0, 340, 340));
				sprite.setTexture(texture);
				sprite.scale(0.1, 0.1);
				sprite.setOrigin(170, 170);
			}
			else if (type == 1)
			{
				texture.loadFromFile(resourcePath() + "TNormal.jpg", IntRect(340, 0, 340, 340));
				sprite.setTexture(texture);
				sprite.setColor(Color(116, 70, 25, 255));
				sprite.scale(0.1, 0.1);
				sprite.setOrigin(170, 170);
			}
		};
		~bloque(){};
    
		Sprite getSprite() { return sprite; };
    
		void positionOnMap(Vector2f *posiciones)
		{
			position.x = posiciones->x * 34;
			position.y = posiciones->y * 34;
			sprite.setPosition(position);
		};
	private:
		Sprite sprite;
		Texture texture;
		Vector2f position;
};

#endif
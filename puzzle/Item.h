
class Item
{
    public:
		Item(){};
		Item(int ID){
        texture.loadFromFile(resourcePath() + "Spray.png");
        sprite.setTexture(texture);
        sprite.scale(0.06, 0.06);// aun en prueba no es el tamaña final
        sprite.setOrigin(Vector2f(sprite.getTexture()->getSize().x / 3 * 0.5, sprite.getTexture()->getSize().y / 2 * 0.5));
        itemId = ID;
		};
        ~Item(){};
        void setPosition(Vector2f *newPosition)
        {
            position.x = newPosition-> x * 34;
            position.y = newPosition-> y * 34;
            sprite.setPosition(position);
        };
        void setPosition(int newPositionX, int newPositionY)
        {
            position.x = newPositionX * 34;
            position.y = newPositionY * 34;
            sprite.setPosition(position);
        };
    
        Vector2f getPosition()
        {
            return position;
        };
        bool destroy = false;  // Nueva variable publica !
        int getId(){return itemId;};
        Sprite getSprite(){return sprite;};
        void setSprite(Sprite tempSprite){  sprite = tempSprite; };
        Sprite sprite;
	private:
			Texture texture;
			
			Vector2f position;
            int itemId;
};

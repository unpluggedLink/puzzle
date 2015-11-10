
class Item
{
	//Hasta ahora solo existe un tipo de item, el 1 que es una lata
	public:
		Item(){};
		Item(int ID){
        texture.loadFromFile(resourcePath() + "Spray.png");
        Sprite.setTexture(texture);
        Sprite.scale(0.06, 0.06);// aun en prueba no es el tamaña final
        Sprite.setOrigin(Vector2f(Sprite.getTexture()->getSize().x / 3 * 0.5, Sprite.getTexture()->getSize().y / 2 * 0.5));
        itemId = ID;
		};
        ~Item(){};
        void setPosition(Vector2f *newPosition)
        {
            position.x = newPosition-> x * 34;
            position.y = newPosition-> y * 34;
            Sprite.setPosition(position);
        };
    
        Vector2f getPosition()
        {
            return position;
        };
        void setVisible(bool input)
        {
            visible = input; 
        };
        bool isVisible()
        {
            return visible;
        };
        int getId(){return itemId;};
        Sprite getSprite(){return Sprite;};
        void setSprite(Sprite tempSprite){  Sprite = tempSprite; };
	private:
			Texture texture;
			Sprite Sprite;
			Vector2f position;
            bool visible = true;
            int itemId;
};

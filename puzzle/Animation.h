#ifndef ANIMATION_H
#define ANIMATION_H

#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

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

#endif
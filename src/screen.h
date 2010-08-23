#ifndef GW_SCREEN_H
#define GW_SCREEN_H

class Screen {
public:
	virtual void update()=0;
	virtual void render()=0;

	virtual void handleEvents()=0;
	virtual void handleEvent(sf::Event e)=0;
};

#endif

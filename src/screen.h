#ifndef GW_SCREEN_H
#define GW_SCREEN_H

class Screen {
public:
	virtual void update()=0;
	virtual void render()=0;
};

#endif

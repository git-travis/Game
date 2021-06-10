#pragma once

#include "rectIMG.h"
/*
class aniRectIMG: public rectIMG{
public:
	aniRectIMG(int x, int y, int width, int height, std::string file, int frames);
	aniRectIMG(std::string file);
	virtual ~aniRectIMG();

	void playAni(int);
	void stopAni();
	void resetAni();
	void addAni(int maxFrames, int x, int y, int width, int height);
	void update();
	void updateAni(int i);


protected:
	void setVisible(bool visible);
	virtual void setupAni();

	int _frameIndex, _maxFrames, _currentAni;
private:
	std::vector<std::vector<sf::IntRect>> _animations;


	double _timeElapsed;
	bool _visible, _notDone;
};
*/

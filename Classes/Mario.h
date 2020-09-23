#pragma once
#include "cocos2d.h"
#include <string>

USING_NS_CC;

class Mario:public cocos2d::Sprite
{
public:
	
	RepeatForever* __small_left;
	RepeatForever* __small_right;






	enum Direction { dir_stop = 0, dir_right, dir_left};

	virtual bool init() override;
	RepeatForever* CreateRepeatAnimate(std::string);
	void InitAllAnimateAction();

	void SmallRightMove();
	void SmallLeftMove();


	void update(float f);
	float GetSpeed() { return move_speed; }
	CREATE_FUNC(Mario);
private:
	//std::string file_name= "images\\MarioMap1.png";
	std::string file_name="images\\mario-small-stand.png";

	bool right = false;
	bool left = false;
	float move_speed = 2;
	float jump_height = 80; 
	float base_line = 32;

};
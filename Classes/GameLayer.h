#pragma once

#include "cocos2d.h"
#include "Mario.h"
class GameMap;
USING_NS_CC;

class GameLayer :public cocos2d::Layer
{
public:
	GameMap* main_map;
	Mario* mario;

	bool jump_keydown;
	bool right_keydown;
	bool left_keydown;

	bool can_jump;
	bool is_flying;
	int jump_action_tag;
	int right_action_tag;
	int left_action_tag;
	EventKeyboard::KeyCode last_keydown;

	float move_speed;
	float max_move_speed;
	float acce_move;
	float jump_hight;
	float vision_offset;
	Size visible_size;

	//mario relative pos
	Vec2 mario_pos;
	Size mario_size;

	Vec2 down_left;
	Vec2 down_right;

	Vec2 up_left;
	Vec2 up_right;

	Vec2 right_up;
	Vec2 right_down;

	Vec2 left_up;
	Vec2 left_down;
	
	GameLayer();

	void update(float dt);


	virtual bool init() override;
	void InitMapAndMario();

	void KeyEventInit();
	void KeyEventProcess();

	void PositionFresh();
	void CollisionControlH();
	void CollisionControlV();

	

	CREATE_FUNC(GameLayer);
protected:
private:
	void RightMove();
	void LeftMove();
	void JumpMove();

};
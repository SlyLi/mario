

#include "GameLayer.h"
#include "GameMap.h"
#include "Mario.h"

USING_NS_CC;



GameLayer::GameLayer():
	main_map(NULL),mario(NULL),
	jump_keydown(false),right_keydown(false),left_keydown(false), can_jump(true),is_flying(false),
	jump_action_tag(13579), left_action_tag(13578), right_action_tag(13576),
	last_keydown(EventKeyboard::KeyCode::KEY_NONE),
	move_speed(0.0f), max_move_speed(2.5f),acce_move(0.1f),jump_hight(2.0f),vision_offset(0),
	visible_size(Director::getInstance()->getVisibleSize())
{ 
}


void GameLayer::update(float dt)
{
	

	if (mario_pos.x > vision_offset + visible_size.width * 0.7 &&
		vision_offset<main_map->map_size.width- visible_size.width)
	{
		vision_offset += move_speed;
		this->setPositionX(0 - vision_offset);
	}

	KeyEventProcess();
	PositionFresh();
	CollisionControlH();
	CollisionControlV();


}

void GameLayer::PositionFresh()
{
	mario_pos = mario->getPosition();
	mario_size = mario->getContentSize();

	down_left = mario_pos + Vec2(1, -1);
	down_right = mario_pos + Vec2(mario_size.width, 0) + Vec2(-1, -1);

	up_left = mario_pos + Vec2(0, mario_size.height) + Vec2(1, 1);
	up_right = mario_pos + Vec2(mario_size.width, mario_size.height) + Vec2(-1, 1);

	right_up = mario_pos + mario_size + Vec2(1, -1);
	right_down = mario_pos + Vec2(mario_size.width, 0) + Vec2(1, 1);

	left_up = mario_pos + Vec2(0, mario_size.height) + Vec2(-1, -1);
	left_down = mario_pos + Vec2(-1, 1);
}
void GameLayer::CollisionControlH()
{
	static float acceleration = -0.285; // 这个跳跃下的加速度
	static float this_y, last_y;
	static float down_speed;

	last_y = this_y;
	this_y = mario_pos.y;
	down_speed = down_speed < this_y - last_y ? down_speed : this_y - last_y;

	//log("down speed %f", this_y - last_y);


	if (main_map->TileTypeForPos(down_left) == TileType::TILE_NONE &&
		main_map->TileTypeForPos(down_right) == TileType::TILE_NONE &&
		is_flying && mario->getNumberOfRunningActionsByTag(jump_action_tag) == 0)
	{

		mario->setPositionY(mario_pos.y + down_speed + acceleration);

		Vec2 down_left1 = down_left, down_right1 = down_right;
		down_left1.y += (int)(down_speed + acceleration);
		down_right1.y += (int)(down_speed + acceleration);
		if (main_map->TileTypeForPos(down_left1) == TileType::TILE_PIPE ||
			main_map->TileTypeForPos(down_right1) == TileType::TILE_PIPE ||
			main_map->TileTypeForPos(down_left1) == TileType::TILE_LAND ||
			main_map->TileTypeForPos(down_right1) == TileType::TILE_LAND ||
			main_map->TileTypeForPos(down_left1) == TileType::TILE_BLOCK ||
			main_map->TileTypeForPos(down_right1) == TileType::TILE_BLOCK)
		{
			while (main_map->TileTypeForPos(down_left1) == TileType::TILE_PIPE ||
				main_map->TileTypeForPos(down_right1) == TileType::TILE_PIPE ||
				main_map->TileTypeForPos(down_left1) == TileType::TILE_LAND ||
				main_map->TileTypeForPos(down_right1) == TileType::TILE_LAND ||
				main_map->TileTypeForPos(down_left1) == TileType::TILE_BLOCK ||
				main_map->TileTypeForPos(down_right1) == TileType::TILE_BLOCK)
			{
				down_left1 = Vec2(down_left1.x, down_left1.y + 1);
				down_right1 = Vec2(down_right1.x, down_right1.y + 1);
			}
			mario->setPositionY(down_left1.y - 1);
			down_speed = 0;
		}

	}

	if (is_flying)
	{
		if (main_map->TileTypeForPos(up_left) == TileType::TILE_BLOCK ||
			main_map->TileTypeForPos(up_right) == TileType::TILE_BLOCK)
		{
			mario->stopActionByTag(jump_action_tag);
			down_speed = 0;
		}


		if (main_map->TileTypeForPos(down_left) == TileType::TILE_PIPE ||
			main_map->TileTypeForPos(down_right) == TileType::TILE_PIPE ||
			main_map->TileTypeForPos(down_left) == TileType::TILE_BLOCK ||
			main_map->TileTypeForPos(down_right) == TileType::TILE_BLOCK)
		{
			down_speed = 0;
			is_flying = false;
			can_jump = true;
			mario->stopActionByTag(jump_action_tag);

			Vec2 down_left1 = down_left, down_right1 = down_right;
			while (main_map->TileTypeForPos(down_left1) == TileType::TILE_PIPE ||
				main_map->TileTypeForPos(down_right1) == TileType::TILE_PIPE ||
				main_map->TileTypeForPos(down_left1) == TileType::TILE_LAND ||
				main_map->TileTypeForPos(down_right1) == TileType::TILE_LAND ||
				main_map->TileTypeForPos(down_left1) == TileType::TILE_BLOCK ||
				main_map->TileTypeForPos(down_right1) == TileType::TILE_BLOCK)
			{
				down_left1 = Vec2(down_left1.x, down_left1.y + 1);
				down_right1 = Vec2(down_right1.x, down_right1.y + 1);
			}
			mario->setPositionY(down_left1.y - 1);

		}

		if (main_map->TileTypeForPos(down_left) == TileType::TILE_LAND ||
			main_map->TileTypeForPos(down_right) == TileType::TILE_LAND)
		{
			down_speed = 0;
			is_flying = false;
			can_jump = true;
		}
	}
	if (can_jump && main_map->TileTypeForPos(down_left) == TileType::TILE_NONE &&
		main_map->TileTypeForPos(down_right) == TileType::TILE_NONE)
	{
		is_flying = true;
		can_jump = false;

	}
}

void GameLayer::CollisionControlV()
{
	if ((main_map->TileTypeForPos(right_up) == TileType::TILE_PIPE ||
		main_map->TileTypeForPos(right_down) == TileType::TILE_PIPE ||
		main_map->TileTypeForPos(right_up) == TileType::TILE_BLOCK ||
		main_map->TileTypeForPos(right_down) == TileType::TILE_BLOCK||
		main_map->TileTypeForPos(right_up) == TileType::TILE_LAND ||
		main_map->TileTypeForPos(right_down) == TileType::TILE_LAND
		))
	{
		mario->stopAllActionsByTag(right_action_tag);
	}
	if ((main_map->TileTypeForPos(left_up) == TileType::TILE_PIPE ||
		main_map->TileTypeForPos(left_down) == TileType::TILE_PIPE ||
		main_map->TileTypeForPos(left_up) == TileType::TILE_BLOCK ||
		main_map->TileTypeForPos(left_down) == TileType::TILE_BLOCK||
		main_map->TileTypeForPos(left_up) == TileType::TILE_LAND ||
		main_map->TileTypeForPos(left_down) == TileType::TILE_LAND
		))
	{
		mario->stopAllActionsByTag(left_action_tag);
	}

}

bool GameLayer::init()
{
	InitMapAndMario();
	KeyEventInit();
	this->scheduleUpdate();
	return true;
}
void GameLayer::InitMapAndMario()
{
	main_map = GameMap::create("images\\MarioMap1.tmx");
	jump_hight = main_map->tile_size.height * 4;
	mario = Mario::create();

	this->addChild(main_map);
	this->addChild(mario);
}

void GameLayer::KeyEventInit()
{
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event)
	{
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			left_keydown = true;
			last_keydown = EventKeyboard::KeyCode::KEY_LEFT_ARROW;
			move_speed = 0.f;
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			right_keydown = true;
			last_keydown = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
			move_speed = 0.f;

			break;

		case EventKeyboard::KeyCode::KEY_SPACE:
			jump_keydown = true;
			break;
		default:
			break;
		}

	};
	listener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* event)
	{
		switch (keyCode)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			left_keydown = false;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			right_keydown = false;
			break;

		case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:
			jump_keydown = false;
			break;
		default:
			break;
		}

	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void GameLayer::KeyEventProcess()
{

	if (right_keydown && left_keydown)
	{
		switch (last_keydown)
		{
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:

			RightMove();
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:

			LeftMove();
			break;

		default:
			break;
		}
	}
	else if (right_keydown)
	{
		RightMove();
	}
	else if (left_keydown)
	{
		LeftMove();
	}

	if (jump_keydown && can_jump)
	{
		JumpMove();
		//log("%d", mario->getNumberOfRunningActionsByTag(jump_action_tag));

		jump_keydown = false;
		can_jump = false;
		is_flying = true;
	}
}



void GameLayer::RightMove()
{
	mario->__small_right->setTag(right_action_tag);
	mario->SmallRightMove();

	move_speed += acce_move;
	move_speed = move_speed > max_move_speed ? max_move_speed : move_speed;
	auto move_by = MoveBy::create(0, Vec2(move_speed, 0));
	move_by->setTag(right_action_tag);
	mario->runAction(move_by);

	
}

void GameLayer::LeftMove()
{
	mario->__small_left->setTag(left_action_tag);
	mario->SmallLeftMove();

	move_speed += acce_move;
	move_speed = move_speed > max_move_speed ? max_move_speed : move_speed;
	auto move_by = MoveBy::create(0, Vec2(0-move_speed, 0));
	move_by->setTag(left_action_tag);
	mario->runAction(move_by);

	

}

void GameLayer::JumpMove()
{
	mario->setPositionY(mario->getPositionY() + 2);
	auto jump_by = JumpBy::create(1, Vec2(0, -2), jump_hight, 1);
	jump_by->setTag(jump_action_tag);
	mario->runAction(jump_by);
}

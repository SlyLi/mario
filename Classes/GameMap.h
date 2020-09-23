#pragma once

#include "cocos2d.h"
USING_NS_CC;

enum class TileType
{
	TILE_BLOCK = 1,
	TILE_PIPE,
	TILE_LAND,
	TILE_TRAP,
	TILE_COIN,
	TILE_FLAGPOLE,

	TILE_NONE
	/*TILE_NONEX,
	TILE_NONEY*/
};

class GameMap :public cocos2d::TMXTiledMap
{

public:
	

	Size tile_size;
	Size tile_num;
	Size map_size;

	static GameMap* create(std::string);

	void Init();


	TMXLayer* GetBlockLayer();
	TMXLayer* GetPipeLayer();
	TMXLayer* getLandLayer();
	TMXLayer* GetTrapLayer();

	TMXLayer* GetCloudLayer();

	TMXLayer* GetCoinLayer();
	TMXLayer* GetMountainLayer();
	TMXLayer* GetFlagpoleLayer();

	TMXObjectGroup* GetObjectLayer();

	cocos2d::Vec2 ToTilePos(cocos2d::Vec2);
	TileType TileTypeForPos(cocos2d::Vec2);

protected:
	

	//Åö×²¼ì²â
	TMXLayer* block_layer;
	TMXLayer* pipe_layer;
	TMXLayer* land_layer;
	TMXLayer* trap_layer;

	TMXLayer* cloud_layer;

	TMXLayer* coin_layer;
	TMXLayer* mountaion_layer;
	TMXLayer* flagpole_layer;

	TMXObjectGroup* object_layer;


private:


};
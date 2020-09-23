#include "GameMap.h"


USING_NS_CC;

GameMap* GameMap::create(std::string tmx_file)
{
    GameMap* ret = new GameMap();
    if (ret->initWithTMXFile(tmx_file))
    {
        ret->Init();
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;

}

void GameMap::Init()
{
    block_layer = this->getLayer("block");
    pipe_layer = this->getLayer("pipe");
    land_layer = this->getLayer("land");
    trap_layer = this->getLayer("trap");

    cloud_layer = this->getLayer("cloud");
    mountaion_layer = this->getLayer("mountain");
    coin_layer = this->getLayer("coin");
    flagpole_layer = this->getLayer("flagpole");
    object_layer = this->getObjectGroup("objects");

    //mountaion_layer->setVisible(false);

    tile_size = this->getTileSize();
    tile_num = this->getMapSize();
    map_size = Size(tile_size.width * tile_num.width, tile_size.height * tile_num.height);
    
}

TMXLayer* GameMap::GetBlockLayer()
{
    return block_layer;
}

TMXLayer* GameMap::GetPipeLayer()
{
    return pipe_layer;
}

TMXLayer* GameMap::getLandLayer()
{
    return land_layer;
}

TMXLayer* GameMap::GetTrapLayer()
{
    return trap_layer;
}

TMXLayer* GameMap::GetCloudLayer()
{
    return cloud_layer;
}

TMXLayer* GameMap::GetCoinLayer()
{
    return coin_layer;
}

TMXLayer* GameMap::GetMountainLayer()
{
    return mountaion_layer;
}

TMXLayer* GameMap::GetFlagpoleLayer()
{
    return flagpole_layer;
}

TMXObjectGroup* GameMap::GetObjectLayer()
{
    return object_layer;
}

cocos2d::Vec2 GameMap::ToTilePos(cocos2d::Vec2 row_pos)
{

    return cocos2d::Vec2(row_pos.x / tile_size.width, tile_num.height  - (row_pos.y / tile_size.height));
}

TileType GameMap::TileTypeForPos(cocos2d::Vec2 pos)
{
    pos = ToTilePos(pos);
    if(pos.x>tile_num.width||pos.x<0||pos.y>tile_num.height||pos.y<0)
        return TileType::TILE_NONE;

    if (block_layer->getTileGIDAt(pos))
        return TileType::TILE_BLOCK;
   
    if (pipe_layer->getTileGIDAt(pos))
        return TileType::TILE_PIPE;

    if (land_layer->getTileGIDAt(pos))
        return TileType::TILE_LAND;
    return TileType::TILE_NONE;
}

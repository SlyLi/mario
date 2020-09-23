#include "Mario.h"
USING_NS_CC;

bool Mario::init()
{
	if (!Sprite::initWithFile(file_name))
		return false;
	this->setAnchorPoint(Vec2(0,0));

	this->setPosition(Vec2(20,base_line));
	this->scheduleUpdate();
	
	InitAllAnimateAction();

	//SmallRightMove();
	return true;
}

RepeatForever* Mario::CreateRepeatAnimate(std::string path)
{
	Texture2D* texture;
	Size cont_size;
	auto cache = Director::getInstance()->getTextureCache();
	texture = cache->addImage(path);
	cont_size = texture->getContentSize();
	cont_size.width /= 11;
	Vector< SpriteFrame*> frames = Vector< SpriteFrame*>();
	for (int i = 0; i < 11; i++)
	{
		auto frame = SpriteFrame::createWithTexture(texture,
			Rect(cont_size.width * i, 0, cont_size.width, cont_size.height));
		frames.pushBack(frame);
	}
	auto animation = Animation::createWithSpriteFrames(frames, 0.1f);
	return RepeatForever::create(Animate::create(animation));
}

void Mario::InitAllAnimateAction()
{
	__small_left = CreateRepeatAnimate("images\\smallWalkLeft.png");
	__small_left->retain();

	__small_right = CreateRepeatAnimate("images\\smallWalkRight.png");
	__small_right->retain();


}

void Mario::SmallRightMove()
{
	stopAction(__small_left);
	if(this->getNumberOfRunningActionsByTag(__small_right->getTag())==0)
		runAction(__small_right);

	
}

void Mario::SmallLeftMove()
{
	stopAction(__small_right);
	if (this->getNumberOfRunningActionsByTag(__small_left->getTag()) == 0)
		runAction(__small_left);


	
}



void Mario::update(float f)
{

}

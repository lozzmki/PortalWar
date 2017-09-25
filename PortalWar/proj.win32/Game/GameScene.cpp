#include "GameScene.h"
#include "Entity.h"

USING_NS_CC;

bool GameScene::init()
{
	Entity::ms_pcGameScene = this;

	auto _vSize = Director::getInstance()->getVisibleSize();
	auto _vOrigin = Director::getInstance()->getVisibleOrigin();

	m_pcBackground = Layer::create();
	Sprite* _pcSprite = Sprite::create("res/background.png");
	_pcSprite->setAnchorPoint(Vec2::ZERO);
	m_pcBackground->addChild(_pcSprite);
	m_pcBackground->setAnchorPoint(Vec2::ZERO);
	double _dScaleX = _vSize.width / _pcSprite->getContentSize().width;
	double _dScaleY = _vSize.height / _pcSprite->getContentSize().height;
	m_pcBackground->setScaleX(_dScaleX);
	m_pcBackground->setScaleY(_dScaleY);
	this->addChild(m_pcBackground);

	m_pcGameWorld = Layer::create();
	m_pcGameWorld->setAnchorPoint(Vec2::ZERO);
	m_pcGameWorld->setScaleX(_dScaleX);
	m_pcGameWorld->setScaleY(_dScaleY);
	m_pcGameWorld->scheduleUpdate();
	this->addChild(m_pcGameWorld);

	//test
	DEntityInfo _stTestEntity;

	_stTestEntity.m_sBody = "red_unit_body.png";
	_stTestEntity.m_sWeapon = "sword.png";
	Entity* _pEntity = Entity::createEntity(_stTestEntity);
	CCAssert(_pEntity, "CreateEntity failed.");
	m_pcGameWorld->addChild(_pEntity);

	m_pcUI = Layer::create();
	this->addChild(m_pcUI);


	return true;
}

void GameScene::update(float delta)
{

}

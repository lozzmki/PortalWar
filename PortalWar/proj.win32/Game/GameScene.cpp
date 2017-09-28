#include "GameScene.h"
#include "Entity.h"
#include "TextLabel.h"

USING_NS_CC;

bool GameScene::init()
{
	Entity::ms_pcGameScene = this;
	TextLabel::ms_pcGameScene = this;

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
	this->addChild(m_pcGameWorld,1);

	//test
	DEntityInfo _stTestEntity;

	_stTestEntity.m_sBody = "red_unit_body.png";
	_stTestEntity.m_sWeapon = "sword.png";
	_stTestEntity.m_dHP = 50.0;
	_stTestEntity.m_nType = ENTITY_TYPE_KNIGHT;
	_stTestEntity.m_dAtkRng = 80.0;
	_stTestEntity.m_dSpd = 30.0;
	_stTestEntity.m_dAtk = 4.0;
	_stTestEntity.m_dAtkIntv = 1.0;
	_stTestEntity.m_bUseContentSize = false;
	_stTestEntity.m_vBoundSize = Vec2(40,120);
	_stTestEntity.m_dDef = 1.0;
	_stTestEntity.m_nAtkType = ATTACK_TYPE_MELEE;
	Entity* _pEntity = Entity::createEntity(_stTestEntity,0);
	m_pcGameWorld->addChild(_pEntity);
	_pEntity = Entity::createEntity(_stTestEntity, 0);
	m_pcGameWorld->addChild(_pEntity);
	_pEntity = Entity::createEntity(_stTestEntity, 0);
	m_pcGameWorld->addChild(_pEntity);
	_pEntity = Entity::createEntity(_stTestEntity, 0);
	m_pcGameWorld->addChild(_pEntity);
	_pEntity = Entity::createEntity(_stTestEntity, 0);
	m_pcGameWorld->addChild(_pEntity);
	_stTestEntity.m_sBody = "lime_unit_body.png";
	_pEntity = Entity::createEntity(_stTestEntity, 1);
	m_pcGameWorld->addChild(_pEntity);
	_stTestEntity.m_dSpd = 35.0;
	_pEntity = Entity::createEntity(_stTestEntity, 1);
	m_pcGameWorld->addChild(_pEntity);
	_stTestEntity.m_dSpd = 40.0;
	_pEntity = Entity::createEntity(_stTestEntity, 1);
	m_pcGameWorld->addChild(_pEntity);
	_stTestEntity.m_dSpd = 45.0;
	_pEntity = Entity::createEntity(_stTestEntity, 1);
	m_pcGameWorld->addChild(_pEntity);
	_stTestEntity.m_dSpd = 50.0;
	_pEntity = Entity::createEntity(_stTestEntity, 1);
	m_pcGameWorld->addChild(_pEntity);
	_stTestEntity.m_dSpd = 55.0;
	_pEntity = Entity::createEntity(_stTestEntity, 1);
	m_pcGameWorld->addChild(_pEntity);
	_stTestEntity.m_dSpd = 60.0;
	_pEntity = Entity::createEntity(_stTestEntity, 1);
	m_pcGameWorld->addChild(_pEntity);
	_stTestEntity.m_dSpd = 60.0;
	_pEntity = Entity::createEntity(_stTestEntity, 1);
	m_pcGameWorld->addChild(_pEntity);
	_stTestEntity.m_dSpd = 60.0;
	_pEntity = Entity::createEntity(_stTestEntity, 1);
	m_pcGameWorld->addChild(_pEntity);
	_stTestEntity.m_dSpd = 60.0;
	_pEntity = Entity::createEntity(_stTestEntity, 1);
	m_pcGameWorld->addChild(_pEntity);

	_stTestEntity.m_nType = ENTITY_TYPE_MAGE;
	_stTestEntity.m_dAtkRng = 400.0;
	_stTestEntity.m_nAtkType = ATTACK_TYPE_MAGIC;
	_stTestEntity.m_sWeapon = "staff.png";
	_stTestEntity.m_sProjectile = "magic_bolt.png";
	_pEntity = Entity::createEntity(_stTestEntity, 1);
	m_pcGameWorld->addChild(_pEntity);
	_stTestEntity.m_sBody = "red_unit_body.png";
	_pEntity = Entity::createEntity(_stTestEntity, 0);
	m_pcGameWorld->addChild(_pEntity);
	_stTestEntity.m_dSpd = 40.0;
	_pEntity = Entity::createEntity(_stTestEntity, 0);
	m_pcGameWorld->addChild(_pEntity);
	_stTestEntity.m_dSpd = 50.0;
	_pEntity = Entity::createEntity(_stTestEntity, 0);
	m_pcGameWorld->addChild(_pEntity);
	_stTestEntity.m_dSpd = 60.0;
	_pEntity = Entity::createEntity(_stTestEntity, 0);
	m_pcGameWorld->addChild(_pEntity);
	_stTestEntity.m_dSpd = 50.0;
	_pEntity = Entity::createEntity(_stTestEntity, 0);
	m_pcGameWorld->addChild(_pEntity);

	_stTestEntity.m_nType = ENTITY_TYPE_ARCHER;
	_stTestEntity.m_nAtkType = ATTACK_TYPE_RANGE;
	_stTestEntity.m_sWeapon = "bow.png";
	_stTestEntity.m_sProjectile = "bolt.png";
	_stTestEntity.m_sBody = "lime_unit_body.png";
	_pEntity = Entity::createEntity(_stTestEntity, 1);
	m_pcGameWorld->addChild(_pEntity);
	_pEntity = Entity::createEntity(_stTestEntity, 1);
	m_pcGameWorld->addChild(_pEntity);
	_pEntity = Entity::createEntity(_stTestEntity, 1);
	m_pcGameWorld->addChild(_pEntity);
	_pEntity = Entity::createEntity(_stTestEntity, 1);
	m_pcGameWorld->addChild(_pEntity);
	_pEntity = Entity::createEntity(_stTestEntity, 1);
	m_pcGameWorld->addChild(_pEntity);
	_pEntity = Entity::createEntity(_stTestEntity, 1);
	m_pcGameWorld->addChild(_pEntity);
	_pEntity = Entity::createEntity(_stTestEntity, 1);
	m_pcGameWorld->addChild(_pEntity);
	//test over


	m_pcProjectiles = Layer::create();
	m_pcProjectiles->scheduleUpdate();
	m_pcProjectiles->setAnchorPoint(Vec2::ZERO);
	m_pcProjectiles->setScaleX(_dScaleX);
	m_pcProjectiles->setScaleY(_dScaleY);
	this->addChild(m_pcProjectiles,2);

	m_pcTextLayer = Layer::create();
	m_pcTextLayer->scheduleUpdate();
	m_pcTextLayer->setAnchorPoint(Vec2::ZERO);
	m_pcTextLayer->setScaleX(_dScaleX);
	m_pcTextLayer->setScaleY(_dScaleY);
	this->addChild(m_pcTextLayer,3);

	m_pcUI = Layer::create();
	this->addChild(m_pcUI,4);


	return true;
}

void GameScene::update(float delta)
{

}

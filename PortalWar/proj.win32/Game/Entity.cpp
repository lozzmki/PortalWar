#include"Entity.h"
USING_NS_CC;

Entity* Entity::createEntity(const DEntityInfo& stTemplate)
{

	Entity* _pEntity = new(std::nothrow) Entity();
	if (!_pEntity || _pEntity->initWithSpriteFrameName(stTemplate.m_sBody)) {
		delete _pEntity;
		_pEntity = nullptr;
		return nullptr;
	}
	_pEntity->m_pcWeapon = Sprite::createWithSpriteFrameName(stTemplate.m_sWeapon);
	if (!_pEntity->m_pcWeapon) {
		delete _pEntity;
		_pEntity = nullptr;
		return nullptr;
	}
	_pEntity->m_pcWeapon->setPosition(Vec2(100.0, 0.0));
	_pEntity->addChild(_pEntity->m_pcWeapon);

	_pEntity->autorelease();
	_pEntity->m_stInfo = stTemplate;
	_pEntity->scheduleUpdate();

	return _pEntity;
}

void Entity::update(float delta)
{
	this->runAction(RotateBy::create(0.0f, 10));
	this->runAction(MoveBy::create(0.0f, Vec2(10, 10)));
}

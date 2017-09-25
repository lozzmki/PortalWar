#include"Entity.h"
#include"GameScene.h"
USING_NS_CC;

Entity* Entity::createEntity(const DEntityInfo& stTemplate, int nParty)
{
	Entity* _pEntity = new(std::nothrow) Entity();
	if (!_pEntity || !_pEntity->initWithSpriteFrameName(stTemplate.m_sBody)) {
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
	
	auto _vEntitySize = _pEntity->getContentSize();
	_pEntity->m_pcWeapon->setPosition(Vec2(_vEntitySize.width*0.8, _vEntitySize.height*0.5));
	_pEntity->addChild(_pEntity->m_pcWeapon);
	//_pEntity->setAnchorPoint(Vec2(1,1));
	_pEntity->m_pcWeapon->setAnchorPoint(Vec2(0.5,0.5));

	_pEntity->m_pcStateMachine = new EntityStateMachine(_pEntity);
	_pEntity->m_nParty = nParty;
	_pEntity->autorelease();
	_pEntity->m_stInfo = stTemplate;
	_pEntity->scheduleUpdate();

	if (!nParty)
		_pEntity->setPosition(RED_START_POINT);
	else
		_pEntity->setPosition(LIME_START_POINT);
	//_pEntity->setPosition(Vec2(500.0, 300.0));
	//_pEntity->runAction(RepeatForever::create(RotateBy::create(0.1, 10)));

	return _pEntity;
}

Entity::~Entity()
{
	delete m_pcStateMachine;
}

void Entity::update(float delta)
{
	m_pcStateMachine->update(delta);
}

GameScene* Entity::ms_pcGameScene = 0;

EntityStateMachine::EntityStateMachine(Entity* pcEntity/*=0*/)
{
	m_pcEntity = pcEntity;
	m_nState = ENTITY_STATE_IDLE;
}

void EntityStateMachine::update(float delta)
{
	m_dDelta = delta;
	switch (m_nState)
	{
	case ENTITY_STATE_IDLE:
		onIdle();
		break;
	case ENTITY_STATE_MOVING:
		onMove();
		break;
	case ENTITY_STATE_ATTACKING:
		onAttack();
		break;
	case ENTITY_STATE_DEAD:
		onDead();
		break;
	default:
		break;
	}
}

void EntityStateMachine::onIdle()
{
	//get on to move!
	m_nState = ENTITY_STATE_MOVING;
}

void EntityStateMachine::onMove()
{
	if (!m_pcEntity->getParty()) {
		m_pcEntity->setPosition(m_pcEntity->getPosition() + Vec2(m_pcEntity->getStatus().m_dSpd*m_dDelta, 0.0));
	}
	else {
		m_pcEntity->setPosition(m_pcEntity->getPosition() - Vec2(m_pcEntity->getStatus().m_dSpd*m_dDelta, 0.0));
	}
	//search for enemy;
	auto _lsEntities = Entity::ms_pcGameScene->getObjectLayer()->getChildren();
	for (auto _pObj : _lsEntities) {
		Entity* _pcEty = dynamic_cast<Entity*>(_pObj);
		if (_pcEty->getParty() == m_pcEntity->getParty() || _pcEty->ifDestroy())
			continue;
		Vec2 _vDelta = _pcEty->getPosition() - m_pcEntity->getPosition();
		if (m_pcEntity->getStatus().m_dAtkRng >= _vDelta.length()) {
			m_nState = ENTITY_STATE_ATTACKING;
			m_pcTarget = _pcEty;
			return;
		}

	}

}

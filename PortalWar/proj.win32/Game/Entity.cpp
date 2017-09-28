#include"Entity.h"
#include"GameScene.h"
#include"Projectile.h"
#include"TextLabel.h"
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
	_pEntity->m_nID = ms_nEntityID++;
	_pEntity->m_bIfDestroy = false;
	_pEntity->m_pcWeapon->setPosition(Vec2(_vEntitySize.width*0.8, _vEntitySize.height*0.5));
	_pEntity->addChild(_pEntity->m_pcWeapon);
	//_pEntity->setAnchorPoint(Vec2(1,1));
	_pEntity->m_pcWeapon->setAnchorPoint(Vec2(0.5,0.5));

	_pEntity->m_pcStateMachine = new EntityStateMachine(_pEntity);
	_pEntity->m_nParty = nParty;
	_pEntity->autorelease();
	_pEntity->m_stInfo = stTemplate;
	_pEntity->scheduleUpdate();

	if (!nParty) {
		_pEntity->setPosition(RED_START_POINT);
		_pEntity->setFacing(0);
	}
	else{
		_pEntity->setPosition(LIME_START_POINT);
		_pEntity->setFacing(1);
	}
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
	if (m_bIfDestroy) {
		m_dDeadTimer -= delta;
		if (m_dDeadTimer < 1e-6) {
			ms_pcGameScene->getObjectLayer()->removeChild(this);
			return;
		}
	}
	else
	{
		if (m_nFacing) {
			this->setScaleX(-1.0);
		}
		else {
			this->setScaleX(1.0);
		}
		if (m_stInfo.m_dHP <= 0.0) {
			this->setDestroy();
			return;
		}
		if (m_dAttackTimer >= 0.0) {
			m_dAttackTimer -= delta;
		}
		m_pcStateMachine->update(delta);
	}
}

void Entity::damaged(int nType, double dDamage)
{
	enumEntityType _nType = (enumEntityType)nType;
	double _dFactor = 1.0;
	switch (_nType)
	{
	case ENTITY_TYPE_WARRIOR:
		if (m_stInfo.m_nType == ENTITY_TYPE_KNIGHT) _dFactor = 0.75;
		if (m_stInfo.m_nType == ENTITY_TYPE_ASSASSIN) _dFactor = 1.25;
		break;
	case ENTITY_TYPE_ARCHER:
		if (m_stInfo.m_nType == ENTITY_TYPE_MAGE) _dFactor = 1.5;
		if (m_stInfo.m_nType == ENTITY_TYPE_KNIGHT) _dFactor = 0.7;
		if (m_stInfo.m_nType == ENTITY_TYPE_ASSASSIN) _dFactor = 0.5;
		break;
	case ENTITY_TYPE_MAGE:
		if (m_stInfo.m_nType == ENTITY_TYPE_WARRIOR) _dFactor = 1.25;
		if (m_stInfo.m_nType == ENTITY_TYPE_KNIGHT) _dFactor = 2.0;
		if (m_stInfo.m_nType == ENTITY_TYPE_ASSASSIN) _dFactor = 0.5;
		break;
	case ENTITY_TYPE_KNIGHT:
		if (m_stInfo.m_nType == ENTITY_TYPE_WARRIOR) _dFactor = 1.25;
		if (m_stInfo.m_nType == ENTITY_TYPE_ASSASSIN) _dFactor = 1.25;
		break;
	case ENTITY_TYPE_ASSASSIN:
		if (m_stInfo.m_nType == ENTITY_TYPE_WARRIOR) _dFactor = 0.75;
		if (m_stInfo.m_nType == ENTITY_TYPE_ARCHER) _dFactor = 1.5;
		if (m_stInfo.m_nType == ENTITY_TYPE_MAGE) _dFactor = 1.5;
		if (m_stInfo.m_nType == ENTITY_TYPE_KNIGHT) _dFactor = 0.75;
		break;
	default:
		break;
	}

	double _dDamage = dDamage * _dFactor - m_stInfo.m_dDef;
	if (_dDamage < 0.0)_dDamage = 0.0;
	m_stInfo.m_dHP -= _dDamage;
	if (m_stInfo.m_dHP <= 0.0) {
		this->setDestroy();
	}
	CCLOG("%d Attacked, %f damage.", m_nID, _dDamage);
	char* _sDamageText = new char[100];
	sprintf(_sDamageText, "-%d", (int)_dDamage);
	TextLabel::createFloatingText(this->getPosition(), _sDamageText);
	delete _sDamageText;
}

void Entity::attack(cocos2d::Vec2 vDirection)
{
	if (m_dAttackTimer > 1e-6) {
		return;
	}
	else {
		//CD
		m_dAttackTimer = m_stInfo.m_dAtkIntv;
		//create a projectile towards vDirection
		DProjectileInfo _stProjectile;
		switch (m_stInfo.m_nAtkType)
		{
		case ATTACK_TYPE_MELEE:
			_stProjectile.m_bShow = false;
			_stProjectile.m_bMove = false;
			_stProjectile.m_bUseContentSize = false;
			_stProjectile.m_vBoundSize = m_pcWeapon->getContentSize();
			_stProjectile.m_dLastTime = 0.5;
			break;
		case ATTACK_TYPE_RANGE:
			_stProjectile.m_sBody = m_stInfo.m_sProjectile;
			_stProjectile.m_bShow = true;
			_stProjectile.m_bMove = true;
			_stProjectile.m_bUseContentSize = true;
			_stProjectile.m_dLastTime = 10.0;
			_stProjectile.m_nAtkNum = 1;
			_stProjectile.m_vDirection = vDirection;
			break;
		case ATTACK_TYPE_MAGIC:
			_stProjectile.m_sBody = m_stInfo.m_sProjectile;
			_stProjectile.m_bShow = true;
			_stProjectile.m_bMove = true;
			_stProjectile.m_bUseContentSize = true;
			_stProjectile.m_dLastTime = 10.0;
			_stProjectile.m_nAtkNum = 2;
			_stProjectile.m_vDirection = vDirection;
			break;
		default:
			break;
		}
		_stProjectile.m_dAtk = m_stInfo.m_dAtk;
		_stProjectile.m_dSpd = 200.0;
		_stProjectile.m_nType = m_stInfo.m_nType;
		
		Projectile::createProjectile(_stProjectile, this);
	}
	
}

cocos2d::Vec2 Entity::getWeaponPos()
{
	Vec2 _vWeapon = m_pcWeapon->getPosition();
	_vWeapon.y = 0.0;
	if (m_nFacing) {
		_vWeapon.x = -_vWeapon.x;
	}
	_vWeapon.x /= 2;
	//return m_pcWeapon->getPosition();
	return this->getPosition() +_vWeapon;
	//return m_pcWeapon->convertToWorldSpace(m_pcWeapon->getPosition());
}

cocos2d::Rect Entity::getBoundRect()
{
	Rect _rctBound;
	Vec2 _vPos = this->getPosition();
	Vec2 _vSize;
	if (m_stInfo.m_bUseContentSize) {
		_vSize = this->getContentSize();
	}
	else {
		_vSize = this->m_stInfo.m_vBoundSize;
	}
	_rctBound.origin = _vPos;// -_vSize / 2;
	_rctBound.size = Size(_vSize);

	return _rctBound;
}

void Entity::setDestroy()
{
	m_bIfDestroy = true;
	this->stopAllActions();
	if(this->m_nFacing)
		this->runAction(RotateBy::create(0.6f, -90.0));
	else
		this->runAction(RotateBy::create(0.6f, 90.0));

	m_dDeadTimer = 1.0;
}

GameScene* Entity::ms_pcGameScene = 0;

int Entity::ms_nEntityID = 0;

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
			if (_vDelta.x < 0) {
				m_pcEntity->setFacing(1);
			}
			else {
				m_pcEntity->setFacing(0);
			}
			return;
		}

	}

}

void EntityStateMachine::onAttack()
{

	if (m_pcEntity && !m_pcEntity->ifDestroy() && m_pcTarget && !m_pcTarget->ifDestroy()) {
		//perform an attack;
		m_pcEntity->attack(m_pcTarget->getPosition() - m_pcEntity->getPosition());
	}
	else {
		//target lost
		m_nState = ENTITY_STATE_MOVING;
	}
}

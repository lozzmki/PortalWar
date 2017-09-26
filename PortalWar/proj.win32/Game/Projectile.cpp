#include"Entity.h"
#include"Projectile.h"
#include"GameScene.h"

USING_NS_CC;

Projectile* Projectile::createProjectile(const DProjectileInfo& stInfo, Entity* pcSource)
{
	Projectile* _pProjectile = new(std::nothrow) Projectile();
	if(stInfo.m_bShow){
		if (!_pProjectile || !_pProjectile->initWithSpriteFrameName(stInfo.m_sBody)) {
			delete _pProjectile;
			_pProjectile = nullptr;
			return nullptr;
		}
	}
	else {
		if (!_pProjectile) {
			delete _pProjectile;
			_pProjectile = nullptr;
			return nullptr;
		}
	}

	_pProjectile->m_stInfo = stInfo;
	_pProjectile->m_bIfDestroy = false;
	_pProjectile->m_dLastTimer = stInfo.m_dLastTime;
	_pProjectile->m_nParty = pcSource->getParty();
	_pProjectile->setPosition(pcSource->getWeaponPos());
	_pProjectile->setAnchorPoint(Vec2(0.5, 0.5));
	//_pProjectile->setPosition(pcSource->getPosition());
	if (stInfo.m_vDirection.x < 0.0) {
		_pProjectile->setScaleX(-1.0f);
	}
	_pProjectile->scheduleUpdate();
	_pProjectile->autorelease();
	Entity::ms_pcGameScene->getProjectileLayer()->addChild(_pProjectile);

	return _pProjectile;
}

cocos2d::Rect Projectile::getBoundRect()
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

void Projectile::setDestroy()
{
	m_bIfDestroy = true;
}

void Projectile::update(float delta)
{
	

	//ifDestroy
	if (m_bIfDestroy) {
		Entity::ms_pcGameScene->getProjectileLayer()->removeChild(this);
		return;
	}
	//check last time
	if (m_dLastTimer > 0.0) {
		m_dLastTimer -= delta;
	}
	else {
		this->setDestroy();
		return;
	}

	if (m_stInfo.m_vDirection.x < 0.0) {
		this->setScaleX(-1.0);
	}
	else {
		this->setScaleX(1.0);
	}

	//move
	if(m_stInfo.m_bMove)
		this->setPosition(this->getPosition() + m_stInfo.m_vDirection.getNormalized() * m_stInfo.m_dSpd * delta);

	//checkBound
	for (auto _pObj : Entity::ms_pcGameScene->getObjectLayer()->getChildren()) {
		Entity* _pEntity = dynamic_cast<Entity*>(_pObj);
		CCASSERT(_pEntity, "should be entity!");
		if (_pEntity->ifDestroy() || _pEntity->getParty() == m_nParty)
			continue;
		if (_pEntity->getBoundRect().intersectsRect(this->getBoundRect())) {
			//pEntity got hit!
			if (m_stInfo.m_nAtkNum < 0 || m_setHitList.size() < m_stInfo.m_nAtkNum) {
				if (m_setHitList.find(_pEntity->getID()) != m_setHitList.end()) {
					//already hit, pass
					continue;
				}
				else {
					m_setHitList.insert(_pEntity->getID());
					//perform a hit action, inflict damage
					_pEntity->damaged(m_stInfo.m_nType, m_stInfo.m_dAtk);
				}
			}
			else {
				//hit list full, destroy this projectile
				this->setDestroy();
				return;
			}
		}
	}
}

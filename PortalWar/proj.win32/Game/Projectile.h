#ifndef PROJECTILE_H
#define PROJECTILE_H

#include<cocos2d.h>
#include<set>

class Entity;

struct DProjectileInfo {
	cocos2d::Vec2 m_vDirection;
	
	double m_dSpd;
	int m_nAtkNum;
	int m_nType;
	double m_dAtk;
	double m_dLastTime;

	bool m_bUseContentSize;
	cocos2d::Vec2 m_vBoundSize;

	bool m_bMove;
	bool m_bShow;
	std::string m_sBody;
};

class Projectile :public cocos2d::Sprite {
public:
	static Projectile* createProjectile(const DProjectileInfo& stInfo, Entity* pcSource);

	cocos2d::Rect getBoundRect();
	void setDestroy();

	void update(float delta);
private:
	int m_nParty;
	DProjectileInfo m_stInfo;
	
	double m_dLastTimer;
	bool m_bIfDestroy;
	std::set<int> m_setHitList;
};

#endif
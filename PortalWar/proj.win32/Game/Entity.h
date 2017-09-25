#ifndef ENTITY_H
#define ENTITY_H

#include<cocos2d.h>

struct DEntityInfo {
	double m_dHP;
	double m_dAtk;
	double m_dDef;
	double m_dSpd;
	double m_dAtkSpd;
	double m_dAtkRng;

	std::string m_sBody;
	std::string m_sWeapon;
};

class Entity :public cocos2d::Sprite {

public:
	static Entity* createEntity(const DEntityInfo&);

	virtual void update(float delta);
private:
	cocos2d::Sprite* m_pcWeapon;
	
	DEntityInfo m_stInfo;
};
#endif
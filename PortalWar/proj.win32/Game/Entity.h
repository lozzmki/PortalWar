#ifndef ENTITY_H
#define ENTITY_H

#include<cocos2d.h>

const Vec2 RED_START_POINT = Vec2(100.0, 250.0);
const Vec2 LIME_START_POINT = Vec2(900.0, 250.0);

class Entity;
class GameScene;

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

enum enumEntityState {
	ENTITY_STATE_IDLE,
	ENTITY_STATE_MOVING,
	ENTITY_STATE_ATTACKING,
	ENTITY_STATE_DEAD,
};

class EntityStateMachine {
public:
	EntityStateMachine(Entity* pcEntity=0);

	void update(float delta);
private:
	Entity* m_pcEntity;
	Entity* m_pcTarget;
	enumEntityState m_nState;
	double m_dDelta;

	void onIdle();
	void onMove();
	void onAttack();
	void onDead();
};

class Entity :public cocos2d::Sprite {

public:
	static Entity* createEntity(const DEntityInfo&, int nParty = 0);
	virtual ~Entity();
	virtual void update(float delta);

	inline void setDestroy() { m_bIfDestroy = true; }
	inline int getParty() { return m_nParty; }
	inline const DEntityInfo& getStatus() { return m_stInfo; }
	inline bool ifDestroy() { return m_bIfDestroy; }

	static GameScene* ms_pcGameScene;
private:
	EntityStateMachine* m_pcStateMachine;
	cocos2d::Sprite* m_pcWeapon;

	int m_nParty;
	bool m_bIfDestroy;

	DEntityInfo m_stInfo;
};
#endif
#ifndef ENTITY_H
#define ENTITY_H

#include<cocos2d.h>

const cocos2d::Vec2 RED_START_POINT = Vec2(100.0, 250.0);
const cocos2d::Vec2 LIME_START_POINT = Vec2(900.0, 250.0);

class Entity;
class GameScene;

enum enumEntityState {
	ENTITY_STATE_IDLE,
	ENTITY_STATE_MOVING,
	ENTITY_STATE_ATTACKING,
};
enum enumEntityType {
	ENTITY_TYPE_WARRIOR,
	ENTITY_TYPE_ARCHER,
	ENTITY_TYPE_MAGE,
	ENTITY_TYPE_KNIGHT,
	ENTITY_TYPE_ASSASSIN
};

struct DEntityInfo {
	double m_dHP;
	double m_dAtk;
	double m_dDef;
	double m_dSpd;
	double m_dAtkSpd;
	double m_dAtkRng;
	
	enumEntityType m_nType;

	cocos2d::Vec2 m_vBoundSize;

	std::string m_sBody;
	std::string m_sWeapon;
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
};

class Entity :public cocos2d::Sprite {

public:
	static Entity* createEntity(const DEntityInfo&, int nParty = 0);
	virtual ~Entity();
	virtual void update(float delta);

	void damaged(int nType, double dDamage);
	void attack(cocos2d::Vec2);
	cocos2d::Vec2 getWeaponPos();
	cocos2d::Rect getBoundRect();

	inline int getFacing() { return m_nFacing; }
	inline void setFacing(int val) { m_nFacing = val; }
	inline int getID() { return m_nID; }
	inline void setDestroy();
	inline int getParty() { return m_nParty; }
	inline const DEntityInfo& getStatus() { return m_stInfo; }
	inline bool ifDestroy() { return m_bIfDestroy; }

	static GameScene* ms_pcGameScene;
private:
	EntityStateMachine* m_pcStateMachine;
	cocos2d::Sprite* m_pcWeapon;

	int m_nID;
	int m_nParty;
	int m_nFacing;//0=towards right
	bool m_bIfDestroy;
	double m_dAttackTimer;
	double m_dDeadTimer;

	static int ms_nEntityID;

	DEntityInfo m_stInfo;
};
#endif
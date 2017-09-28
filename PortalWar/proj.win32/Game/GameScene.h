#ifndef GAMESCENE_H
#define GAMESCENE_H

#include<cocos2d.h>

class GameScene :public cocos2d::Scene {
public:
	CREATE_FUNC(GameScene);

	virtual bool init();
	virtual void update(float delta);

	inline cocos2d::Layer* getObjectLayer() { return m_pcGameWorld; }
	inline cocos2d::Layer* getProjectileLayer() { return m_pcProjectiles; }
	inline cocos2d::Layer* getTextlayer() { return m_pcTextLayer; }
private:
	cocos2d::Layer* m_pcBackground;
	cocos2d::Layer* m_pcGameWorld;
	cocos2d::Layer* m_pcProjectiles;
	cocos2d::Layer* m_pcTextLayer;
	cocos2d::Layer* m_pcUI;

	void initEntities();
};

#endif

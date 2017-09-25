#ifndef GAMESCENE_H
#define GAMESCENE_H

#include<cocos2d.h>

class GameScene :public cocos2d::Scene {
public:
	CREATE_FUNC(GameScene);

	virtual bool init();
	virtual void update(float delta);
private:
	cocos2d::Layer* m_pcBackground;
	cocos2d::Layer* m_pcGameWorld;
	cocos2d::Layer* m_pcUI;

};

#endif
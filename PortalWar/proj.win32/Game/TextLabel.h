#ifndef TEXTLABEL_H
#define TEXTLABEL_H

#include<cocos2d.h>

class GameScene;

enum enumLabelType {
	LABEL_TYPE_FLOAT,
	LABEL_TYPE_NORMAL,
};

class TextLabel :public cocos2d::Label {
public:
	CREATE_FUNC(TextLabel);
	static TextLabel* createFloatingText(cocos2d::Vec2 vPos, std::string sText, double dTime = 1.0);

	virtual bool init();
	virtual void update(float delta);

	static GameScene* ms_pcGameScene;
private:
	enumLabelType m_nType;
	double m_dTimer;
	double m_dSetTime;
	bool m_bActive;
};

#endif
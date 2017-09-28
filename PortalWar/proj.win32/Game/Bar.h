#ifndef BAR_H
#define BAR_H

#include<cocos2d.h>

class Bar :public cocos2d::Node {
public:
	static Bar* createBar(std::string sContents, std::string sFrame);

	bool init(std::string sContents, std::string sFrame);
	void setRatio(double dTime, double dVal);
private:
	cocos2d::Sprite* m_pcContents;
	cocos2d::Sprite* m_pcFrame;
	cocos2d::ProgressTimer* m_pcController;
};

#endif
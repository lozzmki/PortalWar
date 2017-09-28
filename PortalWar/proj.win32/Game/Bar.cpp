#include"Bar.h"
USING_NS_CC;

Bar* Bar::createBar(std::string sContents, std::string sFrame)
{
	Bar* _pBar = new(std::nothrow) Bar();
	if (!_pBar || !_pBar->init(sContents, sFrame)) {
		delete _pBar;
		_pBar = nullptr;
		return nullptr;
	}

	return _pBar;
}

bool Bar::init(std::string sContents, std::string sFrame)
{
	m_pcFrame = Sprite::createWithSpriteFrameName(sFrame);
	m_pcContents = Sprite::createWithSpriteFrameName(sContents);
	m_pcController = ProgressTimer::create(m_pcContents);

	if(!m_pcContents || !m_pcController || !m_pcFrame){
		delete m_pcContents;
		delete m_pcController;
		delete m_pcFrame;
		return false;
	}

	m_pcController->setType(ProgressTimerType::BAR);
	m_pcController->setMidpoint(Vec2(0.5, 0));
	m_pcController->setBarChangeRate(Vec2(0,1));
	m_pcController->setPercentage(100.0);
	m_pcController->setPosition(Vec2::ZERO);
	m_pcFrame->setPosition(Vec2::ZERO);

	this->scheduleUpdate();
	this->setContentSize(m_pcFrame->getContentSize());
	this->setAnchorPoint(Vec2::ZERO);
	this->addChild(m_pcFrame);
	this->addChild(m_pcController);

	return true;

}

void Bar::setRatio(double dTime, double dVal)
{
	//m_pcController->stopAllActions();
	//m_pcController->runAction(ProgressTo::create(dTime, dVal));
	m_pcController->setPercentage(dVal);
}

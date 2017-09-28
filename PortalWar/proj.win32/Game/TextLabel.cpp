#include "TextLabel.h"
#include "GameScene.h"
USING_NS_CC;

TextLabel* TextLabel::createFloatingText(Vec2 vPos, std::string sText, double dTime /*= 1.0*/)
{
	TTFConfig _stConfig;
	_stConfig.fontFilePath = "fonts/Marker Felt.ttf";
	_stConfig.outlineSize = 2;
	_stConfig.fontSize = 30.0;
	TextLabel* _text = new(std::nothrow)TextLabel();
	if (!_text || !_text->initWithTTF(_stConfig,sText,TextHAlignment::CENTER,0)) {
		CCAssert(0, "init failed");
		delete _text;
		_text = nullptr;
		return nullptr;
	}
	_text->autorelease();
	_text->setString(sText);
	_text->m_dSetTime = _text->m_dTimer = dTime;
	_text->m_nType = LABEL_TYPE_FLOAT;
	_text->m_bActive = true;
	_text->scheduleUpdate();
	_text->runAction(MoveBy::create(dTime, Vec2(0.0, 100.0)));
	_text->setPosition(vPos);
	_text->enableOutline(Color4B(0, 0, 0, 255));
	_text->setColor(Color3B(255, 192, 64));
	ms_pcGameScene->getTextlayer()->addChild(_text);
	return _text;
}

bool TextLabel::init()
{
	m_nType = LABEL_TYPE_NORMAL;
	m_bActive = false;
	m_dSetTime = m_dTimer = 0.0;
	return true;
}

void TextLabel::update(float delta)
{
	switch (m_nType)
	{
	case LABEL_TYPE_FLOAT:
		if (m_dTimer > 0.0) {
			m_dTimer -= delta;
			if (m_dTimer > 0.0)
				this->setOpacity(255 * m_dTimer / m_dSetTime);
			else
				this->setOpacity(0);
		}
		else {
			ms_pcGameScene->getTextlayer()->removeChild(this);
		}
		break;
	case LABEL_TYPE_NORMAL:
		break;
	default:
		break;
	}
}

GameScene* TextLabel::ms_pcGameScene = 0;

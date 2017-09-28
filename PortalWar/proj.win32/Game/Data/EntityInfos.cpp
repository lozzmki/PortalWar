#include"EntityInfos.h"
#include<cocos2d.h>
USING_NS_CC;

void EntityInfos::initInfos()
{
	//Warrior
	s_stWarrior.m_sWeapon = "sword.png";
	s_stWarrior.m_sProjectile = "";
	s_stWarrior.m_nType = ENTITY_TYPE_WARRIOR;
	s_stWarrior.m_nAtkType = ATTACK_TYPE_MELEE;
	s_stWarrior.m_dHP = s_stWarrior.m_dMaxHP = 60.0;
	s_stWarrior.m_dAtk = 5.0;
	s_stWarrior.m_dAtkIntv = 1.0;
	s_stWarrior.m_dAtkRng = 80.0;
	s_stWarrior.m_dDef = 1.0;
	s_stWarrior.m_dSpd = 50.0;
	s_stWarrior.m_bUseContentSize = false;
	s_stWarrior.m_vBoundSize = Vec2(40, 120);

	//Archer
	s_stArcher.m_sWeapon = "bow.png";
	s_stArcher.m_sProjectile = "bolt.png";
	s_stArcher.m_nType = ENTITY_TYPE_ARCHER;
	s_stArcher.m_nAtkType = ATTACK_TYPE_RANGE;
	s_stArcher.m_dHP = s_stArcher.m_dMaxHP = 50.0;
	s_stArcher.m_dAtk = 7.0;
	s_stArcher.m_dAtkIntv = 1.2;
	s_stArcher.m_dAtkRng = 400.0;
	s_stArcher.m_dDef = 0.0;
	s_stArcher.m_dSpd = 40.0;
	s_stArcher.m_bUseContentSize = false;
	s_stArcher.m_vBoundSize = Vec2(40, 120);

	//Mage
	s_stMage.m_sWeapon = "staff.png";
	s_stMage.m_sProjectile = "magic_bolt.png";
	s_stMage.m_nType = ENTITY_TYPE_MAGE;
	s_stMage.m_nAtkType = ATTACK_TYPE_MAGIC;
	s_stMage.m_dHP = s_stMage.m_dMaxHP = 45.0;
	s_stMage.m_dAtk = 6.0;
	s_stMage.m_dAtkIntv = 1.2;
	s_stMage.m_dAtkRng = 300.0;
	s_stMage.m_dDef = 0.0;
	s_stMage.m_dSpd = 40.0;
	s_stMage.m_bUseContentSize = false;
	s_stMage.m_vBoundSize = Vec2(40, 120);

	//Knight
	s_stKnight.m_sWeapon = "sword.png";
	s_stKnight.m_sProjectile = "";
	s_stKnight.m_nType = ENTITY_TYPE_KNIGHT;
	s_stKnight.m_nAtkType = ATTACK_TYPE_MELEE;
	s_stKnight.m_dHP = s_stKnight.m_dMaxHP = 80.0;
	s_stKnight.m_dAtk = 8.0;
	s_stKnight.m_dAtkIntv = 1.0;
	s_stKnight.m_dAtkRng = 100.0;
	s_stKnight.m_dDef = 3.0;
	s_stKnight.m_dSpd = 75.0;
	s_stKnight.m_bUseContentSize = false;
	s_stKnight.m_vBoundSize = Vec2(40, 120);

	//Assassin
	s_stAssassin.m_sWeapon = "sword.png";
	s_stAssassin.m_sProjectile = "";
	s_stAssassin.m_nType = ENTITY_TYPE_ASSASSIN;
	s_stAssassin.m_nAtkType = ATTACK_TYPE_MELEE;
	s_stAssassin.m_dHP = s_stAssassin.m_dMaxHP = 50.0;
	s_stAssassin.m_dAtk = 7.0;
	s_stAssassin.m_dAtkIntv = 0.8;
	s_stAssassin.m_dAtkRng = 80.0;
	s_stAssassin.m_dDef = 1.0;
	s_stAssassin.m_dSpd = 65.0;
	s_stAssassin.m_bUseContentSize = false;
	s_stAssassin.m_vBoundSize = Vec2(40, 120);
}

DEntityInfo EntityInfos::s_stWarrior;

DEntityInfo EntityInfos::s_stArcher;

DEntityInfo EntityInfos::s_stMage;

DEntityInfo EntityInfos::s_stKnight;

DEntityInfo EntityInfos::s_stAssassin;

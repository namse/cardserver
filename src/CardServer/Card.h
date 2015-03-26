#pragma once
#include "protocol.pb.h"
typedef unsigned int Mana;
class Card
{
	enum CardType
	{
		UNIT = 0,
		ARCANE = 1,
	};

	enum UnitAttackType
	{
		NONE = 0,
		NEAR = 1,
		FAR = 2,
	};
public:
	Card();
	~Card();
	
	virtual bool AvailableAction(protocol::Card& inPacket, const void* gameRef);
	virtual void DoAction(protocol::Card& inPacket, const void* gameRef);
	virtual void DoAttack(const void* gameRef);
	virtual int OnAttack(int damage); // return value for counting damage
	virtual void OnDie();

	virtual Mana GetCostMana(){ return m_CostMana; }
private:
	bool AvailableUnitSpace(protocol::Card& inPacket, const void* gameRef);
	bool AvailableMana(protocol::Card& inPacket, const void* gameRef);
	// on Field
	void* FindMyOwnerPlayer(const void* gameRef);

	virtual int GetDamage();

	Mana m_CostMana;
	CardType m_CardType;
	UnitAttackType m_UnitAttackType;
};

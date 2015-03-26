#pragma once
#include "Field.h"
#include "Hands.h"
#include "Decks.h"

class Player
{
public:
	Player();
	~Player();

	Field* GetField(){ return &m_Field; }
	Hands* GetHands(){ return &m_Hands; }
	Decks* GetDecks(){ return &m_Decks; }
	Mana GetMana(){ return m_Mana; }
	void CostMana(Mana mana){ m_Mana -= mana; }

	void OnAttack(int damage);
private:
	Field m_Field;
	Hands m_Hands;
	Decks m_Decks;
	Mana m_Mana;
};
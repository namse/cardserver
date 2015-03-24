#pragma once
#include "Card.h"
class Hands
{
public:
	Hands();
	~Hands();

	enum CardIndex
	{
		CARD_1 = 0,
		CARD_2 = 1,
		CARD_3 = 2,
		CARD_4 = 3,
	};
	enum CardType
	{
		UNIT = 0,
		ARCANE = 1,
	};

	Card* GetCard(IN CardType cardType, IN CardIndex index)
	{
		return m_Cards[cardType * 4 + index];
	}
	void SetCard(IN CardType cardType, IN CardIndex index, IN Card* card)
	{
		m_Cards[cardType * 4 + index] = card;
	}

private:
	Card* m_Cards[8];
};


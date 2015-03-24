#pragma once
#include "Card.h"
#define IN
#define OUT

class Field
{
public:
	Field();
	~Field();
	enum Player
	{
		PLAYER_1 = 0,
		PLAYER_2 = 1,
	};
	enum CardIndex
	{
		CARD_1 = 0,
		CARD_2 = 1,
		CARD_3 = 2,
	};
	enum FrontOrBack
	{
		FRONT = 0,
		BACK = 1,
	};

	Card* GetCard(IN Player player, IN FrontOrBack frontOrBack, IN CardIndex index)
	{
		return m_Cards[player * 6 + frontOrBack * 3 + index];
	}
	void SetCard(IN Player player, IN FrontOrBack frontOrBack, IN CardIndex index, IN Card* card)
	{
		m_Cards[player * 6 + frontOrBack * 3 + index] = card;
	}

private:
	Card* m_Cards[12];
};


#include "stdafx.h"
#include "Card.h"
#include "Game.h"


Card::Card()
{
}


Card::~Card()
{
}

bool Card::AvailableAction(protocol::Card& inPacket, const void* gameRef)
{
	auto game = (Game*)gameRef;

	return AvailableMana(inPacket, gameRef) && AvailableUnitSpace(inPacket, gameRef);
}

void Card::DoAction(protocol::Card& inPacket, const void* gameRef)
{
	auto game = (Game*)gameRef;

	if (m_CardType == UNIT)
	{
		auto cardTarget = inPacket.cardtarget().Get(0);
		auto field = game->GetPlayer(inPacket.playerid())->GetField();
		field->SetCard((Field::FrontOrBack)cardTarget.fieldfrontorback(), (Field::CardIndex)cardTarget.fieldindex(), this);
	}

}

bool Card::AvailableUnitSpace(protocol::Card& inPacket, const void* gameRef)
{
	auto game = (Game*)gameRef;
	
	if (m_CardType == ARCANE)
		return true;
	
	if (inPacket.cardtarget_size() <= 0)
		return false;
	auto cardTarget = inPacket.cardtarget().Get(0);
	if (nullptr == game->GetPlayer(inPacket.playerid())->GetField()->GetCard((Field::FrontOrBack)cardTarget.fieldfrontorback(), (Field::CardIndex)cardTarget.fieldindex()))
		return false;
	return true;
}

bool Card::AvailableMana(protocol::Card& inPacket, const void* gameRef)
{
	auto game = (Game*)gameRef;
	auto haveMana = game->GetPlayer(inPacket.playerid())->GetMana();

	return haveMana >= m_CostMana;
}

void Card::DoAttack(const void* gameRef)
{
	auto game = (Game*)gameRef;
	auto myPlayer = (Player*)FindMyOwnerPlayer(gameRef);
	auto enemyPlayer = game->GetEnemyPlayer(myPlayer);
	
	Field::CardIndex fieldIndex;
	Field::FrontOrBack fieldFrontOrBack;

	// init field info
	for (int i = 0; i < 2; i++) // front(0) or back(1)
	{
		for (int l = 0; l < 4; l++) // first(0) ~ fourth(3)
		{
			if (this == myPlayer->GetField()->GetCard((Field::FrontOrBack)i, (Field::CardIndex)l))
			{
				fieldIndex = (Field::CardIndex)l;
				fieldFrontOrBack = (Field::FrontOrBack)i;
				break;
			}
		}
	}

	// 근거리면 (내가 뒤고 앞에 아군이 있으면)을 제외하고 공격
	// 뒤면 무조건 공격
	if ((m_UnitAttackType == UnitAttackType::NEAR
		&& (fieldFrontOrBack == Field::FRONT
		|| (fieldFrontOrBack == Field::BACK
		&& nullptr == myPlayer->GetField()->GetCard(Field::FRONT, fieldIndex))))
		|| m_UnitAttackType == UnitAttackType::FAR)
	{
		Card* attackTargetCard = nullptr;
		auto frontEnemyCard = enemyPlayer->GetField()->GetCard(Field::FRONT, fieldIndex);
		auto backEnemyCard = enemyPlayer->GetField()->GetCard(Field::FRONT, fieldIndex);
		if (frontEnemyCard != nullptr)
			attackTargetCard = frontEnemyCard;
		else if (backEnemyCard != nullptr)
			attackTargetCard = backEnemyCard;

		if (attackTargetCard != nullptr)
		{
			if (m_UnitAttackType == UnitAttackType::FAR
				&& fieldFrontOrBack == Field::BACK
				&& nullptr != myPlayer->GetField()->GetCard(Field::FRONT, fieldIndex))
				frontEnemyCard->OnAttack(GetDamage());
			else
				OnAttack(frontEnemyCard->OnAttack(GetDamage()));
		}
		else
		{
			enemyPlayer->OnAttack(GetDamage());
		}
	}
}

void* Card::FindMyOwnerPlayer(const void* gameRef)
{
	auto game = (Game*)gameRef;

	auto player1Field = game->GetPlayer(Game::PlayerType::PLAYER_1)->GetField();
	for (int playerIndex = 0; playerIndex < 2; playerIndex++) // player1(0) ~ player2(1)
	{
		for (int i = 0; i < 2; i++) // front(0) or back(1)
		{
			for (int l = 0; l < 4; l++) // first(0) ~ fourth(3)
			{
				if (this == game->GetPlayer((Game::PlayerType)playerIndex)->GetField()->GetCard((Field::FrontOrBack)i, (Field::CardIndex)l))
					return game->GetPlayer((Game::PlayerType)playerIndex);
			}
		}
	}
	//assert(false); // 여기까지 오면 안됌~
}

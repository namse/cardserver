#include "stdafx.h"
#include "Card.h"
#include "Game.h"


Card::Card()
{
}


Card::~Card()
{
}

bool Card::AvailableAction(protocol::Card inPacket, const void* gameRef)
{
	auto game = (Game*)gameRef;


	return true;
}

void Card::DoAction(protocol::Card inPacket, const void* gameRef)
{
	auto game = (Game*)gameRef;
}

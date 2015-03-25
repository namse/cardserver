#pragma once
#include "protocol.pb.h"
class Card
{
public:
	Card();
	~Card();
	
	bool AvailableAction(protocol::Card inPacket, const void* gameRef);
	void DoAction(protocol::Card inPacket, const void* gameRef);
};


#include "stdafx.h"
#include "Player.h"

Player::Player()
{

}

Player::~Player()
{

}

void Player::OnAttack(int damage)
{
	m_HP -= damage;
}

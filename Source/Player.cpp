#include "Player.h"

bool Player::IsValid ()
{
  return Health > 0.1f && Health <= 100 && (Origin.x != 0 && Origin.y != 0 && Origin.z != 0);
}

bool Player::IsDead ()
{
  return Health <= 0.1f;
}

bool Player::IsVisible ()
{
  return IsOccluded == 0;
}
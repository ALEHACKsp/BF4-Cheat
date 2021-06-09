#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Gun.h"

struct vec3
{
    int x, y, z;
};

class Player {
 public:
  char* Name;
  char* VehiculeName;
  int Team;
  vec3 Origin;
  int Pose;

  int IsOccluded;
  bool IsSpectator;

  bool IsDriver;
  bool InVehicule;

  float Health;
  float MaxHealth;

  Gun CurrentWeapon;

  //Cheat Var
  bool NoGravity = false;
  bool SpeedBullet = false;
  bool Recoil = false;
  bool Spread = false;

  bool IsValid();
  bool IsDead();
  bool IsVisible();
};

#endif //_PLAYER_H_

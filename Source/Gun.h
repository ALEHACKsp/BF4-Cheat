#ifndef _GUN_H_
#define _GUN_H_

#include <string>

enum WeaponSlot
{
    M_PRIMARY = 0,
    M_SECONDARY = 1,
    M_GADGET = 2,
    M_GRENADE = 6,
    M_KNIFE = 7
};

class Gun {
 public:
  char* Name;
  WeaponSlot Slot;

  int Ammo;
  int AmmoClip;

  float RecoilMultiplier;
  float RecoilDecrease;

  float DeviationZoom;
  float GameplayDevationZoom;
  float DevationNoZoom;
  float GameplayDeviationNoZoom;

  float BulletSpeed;
  float BulletGravity;
  int BulletsPerShell;
  int BulletsPerShot;

  bool IsValid();
};

#endif //_GUN_H_

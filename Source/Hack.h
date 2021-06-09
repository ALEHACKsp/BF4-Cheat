#ifndef _HACK_H_
#define _HACK_H_

#include "Player.h"
#include "Offset.h"

class Hack {
 public:
  bool bGravity, bRecoil, bSpread;

  Hack();
  bool CheatRoutine();
 private:
  Offsets offsets;
  Player LocalPlayer;

  static bool IsValid(uintptr_t address);
  uintptr_t GetClientSoldierEntity(uintptr_t pClientPlayer, Player player) const;
  uintptr_t GetLocalSoldier();
  uintptr_t GetSoldierWeapon();
  bool NoGravity();
  bool NoRecoil();
  bool NoSpread();
};

#endif //_HACK_H_

#include "Hack.h"

bool Hack::CheatRoutine ()
{
  uintptr_t pGContext = *(uintptr_t*)(offsets.OFFSET_CLIENTGAMECONTEXT);
  if (!IsValid(pGContext))
    return false;

  uintptr_t pPlayerManager = *(uintptr_t*)(pGContext + offsets.m_pPlayerManager);
  if (!IsValid(pPlayerManager))
    return false;

  uintptr_t pLocalPlayer = *(uintptr_t*)(pPlayerManager + offsets.m_pLocalPlayer);
  if (!IsValid(pLocalPlayer))
    return false;

  LocalPlayer.Team = *(int*)(pLocalPlayer + offsets.m_teamId);

  uintptr_t pLocalSoldier = GetClientSoldierEntity(pLocalPlayer, LocalPlayer);
  if (!IsValid(pLocalSoldier))
    return false;

  uintptr_t pHealthComponent = *(uintptr_t*)(pLocalSoldier + offsets.m_pHealthComponent);
  if (!IsValid(pHealthComponent))
    return false;

  LocalPlayer.Health = *(float*)(pHealthComponent + offsets.m_Health);
  if (LocalPlayer.IsDead())
    return false;

  if (!LocalPlayer.InVehicule)
    {
      uintptr_t pClientWeaponComponent = *(uintptr_t*)(pLocalSoldier + offsets.m_soldierWeaponsComponent);
      if (IsValid(pClientWeaponComponent))
        {
          uintptr_t pWeaponHandle = *(uintptr_t*)(pClientWeaponComponent + offsets.m_handler);
          int ActiveSlot = *(int*)(pClientWeaponComponent + offsets.m_activeSlot);

          if (IsValid(pWeaponHandle))
            {
              uintptr_t pSoldierWeapon = *(uintptr_t*)(pWeaponHandle + ActiveSlot * 0x8);
              if (IsValid(pSoldierWeapon))
                {
                  auto currWeaponSlot = (WeaponSlot)(ActiveSlot);
                  uintptr_t pWeaponEntityData = *(uintptr_t*)(pSoldierWeapon + offsets.m_dataWeapon);
                  if (IsValid(pWeaponEntityData))
                    {
                      uintptr_t pWeaponName = *(uintptr_t*)(pWeaponEntityData + 0x0130);
                      if (IsValid(pWeaponName))
                        {
                          uintptr_t pCorrectedFiring = *(uintptr_t *) (pSoldierWeapon + offsets.m_pPrimary);
                          if (IsValid (pCorrectedFiring))
                            {
                              uintptr_t pPrimaryFire = *(uintptr_t *) (pCorrectedFiring + offsets.m_pPrimaryFire);
                              if (IsValid (pPrimaryFire))
                                {
                                  uintptr_t pShotConfigData = *(uintptr_t *) (pPrimaryFire + offsets.m_shotConfigData);
                                  if (IsValid (pShotConfigData))
                                    {
                                      uintptr_t pProjectileData = *(uintptr_t *) (pShotConfigData + offsets.m_pProjectileData);
                                      if (IsValid (pProjectileData) && !LocalPlayer.NoGravity)
                                        LocalPlayer.CurrentWeapon.BulletGravity = *(float*)(pProjectileData + offsets.m_Gravity);
                                    }
                                }

                              if ((int) currWeaponSlot >= 0 && (int) currWeaponSlot < 2)
                                {
                                  uintptr_t pSway = *(uintptr_t *) (pCorrectedFiring + offsets.m_pSway);
                                  if (IsValid (pSway))
                                    {
                                      uintptr_t pSwayData = *(uintptr_t *) (pSway + offsets.m_pSwayData);
                                      if (IsValid (pSwayData))
                                        {
                                          if(!LocalPlayer.Recoil)
                                            {
                                              LocalPlayer.CurrentWeapon.RecoilMultiplier = *(float*)(pSwayData + offsets.m_FirstShotRecoilMultiplier);
                                              LocalPlayer.CurrentWeapon.RecoilDecrease = *(float*)(pSwayData + offsets.m_ShootingRecoilDecreaseScale);
                                            }

                                          if (!LocalPlayer.Spread)
                                            {
                                              LocalPlayer.CurrentWeapon.DeviationZoom = *(float*)(pSwayData + offsets.m_DeviationScaleFactorZoom);
                                              LocalPlayer.CurrentWeapon.GameplayDevationZoom = *(float*)(pSwayData + offsets.m_GameplayDeviationScaleFactorZoom);
                                              LocalPlayer.CurrentWeapon.DevationNoZoom = *(float*)(pSwayData + offsets.m_DeviationScaleFactorNoZoom);
                                              LocalPlayer.CurrentWeapon.GameplayDeviationNoZoom = *(float*)(pSwayData + offsets.m_GameplayDeviationScaleFactorNoZoom);
                                            }
                                        }
                                    }
                                  char* WeaponName = (char*)(pWeaponName);
                                  if (strcmp(WeaponName, LocalPlayer.CurrentWeapon.Name) != 0)
                                    {
                                      LocalPlayer.CurrentWeapon.Name = (char*)(pWeaponName);
                                      LocalPlayer.NoGravity = false;
                                      LocalPlayer.Recoil = false;
                                      LocalPlayer.Spread = false;
                                    }

                                  if (LocalPlayer.CurrentWeapon.IsValid())
                                    {
                                      NoGravity();
                                      NoRecoil();
                                      NoSpread();
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
  return true;
}

bool Hack::IsValid (uintptr_t address)
{
  return (address >= 0x10000 && address < 0x000F000000000000);
}

uintptr_t Hack::GetClientSoldierEntity (uintptr_t pClientPlayer, Player player) const
{
  player.InVehicule = false;
  player.IsDriver = false;

  uintptr_t pAttached = *(uintptr_t*)(pClientPlayer + offsets.m_pAttachedControllable);
  if (IsValid(pAttached))
    {
      uintptr_t m_ClientSoldier = *(uintptr_t *)(*(uintptr_t*)(pClientPlayer + offsets.m_character)) - sizeof (uintptr_t);
      if (IsValid(m_ClientSoldier))
        {
          player.InVehicule = true;
          return m_ClientSoldier;
        }
    }
  return *(uintptr_t *)(pClientPlayer + offsets.m_pControlledControllable);
}

uintptr_t Hack::GetLocalSoldier ()
{
  uintptr_t pGContext = *(uintptr_t*)(offsets.OFFSET_CLIENTGAMECONTEXT);
  if (!IsValid(pGContext))
    return 0;

  uintptr_t pPlayerManager = *(uintptr_t*)(pGContext + offsets.m_pPlayerManager);
  if (!IsValid(pPlayerManager))
    return 0;

  uintptr_t pLocalPlayer = *(uintptr_t*)(pPlayerManager + offsets.m_pLocalPlayer);
  if (!IsValid(pLocalPlayer))
    return 0;

  uintptr_t pLocalSoldier = GetClientSoldierEntity(pLocalPlayer, LocalPlayer);
  if (IsValid(pLocalSoldier))
    return pLocalSoldier;
  else
    return 0;
}

uintptr_t Hack::GetSoldierWeapon ()
{
  uintptr_t pSoldierWeapon = 0;

  uintptr_t pLocalSoldier = GetLocalSoldier();
  if (!IsValid(pLocalSoldier))
    return pSoldierWeapon;

  uintptr_t pClientWeaponComponent = *(uintptr_t*)(pLocalSoldier + offsets.m_soldierWeaponsComponent);
  if (IsValid(pClientWeaponComponent))
    {
      uintptr_t pWeaponHandle = *(uintptr_t*)(pClientWeaponComponent + offsets.m_handler);
      int ActiveSlot = *(int*)(pClientWeaponComponent + offsets.m_activeSlot);
      if (IsValid(pWeaponHandle))
        pSoldierWeapon = *(uintptr_t*)(pWeaponHandle + ActiveSlot * 0x8);
    }
  return pSoldierWeapon;
}

bool Hack::NoGravity ()
{
  if (LocalPlayer.InVehicule || !LocalPlayer.CurrentWeapon.IsValid() || (int)LocalPlayer.CurrentWeapon.Slot >= 2 || LocalPlayer.IsDead())
    return false;

  uintptr_t pSoldierWeapon = GetSoldierWeapon();
  if (!IsValid(pSoldierWeapon))
    return false;

  uintptr_t pCorrectFiring = *(uintptr_t*)(pSoldierWeapon + offsets.m_pPrimary);
  if (!IsValid(pCorrectFiring))
    return false;

  uintptr_t pPrimaryFire = *(uintptr_t*)(pCorrectFiring + offsets.m_pPrimaryFire);
  if (!IsValid(pPrimaryFire))
    return false;

  uintptr_t pShotConfigData = *(uintptr_t*)(pPrimaryFire + offsets.m_shotConfigData);
  if (!IsValid(pShotConfigData))
    return false;

  uintptr_t pProjectileData = *(uintptr_t*)(pShotConfigData + offsets.m_pProjectileData);
  if (!IsValid(pProjectileData))
    return false;

  if (bGravity && !LocalPlayer.NoGravity)
    {
      *(float*)(pProjectileData + offsets.m_Gravity) = 0.0f;
      if (*(float*)(pProjectileData + offsets.m_Gravity) == 0.0f)
        {
          LocalPlayer.NoGravity = true;
          return true;
        }
    }
  else if(!bGravity && LocalPlayer.NoGravity)
    {
      *(float*)(pProjectileData + offsets.m_Gravity) = LocalPlayer.CurrentWeapon.BulletGravity;
      if (*(float*)(pProjectileData + offsets.m_Gravity) == LocalPlayer.CurrentWeapon.BulletGravity)
        {
          LocalPlayer.NoGravity = false;
          return true;
        }
    }
  return false;
}

bool Hack::NoRecoil ()
{
  if (LocalPlayer.InVehicule || !LocalPlayer.CurrentWeapon.IsValid() || (int)LocalPlayer.CurrentWeapon.Slot >= 2 || LocalPlayer.IsDead())
    return false;

  uintptr_t pSoldierWeapon = GetSoldierWeapon();
  if (!IsValid(pSoldierWeapon))
    return false;

  uintptr_t pCorrectedFiring = *(uintptr_t*)(pSoldierWeapon + offsets.m_pPrimary);
  if (!IsValid(pCorrectedFiring))
    return false;

  uintptr_t pSway = *(uintptr_t*)(pCorrectedFiring + offsets.m_pSway);
  if (!IsValid(pSway))
    return false;

  uintptr_t pSwayData = *(uintptr_t*)(pSway + offsets.m_pSwayData);
  if (!IsValid(pSwayData))
    return false;

  if (bRecoil && !LocalPlayer.Recoil)
    {
      *(float*)(pSwayData + offsets.m_FirstShotRecoilMultiplier) = 0.0f;
      *(float*)(pSwayData + offsets.m_ShootingRecoilDecreaseScale) = 100.0f;
      if (*(float*)(pSwayData + offsets.m_FirstShotRecoilMultiplier) == 0.0f && *(float*)(pSwayData + offsets.m_ShootingRecoilDecreaseScale) == 100.0f)
        {
          LocalPlayer.Recoil = true;
          return true;
        }
    }
  else if(!bRecoil && LocalPlayer.Recoil)
    {
      *(float*)(pSwayData + offsets.m_FirstShotRecoilMultiplier) = LocalPlayer.CurrentWeapon.RecoilMultiplier;
      *(float*)(pSwayData + offsets.m_ShootingRecoilDecreaseScale) = LocalPlayer.CurrentWeapon.RecoilDecrease;
      if (*(float*)(pSwayData + offsets.m_FirstShotRecoilMultiplier) == LocalPlayer.CurrentWeapon.RecoilMultiplier && *(float*)(pSwayData + offsets.m_ShootingRecoilDecreaseScale) == LocalPlayer.CurrentWeapon.RecoilDecrease)
        {
          LocalPlayer.Recoil = false;
          return true;
        }
    }
  return false;
}

bool Hack::NoSpread ()
{
  if (LocalPlayer.InVehicule || !LocalPlayer.CurrentWeapon.IsValid() || (int)LocalPlayer.CurrentWeapon.Slot >= 2 || LocalPlayer.IsDead())
    return false;

  uintptr_t pSoldierWeapon = GetSoldierWeapon();
  if (!IsValid(pSoldierWeapon))
    return false;

  uintptr_t pCorrectedFiring = *(uintptr_t*)(pSoldierWeapon + offsets.m_pPrimary);
  if (!IsValid(pCorrectedFiring))
    return false;

  uintptr_t pSway = *(uintptr_t*)(pCorrectedFiring + offsets.m_pSway);
  if (!IsValid(pSway))
    return false;

  uintptr_t pSwayData = *(uintptr_t*)(pSway + offsets.m_pSwayData);
  if (!IsValid(pSwayData))
    return false;

  if (bSpread && !LocalPlayer.Spread)
    {
      *(float*)(pSwayData + offsets.m_DeviationScaleFactorZoom) = 0.0f;
      *(float*)(pSwayData + offsets.m_GameplayDeviationScaleFactorZoom) = 0.0f;
      *(float*)(pSwayData + offsets.m_DeviationScaleFactorNoZoom) = 0.0f;
      *(float*)(pSwayData + offsets.m_GameplayDeviationScaleFactorNoZoom) = 0.0f;

      if (*(float*)(pSwayData + offsets.m_FirstShotRecoilMultiplier) == 0.0f && *(float*)(pSwayData + offsets.m_ShootingRecoilDecreaseScale) == 0.0f && *(float*)(pSwayData + offsets.m_GameplayDeviationScaleFactorNoZoom) == 0.0f && *(float*)(pSwayData + offsets.m_DeviationScaleFactorNoZoom) == 0.0f)
        {
          LocalPlayer.Spread = true;
          return true;
        }
    }
  else if(!bSpread && LocalPlayer.Spread)
    {
      *(float*)(pSwayData + offsets.m_DeviationScaleFactorZoom) = LocalPlayer.CurrentWeapon.DeviationZoom;
      *(float*)(pSwayData + offsets.m_GameplayDeviationScaleFactorZoom) = LocalPlayer.CurrentWeapon.GameplayDevationZoom;
      *(float*)(pSwayData + offsets.m_DeviationScaleFactorNoZoom) = LocalPlayer.CurrentWeapon.DevationNoZoom;
      *(float*)(pSwayData + offsets.m_GameplayDeviationScaleFactorNoZoom) = LocalPlayer.CurrentWeapon.GameplayDeviationNoZoom;

      if (*(float*)(pSwayData + offsets.m_DeviationScaleFactorZoom) == LocalPlayer.CurrentWeapon.DeviationZoom && *(float*)(pSwayData + offsets.m_GameplayDeviationScaleFactorZoom) == LocalPlayer.CurrentWeapon.GameplayDevationZoom && *(float*)(pSwayData + offsets.m_DeviationScaleFactorNoZoom) == LocalPlayer.CurrentWeapon.DevationNoZoom && *(float*)(pSwayData + offsets.m_GameplayDeviationScaleFactorNoZoom) == LocalPlayer.CurrentWeapon.GameplayDeviationNoZoom)
        {
          LocalPlayer.Spread = false;
          return true;
        }
    }
  return false;
}
Hack::Hack ()
{
  LocalPlayer.CurrentWeapon.Name = "";
  this->bGravity = true;
  this->bRecoil = true;
  this->bSpread = true;
}

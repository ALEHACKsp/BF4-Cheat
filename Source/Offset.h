#ifndef _OFFSET_H_
#define _OFFSET_H_

#include <windows.h>

struct Offsets {

    /*
     * Game State
     */

    uintptr_t OFFSET_DXRENDERER = 0x142738080; //0x142572fa0;
    uintptr_t OFFSET_CLIENTGAMECONTEXT = 0x142670d80; //0x1424abd20;
    uintptr_t OFFSET_GAMERENDERER = 0x142672378; //0x1424ad330;
    uintptr_t OFFSET_ANGLES = 0x1423b2ec0; //0x1421caee0;
    uintptr_t OFFSET_CURRENT_WEAPONFIRING = OFFSET_ANGLES + 0x8;
    uintptr_t OFFSET_SETTINGS = 0x1423717C0; //0x1421AC5A0;
    uintptr_t OFFSET_SHOTSTATS = 0x142737A40; //0x142572950;

    /*
     *  Weapon Firing
     */

    DWORD m_pSway = 0x0078;                  // WeaponSway
    DWORD m_pPrimaryFire = 0x0128;           // PrimaryFire
    DWORD m_pWeaponModifier = 0x01F0;        // WeaponModifier
    DWORD m_pFiringHolderData = 0x01C8;      // FireLogicData
    DWORD m_projectilesLoaded = 0x01A0;      // INT32
    DWORD m_projectilesInMagazines = 0x01A4; // INT32
    DWORD m_overheatPenaltyTimer = 0x01B0;   // FLOAT


    DWORD m_RecoilTimer = 0x0168; //float RecoilTimer; //0x0168
    DWORD m_recoilAngleX = 0x016c;//float RecoilAngleX; //0x016C
    DWORD m_RecoilAngleY = 0x0170;//float RecoilAngleY; //0x0170
    DWORD m_RecoilAngleZ = 0x0174;//float RecoilAngleZ; //0x0174
    DWORD m_RecoilFOVAngle = 0x0178;//float RecoilFOVAngle; //0x0178
    DWORD m_recoilTimeMultiplier = 0x017c;//float RecoilTimeMultiplier; //0x017C
    DWORD m_shotConfigData = 0x0010;

    /*
     *  Weapon Sway
     */

    DWORD m_pSwayData = 0x0008;      // GunSwayData
    DWORD m_deviationPitch = 0x0130; // FLOAT
    DWORD m_deviationYaw = 0x0134;   // FLOAT

    DWORD m_devRoll = 0x0138;        //float //new
    DWORD m_devTransY = 0x013C;      //float

    DWORD m_CurDispersionPitch = 0x01AC;
    DWORD m_CurDispersionYaw = 0x01B0;
    DWORD m_CurDispersionRoll = 0x01B4;
    DWORD m_CurDispersionTransY = 0x01B8;
    DWORD m_RipOfRecoil = 0x0208;

    /*
     * Bullet Entity Data
     */

    DWORD m_Gravity = 0x0130;     // FLOAT
    DWORD m_StartDamage = 0x0154; // FLOAT
    DWORD m_EndDamage = 0x0158;   // FLOAT

    /*
     * Gun Sway Data
     */

    DWORD m_DeviationScaleFactorZoom = 0x0430;           // FLOAT
    DWORD m_GameplayDeviationScaleFactorZoom = 0x0434;   // FLOAT
    DWORD m_DeviationScaleFactorNoZoom = 0x438;         // FLOAT
    DWORD m_GameplayDeviationScaleFactorNoZoom = 0x043c; // FLOAT

    DWORD m_ShootingRecoilDecreaseScale = 0x0440; // FLOAT
    DWORD m_FirstShotRecoilMultiplier = 0x0444;   // FLOAT

    /*
     * Shot Config Data
     */

    DWORD m_pProjectileData = 0x00B0;   // BulletEntityData
    DWORD m_FireLogic = 0x01C8;         // FireLogicData
    DWORD m_PositionOffset = 0x0060;    // VECTOR3
    DWORD m_initialSpeed = 0x0080;      // VECTOR3
    DWORD m_Speed = 0x0088;             // FLOAT
    DWORD m_numberOfBulletsPerShell = 0x00D4;   // INT
    DWORD m_numberOfBulletsPerShot = 0x00D8;    // INT
    DWORD m_numberOfBulletsPerBurst = 0x00DC;   // INT

    /*
     *  Client Soldier Weapon
     */

    DWORD m_dataWeapon = 0x0030;              // WeaponEntityData
    DWORD m_authorativeAiming = 0x4988; // ClientSoldierAimingSimulation
    DWORD m_pWeapon = 0x49A8;           // ClientWeapon
    DWORD m_pPrimary = 0x49C0;          // WeaponFiring

    /*
     * Client Soldier Weapons Component
     */


    DWORD m_handler = 0x0890;      // m_handler + m_activeSlot * 0x8 = ClientSoldierWeapon
    DWORD m_activeSlot = 0x0A98;   // INT32 (WeaponSlot)
    DWORD m_activeHandler = 0x08D0; // ClientActiveWeaponHandler
    DWORD m_zeroingDistanceLevel = 0x0AC8; // INT32

    // VehicleEntityData
    DWORD m_pPlayer = 0x01E0;          // ClientPlayer
    DWORD m_pHealthComponent = 0x0140; // HealthComponent
    DWORD m_authorativeYaw = 0x04D8;   // FLOAT
    DWORD m_authorativePitch = 0x04DC; // FLOAT
    DWORD m_poseType = 0x04F0;         // INT32
    DWORD m_RenderFlags = 0x04F4;      // INT32
    DWORD m_pPhysicsEntity = 0x0238;   // VehicleDynamicPhysicsEntity
    DWORD m_pPredictedController = 0x0490;    // ClientSoldierPrediction
    DWORD m_soldierWeaponsComponent = 0x0570; // ClientSoldierWeaponsComponent
    DWORD m_ragdollComponent = 0x0580;        // ClientRagDollComponent
    DWORD m_breathControlHandler = 0x0588;    // BreathControlHandler
    DWORD m_sprinting = 0x5B0;  // BYTE
    DWORD m_occluded = 0x05B1;  // BYTE
    DWORD m_pVaultComp = 0x0D30; // VaultComponent
    DWORD m_pSpottingTargetComponentData = 0x0BF0; //SpottingTargetComponentData

    /*
     * Client Game Context
     */

    DWORD m_pPhysicsManager = 0x28; // HavokPhysicsManager
    DWORD m_pPlayerManager = 0x60;  // ClientPlayerManager

    /*
     * Client Player Manager
     */

    DWORD m_pLocalPlayer = 0x540; // ClientPlayer
    DWORD m_ppPlayer = 0x548;     // ClientPlayer

    /*
     * Health Componment
     */

    DWORD m_Health = 0x0020;        // FLOAT
    DWORD m_MaxHealth = 0x0024;     // FLOAT
    DWORD m_vehicleHealth = 0x0038; // FLOAT (pLocalSoldier + 0x1E0 + 0x14C0 + 0x140 + 0x38)

    /*
     * ClientPlayer
     */

    DWORD szName = 0x40;            // 10 CHARS
    DWORD m_isSpectator = 0x13C9;   // BYTE
    DWORD m_teamId = 0x13CC;        // INT32
    DWORD m_character = 0x14B0;     // ClientSoldierEntity
    DWORD m_ownPlayerView = 0x1510; // ClientPlayerView
    DWORD m_PlayerView = 0x1520;    // ClientPlayerView
    DWORD m_pAttachedControllable = 0x14C0;   // ClientSoldierEntity (ClientVehicleEntity)
    DWORD m_pControlledControllable = 0x14D0; // ClientSoldierEntity
    DWORD m_attachedEntryId = 0x14C8; // INT32
};

#endif //_OFFSET_H_
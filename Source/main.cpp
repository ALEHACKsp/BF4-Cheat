#include <Windows.h>
#include "Hack.h"

void HackThread()
{
  Hack Cheat;
  AllocConsole();
  FILE* f;
  freopen_s(&f, "CONOUT$", "w", stdout);

  while(true)
    {
      if (GetAsyncKeyState(VK_DELETE) & 1)
        break;

      if (GetAsyncKeyState(VK_F1) & 1)
        Cheat.bGravity = !Cheat.bGravity;

      if (GetAsyncKeyState(VK_F2) & 1)
        Cheat.bRecoil = !Cheat.bRecoil;

      if (GetAsyncKeyState(VK_F3) & 1)
        Cheat.bSpread = !Cheat.bSpread;

      Cheat.CheatRoutine();
      Sleep(1000);
    }

  fclose(f);
  FreeConsole();
}

BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD  ul_reason_for_call,
                      LPVOID lpReserved
)
{
  switch (ul_reason_for_call)
    {
      case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr));
      case DLL_THREAD_ATTACH:
      case DLL_THREAD_DETACH:
      case DLL_PROCESS_DETACH:
        break;
    }
  return TRUE;
}
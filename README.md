# LockScreenTweaker
This tool allows you to customize your lock screen
### Written in [C](https://en.wikipedia.org/wiki/C_(programming_language))
### GUI written in [WinAPI](https://en.wikipedia.org/wiki/Windows_API)
### Using [SB_registry.h](https://github.com/Svyatik-Bak/SB_registry.h)

![2022-10-28-13-43-38-999](https://user-images.githubusercontent.com/89962566/198569193-798d6f58-db44-4636-85fc-3bb219086af4.jpg)

# How to customize with cmd.exe
Disable Lock Screen: ```reg add HKLM\SOFTWARE\Policies\Microsoft\Windows\Personalization /v NoLockScreen /t REG_DWORD /d 1 /f```

Enable Lock Screen: ```reg add HKLM\SOFTWARE\Policies\Microsoft\Windows\Personalization /v NoLockScreen /t REG_DWORD /d 0 /f```

Disable blur: ```reg add HKLM\SOFTWARE\Policies\Microsoft\Windows\System /v DisableAcrylicBackgroundOnLogon /t REG_DWORD /d 1 /f```

Enable blur: ```reg add HKLM\SOFTWARE\Policies\Microsoft\Windows\System /v DisableAcrylicBackgroundOnLogon /t REG_DWORD /d 0 /f```

# Compiling
```gcc -o LockScreenTweaker.exe LockScreenTweaker.c res.o -lgdi32```


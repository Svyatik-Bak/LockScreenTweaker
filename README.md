# LockScreenTweaker
This tool allows you to customize your lock screen

![Screenshot_2022-08-35-22-20-20-25-574](https://user-images.githubusercontent.com/89962566/185991386-1f0fa8fe-2703-4740-a0bb-742e7dab52b1.png)
![Screenshot_2022-08-35-22-20-20-44-547](https://user-images.githubusercontent.com/89962566/185991435-922fdb1f-dff5-4ae6-bb4c-fc2b84cff5d9.png)

# How to customize with cmd.exe
Disable Lock Screen: ```reg add HKLM\SOFTWARE\Policies\Microsoft\Windows\Personalization /v NoLockScreen /t REG_DWORD /d 1 /f```

Enable Lock Screen: ```reg add HKLM\SOFTWARE\Policies\Microsoft\Windows\Personalization /v NoLockScreen /t REG_DWORD /d 0 /f```

Disable blur: ```reg add HKLM\SOFTWARE\Policies\Microsoft\Windows\System /v DisableAcrylicBackgroundOnLogon /t REG_DWORD /d 1 /f```

Enable blur: ```reg add HKLM\SOFTWARE\Policies\Microsoft\Windows\System /v DisableAcrylicBackgroundOnLogon /t REG_DWORD /d 0 /f```

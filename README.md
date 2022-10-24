# AmongUsMenu [![Discord](https://img.shields.io/badge/Discord-Invite-7289DA.svg?logo=Discord&style=flat-square)](https://discord.gg/AUpXd3VUh8) [![Paypal](https://img.shields.io/badge/PayPal-Donate-Green.svg?logo=Paypal&style=flat-square)](https://www.paypal.com/donate/?hosted_button_id=TYMU92FD9D9UW)

<p align="center">
   AmongUsMenu is a Cheat Menu for the popular Game Among Us.
</p>

## 中文支持 :)
如果你想使用中文版AUM可以前往链接https://github.com/CryptEvc/AmongUsMenuChinese
与原版同步更新 减少您阅读障碍的烦恼 

## Disclaimer
This project is for Educational Use only. We do not condone this software being used to gain an advantage against other people. I made this project for my university project to show how cheating software works and how it is possible to block these manipulations in the future.

## Compile (Configurations)
You can compile two different versions of the menu. Normal or Version Proxy.

### Normal (AmongUsMenu.dll)
Inject it with any injector you have.

- Debug (With Debug Information and can be attached to process)
- Release (Optimized with all information stripped)

### Version Proxy (version.dll)
Will automatically be loaded by the Game itself if the dll is in the game directory.

- Debug_Version (With Debug Information and can be attached to process)
- Release_Version (Optimized with all information stripped)

### Default Hotkeys
- Show Menu - DELETE
- Show Radar - INSERT
- Show Console - HOME
- Show Replay - END
- Repair Sabotage - PAGE DOWN (PgDn)

## Screenshot
<p align="center">
   <img src="screenshot.png">
</p>

## Special Thanks
* [KulaGGin](https://github.com/KulaGGin) (Helped with some ImGui code for replay system)
* [tomsa000](https://github.com/tomsa000) (Helped with fixing memory leaks and smart pointers)
* Everyone else who contributed to the code and I couldn't list here. Thank you!

## Contributing

1. Fork it (<https://github.com/BitCrackers/AmongUsMenu/fork>)
2. Create your feature branch (`git checkout -b feature/fooBar`)
3. Commit your changes (`git commit -am 'Add some fooBar'`)
4. Push to the branch (`git push origin feature/fooBar`)
5. Create a new Pull Request

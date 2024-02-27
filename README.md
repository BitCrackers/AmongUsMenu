### The menu has moved to a brand new [repository](https://github.com/g0aty/SickoMenu) for better issue support and visibility! This repository will now only be used for committing new stuff to AUM.

## Version 2.2.3: Prepare for SickoMenu v3.0!!!
SickoModeAU will be moving to a new repository by the end of February for better issue support and more!

# Original AmongUsMenu (BitCrackers) [![Discord](https://img.shields.io/badge/Discord-Invite-7289DA.svg?logo=Discord&style=flat-square)](https://discord.gg/AUpXd3VUh8) [![Paypal](https://img.shields.io/badge/PayPal-Donate-Green.svg?logo=Paypal&style=flat-square)](https://www.paypal.com/donate/?hosted_button_id=TYMU92FD9D9UW)
## Note: I am not associated with/part of the BitCrackers team, these links are for BitCrackers only. Please don't harass the BitCrackers team regarding this fork.
<p align="center">
   SickoModeAU is a Cheat Menu forked from AmongUsMenu for the popular Game Among Us.
</p>

## Disclaimer
This project is for Educational Use only. We do not condone this software being used to gain an advantage against other people. This project is aimed to make Innersloth's anticheat better.
Use at your own risk. If you get banned from playing entirely or from a lobby, I (g0aty) am not responsible.

## Compile (Configurations)
You can compile two different versions of the menu. Normal or Version Proxy. Steps to compile can be found here: https://docs.google.com/document/d/16Tnqk7LIqyQlw74TuV34Wsy9JDqIfVy7DgUndwIL3uw/edit?usp=sharing

### Normal (SickoModeAU.dll)
Inject it with any injector you have.

- Debug (With Debug Information and can be attached to process)
- Release (Optimized with all information stripped)

### Version Proxy (version.dll)
Will automatically be loaded by the Game itself if the dll is in the game directory.

- Debug_Version (With Debug Information and can be attached to process)
- Release_Version (Optimized with all information stripped)

### Running on Proton (Version Proxy Only)
First you will need protontricks, you can install it with your packager of choice.

1. Make sure you are running Among Us under Proton  
   You can check by going to **Properties -> Compatibility**
3. Put version.dll into Among Us folder
4. Run `protontricks --gui`
5. Choose **Among Us**
6. Click on **Select the default wineprefix** and then **OK**
7. Click on **Run winecfg** and then **OK**
8. In the configuration window, click on **Libraries**
9. Type `version` into the **New override for library** input
10. Click **Add** and then **Apply**
11. SickoModeAU should now work properly in the game

### Default Hotkeys
- Show Menu - DELETE
- Show Radar - INSERT
- Show Console - HOME
- Show Replay - END
- Repair Sabotage - PAGE DOWN (PgDn)
- Panic / Disable SMAU - PAUSE BREAK (Break)

## Screenshot
<p align="center">
   <img src="screenshot.png">
</p>

## Special Thanks
* The BitCrackers team for creating a great mod, which was easy to add features to
* [KulaGGin](https://github.com/KulaGGin) (Helped with some ImGui code for replay system)
* [tomsa000](https://github.com/tomsa000) (Helped with fixing memory leaks and smart pointers)
* [cddjr](https://github.com/cddjr) (Helped in updating to the Fungle map, saved a lot of my time)
* Everyone else who contributed to the code and I couldn't list here. Thank you!

## Contributing (AUM, not here)

1. Fork it (<https://github.com/BitCrackers/AmongUsMenu/fork>)
2. Create your feature branch (`git checkout -b feature/fooBar`)
3. Commit your changes (`git commit -am 'Add some fooBar'`)
4. Push to the branch (`git push origin feature/fooBar`)
5. Create a new Pull Request

## Added/Changed Features
Settings Tab:
1. Hide Keybinds (so u don't accidentally change any keybind when opening menu)
2. Menu Size (More control over size)
3. Colored / RGB menu theme (more customization - also applies to radar/replay)
4. Menu Transparency (makes the menu see-through)
5. Automatically set name / Set name button (more control over ign)
6. Custom Streamer Mode lobby code (changes ****** to custom text - defaults to GOATYY)
7. Spoofers (changes level, friendcode, product user id)
8. Cosmetic Unlocker (added toggle for when u wanna unlock stuff legit)
9. Safe Mode (when toggled off, adds more features that were originally detected by anticheat - meant to be used in servers w/ no anticheat)
10. Hide Friend Code (so no one catches you with the same friend code)

Game Tab:
1. No Ability Cooldown (removes cooldown for venting/vitals/killing/shapeshifting (in certain cases)/protecting)
2. Speed Multiplier (self-explanatory)
3. Kill Distance Modifier (self-explanatory)
4. Fortegreen in the list of available colors (accessible w/ host)
5. Color Sniper (when a player with ur color leaves, change to that color immediately)
6. Chat message sending (add newlines and stuff, spam)
7. Cycler (change ur cosmetics/name randomly)
8. Confuser (randomize appearance at will to avoid being detected)
9. Spam Report (keeps on reporting dead bodies even while in a meeting)
10. Added hide and seek game options
11. Added cycle between players (impersonates random players on a fixed timer)

Self Tab:
1. Disable HUD (self-explanatory)
2. Freecam/Zoom (now works in the lobby, change speed with scroll wheel, and zoom with ctrl-scroll)
3. Custom Name (adds a custom client-sided (server sided option when hosting) name with color and formatting)
4. Show Player Info in Lobby (shows player level, friendcode)
5. Player Colored Names (self-explanatory)
6. Move in Vent (added moving while shapeshifting)
7. Always Move (move while chatting, meeting, etc.)
8. Kill Other Impostors (self-explanatory)
9. Right Click TP (changed so u have to hold shift)
10. Teleport/Rotate everyone (only when not in safe mode)
11. Coordinate-based Teleport (input x and y coordinates)
12. Move in Meeting (self-explanatory)
13. Fake Role (adds a client-sided role such as impostor)
14. Kill Through Walls (self-explanatory)
15. Infinite Kill Range (allows "infinite" kill distance)
16. Do Tasks as Impostor (self-explanatory)
17. Show Vote Kicks (shows if anyone votekicked you below ping)

Radar Tab / Radar:
1. Changed the crewmate icon
2. Added a border toggle to the radar
3. Changed visor color to the actual visor color
4. Added role display on visor
5. Changed role-based to selectively show crew/imp

Replay Tab:
None

ESP Tab:
1. ESP now works in lobby

Players Tab:
1. Show Extra Info (player id, friendcode, level, user id)
2. Allows calling a meeting while already in a meeting
3. Force call a meeting by another player (host-only)
4. Allows killing even with non killer role (sometimes doesn't work due to limitations)
5. Murder Loop (kills the player 20 times, useful when the person keeps annoying you)
6. Suicide / Suicide Loop (makes the player unalive themselves (in the game ofc))
7. Kill All Crewmates/Impostors (self-explanatory)
8. Vote Controls (host-only)
9. Kick/Ban (host-only)
10. Shapeshift into selected player (self-explanatory, also adds an option to shapeshift everyone to player when not in safe mode)
Note: The cooldown is not set, meaning you will get kicked for shifting during the cooldown
11. Protect selected player (self-explanatory)
12. Teleport player to you (self-explanatory)
13. Attach to player (constantly teleports you to a player)
14. Set roles for player (doesn't work after game starts)
15. Revive player (self-explanatory)
16. Set Scanner (only when not in safe mode)
17. Force name/color (host-only)
18. Chat spoofing (only when not in safe mode)
19. Cosmetics Stealer (allows stealing individual cosmetics from player)

Tasks Tab:
1. Keybind for complete all tasks
2. Complete Everyone's Tasks (only when not in safe mode)
3. Complete Tasks even as Impostor (doesn't do anything other than show u have completed tasks to urself and other cheaters)
4. Warning when visual tasks are turned off
5. Changed weapons button to a checkbox (constantly plays weapons animation when toggled)
6. % tasks completed by all crewmates

Sabotage Tab:
1. Map specific names for reactor sabotage

Doors Tab:
None

Debug Tab:
1. Clear RPC Queues (when too many packets are in queue to send to server)

Host Tab:
1. Disable Game Ending
2. End Game (host only, select a reason and end the game at ur own will)
3. Force name/color for everyone
4. Disable Meetings/Sabotages
5. Revive Yourself
6. Custom Impostor Count (forces the number of impostors to be the value you set)

Miscellaneous:
1. Allow all unblocked characters in chat and extend char limit (in special cases)
2. Kill packets changed from CmdCheckMurder to RpcMurderPlayer (allows killing in certain cases)
3. Added mod version and shows when freecam/noclip is turned on
4. Disable freecam moving when chat text is focused
5. Check for invalid names detected by anticheat

## Removed Features
1. Removed custom RPC and AUM chat (prevents detection by other mod users)
2. Removed changing taskbar updates (doesn't work client-side)

## Notes
1. If you get crashes, make sure you upload your "smau-log.txt" (in your Among Us directory) and mark the issue on the repo.
2. If your game crashes when joining a lobby, host a local lobby then join that lobby.

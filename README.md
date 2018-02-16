# mage-battle-royale
Mage Battle Royale game playable on the desktop or browser. Built in C. Watch development at twitch.tv/peteycodes

## Build Notes
- Install SDL2 and SDL2_image using homebrew on MacOS. This will put the header files in /usr/local/include and the library files in /usr/local/lib. Both are referenced in the Makefile. If you have your SDL2 libs in a different place, you will need to modify the variables in the Makefile accordingly.

  - brew install sdl2
  - brew install sdl2_image


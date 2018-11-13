# Deep Face
This is an interface for your AI. Inspired by A Space Odyssey's HAL 9000
and the Eye of Sauron (LOTR), the eye of the AI is made out of tiny
particles swarming around the pupil and contours. They will react to sound,
touch, and other events, and will resemble emotions from the AI and
surrounding system Deep Face is integrated in.

Features include:

- Eye simulation based on thousands of particles
- Runs on a Raspberry Pi (3 B+) or other ARM boards or computers
- Reacts to touch (& mouse)
- Reacts to sound
- (TODO) API to control entropy (excitement) and colour (currently keyboard shortcuts)


## Hardware
This repository is tested on:
1. Ubuntu 18.04 on x64
2. Raspberry Pi 3 B+ with Raspbian 9, and
   - USB microphone
   - HDMI Touchscreen (5 inch)


## Installation
- Install OpenFrameworks into ~/software/openframeworks/;
  - To get rid of Poco compile errors, I had to recompile Poco with apothecary (an OFX specific build system):
  ```
  git clone https://github.com/openframeworks/apothecary.git && cd apothecary
  ./apothecary/apothecary update poco
  cp poco/ $OF_ROOT/addons/ofxPoco/libs/ -r
  ```

- Set $OF_ROOT to ~/software/openframeworks (add to .profile / .bashrc / .zshrc)

- Install addons: `./install_dependencies.sh`, or manually to `$OF_ROOT/addons`:
    - Install [ofxRPiTouch](https://github.com/turiphro/ofxRPiTouch)
    - Install [ofxMQTT](https://github.com/256dpi/ofxMQTT.git)

- `make && make RunRelease`

### Additional installation for raspberry pi
- Configure touchscreen: [[https://www.raspberrypi.org/forums/viewtopic.php?t=143581]]

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
- Install OpenFrameworks into ~/software/openframeworks/
- Set $OF_ROOT to ~/software/openframeworks (add to .profile / .bashrc / .zshrc)
- Configure touchscreen: [[https://www.raspberrypi.org/forums/viewtopic.php?t=143581]]
- Install [https://github.com/apparentVJ/ofxRPiTouch](ofxRPiTouch)



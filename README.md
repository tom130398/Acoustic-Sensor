# This is my readme file by Hoang Nguyen (e1601111)
Raspberry Pi  acoustic sensor project

This project will turn a raspberry Pi 3  into  an acoustic sensor

1.Configuration

1.1 Hardware configuration

A raspberry Pi 3 is recommended: If a older version of Pi is used, corresponding configuration might be changed.
The Pi is mounted with a USB sound card, and plugged in a microphone.
It is recommended to have Ethernet connection for your Pi.

1.2 Software configurations

The USB sound card has to be set as default audio device. To do so, you neeed to modify 2 files with following contents
 - Boot up RPi and apply the USB sound card.
 - RPi onboard sound card doesn't have microphone interface. We have to change the default audio device to be USB sound card.
 - Use "lusb" command to check if your USB sound card is mounted.
 - Use "sudo nano /etc/asound.conf" command and put following content to the file:
        pcm.!default {
                type plug
                slave {
                        pcm "hw:1,0"
                }
        }
        ctl.!default {
                type hw
                card 1
        }
 - Go to home directory. Use "nano .asoundrc" command and put the same content to file.
 - Run "alsamixer" you should be able to see that USB sound card is default audio device.

Next, you need to fix the bug of arecord. The newest version of Raspbian comes with a new version of alsa-utils (1.0.28), which has a bug while recording: it doesn't stop even a '-duration' switch is given, and generates lots of
useless audio files. To fix this problem, we have to downgrade alsa-util to an earlier version (1.0.25).
 - Use "sudo nano /etc/apt/sources.list" command and add : "deb http://mirrordirector.raspbian.org/raspbian/ wheezy main contrib non-free rpi".
 - Run "sudo apt-get update".
 - Run "sudo aptitude versions alsa-utils" to check if version 1.0.25 of alsa-util is availble.
 - Run "sudo apt-get install alsa-utils=1.0.25-4" to downgrade.
 - Reboot (if necessary).
 - Run “arecord -r44100 -c1 -f S16_LE -d5 test.wav” to test that your microphone is working. You should see a “test.wav” file in the current folder.
 - Put earphone on. Run “aplay test.wav” to check that your recording is okay.

2.Operating Instructions

 - Run "make" to make file.
 - Run "./sound.a" and start recording your sound.
 - Go to "http://www.cc.puv.fi/~e1601111/php/sound_log.txt" to see the data.

3.List of included files

The project contains following files:
 - README.md.
 - makefile: the makefile to run this project.
 - wave.c: the module contains funtions to display the waveform of the sound that you recorded.
 - wave.h: header file of wave.c
 - screen.c: the module contains functions about screen manupulation.
 - screen.h: header file of screen.c
 - comm.c: the communication module using libcurl.
 - comm.h: header file of comm.c
 - main.c: contains main() function.
 - sound.php: the server page to receive data.

4.Contact information

Hoang Nguyen -- Telephone Number:0469458419 -- Email:ngtuanhoang02@gmail.com

5.Credits and acknowledgment:

This project uses Raspberry Pi 3.


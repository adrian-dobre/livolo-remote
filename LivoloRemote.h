/**
 * @file LivoloRemote.h
 * @author Adrian Dobre (adi.dobre90@gmail.com)
 * @brief Livolo Remote Library (TX only) for Livolo RF switches.
 * Thanks kranjec.primoz@gmail.com for the research done on his blog
 * https://neofoxx.com/post-4.html, kind3r@gmail.com for the keycodes
 * (https://github.com/kind3r/livolo-rf-codes), Sergey Chernov for the initial
 * Livolo lib
 * (https://forum.arduino.cc/t/control-livolo-switches-livolo-switch-library/149850)
 * and to all the people that gathered various info here
 * https://community.home-assistant.io/t/broadlink-rm-pro-livolo-switches-rf-learning-woes/12432
 * and here
 * https://forum.arduino.cc/t/control-livolo-switches-livolo-switch-library/149850
 * @version 0.1
 * @date 2022-12-09
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef LivoloRemote_h
#define LivoloRemote_h

#include "Arduino.h"

class LivoloRemote {
   public:
    LivoloRemote(byte pin);
    void send(unsigned short int remoteId, byte keyCode, byte = 150);

   private:
    byte pin;
    byte outputBit = HIGH;
    unsigned short int shortPulse = 162;
    unsigned short int preamblePulse = 530;
    unsigned short int longPulse = 320;
    byte bitStream[60];
    unsigned short int pulses[60];
    byte bitStreamLength = 0;
    void encode(byte bit, bool preamble = false);
    void appendToStream(byte bit, unsigned short int pulseLength);
    void transmit();
    void toggleOutput();
};

namespace LivoloRemoteKey {
const byte BUTTON_1 = 0;
const byte BUTTON_2 = 96;
const byte BUTTON_3 = 120;
const byte BUTTON_4 = 24;
const byte BUTTON_5 = 108;
const byte BUTTON_6 = 80;
const byte BUTTON_7 = 48;
const byte BUTTON_8 = 12;
const byte BUTTON_9 = 72;
const byte BUTTON_10 = 40;
const byte SCENE_1 = 90;
const byte SCENE_2 = 114;
const byte SCENE_3 = 10;
const byte SCENE_4 = 18;
const byte ALL_OFF = 106;
const byte DIMMER_TOGGLE = 8;
const byte DIMMER_UP = 16;
const byte DIMMER_DOWN = 56;
}  // namespace LivoloRemoteKey

#endif
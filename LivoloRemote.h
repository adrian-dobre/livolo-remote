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
    LivoloRemote(unsigned int pin);
    void send(unsigned int remoteId, unsigned int keyCode,
              unsigned int repeats = 200);

   private:
    unsigned int pin;
    unsigned int output = HIGH;
    unsigned int shortLength = 162;
    unsigned int preambleLength = 530;
    unsigned int longLength = 320;
    unsigned int encodedSequence[100];
    unsigned int encodedSequenceLength = 0;
    void encode(unsigned int bit, bool preamble = false);
    void appendToSequence(unsigned int bit, unsigned int pulseLength);
    void transmit();
    void toggleOutput();
};

namespace LivoloRemoteKey {
const int BUTTON_1 = 0;
const int BUTTON_2 = 96;
const int BUTTON_3 = 120;
const int BUTTON_4 = 24;
const int BUTTON_5 = 108;
const int BUTTON_6 = 80;
const int BUTTON_7 = 48;
const int BUTTON_8 = 12;
const int BUTTON_9 = 72;
const int BUTTON_10 = 40;
const int SCENE_1 = 90;
const int SCENE_2 = 114;
const int SCENE_3 = 10;
const int SCENE_4 = 18;
const int ALL_OFF = 106;
const int DIMMER_TOGGLE = 8;
const int DIMMER_UP = 16;
const int DIMMER_DOWN = 56;
}  // namespace LivoloRemoteKey

#endif
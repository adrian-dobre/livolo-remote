
#include "LivoloRemote.h"

LivoloRemote::LivoloRemote(byte pin) {
    pinMode(pin, OUTPUT);
    LivoloRemote::pin = pin;
}

void LivoloRemote::send(unsigned short int remoteId, byte keyCode,
                        byte repeats) {
    LivoloRemote::bitStreamLength = 0;
    LivoloRemote::outputBit = HIGH;
    LivoloRemote::encode(1, true);

    for (byte i = 16; i > 0; i--) {
        LivoloRemote::encode(bitRead(remoteId, i - 1));
    }

    for (byte i = 7; i > 0; i--) {
        LivoloRemote::encode(bitRead(keyCode, i - 1));
    }

    for (byte i = 0; i <= repeats; i++) {
        LivoloRemote::transmit();
    }
}
void LivoloRemote::toggleOutput() {
    if (LivoloRemote::outputBit == HIGH) {
        LivoloRemote::outputBit = LOW;
    } else {
        LivoloRemote::outputBit = HIGH;
    }
}

void LivoloRemote::encode(byte bit, bool preamble) {
    int pulseLength = shortPulse;
    int repeats = 0;
    if (preamble) {
        pulseLength = preamblePulse;
    } else if (bit == 1) {
        pulseLength = longPulse;
    } else {
        repeats = 1;
    }
    for (byte i = 0; i <= repeats; i++) {
        LivoloRemote::appendToStream(LivoloRemote::outputBit, pulseLength);
        LivoloRemote::toggleOutput();
    }
}

void LivoloRemote::appendToStream(byte bit, unsigned short int pulseLength) {
    LivoloRemote::bitStream[LivoloRemote::bitStreamLength] = bit;
    LivoloRemote::pulses[LivoloRemote::bitStreamLength] = pulseLength;
    LivoloRemote::bitStreamLength++;
}

void LivoloRemote::transmit() {
    byte outputBit = HIGH;
    for (byte i = 0; i < LivoloRemote::bitStreamLength; i++) {
        outputBit = LivoloRemote::bitStream[i];
        digitalWrite(LivoloRemote::pin, outputBit);
        delayMicroseconds(LivoloRemote::pulses[i]);
    }
    if (outputBit == HIGH) {
        digitalWrite(LivoloRemote::pin, LOW);
    }
}
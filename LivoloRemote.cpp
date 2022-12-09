
#include "LivoloRemote.h"

LivoloRemote::LivoloRemote(unsigned int pin) {
    pinMode(pin, OUTPUT);
    LivoloRemote::pin = pin;
}

void LivoloRemote::send(unsigned int remoteId, unsigned int keyCode,
                        unsigned int repeats) {
    LivoloRemote::encodedSequenceLength = 0;
    LivoloRemote::output = HIGH;
    LivoloRemote::encode(1, true);

    for (int i = 15; i >= 0; i--) {
        LivoloRemote::encode(bitRead(remoteId, i));
    }

    for (int i = 6; i >= 0; i--) {
        LivoloRemote::encode(bitRead(keyCode, i));
    }

    for (int i = 0; i <= repeats; i++) {
        LivoloRemote::transmit();
    }
}
void LivoloRemote::toggleOutput() {
    if (LivoloRemote::output == HIGH) {
        LivoloRemote::output = LOW;
    } else {
        LivoloRemote::output = HIGH;
    }
}

void LivoloRemote::encode(unsigned int bit, bool preamble) {
    int pulseLength = shortLength;
    int repeats = 0;
    if (preamble) {
        pulseLength = preambleLength;
    } else if (bit == 1) {
        pulseLength = longLength;
    } else {
        repeats = 1;
    }
    for (int i = 0; i <= repeats; i++) {
        LivoloRemote::appendToSequence(LivoloRemote::output, pulseLength);
        LivoloRemote::toggleOutput();
    }
}

void LivoloRemote::appendToSequence(unsigned int bit,
                                    unsigned int pulseLength) {
    LivoloRemote::encodedSequence[LivoloRemote::encodedSequenceLength] = bit;
    LivoloRemote::encodedSequence[LivoloRemote::encodedSequenceLength + 1] =
        pulseLength;
    LivoloRemote::encodedSequenceLength += 2;
}

void LivoloRemote::transmit() {
    unsigned int output = HIGH;
    for (int i = 0; i < LivoloRemote::encodedSequenceLength; i += 2) {
        output = LivoloRemote::encodedSequence[i];
        digitalWrite(LivoloRemote::pin, output);
        delayMicroseconds(LivoloRemote::encodedSequence[i + 1]);
    }
    if (output == HIGH) {
        digitalWrite(LivoloRemote::pin, LOW);
    }
}
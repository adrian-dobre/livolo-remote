#include <LivoloRemote.h>

// set the output pin
LivoloRemote livoloRemote(4);

void setup() {}

void loop() {
    // transmit button 5 using remoteId 6400, every 3 sec
    livoloRemote.send(6400, LivoloRemoteKey::BUTTON_5);
    // optionally specify the number of command repeats, by default it repeats 200x
    // livoloRemote.send(6400, LivoloRemoteKey::BUTTON_5, 50);
    delay(3000);
}
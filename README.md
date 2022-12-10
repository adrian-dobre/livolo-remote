# (Arduino) Livolo Remote Library (TX only) for Livolo RF switches.

## Thanks to the community
 Thanks kranjec.primoz@gmail.com for the research done on his blog https://neofoxx.com/post-4.html, kind3r@gmail.com for the keycodes (https://github.com/kind3r/livolo-rf-codes), Sergey Chernov for the initial Livolo lib (https://forum.arduino.cc/t/control-livolo-switches-livolo-switch-library/149850) and to all the awesome people that gathered various info here https://community.home-assistant.io/t/broadlink-rm-pro-livolo-switches-rf-learning-woes/12432 and here https://forum.arduino.cc/t/control-livolo-switches-livolo-switch-library/149850

## How to use it
The easiest way is to check the [blink example](./examples/blink.ino)
Basically you need to init the library with the output pin 
```
LivoloRemote livoloRemote(4);
```
and then just sent the remoteId and button code
```
livoloRemote.send(6400, LivoloRemoteKey::BUTTON_5);
```
optionally you can specify the number of repeated commands, by default is 150
```
livoloRemote.send(6400, LivoloRemoteKey::BUTTON_5, 50);
```

Keycodes are provided via LivoloRemoteKey namespace, but you can send others if you want.

Some notes on remote IDs (from: https://github.com/kind3r/livolo-rf-codes/blob/master/src/broadlink.js):
 - valid remote IDs: 1 - 65500
 - valid dimmer remote IDs: 16384 - 32767


When transformed in binary:
 - 4 button remotes have an even number of 1's
 - full remotes have an odd number of 1's

Dimmer-able remotes have special IDs
 Assumption:
 - between 16399 and 32767
 - have at least 5 1's

Remote ids that work (*) or not with dimmer switches.

|ID     |Binary             |Working|
| --- | ----------- | ---- |
|7400   |001110011101000 (7)||
|12871  |011001001000111 (7)||
|16384  |100000000000000 (1)||
|16387  |100000000000011 (3)||
|16389  |100000000000101 (3)||
|16390  |100000000000110 (3)||
|16396  |100000000001100 (3)||
|16399  |100000000001111 (5)|*|
|16408  |100000000011000 (3)||
|16500  |100000001110100 (5)|*|
|17084  |100001010111100 (7)|*|
|18083  |100011010100011 (7)|*|
|18285  |100011101101101 (9)|*|
|18286  |100011101101110 (9)|*|
|18288  |100011101110000 (7)|*|
|26339  |110011011100011 (9)|*|
|26560  |110011111000000 (7)|*|
|26623  |110011111111111 (13)|*|
|32764  |111111111111100 (13)|*|
|32765  |111111111111101 (14)|DIMMER|
|32767  |111111111111111 (15)|*|
|55555  |1101100100000011 (7)||

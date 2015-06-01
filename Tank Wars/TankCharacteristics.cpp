#include "TankCharacteristics.h"
#include <string>
#include <iostream>



TankCharacteristic ussrT46 = { L"T-46", 1, "images/T-46.png",
IntRect(0, 0, 100, 48), IntRect(0, 51, 85, 29),
17, 2, 59, 52, 44, 0.6, 14, 250 };

TankCharacteristic ussrT34 = { L"T-34", 2, "images/T-34.png",
IntRect(0, 0, 112, 56), IntRect(0, 58, 128, 42),
28, 8, 44, 40, 49, 2.5, 85, 450 };

TankCharacteristic ussrKV1 = { L"KB-1", 3, "images/KV1.png",
IntRect(0, 0, 120, 60), IntRect(0, 62, 102, 36),
26, 6, 26, 20, 24, 5, 200, 840 };

TankCharacteristic ussrIS = { L"IS", 4, "images/IS.png",
IntRect(0, 0, 131, 64), IntRect(0, 71, 152, 50),
33, 14, 38, 35, 28, 12.3, 390, 1250 };

TankCharacteristic ussrIS3 = { L"IS-3", 5, "images/IS-3.png",
IntRect(0, 0, 129, 60), IntRect(0, 61, 138, 55),
32, 15, 35, 30, 26, 10, 390, 1850 };

TankCharacteristic germanyPz1C = { L"Pz-1C", 1, "images/PZ-1C.png",
IntRect(0, 0, 98, 46), IntRect(0, 49, 54, 32),
18, 3, 55, 44, 42, 0.3, 8, 230 };

TankCharacteristic germanyPZIV = { L"PZ IV", 2, "images/PZIV.png",
IntRect(0, 0, 110, 59), IntRect(0, 60, 123, 53),
36, 0, 43, 32, 44, 6, 230, 480 };

TankCharacteristic germanyTiger1 = { L"Tiger I", 3, "images/TigerI.png",
IntRect(0, 0, 120, 68), IntRect(0, 69, 142, 46),
22, 1, 30, 26, 18, 6.6, 275, 750 };

TankCharacteristic germanyTiger2 = { L"Tiger II", 4, "images/TigerII.png",
IntRect(0, 0, 140, 72), IntRect(0, 74, 190, 54),
36, 7, 24, 28, 27, 10.3, 320, 1230 };

TankCharacteristic germanyMaus = { L"Maus", 5, "images/Maus.png",
IntRect(0, 0, 171, 76), IntRect(0, 77, 196, 70),
51, -22, 20, 15, 16, 15, 490, 2000 };
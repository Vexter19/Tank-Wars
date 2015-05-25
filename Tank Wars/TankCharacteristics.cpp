#include "TankCharacteristics.h"
#include <string>
#include <iostream>



TankCharacteristic ussrT46 = { L"T-46", 1, "images/T-46.png",
IntRect(0, 0, 100, 48), IntRect(0, 51, 85, 29),
17, 2, 52, 36, 36, 1, 50, 100 };

TankCharacteristic ussrT34 = { L"T-34", 2, "images/T-34.png",
IntRect(0, 0, 112, 56), IntRect(0, 58, 128, 42),
28, 8, 52, 36, 36, 1, 50, 100 };

TankCharacteristic ussrKV1 = { L"ÊÂ-1", 3, "images/KV1.png",
IntRect(0, 0, 120, 60), IntRect(0, 61, 102, 36),
26, 6, 52, 36, 36, 1, 50, 100 };

TankCharacteristic ussrIS = { L"ÈÑ", 4, "images/IS.png",
IntRect(0, 0, 131, 64), IntRect(0, 71, 152, 50),
33, 14, 52, 36, 36, 1, 50, 100 };

TankCharacteristic ussrIS3 = { L"ÈÑ-3", 5, "images/IS-3.png",
IntRect(0, 0, 129, 60), IntRect(0, 61, 138, 55),
32, 15, 100, 100, 100, 1, 50, 800 };

TankCharacteristic germanyPz1C = { L"Pz-1C", 1, "images/PZ-1C.png",
IntRect(0, 0, 98, 46), IntRect(0, 49, 54, 32),
18, 3, 70, 100, 50, 1, 10, 100 };

TankCharacteristic germanyPZIV = { L"PZ IV", 2, "images/PZIV.png",
IntRect(0, 0, 110, 59), IntRect(0, 60, 123, 53),
36, 0, 50, 25, 25, 10, 10, 100 };

TankCharacteristic germanyTiger1 = { L"Tiger I", 3, "images/TigerI.png",
IntRect(0, 0, 120, 68), IntRect(0, 69, 142, 46),
22, 1, 50, 25, 25, 10, 10, 100 };

TankCharacteristic germanyTiger2 = { L"Tiger II", 4, "images/TigerII.png",
IntRect(0, 0, 140, 72), IntRect(0, 74, 190, 54),
36, 7, 50, 25, 25, 10, 10, 100 };

TankCharacteristic germanyMaus = { L"Maus", 5, "images/Maus.png",
IntRect(0, 0, 171, 76), IntRect(0, 77, 196, 70),
51, -22, 26, 20, 18, 16, 80, 100 };
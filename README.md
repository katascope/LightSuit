# KataTracks
The KataTracks system is three parts: The KataTracks software, the LightSuit, and the LightSuitAngel device.

## KataTracks
![Image](https://github.com/katascope/KataTracks/blob/main/Images/KataTracks.png)

The KataTracks Application provides remote Bluetooth Low Energy (BLE) control over multiple LightSuits.

## LightSuit
![Image](https://github.com/katascope/KataTracks/blob/main/Images/Lightsuits1.png)
![Image](https://github.com/katascope/KataTracks/blob/main/Images/PrototypeBelt3.png)
![Image](https://github.com/katascope/KataTracks/blob/main/Images/LightVests1.png)
![Image](https://github.com/katascope/KataTracks/blob/main/Images/LightSuitInternal.png)
![Image](https://github.com/katascope/KataTracks/blob/main/Images/LightsuitCableHole2.png)

Parts:
* BTF-LIGHTING WS2812B RGB 5050SMD Individual Addressable LED
* BTF-LIGHTING 3 Pin Electrical Connector 22AWG IP65 Male Female Connector
* Two-sided Velcro strip attached to suits
* Adhesive Velctro strip attached to LED strips
* Rubberized suit hole

Each LightSuit is a series of individually controlled addressable LED strips and LightSuitAngel. Velcro strips are attached to clothing, then to led strips. The velcro holds the strips together and connect at ends through 3-wire BTF connectors into the LightSuitAngel.

## LightSuitAngel
The LightSuitAngel devices provides 8-channels of control of LightSuit control. A 3d-printed case covers an Arduino Nano BLE device, using NeoPixel to run micro-second timed preprogrammed tracks.

![Image](https://github.com/katascope/KataTracks/blob/main/Images/LightAngel1.png)
![Image](https://github.com/katascope/KataTracks/blob/main/Images/ExplodedLightAngel.png)
![Image](https://github.com/katascope/KataTracks/blob/main/Images/PrototypeSquid.png)
![Image](https://github.com/katascope/KataTracks/blob/main/Images/PrototypeSquid2.png)

Parts
* Arduino Nano BLE
* BTF-LIGHTING WS2812B RGB 5050SMD Individual Addressable LED
* BTF-LIGHTING 3 Pin Electrical Connector 22AWG IP65 Male Female Connector
* LM2596S LM2596 Buck Converter 3A DC-DC 3-40V to 1.5-35v DC Voltage Regulator 
* 1000uF 50V Capacitor
* XT60 connector
* 25pcs DIP IC Chip Socket Adaptor
* M3 screws

Other simpler 1-channel devices can also be used with BTF splitters.

![Image](https://github.com/katascope/KataTracks/blob/main/Images/LightDeviceMarkTwo-1.png)
![Image](https://github.com/katascope/KataTracks/blob/main/Images/ExplodedDevice.png)
![Image](https://github.com/katascope/KataTracks/blob/main/Images/LightDevices2.png)

In combination, the KataTracks system allows for multiple time-synchronized led light-suits to be used for performance dance.

![Image](https://github.com/katascope/KataTracks/blob/main/Images/TronPasoDoble.png)

Abandoned ideas:
* Using EL wire, too monochrome of effects.
* Using IMU for colors, too unpredictable during dance.
* Using regular Arduino Nano, Bluetooth modules cumbersome to attach.
* Using Arduino Nano IOT, timing was flaky.
* Playing music to theater, theater will have to provide sound.
* JST 3-wires, connectors have no tension or bend protection.

KataTracks is under the [MIT License](https://opensource.org/licenses/MIT)

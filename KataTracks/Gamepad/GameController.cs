/*Copyright 6/14/2022 github/katascope
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/
using System;
using System.Collections.Generic;
using SharpDX;
using SharpDX.DirectInput;

/*
 * Buttons
 *  Buttons0 = 1
 *  Buttons1 = 2
 *  Buttons2 = 3
 *  Buttson3 = 4
 *  Buttons4 = L1
 *  Buttons5 = R1
 *  Buttons6 = L2
 *  Buttons7 = R2
 *  Buttons8 = Select
 *  Buttons9 = Start
 *  Buttons10 = JoyLeftBtn
 *  Buttons11 = JoyRightBtn
 *  D-Left = X 0, 32511
 *  D-Right = X 65535, 32511
 *  D-Up = Y 0, 32511
 *  D-Dn = Y 65535, 32511
 *  Analog, then JoyRight = RotationZ, Z
 */

namespace KataTracks
{
    class GameControllerState
    {
        public bool Button0;
        public bool Button1;
        public bool Button2;
        public bool Button3;
        public bool Button4;
        public bool Button5;
        public bool Button6;
        public bool Button7;
        public bool Button8;
        public bool Button9;
        public bool Button10;
        public bool Button11;
        public bool XLeft;
        public bool XRight;
        public bool YUp;
        public bool YDn;
        public override string ToString()
        {
            return Button0 + " "
                + Button1 + " "
                + Button2 + " "
                + Button3 + " "
                + Button4 + " "
                + Button5 + " "
                + Button6 + " "
                + Button7 + " "
                + Button8 + " "
                + Button9 + " "
                + Button10 + " "
                + Button11 + " "
                + XLeft + " "
                + XRight + " "
                + YUp + " "
                + YDn + " "
                ;
        }
    }

    class GameController
    {
        public GameControllerState gameControllerState = new GameControllerState();
        Joystick joystick;

        public void Initialize()
        {
            // Initialize DirectInput
            var directInput = new DirectInput();

            // Find a Joystick Guid
            var joystickGuid = Guid.Empty;

            foreach (var deviceInstance in directInput.GetDevices(DeviceType.Gamepad,
                        DeviceEnumerationFlags.AllDevices))
                joystickGuid = deviceInstance.InstanceGuid;

            // If Gamepad not found, look for a Joystick
            if (joystickGuid == Guid.Empty)
                foreach (var deviceInstance in directInput.GetDevices(DeviceType.Joystick,
                        DeviceEnumerationFlags.AllDevices))
                    joystickGuid = deviceInstance.InstanceGuid;

            // If Joystick not found, throws an error
            if (joystickGuid == Guid.Empty)
            {
                Console.WriteLine("No joystick/Gamepad found.");
                Console.ReadKey();
                Environment.Exit(1);
            }

            // Instantiate the joystick
            joystick = new Joystick(directInput, joystickGuid);

            Console.WriteLine("Found Joystick/Gamepad with GUID: {0}", joystickGuid);

            // Query all suported ForceFeedback effects
            var allEffects = joystick.GetEffects();
            foreach (var effectInfo in allEffects)
                Console.WriteLine("Effect available {0}", effectInfo.Name);

            // Set BufferSize in order to use buffered data.
            joystick.Properties.BufferSize = 128;

            // Acquire the joystick
            joystick.Acquire();

        }
        public void Poll()
        {
            joystick.Poll();
            var datas = joystick.GetBufferedData();

            foreach (var state in datas)
            {
                JoystickOffset offset = state.Offset;
                if (offset.ToString() == "Buttons0") gameControllerState.Button0 = (state.Value == 128);
                else if (offset.ToString() == "Buttons1") gameControllerState.Button1 = (state.Value == 128);
                else if (offset.ToString() == "Buttons2") gameControllerState.Button2 = (state.Value == 128);
                else if (offset.ToString() == "Buttons3") gameControllerState.Button3 = (state.Value == 128);
                else if (offset.ToString() == "Buttons4") gameControllerState.Button4 = (state.Value == 128);
                else if (offset.ToString() == "Buttons5") gameControllerState.Button5 = (state.Value == 128);
                else if (offset.ToString() == "Buttons6") gameControllerState.Button6 = (state.Value == 128);
                else if (offset.ToString() == "Buttons7") gameControllerState.Button7 = (state.Value == 128);
                else if (offset.ToString() == "Buttons8") gameControllerState.Button8 = (state.Value == 128);
                else if (offset.ToString() == "Buttons9") gameControllerState.Button9 = (state.Value == 128);
                else if (offset.ToString() == "Buttons10") gameControllerState.Button10 = (state.Value == 128);
                else if (offset.ToString() == "Buttons11") gameControllerState.Button11 = (state.Value == 128);
                else if (offset.ToString() == "X")
                {
                    switch (state.Value)
                    {
                        case 0: gameControllerState.XLeft = true; break;
                        case 65535: gameControllerState.XRight = true; break;
                        case 32511:
                            gameControllerState.XLeft = false;
                            gameControllerState.XRight = false;
                            break;
                    }
                }
                else if (offset.ToString() == "Y")
                {
                    switch (state.Value)
                    {
                        case 0: gameControllerState.YUp = true; break;
                        case 65535: gameControllerState.YDn = true; break;
                        case 32511:
                            gameControllerState.YUp = false;
                            gameControllerState.YDn = false;
                            break;
                    }
                }

                Console.WriteLine("Offset " + offset);
                Console.WriteLine(state);
                Console.WriteLine(gameControllerState);
            }
        }
    }
}

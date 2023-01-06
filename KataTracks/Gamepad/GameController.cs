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
    public enum GameControllerEvent
    {
        None,
        B1_Dn, B1_Up,
        B2_Dn, B2_Up,
        B3_Dn, B3_Up,
        B4_Dn, B4_Up,
        L1_Dn, L1_Up,
        R1_Dn, R1_Up,
        L2_Dn, L2_Up,
        R2_Dn, R2_Up,

        Select_Dn, Select_Up,
        Start_Dn, Start_Up,
        J1_Dn, J1_Up,
        J2_Dn, J2_Up,

        XLeft_Dn, XLeft_Up,
        XRight_Dn, XRight_Up,
        YUp_Dn, YUp_Up,
        YDn_Dn, YDn_Up,
    }

    class GameControllerState
    {
        public bool B1;
        public bool B2;
        public bool B3;
        public bool B4;
        public bool L1;
        public bool R1;
        public bool L2;
        public bool R2;
        public bool Select;
        public bool Start;
        public bool J1;
        public bool J2;
        public bool XLeft;
        public bool XRight;
        public bool YUp;
        public bool YDn;


        public override string ToString()
        {
            return "B1=" + B1
                + " B2=" + B2
                + " B3=" + B3
                + " B4=" + B4
                + " L1=" + L1
                + " R1=" + R1
                + " L2=" + L2
                + " R2=" + R2
                + " Sel=" + Select
                + " Start=" + Start
                + " J1=" + J1
                + " J2=" + J2
                + " XL=" + XLeft
                + " XR=" + XRight
                + " YUp=" + YUp
                + " YDn=" + YDn
                ;
        }
    }

    class GameController
    {
        public GameControllerState gameControllerState = new GameControllerState();
        private Joystick joystick;

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
        public GameControllerEvent Poll()
        {
            joystick.Poll();
            var datas = joystick.GetBufferedData();

            foreach (var state in datas)
            {
                JoystickOffset offset = state.Offset;
                if (offset.ToString() == "Buttons0") return (state.Value == 0) ? GameControllerEvent.B1_Up : GameControllerEvent.B1_Dn;
                else if (offset.ToString() == "Buttons1") return (state.Value == 0) ? GameControllerEvent.B2_Up : GameControllerEvent.B2_Dn;
                else if (offset.ToString() == "Buttons2") return (state.Value == 0) ? GameControllerEvent.B3_Up : GameControllerEvent.B3_Dn;
                else if (offset.ToString() == "Buttons3") return (state.Value == 0) ? GameControllerEvent.B4_Up : GameControllerEvent.B4_Dn;
                else if (offset.ToString() == "Buttons4") return (state.Value == 0) ? GameControllerEvent.L1_Up : GameControllerEvent.L1_Dn;
                else if (offset.ToString() == "Buttons5") return (state.Value == 0) ? GameControllerEvent.R1_Up : GameControllerEvent.R1_Dn;
                else if (offset.ToString() == "Buttons6") return (state.Value == 0) ? GameControllerEvent.L2_Up : GameControllerEvent.L2_Dn;
                else if (offset.ToString() == "Buttons7") return (state.Value == 0) ? GameControllerEvent.R2_Up : GameControllerEvent.R2_Dn;
                else if (offset.ToString() == "Buttons8") return (state.Value == 0) ? GameControllerEvent.Select_Up : GameControllerEvent.Select_Dn;
                else if (offset.ToString() == "Buttons9") return (state.Value == 0) ? GameControllerEvent.Start_Up : GameControllerEvent.Start_Dn;
                else if (offset.ToString() == "Buttons10") return (state.Value == 0) ? GameControllerEvent.J1_Up : GameControllerEvent.J1_Dn;
                else if (offset.ToString() == "Buttons11") return (state.Value == 0) ? GameControllerEvent.J2_Up : GameControllerEvent.J2_Dn;
                else if (offset.ToString() == "X")
                {
                    switch (state.Value)
                    {
                        case 0: gameControllerState.XLeft = true; return GameControllerEvent.XLeft_Dn;
                        case 65535: gameControllerState.XRight = true; return GameControllerEvent.XRight_Dn;
                        case 32511:
                            if (gameControllerState.XLeft) { gameControllerState.XLeft = false; return GameControllerEvent.XLeft_Dn; }
                            if (gameControllerState.XRight) { gameControllerState.XRight = false; return GameControllerEvent.XRight_Dn; }
                            break;
                    }
                }
                else if (offset.ToString() == "Y")
                {
                    switch (state.Value)
                    {
                        case 0: gameControllerState.YUp = true; return GameControllerEvent.YUp_Dn;
                        case 65535: gameControllerState.YDn = true; return GameControllerEvent.YDn_Dn;
                        case 32511:
                            if (gameControllerState.YUp) { gameControllerState.YUp = false; return GameControllerEvent.YUp_Dn; }
                            if (gameControllerState.YDn) { gameControllerState.XRight = false; return GameControllerEvent.YDn_Dn; }
                            break;
                    }
                }

                /*Console.WriteLine("Offset " + offset);
                Console.WriteLine(state);
                Console.WriteLine(gameControllerState);*/
            }

            return GameControllerEvent.None;
        }
    }
}

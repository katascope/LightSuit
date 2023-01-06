/*Copyright 6/14/2022 github/katascope
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/
using System;
using System.Collections.Generic;
using SharpDX;
using SharpDX.DirectInput;

namespace KataTracks
{
    class Program
    {
        static void Main(string[] args)
        {
            GameController gameController = new GameController();
            gameController.Initialize();

            while (true)
            {
                GameControllerEvent joyEvent = gameController.Poll();

                switch (joyEvent)
                {
                    case GameControllerEvent.B1_Dn: Console.WriteLine("B1_Dn"); break;
                    case GameControllerEvent.B1_Up: Console.WriteLine("B1_Up"); break;
                    case GameControllerEvent.B2_Dn: Console.WriteLine("B2_Dn"); break;
                    case GameControllerEvent.B2_Up: Console.WriteLine("B2_Up"); break;
                    case GameControllerEvent.B3_Dn: Console.WriteLine("B3_Dn"); break;
                    case GameControllerEvent.B3_Up: Console.WriteLine("B3_Up"); break;
                    case GameControllerEvent.B4_Dn: Console.WriteLine("B4_Dn"); break;
                    case GameControllerEvent.B4_Up: Console.WriteLine("B4_Up"); break;
                    case GameControllerEvent.L1_Dn: Console.WriteLine("L1_Dn"); break;
                    case GameControllerEvent.L1_Up: Console.WriteLine("L1_Up"); break;
                    case GameControllerEvent.R1_Dn: Console.WriteLine("R1_Dn"); break;
                    case GameControllerEvent.R1_Up: Console.WriteLine("R1_Up"); break;
                    case GameControllerEvent.L2_Dn: Console.WriteLine("L2_Dn"); break;
                    case GameControllerEvent.L2_Up: Console.WriteLine("L2_Up"); break;
                    case GameControllerEvent.R2_Dn: Console.WriteLine("R2_Dn"); break;
                    case GameControllerEvent.R2_Up: Console.WriteLine("R2_Up"); break;
                    case GameControllerEvent.Select_Dn: Console.WriteLine("Select_Dn"); break;
                    case GameControllerEvent.Select_Up: Console.WriteLine("Select_Up"); break;
                    case GameControllerEvent.Start_Dn: Console.WriteLine("Start_Dn"); break;
                    case GameControllerEvent.Start_Up: Console.WriteLine("Start_Up"); break;
                    case GameControllerEvent.J1_Dn: Console.WriteLine("J1_Dn"); break;
                    case GameControllerEvent.J1_Up: Console.WriteLine("J1_Up"); break;
                    case GameControllerEvent.J2_Dn: Console.WriteLine("J2_Dn"); break;
                    case GameControllerEvent.J2_Up: Console.WriteLine("J2_Up"); break;
                    case GameControllerEvent.XLeft_Dn: Console.WriteLine("XLeft_Dn"); break;
                    case GameControllerEvent.XLeft_Up: Console.WriteLine("XLeft_Up"); break;
                    case GameControllerEvent.XRight_Dn: Console.WriteLine("XRight_Dn"); break;
                    case GameControllerEvent.XRight_Up: Console.WriteLine("XRight_Up"); break;
                    case GameControllerEvent.YUp_Dn: Console.WriteLine("YUp_Dn"); break;
                    case GameControllerEvent.YUp_Up: Console.WriteLine("YUp_Up"); break;
                    case GameControllerEvent.YDn_Dn: Console.WriteLine("YDn_Dn"); break;
                    case GameControllerEvent.YDn_Up: Console.WriteLine("YDn_Up"); break;

                }
            }
        }
    }
}

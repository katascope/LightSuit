/*Copyright 6/14/2022 github/katascope
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/
//Reading: https://docs.microsoft.com/en-us/dotnet/core/compatibility/interop/5.0/built-in-support-for-winrt-removed
using System;
using System.Text;
using System.Threading;

namespace KataTracks
{
    class DeviceWatcher
    { 
        static public Thread bleListenerThread = null;
        static public Thread btListenerThread = null;
        static public bool keepListening = true;
        static public string bleMonitorLog = "";
        static public string btMonitorLog = "";

        static private void ListenToConnected(object in_name)
        {
            while (keepListening)
            {
                btMonitorLog = "Inactive BT:\n";
                bleMonitorLog = "Inactive BLE:\n";
                Thread.Sleep(1);
            }
        }

        static private void MonitorBLEDevices(object in_name)
        {
            while (keepListening)
            {
                /*bleMonitorLog = "MonitoringBLE ("+ DeviceManagerBLE.discoveredBLE.Count+")\n";
                foreach (KeyValuePair<string,string> kvp in DeviceManagerBLE.discoveredBLE)
                {
                    bleMonitorLog += " " + kvp.Key + " : " + kvp.Value + "\n";
                }
                foreach (KeyValuePair<string, string> kvp in DeviceManagerBLE.discoveredBLE)
                {
                    DeviceManagerBLE.poll();
                }*/
            }
        }


        private static bool _isMonitoring = false;
        public static bool IsMonitoring() { return _isMonitoring; }  
        public static void StartMonitoring()
        {
            _isMonitoring = true;
            DeviceManagerBLE.StartMonitoring(null);
        }

        public static void StopMonitoring()
        {
            keepListening = false;
        }
    }
}

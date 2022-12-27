/*Copyright 6/14/2022 github/katascope
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/
//Reading: https://docs.microsoft.com/en-us/dotnet/core/compatibility/interop/5.0/built-in-support-for-winrt-removed
using System;
using System.Text;
using System.Threading;
using System.Collections.Generic;
using System.Threading.Tasks;
using System.Collections.Concurrent;
using InTheHand.Bluetooth;

namespace KataTracks
{
    public class DeviceSearchBLE
    {
        private static BluetoothLEScanFilter scanFilter = new BluetoothLEScanFilter();
        private static RequestDeviceOptions rdo = new RequestDeviceOptions();
        private static Dictionary<string, string> discoveredBLE = new Dictionary<string, string>();
        private static IReadOnlyCollection<BluetoothDevice> discoveredDevices = null;
        public static async Task<Dictionary<string, string>> DiscoverDevicesAsync()
        {
            scanFilter = new BluetoothLEScanFilter();
            rdo = new RequestDeviceOptions();
            discoveredBLE = new Dictionary<string, string>();
            //scanFilter.NamePrefix = "Light";    
            //rdo.Filters.Add(scanFilter);
            discoveredDevices = await Bluetooth.ScanForDevicesAsync();            

            foreach (BluetoothDevice bd in discoveredDevices)
            {
                if (bd.Name.Contains("Pree") || bd.Name.Contains("Mree") || bd.Name.Contains("LightSuit") || bd.Name.Contains("Lightsuit"))
                {
                    if (!discoveredBLE.ContainsKey(bd.Id))
                    {
                        discoveredBLE[bd.Id] = bd.Name;
                    }
                }
            }
            return discoveredBLE;
        }
    }
}
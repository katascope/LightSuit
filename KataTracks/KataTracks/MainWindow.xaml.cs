using System;
using System.Collections.Generic;
using InTheHand.Net.Sockets;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Threading;
using NAudio;
using NAudio.Wave;
using NAudio.MediaFoundation;
using NAudio.FileFormats;
using System.Windows.Threading;
using System.Windows.Controls.Primitives;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace KataTracks
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        static string filename = "..\\..\\..\\TronGame.m4a";
        static WaveOutEvent outputDevice = null;
        static DispatcherTimer animationTimer;
        static DispatcherTimer connectionTimer;
        static DispatcherTimer btTextTimer;
        static bool playing = false;
        static DateTime literalTrackStartTime;
        float volume = 100;
        static long timePick = 0;
        static bool b1Down = false;
        static ulong textTickCount = 0;
        static Thread discoverBleThread;
        static Dictionary<string, string> foundDevices = null;
        static bool useSoundTrigger = false;
        static float InputVolumeBias = 50;
        static int VolumeThreshold = 50;

        public MainWindow()
        {
            InitializeComponent();
            MainLog.Text = "KataTracks initializing\n";

            outputDevice = new WaveOutEvent();
            if (outputDevice == null)
            {
                MainLog.Text += "No wave out\n";
            }

            animationTimer = new DispatcherTimer();
            connectionTimer = new DispatcherTimer();
            btTextTimer = new DispatcherTimer();
            Canvas.SetLeft(TrackIndex, 0);
            Canvas.SetLeft(TrackIndexPlay, 0);
            OutputVolumeSlider.Value = volume;
            InputVolumeSlider.Value = InputVolumeBias;

            //CombinedBluetoothController.Initialize();

            DeviceVolume.Use("Line");
            DeviceWatcher.StartMonitoring();

            MainLog.Text += "Ready to Connect\n";

            animationTimer.Tick += new EventHandler(dispatcherTimer_Tick);
            animationTimer.Interval = new TimeSpan(0, 0, 0, 0, 100);
            animationTimer.Start();

            btTextTimer.Tick += new EventHandler(btTextTimer_Tick);
            btTextTimer.Interval = new TimeSpan(0, 0, 0, 0, 100);
            btTextTimer.Start();



            WriteableBitmap writeableBitmap = new WriteableBitmap(
                            (int)1300,
                            (int)512,
                            96,
                            96,
                            PixelFormats.Bgr32,
                            null);

            byte[] pixels = new byte[1300*8*4];

            for (int y=0;y<8;y++)
            {
                for (int x=0;x<1300;x++)
                {
                    pixels[y * 1300 * 4 + x * 4 + 0] = 0;
                    pixels[y * 1300 * 4 + x * 4 + 1] = 255;
                    pixels[y * 1300 * 4 + x * 4 + 2] = 0;
                    pixels[y * 1300 * 4 + x * 4 + 3] = 255;
                }
            }
            TrackDecoder.Decode(pixels);
            Int32Rect rect = new Int32Rect(0, 0, 1300, 8);
            writeableBitmap.WritePixels(rect, pixels, 1300*4, 0);

            image.Source = writeableBitmap;
            image.Stretch = Stretch.None;
            image.HorizontalAlignment = HorizontalAlignment.Left;
            image.VerticalAlignment = VerticalAlignment.Top;
        }

        private void PlayTrack(int seconds)
        {
            if (playing)
                return;

            MainLog.Text += "Playing Track @" + seconds + " seconds\n";

            var audioFile = new AudioFileReader(filename);

            audioFile.Skip((int)(seconds));
            outputDevice.Init(audioFile);

            timePick = seconds * 10;

            string code = "@" + (timePick * 100) + "\r\n";
            DeviceManagerBLE.Play((ulong)timePick * 100);

            outputDevice.Play();
            outputDevice.Volume = volume/100.0f;

            literalTrackStartTime = DateTime.Now;

            playing = true;
        }

        private void StopTrack(bool resetLocation)
        {
            MainLog.Text += "Stopping track\n";

            outputDevice.Stop();
            //dispatcherTimer.Stop();
            playing = false;
            if (resetLocation)
            {
                Canvas.SetLeft(TrackIndexPlay, 0);
            }
            DeviceManagerBLE.SendMessage("(");
            DeviceManagerBLE.SendMessage("0");
        }

        private void WriteLogSlot(int slot, string title, string message, int color)
        {
            var brush = new SolidColorBrush(Color.FromRgb(127, 127, 127));
            if (color == 1)
                brush = new SolidColorBrush(Color.FromRgb(192,192, 63));
            if (color == 2)
                brush = new SolidColorBrush(Color.FromRgb(63, 192, 63));
            if (color == 3)
                brush = new SolidColorBrush(Color.FromRgb(192, 63, 63));

            switch (slot)
            {
                case 0:
                    Log1.Text = title + "\n" + message;
                    Log1.Foreground = brush;
                    Log1.ScrollToEnd();
                    break;
                case 1:
                    Log2.Text = title + "\n" + message;
                    Log2.Foreground = brush;
                    Log2.ScrollToEnd();
                    break;
                case 2:
                    Log3.Text = title + "\n" + message;
                    Log3.Foreground = brush;
                    Log3.ScrollToEnd();
                    break;
                case 3:
                    Log4.Foreground = brush;
                    Log4.Text = title + "\n" + message;
                    Log4.ScrollToEnd();
                    break;
                case 4:
                    Log5.Text = title + "\n" + message;
                    Log5.Foreground = brush;
                    Log5.ScrollToEnd();
                    break;
                case 5:
                    Log6.Text = title + "\n" + message;
                    Log6.Foreground = brush;
                    Log6.ScrollToEnd();
                    break;
                case 6:
                    Log7.Text = title + "\n" + message;
                    Log7.Foreground = brush;
                    Log7.ScrollToEnd();
                    break;
                case 7:
                    Log8.Foreground = brush;
                    Log8.Text = title + "\n" + message;
                    Log8.ScrollToEnd();
                    break;
                case 8:
                    Log9.Foreground = brush;
                    Log9.Text = title + "\n" + message;
                    Log9.ScrollToEnd();
                    break;
                case 9:
                    Log10.Foreground = brush;
                    Log10.Text = title + "\n" + message;
                    Log10.ScrollToEnd();
                    break;
                case 10:
                    Log11.Foreground = brush;
                    Log11.Text = title + "\n" + message;
                    Log11.ScrollToEnd();
                    break;
                case 11:
                    Log12.Foreground = brush;
                    Log12.Text = title + "\n" + message;
                    Log12.ScrollToEnd();
                    break;
            }
        }

        private void btTextTimer_Tick(object sender, EventArgs e)
        {
            //DeviceManagerBLE.poll();

            int slot = 0;
            foreach (KeyValuePair<string,BleDevice> kvp in DeviceManagerBLE.bleDevices)
            {
                int color = 0;
                if (DeviceManagerBLE.bleDevices[kvp.Key].log.Contains("Waiting"))
                    color = 1;
                if (DeviceManagerBLE.bleDevices[kvp.Key].log.Contains("OK"))
                    color = 2;
                if (DeviceManagerBLE.bleDevices[kvp.Key].log.Contains(" DC"))
                    color = 3;
                WriteLogSlot(slot, kvp.Value.name, DeviceManagerBLE.bleDevices[kvp.Key].log, color);
                slot++;
            }

            textTickCount++;

            MainLog.Text = "";
            float inputVolume = DeviceVolume.GetVolume();
            InputVolume.Value = inputVolume;

            if (useSoundTrigger && inputVolume >= VolumeThreshold && !playing)
            {
                Canvas.SetLeft(TrackIndex, 0);
                timePick = 0;
                Canvas.SetLeft(TrackIndexPlay, timePick);

                TrackTime.Content = "0:0:0";
                TrackTimeOffset.Content = "0:0:0";

                PlayTrack(1);
            }

            //MainLog.Text += "Update #" + textTickCount + " ";

            if (playing)
                MainLog.Text += "Playing,";
            else MainLog.Text += "Stopped,";
            MainLog.Text += " Seek " + (timePick*100.0f)+ " ms\n";

            MainLog.Text += "SoundTrigger " + (useSoundTrigger ? "ON" : "off") + "\n";

            MainLog.Text += "SoundInput " + DeviceVolume.GetName() + "\n";

            if (DeviceVolume.IsActive())
                MainLog.Text += "Input (" + (int)(DeviceVolume.GetBias()*100.0f) + "%) "+ (int)inputVolume + " of " + (int)VolumeThreshold + "\n";
            else MainLog.Text += "Input inactive\n";

/*            if (outputDevice != null)
                MainLog.Text += "Output (" + (int)volume + "%)\n";
            else
                MainLog.Text += "Output inactive\n";*/

            if (foundDevices != null)
                MainLog.Text += "Devices " + foundDevices.Count + "\n";

            /* MainLog.Text += "Actives:\n";
             foreach (KeyValuePair<string, BleDevice> kvp in DeviceManagerBLE.bleDevices)
                 MainLog.Text += " " + kvp.Value.log + "\n";

             foreach (KeyValuePair<string, BluetoothClient> kvp in DeviceManagerBT.clients)
             {
                 if (kvp.Value.Connected)
                     MainLog.Text += " (BT) " + kvp.Key + " ok\n";
                 else if (kvp.Value.Connected)
                     MainLog.Text += " (BT) " + kvp.Key + " NOT ok\n";
             }*/

            string bleScanned = "";
            if (foundDevices!= null)
            {
                bleScanned = "Found: " + foundDevices.Count + "\n";
                foreach (KeyValuePair<string, string> kvp in foundDevices)
                {
                    bleScanned += kvp.Value + " : " + kvp.Key + "\n";
                }
            }
            MainLog.Text += bleScanned;


            //MainLog.Text += "\n";
            MainLog.Text += DeviceManagerBLE.MonitorLog;
            MainLog.ScrollToEnd();
        }

        private void dispatcherTimer_Tick(object sender, EventArgs e)
        {
            if (!playing) return;

            if (outputDevice.PlaybackState == PlaybackState.Stopped)
                StopTrack(true);

            //4,416,049
            TimeSpan timeElapsedSincePlay = DateTime.Now - literalTrackStartTime;// + new TimeSpan(0,0,0,0,(int)timePlay*100);
            TimeSpan timeCurrentInSong = timeElapsedSincePlay + new TimeSpan(0, 0, 0, 0, (int)timePick * 100);
            TrackTime.Content = ""
                + timeCurrentInSong.Minutes + ":"
                + timeCurrentInSong.Seconds + ":"
                + timeCurrentInSong.Milliseconds / 100;

            double timeValue = (double)(timeCurrentInSong.TotalMilliseconds) / 100;
            Canvas.SetLeft(TrackIndexPlay, Math.Round(timeValue, 0));
            CommandManager.InvalidateRequerySuggested();
        }

        private void Exit(object sender, RoutedEventArgs e)
        {
            DeviceManagerBLE.DisconnectAll();
            MainLog.Text += "Exiting\n";
            System.Windows.Application.Current.Shutdown();
            Environment.Exit(0);
        }

        private static void DiscoverBleThread(object in_name)
        {
            foundDevices = DeviceSearchBLE.DiscoverDevicesAsync().Result;
        }

        private void BleSearchButton_Click(object sender, RoutedEventArgs e)
        {
            discoverBleThread = new Thread(DiscoverBleThread);
            discoverBleThread.Start();
        }

        private void PlayFromStartButton_Click(object sender, RoutedEventArgs e)
        {
            Canvas.SetLeft(TrackIndex, 0);
            timePick = 0;
            Canvas.SetLeft(TrackIndexPlay, timePick);

            TrackTime.Content = "0:0:0";
            TrackTimeOffset.Content = "0:0:0";

            PlayTrack(0);
        }

        private void PlayButton_Click(object sender, RoutedEventArgs e)
        {
            double ts = timePick;
            ts = Math.Round(ts / 10, 0);
            PlayTrack((int)ts);
        }
        private void StopButton_Click(object sender, RoutedEventArgs e)
        {
            Canvas.SetLeft(TrackIndexPlay, 0);
            StopTrack(true);
        }

        private void OnMouseDown(object sender, MouseEventArgs e)
        {
            if (playing)
                return;
            b1Down = true;
        }
        private void OnMouseUp(object sender, MouseEventArgs e)
        {
            b1Down = false;
        }

        private void OnMouseMove(object sender, MouseEventArgs e)
        {
            double Y = e.GetPosition(this).Y;
            if (b1Down && Y > 150)
            {
                double X = e.GetPosition(this).X;
                timePick = (long)X;

                X = Math.Round(X / 10, 0) * 10;
                Canvas.SetLeft(TrackIndex, X);

                TimeSpan ts = new TimeSpan(0, 0, 0, 0, (int)timePick * 100);// DateTime.Now - trackStartTime;
                TrackTimeOffset.Content = ""
                    + ts.Minutes + ":"
                    + ts.Seconds + ":"
                    + 0;
            }
        }

        private void VolumeSlider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            volume = (float)e.NewValue;
            if (outputDevice != null)
                outputDevice.Volume = (volume/100.0f);
        }


        void StopAndSendToBoth(string value)
        {
            if (value == "gt") value = ">";
            else if (value == "lt") value = "<";
            DeviceManagerBLE.SendMessage(value);
        }
        private void SendBoth(object sender, RoutedEventArgs e)
        {
            var button = sender as Button;            
            StopAndSendToBoth(""+button.Tag);
        }

        private void SendColor(object sender, RoutedEventArgs e)
        {
            var button = sender as Button;
            string buttonTag = button.Tag.ToString();
            char buttonTagChar = buttonTag[0];

            if (RadioColorSolid.IsChecked == true)
            {
                switch (buttonTagChar)
                {
                    case '0': StopAndSendToBoth("0"); break;
                    case '1': StopAndSendToBoth("1"); break;
                    case '2': StopAndSendToBoth("2"); break;
                    case '3': StopAndSendToBoth("3"); break;
                    case '4': StopAndSendToBoth("4"); break;
                    case '5': StopAndSendToBoth("5"); break;
                    case '6': StopAndSendToBoth("6"); break;
                    case '7': StopAndSendToBoth("7"); break;
                    case '8': StopAndSendToBoth("8"); break;
                    case '9': StopAndSendToBoth("9"); break;
                }
            }
            else if (RadioColorPulse.IsChecked == true)
            {
                switch (buttonTagChar)
                {
                    case '0': StopAndSendToBoth("a"); break;
                    case '1': StopAndSendToBoth("s"); break;
                    case '2': StopAndSendToBoth("d"); break;
                    case '3': StopAndSendToBoth("f"); break;
                    case '4': StopAndSendToBoth("g"); break;
                    case '5': StopAndSendToBoth("h"); break;
                    case '6': StopAndSendToBoth("j"); break;
                    case '7': StopAndSendToBoth("k"); break;
                    case '8': StopAndSendToBoth("l"); break;
                    case '9': StopAndSendToBoth("m"); break;
                }
            }
            else if (RadioColorPulse2.IsChecked == true)
            {
                switch (buttonTagChar)
                {
                    case '0': StopAndSendToBoth("A"); break;
                    case '1': StopAndSendToBoth("S"); break;
                    case '2': StopAndSendToBoth("D"); break;
                    case '3': StopAndSendToBoth("F"); break;
                    case '4': StopAndSendToBoth("G"); break;
                    case '5': StopAndSendToBoth("H"); break;
                    case '6': StopAndSendToBoth("J"); break;
                    case '7': StopAndSendToBoth("K"); break;
                    case '8': StopAndSendToBoth("L"); break;
                    case '9': StopAndSendToBoth("M"); break;
                }
            }

        }


        private void InputVolumeTriggerSlider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            VolumeThreshold = (int)e.NewValue;
        }

        private void InputVolumeSlider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            DeviceVolume.SetBias((float)e.NewValue/50.0f);//100 * 2
        }

        private void TriggerCheckBox_Checked(object sender, RoutedEventArgs e)
        {
            useSoundTrigger = true;
        }

        private void TriggerCheckBox_Unchecked(object sender, RoutedEventArgs e)
        {
            useSoundTrigger = false;
        }
    }
}

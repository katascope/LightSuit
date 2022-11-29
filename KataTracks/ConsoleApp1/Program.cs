using System.Runtime.CompilerServices;

namespace ConsoleApp1
{
    class TrackMacro
    {
        public string name;
        public TrackMacro(string n)
        {
            name = n;
        }
        public override string ToString()
        {
            return name;
        }
    }

    class TrackEvent
    {
        public string name;
        public TrackEvent(string n)
        {
            name = n;
        }
        public override string ToString()
        {
            return name;
        }
    }

    class TrackDefs
    {
        public List<TrackMacro> macros = new List<TrackMacro>();
        public List<TrackEvent> events = new List<TrackEvent>();

        public void ReadMacros(string filename)
        {
            string[] lines = System.IO.File.ReadAllLines(filename);

            foreach (string line in lines)
            {
                if (line.Contains("#define"))
                {
                    string name = line.Split(' ')[1];
                    name = name.Split('(')[0].TrimStart('_');
                    macros.Add(new TrackMacro(name));
                }
            }
        }

        public void ReadEvents(string filename)
        {
            string[] lines = System.IO.File.ReadAllLines(filename);

            bool inFxEvent = false;
            foreach (string line in lines)
            {
                if (line.Contains('}'))
                    inFxEvent = false;
                else if (line.Contains("enum FxEvent"))
                    inFxEvent = true;
                else if (inFxEvent)
                {
                    string name = line.Trim();
                    name = name.Split(',')[0];
                    name = name.Split(' ')[0];
                    if (name.Length > 1)
                    {
                        events.Add(new TrackEvent(name));
                    }
                }
            }
        }

        public void DisplayMacros()
        {
            Console.WriteLine("Macros\n----------------------------------------------------------");
            foreach (TrackMacro tm in macros)
                Console.WriteLine(tm);
            Console.WriteLine();
        }

        public void DisplayEvents()
        {
            Console.WriteLine("Events\n----------------------------------------------------------");
            foreach (TrackEvent te in events)
                Console.WriteLine(te);
            Console.WriteLine();
        }

        public void Read(string folder)
        {
            ReadMacros(folder + @"\TrackMacros.h");
            ReadEvents(folder + @"\FxCore.h");
        }
    };

    class TrackCommand
    {
        public ulong tc;
        public string cmd;
        public string fx;        
    }

    class Tracks
    {
        public static void ReadTracks(string filename)
        {
            string[] lines = System.IO.File.ReadAllLines(filename);
            bool inMacro = false;
            foreach (string str in lines)
            {
                if (str.Contains("}"))
                    inMacro = false;
                else if (str.Contains("const unsigned long SongTrack"))
                    inMacro = true;
                else if (inMacro)
                {
                    Console.WriteLine(str);
                }

            }
        }
    }

    class Performer
    {

    }

    internal class Program
    {
        static void Main(string[] args)
        {
            TrackDefs td = new TrackDefs();
            td.Read(@"G:\github\LightSuit\Arduino\LedTracks");
            Tracks.ReadTracks(@"G:\github\LightSuit\Arduino\LedTracks\Track.h");

            //td.DisplayMacros();
            //td.DisplayEvents();
        }
    }
}
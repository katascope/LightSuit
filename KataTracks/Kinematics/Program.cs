/*Copyright 6/14/2022 github/katascope
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/
using System;
using System.Collections.Generic;
using System.Reflection.Metadata;

namespace KataTracks
{
    class Program
    {
        //Given two sides, return length of third side of triangle.
        static double LengthTriangleSideC(double lenA, double lenB)
        {
            return Math.Sqrt(lenA * lenA + lenB * lenB);
        }

        static double rad2d(double rad)
        {
            return (rad * 180.0 / Math.PI);
        }
        static double d2rad(double deg)
        {
            return (deg * (Math.PI/180.0));
        }

        static double GetLengthGivenAngle(double lenThigh, double lenFoot, double angle)
        {
            double c = Math.Sqrt((lenThigh * lenThigh) + (lenFoot * lenFoot) - ((2 * lenFoot * lenThigh) * Math.Cos(angle)));
            return c;
        }

        static double GetThirdangle(double angle1, double angle2)
        {
            return d2rad(180 - (rad2d(angle1) + rad2d(angle2)));
        }

        static void GetFootAngleGivenThighAngleAndHeight(double lenThigh, double lenFoot, double distance, double height, out double topAngle, out double footAngle)
        {
            double lenThird = Math.Sqrt(height * height + distance * distance);
            topAngle  = Math.Asin( ( (lenThigh * lenThigh) + (lenThird * lenThird) - (lenFoot * lenFoot) ) / (2 * lenThigh * lenThird) );
            footAngle = Math.Asin( ( (lenThigh * lenThigh) + (lenFoot * lenFoot) - (lenThird * lenThird) ) / (2 * lenThigh * lenFoot)  );

            if (distance < 0)
            {
                topAngle = -topAngle;
            }

            //double angleTipToThigh = Math.Asin(lenThigh / lenFoot * Math.Sin(thighAngle));//from adjacent angle
            //double angleC = GetThirdangle(thighAngle, angleTipToThigh);
            //double lenHyp = GetLengthGivenAngle(lenThigh, lenFoot, angleC);

            //double lenFloor = LengthTriangleSideC(lenHyp, height);
            //Console.Write("("+rad2d(thighAngle) + ", " + rad2d(angleC) + ", " + rad2d(angleTipToThigh)+".." + lenHyp+")");

            //Console.Write("("+ lenHyp + "/"+ ")");
            //return angleFoot;
        }

        static void Main(string[] args)
        {
            double lenThigh = 11;
            double lenFoot  = 14;
            double lenBottom = LengthTriangleSideC(lenThigh,lenFoot);//at 90 degrees
            Console.WriteLine("Triangle " + lenThigh + ", " + lenFoot + ", " + lenBottom);

            double c = GetLengthGivenAngle(lenThigh, lenFoot, d2rad(90));
            Console.WriteLine("c=" + c);

            double height = 17.8;
            int stride = 10;
            for (int distance = stride; distance > -stride; distance--)
            {
                double topAngle = 0;
                double footAngle = 0;
                GetFootAngleGivenThighAngleAndHeight(lenThigh, lenFoot, distance, height, out topAngle, out footAngle);
                Console.WriteLine("["+distance+","+height + "] top=" + rad2d(topAngle) + ", foot=" + rad2d(footAngle));
            }
            return;

            double angleT = Math.Acos(( ((lenFoot * lenFoot) + (lenBottom * lenBottom)) - (lenThigh * lenThigh)) / (2 * lenFoot * lenBottom));
            Console.WriteLine(rad2d(angleT));

            double angleF = Math.Acos((((lenThigh * lenThigh) + (lenBottom * lenBottom)) - lenFoot * lenFoot) / (2 * lenThigh * lenBottom));
            Console.WriteLine(rad2d(angleF));

            double angleB = Math.Acos(( ((lenFoot * lenFoot) + (lenThigh * lenThigh)) - (lenBottom * lenBottom) ) / (2 * lenFoot * lenThigh));
            Console.WriteLine(rad2d(angleB));

        }
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;

using MathNet.Numerics.LinearAlgebra;
using MathNet.Numerics.LinearAlgebra.Storage;
using MathNet.Numerics.LinearAlgebra.Double;

namespace ai.lab
{
    public class Program
    {

        public static int f = 3;
        private static int steps = 2000;

        public static void Main(String[] args)
        {
            Stopwatch st = new Stopwatch();
            st.Start();

            // generate tensor
            int n = 100;
            int m = 100;
            int k = 100;
            int elems = 10000;
            Tensor a = new Tensor(n, m, k, elems, 1000);
            Console.WriteLine("Tensor generated");
            Tensor aOld = a.Clone();
            Console.WriteLine("Cloned");

            // slice tensor by one dimension and concat received matricies consequently.
            for (int i = 1; i <= f; i++)
            {
                a.calcSlices();
                Console.WriteLine("Slices calculated");
                Solver.solve(
                        a,
                        a.sliceN,   // n x (m*k)
                        a.sliceM,   // m x (n*k)
                        a.sliceK,   // k x (n*m)
                        steps,
                        SparseVector.Create(a.n, 1),
                        SparseVector.Create(a.m, 1),
                        SparseVector.Create(a.k, 1),
                        i);
            }

            double av = 0;
            for (int i = 0; i < aOld.k; ++i)
            {
                var els = aOld.a[i].EnumerateIndexed(Zeros.AllowSkip);
                foreach (var elem in els)
                    av += Math.Abs(elem.Item3 - Solver.getAns(elem.Item1, elem.Item2, i));
            }
            Console.WriteLine("|| Diff || = " + (av / (a.n * a.m * a.k)));

            st.Stop();
            Console.WriteLine(st.ElapsedMilliseconds / 1000.0);
        }
    }

}

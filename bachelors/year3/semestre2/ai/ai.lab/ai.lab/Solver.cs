using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using MathNet.Numerics.LinearAlgebra;
using MathNet.Numerics.LinearAlgebra.Double;
using MathNet.Numerics.LinearAlgebra.Factorization;
using MathNet.Numerics.LinearAlgebra.Storage;

namespace ai.lab
{
    public class Solver
    {
        public static List<Vector> nnn = new List<Vector>();
        public static List<Vector> mmm = new List<Vector>();
        public static List<Vector> kkk = new List<Vector>();

        public static void solve(
                Tensor a,
                Matrix sliceN, Matrix sliceM, Matrix sliceK,
                int steps,
                Vector n, Vector m, Vector k,
                int it)
        {

            for (int ff = 0; ff < steps; ff++)
            {
                Console.Write("step " + ff); System.GC.Collect();
                n = approx(sliceN, k, m);
                Console.Write("."); System.GC.Collect();
                m = approx(sliceM, k, n);
                Console.Write("."); System.GC.Collect();
                k = approx(sliceK, n, m);
                Console.WriteLine(".");
            }
            Console.WriteLine("Estimated");
            //printArray(n);
            nnn.Add(n);
            //printArray(m);
            mmm.Add(m);
            //printArray(k);
            kkk.Add(k);
            Console.WriteLine();

            // rewrite tensor
            Parallel.For(0, a.k, i =>
            {
                var data = a.a[i].EnumerateIndexed(Zeros.AllowSkip);
                var lst = new List<Tuple<int, int, double>>();
                foreach (var elem in data)
                {
                    lst.Add(Tuple.Create(
                        elem.Item1, elem.Item2,
                        elem.Item3 - n[elem.Item1] * m[elem.Item2] * k[i]));
                }
                a.a[i] = SparseMatrix.OfIndexed(a.n, a.m, lst);
            });
        }

        public static double getAns(int i, int j, int k)
        {
            double ans = 0;
            for (int q = 0; q < Program.f; q++)
                ans += nnn[q][i] * mmm[q][j] * kkk[q][k];
            return ans;
        }

        public static void printArray(Vector m)
        {
            Console.Write(" [");
            for (int i = 0; i < m.Count; i++)
                Console.Write("{0:F3} ", m[i]);
            Console.WriteLine("] ");

        }

        public static Vector approx(Matrix x, Vector b, Vector c)
        {
            return approx2(x, getCron(b, c));
        }

        public static Vector approx2(Matrix x, Vector z)
        {
            Vector x1 = x.Multiply(z) as Vector;
            double zz = Math.Pow(z.Norm(2), 2);
            return x1.Multiply(1 / Math.Max(1e-3, zz)) as Vector;
        }

        public static Vector getCron(Vector b, Vector c)
        {
            Vector cron = DenseVector.Create(b.Count * c.Count, 0);
            for (int j = 0; j < c.Count; j++)
                for (int i = 0; i < b.Count; i++)
                    cron[i + j * b.Count] = b[i] * c[j];
            return cron;
            //var lst = new List<Tuple<int, double>>();
            //var lstB = b.EnumerateIndexed(Zeros.AllowSkip);
            //var lstC = c.EnumerateIndexed(Zeros.AllowSkip);
            //foreach (var elB in lstB)
            //    foreach (var elC in lstC)
            //        // cron[i + j * b.Count] = b[i] * c[j];
            //        lst.Add(Tuple.Create(elB.Item1 + elC.Item1 * b.Count, elB.Item2 * elC.Item2));
            ////lst.Sort();
            //return SparseVector.OfIndexedEnumerable(b.Count * c.Count, lst);
        }
    }
}

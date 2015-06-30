using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using MathNet.Numerics.LinearAlgebra;
using MathNet.Numerics.LinearAlgebra.Double;
using MathNet.Numerics.Distributions;
using System.Collections;

namespace ai.lab
{
    public class Tensor
    {
        public int n, m, k;
        public SparseMatrix[] a;

        private Tensor() { }

        public Tensor(int n, int m, int k, int number, int maxElem)
        {
            this.n = n;
            this.m = m;
            this.k = k;
            a = new SparseMatrix[k];
            Random rand = new Random();
            for (int i = 0; i < k; ++i)
            {
                var elems = new List<Tuple<int, int, double>>();
                Console.WriteLine(i + " ");
                for (int j = 0; j < number / k; ++j)
                {
                    elems.Add(new Tuple<int, int, double>(
                        rand.Next(n), rand.Next(m),
                        rand.NextDouble() * maxElem));
                }
                a[i] = SparseMatrix.OfIndexed(n, m, elems);
            }
        }

        public SparseMatrix sliceK { get; set; }
        public SparseMatrix sliceN { get; set; }
        public SparseMatrix sliceM { get; set; }

        public void calcSlices()
        {
            var listK = new List<Tuple<int, int, double>>();
            var listN = new List<Tuple<int, int, double>>();
            var listM = new List<Tuple<int, int, double>>();
            for (int i = 0; i < k; ++i)
            {
                var cur = a[i].EnumerateIndexed(Zeros.AllowSkip);
                foreach (var elem in cur)
                {
                    //[i][j, s]->[i, j+s*n]
                    //[i][Item1, Item2] -> [i, Item1 + Item2 * n]
                    listK.Add(new Tuple<int, int, double>(i, elem.Item1 + elem.Item2 * n, elem.Item3));
                    //[j][s, i]->[i, j+s*k]
                    //[i][Item1, Item2] -> [Item2, i + Item1 * k]
                    listM.Add(new Tuple<int, int, double>(elem.Item2, i + elem.Item1 * k, elem.Item3));
                    //[s][i,j]->[i,j+s*m]  - sliceN
                    //[i][Item1, Item2] -> [Item1, Item2 + i * m]
                    listN.Add(new Tuple<int, int, double>(elem.Item1, elem.Item2 + i * m, elem.Item3));
                }
            }
            sliceK = SparseMatrix.OfIndexed(k, n * m, listK);
            sliceN = SparseMatrix.OfIndexed(n, k * m, listN);
            sliceM = SparseMatrix.OfIndexed(m, k * n, listM);
        }

        public Tensor Clone()
        {
            Tensor res = new Tensor();
            res.a = new SparseMatrix[this.a.Length];
            res.n = n; res.m = m; res.k = k;
            for (int i = 0; i < res.a.Length; ++i)
                res.a[i] = this.a[i].Clone() as SparseMatrix;
            return res;
        }
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace testing_lab1
{
    public class MyMaths
    {
        public const double EPS = 1e-5;

        private static List<double> nextCoefs(List<double> coefs)
        {
            List<double> result = new List<double>();
            result.Add(1);
            for (int i = 1; i < coefs.Count; ++i)
            {
                result.Add(coefs[i - 1] + coefs[i]);
            }
            result.Add(1);
            return result;
        }

        private static double nextBernulli(int n, List<double> Bs, List<double> coefs) // coefs[n + 1]
        {
            double result = 0;
            for (int k = 1; k <= n; ++k)
            {
                result += coefs[k + 1] * Bs[n - k];
            }
            result *= -1.0 / (n + 1);
            return result;
        }

        public static Tuple<double, int> cth(double x, double e)
        {
            if (Math.Abs(x) < 1e-10 || Math.Abs(x) > Math.PI - 1e-10) throw new ArgumentException("x should be in range (0, Pi)");
            e = Math.Abs(e);
            double result = 0;
            int nsteps = 0;
            int minus_1_pow_n_minus_1 = -1;
            double two_pow_2n = 1;
            double x_pow_2n_minus_1 = 1 / x;
            double fact_2n = 1;
            List<double> Bs = new List<double>();
            Bs.Add(1);
            List<double> coefs = new double[] { 1, 1 }.ToList(); // coefs[n = 1]
            for (;;)
            {
                double cur = minus_1_pow_n_minus_1 * two_pow_2n * Bs[nsteps * 2] * x_pow_2n_minus_1 / fact_2n;
                if (nsteps == 0) cur = 1 / x;

                if (Math.Abs(cur) < e)
                {
                    break;
                }
                // update result
                ++nsteps;
                result += cur;
                // update iteration values
                minus_1_pow_n_minus_1 = minus_1_pow_n_minus_1 == -1 ? 1 : -1;
                two_pow_2n *= 4; // 2^2(n+1) = 2^2n*2^2
                x_pow_2n_minus_1 *= x * x; // same for x
                for (int i = ((nsteps - 1) << 1) + 1; i <= (nsteps << 1); ++i)
                {
                    fact_2n *= i;
                }
                for (int i = 0; i < 2; ++i)
                {
                    coefs = nextCoefs(coefs);  // coefs [n + 1]
                    Bs.Add(nextBernulli(Bs.Count, Bs, coefs));
                }
            }
            return new Tuple<double, int>(result, nsteps);
        }

        public static bool CthResultCorrect(double x, double e)
        {
            var myRes = cth(x, e);
            var res = Math.Cosh(x) / Math.Sinh(x);
            return Math.Abs(res - myRes.Item1) < 0.1;
        }
    }
}

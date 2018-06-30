using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace testing_lab1
{
    class Program
    {
        static void Main(string[] args)
        {
            var results = new List<Tuple<double, double, double, int>>();
            for (;;)
            {
                Console.Write("Enter value of x (or 'end' to end the programme): ");
                double x;
                string x_str = Console.ReadLine();
                if (x_str == "end") break;
                if (!double.TryParse(x_str, out x))
                {
                    Console.WriteLine("Wrong value of x entered");
                    return;
                }
                Console.Write("Enter value of e: ");
                double e;
                if (!double.TryParse(Console.ReadLine(), out e))
                {
                    Console.WriteLine("Wrong value of e entered");
                    return;
                }

                try
                {
                    var curRes = MyMaths.cth(x, e);
                    Console.WriteLine($"(with precision {e}) y=cth({x})={curRes.Item1} (in {curRes.Item2} steps)");
                    results.Add(new Tuple<double, double, double, int>(x, e, curRes.Item1, curRes.Item2));
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex.Message);
                }
            }
            try
            {
                Console.Write("Write to a file? [yes/no]: ");
                if (Console.ReadLine() == "yes")
                {
                    string lastfile = null;
                    string filename = null;
                    if (File.Exists("lastfile.dat"))
                    {
                        lastfile = File.ReadAllLines("lastfile.dat").FirstOrDefault();
                    }
                    if (!string.IsNullOrEmpty(lastfile))
                    {
                        // Ask if write into last file
                        Console.Write($"Write into last file<{lastfile}>? [yes/no]: ");
                        if (Console.ReadLine() == "yes")
                        {
                            filename = lastfile;
                        }
                    }
                    if (string.IsNullOrEmpty(filename))
                    {
                        // Ask for a file name
                        Console.Write("Enter filename: ");
                        filename = Console.ReadLine();
                    }

                    if (filename == "*")
                    {
                        throw new Exception();
                    }

                    if (!File.Exists(filename))
                    {
                        using (var file = File.CreateText(filename))
                        {
                            file.WriteLine(
                                "Date".PadRight(20) + "|" +
                                "Argument x".PadRight(20) + "|" +
                                "Precision e".PadRight(20) + "|" +
                                "Value f(x)".PadRight(20) + "|" +
                                "Length of N".PadRight(20));
                        }
                    }

                    File.AppendAllLines(filename, results.ConvertAll(
                        tpl =>
                            DateTime.Now.Date.ToShortDateString().PadRight(20) + "|" + 
                            tpl.Item1.ToString().PadRight(20) + "|" + 
                            tpl.Item2.ToString().PadRight(20) + "|" + 
                            tpl.Item3.ToString().PadRight(20) + "|" + 
                            tpl.Item4.ToString().PadRight(20)).ToArray());

                    File.WriteAllText("lastfile.dat", filename);

                    Console.WriteLine($"Written to a file <{filename}>");
                    Console.WriteLine($"Total of {File.ReadAllLines(filename).Length - 1} records");
                }
                else
                {
                    throw new Exception();
                }
            }
            catch
            {
                Console.WriteLine("Data hasn't been written to a file");
            }
        }
    }
}

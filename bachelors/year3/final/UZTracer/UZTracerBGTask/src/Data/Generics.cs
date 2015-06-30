using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace UZTracerBGTask.src.Data
{
    public sealed class Generics
    {
        public static IDictionary<string, string> createDictStringString()
        {
            Type d1 = typeof(Dictionary<,>);
            Type[] typeArgs = { typeof(string), typeof(string) };
            Type makeme = d1.MakeGenericType(typeArgs);
            object o = Activator.CreateInstance(makeme);
            return o as IDictionary<string, string>;
        }

        public static IDictionary<string, int> createDictStringInt()
        {
            Type d1 = typeof(Dictionary<,>);
            Type[] typeArgs = { typeof(string), typeof(int) };
            Type makeme = d1.MakeGenericType(typeArgs);
            object o = Activator.CreateInstance(makeme);
            return o as IDictionary<string, int>;
        }

        public static IList<IList<int>> createListListInt()
        {
            Type d1 = typeof(List<>);
            Type[] typeArgs = { typeof(List<int>) };
            Type makeme = d1.MakeGenericType(typeArgs);
            object o = Activator.CreateInstance(makeme);
            return o as IList<IList<int>>;
        }
    }
}

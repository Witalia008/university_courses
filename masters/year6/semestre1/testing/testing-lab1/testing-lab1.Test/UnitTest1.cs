using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using testing_lab1;
using NUnit.Framework;

namespace testing_lab1.Test
{
    [TestFixture]
    public class UnitTest1
    {
        [Test]
        public void TestMethod1()
        {
            Assert.IsTrue(MyMaths.CthResultCorrect(0.3, 0.0000001));
        }

        [Test]
        public void TestMethod2()
        {
            Assert.IsTrue(MyMaths.CthResultCorrect(0.7, 0.0000000005));
        }

        [Test]
        public void TestMethod3()
        {
            Assert.IsTrue(MyMaths.CthResultCorrect(0.0055, 00.0000000001));
        }

        [Test]
        public void TestMethod4()
        {
            Assert.Throws(typeof(ArgumentException), () => MyMaths.CthResultCorrect(5.9, 0.00005));
        }

        [Test]
        public void TestMethod5()
        {
            Assert.Throws(typeof(ArgumentException), () => MyMaths.cth(0, 1e-6));
        }

        [Test]
        public void TestMethod6()
        {
            Assert.Throws(typeof(ArgumentException), () => MyMaths.cth(Math.PI * 100, 1e-6));
        }
    }
}

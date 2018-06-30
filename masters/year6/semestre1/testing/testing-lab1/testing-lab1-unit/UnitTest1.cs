using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;

using testing_lab1;

namespace testing_lab1_unit
{
    [TestClass]
    public class UnitTest1
    {
        [TestMethod]
        public void TestMethod1()
        {
            Assert.IsTrue(MyMaths.CthResultCorrect(0.3, 0.0000001));
        }

        [TestMethod]
        public void TestMethod2()
        {
            Assert.IsTrue(MyMaths.CthResultCorrect(0.7, 0.0000000005));
        }

        [TestMethod]
        public void TestMethod3()
        {
            Assert.IsTrue(MyMaths.CthResultCorrect(0.0055, 00.0000000001));
        }

        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void TestMethod4()
        {
            Assert.IsTrue(MyMaths.CthResultCorrect(5.9, 0.00005));
        }

        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void TestMethod5()
        {
            Assert.IsTrue(MyMaths.CthResultCorrect(0, 1e-6));
        }

        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void TestMethod6()
        {
            Assert.IsTrue(MyMaths.CthResultCorrect(Math.PI * 100, 1e-6));
        }
    }
}

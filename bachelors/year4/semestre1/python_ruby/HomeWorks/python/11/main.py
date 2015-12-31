import math


class Expr:
    def __add__(self, other):
        return Plus(self, other)

    def __mul__(self, other):
        return Times(self, other)

    def __sub__(self, other):
        return Sub(self, other)

    def __div__(self, other):
        return Divide(self, other)

    def __pow__(self, power):
        return Power(self, power)

    @staticmethod
    def sin(arg):
        return Sin(arg)

    @staticmethod
    def cos(arg):
        return Cos(arg)

    @staticmethod
    def tan(arg):
        return Tan(arg)

    @staticmethod
    def cot(arg):
        return Cot(arg)

    @staticmethod
    def ln(arg):
        return Ln(arg)

    @staticmethod
    def exp(arg):
        return Exp(arg)

    def simplify(self):
        return self


class Number(Expr):
    def __init__(self, num):
        self.num = num

    def deriv(self, v):
        return Number(0)

    def __str__(self):
        return str(self.num)
NumberE = Number(2.71828182846)
NumberPi = Number(math.pi)


class Variable(Expr):
    def __init__(self, var):
        self.var = var

    def deriv(self, v):
        return Number(1 if self.var == v else 0)

    def __str__(self):
        return self.var


class UnaryFunc(Expr):
    def __init__(self, arg):
        self.arg = arg

    def deriv_unary(self, dlow, v):
        return dlow * self.arg.deriv(v)

    def simplify(self):
        type(self)(self.arg.simplify())

    def simplify_unary(self):
        self.arg = self.arg.simplify()


class UMinus(UnaryFunc):
    def deriv(self, v):
        return UMinus(self.arg.deriv(v))

    def __str__(self):
        return "(-(%s))" % self.arg

    def simplify(self):
        self.simplify_unary()
        if isinstance(self.arg, Number) and self.arg.num == 0:
            return Number(0)
        return self


class Exp(UnaryFunc):
    def deriv(self, v):
        return self.deriv_unary(self, v)

    def __str__(self):
        return 'exp(%s)' % self.arg

    def simplify(self):
        self.simplify_unary()
        if isinstance(self.arg, Number):
            if self.arg.num == 0:
                return Number(1)
            if self.arg.num == 1:
                return NumberE
        return self


class Ln(UnaryFunc):
    def deriv_unary(self, dlow, v):
        return self.deriv_unary(Number(1) / self.arg, v)

    def __str__(self):
        return 'ln(%s)' % self.arg

    def simplify(self):
        self.simplify_unary()
        if isinstance(self.arg, Number):
            if self.arg.num == 1:
                return Number(0)
            if self.arg.num == NumberE:
                return Number(1)
        return self


class Sin(UnaryFunc):
    def deriv(self, v):
        return self.deriv_unary(Cos(self.arg), v)

    def __str__(self):
        return "sin(%s)" % self.arg


class Cos(UnaryFunc):
    def deriv(self, v):
        return self.deriv_unary(UMinus(Sin(self.arg)), v)

    def __str__(self):
        return "cos(%s)" % self.arg


class Tan(UnaryFunc):
    def deriv(self, v):
        return self.deriv_unary(Number(1) / (Cos(self.arg) ** Number(2)), v)

    def __str__(self):
        return "tan(%s)" % self.arg


class Cot(UnaryFunc):
    def deriv(self, v):
        return self.deriv_unary(UMinus(Number(1) / (Sin(self.arg) ** Number(2))), v)

    def __str__(self):
        return "cot(%s)" % self.arg


class BinaryFunction(Expr):
    def __init__(self, arg1, arg2):
        self.arg1 = arg1
        self.arg2 = arg2

    def simplify(self):
        type(self)(self.arg1.simplify(), self.arg2.simplify())

    def simplify_binary(self, commutative=False):
        self.arg1 = self.arg1.simplify()
        self.arg2 = self.arg2.simplify()
        if isinstance(self.arg2, Number) and commutative:
            self.arg1, self.arg2 = self.arg2, self.arg1


class Plus(BinaryFunction):
    def deriv(self, v):
        return self.arg1.deriv(v) + self.arg2.deriv(v)

    def __str__(self):
        return "(%s + %s)" % (self.arg1, self.arg2)

    def simplify(self):
        BinaryFunction.simplify_binary(self, commutative=True)
        if isinstance(self.arg1, Number) and self.arg1.num == 0:
            return self.arg2
        return self


class Sub(BinaryFunction):
    def deriv(self, v):
        return self.arg1.deriv(v) - self.arg2.deriv(v)

    def __str__(self):
        return "(%s - %s)" % (self.arg1, self.arg2)

    def simplify(self):
        BinaryFunction.simplify(self)
        if isinstance(self.arg1, Number) and self.arg1.num == 0:
            return UMinus(self.arg2)
        if isinstance(self.arg2, Number) and self.arg2.num == 0:
            return self.arg1
        return self


class Times(BinaryFunction):
    def deriv(self, v):
        return self.arg2 * self.arg1.deriv(v) + self.arg1 * self.arg2.deriv(v)

    def __str__(self):
        return "(%s * %s)" % (self.arg1, self.arg2)

    def simplify(self):
        BinaryFunction.simplify_binary(self, commutative=True)
        if isinstance(self.arg1, Number):
            if self.arg1.num == 0:
                return self.arg1
            if self.arg1.num == 1:
                return self.arg2
        return self


class Divide(BinaryFunction):
    def deriv(self, v):
        return (self.arg2 * self.arg1.deriv(v) - self.arg1 * self.arg2.deriv(v)) / (self.arg2 ** Number(2))

    def __str__(self):
        return "(%s / %s)" % (self.arg1, self.arg2)

    def simplify(self):
        BinaryFunction.simplify(self)
        if isinstance(self.arg1, Number) and self.arg1.num == 0:
            return Number(0)
        if isinstance(self.arg2, Number):
            if self.arg2.num == 0:
                return Number(float('inf'))
            if self.arg2.num == 1:
                return self.arg1
        return self


class Power(BinaryFunction):
    def deriv(self, v):
        BinaryFunction.simplify_binary(self)
        if isinstance(self.arg2, Number):
            return self.arg2 * (self.arg1 ** Number(self.arg2.num-1)) * self.arg1.deriv(v)
        if isinstance(self.arg1, Number):
            return Ln(self.arg1) * self * self.arg2.deriv()
        return None

    def __str__(self):
        return "(%s ^ %s)" % (self.arg1, self.arg2)

    def simplify(self):
        BinaryFunction.simplify(self)
        if isinstance(self.arg2, Number):
            if self.arg2.num == 0:
                return Number(1)
            if self.arg2.num == 1:
                return self.arg1
        return self


if __name__ == '__main__':
    a = Variable('a')
    b = Variable('b')
    c = Variable('c')
    x = Variable('x')
    e = Number(5) * a * x * x + b * x + c + Expr.sin(x*a) + Expr.exp(x)
    print(e.deriv(x.var).simplify())

import os
try:
    from rpython.rlib.jit import JitDriver, elidable
except ImportError:
    class JitDriver:
        def __init__(self, **kw): pass
        def jit_merge_point(self, **kw): pass
        def can_enter_jit(self, **kw): pass
    def elidable(f): return f

jitdriver = JitDriver(greens=['pos', 'trees', 'labels'], reds=['vars'])


def jitpolicy(driver):
    from rpython.jit.codewriter.policy import JitPolicy
    return JitPolicy()


class Program:
    def __init__(self, text, pos):
        self.text = text
        self.pos = pos


class Tree:
    def __init__(self, data, sons):
        self.data = data
        self.sons = sons

    def __str__(self):
        return "(" + str(self.data) + ", [" + ','.join([str(x) for x in self.sons]) + "])"

    def __repr__(self):
        return str(self)


class Node:
    def __init__(self, name, value):
        self.name = name
        self.value = value

    def __str__(self):
        return "{" + str(self.name) + ", " + str(self.value) + "}"

    def __repr__(self):
        return str(self)


def ignore_ws(p):
    while p.pos < len(p.text) and p.text[p.pos] in [' ']:
        p.pos += 1


def checkstr(p, str, advance=False, err=False):
    ignore_ws(p)
    for i in xrange(len(str)):
        if p.pos+i >= len(p.text) or p.text[p.pos+i] != str[i]:
            if err:
                print("Expected %s" % str)
            return False
    if advance:
        p.pos += len(str)
    return True


def letter(p):
    return p.pos < len(p.text) and ('a' <= p.text[p.pos] <= 'z' or 'A' <= p.text[p.pos] <= 'Z')
def digit(p):
    return p.pos < len(p.text) and '0' <= p.text[p.pos] <= '9'


def reserved_name(p):
    for st in ['abs', 'get', 'put', 'go', 'finish', 'if']:
        if checkstr(p, st):
            return True
    return False


def number(p, neg=True):
    ignore_ws(p)
    res = 0
    if not (neg and checkstr(p, '-', advance=True)):
        neg = False

    while digit(p):
        res = res * 10 + ord(p.text[p.pos]) - ord('0')
        p.pos += 1

    return Node("number", str(-res if neg else res))


def varname(p):
    ignore_ws(p)
    vn = p.text[p.pos]
    p.pos += 1
    return Node("variable", vn)


def literal(p):
    res = ''
    while p.text[p.pos] != ')':
        res += p.text[p.pos]
        p.pos += 1
    return Node('literal', res)


def assign(p):
    res = cond(p)
    while checkstr(p, ':=', advance=True):
        other = cond(p)
        res = Tree(Node("oper", ":="), [res, other])
    return res


def cond(p):
    res = expr(p)
    while True:
        found = ''
        for i in ['<=', '>=', '!=', '=', '<', '>']:
            if checkstr(p, i, advance=True):
                found = i
                break

        if found == '':
            break
        other = expr(p)
        res = Tree(Node("oper", found), [res, other])
    return res


def expr(p):
    res = mult_expr(p)
    while checkstr(p, '-') or checkstr(p, '+'):
        op = p.text[p.pos]
        p.pos += 1
        other = mult_expr(p)
        res = Tree(Node("oper", op), [res, other])
    return res


def mult_expr(p):
    res = func(p)
    while checkstr(p, '*') or checkstr(p, ':') and not checkstr(p, ':='):
        op = p.text[p.pos]
        p.pos += 1
        other = func(p)
        res = Tree(Node("oper", op), [res, other])
    return res


def func(p):
    if checkstr(p, 'abs', advance=True):
        return Tree(Node("func", "abs"), [operand(p)])
    return operand(p)


def operand(p):
    if checkstr(p, '-') or digit(p):
        return Tree(number(p), [])
    elif checkstr(p, '$', advance=True):
        return Tree(literal(p), [])
    elif letter(p) and not reserved_name(p):
        return Tree(varname(p), [])
    elif checkstr(p, '(', advance=True):
        res = assign(p)
        checkstr(p, ')', advance=True, err=True)
        return res
    return None


def eval(tree, dict):
    name = tree.data.name
    value = tree.data.value
    # print("enter", name, value)
    if name == "number":
        return value
    if name == "variable":
        return dict.get(value, "0")
    if name == "func":
        return str(abs(int(eval(tree.sons[0], dict))))
    if name == 'literal':
        return value
    if name == "oper":
        if value == 'finish':
            return None
        if value == 'put':
            os.write(1, eval(tree.sons[0], dict) + '\n')
            return ''
        if value == 'get':
            val = os.read(0, 256).strip()
            dict[tree.sons[0].data.value] = val
            return val
        if value == 'go':
            return tree.sons[0].data.value
        if value == 'if':
            if eval(tree.sons[0], dict) == "1":
                return eval(tree.sons[1], dict)
            return ''

        second = int(eval(tree.sons[1], dict))
        if value == ":=":
            dict[tree.sons[0].data.value] = str(second)
            return ''
        elif value in ['<=', '>=', '!=', '=', '<', '>']:
            first = int(eval(tree.sons[0], dict))
            if value == '<=':
                # print(first <= second)
                return str(first <= second)
            if value == '>=':
                return str(first >= second)
            if value == '!=':
                return str(first != second)
            if value == '=':
                return str(first == second)
            if value == '<':
                return str(first < second)
            if value == '>':
                return str(first > second)
        else:
            first = int(eval(tree.sons[0], dict))
            if value == '+':
                return str(first + second)
            if value == '-':
                return str(first - second)
            if value == '*':
                return str(first * second)
            if value == ':':
                return str(first // second)
    # print("exit", name, value)


def operator(p):
    if checkstr(p, 'finish', advance=True):
        return Tree(Node('oper', 'finish'), [])
    if checkstr(p, 'if', advance=True):
        c = cond(p)
        o = operator(p)
        return Tree(Node('oper', 'if'), [c, o])
    for op in ['get', 'put', 'go']:
        if checkstr(p, op, advance=True):
            return Tree(Node('oper', op), [operand(p)])
    return assign(p)


def operator_label(p, id):
    labels = {}

    num = number(p, neg=False)
    if checkstr(p, '#'):
        labels[num.value] = id
        p.pos += 1

    return operator(p), labels



@elidable
def get_label_row(labels, p, pos):
    return labels.get(p, pos)


def mainloop(trees, labels):
    pos = 0
    vars = {}
    while pos >= 0:
        jitdriver.jit_merge_point(pos=pos, vars=vars, trees=trees, labels=labels)
        p = eval(trees[pos], vars)
        if p is None:
            pos = -1
        elif trees[pos].data.name == 'oper' and trees[pos].data.value == 'go':
            pos = get_label_row(labels, p, pos)
        else:
            pos += 1


def program(lines):
    trees, labels = [], {}
    for i in range(0, len(lines)):
        prog = Program(lines[i], 0)
        t, l = operator_label(prog, i)
        trees.append(t)
        labels.update(l)
    return trees, labels


def beautify(prog):
    prog = [x.strip() for x in prog.splitlines()]
    return [x for x in prog if x != '']


def run(file):
    program_contents = ''
    while True:
        read = os.read(file, 4096)
        if len(read) == 0:
            break
        program_contents += read
    os.close(file)
    program_contents = beautify(program_contents)
    trees, labels = program(program_contents)
    mainloop(trees, labels)


def entry_point(argv):
    try:
        filename = argv[1]
    except IndexError:
        print("You must supply a filename")
        return 1
    run(os.open(filename, os.O_RDONLY, 0777))
    return 0


def target(*args):
    return entry_point, None

if __name__ == '__main__':
    import sys
    entry_point(sys.argv)

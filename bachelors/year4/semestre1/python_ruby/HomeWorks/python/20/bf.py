# http://morepypy.blogspot.com/2011/04/tutorial-writing-interpreter-with-pypy.html
# http://morepypy.blogspot.com/2011/04/tutorial-part-2-adding-jit.html

import os
try:
    from rpython.rlib.jit import JitDriver, elidable
except ImportError:
    class JitDriver:
        def __init__(self, **kw): pass
        def jit_merge_point(self, **kw): pass
        def can_enter_jit(self, **kw): pass
    def elidable(f): return f


# PYPYLOG=jit-log-opt:logfile bf.exe prog.bf
# def get_location(pc, program, bracket_map):
#     return "%s_%s_%s" % (program[:pc], program[pc], program[pc+1:])


jitdriver = JitDriver(greens=['pc', 'program', 'bracket_map'], reds=['tape'])
                      #, get_printable_location=get_location)


def jitpolicy(driver):
    from rpython.jit.codewriter.policy import JitPolicy
    return JitPolicy()


@elidable
def get_matching_bracket(bracket_map, pc):
    return bracket_map[pc]


def mainloop(program, bracket_map):
    tape = Tape()
    pc = 0
    while pc < len(program):
        jitdriver.jit_merge_point(pc=pc, tape=tape, program=program, bracket_map=bracket_map)

        code = program[pc]

        if code == '>':
            tape.advance()
        elif code == '<':
            tape.devance()
        elif code == '+':
            tape.inc()
        elif code == '-':
            tape.dec()
        elif code == '.':
            os.write(1, chr(tape.get()))
            pass
        elif code == ',':
            tape.set(ord(os.read(0, 1)[0]))
            pass
        elif code == '[' and tape.get() == 0:
            pc = get_matching_bracket(bracket_map, pc)
        elif code == ']' and tape.get() != 0:
            pc = get_matching_bracket(bracket_map, pc)

        pc += 1


class Tape(object):
    def __init__(self):
        self.thetape = [0]
        self.position = 0

    def get(self):
        return self.thetape[self.position]

    def set(self, val):
        self.thetape[self.position] = val

    def inc(self):
        self.thetape[self.position] += 1

    def dec(self):
        self.thetape[self.position] -= 1

    def advance(self):
        self.position += 1
        if len(self.thetape) == self.position:
            self.thetape.append(0)

    def devance(self):
        self.position -= 1


def parse(program):
    parsed = []
    bracket_map = {}
    leftstack = []

    pc = 0
    for char in program:
        if char in ('[', ']', '<', '>', '+', '-', '.', ','):
            parsed.append(char)

            if char == '[':
                leftstack.append(pc)
            elif char == ']':
                left = leftstack.pop()
                right = pc
                bracket_map[left] = right
                bracket_map[right] = left
            pc += 1

    return ''.join(parsed), bracket_map


def run(fp):
    program_contents = ''
    while True:
        read = os.read(fp, 4096)
        if len(read) == 0:
            break
        program_contents += read
    os.close(fp)
    program, bm = parse(program_contents)
    mainloop(program, bm)


def entry_point(argv):
    try:
        filename = argv[1]
    except IndexError:
        print('You must supply a filename')
        return 1

    run(os.open(filename, os.O_RDONLY, 0777))
    return 0


def target(*args):
    return entry_point, None

if __name__ == '__main__':
    import sys
    entry_point(sys.argv)

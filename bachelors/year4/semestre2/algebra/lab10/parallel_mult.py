import random
import time
from copy import deepcopy
from multiprocessing.connection import Pipe
from threading import Thread

from multiprocessing import Process


def timing(f):
    def wrap(*args):
        time1 = time.time()
        ret = f(*args)
        time2 = time.time()
        print('%s function took %.3f ms' %
              (f.__name__, (time2 - time1) * 100.0))
        return ret
    return wrap


def rand_m(n, m):
    res = []
    for i in range(n):
        cur = []
        for j in range(m):
            cur.append(random.randint(0, 1000))
        res.append(cur)
    return res

@timing
def mult_slow(A, B):
    n, m = len(A), len(A[0])
    if m != len(B):
        return None
    r = len(B[0])
    res = []
    for a in A:
        cur = []
        for j in range(r):
            sum = 0
            for i in range(m):
                sum += a[i] * B[i][j]
            cur.append(sum)
        res.append(cur)
    return res


class MyThread(Thread):
    def __init__(self, Aa, B):
        Thread.__init__(self)
        self.A = Aa
        self.B = B
        self.res = []

    def run(self):
        self.res += mult_slow(self.A, self.B)
        print(self.res)


def mult_s(A, B, c):
    res = mult_slow(A, B)
    c.send(res)
    c.close()

@timing
def mult_fast(A, B):
    thread_cnt = 4
    n = len(A) // thread_cnt
    threads = []
    cs = []
    for i in range(thread_cnt):
        p_conn, c_conn = Pipe()
        # th = MyThread(A[n*i:n*(i+1)], B)
        th = Process(target=mult_s, args=(A[n*i:n*(i+1)], B, c_conn))
        cs.append(p_conn)
        threads.append(th)
        th.start()
    res = []
    # for t in threads:
        # t.join()
        # res += t.res
    for (t, c) in zip(threads, cs):
        res += c.recv()
    return res


if __name__ == '__main__':
    A = rand_m(100, 200)
    B = rand_m(200, 300)
    mult_slow(A, B)
    mult_fast(A, B)

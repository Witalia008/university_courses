from sympy import *

# k = 3
# V = range(1, 8+1)  # vertices
#
# E = [(1, 2), (1, 6), (1, 7), (2, 3), (3, 4), (3, 8),
#      (4, 5), (4, 8), (5, 6), (5, 8), (7, 8)]  # edges

k = 2
V = range(1, 8+1)  # vertices

E = [(1, 2), (1, 6), (1, 7), (2, 3), (3, 4),
     (4, 5), (4, 8), (5, 6), (7, 8)]  # edges

print(E)

print("--------------------")

Vx = [Symbol('x' + str(i)) for i in V]
Ex = [(Vx[i-1], Vx[j-1]) for i, j in E]

print(Ex)

print("--------------------")

F3 = [x**k - 1 for x in Vx]
Fg = [factor((x**k - y**k)/(x-y)) for x, y in Ex]

G = groebner(F3 + Fg, Vx)
print(G)

if G != [1]:
    print("Graph is colorable")
else:
    print("Graph is not colorable")

print("--------------------")

colorings = solve(G, Vx)
print(len(colorings))
print(colorings[0])

print("--------unique------------")
# uniquelist =[]
# for i in range(0,len(colorings[0])):
#  if not(colorings[0][i] in uniquelist):
#     uniquelist = uniquelist + [colorings[0][i]]
# print(uniquelist)

unique = set(colorings[0])
print(unique)

uniquelist = list(unique)

var('red,green,blue,yellow')  # variables for k colors
cols = [red, green, blue, yellow]  # list of k possible colors

substitutions = [(uniquelist[i], cols[i]) for i in range(0,k)]  # k colors

print("---------substitutions-----------")
print(substitutions)


print("---------colorings-----------")


def repl(elt):
    for i in range(k):
        res = elt.expand(complex=True).subs([substitutions[i]])
        if res in cols:
            break
    return res

for coloring in colorings:
    print ([repl(elt) for elt in coloring])
    # print ([repl(elt).count_ops(False) for elt in coloring ])

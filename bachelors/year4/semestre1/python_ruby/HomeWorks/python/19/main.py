import operator
import networkx as nx
import matplotlib.pyplot as plt
import heapq


def get_lt_path(G, s, f):
    n = len(G.node)
    dist = [int(1e9) for i in range(0, n)]
    dist[s] = 0
    par = [-1 for i in range(0, n)]
    queue = [(dist[s], s)]
    while True:
        (cur, v) = heapq.heappop(queue)
        if v == f:
            res = (cur, [])
            res[1].append(f)
            while v != s:
                v = par[v]
                res[1].append(v)
            return res

        for to in G.neighbors(v):
            to_w = G[v][to]['weight']
            if dist[to] > cur + to_w:
                par[to] = v
                dist[to] = cur + to_w
                heapq.heappush(queue, (dist[to], to))


used = {}
dist = {}
path = []


def get_gt_path(G, v, f, cur=0):
    global used, dist, path
    path.append(v)

    used[v] = True
    dist[v] = cur

    res = (-1, None)

    if v == f:
        path.pop()
        del used[v]
        return cur, path+[f]

    for to in G.neighbors(v):
        w = G[v][to]['weight']
        if (to not in used) and (to not in dist or dist[to] < cur+w):
            cpath = get_gt_path(G, to, f, cur+w)
            if cpath[0] > res[0]:
                res = cpath

    path.pop()
    del used[v]
    return res


def get_euler_path(G, v, prev=-1):
    print(v, prev)
    res = []
    if prev != -1:
        res.append((prev, v))

    if G.degree(v):
        to = G.neighbors(v)[0]
        G.remove_edge(v, to)
        res += get_euler_path(G, to, v)

    return res


def read_ints(f):
    return [int(x) for x in f.readline().split()]

filename = 'some.txt'

with open(filename, 'r') as f:
    n, m = read_ints(f)
    G = nx.Graph()
    G.add_nodes_from(range(0, n))
    print(len(G.node))
    for i in range(0, n):
        G.node[i]['used'] = False
    for i in range(0, m):
        u, v, w = read_ints(f)
        G.add_edge(u, v)
        G[u][v]['weight'] = w
    s, f = read_ints(f)

    pos = nx.spring_layout(G)

    # Smallest path
    (_, smallest_path) = get_lt_path(G, s, f)
    print(list(smallest_path))
    lt_edges = []
    for i in range(1, len(smallest_path)):
        lt_edges.append((smallest_path[i-1], smallest_path[i]))
    # Biggest path
    (_, biggest_path) = get_gt_path(G, s, f)
    gt_edges = []
    for i in range(1, len(biggest_path)):
        gt_edges.append((biggest_path[i-1], biggest_path[i]))
    print(list(biggest_path))

    # Euler cycle
    countOdd = 0
    startV = 0
    for i in range(0, n):
        if G.degree(i) % 2 == 1:
            startV = i
            countOdd += 1
    if countOdd != 0 and countOdd != 2:
        print('No Euler path')

    euler_path = get_euler_path(G.copy(), v)
    euler_edges_labels = []
    for i in range(0, len(euler_path)):
        edge = euler_path[i]
        euler_edges_labels.append((edge, (i, G[edge[0]][edge[1]]['weight'])))
    euler_edges_labels = dict(euler_edges_labels)

    nx.draw_networkx_nodes(G, pos=pos, with_labels=True, alpha=0.8)
    nx.draw_networkx_edges(G, pos=pos, width=1.0, alpha=0.5)
    nx.draw_networkx_edges(G, pos=pos, edgelist=lt_edges, width=4, alpha=0.5, edge_color='r')
    nx.draw_networkx_edges(G, pos=pos, edgelist=gt_edges, width=8, alpha=0.5, edge_color='b')
    nx.draw_networkx_edge_labels(G, pos=pos, edge_labels=euler_edges_labels)

    node_labels = {}
    for i in range(0, n):
        label = str(i)
        if i == s: label += 'S'
        if i == f: label += 'F'
        if i == startV: label += 's'
        node_labels[i] = label
    nx.draw_networkx_labels(G, pos=pos, labels=node_labels)

    plt.axis('off')
    plt.savefig(filename + ".png")
    plt.show()

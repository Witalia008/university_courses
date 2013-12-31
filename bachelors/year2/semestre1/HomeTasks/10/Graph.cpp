#include "Graph.h"


void Graph::addRib(int source, int dest, int edg) {
    adj[source].push_back(make_pair(dest, edg));
    adj[dest].push_back(make_pair(source, edg));
}

void Graph::readIncidencyList(string fname) {
    ifstream fin(fname.c_str());
    fin >> V >> E;
    adj.resize(V);
    vector<int> edge(E, -1);
    for (int i = 0; i < E * 2; ++i) {
        int edgeNum, incVertex;
        fin >> edgeNum >> incVertex;
        if (edge[edgeNum] == -1)
            edge[edgeNum] = incVertex;
        else {
            addRib(incVertex, edge[edgeNum], edgeNum);
        }
    }
    fin.close();
}

bool Graph::isEuler() {
    for (int i = 0; i < V; ++i)
        if (adj[i].size() % 2 != 0)
            return false;
    return true;
}

vector<int> Graph::euler() {
    if (isEuler() == false)
        return vector<int>();
    vector<int> res;
    stack<int> st;
    vector<int> last(V, 0);
    vector<bool> used(E, false);
    st.push(0);
    while (!st.empty()) {
        int v = st.top();
        while (last[v] < adj[v].size() && used[adj[v][last[v]].second])
            ++last[v];
        if (last[v] == adj[v].size()) {
            res.push_back(v);
            st.pop();
        } else {
            used[adj[v][last[v]].second] = true;
            st.push(adj[v][last[v]].first);
        }
    }
    return res;
}
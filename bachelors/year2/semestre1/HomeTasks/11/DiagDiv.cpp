
#include "DiagDiv.h"

vector<Point> readPoints(string fname) {
    ifstream fin(fname.c_str());
    int n;
    fin >> n;
    vector<Point> res;
    for (int i = 0; i < n; ++i) {
        int cx, cy;
        fin >> cx >> cy;
        res.push_back(Point(cx, cy));
    }
    fin.close();
    return res;
}

double dist(Point a, Point b) {
    auto sqr = [](double a) { return a * a; };
    return sqrt(sqr(a.X() - b.X()) + sqr(a.Y() - b.Y()));
}

pair<int, double> findDivision(vector<Point>& pts, int l, int r, cmpFunc comp, vvd &Mem_F) {
    if (r - l + 1 <= 3)
        return make_pair(-1, 0);
    if (Mem_F[l][r].second != -1)
        return Mem_F[l][r];
    pair<int, double> res = make_pair(0, InfL);
    for (int i = l + 1; i != r; ++i) {
        double a = dist(pts[l], pts[i]),
                b = dist(pts[r], pts[i]);
        double cur = comp(
                        comp(findDivision(pts, l, i, comp, Mem_F).second, findDivision(pts, i, r, comp, Mem_F).second),
                        comp((i == l + 1 ? 0 : a), (i == r - 1 ? 0 : b))
                        );
        if (cur < res.second)
            res = make_pair(i, cur);
    }
    return Mem_F[l][r] = res;
}

vpii getPath(vvd& Mem_F, int l, int r) {
    if (r - l + 1 <= 3)
        return vpii();
    vpii res;
    vpii fst = getPath(Mem_F, l, Mem_F[l][r].first);
    vpii snd = getPath(Mem_F, Mem_F[l][r].first, r);
    res.insert(res.end(), fst.begin(), fst.end());
    res.insert(res.end(), snd.begin(), snd.end());
    if (Mem_F[l][r].first != l + 1)
        res.push_back(make_pair(l, Mem_F[l][r].first));
    if (Mem_F[l][r].first != r - 1)
        res.push_back(make_pair(r, Mem_F[l][r].first));
    return res;
}

void calcDiadDivision(ostream& out, vector<Point> points, cmpFunc comp) {
    int n = points.size();
    vvd Mem_F;
    Mem_F.resize(n);
    for (auto &i : Mem_F)
        i.assign(n, make_pair(-1, -1));

    findDivision(points, 0, n - 1, comp, Mem_F);

    out << Mem_F[0][n - 1].second << endl;
    vpii ans = getPath(Mem_F, 0, n - 1);
    for (int i = 0; i < ans.size(); ++i)
        out << ans[i].first << " " << ans[i].second << endl;

    out << endl;
}
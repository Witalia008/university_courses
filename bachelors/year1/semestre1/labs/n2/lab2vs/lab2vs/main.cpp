#include "shapes.h"

typedef pair<Point, Point> ppp;

Circle A1, A2;
Polygon B1, B2;
Point P;
ppp cc;

void outPt (Point a)
{
    if (a == InfPt)
        cout << "No point\n";
    else
        cout << fixed << setprecision(4) << "(" <<  a.x << ", " << a.y << ") ";
}

ppp rev(ppp a)
{
    return make_pair(a.second, a.first);
}

void outArc (Circle a, ppp b, bool in)
{
    double a1 = a.getAng(b.first), a2 = a.getAng(b.second);
    if (a2 < a1) a2 += 2 * M_PI;
    double ang = (a1 + a2) / 2;
    if (!in) ang += M_PI;
    if (ang > M_PI) ang -= 2 * M_PI;
    cout << "arc from "; outPt(b.first);
    cout << "to "; outPt(b.second);
    cout << "through "; outPt(a.FromAng(ang));
    cout << endl;
}

void outPoly (Polygon a, bool in)
{
    cout << "Number of vertexes: " << a.n << endl;
    //cout << "All segments: \n";
    cout << "All points: \n";
    REP(i, a.n)
    {
        //cout << " to "; outPt(a.points[(i + 1) % a.n]);
        if (a.points[i].arcp && a.points[(i + 1) % a.n].arcp)
        {
            outArc (A1, make_pair(a.points[i], a.points[(i + 1) % a.n]), in); 
            a.points[i].arcp = false;
            ++i;
        } else
        {
            cout << "point: ";
            outPt(a.points[i]);
            cout << endl;
        }
    }
}

void greet ()
{
    fstream tt ("greet.txt", fstream::in);
    string s;
    while (!tt.eof())
    {
        getline(tt, s);
        cout << s << endl;
    }
    tt.close();
}

#define ONLINE_JUDGE
int main ()
{
    #ifndef ONLINE_JUDGE
        freopen ("input.txt", "r", stdin);
        freopen ("output.txt", "w", stdout);
    #endif
    greet();
    string s;
    for (cin >> s; s != "exit"; cin >> s)
    {
        if (s == "inp")
        {
            cout << "Enter 1 - for convex polygon, 2 - circle\n";
            int tt; cin >> tt;
            if (tt == 1)
            {
                B2 = B1;
                cout << "Enter number of vertexes\n";
                int nn;
                cin >> nn;
                cout << "Enter coordinates of all vertexes\n";
                B1.n = 0;
                B1.points.clear();
                REP(i, nn)
                {
                    cin >> P.x >> P.y;
                    B1.pb(P);
                }
                B1 = B1.convex_hull();
            } else {
                cout << "Enter coordinates of center of circle and radius\n";
                A2 = A1;
                cin >> A1.o.x >> A1.o.y >> A1.r;
            }
            cout << "successfully\n";
        } else
        if (s == "sqr")
        {
            cout << "Enter 1 - for convex polygon, 2 - circle\n";
            int tt; cin >> tt;
            if (tt == 1)
                cout << fixed << setprecision(6) << B1.square() << endl;
            else
                cout << fixed << setprecision(6) << A1.square() << endl;
        } else
        if (s == "per")
        {
            cout << "Enter 1 - for convex polygon, 2 - circle\n";
            int tt; cin >> tt;
            if (tt == 1)
                cout << fixed << setprecision(6) << B1.perimeter() << endl;
            else
                cout << fixed << setprecision(6) << A1.perimeter() << endl;
        } else
        if (s == "sidelen")
        {
            vector<Segment> cur = B1.Sides();
            REP(i, cur.size())
            {
                cout << "Segment from "; outPt(cur[i].s);
                cout << " to "; outPt(cur[i].f);
                cout << " have length " << cur[i].length() << endl;
            }
        } else
        {
            cout << "Enter type of combination. 11 - two circles, 12 circle with polygon, 22 - two polygons\n";
            string yy; cin >> yy;
            Polygon cur;
            if (s == "inter")
            {
                if (yy == "11")
                {
                    cc = Circle::getCommon(A1, A2);
                    outArc (A1, rev(cc), true);
                    outArc (A2, cc, true);
                } else
                {
                    if (yy == "22")
                        cur = Polygon::intersect(B1, B2);
                    else
                        cur = Polygon::intersect(B1, A1);
                    outPoly(cur, true);
                }
            } else
            if (s == "union")
            {
                if (yy == "11")
                {
                    cc = Circle::getCommon(A1, A2);
                    outArc (A1, rev(cc), false);
                    outArc (A2, cc, false);
                } else
                {
                    if (yy == "22")
                        cur = Polygon::unionPoly(B1, B2);
                    else
                        cur = Polygon::unionPoly(B1, A1);
                    outPoly(cur, false);
                }
            } else
            if (s == "diff")
            {
                if (yy == "11")
                {
                    cc = Circle::getCommon(A1, A2);
                    outArc(A1, cc, false);
                    outArc(A2, cc, false);
                } else
                {
                    if (yy == "22")
                        cur = Polygon::difference(B1, B2);
                    else
                        cur = Polygon::difference(B1, A1);
                    outPoly(cur, true);
                }
            } else
            if (s == "symd")
            {
                if (yy == "11")
                {
                    cc = Circle::getCommon(A1, A2);
                    cout << "First figure:\n";
                    outArc(A1, cc, true);
                    outArc(A2, cc, true);
                    cout << "Second figure:\n";
                    outArc(A1, cc, false);
                    outArc(A2, cc, false);
                } else
                {
                    pair<Polygon, Polygon> Cur;
                    if (yy == "22")
                        Cur = Polygon::symmDiff(B1, B2);
                    else
                        Cur = Polygon::symmDiff(B1, A1);
                    outPoly(Cur.first, false);
                    outPoly(Cur.second, true);
                }
            }
        }
    }
    return 0;
}

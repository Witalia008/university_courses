#include "shapes.h"


//Implementation for POINT

double Point::distance (Point a, Point b)
{
    return sqrt (sqr(a.x - b.x) + sqr(a.y - b.y));
}

double Point::distance(Line a)
{
    return fabs(a.A * x + a.B * y + a.C) / sqrt(sqr(a.A) + sqr(a.B));
}

bool Point::operator == (Point b)
{
    return fabs(x - b.x) <= eps && fabs(y - b.y) <= eps;
}

//Implementation for LINE
bool Line::belong (Point a)
{
    return a.distance(*this) < eps;
}

Vector Line::normal ()
{
    return Vector (A, B);
}

Vector Line::direct ()
{
    return Vector(-B, A);
}

Point Line::intersect (Line a, Line b)
{
    Point result = InfPt;
    double dt = a.A * b.B - a.B * b.A;
    if (fabs(dt) < eps) return result;
    result.x = -(a.C * b.B - a.B * b.C) / dt;
    result.y = -(a.A * b.C - a.C * b.A) / dt;
    return result;
}

//Implementation for SEGMENT
double Segment::length()
{
    return Vector(s, f).length();
}

bool Segment::in (Point a)
{
    Line x(s, f);
    return a.x >= min (s.x, f.x) - eps && a.x <= max(s.x, f.x) + eps
        && a.y >= min (s.y, f.y) - eps && a.y <= max(s.y, f.y) + eps && a.distance(x) <= eps;
}

bool Segment::intersect_proj (double a, double b, double c, double d){
    if (a > b) swap (a, b);
    if (c > d) swap (c, d);
    return min(b, d) >= max (a, c);
}

bool Segment::intersect (Segment a, Segment b)
{
    return  Segment::intersect_proj(a.s.x, a.f.x, b.s.x, b.f.x) &&
            Segment::intersect_proj(a.s.y, a.f.y, b.s.y, b.f.y) &&
            Vector::vProduct(a.s, a.f, b.s) * Vector::vProduct(a.s, a.f, b.f) <= 0 &&
            Vector::vProduct(b.s, b.f, a.s) * Vector::vProduct(b.s, b.f, a.f) <= 0;
}

Point Segment::getCommon (Segment a, Segment b)
{
    if (!Segment::intersect(a, b)) return InfPt;
    return Line::intersect(Line(a.s, a.f), Line(b.s, b.f));
}

//Implementation for VECTOR
double Vector::length()
{
    return sqrt(sqr(x) + sqr(y));
}

double Vector::vProduct (Point a, Point b, Point c)
{
    return Vector::vProduct (Vector(a, b), Vector(a, c));
}

double Vector::vProduct (Vector a, Vector b)
{
    return a.x * b.y - a.y * b.x;
}

double Vector::sProduct (Vector a, Vector b)
{
    return a.x * b.x + a.y * b.y;
}

void Vector::multiKoef(double k)
{
    x *= k; y *= k;
}


//Implementation for CIRCLE
double Circle::square ()
{
    return PI * sqr(r);
}

double Circle::perimeter()
{
    return 2 * PI * r;
}

bool Circle::innerPoint(Point a)
{
    return Point::distance(a, o) <= r + eps;
}


double Circle::getAng (Point a)
{
    return atan2(a.y - o.y, a.x - o.x);
}

bool Circle::intersect(Circle a, Circle b)
{
    double dist = Point::distance(a.o, b.o);
    return dist <= a.r + b.r + eps && !(dist + a.r < b.r - eps) && !(dist + b.r < a.r - eps);
}

bool Circle::intersect(Circle a, Line b)
{
    return a.o.distance(b) <= a.r + eps;
}

Point Circle::FromAng (double ang)
{
    return Point(cos(ang) * r + o.x, sin(ang) * r + o.y);
}

pair<Point, Point> Circle::getCommon(Circle a, Line b)
{
    if (!Circle::intersect(a, b))
        return mp(InfPt, InfPt);
    Vector n = b.normal(), l = b.direct();
    double d = a.o.distance(b);
    double k1 = d / n.length();
    Point P = Point (a.o.x + n.x * k1, a.o.y + n.y * k1);
    if (!b.belong(P)) P.x -= 2 * n.x * k1, P.y -= 2 * n.y * k1;
    double inn = sqrt (sqr(a.r) - sqr(d));
    double k2 = inn / l.length();
    return mp (Point(P.x + l.x * k2, P.y + l.y * k2, true), Point(P.x - l.x * k2, P.y - l.y * k2, true));
}

pair<Point, Point> Circle::getCommon(Circle a, Circle b)
{
    if (!Circle::intersect(a, b))
        return mp(InfPt, InfPt);
    double d = Point::distance(a.o, b.o);
    double x = (sqr(a.r) - sqr(b.r) + sqr(d)) / (2 * d);
    Vector n(a.o, b.o);
    n.multiKoef(x / d);
    Point P(a.o.x + n.x, a.o.y + n.y);
    Vector m(-n.y, n.x);
    double k2 = sqrt(sqr(a.r) - sqr(x)) / m.length();
    m.multiKoef(k2);
    return mp(Point(P.x + m.x, P.y + m.y, true), Point(P.x - m.x, P.y - m.y, true));
}

pair<Point, Point> Circle::getCommon (Circle a, Segment b)
{
    Line x (b.s, b.f);
    pair<Point, Point> res = Circle::getCommon(a, x);
    if (!b.in(res.first)) res.first = InfPt;
    if (!b.in(res.second)) res.second = InfPt;
    return res;
}

//Implementation for POLYGON
void Polygon::push_back(Point a)
{
    n++;
    points.push_back(a);
}

double Polygon::square ()
{
    double result = 0;
    REP(i, n)
        result += Vector::vProduct(Vector(points[i]), Vector(points[(i + 1) % n]));
    return fabs(result / 2);
}

double Polygon::perimeter ()
{
    double result = 0;
    REP(i, n)
        result += Point::distance(points[i], points[(i + 1) % n]);
    return result;
}

bool Polygon::innerPoint (Point a)
{
    Point st = points[0];
    int l = 0, r = n - 1;
    while (l < r - 1)
    {
        int mid = (l + r) >> 1;
        if (Vector::vProduct(st, points[mid], a) >= 0)
            r = mid;
        else
            l = mid;
    }
    return inTriangle(a, st, points[l], points[r]);
}

vector<Segment> Polygon::Sides()
{
    vector<Segment> res;
    res.clear();
    REP(i, n)
        res.push_back(Segment(points[i], points[(i + 1) % n]));
    return res;
}

Polygon Polygon::convex_hull()
{
    if (n == 1) return *this;
    vector<Point> up, down;
    sort (points.begin(), points.end(), &comp_x);
    Point ps = points[0], pf = points.back();
    up.push_back(ps); down.push_back(ps);
    REP(i, points.size()) if (i)
    {
        if (i == n - 1 || Vector::vProduct(ps, pf, points[i]) > 0)
        {
            while (up.size() > 1 && Vector::vProduct(up[up.size() - 2], up.back(), points[i]) >= 0)
                up.pop_back();
            up.push_back(points[i]);
        }
        if (i == n - 1 || Vector::vProduct(ps, pf, points[i]) < 0)
        {
            while (down.size() > 1 && Vector::vProduct(down[down.size() - 2], down.back(), points[i]) <= 0)
                down.pop_back();
            down.push_back(points[i]);
        }
    }
    Polygon res(0);
    REP(i, up.size())
        res.push_back(up[i]);
    FORD(i, down.size() - 2, 1)
        res.push_back(down[i]);
    res.n = res.points.size();
    return res;
}

Polygon Polygon::inter_pt (Polygon a, Polygon b)
{
    Polygon res(0);
    REP(i, a.n)
        REP(j, b.n)
        {
            Segment x(a.points[i], a.points[(i + 1) % a.n]);
            Segment y(b.points[j], b.points[(j + 1) % b.n]);
            if (Segment::intersect(x, y))
                res.push_back(Segment::getCommon(x, y));
        }
    res.n = res.points.size();
    return res;
}

Polygon Polygon::intersect(Polygon a, Polygon b)
{
    Polygon res(0);
    REP(i, a.n)
        if (b.innerPoint(a.points[i]))
            res.push_back(a.points[i]);
    REP(i, b.n)
        if (a.innerPoint(b.points[i]))
            res.push_back(b.points[i]);
    Polygon h = Polygon::inter_pt(a, b);
    REP(i, h.n)
        res.push_back(h.points[i]);
    //res = res.convex_hull();
    return res;
}

Polygon Polygon::unionPoly (Polygon a, Polygon b)
{
    Polygon res(0);
    REP(i, a.n)
        if (!b.innerPoint(a.points[i]))
            res.push_back(a.points[i]);
    REP(i, b.n)
        if (!a.innerPoint(b.points[i]))
            res.push_back(b.points[i]);
    Polygon r1 = Polygon::inter_pt(a, b);
    REP(i, r1.n)
        res.push_back(r1.points[i]);
    res.n = res.points.size();
    return res;
}

Polygon Polygon::difference (Polygon a, Polygon b)
{
    Polygon h = Polygon::inter_pt(a, b);
    if (!h.n) return a;
    Polygon res(0);
    REP(i, a.n)
        if (!b.innerPoint(a.points[i]))
            res.push_back(a.points[i]);
    REP(i, b.n)
        if (a.innerPoint(b.points[i]))
            res.push_back(b.points[i]);
    REP(i, h.n)
        res.push_back(h.points[i]);
    res.n = res.points.size();
    return res;
}

pair<Polygon, Polygon> Polygon::symmDiff(Polygon a, Polygon b)
{
    return mp(Polygon::difference(a, b), Polygon::difference(b, a));
}

Polygon Polygon::inter_pt (Polygon a, Circle b)
{
    Polygon res(0);
    REP(i, a.n)
    {
        Segment x (a.points[i], a.points[(i + 1) % a.n]);
        pair<Point, Point> y = Circle::getCommon(b, x);
        if (!(y.first == InfPt)) res.push_back(y.first);
        if (!(y.second == InfPt)) res.push_back(y.second);
    }
    res.n = res.points.size();
    return res;
}

Polygon Polygon::intersect(Polygon a, Circle b)
{
    Polygon res = inter_pt(a, b);
    REP(i, a.n)
        if (b.innerPoint(a.points[i]))
            res.push_back(a.points[i]);
    res.n = res.points.size();
    return res;
}

Polygon Polygon::unionPoly(Polygon a, Circle b)
{
    Polygon res = inter_pt(a, b);
    REP(i, a.n)
        if (!b.innerPoint(a.points[i]))
            res.pb(a.points[i]);
    res.n = res.points.size();
    return res;
}

Polygon Polygon::difference(Polygon a, Circle b)
{
    return Polygon::unionPoly(a, b);
}

pair<Polygon, Polygon> Polygon::symmDiff (Polygon a, Circle b)
{
    Polygon r1(0), r2(0);
    Polygon h = Polygon::inter_pt(a, b);
    REP(i, h.n)
        r1.pb(h.points[i]), r2.pb(h.points[i]);
    REP(i, a.n)
        if (b.innerPoint(a.points[i]))
            r1.pb(a.points[i]);
        else
            r2.pb(a.points[i]);
    return mp(r1, r2);
}

//OTHER
bool comp_x (Point a, Point b)
{
    return a.x < b.x || a.x == b.x && a.y < b.y;
}

bool comp_y (Point a, Point b)
{
    return a.y < b.y || a.y == b.y && a.x < b.x;
}

bool inTriangle (Point o, Point a, Point b, Point c)
{
    double s = fabs(Vector::vProduct(a, b, c));
    double s1 = fabs(Vector::vProduct(o, a, b));
    double s2 = fabs(Vector::vProduct(o, c, b));
    double s3 = fabs(Vector::vProduct(o, a, c));
    return (fabs(s - s1 - s2 - s3) < eps);
}

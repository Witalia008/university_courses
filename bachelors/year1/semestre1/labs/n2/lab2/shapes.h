#include "head.h"

struct Point;
struct Line;
struct Segment;
struct Vector;
struct Circle;
struct Polygon;

struct Point
{
    double x, y;
    bool arcp;
    Point () {}
    Point (double _x, double _y) : x(_x), y(_y), arcp(0) {}
    Point (double _x, double _y, bool _arcp) : x(_x), y(_y), arcp(_arcp) {}
    bool operator == (Point b);
    static double distance(Point a, Point b);
    double distance(Line a);
};

struct Line
{
    double A, B, C;
    Line () {}
    Line (Point a, Point b){
        A = a.y - b.y;
        B = b.x - a.x;
        C = a.x * b.y - a.y * b.x;
    }
    bool belong (Point a);
    Vector normal ();
    Vector direct ();
    static Point intersect (Line a, Line b);
};

struct Segment
{
    Point s, f;
    Segment () {}
    Segment (Point _s, Point _f): s(_s), f(_f) {}
    double length();
    bool in (Point a);
    static bool intersect_proj (double a, double b, double c, double d);
    static bool intersect (Segment a, Segment b);
    static Point getCommon (Segment a, Segment b);
};

struct Vector
{
    double x, y;
    Vector () {}
    Vector (Point a): x(a.x), y(a.y) {}
    Vector (double _x, double _y) : x(_x), y(_y) {}
    Vector (Segment a) : x(a.f.x - a.s.x), y(a.f.y - a.s.y) {}
    Vector (Point a, Point b) : x(b.x - a.x), y(b.y - a.y) {}
    double length();
    void multiKoef(double k);
    static double vProduct (Point a, Point b, Point c);
    static double vProduct (Vector a, Vector b);
    static double sProduct (Vector a, Vector b);
};

struct Circle
{
    Point o;
    double r;
    Circle() {}
    Circle(Point _o, double _r): o(_o), r(_r) {}
    double square ();
    double perimeter ();
    bool innerPoint (Point a);
    Point FromAng (double ang);
    double getAng (Point a);
    static bool intersect (Circle a, Circle b);
    static bool intersect (Circle a, Line b);
    static pair<Point, Point> getCommon (Circle a, Line b);
    static pair<Point, Point> getCommon (Circle a, Circle b);
    static pair<Point, Point> getCommon (Circle a, Segment b);
};

struct Polygon
{
    int n;
    vector<Point> points;
    Polygon () {}
    Polygon (int _n) {
        n = _n;
        points.resize(n);
    }
    void push_back(Point a);
    double square();
    double perimeter ();
    bool innerPoint (Point a);
    vector<Segment> Sides();
    Polygon convex_hull ();
    static Polygon inter_pt (Polygon a, Polygon b);
    static Polygon intersect(Polygon a, Polygon b);
    static Polygon unionPoly (Polygon a, Polygon b);
    static Polygon difference (Polygon a, Polygon b);
    static pair<Polygon, Polygon> symmDiff (Polygon a, Polygon b);

    static Polygon inter_pt (Polygon a, Circle b);
    static Polygon intersect(Polygon a, Circle b);
    static Polygon unionPoly (Polygon a, Circle b);
    static Polygon difference (Polygon a, Circle b);
    static pair<Polygon, Polygon> symmDiff (Polygon a, Circle b);
};


bool comp_x (Point a, Point b);
bool comp_y (Point a, Point b);
bool inTriangle (Point o, Point a, Point b, Point c);


const Point InfPt = Point(InfL * 1.0, InfL * 1.0);

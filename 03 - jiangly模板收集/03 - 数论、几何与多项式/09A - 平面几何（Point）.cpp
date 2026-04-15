#include<bits/stdc++.h>
using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

using ld = long double;
constexpr ld eps = 1e-9;

template<class T>int sign(T x){
    if(x<-eps) return -1;
    else if(x>eps) return 1;
    else return 0;
}

template<class T>int small(T a,T b){
    if(sign(a-b)==-1) return 1;
    else return 0;
}

template<class T>int smallequal(T a,T b){
    if(sign(a-b)<=0) return 1;
    else return 0;
}

template<class T>int big(T a,T b){
    if(sign(a-b)==1) return 1;
    else return 0;
}

template<class T>int bigequal(T a,T b){
    if(sign(a-b)>=0) return 1;
    else return 0;
}

template<class T>int equal(T a,T b){
    if(sign(a-b)==0) return 1;
    else return 0;
}

template<class T>
struct Point {
    T x;
    T y;
    Point(const T &x_ = 0, const T &y_ = 0) : x(x_), y(y_) {}
    
    
    template<class U>
    operator Point<U>() {
        return Point<U>(U(x), U(y));
    }
    Point &operator+=(const Point &p) & {
        x += p.x;
        y += p.y;
        return *this;
    }
    Point &operator-=(const Point &p) & {
        x -= p.x;
        y -= p.y;
        return *this;
    }
    Point &operator*=(const T &v) & {
        x *= v;
        y *= v;
        return *this;
    }
    Point &operator/=(const T &v) & {
        x /= v;
        y /= v;
        return *this;
    }
    Point operator-() const {
        return Point(-x, -y);
    }
    friend Point operator+(Point a, const Point &b) {
        return a += b;
    }
    friend Point operator-(Point a, const Point &b) {
        return a -= b;
    }
    friend Point operator*(Point a, const T &b) {
        return a *= b;
    }
    friend Point operator/(Point a, const T &b) {
        return a /= b;
    }
    friend Point operator*(const T &a, Point b) {
        return b *= a;
    }
    friend std::istream &operator>>(std::istream &is, Point &p) {
        return is >> p.x >> p.y;
    }
    friend std::ostream &operator<<(std::ostream &os, const Point &p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }


    friend bool operator==(const Point &a, const Point &b) {
        return equal(a.x,b.x) && equal(a.y,b.y);
    }
    friend bool operator<(const Point &a, const Point &b) {
        return small(a.x,b.x)||(equal(a.x,b.x)&&small(a.y,b.y));
    }
    friend bool operator>(const Point &a, const Point &b) {
        return big(a.x,b.x)||(equal(a.x,b.x)&&big(a.y,b.y));
    }
};

template<class T>
struct Line {
    Point<T> a;
    Point<T> b;
    Line(const Point<T> &a_ = Point<T>(), const Point<T> &b_ = Point<T>()) : a(a_), b(b_) {}
};

template<class T>
T dot(const Point<T> &a, const Point<T> &b) {
    return a.x * b.x + a.y * b.y;
}

template<class T>
T cross(const Point<T> &a, const Point<T> &b) {
    return a.x * b.y - a.y * b.x;
}

template<class T>
T square(const Point<T> &p) {
    return dot(p, p);
}

template<class T>
double length(const Point<T> &p) {
    return std::sqrt(square(p));
}

template<class T>
double length(const Line<T> &l) {
    return length(l.a - l.b);
}

template<class T>
Point<T> normalize(const Point<T> &p) {
    return p / length(p);
}

template<class T>
bool parallel(const Line<T> &l1, const Line<T> &l2) {
    return equal(cross(l1.b - l1.a, l2.b - l2.a),T(0));
}

template<class T>
double distance(const Point<T> &a, const Point<T> &b) {
    return length(a - b);
}

template<class T>
double distancePL(const Point<T> &p, const Line<T> &l) {
    return std::abs(cross(l.a - l.b, l.a - p)) / length(l);
}

template<class T>
double distancePS(const Point<T> &p, const Line<T> &l) {
    if (dot(p - l.a, l.b - l.a) < 0) {
        return distance(p, l.a);
    }
    if (dot(p - l.b, l.a - l.b) < 0) {
        return distance(p, l.b);
    }
    return distancePL(p, l);
}

template<class T>
Point<T> rotate(const Point<T> &a) {
    return Point(-a.y, a.x);
}

template<class T>
int sgn(const Point<T> &a) {
    return big(a.y , T(0)) || (equal(a.y , T(0)) && big(a.x , T(0))) ? 1 : -1;
}

template<class T>
bool pointOnLineLeft(const Point<T> &p, const Line<T> &l) {
    return big(cross(l.b - l.a, p - l.a) , 0);
}

template<class T>
Point<T> lineIntersection(const Line<T> &l1, const Line<T> &l2) {
    return l1.a + (l1.b - l1.a) * (cross(l2.b - l2.a, l1.a - l2.a) / cross(l2.b - l2.a, l1.a - l1.b));
}

template<class T>
bool pointOnSegment(const Point<T> &p, const Line<T> &l) {
    return equal(cross(p - l.a, l.b - l.a),T(0)) && smallequal(std::min(l.a.x, l.b.x) , p.x) && smallequal(p.x , std::max(l.a.x, l.b.x))
        && smallequal(std::min(l.a.y, l.b.y) , p.y) && smallequal(p.y , std::max(l.a.y, l.b.y));
}

template<class T>
bool pointInPolygon(const Point<T> &a, const std::vector<Point<T>> &p) {
    int n = p.size();
    for (int i = 0; i < n; i++) {
        if (pointOnSegment(a, Line(p[i], p[(i + 1) % n]))) {
            return true;
        }
    }
    
    int t = 0;
    for (int i = 0; i < n; i++) {
        auto u = p[i];
        auto v = p[(i + 1) % n];
        if (u.x < a.x && bigequal(v.x , a.x) && pointOnLineLeft(a, Line(v, u))) {
            t ^= 1;
        }
        if (bigequal(u.x , a.x) && v.x < a.x && pointOnLineLeft(a, Line(u, v))) {
            t ^= 1;
        }
    }
    
    return t == 1;
}

// 0 : not intersect
// 1 : strictly intersect
// 2 : overlap
// 3 : intersect at endpoint
template<class T>
std::tuple<int, Point<T>, Point<T>> segmentIntersection(const Line<T> &l1, const Line<T> &l2) {
    if (std::max(l1.a.x, l1.b.x) < std::min(l2.a.x, l2.b.x)) {
        return {0, Point<T>(), Point<T>()};
    }
    if (std::min(l1.a.x, l1.b.x) > std::max(l2.a.x, l2.b.x)) {
        return {0, Point<T>(), Point<T>()};
    }
    if (std::max(l1.a.y, l1.b.y) < std::min(l2.a.y, l2.b.y)) {
        return {0, Point<T>(), Point<T>()};
    }
    if (std::min(l1.a.y, l1.b.y) > std::max(l2.a.y, l2.b.y)) {
        return {0, Point<T>(), Point<T>()};
    }

    if (equal(cross(l1.b - l1.a, l2.b - l2.a) , T(0))) {
        if (!equal(l1.b - l1.a, l2.a - l1.a , T(0))) {
            return {0, Point<T>(), Point<T>()};
        } else {
            auto maxx1 = std::max(l1.a.x, l1.b.x);
            auto minx1 = std::min(l1.a.x, l1.b.x);
            auto maxy1 = std::max(l1.a.y, l1.b.y);
            auto miny1 = std::min(l1.a.y, l1.b.y);
            auto maxx2 = std::max(l2.a.x, l2.b.x);
            auto minx2 = std::min(l2.a.x, l2.b.x);
            auto maxy2 = std::max(l2.a.y, l2.b.y);
            auto miny2 = std::min(l2.a.y, l2.b.y);
            Point<T> p1(std::max(minx1, minx2), std::max(miny1, miny2));
            Point<T> p2(std::min(maxx1, maxx2), std::min(maxy1, maxy2));
            if (!pointOnSegment(p1, l1)) {
                std::swap(p1.y, p2.y);
            }
            if (p1 == p2) {
                return {3, p1, p2};
            } else {
                return {2, p1, p2};
            }
        }
    }
    auto cp1 = cross(l2.a - l1.a, l2.b - l1.a);
    auto cp2 = cross(l2.a - l1.b, l2.b - l1.b);
    auto cp3 = cross(l1.a - l2.a, l1.b - l2.a);
    auto cp4 = cross(l1.a - l2.b, l1.b - l2.b);
    
    if ((cp1 > 0 && cp2 > 0) || (cp1 < 0 && cp2 < 0) || (cp3 > 0 && cp4 > 0) || (cp3 < 0 && cp4 < 0)) {
        return {0, Point<T>(), Point<T>()};
    }
    
    Point p = lineIntersection(l1, l2);
    if (!equal(cp1,T(0)) && !equal(cp2,T(0)) && !equal(cp3,T(0)) && !equal(cp4,T(0))) {
        return {1, p, p};
    } else {
        return {3, p, p};
    }
}

template<class T>
double distanceSS(const Line<T> &l1, const Line<T> &l2) {
    if (std::get<0>(segmentIntersection(l1, l2)) != 0) {
        return 0.0;
    }
    return std::min({distancePS(l1.a, l2), distancePS(l1.b, l2), distancePS(l2.a, l1), distancePS(l2.b, l1)});
}

template<class T>
bool segmentInPolygon(const Line<T> &l, const std::vector<Point<T>> &p) {
    int n = p.size();
    if (!pointInPolygon(l.a, p)) {
        return false;
    }
    if (!pointInPolygon(l.b, p)) {
        return false;
    }
    for (int i = 0; i < n; i++) {
        auto u = p[i];
        auto v = p[(i + 1) % n];
        auto w = p[(i + 2) % n];
        auto [t, p1, p2] = segmentIntersection(l, Line(u, v));
        
        if (t == 1) {
            return false;
        }
        if (t == 0) {
            continue;
        }
        if (t == 2) {
            if (pointOnSegment(v, l) && v != l.a && v != l.b) {
                if (cross(v - u, w - v) > 0) {
                    return false;
                }
            }
        } else {
            if (p1 != u && p1 != v) {
                if (pointOnLineLeft(l.a, Line(v, u))
                    || pointOnLineLeft(l.b, Line(v, u))) {
                    return false;
                }
            } else if (p1 == v) {
                if (l.a == v) {
                    if (pointOnLineLeft(u, l)) {
                        if (pointOnLineLeft(w, l)
                            && pointOnLineLeft(w, Line(u, v))) {
                            return false;
                        }
                    } else {
                        if (pointOnLineLeft(w, l)
                            || pointOnLineLeft(w, Line(u, v))) {
                            return false;
                        }
                    }
                } else if (l.b == v) {
                    if (pointOnLineLeft(u, Line(l.b, l.a))) {
                        if (pointOnLineLeft(w, Line(l.b, l.a))
                            && pointOnLineLeft(w, Line(u, v))) {
                            return false;
                        }
                    } else {
                        if (pointOnLineLeft(w, Line(l.b, l.a))
                            || pointOnLineLeft(w, Line(u, v))) {
                            return false;
                        }
                    }
                } else {
                    if (pointOnLineLeft(u, l)) {
                        if (pointOnLineLeft(w, Line(l.b, l.a))
                            || pointOnLineLeft(w, Line(u, v))) {
                            return false;
                        }
                    } else {
                        if (pointOnLineLeft(w, l)
                            || pointOnLineLeft(w, Line(u, v))) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

template<class T>
std::vector<Point<T>> hp(std::vector<Line<T>> lines) {
    std::sort(lines.begin(), lines.end(), [&](auto l1, auto l2) {
        auto d1 = l1.b - l1.a;
        auto d2 = l2.b - l2.a;
        
        if (sgn(d1) != sgn(d2)) {
            return sgn(d1) == 1;
        }
        
        return cross(d1, d2) > 0;
    });
    
    std::deque<Line<T>> ls;
    std::deque<Point<T>> ps;
    for (auto l : lines) {
        if (ls.empty()) {
            ls.push_back(l);
            continue;
        }
        
        while (!ps.empty() && !pointOnLineLeft(ps.back(), l)) {
            ps.pop_back();
            ls.pop_back();
        }
        
        while (!ps.empty() && !pointOnLineLeft(ps[0], l)) {
            ps.pop_front();
            ls.pop_front();
        }
        
        if (equal(cross(l.b - l.a, ls.back().b - ls.back().a),T(0))) {
            if (dot(l.b - l.a, ls.back().b - ls.back().a) > 0) {
                
                if (!pointOnLineLeft(ls.back().a, l)) {
                    assert(ls.size() == 1);
                    ls[0] = l;
                }
                continue;
            }
            return {};
        }
        
        ps.push_back(lineIntersection(ls.back(), l));
        ls.push_back(l);
    }
    
    while (!ps.empty() && !pointOnLineLeft(ps.back(), ls[0])) {
        ps.pop_back();
        ls.pop_back();
    }
    if (ls.size() <= 2) {
        return {};
    }
    ps.push_back(lineIntersection(ls[0], ls.back()));
    
    return std::vector(ps.begin(), ps.end());
}


template<class T>double Area(vector<Point<T>>pt){
    int n=pt.size();

    double res=0;
    for(int i=0;i<n;++i){
        res+=cross(pt[i],pt[(i+1)%n]);
    }

    return abs(res)/2;
}

//点数为凸包点数+1
template<class T>vector<Point<T>>Andrew(vector<Point<T>>pt){
    sort(pt.begin(),pt.end());

    int n=pt.size();
    int cnt=1;
    vector<Point<T>>con;
    for(int i=0;i<n;++i){
        while(con.size()>cnt){
            int have=con.size();

            auto p0=pt[i];
            auto p1=con[have-1];
            auto p2=con[have-2];
            if(small(cross(p1-p2,p0-p2),T(0))) con.pop_back();
            else break;
        }
        con.push_back(pt[i]);
    }
    cnt=con.size();

    for(int i=n-2;i>=0;--i){
        while(con.size()>cnt){
            int have=con.size();

            auto p0=pt[i];
            auto p1=con[have-1];
            auto p2=con[have-2];
            if(small(cross(p1-p2,p0-p2),T(0))) con.pop_back();
            else break;
        }
        con.push_back(pt[i]);
    }
    cnt=con.size();

    return con;
}

//直径的平方
template<class T>T Diameter(vector<Point<T>>pt){
    auto con=Andrew(pt);
    int cnt=con.size();

    if(cnt==3) return square(con[0]-con[1]);
    
    T res=0;
    for(int i=1,j=0;i<cnt;++i){
        while(1){
            vector<Point<T>>pt1;
            pt1.push_back(con[i-1]);
            pt1.push_back(con[i]);
            pt1.push_back(con[(j+1)%cnt]);

            vector<Point<T>>pt2;
            pt2.push_back(con[i-1]);
            pt2.push_back(con[i]);
            pt2.push_back(con[j%cnt]);

            if(bigequal(Area(pt1)-Area(pt2),0.0)) ++j;
            else break;
        }

        res=max(square(con[i-1]-con[j%cnt]),res);
        res=max(square(con[i]-con[j%cnt]),res);
    }

    return res;
}

void solve(){
    int n;
    cin>>n;
    vector pt(n,Point<int>());
    for(int i=0;i<n;++i) cin>>pt[i];

    cout<<Diameter(pt)<<"\n";
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T=1;
    //cin>>T;
    while(T--) solve();

    return 0;
}

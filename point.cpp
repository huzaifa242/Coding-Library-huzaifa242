/**
 * Usage point<int/double> p1;
 * To know cw or ccw of vector AB and CD
 * (B-A).cross(D-C)
 * if cross < 0 then AB has more theta with positive x axis than CD
 * if cross > 0 then AB has less theta with positive x axis than CD
 * if cross == 0 then AB and CD are collinear
 */
const double eps = 1e-15;
double to_rad(double deg) {
	return deg * acos(-1.0) / 180.0;
}
double to_deg(double rad) {
	return rad * 180.0 / acos(-1.0);
}
bool EQ(double a, double b) {
	return fabs(a - b) <= eps;
}
bool LT(double a, double b) {
	return a < b - eps;
}

class point {
	public:
	double x, y;
	point() : x(0), y(0) {}
	point(double _x, double _y) : x(_x), y(_y) {}
	point(point &p) : x(p.x), y(p.y) {}
	bool operator < (const point &p) const {
		return EQ(x, p.x) ? LT(y, p.y) : LT(x, p.x);
	}
	bool operator > (const point &p) const {
		return EQ(x, p.x) ? LT(p.y, y) : LT(p.x, x);
	}
	bool operator == (const point &p) const {
		return EQ(x, p.x) && EQ(y, p.y);
	}
	bool operator != (const point &p) const {
		return !(*this == p);
	}
	bool operator <= (const point &p) const {
		return !(*this > p);
	}
	bool operator >= (const point &p) const {
		return !(*this < p);
	}
	point operator + (const point &p) const {
		return point(x + p.x, y + p.y);
	}
	point operator - (const point &p) const {
		return point(x - p.x, y - p.y);
	}
	point operator + (double v) const {
		return point(x + v, y + v);
	}
	point operator - (double v) const {
		return point(x - v, y - v);
	}
	point operator * (double v) const {
		return point(x * v, y * v); 
	}
	point operator / (double v) const {
		return point(x / v, y / v);
	}
	point& operator += (const point &p) {
		x += p.x; y += p.y; return *this;
	}
	point& operator -= (const point &p) {
		x -= p.x; y -= p.y; return *this;
	}
	point& operator += (double v) {
		x += v; y += v; return *this;
	}
	point& operator -= (double v) {
		x -= v; y -= v; return *this;
	}
	point& operator *= (double v) {
		x *= v; y *= v; return *this;
	}
	point& operator /= (double v) {
		x /= v; y /= v; return *this;
	}
	friend point operator + (double v, const point &p) {
		return p + v; 
	}
	friend point operator * (double v, const point &p) {
		return p * v;
	}
	// Distance and angle from Origin
	double sqmag() const {
		return x * x + y * y;
	}
	double mag() const {
		return sqrt(sqmag());
	}
	double arg() const {
		return atan2(y, x);
	}
	double dot(const point &p) const {
		return x * p.x + y * p.y;
	}
	double cross(const point &p) const {
		return x * p.y - y * p.x;
	}
	//projection of this vector on vector p
	//component of this vector along vector p
	double proj(const point &p) const {
		return dot(p) / p.mag();
	}
	//returns the proportional unit vector
	point unit_vector() const {
		return EQ(x, 0) && EQ(y, 0)? point(0, 0): point(x, y) / mag();
	}
	//returns (x,y) rotated t radians clockwise about Origin.
	point rotateCW(double t) {
		return point(x * cos(t) + y * sin(t), y * cos(t) - x * sin(t));
	}
	//returns (x,y) rotated t radians anti-clockwise about Origin.
	point rotateCCW(double t) {
		return point(x * cos(t) - y * sin(t), x * sin(t) + y * cos(t));
	}
	//returns (x,y) rotated t radians clockwise about Point P.
	point rotateCW(const point &p,double t) {
		return (*this - p).rotateCW(t) + p;
	}
	//returns (x,y) rotated t radians anti-clockwise about Point P.
	point rotateCCW(const point &p,double t) {
		return (*this - p).rotateCCW(t) + p;
	} 
	//returns (x,y) reflected along point P
	point reflect(const point &p) {
		return point(2 * p.x - x, 2 * p.y - y);
	}
	//returns (x,y) reflected along line passing through P and Q
	point reflect(const point &p, const point &q){
		if (p == q)
			return reflect(p);
		point r = (*this - p), s = q - p;
		r = point(r.x * s.x + r.y * s.y, r.x * s.y - r.y * s.x) / s.sqmag();
		r = point(r.x * s.x - r.y * s.y, r.x * s.y + r.y * s.x) + p;
		return r;
	}

	ostream& operator << (ostream &out, const point &p) {
		return out << "(" << (fabs(p.x) < EPS ? 0 : p.x) << ","
		<< (fabs(p.y) < EPS ? 0 : p.y) << ")"; 
	}
};

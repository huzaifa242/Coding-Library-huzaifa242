/**
 * Usage for array
 * vector<convexhull_trick_semi> poly(MAX,convexhull_trick_semi(false));
 * Usage for Single
 * convexhull_trick_semi poly(false);
 * SEVERE NOTE m is actual m(not modified one for min/max adjustment)
 * m must be descending for min
 * m must be ascending for max
 * check for c if m(slopes) are equal
 */
class convexhull_trick_semi{
	public:
	static const int inf = 1e18;
	private:
	class line {
		private:
		int m, c;// y= mx+c
		long double xlft; //Stores the intersection wiith previous line in the convex hull. First line has -inf
		public:
		explicit line(int _m = 0, int _c = 0){
			m = _m;
			c = _c;
			xlft = -inf;
		}
		int getc() const {
			return c;
		}
		int getm() const {
			return m;
		}
		void setxlft(long double lf) {
			xlft = lf;
		}
		long double getxlft() const {
			return xlft;
		}
		int gety( int x) const {
			return m * x + c;
		}
		bool isparallel(line ll) const {
			return m == ll.m;
		}
		long double intersectX(line ll) const {
			return isparallel(ll)? inf: (1.0 * (c - ll.c)) / (ll.m - m);
		}
	};
	bool maxQ;
	vector <line> hull;
	public:
	convexhull_trick_semi(bool mq) {
		maxQ = mq;
	}
	bool useless(line l1, line l2, line l3) {
		return l1.intersectX(l3) <= l1.intersectX(l2);
	}
	void addline(int m,int c){
		line ll;
		if (maxQ)
			ll = line(-m, -c);
		else
			ll = line(m, c);
		while (hull.size() >= 2 && useless(hull[hull.size() - 2], hull[hull.size() - 1], ll))
			hull.pop_back();
		if (hull.size()) {
			long double dst = hull.back().intersectX(ll); 
			ll.setxlft(dst);
		}
		hull.push_back(ll);
	}
	int query(int x) {
		int ll = 0, rr = hull.size() - 1, aa = 0;
		while (ll <= rr){
			int mm = (ll + rr) / 2;
			if (hull[mm].getxlft() <= (1.0 * x)) {
				aa = mm;
				ll = mm + 1;
			} else
				rr = mm - 1;
		}
		return (maxQ? -hull[aa].gety(x): hull[aa].gety(x));
	}
};
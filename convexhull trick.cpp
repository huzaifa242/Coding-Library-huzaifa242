/**
 * Usage for array
 * vector <convexhull_trick> poly(MAX,convexhull_trick(false));
 * Usage for Single
 * convexhull_trick poly(false);
 */
class convexhull_trick {
	public:
	static const int inf = 1e18;
	private:
	class line {
		private:
		int m, c;// y= mx+c
		long double xlft; //Stores the intersection wiith previous line in the convex hull. First line has -inf
		public:
		enum qtype {noq, maxq, minq} type;
		int val;
		explicit line(int _m = 0, int _c = 0) {
			m = _m; c = _c;
			xlft = -inf;
			type = qtype::noq;
			val = 0;
		}
		int getc() const {
			return c;
		}
		int getm() const {
			return m;
		}
		void setxlft(long double lf) {
			xlft=lf;
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
		bool operator < (line ll) const	{
			if(ll.type == qtype::noq)
				return m < ll.m;
			if(ll.type == qtype::minq)
				return xlft > ( 1.0 * ll.val);
			if(ll.type == qtype::maxq)
				return xlft < ( 1.0 * ll.val);
		}
	};
	bool maxQ;
	set <line> hull;
	typedef set <line>::iterator suto;
	public:
	convexhull_trick(bool mq) {
		maxQ = mq;
	}
	bool hasprev(suto it) {
		return it != hull.begin();
	}
	bool hasnext(suto it) {
		return it != hull.end() && next(it) != hull.end();
	}
	bool useless(line l1, line l2, line l3) {
		return l1.intersectX(l3) <= l1.intersectX(l2);
	}
	bool useless(suto it){
		return hasprev(it) && hasnext(it) &&
				((maxQ && useless(*prev(it), *it, *next(it)))
				|| (!maxQ && useless(*next(it), *it, *prev(it))));
	}
	suto updateleftborder(suto it) {
		if ((maxQ && !hasprev(it)) || (!maxQ && !hasnext(it)))
			return it;
		long double dst = it->intersectX((maxQ? *prev(it): *next(it)));
		line tmp(*it);
		it = hull.erase(it);
		tmp.setxlft(dst);
		it = hull.insert(it,tmp);
		return it;
	}
	void addline(int m, int c) {
		line ll = line(m,c);
		suto it = hull.lower_bound(ll);
		//For Parallel lines emove useless ones
		if (it != hull.end() && ll.isparallel(*it)) {
			if ((maxQ && it->getc() < c) || (!maxQ && it->getc() > c))
				it = hull.erase(it);
			else
				return;
		}
		it = hull.insert(it,ll);
		if (useless(it)) {
			hull.erase(it);
			return;
		}
		//Remove lines which are useless after inserting
		while (hasprev(it) && useless(prev(it)))
			hull.erase(prev(it));
		while (hasnext(it) && useless(next(it)))
			hull.erase(next(it));
		//Update the left Border
		it = updateleftborder(it);
		if (hasprev(it))
			updateleftborder(prev(it));
		if (hasnext(it))
			updateleftborder(next(it));
	}
	int query(int x) {
		line ll;
		ll.val = x;
		ll.type = maxQ? (line::qtype::maxq): (line::qtype::minq);
		suto reqline = hull.lower_bound(ll);
		if (maxQ)
			reqline--;
		return reqline->gety(x);
	}
};
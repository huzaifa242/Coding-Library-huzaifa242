/**
 * For cross we talk about AB and AC vector
 * ccw if cross()>0 cw if cross()<0 collinear if cross()==0
 * Returns a list of points on the convex hull in counter-clockwise order.
 */
typedef pair <int,int> point;

int cross(point &a, point &b, point &c){
	return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
}

vector <point> convex_hull(vector <point> &p){
	int n = p.size(), k = 0;
	if (n <= 3)
		return p;
	vector <point> hull(2 * n);
	sort(p.begin(), p.end());
	for (int i = 0; i < n; ++i) {
		while (k >= 2 && cross(hull[k - 2], hull[k - 1], p[i]) <= 0)
			k--;
		hull[k++] = p[i];
	}
	for (int i = n - 1, j = k + 1; i > 0; --i) {
		while (k >= j && cross(hull[k - 2], hull[k - 1], p[i - 1]) <= 0)
			k--;
		hull[k++] = p[i - 1];
	}
	hull.resize(k - 1);
	//Note: the last point in the returned list is the same as the first one.
	if (hull[0] == hull.back() && hull.size() > 1)
		hull.pop_back();
	return hull;
}
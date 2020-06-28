/**
 *Usage find_closest()
 *dst has square of minimum distance
 *best has the id of closest pair of points
 */
struct point {
	int x, y, id;
	point operator - (point a){ 
		return {x - a.x, y - a.y};
	}
	int distance(){
		return x * x + y * y;
	}
};

vector <point> pt;
int dst;
pair <int,int> best;

void comp_ans(point u, point v) {
	if ((u - v).distance() < dst) {
		dst = (u - v).distance();
		best = {u.id, v.id};
	}
}

void closest_points(int l,int r) {
	if(l >= r)
		return;
	int m = (l + r) / 2LL;
	closest_points(l, m);
	closest_points(m + 1, r);
	vector <point> tp;
	for (int i = l; i <= r; ++i){
		if (point{pt[i].x - pt[m].x, 0}.distance() < dst){
			for (int j = (int)tp.size() - 1; j >= 0 && point{0, pt[i].y - tp[j].y}.distance() < dst; --j)
				comp_ans(pt[i], tp[j]);
			tp.push_back(pt[i]);
		}
	}
}

void find_closest() {
	dst = LLONG_MAX;
	best = {-1, -1};
	auto by_x = [&](point u, point v) {
		return u.x < v.x || (u.x == v.x && u.y < v.y);
	};

	auto by_y = [&](point u, point v) {
		return u.y < v.y || (u.y == v.y && u.x < v.x);
	};

	auto by_id = [&](point u, point v) {
		return u.id < v.id;
	};
	sort(pt.begin(), pt.end(), by_y);
	closest_points(0, pt.size() - 1);
	sort(pt.begin(), pt.end(), by_id);
}

/**
 * sort by polar angle in counter-clockwise direction
 * for clockwise change the < to >
 * atan2(y,x) gives the angle from positive x-axis
 * handle negative angles carefully
 */
auto polarangle = [&](point a, point b, point c) {
	return atan2(b.y - a.y, b.x - a.x) < atan2(c.y - a.y, c.x - a,x);
};
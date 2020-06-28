/**
 * When using for Tree label vertices in order of visit
 * Don't just depend on parent it gives WA
 */
struct info {
	info *left, *right;
	int val;
	info(int v) {
		left = nullptr;
		right = nullptr;
		//inits
		val = v;
	}
	info(info* l, info* r) {
		val = 0;
		//merge logic
		if (l != nullptr) {
			left = l;
			val += left->val;
		}
		if (r != nullptr) {
			right = r;
			val += right->val;
		}
	}
};
class persistent_tree {
	private:
	vector <info*> roots;
	info* build(int a[], int l, int r) {
		if (l > r)
			return nullptr;
		if (l == r)
			return new info(a[l]);
		int m = (l + r) / 2;
		return new info(build(a, l, m), build(a, m + 1, r));
	}
	info* update(info* node, int l, int r, int id, int z) {
		if (l > r)
			return nullptr;
		if (l == r) {
			//Do correct update here
			return new info(z);
		}
		int m = (l + r) / 2;
		if (id <= m)
			return new info(update(node->left, l, m, id, z), node->right);
		else
			return new info(node->left, update(node->right, m + 1, r, id, z));
	}
	info* query(info* node, int l, int r, int x, int y) {
		if (l > r || x > r || y < l)
			return nullptr;
		if (l >= x && r <= y)
			return node;
		int m = (l + r) / 2;
		if (m >= y)
			return query(node->left, l, m, x, y);
		else if (m < x)
			return query(node->right, m + 1, r, x, y);
		else
			return new info(query(node->left, l, m, x, y), query(node->right, m + 1, r, x, y));
	}
	public:
	persistent_tree(){
		roots.push_back(build(a, 0, n - 1));
	}
	void update(int rt, int l, int r, int id, int z) {
		if (rt >= roots.size())
			return;
		roots.push_back(update(roots[rt], l, r, id, z));
	}
	info query(int rt, int l, int r, int x, int y) {
		if (rt >= roots.size()) {
			info grbg;//set garbage
			return grbg;
		}
		return *(query(roots[rt], l, r, x, y));
	}
};
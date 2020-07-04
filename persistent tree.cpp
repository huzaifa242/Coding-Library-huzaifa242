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
template <typename T>
class persistent_tree {
	private:
	vector <T*> roots;
	T* build(int a[], int l, int r) {
		if (l > r)
			return nullptr;
		if (l == r)
			return new T(a[l]);
		int m = (l + r) / 2;
		return new T(build(a, l, m), build(a, m + 1, r));
	}
	T* update(T* node, int l, int r, int id, int z) {
		if (l > r)
			return nullptr;
		if (l == r) {
			//Do correct update here
			return new T(z);
		}
		int m = (l + r) / 2;
		if (id <= m)
			return new T(update(node->left, l, m, id, z), node->right);
		else
			return new T(node->left, update(node->right, m + 1, r, id, z));
	}
	T* query(T* node, int l, int r, int x, int y) {
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
			return new T(query(node->left, l, m, x, y), query(node->right, m + 1, r, x, y));
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
	T query(int rt, int l, int r, int x, int y) {
		if (rt >= roots.size()) {
			T grbg;//set garbage
			return grbg;
		}
		return *(query(roots[rt], l, r, x, y));
	}
};
/**
 * fenwick_tree Tree(Binary Indexed Tree)
 * Usage fenwick_tree<type> f1, f2(100);
 */
template <typename T>
class fenwick_tree {
	private:
	vector <T> bit;
	int n;
	public:
	fenwick_tree() {
		n = MAX;
		bit.assign(n, {0});
	}
	fenwick_tree(int size) {
		n = size;
		bit.assign(n, {0});
	}
	//Point Update
	void update(int id, T z) {
		while(id <= n){
			bit[id] = bit[id] + z;
			id += (id & (-id));
		}
	}
	T query(int id) {
		//Initialize answer variable
		T ans={0};
		while(id > 0) {
			ans = ans + bit[id];
			id -= (id & (-id));
		}
		return ans;
	}
};
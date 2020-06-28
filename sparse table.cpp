/**
 * Sparse Table
 * Usage sparse_table<type> s1(merge_function,size,init_value)
 * Usage sparse_table<type> s1(merge_function)
 */
const int lgs = 20;
template <typename T>
class sparse_table {
	private:
	vector <vector <T> > sprs;
	int n;
	function <T(T,T)> merge;
	public:
	sparse_table(auto fnc) {
		merge = func;
	}
	sparse_table(auto fnc, int size, T val) {
		n = size;
		merge = func;
		sprs.assign(n, vector <T> (lgs, {val}));
	}
	void setsize(int size, T val) {
		n = size;
		sprs.assign(n, vector <T> (lgs, {val}));
	}
	void build() {
		for (int i = 0; i < n; ++i)
		sprs[i][0] = i;//initialize value
		for (int j = 1; j < lgs; ++j) {
			for (int i = 0; i + (1 << j) <= n; ++i) {
				sprs[i][j] = merge(sprs[i][j - 1], sprs[i + (1 << (j - 1))][j - 1]);
				//always relation between sprs[i][j-1] and sprs[i+(1<<(j-1))][j-1]
			}
		}
	}
	//for O(1) relation use this
	T query(int l, int r) {
		int i = log2(r - l + 1), j;
		return merge(sprs[l][i], sprs[r - (1 << i) + 1][i]);
	}
	//otherwise do log query using bits x=r-l+1
	T query(int l, int r) {
		T sum = {0};
		for (int j = lgs - 1; j >= 0; --j) {
			if ((1 << j) <= r - l + 1) {
				sum = merge(sum, sprs[l][j]);
				l += (1 << j);
			}
		}
	}
};
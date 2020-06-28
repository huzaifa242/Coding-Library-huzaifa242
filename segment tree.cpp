/**
 * Segment Tree
 * Usage segment_tree <type> s1(merge_function,size)
 * Usage segment_tree <type> s1(merge_function)
 */
struct info {
	// node structure of segment tree
	bool lz;//for Lazy Propogation
};
template <typename T>
class segment_tree {
	#define left_node 2 * node
	#define right_node 2 * node + 1
	private:
	vector <T> tree;
	function <T(T,T)> merge;
	public:
	segment_tree(auto fnc, int size) {
		merge = fnc;
		tree.resize(4 * size);
	}
	segment_tree(auto fnc) {
		merge = fnc;
		tree.resize(4 * MAX);
	}
	void build(int node, int l, int r) {
		//build(1,0,n-1);
		if (l > r)
			return;
		if (l == r) {
			//leaf node of segment tree
			tree[node] = //init ;
			tree[node].lz = false;
			return;
		}
		int m = (l + r) / 2;
		build(left_node, l, m);
		build(right_node, m + 1, r);
		// merging of nodes
		tree[node] = merge(tree[left_node], tree[right_node]);
		return;
	}
	//Point Update
	void update(int node, int l, int r, int id, int z) {
		//update(1,0,n-1,ind,val)
		if (l > r)
			return;
		if (l == r) {
			a[l] = z;
			tree[node] = //init;
			//leaf node of segment tree a[l]=point update id=index z=new value l,r =tree range
			return;
		}
		int m = (l + r) / 2;
		if (l <= id && id <= m)
			update(left_node, l, m, id, z);
		else
			update(right_node, m + 1, r, id, z);
		// merging of nodes
		tree[node] = merge(tree[left_node], tree[right_node]);
		return;
	}
	//Calculate Lazy Propogation
	void calclazy(int node, int l, int r, int x, int y) {
		//this function relaxes previous lazy values.
		//call same as query function
		if (!tree[node].lz)
			return;
		tree[node].lz = false;
		// Apply Lazy Logic to current node
		if (l != r) {
			tree[left_node].lz = true;
			tree[right_node].lz = true; 
			//Propogate to child
		}
		// erase lazy logic for current node
		return;	
	}
	//Range Update
	void updateRange(int node, int l, int r, int x, int y, int z) {
		//update(1,a,0,n-1,left,right,val)
		calclazy(node, l, r, x, y);
		if (l > r || x > r || y < l)
			return ; //out of range
		if (l >= x && r <= y) {
			tree[node].lz = true;
			//Apply Lazy Logic to current Node
			calclazy(node, l, r, x, y);
			return;
		}
		int m = (l + r) / 2;
		updateRange(left_node, l, m, x, y, z);
		updateRange(right_node, m + 1, r, x, y, z);
		// merging of nodes
		tree[node] = merge(tree[left_node], tree[right_node]);
		return;
	}
	//Range Query
	T query(int node, int l, int r, int x, int y) {
		//query(1,0,n-1,left,right); left and right are query range
		//l,r=array  x,y=tree query range returns segment tree node.
		calclazy(node, l, r, x, y);// Only for Lazy Propogation
		if (l > r || x > r || y < l) {
			T grbg;
			//set garbge value for grbg
			return grbg;
		}
		if (l >= x && r <= y)
			return tree[node];
		int m = (l + r) / 2;
		if (m >= y)
			return query(left_node, l, m, x, y);
		else if (m < x)
			return query(right_node, m + 1, r, x, y); 
		return merge(query(left_node, l, m, x, y), query(right_node, m + 1, r, x, y));
	}
	#undef left_node
	#undef right_node 
};
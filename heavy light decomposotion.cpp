/**
 * Usage heavylight_decomposition h1(mrg)
 * mrg is merge function of segment tree;
 * Don't forget to write calc_sar() method
 * put lca first
 * then put segment tree or other datastructure
 * then continue from below;
 */
vector <int> sbsz;
class heavylight_decomposition{
	private:
	//chid is starting element of chain
	vector <int> chid, sid, sar;
	//chn[i] has all the element of the chain starting at i-th node
	vector <vector <int> > chn;
	int itr, root, n;
	// Segment tree or any other data structure
	segment_tree t1;
	void calc_sar() {
		/*------------Fill this----------*/
	}
	void getsize(int u, int p) {
		sbsz[u] = 1;
		for (auto v : adjlst[u]) {
			if (v != p) {
				getsize(v, u);
				sbsz[u] += sbsz[v];
			}
		}
	}
	void decompose(int u, int p, int id) {
		sid[u] = itr++;
		chn[id].push_back(u);
		chid[u] = id;
		int bigc = -1, mx = -1;
		for (auto v : adjlst[u]) {
			if (v != p && mx < sbsz[v]) {
				mx = sbsz[v];
				bigc = v;
			}
		}
		if (bigc != -1)
			decompose(bigc, u, id);
		for (auto v:adjlst[u])
			if (v != p && bigc != v)
				decompose(v, u, v);
	}
	//v is ancestor of u
	int query_up(int u, int v) {
		//assign proper value
		int ans;
		while (u) {//make it u!=v for edge calculation stuff
			if (chid[u] == chid[v]) {
				//both u and v are in same chain
				ans = max(ans, t1.query(1, 1, n, sid[v], sid[u]));
				return ans;//remove this for edge calculation stuff
			}
			ans = max(ans, t1.query(1, 1, n, sid[chid[u]], sid[u]));
			u = up[chid[u]][0];
		}
		return ans;
	}
	//v is ancestor of u
	void update_up(int u, int v, int val) {
		while (u != v) {
			if (chid[u] == chid[v]) {
				//both u and v are in same chain
				t1.updateRange(1, sar, 1, n, sid[v], sid[u], val);
			}
			t1.updateRange(1, sar, 1, n, sid[chid[u]], sid[u],val);
			u = up[chid[u]][0];
		}
		return;
	}
	public:
	//modify constructor as per data structure
	heavylight_decomposition(auto mrg, int n, int root = 1) {
		chid.assign(n + 1, 0);
		sid.assign(n + 1, 0);
		sar.assign(n + 1, 0);
		sbsz.assign(n + 1, 0);
		chn.assign(n + 1, vector <int> (0));
		t1=segment_tree(mrg);
		itr = 1;
		getsize(root, 0);
		pre_lca(root);
		decompose(root, 0, root);
		// assign values in sar[] to builld Range data structure
		calc_sar();
		//Build tree
		t1.build(1, sar, 1, n);
	}
	int query(int u, int v) {
		int luv = lca(u, v);
		int pu = query_up(u, luv);
		int pv = query_up(v, luv);
		return max(pu, pv);
	}
	//Point Update 
	void update(int u, int val) {
		t1.update(1, sar, 1, n, u, val);
	}
	//Range Update
	void updateRange(int u, int v, int val) {
		int luv = lca(u, v);
		update_up(u, luv, val);
		update_up(v, luv, val);
		return;
	}
};
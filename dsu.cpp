/**
 *Find parent is post order. i.e. first  reaches
 * Disjoint Set Union
 * DON'T FORGET TO INITIALIZE PARENT
 * in union_all(u,v) v is joined into u.
  representative element, then it taues the value
  and while returning it updates corresponding children
  1->2->3->4->5     first it reaches 5 then updates par[4]=5
  then updates par[3]=par[4](which is now 5)
	void find_par(int u){
		if(par[par[u]]==u)//reached representative element now update will start
		return;
		find_par(par[u]);// grandparent update. Parent is not
		// Condition for Grandparent updated and not parent
		par[u]=par[par[u]];//Parent Updated
		// Condition when parent is Updated
	}
 * Usage dsu d1(x)
 */
class dsu {
	private:
	vector <int> par,sz;
	void find_par(int u) {
		if(par[par[u]] == u)
			return;
		find_par(par[u]);
		par[u] = par[par[u]];
	}
	public:
	int connected;
	dsu() {}
	dsu(int n) {
		par.resize(n + 1);
		sz.assign(n + 1, 1);
		iota(par.begin(), par.end(), 0);
		connected = n;
	}
	int get_par(int u) {
		find_par(u);
		return par[u];
	}
	int get_size(int u) {
		return sz[get_par(u)];
	}
	void union_all(int u, int v) {
		if(get_par(u) != get_par(v)){
			connected--;
			sz[par[u]] += sz[par[par[v]]];
			sz[par[par[v]]] = 0;
		}
		par[par[v]] = par[u];
	}
};
/**
 * make version stack for new properties
 * follow comments for implementing other undo operation
 * undo is always an assignment operation hence implement it that way
 * first preserve history then change property. "ORDER is IMPORTANT"
 */
class dsu_rollback {
	private:
	vector <int> par, sz, parity;
	stack <pair <int,int> > par_version, sz_version, parity_version;
	void undo_par() {
		auto u = par_version.top();
		par_version.pop();
		par[u.x] = u.y;
	}
	void undo_sz() {
		auto u = sz_version.top();
		sz_version.pop();
		sz[u.x] = u.y;
	}
	void undo_parity() {
		auto u = parity_version.top();
		parity_version.pop();
		parity[u.x] = u.y;
	}
	public:
	int connected;
	dsu_rollback() {}
	dsu_rollback(int n) {
		par.resize(n + 1);
		sz.assign(n + 1, 1);
		parity.assign(n + 1, 0);
		iota(par.begin(), par.end(), 0);
		connected = n;
	}
	int get_par(int u) {
		return (par[u] == u? u: get_par(par[u]));
	}
	int get_size(int u) {
		return sz[get_par(u)];
	}
	int get_parity(int u) {
		return (par[u] == u? 0: parity[u] ^ get_parity(par[u]));
	}
	void union_all(int u, int v) {
		int root_u = get_par(u);
		int root_v = get_par(v);
		if (root_u != root_v) {
			if (sz[root_u] < sz[root_v]) {
				swap(u, v);
				swap(root_u, root_v);
			} 
			connected--;
			par_version.push({root_v, par[root_v]});
			sz_version.push({root_u, sz[root_u]});
			parity_version.push({root_v, parity[root_v]});
			// other_version.push({root_v, other[root_v]});
			//other[root_v] = formulate from root_u to root_v gneralisation
			parity[root_v] = get_parity(u) ^ get_parity(v) ^ 1;
			sz[root_u] += sz[root_v];
			par[root_v] = root_u;
		} else {
			if (get_parity(u) == get_parity(v)) {
				// not bipartite		
			}
		}
	}
	void rollback() {
		if (par_version.empty())
			return; 
		connected++;
		// undo_other();
		undo_sz();
		undo_par();
		undo_parity();
	}
};
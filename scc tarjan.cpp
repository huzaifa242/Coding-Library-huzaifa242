/**
 * Usage tarjan().
 * lb is number of strongly connected components
 * compo[i] in Kosaraju = compo[lb-i+1] in tarjan 
 * lbl[i] has label of each node
 * compo[i] has all the node that are strongly connected
 */
vector <vector <int> > adjlst, compo;
vector <int> low, tin, lbl;
vector <bool> inst;
int ptr, n, m, lb;
stack <int> scc;
void scc_dfs(int u, int p) {
	ptr++;
	low[u] = ptr;
	tin[u] = ptr;
	inst[u] = true;
	scc.push(u);
	for (auto v : adjlst[u]) {
		if (tin[v] == 0) {
			scc_dfs(v, u);
			low[u] = min(low[u], low[v]);
		} else if (inst[v])
			low[u] = min(low[u], tin[v]);
	}
	if (low[u] == tin[u]) {
		lb++;
		int v;
		do {
			v = scc.top();
			compo[lb].push_back(v);
			lbl[v] = lb;
			inst[v] = false;
			scc.pop();
		} while(v != u);
	}
}
int tarjan() {
	ptr = 0;lb = 0;
	compo.assign(n + 1, vector <int> (0));
	low.assign(n + 1, 0);
	tin.assign(n + 1, 0);
	lbl.assign(n + 1, 0);
	inst.assign(n + 1, 0);
	while (!scc.empty())
		scc.pop();
	for (int i = 1; i <= n; ++i)
		if (tin[i] == 0)
			scc_dfs(i, 0);
	return lb;
}
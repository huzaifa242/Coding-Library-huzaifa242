#include<bits/stdc++.h>
using namespace std;
int main()
{
	vector<string> files={
	"#huzaifa242.cpp",
	"articulation_points.cpp",
	"binary_lifting.cpp",
	"bit.cpp",
	"bridges.cpp",
	"dsu.cpp",
	"fenwick_tree.cpp",
	"floydwarshall.cpp",
	"in_builtRef.cpp",
	"lca_O(1).cpp",
	"lca_O(log).cpp",
	"lcs.cpp",
	"lis.cpp",
	"math.cpp",
	"matrix_chain_multi.cpp",
	"max_min_expression.cpp",
	"minimum_editdistance.cpp",
	"mst_kruskal.cpp",
	"mst_prim.cpp",
	"scc_kosaraju.cpp",
	"segment_tree.cpp",
	"sparse_table.cpp",
	"sqrt_decomposition.cpp",
	"sssd_bellman_ford.cpp",
	"sssd_dijkstra.cpp",
	"topological_sort.cpp"};
	freopen("huzaifa242.cpp","w",stdout);
	for(auto file:files)
	{
		char *f=const_cast<char*>(file.c_str()); 
		FILE *fl=fopen(f,"r");
		cout<<"//"<<file<<"\n";
		char ch=fgetc(fl);
		while(ch!=EOF)
		{
			cout<<ch;
			ch=fgetc(fl);
		}
		cout<<"\n";
		fclose(fl);
	}
	return 0;
}
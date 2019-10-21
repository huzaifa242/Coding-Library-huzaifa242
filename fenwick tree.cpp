//Fenwick Tree(Binary Indexed Tree)
//Usage fenwick f1, f2(100);
struct data{
	//node structure of Fenwick Tree
};
class fenwick{
	private:
	vector<data> bit;
	int n;
	public:
	fenwick(){
		n=MAX;
		bit.assign(n,{0});
	}
	fenwick(int size){
		n=size;
		bit.assign(n,{0});
	}
	//Point Update
	void update(int id, int z){
		while(id<=n){
			bit[id]= bit[id] + z;
			id+=(id & (-id));
		}
	}
	data query(int id){
		//Initialize answer variable
		data ans;
		while(id>0){
			ans= ans + bit[id];
			id-=(id & (-id));
		}
		return ans;
	}
};
//Fenwick Tree(Binary Indexed Tree)
//Usage fenwick<type> f1, f2(100);
template <typename T>
class fenwick{
	private:
	vector<T> bit;
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
	void update(int id, T z){
		while(id<=n){
			bit[id]= bit[id] + z;
			id+=(id & (-id));
		}
	}
	T query(int id){
		//Initialize answer variable
		T ans={0};
		while(id>0){
			ans= ans + bit[id];
			id-=(id & (-id));
		}
		return ans;
	}
};
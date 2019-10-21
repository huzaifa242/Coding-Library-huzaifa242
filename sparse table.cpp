//Sparse Table
//Usage sparse_table s1(n)
#define lgs 20
struct data{
	//data in sparse table
};
class sparse_table
{
	private:
	vector<vector<data> > sprs;
	int n;
	data merge(data p, data q){
		data r;
		//logic here
		return r;
	}
	public:
	sparse_table(){}
	sparse_table(int size){
		n=size;
		sprs.assign(n,vector<data>(lgs,{/*init*/}));
	}
	void setsize(int size){
		n=size;
		sprs.assign(n,vector<data>(lgs,{/*init*/}));
	}
	void build(){
		int i,j;
		for(i=0;i<n;i++)
		sprs[i][0]=//initialize value;
		for(j=1;j<lgs;j++){
			for(i=0;i+(1<<j)<=n;i++){
				sprs[i][j]= merge(sprs[i][j-1],sprs[i+(1<<(j-1))][j-1]);
				//always relation between sprs[i][j-1] and sprs[i+(1<<(j-1))][j-1]
			}
		}
	}
	data query(int l, int r){
		int i=log2(r-l+1),j;
		return min(sprs[l][i], sprs[r-(1<<i)+1][i]);//for O(1) relation use this
		//otherwise do log query using bits x=r-l+1
		int sum = 0;
		for (j=lgs-1;j>=0;j--){
			if((1<<j)<=r-l+1){
				sum+=sprs[l][j];
				l+= (1<<j);
			}
		}
	}
};
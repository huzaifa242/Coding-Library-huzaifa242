//Segment Tree
//Usage segment_tree s1(merge_function,size)
//Usage segment_tree s1(merge_function,)
struct data{
	// node structure of segment tree
	bool lz;//for Lazy Propogation
};
class segment_tree{
	private:
	vector<data> tree;
	function<data(data,data)> merge;
	public:
	segment_tree(auto fnc,int size){
		merge=fnc;
		tree.resize(4*size);
	}
	segment_tree(auto fnc){
		merge=fnc;
		tree.resize(4*MAX);
	}
	void build(int node,int l,int r){
		//build(1,a,0,n-1);
		if(l>r)
			return;
		if(l==r){
			//leaf node of segment tree
			tree[node]= //init ;
			tree[node].lz=false;
			return;
		}
		int m=(l+r)/2;
		build(2*node,l,m);
		build(2*node+1,m+1,r);
		// merging of nodes
		tree[node]=merge(tree[2*node],tree[2*node+1]);
		return;
	}
	//Point Update
	void update(int node,int l,int r,int id,int z){
		//update(1,a,0,n-1,ind,val)
		if(l>r)
			return;
		if(l==r){
			a[l]=z;
			tree[node]=//init;
			//leaf node of segment tree a[l]=point update id=index z=new value l,r =tree range
			return;
		}
		int m=(l+r)/2;
		if(l<=id && id<=m)
		update(2*node,l,m,id,z);
		else
		update(2*node+1,m+1,r,id,z);
		// merging of nodes
		tree[node]=merge(tree[2*node],tree[2*node+1]);
		return;
	}
	//Calculate Lazy Propogation
	void calclazy(int node,int l,int r,int x,int y){
		//this function relaxes previous lazy values.
		//call same as query function
		if(!tree[node].lz)
			return;
		tree[node].lz=false;
		// Apply Lazy Logic to current node
		if(l!=r){
			tree[2*node].lz=true;
			tree[2*node+1].lz = true; 
			//Propogate to child
		}
		return;	
	}
	//Range Update
	void updateRange(int node,int l,int r,int x,int y,int z){
		//update(1,a,0,n-1,left,right,val)
		calclazy(node,l,r,x,y);
		if(l>r || x>r || y<l)
			return ; //out of range
		if(l>=x && r<=y){
			tree[node].lz=true;
			//Apply Lazy Logic to current Node
			calclazy(node,l,r,x,y);
			return;
		}
		int m=(l+r)/2;
		updateRange(2*node,l,m,x,y,z);
		updateRange(2*node +1,m+1,r,x,y,z);
		// merging of nodes
		tree[node]=merge(tree[2*node],tree[2*node+1]);
		return;
	}
	//Range Query
	data query(int node,int l,int r,int x, int y){
		//query(1,0,n-1,left,right); left and right are query range
		//l,r=array  x,y=tree query range returns segment tree node.
		calclazy(node,l,r,x,y);// Only for Lazy Propogation
		if(l>r || x>r || y<l){
			data grbg;
			//set garbge value for grbg
			return grbg;
		}
		if(l>=x && r<=y)
			return tree[node];
		int m=(l+r)/2;
		if(m>=y)
			return query(2*node,l,m,x,y);
		else if(m<x)
			return query(2*node+1,m+1,r,x,y); 
		data t1=query(2*node,l,m,x,y);
		data t2=query(2*node+1,m+1,r,x,y);
		data tr;
		// merging of nodes
		tr=merge(t1,t2);
		return tr;
	}
};
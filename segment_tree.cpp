//Segment Tree
struct seg
{
    // node structure of segment tree
    bool lz;//for Lazy Propogation
}tree[4*MAX];
void build(long long int node,long long int a[],long long int l,long long int r)
{
    //build(1,a,0,n-1);
    if(l>r)
    return;
    if(l==r)
    {
        //leaf node of segment tree

        return;
    }
    long long int m=(l+r)/2;
    build(2*node,a,l,m);
    build(2*node+1,a,m+1,r);
    
    // merging of nodes

    return;
}
//Point Update
void update(long long int node,long long int a[],long long int l,long long int r,long long int id,long long int z)
{
    //update(1,a,0,n-1,ind,val)
    if(l>r)
    return;
    if(l==r)
    {
        a[l]=z;
        
        //leaf node of segment tree a[l]=point update id=index z=new value l,r =tree range

        return;
    }
    long long int m=(l+r)/2;
    if(l<=id && id<=m)
    update(2*node,a,l,m,id,z);
    else
    update(2*node+1,a,m+1,r,id,z);
    
    // merging of nodes
    
    return;
}
//Calculate Lazy Propogation
void calclazy(long long int node,long long int l,long long int r,long long int x,long long int y)
{
	//this function relaxes previous lazy values.
	//call same as query function
	if(!tree[node].lz)
	return;
	tree[node].lz=false;
	// Apply Lazy Logic to current node

	if(l!=r)
	{	tree[2*node].lz=true;
		tree[2*node+1].lz = true; 
		//Propogate to child
	}
	return;	
}
//Range Update
void updateRange(long long int node,long long int a[],long long int l,long long int r,long long int x,long long int y,long long int z)
{
    //update(1,a,0,n-1,left,right,val)
    if(l>r || x>r || y<l)
    {
        //out of range
        return ;
    }
    calclazy(node,l,r,x,y);
    if(l>=x && r<=y)
    {
    	tree[node].lz=false;
    	//Apply Lazy Logic to current Node
    	if(l!=r)
    	{
    		tree[2*node].lz=true;
    		tree[2*node+1].lz=true;
    		//Propogate to child
    	}
    	return;
    }
    int m=(l+r)/2;
    updateRange(2*node,a,l,m,x,y,z);
    updateRange(2*node +1, a,m+1,r,x,y,z);
    // merging of nodes

    return;
}
//Range Query
seg query(long long int node,long long int l,long long int r,long long int x, long long int y)
{
    //query(1,0,n-1,left,right); left and right are query range
    //l,r=array  x,y=tree query range returns segment tree node.
    if(l>r || x>r || y<l)
    {
        seg grbg;
        //set garbge value for grbg
        return grbg;
    }
    
    calclazy(node,l,r,x,y);// Only for Lazy Propogation
    
    if(l>=x && r<=y)
        return tree[node];
    long long int m=(l+r)/2;
    seg t1=query(2*node,l,m,x,y);
    seg t2=query(2*node+1,m+1,r,x,y);
    seg tr;
    
    // merging of nodes

    return tr;
}
//When using for Tree label vertices in order of visit
//Don't just depend on parent it gives WA
struct data
{
	data *left,*right;
	int val;
	data(int v)
	{
		left=NULL;
		right=NULL;
		//inits
		val=v;
	}
	data(data* l, data* r)
	{
		val=0;
		//merge logic
		if(l!=NULL)
		{
			left=l;
			val+=left->val;
		}
		if(r!=NULL)
		{
			right=r;
			val+=right->val;
		}
	}
};
class persistent_tree
{
	private:
	
	vector<data*> roots;
	data* build(int a[],int l, int r)
	{
		if(l>r)
			return NULL;
		if(l==r)
		{
			return new data(a[l]);
		}
		int m=(l+r)/2;
		return new data(build(a,l,m),build(a,m+1,r));
	}
	data* update(data* node, int l, int r, int id, int z)
	{
		if(l>r)
			return NULL;
		if(l==r)
		{
			//Do correct update here
			return new data(z);
		}
		int m=(l+r)/2;
		if(id<=m)
			return new data(update(node->left,l,m,id,z),node->right);
		else
			return new data(node->left,update(node->right,m+1,r,id,z));
	}
	data* query(data* node, int l, int r, int x, int y)
	{
		if(l>r || x>r || y<l)
			return NULL;
		if(l>=x && r<=y)
			return node;
		int m=(l+r)/2;
		if(m>=y)
			return query(node->left,l,m,x,y);
		else if(m<x)
			return query(node->right,m+1,r,x,y);
		else
			return new data(query(node->left,l,m,x,y),query(node->right,m+1,r,x,y));
	}
	public:
	persistent_tree()
	{
		roots.push_back(build(a,0,n-1));
	}
	void update(int rt,int l,int r, int id, int z)
	{
		if(rt>=roots.size())
			return;
		roots.push_back(update(roots[rt],l,r,id,z));
	}
	data query(int rt,int l,int r,int x,int y)
	{
		if(rt>=roots.size())
		{
			data grbg;//set garbage
			return grbg;
		}
		return *(query(roots[rt],l,r,x,y));
	}
};
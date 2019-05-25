//SquareRoot Decomposition
//Usage sqrt_decomposition s1(size)
struct bkt
{
	//Node Structure of Bucket
};
class sqrt_decomposition
{
	private:
	int bksz,tbk,n;
	vector<bkt> sqan;
	public:
	sqrt_decomposition(int size)
	{
		n=size;
		bksz=sqrt(n);
		tbk=(n%bksz==0?n/bksz:(n/bksz)+1);
		sqan.resize(tbk);
	}
	void sqan_init()
	{
		int i;
		for(i=0;i<tbk;i++)
		{
			//init bucket block
		}
		for(i=0;i<n;i++)
		{
			//Array bucket relation
		}
	}
	int query(int l,int r)
	{
		int i,bs,be,ans,s,e;
		bs=(l)/bksz+1;
		be=(r)/bksz;
		s=((l)/bksz)*bksz;
		//cout<<"s: "<<s<<"\n";
		//cout<<"bs*bksz: "<<bs*bksz<<"\n";
		for(i=s;i<bs*bksz;i++)
		{
			if(i<l)
			{
				// start of this bucket to  l-1
			}
			else
			{
				// l to start of nearest bucket
			}
		}
		//cout<<"bs: "<<bs*bksz<<"\n";
		//cout<<"be: "<<be*bksz<<"\n";
		for(i=bs;i<be;i++)
		{
			// block/bucket traversal 
		}
		e=min((be+1)*bksz,n);
		//cout<<"be*bksz: "<<be*bksz<<"\n";
		//cout<<"e: "<<e<<"\n";
		for(i=be*bksz;i<e;i++)
		{
			if(i<=r)
			{
				// last bucket to r
			}
			else
			{
				// r+1 to end of that bucket
			}
		}        
	}
};
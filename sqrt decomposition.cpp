//SquareRoot Decomposition
struct bkt
{
	//Node Structure of Bucket
};
long long int bksz=sqrt(n),tbk=(n%bksz==0?n/bksz:(n/bksz)+1),bi;
bkt sqan[tbk];
void sqan_init()
{
	for(i=0;i<tbk;i++)
	{
		//init bucket block
	}
	for(i=0;i<n;i++)
	{
		//Array bucket relation
	}
}
long long int query(long long int l,long long int r)
{
	long long int bs,be,ans,s,e;
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
			// l to nearest bucket start   
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

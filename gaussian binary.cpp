//Number of bts to work upon
/*Gauss_bin basically holds a set of integers (you can add() them)
can(x) checks if a subset of integers added xor up to the number x
best(x) checks the max x xor a such that a is the xor of a subset
of the integers added
size() return the number of indepent(of xor) groups*/
class Gauss_bin
{
	private:
	const static int bts=20;
	int mat[bts];
	public:
	Gauss_bin()
	{
		memset(mat,0,sizeof(mat));
	}
	int size()
	{
		int i,ans=0;
		for(i=0;i<bts;i++)
		{
			if(mat[i])
			ans++;
		}
		return ans;
	}
	bool can(int x)
	{
		int i;
		for(i=bts-1;i>=0;i--)
		{
			x=min(x, x ^ mat[i]);
		}
		return (x==0);
	}
	void add(int x)
	{
		int i;
		for(i=bts-1;i>=0 && x;i--)
		{
			if(mat[i]==0)
			{
				mat[i] = x;
				x = 0;
			}
			else
			x=min(x, x ^ mat[i]);
		}
	}
	int best()
	{
		int i,x=0;
		for(i=bts-1;i>=0;i--)
		x=max(x, x ^ mat[i]);
		return x;
	}
};
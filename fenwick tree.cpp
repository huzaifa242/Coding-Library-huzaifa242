//Fenwick Tree(Binary Indexed Tree)
struct fen
{
	//node structure of Fenwick Tree
}bit[MAX];
//Point Update
void update(long long int id, long long int z)
{
	while(id<=n)
	{
		bit[id]= bit[id] * z; //'*' denotes the operation
		id+=(id & (-id));
	}
}
fen query(int id)
{
	//Initialize answer variable
	fen ans;
	while(id>0)
	{
		ans= ans * bit[id]; //'*' denotes the operation
		id-=(id & (-id));
	}
	return ans;
}
//Usage max_min_expression()
//put numbers in v
//put operators in opr
//mx[0][v.size()-1] has maximum value
//mn[0][v.size()-1] has minimum value 
vector<int> v;
vector<char> opr;
int mn[MAX][MAX],mx[MAX][MAX];
void max_min_expression()
{
	int i,j,k,l;
	for(i=0;i<v.size();i++)
	{
		for(j=0;j<v.size();j++)
		{
			mn[i][j]=INT_MAX;
			mx[i][j]=INT_MIN;
			if(i==j)
			mn[i][j]=mx[i][j]=v[i];
		}
	}
	for(l=2;l<v.size();l++)
	{
		for(i=0;i<v.size()-l+1;i++)
		{
			j=i+l-1;
			for(k=i;k<j;k++)
			{
				int mxtp,mxtp;
				if(opr[k]=='+')
				{
					mntp=mn[i][k]+mn[k+1][j];
					mxtp=mx[i][k]+mx[k+1][j];
				}
				//Similiar to '+' change operator
				//to do for any other operator
				mn[i][j]=min(mn[i][j],mntp);
				mx[i][j]=max(mx[i][j],mxtp);
			}
		}
	}
}
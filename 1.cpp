#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int isPrime(int n)
{
    if((n==2 || n==3 || (n+1)%6==0 || (n-1)%6==0) && n!=1)
    return 1;
    else
    return 0;
}
void modifyArray(int *arr,int m,int n)
{
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(i==j)
            {
                int y=isPrime(*((arr+i*n) + j));
                if(y)
                *((arr+i*n) + j)=*((arr+i*n) + j)+1;
            }
            //cout<<*((arr+i*n) + j)<<" ";
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n,m;
    cin>>m>>n;
    int arr[m][n];
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            cin>>arr[i][j];
        }
    }
    
    modifyArray((int *)arr,m,n);
    
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            cout<<arr[i][j]<<" ";
        }
        cout<<endl;
    }

    return 0;
}

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void merge(int arr[],int l,int h,int length)
{
    int a[length/2],r[h-l-(length/2)+1];
    for(int i=0;i<(length/2);i++)
    {
        a[i]=arr[l+i];
    }
    for(int i=0;i<h-l-(length/2)+1;i++)
    {
        r[i]=arr[l+(length/2)+i];
    }
    int p1=0,p2=0,k=l;
    while(1)
    {
        if(a[p1]<r[p2])
        {
            arr[k]=l[p1];
            k++;
            p1++;
        }
        else
        {
            arr[k]=r[p2];
            k++;
            p2++;
        }
        if(p1==(len/2) || p2==(h-l-(length/2)+1))
        break;
    }
    if(p1!=(length/2))
    {
        for(int i=p1;i<length/2;i++)
        {
            arr[k]=a[i];
            k++;
        }
    }
    if(p2!=(h-l-(length/2)+1))
    {
        for(int i=p2;i<(h-l-(length/2)+1);i++)
        {
            arr[k]=r[i];
            k++;
        }
    }
}

void func(int arr[],int l,int h)
{
    if(l==h)
    return ;
    int length=h-l+1;
    func(arr,l,l+((length/2)-1));
    func(arr,l+(length/2),h);
    merge(arr,l,h,length);
}

void populateArray(int *arr,int m,int n)
{
    for(int i=0;i<m;i++)
    {
        *((arr+i*n) + 0)=i+1;
    }
    for(int i=0;i<m;i++)
    {
        for(int j=1;j<n;j++)
        {
            cin>>*((arr+i*n) + j);
        }
    }
}

void sortRows(int *arr,int m,int n)
{
    int arr1[10];
    for(int i=0;i<m;i++)
    {
        for(int j=1;j<n;j++)
        {
            arr1[j-1]=*((arr+i*n) + j);
        }
        func(arr1,0,9);
        for(int j=1;j<n;j++)
        {
            *((arr+i*n) + j)=arr1[j-1];
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int m=5,n=11;
    int arr[m][n];
    
    populateArray((int *)arr,m,n);
    
    sortRows((int *)arr,m,n);
    
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



#include<bits/stdc++.h>
using namespace std;
#define int long long 

// .................................................................................................................................................................................................................................................................
// Simple Segment Tree;  for max query;

void build1(vector<int>&v,vector<int>&tree,int tidx,int s,int e){
  // Base Case;
  if(s==e){
    tree[tidx]=v[s];
    return;
  }
  
  int mid=(s+e)/2;
  // Left Child;
  build1(v,tree,2*tidx,s,mid);
  // Righ Child;
  build1(v,tree,2*tidx+1,mid+1,e);
  
  tree[tidx]=max(tree[2*tidx],tree[2*tidx+1]);
}

void update1(vector<int>&v,vector<int>&tree,int tidx,int s,int e,int idx,int val){
  if(s==e){
    tree[tidx]=val;
    v[idx]=val;
    return;
  }
  
  int mid=(s+e)/2;
  
  if(idx<=mid){
    update1(v,tree,2*tidx,s,mid,idx,val);
  }
  else{
    update1(v,tree,2*tidx+1,mid+1,e,idx,val);
  }
  
  tree[tidx]=max(tree[2*tidx],tree[2*tidx+1]);  
}

int query1(vector<int>&tree,int tidx,int s,int e,int l,int r){
  if(s>r or e<l){
    return 0;
  }
  else if(s>=l and e<=r){
    return tree[tidx];
  }
  
  int mid=(s+e)/2;
  
  int a1=query1(tree,2*tidx,s,mid,l,r);
  int a2=query1(tree,2*tidx+1,mid+1,e,l,r);
  
  return max(a1,a2);
}

// .................................................................................................................................................................................................................................................................
// If we want max value in range [l,r] and also we want
// count of those max in that range >> max and mapp[max] ???  {val,cnt(val)};

pair<int,int>combine(pair<int,int>&a,pair<int,int>&b){
  if(a.first>b.first){
    return a;
  }
  else if(a.first<b.first){
    return b;
  }
  else{
    return {a.first,a.second+b.second};
  }
}

void build2(vector<pair<int,int>>&tree,vector<int>&v,int tidx,int s,int e){
  if(s==e){
    tree[tidx]={v[s],1ll};
    return;
  }
  
  int mid=(s+e)/2;
  
  build2(tree,v,2*tidx,s,mid);
  build2(tree,v,2*tidx+1,mid+1,e);
  
  tree[tidx]=combine(tree[2*tidx],tree[2*tidx+1]);
}

void update2(vector<pair<int,int>>&tree,vector<int>&v,int tidx,int s,int e,int idx,int val){
  if(s==e){
    tree[tidx]={val,1ll};
    v[idx]=val;
    return;
  }
  
  int mid=(s+e)/2;
  update2(tree,v,2*tidx,s,mid,idx,val);
  update2(tree,v,2*tidx+1,mid+1,e,idx,val);
  
  tree[tidx]=combine(tree[2*tidx],tree[2*tidx+1]);
}

pair<int,int>query2(vector<pair<int,int>>&tree,int tidx,int s,int e,int l,int r){
  if(s>r or e>l){
    return {-INT_MAX,0};
  }
  else if(s>=l and e<=r){
    return tree[tidx];
  }
  
  int mid=(s+e)/2;
  
  pair<int,int>p1=query2(tree,2*tidx,s,mid,l,r);
  pair<int,int>p2=query2(tree,2*tidx+1,mid+1,e,l,r);
  
  return combine(p1,p2);
}

// ..................................................................................................................................................................................................................................................................

// Segment [l,r] : Max subsegment sum???

struct data{
  int sum,pref,suff,maxi;
};

data combine(data l,data r){
  data res;
  res.sum=l.sum+r.sum;
  res.pref=max(l.pref,l.sum+r.pref);
  res.suff=max(r.suff,r.sum+l.suff);
  res.maxi=max({ l.maxi, r.maxi, l.suff+r.pref });
  
  return res;
}

data make_data(int val){
  data res;
  res.sum=val;
  res.pref=res.suff=res.maxi=max(0ll,val);
  return res;
}

void build3(vector<int>&v,vector<data>&tree,int tidx,int s,int e){
  if(s==e){
    tree[tidx]=make_data(v[s]);
    return ;
  }
  int mid=(s+e)/2;
  build3(v,tree,2*tidx,s,mid);
  build3(v,tree,2*tidx+1,mid+1,e);
  tree[tidx]=combine(tree[2*tidx],tree[2*tidx+1]);
}

void update3(vector<int>&v,vector<data>&tree,int tidx,int s,int e,int idx,int val){
  if(s==e){
    tree[tidx]=make_data(val);
    v[s]=val;
    return;
  }
  
  int mid=(s+e)/2;
  update3(v,tree,2*tidx,s,mid,idx,val);
  update3(v,tree,2*tidx+1,mid+1,e,idx,val);
  
  tree[tidx]=combine(tree[2*tidx],tree[2*tidx+1]);
}

data query3(vector<data>&tree,int tidx,int s,int e,int l,int r){
  if(s>r or e<l){
    return make_data(0ll);
  }
  else if(s>=l and e<=r){
    return tree[tidx];
  }
  
  int mid=(s+e)/2;
  
  data a1=query3(tree,2*tidx,s,mid,l,r);
  data a2=query3(tree,2*tidx+1,mid+1,e,l,r);
  
  data res=combine(a1,a2);
  return res;
}

int32_t main(){
  
  int n;
  std::vector<int> v(n);
  vector<int>tree(4*n);
  
  vector<pair<int,int>>segtree(4*n);
  
}

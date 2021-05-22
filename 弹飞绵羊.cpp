#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
const double eps=1E-6;
struct Node{
	int num=0;
	int times=0;
	int last=0;
};
vector< vector<Node> >vec;
int r;
int n;
int blocks;
void initblock(int pos,int num){
	int tblocks=((pos==blocks)?r:blocks);
	for(int i=num;i>=0;i--){
		int add=vec[pos][i].num+i;
		if(add>=tblocks){
			vec[pos][i].last=add-tblocks;
			vec[pos][i].times=1;
		} 
		else{
			vec[pos][i].last=vec[pos][add].last;
			vec[pos][i].times=vec[pos][add].times+1;
		}
	}
}
void output(){
	int sz=vec.size();
	for(int i=0;i<sz;i++){
		int tsz=vec[i].size();
		for(int j=0;j<tsz;j++){
			cout<<i<<" "<<j<<":"<<vec[i][j].num<<" "<<vec[i][j].times<<" "<<vec[i][j].last<<endl;
		}
	}
}
int main(){
	//freopen("P3203_2.in","r",stdin);
	cin>>n;
	blocks=(int)(sqrt(n)+eps);
	r=n-blocks*blocks;
	vec.resize(blocks);
	for(int i=0;i<blocks;i++){
		vec[i].resize(blocks);
		for(int j=0;j<blocks;j++){
			cin>>vec[i][j].num;
		}
		initblock(i,blocks-1);
	}
	int endgroup=blocks;
	if(r){
		vector<Node>ttemp;
		ttemp.resize(r);
		for(int i=0;i<r;i++){
			cin>>ttemp[i].num;
		}
		vec.push_back(ttemp);
		initblock(blocks,r-1);
		endgroup=blocks+1;
	}
	//output();
	int m;
	cin>>m;
	for(int i=0;i<m;i++){
		int code;
		cin>>code;
		if(code==1){
			int j;
			cin>>j;
			int group=j/blocks;
			int pos=j%blocks;
			int ans=0;
			while(group<endgroup){
				//cout<<"add:"<<group<<" "<<pos<<" "<<ans<<endl;
				ans+=vec[group][pos].times;
				int t=vec[group][pos].last;
				group+=(t/blocks+1);
				pos=t%blocks;
			}
			cout<<ans<<endl;
			//_getch();
		}
		if(code==2){
			int j,k;
			cin>>j>>k;
			int group=j/blocks;
			int pos=j%blocks;
			vec[group][pos].num=k;
			initblock(group,pos); 
		}
	}
	return 0;
}

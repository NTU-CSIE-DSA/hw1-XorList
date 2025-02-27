#include <bits/stdc++.h>
#include <assert.h>
#include <string.h>
#include "testlib.h"
using namespace std;

const int M_MAX=500000;
const int T_MAX=6;
const int K_MAX=50000000;


int main(int argc, char* argv[]) {
	registerGen(argc, argv, 1);
	int rnd_seed=atoi(argv[1]);
	string gentype=argv[2];
	int M=(atoi(argv[3])==0?rnd.next(1, M_MAX):atoi(argv[3]));
	int ask_freq=atoi(argv[4]);
	int del_freq=atoi(argv[5]);
	int rev_freq=atoi(argv[6]);
	int rnd_limit=atoi(argv[7]);
	//ask, del, add 
	cout<<M<<"\n";
	int length=0;
	if(gentype=="random") {
		int ksum=0;
		for(int i=0;i<M;i++) {
			if(length==0) {
				cout<<"1 0\n";
				length++;
			}
			else {
				int rnx=rnd.next(1, 10);
				if(length>0 && rnx<=ask_freq && K_MAX!=ksum) {
					int k_cur=rnd.next(1, min(length, min(K_MAX-ksum, rnd_limit)));
					cout<<"0 "<<k_cur<<"\n";
					ksum+=k_cur;
				}
				else if(length>0 && rnx>10-del_freq && K_MAX!=ksum) {
					int k_cur=rnd.next(0, min(length, min(K_MAX-ksum, rnd_limit)));
					if(k_cur==0) {
						cout<<"1 0\n";
						length++;
					}
					else if(rnx%2) {
						cout<<"4 "<<k_cur<<"\n";
						length--;
						ksum+=k_cur;
					}
					else {
						cout<<"5 "<<k_cur<<"\n";
						length--;
						ksum+=k_cur;
					}
				}
				else if(length>0 && rnx>ask_freq && rnx<=ask_freq+rev_freq) {
					int k_cur=rnd.next(0, min((length+1)/2, min(K_MAX-ksum, rnd_limit)));
					if(k_cur==0 || ksum==K_MAX) {
						cout<<"1 0\n";
						length++;
					}
					else {
						cout<<"6 "<<k_cur<<"\n";
						ksum+=k_cur;
					}
				}
				else {
					int k_cur=rnd.next(0, min(length, min(K_MAX-ksum, rnd_limit)));
					if(k_cur==0 || ksum==K_MAX) cout<<"1 0\n";
					else {
						ksum+=k_cur;
						if(rnx%2) cout<<"2 "<<k_cur<<"\n";
						else cout<<"3 "<<k_cur<<"\n";
					}
					length++;
				}
			}
		}
	}
	else if(gentype=="tle") {
		cout<<"1 0\n";
		length++;
		if(rnd_seed%5==1) {
			int k_sum=0;
			for(int i=0;i<149;i++) {
				cout<<"3 "<<i+1<<"\n";
				k_sum+=(i+1);
				length++;
			}
			for(int i=0;i<150;i++) {
				int k_cur=rnd.next(1, (length+1)/2);
				cout<<"6 "<<k_cur<<"\n";
			}
			for(int i=1;i<M-300;i++) {
				int k_cur=rnd.next(1, length);
				cout<<"0 "<<k_cur<<"\n";
			}
			cout<<"0 "<<min(1, min(length, K_MAX-k_sum))<<"\n";
		}
		else if(rnd_seed%5==2) {
			int ksum=0;
			for(int i=M/2+1;i<M;i++) {
				cout<<"1 0\n";
				length++;
			}
			for(int i=2;i<=M/2;i++) {
				int k_cur=rnd.next(0, min(rnd_limit, K_MAX-ksum));
				ksum+=k_cur;
				if(k_cur==0) {
					cout<<"1 0\n";
					length++;
				}
				else if(i%del_freq) cout<<"6 "<<k_cur<<"\n";
				else {
					cout<<"0 "<<k_cur<<"\n";
				}
			}
			cout<<"0 "<<min(K_MAX-ksum, length)<<"\n";
		}
		else if(rnd_seed%5==3) {
			for(int i=1;i<M-159;i++) {
				cout<<"1 0\n";
				length++;
			}
			for(int i=0;i<60;i++) {
				if(i%2) {
					cout<<"5 "<<length<<"\n";
					length--;
				}
				else cout<<"6 1\n";
			}
			for(int i=0;i<99;i++) {
				cout<<"0 "<<rnd.next(1, length)<<"\n";
			}
		}
		else if(rnd_seed%5==4) {
			for(int i=1;i<100;i++) {
				cout<<"1 0\n";
				length++;
			}
			for(int i=100;i<M-99;i++) {
				int rnx=rnd.next(1, del_freq);
				if(rnx==1) {
					cout<<"4 1\n";
					length--;
				}
				else if(rnx%2) {
					cout<<"2 1\n";
					length++;
				}
				else {
					cout<<"6 1\n";
				}
			}
			for(int i=0;i<99;i++) {
				cout<<"0 "<<rnd.next(length-200, length)<<"\n";
			}
		}
		else {
			for(int i=1;i<100;i++) {
				cout<<"1 0\n";
				length++;
			}
			for(int i=100;i<M-99;i++) {
				int rnx=rnd.next(1, del_freq);
				if(rnx==1) {
					cout<<"5 1\n";
					length--;
				}
				else if(rnx%2) {
					cout<<"3 1\n";
					length++;
				}
				else {
					cout<<"6 1\n";
				}
			}
			for(int i=0;i<99;i++) {
				cout<<"0 "<<rnd.next(length-200, length)<<"\n";
			}
		}
	}
	else if(gentype=="askall") {
		for(int i=1;i<=M-14000;i++) {
			cout<<"1 0\n";
			length++;
		}
		int zcnt=0, tcnt=0;
		for(int i=14000;i>=1;i--) {
			int rnd_x=rnd.next(1, 13);
			if(rnd_x==13) {
				cout<<"6 "<<rnd.next(1, min(7000, (length+1)/2))<<"\n";
			}
			else if((rnd_x<=6 && tcnt<7000) || zcnt==7000) {
				tcnt++;
				int ty=rnd.next(2, 5);
				if(ty==2 || ty==3) length++;
				else length--;
				cout<<ty<<" "<<tcnt<<"\n";
			}
			else {
				zcnt++;
				cout<<"0 "<<zcnt<<"\n";
			}
		}
	}
	else if(gentype=="edge") {
		cout<<"1 0\n";
		length++;
		int ksum=0;
		for(int i=2;i<=M-100;i++) {
			int seed=rnd.next(1, 16);
			if(length>0 && seed==1) {
				cout<<"4 1\n";
				length--;
			}
			else if(length>0 && seed==4) {
				cout<<"5 1\n";
				length--;
			}
			else if(seed%8==5) {
				cout<<"6 1\n";
			}
			else if(seed%2==0) {
				cout<<"2 1\n";
				length++;
			}
			else {
				cout<<"3 1\n";
				length++;
			}
			ksum++;
		}
		for(int i=M-99;i<=M-1;i++) {
			int k_cur=rnd.next(1, min(length, 100));
			cout<<"0 "<<k_cur<<"\n";
			ksum+=k_cur;
		}
		cout<<"0 "<<min(length, K_MAX-ksum)<<"\n";
	}
	else if(gentype=="empty") {
		bool flag=0;
		int empty=0, empty_freq=atoi(argv[8]);
		for(int i=1;i<=M;i++) {
			if(flag && length!=0) {
				int rnx=rnd.next(1, 2);
				if(rnx==1) cout<<"4 1\n";
				else cout<<"5 1\n";
				length--;
				if(length==0) flag=0;
			}
			else {
				empty=rnd.next(1, empty_freq);
				if(empty==1) flag=1;
				int rnx=rnd.next(1, 10);
				if(length==0) {
					cout<<"1 0\n";
					length++;
				}
				else if(length>0 && rnx<=ask_freq) {
					cout<<"0 "<<rnd.next(1, min(rnd_limit, length))<<"\n";
				}
				else if(length>0 && rnx>10-del_freq) {
					if(rnx%2) cout<<"4 "<<rnd.next(1, min(rnd_limit, length))<<"\n";
					else cout<<"5 "<<rnd.next(1, min(rnd_limit, length))<<"\n";
					length--;
				}
				else if(length>0 && rnx>ask_freq && rnx<=ask_freq+rev_freq) {
					cout<<"6 "<<rnd.next(1, min(rnd_limit, (length+1)/2))<<"\n";
				}
				else {
					int k=rnd.next(0, min(rnd_limit, length));
					if(k==0) cout<<"1 0\n";
					else {
						if(rnx%2) cout<<"2 "<<k<<"\n";
						else cout<<"3 "<<k<<"\n";
					}
					length++;
				}
			}
		}
	}
}

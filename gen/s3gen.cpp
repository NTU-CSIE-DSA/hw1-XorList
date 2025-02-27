#include <bits/stdc++.h>
#include <assert.h>
#include <string.h>
#include "testlib.h"
using namespace std;

const int M_MAX=500000;
const int T_MAX=3;
const int K_MAX=50000000;

int main(int argc, char* argv[]) {
	registerGen(argc, argv, 1);
	int rnd_seed=atoi(argv[1]);
	string gentype=argv[2];
	int M=(atoi(argv[3])==0?rnd.next(1, M_MAX):atoi(argv[3]));
	int ask_freq=atoi(argv[4]);
	int rnd_limit=atoi(argv[5]);
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
				if(rnx<=ask_freq && ksum<K_MAX) {
					int k_cur=rnd.next(1, min(length, min(K_MAX-ksum, rnd_limit)));
					cout<<"0 "<<k_cur<<"\n";
					ksum+=k_cur;
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
		if(rnd_seed%4==1) {
			for(int i=0;i<99;i++) {
				cout<<"3 "<<i+1<<"\n";
				length++;
			}
			for(int i=0;i<M-100;i++) {
				cout<<"0 "<<length<<"\n";
			}
		}
		else if(rnd_seed%4==2) {
			int ksum=0;
			for(int i=2;i<=9999;i++) {
				ksum+=length;
				if(i%2) cout<<"0 "<<length<<"\n";
				else {
					cout<<"3 "<<length<<"\n";
					length++;
				}
			}
			for(int i=10000;i<M;i++) {
				cout<<"1 0\n";
				length++;
			}
			cout<<"0 "<<min(K_MAX-ksum, length)<<"\n";
		}
		else if(rnd_seed%4==3) {
			for(int i=1;i<M-99;i++) {
				cout<<"3 1\n";
				length++;
			}
			for(int i=0;i<99;i++) {
				cout<<"0 "<<length<<"\n";
			}
		}
		else {
			for(int i=1;i<100;i++) {
				cout<<"2 "<<length<<"\n";
				length++;
			}
			for(int i=100;i<M-99;i++) {
				cout<<"3 1\n";
				length++;
			}
			for(int i=0;i<99;i++) {
				cout<<"0 "<<rnd.next(length-200, length)<<"\n";
			}
		}
	}
	else if(gentype=="askall") {
		for(int i=1;i<=M-14000;i++) {
			cout<<"1 0\n";
		}
		int zcnt=0, tcnt=0;
		for(int i=14000;i>=1;i--) {
			int rnd_x=rnd.next(1, 2);
			if((rnd_x==1 && tcnt<7000) || zcnt==7000) {
				tcnt++;
				cout<<"3 "<<tcnt<<"\n";
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
		for(int i=2;i<=M-99;i++) {
			if(i%2) cout<<"2 1\n";
			else cout<<"3 1\n";
			length++;
		}
		for(int i=M-98;i<=M;i++) {
			cout<<"0 "<<length<<"\n";
		}
	}
}

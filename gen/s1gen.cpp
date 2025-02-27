#include <iostream>
#include <assert.h>
#include <string.h>
#include "testlib.h"
using namespace std;

const int M_MAX=500000;
const int T_MAX=1;
const int K_MAX=50000000;

int main(int argc, char* argv[]) {
	registerGen(argc, argv, 1);
	int rnd_seed=atoi(argv[1]);
	string gentype=argv[2];
	int M=(atoi(argv[3])==0?rnd.next(1, M_MAX):atoi(argv[3]));
	int ask_freq=atoi(argv[4]);
	int rnd_limit=atoi(argv[5]);
	cout<<M<<"\n";
	int length=0, ksum=0;
	if(gentype=="random") {
		for(int i=0;i<M;i++) {
			if(length==0) {
				cout<<"1 0\n";
				length++;
			}
			else {
				int rnx=rnd.next(1, 10);
				if(rnx<=ask_freq && ksum<K_MAX) {
					int k_cur;
					k_cur=rnd.next(1, min(length, min(K_MAX-ksum, rnd_limit)));
					cout<<"0 "<<k_cur<<"\n";
					ksum+=k_cur;
				}
				else {
					cout<<"1 0\n";
					length++;
				}
			}
		}
	}
	else if(gentype=="tle") {
		if(rnd_seed%2) {
			for(int i=0;i<100;i++) {
				cout<<"1 0\n";
				length++;
			}
			for(int i=0;i<M-100;i++) {
				cout<<"0 "<<length<<"\n";
			}
		}
		else {
			for(int i=0;i<M-100;i++) {
				cout<<"1 0\n";
				length++;
			}
			for(int i=0;i<100;i++) {
				cout<<"0 "<<length<<"\n";
			}
		}
	}
	else if(gentype=="askall") {
		for(int i=1;i<=M-9999;i++) {
			cout<<"1 0\n";
		}
		for(int i=9999;i>=1;i--) {
			cout<<"0 "<<i<<"\n";
		}
	}
}

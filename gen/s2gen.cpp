#include <iostream>
#include <assert.h>
#include <string.h>
#include "testlib.h"
using namespace std;

const int M_MAX=10000;
const int T_MAX=2;

int main(int argc, char* argv[]) {
	registerGen(argc, argv, 1);
	int rnd_seed=atoi(argv[1]);
	string gentype=argv[2];
	int M=(atoi(argv[3])==0?rnd.next(1, M_MAX):atoi(argv[3]));
	int ask_freq=atoi(argv[4]);
	cout<<M<<"\n";
	int length=0;
	if(gentype=="random") {
		for(int i=0;i<M;i++) {
			if(length==0) {
				cout<<"1 0\n";
				length++;
			}
			else {
				int rnx=rnd.next(1, 10);
				if(rnx<=ask_freq) {
					cout<<"0 "<<rnd.next(1, length)<<"\n";
				}
				else {
					int k=rnd.next(0, length);
					if(k==0) cout<<"1 0\n";
					else cout<<"2 "<<k<<"\n";
					length++;
				}
			}
		}
	}
	else if(gentype=="tle") {
		cout<<"1 0\n";
		length++;
		if(rnd_seed%2) {
			for(int i=1;i<=M-10;i++) {
				cout<<"2 "<<i<<"\n";
				length++;
			}
			for(int i=1;i<=9;i++) {
				cout<<"0 "<<M-8-i<<"\n";
			}
		}
		else {
			for(int i=1;i<=M-10;i++) {
				cout<<"2 "<<(i+1)/2<<"\n";
				length++;
			}
			for(int i=1;i<=9;i++) {
				cout<<"0 "<<min(length, (M-9+1)/2+i)<<"\n";
			}
		}
	}
	else if(gentype=="askall") {
		int exp_length=M/10*(10-ask_freq);
		for(int i=0;i<M-exp_length;i++) {
			if(length==0) {
				cout<<"1 0\n";
				length++;
			}
			else {
				int rnx=rnd.next(1, 10);
				if(rnx<=ask_freq) {
					cout<<"0 "<<rnd.next(1, length)<<"\n";
				}
				else {
					int k=rnd.next(0, length);
					if(k==0) cout<<"1 0\n";
					else cout<<"2 "<<k<<"\n";
					length++;
				}
			}
		}
		for(int i=1;i<=exp_length;i++) {
			if(i>length) cout<<"0 "<<rnd.next(1, length)<<"\n";
			else cout<<"0 "<<i<<"\n";
		}
	}
	else if(gentype=="edge") {
		cout<<"1 0\n";
		for(int i=2;i<=M/2+1;i++) {
			cout<<"2 1\n";
		}
		for(int i=M/2+2;i<=M;i++) {
			cout<<"0 "<<i-M/2-1<<"\n";
		}
	}
}

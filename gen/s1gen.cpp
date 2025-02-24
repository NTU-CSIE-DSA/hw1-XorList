#include <iostream>
#include <assert.h>
#include <string.h>
#include "testlib.h"
using namespace std;

const int M_MAX=10000;
const int T_MAX=1;

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
					cout<<"1 0\n";
					length++;
				}
			}
		}
	}
	else if(gentype=="tle") {
		for(int i=0;i<M/2;i++) {
			cout<<"1 0\n";
			length++;
		}
		for(int i=0;i<M-M/2;i++) {
			cout<<"0 "<<length<<"\n";
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
					cout<<"1 0\n";
					length++;
				}
			}
		}
		for(int i=1;i<=exp_length;i++) {
			if(i>length) cout<<"0 "<<rnd.next(1, length)<<"\n";
			else cout<<"0 "<<i<<"\n";
		}
	}
}

#include <iostream>
#include <assert.h>
#include <string.h>
#include "testlib.h"
using namespace std;

const int M_MAX=10000;
const int T_MAX=5;

int main(int argc, char* argv[]) {
	registerGen(argc, argv, 1);
	int rnd_seed=atoi(argv[1]);
	string gentype=argv[2];
	int M=(atoi(argv[3])==0?rnd.next(1, M_MAX):atoi(argv[3]));
	int ask_freq=atoi(argv[4]);
	int del_freq=atoi(argv[5]);
	//ask, del, add 
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
				if(length>0 && rnx<=ask_freq) {
					cout<<"0 "<<rnd.next(1, length)<<"\n";
				}
				else if(length>0 && rnx>10-del_freq) {
					if(rnx%2) cout<<"4 "<<rnd.next(1, length)<<"\n";
					else cout<<"5 "<<rnd.next(1, length)<<"\n";
					length--;
				}
				else {
					int k=(length==0?0:rnd.next(1, length+1)-1);
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
	else if(gentype=="tle") {
		cout<<"1 0\n";
		length++;
		del_freq=max(del_freq, 16);
		if(rnd_seed%2) {
			for(int i=1;i<=M-31;i++) {
				if(i%del_freq==17) {
					cout<<"4 "<<length<<"\n";
					length--;
				}
				else if(i%del_freq==9) {
					cout<<"5 1\n";
					length--;
				}
				else if(i%4==3) {
					cout<<"2 "<<length<<"\n";
					length++;
				}
				else {
					cout<<"3 1\n";
					length++;
				}
			}
			for(int i=1;i<=30;i++) {
				cout<<"0 "<<length+1-i<<"\n";
			}
		}
		else {
			for(int i=1;i<=M-31;i++) {
				if(i%del_freq==11) {
					cout<<"4 "<<(length+1)/2<<"\n";
					length--;
				}
				else if(i%del_freq==13) {
					cout<<"5 "<<(length+1)/2<<"\n";
					length--;
				}
				else if(i%4==3) {
					cout<<"2 "<<(length+1)/2<<"\n";
					length++;
				}
				else {
					cout<<"3 "<<(length+1)/2<<"\n";
					length++;
				}
			}
			for(int i=1;i<=30;i++) {
				cout<<"0 "<<max(1, min(length, (M-20+1)/2+i))<<"\n";
			}
		}
	}
	else if(gentype=="askall") {
		int exp_length=M/10*(10-ask_freq-2*del_freq);
		for(int i=0;i<M-exp_length;i++) {
			if(length==0) {
				cout<<"1 0\n";
				length++;
			}
			else {
				int rnx=rnd.next(1, 10);
				if(length>0 && rnx<=ask_freq) {
					cout<<"0 "<<rnd.next(1, length)<<"\n";
				}
				else if(length>0 && rnx>10-del_freq) {
					if(rnx%2) cout<<"4 "<<rnd.next(1, length)<<"\n";
					else cout<<"5 "<<rnd.next(1, length)<<"\n";
					length--;
				}
				else {
					int k=(length==0?0:rnd.next(1, length+1)-1);
					if(k==0) cout<<"1 0\n";
					else {
						if(rnx%2) cout<<"2 "<<k<<"\n";
						else cout<<"3 "<<k<<"\n";
					}
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
		length++;
		for(int i=2;i<=M/2+1;i++) {
			int seed=rnd.next(1, 16);
			if(length>0 && seed==1) {
				cout<<"4 1\n";
				length--;
			}
			else if(length>0 && seed==2) {
				cout<<"4 "<<length<<"\n";
				length--;
			}
			else if(length>0 && seed==3) {
				cout<<"5 "<<length<<"\n";
				length--;
			}
			else if(length>0 && seed==4) {
				cout<<"5 1\n";
				length--;
			}
			else if(seed%4==0) {
				cout<<"2 1\n";
				length++;
			}
			else if(seed%4==1) {
				cout<<"2 "<<length<<"\n";
				length++;
			}
			else if(seed%4==2) {
				cout<<"3 "<<length<<"\n";
				length++;
			}
			else {
				cout<<"3 1\n";
				length++;
			}
		}
		for(int i=M/2+2;i<=M;i++) {
			cout<<"0 "<<rnd.next(1, length)<<"\n";
		}
	}
	else if(gentype=="empty") {
		bool flag=0;
		int empty, empty_freq=atoi(argv[6]);
		for(int i=1;i<=M;i++) {
			if(flag) {
				int rnx=rnd.next(1, 2);
				if(rnx==1) cout<<"4 "<<rnd.next(1, length)<<"\n";
				else cout<<"5 "<<rnd.next(1, length)<<"\n";
				length--;
				if(length==0) flag=0;
			}
			else {
				empty=rnd.next(1, empty_freq);
				int rnx=rnd.next(1, 10);
				if(length>0 && rnx<=ask_freq) {
					cout<<"0 "<<rnd.next(1, length)<<"\n";
				}
				else if(length>0 && rnx>10-del_freq) {
					if(rnx%2) cout<<"4 "<<rnd.next(1, length)<<"\n";
					else cout<<"5 "<<rnd.next(1, length)<<"\n";
					length--;
				}
				else {
					int k=(length==0?0:rnd.next(1, length+1)-1);
					if(k==0) cout<<"1 0\n";
					else {
						if(rnx%2) cout<<"2 "<<k<<"\n";
						else cout<<"3 "<<k<<"\n";
					}
					length++;
				}
				if(empty==1) flag=1;
			}
		}
	}
}

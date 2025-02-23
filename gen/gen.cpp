#include <iostream>
#include <assert.h>
#include "testlib.h"
using namespace std;

const int ROW=50;
const int COLUMN=10000;
const int BUF=10000;
const int MXVAL=10000;

int main(int argc, char* argv[]) {
	registerGen(argc, argv, 1);
	int row=(atoi(argv[1])==0?rnd.next(1, ROW):atoi(argv[1]));
	int column=atoi(argv[2]);
	int rnd_seed=atoi(argv[3]);
	int col[row];
	cout<<row<<"\n";
	int buf_cnt=0;
	for(int i=0;i<row;i++) {
		if(i!=row-1) {
			int output=(column==0?rnd.next(1, BUF/row):column);
			col[i]=output;
			buf_cnt+=output;
			cout<<output<<" ";
		}
		else {
			int output=(column==0?BUF-buf_cnt:column);
			col[i]=output;
			buf_cnt+=output;
			assert(buf_cnt<=BUF);
			cout<<output<<"\n";
		}
	}
	for(int i=0;i<row;i++) {
		for(int j=0;j<col[i];j++) {
			cout<<rnd.next(1, MXVAL);
			if(j!=col[i]-1) cout<<" ";
			else cout<<"\n";
		}
	}
}

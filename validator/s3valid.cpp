#include "testlib.h"
using namespace std;

const int M_MAX=10000;
const int T_MAX=3;

int main() {
	int length=0;
	registerValidation();
	int M=inf.readInt(1, M_MAX, "M");
	inf.readEoln();
	for(int i=0;i<M;i++) {
		int t=inf.readInt(0, T_MAX, "t");
		if(length==0) {
			ensuref(t==1, "t is not 1 when list is empty\n");
		}
		inf.readSpace();
		int k;
		if(t==1) {
			k=inf.readInt(0, 0, "k");
		}
		else if(t==6) {
			k=inf.readInt(1, (length+1)/2, "k");
		}
		else {
			k=inf.readInt(1, length, "k");
		}
		if(t==1 || t==2 || t==3) length++;
		else if(t==4 || t==5) length--;
		inf.readEoln();
	}
	inf.readEof();
	return 0;
}

#define SC_INCLUDE_FX
#include <systemc>
#include <iostream>
#include <vector>
#include <deque>

typedef sc_dt::sc_fix_fast num;


double fibb(int n){
	double f0=0;
	double f1=1;
	double result;
	if(n==0)
		return 0;
	if(n==1) return 1;
	for(int i=0;i<n-1;i++){
		result=f0+f1;
		f0=f1;
		f1=result;
	}
	return result;
}


int sc_main(int argc, char* argv[])
{

bool pass = false;
int n = 64;
int num_of_bits=1;
double element;
element = fibb(n);

do{

std::cout<<"Broj bita: "<<num_of_bits<<std::endl;
num res(num_of_bits,num_of_bits);
num fib0(num_of_bits,num_of_bits);
fib0=0;
num fib1(num_of_bits,num_of_bits);
fib1=1;

for(int i=0;i<n-1;i++){
	res=fib0+fib1;
	fib0=fib1;
	fib1=res;
}

std::cout<<"Originalna vrednost: "<<element<<" Vrednost sa fix point: "<<res<<std::endl;

if(res==element){
	std::cout<<"Kraj"<<std::endl;
	pass=true;
}
num_of_bits++;


}while(pass==false);

std::cout<<element<<std::endl;
return 0;
}

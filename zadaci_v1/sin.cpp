#define SC_INCLUDE_FX
#include <systemc>
#include <iostream>
#include <vector>
#include <deque>
#include <cmath>
typedef sc_dt::sc_fix_fast num_t;
typedef std::vector<double> coef_t;
typedef std::deque<num_t> implementation_type;

double factorial(int a){
	double res=1;
	if(a==0)return 1;
	for(int i=2;i<=a;i++){
	res = res* i;
}
	return res;
}

bool passCheck1(const coef_t& c, const int n, const double error){
	double sin_res;
	double tailor_res=0;	

	for(double x=0;x<=2*M_PI;x+=0.01){
		sin_res=sin(x);
		tailor_res=0;
		for(int j=0;j<=n;j++){
			tailor_res=tailor_res + c[j] * pow(x,2*j+1);
		}
		if(std::abs(tailor_res-sin_res)>error)
			return false;
}
	return true;
}

bool passCheck2(const coef_t& orig_coef, implementation_type& dest_coef,int W, int F, double error){

	double orig_res=0;
	num_t dest_res(W,F);
	dest_res=0;
	for(double x=0;x<=2*M_PI;x+=0.01){
		orig_res=0;
		dest_res=0;
		for(int j=0;j<12;j++){
			orig_res=orig_res + orig_coef[j] * pow(x,2*j+1);
			dest_res=dest_res + dest_coef[j] * pow(x,2*j+1);
		}
		//std::cout<<"Orig_res = " <<orig_res<<" Dest_res = "<<dest_res<<std::endl;
		//std::cout<<"Razlika: " <<std::abs(orig_res-dest_res)<<" Error: "<<error<<std::endl;
		
		if(std::abs(orig_res-dest_res)>error)
			return false;
	}
	return true;


}

void copy2fix(const coef_t& orig_coef, implementation_type& dest_coef,int W,int F,int n){
	num_t d(W,F);
	for(int i=0;i<n;i++){
		d = orig_coef[i];
		dest_coef.push_back(d);
		std::cout<<orig_coef[i]<<" "<<dest_coef[i]<<std::endl;
	}

}


int sc_main(int argc, char* argv[])
{


bool pass=false;
double error = 1e-05;
int n=0;
coef_t tailor_coef;
double temp_coef;
std::vector<double>::iterator it;
std::vector<num_t>::iterator it1;
/*
for(int i=0;i<=360;i++){
	std::cout<<"i= "<<i<<" sin("<<i<<") = "<<sin(i*(2*M_PI)/360)<<std::endl;
}
*/

do{
temp_coef =(double)pow(-1,n)/(factorial(2*n+1) * 1.0);
tailor_coef.push_back(temp_coef);
pass = passCheck1(tailor_coef,n,error);
std::cout<<"Broj cinilaca: "<<n<<std::endl;
n++;

}while(pass==false);

/*
for(it = tailor_coef.begin(); it != tailor_coef.end();++it){
	std::cout<<*it<<" ";
}
*/

std::cout<<"Minimalan potreban cinilaca: "<<n<<std::endl;

//potreban broj bita za koeficijente, najveci koeficijent je 1, tako da je potrebno 2 bita za ceo broj.

pass=false;
int W=10;
int F=2;
//copy2fix(tailor_coef,array_coef,W,F,n);


do{
implementation_type array_coef;
copy2fix(tailor_coef,array_coef,W,F,n);
pass=passCheck2(tailor_coef,array_coef,W,F,error);
std::cout<<"Format: " <<F<<"."<<W-F<<std::endl;
W++;

}while(pass==false);



return 0;


} 

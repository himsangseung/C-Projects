#include <iostream>
using std::cin; using std::cout; using std::endl;
#include <cmath>
using std::sqrt;

long k_hyper, k_max, sum=0;   // defining variables
long k;
long r;

int main(){

cin>> k_hyper>> k_max; //inputting the checkvalue and k_max
if (k_hyper< 6 || k_max < 1) 
// if the checkvalue is less than 6, or k_max less than 1: return 0 
	cout<< 0;
else{
	for (long i=1; i<=sqrt(k_hyper);i++) {
		if (i ==1 || i ==k_hyper) // if divided by itself or 1, pass
			continue;
			
		else if ( k_hyper %i ==0)
			sum += i+(k_hyper/i); // sum of all factors excluding itself and 1
	};
	
		


	
	if (sum == 0)
		cout<<0;


	r = (k_hyper-1)%sum;
	if (r == 0){
		k = (k_hyper-1)/sum;
		if (1<= k && k <=k_max)
			cout<<k;
		else
			cout<<0;
		}
	else
		cout<<0;
}
}


	
/*

	if (sum == 0)
		cout<<0;



	if (r == 0){
		k = (k_hyper-1)/sum;
		if (k<=k_max)
			cout<<k;
		else
			cout<<0;
		}
	else
		cout<<0;



	}

*/

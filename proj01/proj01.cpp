#include <iostream>
using std::cout; using std::cin; using std::endl; using std::fixed; using std::noshowpoint;
#include <iomanip>
using std::setprecision;
#include <cmath>
using std::round;

int main(){
	
	long year;
	double slope_def= 0.01173; //degFyear
	double slope; //degF/year
	double intercept =34.3491; //degF
	
	cin>>year>> slope;
	
	double temp = slope_def*year+intercept;
	cout<<fixed<<setprecision(2)<<temp<<endl;
	
	double year_new = ((temp+7)-intercept)/slope_def;
	
	static_cast<long> (year_new);
	
	cout<< noshowpoint << setprecision( 0 )<<round(year_new)<<endl;
	
	double year_new2 = ((temp +7) -intercept)/slope;
	
	//static_cast<long> (year_new2);
	
	cout<< noshowpoint << setprecision( 0 )<<round(year_new2)<<endl;
}



/*

proj06 : Steganography
section 3
10/21/2018
*/

#include "proj06_functions.h"

#include <fstream>
using std::ifstream;

#include<stdexcept>
using std::runtime_error;


using matrix_row = vector<int>;
using matrix = vector<matrix_row>; 

#include<iostream>
using std::cout;using std::cin; using std::endl; using std:: boolalpha;

#include<cmath>
using std::pow;

#include<sstream>
using std::ostringstream;


vector<vector<int>> read_file(const string &fname){
    /*
    takes in a file name and reads the file. each line is separated by \n
    row matrix is separetly set up so that it can be added to the 2-D matrix
    */
    matrix_row row;
    matrix result;

    string line;

    ifstream infile(fname);

    if (infile){
        while (getline(infile,line))
        {
            if (line !=""){
            for (auto chac : line){
            int chacs = static_cast<int>(chac)-48;
            
            row.push_back(chacs);
            
            }
            result.push_back(row);
            row.clear();
            }
        }
        
        return result;

    }

    else{
        throw runtime_error("no file opened");
    }

}
vector<int> get_row(const vector<vector<int>> &v, int row){
    /*
    getting the row vector out of 2-D vector

    */
return v[row];
}
vector<int> get_column(const vector<vector<int>> &v, int col){
    /*

    getting the column information out of 2-D vector
    */
matrix_row result;
    for (auto ele : v){
        result.push_back(ele[col]);
        
    }
    return result;
}

string parity(int a, int pari){
    /*
    checking parity, if the given sum of 1s are even and parity is given to 1,
    return the string "true", also if the given sum is odd, and parity is 0,
    also return "true", other wise return "false"
    */
    if (a%2 ==0 && pari ==1){
        return "true";
    }

    else if (a%2 != 0 && pari ==0){
        return "true";
    }
    return "false";

}


string check_column_parity(const vector<vector<int>> &v, int col){
    /*
    chekcing column parity, sum up all the numbers in the column and comparing
    if odd or even and eventaully to the given parity,

    parity function is used.
    */
matrix_row col_new = get_column(v,col);
int pari = col_new[0];

int val =0;
ostringstream oss;

for (size_t i =0; i<col_new.size();i++){
    if (i==0){
        oss<< col_new[0]<<":";
        continue;
    }

    val += col_new[i];
}

oss<<val<<":";
oss<<parity(val,pari);

return oss.str();

}

string check_row_parity(const vector<vector<int>> &v, int r){
    /*
    chekcing row parity, sum up all the numbers in the row and comparing
    if odd or even and eventaully to the given parity,

    parity function is used.
    */
matrix_row row_new = get_row(v,r);
int pari = row_new[0];

int val =0;
ostringstream oss;

for (size_t i=0; i<row_new.size();i++){
    if(i==0){
        oss<< row_new[0]<<":";
        continue;
    }
    val += row_new[i];
}

oss<<val<<":";
oss<<parity(val,pari);

return oss.str();

}

int col_to_int(const vector<vector<int>> &v, size_t col){
    /*
    getting the sum of numbers with binary sequence
    each row has 2^(row number) sequence

    */

matrix_row col_vec = get_column (v, col);
    int value=0;
    
    for (size_t i =0; i< col_vec.size()-1; i++){
        
        value += col_vec[i+1]*pow(2,6-i);
    }
        
    return value;    
}


string get_time(const vector<vector<int>> &v){
    /*
    column of 4 and 1 have min and hour information
    if the num is a single digit, 0 is added to correspond to 2 digit sequence
    */
    int time = col_to_int(v,4);
    int min = col_to_int(v,1);
    ostringstream oss;

    if (time <=10){
        if(min<10){
            oss<<"0"<<time<<":"<<"0"<<min;
            return oss.str();
        }
        else{
        oss<<"0"<<time<<":"<<min;
        return oss.str();
        }
    }

    else if (time>=10){
        if (min <10){
            oss<<time<<":"<<"0"<<min;
            return oss.str();
        }

        else{
            oss<<time<<":"<<min;
            return oss.str();
        }
    }

}


string get_date(const vector<vector<int>> &v){
    /*

    column sum of 5,6,7 have date, month, year informations
    similar to getting time, if the number is a single digit,
    0 is added and / is added for separtion in between
    */
    int year = col_to_int(v,7);
    int mon = col_to_int(v,6);
    int date = col_to_int(v,5);
    ostringstream oss;
    
        if (mon <10){
       oss<<"0"<<mon<<"/";
        
        if (date <10){
            oss<<"0"<<date<<"/";
        }
        else{
            oss<<date<<"/";
        }
    }

    else {

        oss<<mon<<"/";
        if (date<10){
            oss<<"0"<<date<<"/";
        }
        else{
            oss<<date<<"/";
        }
    }
    
    
    
    if (year<10){
    oss<<"200"<<year;
    }

    else{
        oss<<"20"<<year;
    }


    return oss.str();

}
string get_serial(const vector<vector<int>> &v){
    /*
    getting serial information, using iterator method
    column 10, 11 ,12 ,13 sum have serial information
    also add 0 for single digit numbers

    */

int pair1 = col_to_int(v,13);
int pair2 = col_to_int(v,12);
int pair3 = col_to_int(v,11);
int pair4 = col_to_int(v,10);
ostringstream oss;
matrix_row pairs = {pair1, pair2, pair3, pair4};

for (auto iter = pairs.begin(); iter != pairs.end();++iter)
{
    if (*iter <10){
        oss<<"0"<<*iter;
    }
    else{
        oss<<*iter;
    }
}

return oss.str();

}

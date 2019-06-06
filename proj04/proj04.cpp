/*
Encoding and Decoding Program
4 Functions total
Test each case with 1,2,3,4 on first input
*/

#include<iostream>
using std::cout; using std::cin; using std::endl;
#include<iomanip>
using std::setprecision;
#include<string>
using std::string;

// global variable for count -> char code
const string code = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

string encode_sequence(string input, char sep){
  /*
  sequence encoding function, takes in input and separating character,
  puts out separting character, how many # the character appears follows by what character
  */
    string enc_seq ="";
    int len = input.length();
    char letter = input[0];
    int len_new =0;
    if (len <= 29)// with the length is less than 29
    {len_new = len+93;}//make it go with lowercase letters

    else// if not
    {len_new = len+35;}// go with Uppercase letters

    char len_char = static_cast<char>(len_new);// convert int into char

    enc_seq.append(1,sep);
    enc_seq.append(1,len_char);
    enc_seq.append(1,letter);

    return enc_seq;
}
string encode(string input, char sep){
  /*
  encoding function,
  uses encode_sequence function for characters sequence that has more than 3 repetitions
  otherwise just to be added to the string to be printed
  */
    int count =1;
    string return_str ="";
    for(string::size_type i =0; i<=(input.size());++i){
      
      if (input[i] == input[i+1]){
        count++;

      }//if
      else{  
        string added = "";
        added.append(count,(input[i]));
        
        if (count> 3){// if more than 3 repetitions
          return_str += encode_sequence( added, sep);// run encode_sequence
          count =1;
        }//if
        else{
          return_str+= added;
          count =1;}//else
      }//else1
    }//for
    return return_str;

}

string decode_sequence(string encode, char sep){
  /*
  sequence decoding function, takes in three character string, then converts into sequence of characters

  */
  string return_str ="";
  int num =0;
  if (encode[1]>=97){

   num = static_cast<int>(encode[1])-93; //lowercase
  }
  else 
  {num = static_cast<int>(encode[1]-35);}// uppercase


  return_str.append(num,encode[2]);

  return return_str;
}

string decode( string decode , char sep){
  /*
  decoding function takes in complex sequence of characters with separators
  */
  string return_str ="";

  int k = 0; 
  for (string::size_type i = 0; i<= decode.size(); i+= k){// k step size
    if (decode[i] == sep){
      string decode_part = decode.substr(i,3);
      return_str += decode_sequence(decode_part, sep);
      k=3;}// 3 character sequence with encoding, so skip the following two characters
    
    else{
      return_str.push_back(decode[i]);
      k=1;}// no skip on characters inbetween

    }
  return_str.pop_back();// pop out unnecessary character at the end
  return return_str;
}


double reduction (string ori, string run){
  /*
  reudction function, shows how efficient the encoding process is
  */
  double run_size = run.size();// length of encoded
  double ori_size = ori.size();//length of original
  return run_size/ori_size;// ratio
}

int main (){
  long test_num;
  cin >> test_num;

  switch(test_num) {

  case 1: {
    string input;
    char sep;
    cin >> input;
    cin >> sep;
    cout << encode_sequence(input, sep);
    break;
  }

  case 2:{
    string input;
    char sep;
    cin >> input;
    cin >> sep;
    cout << encode(input, sep);
    break;
  }

  case 3:{
    string input;
    char sep;
    cin >> input;
    cin >> sep;
    cout << decode_sequence(input, sep);
    break;
  }

  case 4:{
    string input;
    char sep;
    cin >> input;
    cin >> sep;
    cout << decode(input, sep);
    break;
  }

  case 5:{
    string s1,s2;
    cin >> s1;
    cin >> s2;
    cout << setprecision(2);
    cout << reduction(s1,s2);
    break;
  }
  
  } // of switch
}  // of main
  

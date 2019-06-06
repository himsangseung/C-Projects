/*
proj05 : THe Playfair Algorithm
section 3
10/15/2018

using five functions with keyword and the plain text,
it is to obtain encrypted keyword printed out

*/

#include "proj05_functions.h" //was used to reference header to test functions

string prepare_plaintext(const string &s){
    /*
    takes in a string, and put strips off all but lowercase alphabets,
    if length of the string is odd, add on character 'x'
    */
    string plain_text = "";
    string::size_type d = s.size();
    

    for(string::size_type i = 0; i< d ; i++){
        
        if (isalpha(s[i])){
            if (tolower(s[i]) == 'j')
            {continue;}
            else if (s[i] == plain_text.back())
            {plain_text.push_back('x');}
            
            else plain_text += tolower(s[i]);     
        }

    }

    if ((plain_text.size()) %2 !=0){
        plain_text.push_back('x');
    }
    
    return plain_text;
    }


string create_encoding(const string &key){
    /*
    takes in the keyword and putting in the form that can symbolize
    2-D form. it has length of 25 with 5x5 representative matrix

    */
    string key_square;
    for (auto charac: key){
        if (key_square.find(charac) == string::npos){
            key_square += charac;
        }
    }

    for (auto characs: alphabet_minus_j){
        if (key_square.find(characs) == string::npos){
            key_square.push_back(characs);
        }
    }

    
    return key_square;
}



string encode_pair(const string &pr, const string &key){
    /*
    with two characters to be encoded using encoding 2-D matrix,
    some vairables for indexes are defined each for better readability

    */
    string en_pair;

    int index_1 = key.find(pr[0]);
    int index_2 = key.find(pr[1]);

    int row_1 = index_1 / dim;
    int row_2 = index_2 / dim;

    int col_1 = index_1 % dim;
    int col_2 = index_2 % dim;


    if (col_1 == col_2){// same column
    
        if (row_1 == dim-1){
            en_pair.push_back(key[col_1]);
        }
        else {en_pair.push_back(key[index_1+dim]);}
        
        
        
        if (row_2 == dim-1){ // 4
        en_pair.push_back(key[col_2]);
        }        
        else{en_pair.push_back(key[index_2+dim]);}
    }

    else if (row_1 == row_2) { //same row

        if (col_1 == dim-1){
            en_pair.push_back(key[row_1*5]);
        }

        else {en_pair.push_back(key[index_1+1]);}


        if (col_2 == dim-1 ){ //4
            en_pair.push_back(key[row_2*5]);}

        else{en_pair.push_back(key[index_2+1]);}
            
    }

    else {
        int new_index_1 = row_1*5 + col_2;
        int new_index_2 = row_2*5 + col_1;


        en_pair.push_back(key[new_index_1]);
        en_pair.push_back(key[new_index_2]);

    }


    return en_pair;
}




string decode_pair(const string &pr, const string &key){
/*
opposite to encode_pair, takes in encoded, two-character input and 
uses key block matrix to print out original, decoded version of the pair
*/
string de_pair;

    int index_1 = key.find(pr[0]);
    int index_2 = key.find(pr[1]);

    int row_1 = index_1 / dim;
    int row_2 = index_2 / dim;

    int col_1 = index_1 % dim;
    int col_2 = index_2 % dim;


    if (col_1 == col_2){// same column
        if(row_1 == dim-5){
            de_pair.push_back(key[(dim-1)*dim + col_1]);
            de_pair.push_back(key[index_2-dim]);
        }
        else{
            de_pair.push_back(key[index_1-dim]);
            if(row_2 ==dim -5){
                de_pair.push_back(key[(dim-1)*dim+col_2]);
            }
            else{de_pair.push_back(key[index_2-dim]);}
            }   

    }


    else if (row_1 == row_2){ // same row

        if (col_1 == dim-5){

            de_pair.push_back(key[row_1*dim+(dim-1)]);
            de_pair.push_back(key[index_2-1]);
            }

        else{
            
            de_pair.push_back(key[index_1-1]);
            
            if (col_2 == dim-5){

            de_pair.push_back(key[row_2*dim+(dim-1)]);
            }

            else {de_pair.push_back(key[index_2-1]);}
        }
        
    }

    else {
        int new_index_1 = row_1*5 + col_2;
        int new_index_2 = row_2*5 + col_1;


        de_pair.push_back(key[new_index_1]);
        de_pair.push_back(key[new_index_2]);

    }


    return de_pair;


}


string encode(const string &plaintxt, const string &key){
    /*
    takes in plain txt and uses prepare_plaintext function to make it
    an even and compatible form of plain text, and uses encode_pair function
    to sort by each two-character then print out the encoded string
    */
    string encoded;
    string new_plaintext = prepare_plaintext(plaintxt);

    for (string::size_type i=0; i< new_plaintext.size(); i+=2){
    encoded += encode_pair(new_plaintext.substr(i,2),key);
    }
    return encoded;
}


string decode(const string &encodedtxt, const string &key){
    /*
    opposite to encode, takes in already encoded text string, and then
    uses decode_pair function to get back to original two-character,
    then puts it back together to decdoed(original) string
    */
    string decoded;

    for (string::size_type i = 0; i< encodedtxt.size(); i+=2){

        decoded += decode_pair(encodedtxt.substr(i,2),key);
    }

    return decoded;
}

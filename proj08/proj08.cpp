/*
Project 8
Creating KTurtle style data structure creator
Section 3
*/


#include "proj08.h"
#include <iostream>
using std::cout; using std::endl;
#include <map>
using std::map; 
#include <string>
using std::string; using std::stoi; using std::to_string;
#include <vector>
using std::vector;

#include<fstream>
using std::ifstream;

#include <utility>
using std::pair; using std::make_pair;

#include<sstream>
using std::ostringstream; using std::istringstream;


#include<iterator>
using std::istream_iterator;
#include<cctype>

Painter::Painter(const string &fname){
    /*
    Constructor with string input of file namespace
    sorts out input and puts into map each
    */
    ifstream infile;
    infile.open(fname);
    

    ostringstream oss;
    
    if (infile.eof()){
        error_log_.push_back("error: template argument 1 is invalid");// error if something empty inthere
    }


    while (!infile.eof()){
       getline(infile,line, '\n');
       if (line ==""){
           line_num--;
           break;
       }
        if (line[0] != '#' && line[0] !='R'){

        for (char li:line){
            
            if(!(isalnum(li) || li ==' ' || li=='#')){
                oss<<"error on line "<<line_num<<": unable to parse \""<<line<<"\"";
                error_log_.push_back(oss.str());
                continue;        // error out if any other than alphabet or number is inside        
            }

       }
        }
        
        Parse(line_num,line);//Parse out
        line_num++;
    
        
    }
}


void Painter::CreateCanvas2(int i, int j){
    /*
    Creating canvas for reating function
     going through each line from starting line i to line j; same function as createcanvas() below
    */
    
    
    for (int k = i ;k <= j; k++){

        
        if (lines__[k][0] == "SetDim"){
            SetDim(k,stoi(lines__[k][1]),stoi(lines__[k][2]));
            
            }
        else if (lines__[k][0] == "SetPenPosition"){
            SetPenPosition(k,stoi(lines__[k][1]),stoi(lines__[k][2]));
   
}

        else if (lines__[k][0] =="SetPenSymbol"){
            SetPenSymbol(i,stoi(lines__[i][1]));
        }
        else if (lines__[k][0] == "Draw"){
            Draw();
        }

        else if (lines__[k][0] =="Move"){
            Move(stol(lines__[k][1]));
        }

        else if (lines__[k][0] =="Turn"){
            Turn(stol(lines__[k][1]));
        }

        else if (lines__[k][0] =="Repeat"){
            int key =0;
            for (auto it = lines__.begin();it !=lines__.end(); ++it){
                if (it->second == lines__[k]){
                    key = it->first; //line_num
                }
            }
           
            
            
            
            Repeat( key,  stol(lines__[k][1]), lines__[k][2][0]-'0', lines__[k][2][2]-'0');
        }
    }
}

void Painter::CreateCanvas(){
    /*
    takes in every string and see the command in first key in the map and runs each function
    */
    
    for (int i =1;i<= line_num; i++){
        if (lines__[i][0] == "SetDim"){
            SetDim(i,stoi(lines__[i][1]),stoi(lines__[i][2]));
            
            }
        else if (lines__[i][0] == "SetPenPosition"){
            SetPenPosition(i,stoi(lines__[i][1]),stoi(lines__[i][2]));
   
}

        else if (lines__[i][0] =="SetPenSymbol"){
            SetPenSymbol(i,stoi(lines__[i][1]));
        }
        else if (lines__[i][0] == "Draw"){
            Draw();
        }

        else if (lines__[i][0] =="Move"){
            Move(stoi(lines__[i][1]));
        }

        else if (lines__[i][0] =="Turn"){
            Turn(stoi(lines__[i][1]));
        }

        else if (lines__[i][0] =="Repeat"){
            int key =0;
     
            for (auto it = lines__.begin();it !=lines__.end(); ++it){
                if (it->second == lines__[i]){
 
                    key = it->first; //line_num
                }// having command as key
            }
            Repeat( key,  stoi(lines__[i][1]), (lines__[i][2][0]-'0'), (lines__[i][2][2])-'0' );
        }
 

}
}


void Painter::Parse(int line_num,const std::string& line){
/*
parsing out each line and putinto the map
*/
        istringstream iss(line);
        lines_v = vector<string> (istream_iterator<string>(iss),istream_iterator<string>());
        lines_pair = make_pair(line_num,lines_v);
        lines__.insert(lines_pair);
        


        //line_num_line = make_pair(line_num, line);
        //lines_.insert(line_num_line);

}



void Painter::SetDim(int line_num, int x_dim, int y_dim){
    /*
    setting dimension and pushes back an error if theres no matching dimension
    */
    
    ostringstream oss;
    if (x_dim<10 ||x_dim >80) {
        oss<<"error on line "<<line_num<<": Row Dimension out of bounds";
        error_log_.push_back(oss.str());
    }

    else if (y_dim<10||y_dim>80){
        oss<<"error on line "<<line_num<<": Column Dimension out of bounds";
        error_log_.push_back(oss.str());
    }

    else{


        rows_ = x_dim;
        columns_= y_dim;
        canvas_ = vector<string>(rows_,string(columns_,' '));

    }
}

void Painter::SetPenPosition(int line_num, int x_pos, int y_pos){
    /*
    Sets the penposition for given input, if dimension i s off, throws an error into the error_log_
    */
    ostringstream oss;
    if (x_pos<0 ||x_pos >rows_) {
        oss<<"error on line "<<line_num<<": Pen cannot be placed on canvas at position "<<x_pos<<" "<<y_pos;
        error_log_.push_back(oss.str());
    }

    else if (y_pos<0||y_pos>columns_){
        oss<<"error on line "<<line_num<<": Pen cannot be placed on canvas at position "<<x_pos<<" "<<y_pos;
        error_log_.push_back(oss.str());
    }

    else{
        
        pen_position_=make_pair(x_pos,y_pos);

    }
}

void Painter::SetPenSymbol(int line_num, int pen_symbol){
    /*
    Sets pensymol by integer input,
    throws out an error if it exeeds or doesn't go over some number
    */
    ostringstream oss;
    if (pen_symbol>127 || pen_symbol<32){
        oss<<"error on line "<<line_num<<": Invalid Pen Symbol "<<pen_symbol;
        error_log_.push_back(oss.str());
    }
    else{
        pen_symbol_ = pen_symbol;
    }

}

void Painter::Draw(){
/*
putting symbol on current position given
*/
    canvas_[pen_position_.first][pen_position_.second] = pen_symbol_;
}

void Painter::Move(int n){
    if ( dir_ == direction::up){//up
        if (abs(pen_position_.first-n) >rows_){
            pen_position_.first = abs(pen_position_.first-n)%rows_;
        }

        else{
            pen_position_.first = abs(pen_position_.first-n);
        }
    }

    else if (dir_ == direction::down){//down
            if (pen_position_.first+n >=rows_){
            pen_position_.first = (pen_position_.first+n)%rows_;
        }

        else{
            pen_position_.first = (pen_position_.first)+n;
        }
    }

    else if (dir_ == direction::left){//left
        if((pen_position_.second-n)<0){
            if (n>columns_){
                pen_position_.second=columns_- abs(pen_position_.second-n%columns_);
            }
            else{
            pen_position_.second = columns_- abs(pen_position_.second-n);
            }
        }

        else{
            pen_position_.second = pen_position_.second -n;
        }

    }

    else {
        if((pen_position_.second+n)>=columns_){
            if (n>columns_){
                pen_position_.second=pen_position_.second - abs(columns_- n%columns_);
            }
            else{
            pen_position_.second=pen_position_.second - abs(columns_- n);
            }
        }

        else{
            pen_position_.second = pen_position_.second +n;
        } 

        
    }
}

void Painter::Turn(int n){
    /*
    turns rightward for each integer value of 1
    class direction is defined and being used
    */
    if (dir_ == direction::left){// left
        if((n%4)==1){
            dir_ = direction::up;
        }

        else if((n%4)==2){
            dir_ = direction::right;
        }

        else if((n%4)==3){
            dir_ = direction::down;
        }
    }

    else if (dir_ == direction::right){//right
            if((n%4)==1){
                dir_ = direction::down;
            }

            else if((n%4)==2){
                dir_ = direction::left;
            }

            else if((n%4)==3){
                dir_ = direction::up;
        }
    }

    else if (dir_ == direction::up){ // up
                if((n%4)==1){
                    dir_ = direction::right;
                }

                else if((n%4)==2){
                    dir_ = direction::down;
                }

                else if((n%4)==3){
                    dir_ = direction::left;
            }
    }

    else if (dir_ == direction::down){ //down
                if((n%4)==1){
                    dir_ = direction::left;
                }

                else if((n%4)==2){
                    dir_ = direction::up;
                }

                else if((n%4)==3){
                    dir_ = direction::right;
            }
    }

}


void Painter::Repeat(int line_num,int n, int start, int end){
    /*
    repeat function, thrwos out some errors if not passing the criteria under if condition
    goes back to createcanvas2 function to redefine start and end paraemeter
    */
    
    signed size = lines__.size();

    if (size <start){
        ostringstream oss;
        
        oss<<"error on line "<<line_num<<": Line "<<start<<" is not in the file";
        error_log_.push_back(oss.str());

        
    }

    
    if (start>end){
        ostringstream oss;
        oss<<"error on line "<<line_num<<": Repeat range must be ascending";
        error_log_.push_back(oss.str());
   
    }

    else {for (int i=0; i<n;i++){
        if (size<end){
        ostringstream oss;
        
        oss<<"error on line "<<line_num<<": Line "<<end<<" is not in the file";
        error_log_.push_back(oss.str());
      
            end =size;
            
        }
        
        if(line_num >start){
            ostringstream oss;
        oss<<"error on line "<<start+1<<": Repeat command contains itself or refers to previous commands; infinite loop!";
        
        error_log_.push_back(oss.str());
            lines__[line_num][2][0] = '5';
            if(error_log_.size()==3){
                // prevents repeating error from passing 3, limits the number ofrepeating error by poping the last
                error_log_.pop_back();
            }
        }
        
        CreateCanvas2(start,end);
        //runs createcanvas 2, starting,end line is different now
    }
    }

}
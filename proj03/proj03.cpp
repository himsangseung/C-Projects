/*
Rock-Paper-Scissor Program
  for this we will use:
  1 - rock
  2 - paper
  3 - scissors

*/

#include<iostream>
using std::cout; using std::cin; using std::endl; using std::boolalpha;



int winning(long plays){
/*
Function for being 1(rock),2(paper),and 3(scissors) as input and return winning move
*/
        switch (plays){
            case 1: return 2; 
            case 2: return 3; 
            case 3: return 1; 
            
     }

    
}

int strategy1(long player, long previous_result, long previous_play, long opponent_play){
/*
Function for taking previous play and get the winning move
*/
     return winning(previous_play); //return winning move 


}

int strategy2(long player, long previous_result, long previous_play, long opponent_play){

/*
Function for stick-or-switch strategy
*/
    if (player == 1){// If Player1
        if (previous_result == 0 ||previous_result ==1){
            return previous_play; 
            //if tied or won previously, return the last move
        }

        else 
            return opponent_play;
    }

    else if (player ==2){// if Player2
        if(previous_result == 0|| previous_result ==2){

            return previous_play;
            //if tied or won previously, return the last move
        }
        else
            return opponent_play;
    }

}


int strategy3(long player, long previous_result, long previous_play, long opponent_play){

/*
Function for stick-or-win strategy
*/
    if (player == 1){
        if (previous_result == 0 || previous_result ==1){
            return previous_play; 
        }

        else 
             
            return winning(opponent_play);
    }

    else if (player == 2){
        if(previous_result == 0||previous_result ==2){

            return previous_play;
        }
        else
            //long play2 = winning(opponent_play);
            return winning(opponent_play);
    }

}


int score_round(long p1, long p2){
/*
Function for announcing winner or tie
*/
    if (p1>p2) 
        {if (p1==3 && p2 ==1)
            {return 2;}
        return 1;
        }

    else if (p2>p1) 
        {if (p2==3 && p1 ==1)
            {return 1;}
        return 2;}

    else {return 0;}

}

// MAIN IS BELOW, DON'T CHANGE

int main() {
  cout << boolalpha;   // print true or false for bools
  int test;
  cin >> test;
  
  switch (test) {
  case 1 : {   // strategy 1
    long player, previous_result, previous_play, opponent_play;
    cin >> player >> previous_result >> previous_play >> opponent_play;
    cout << strategy1(player, previous_result, previous_play, opponent_play) << endl;
    break;
  } // of case 1

  case 2:{    // strategy 2
    long player, previous_result, previous_play, opponent_play;
    cin >> player >> previous_result >> previous_play >> opponent_play;
    cout << strategy2(player, previous_result, previous_play, opponent_play) << endl;
    break;
  } // of case 2

  case 3: {    // strategy 3
    long player, previous_result, previous_play, opponent_play;
    cin >> player >> previous_result >> previous_play >> opponent_play;
    cout << strategy3(player, previous_result, previous_play, opponent_play) << endl;
    break;
  } // of case 3

  case 4: {       // score result
    long p1, p2;
    cin >> p1 >> p2;
    cout << score_round(p1, p2) << endl;
    break;
  } // of case 4
    
  } // of switch
} // of main


	

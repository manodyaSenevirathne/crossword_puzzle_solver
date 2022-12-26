/*

 ██████╗██████╗  ██████╗ ███████╗███████╗    ███████╗██╗      █████╗ ██╗   ██╗███████╗██████╗     ██████╗  ██████╗  ██████╗  ██████╗ 
██╔════╝██╔══██╗██╔═══██╗██╔════╝██╔════╝    ██╔════╝██║     ██╔══██╗╚██╗ ██╔╝██╔════╝██╔══██╗    ╚════██╗██╔═████╗██╔═████╗██╔═████╗
██║     ██████╔╝██║   ██║███████╗███████╗    ███████╗██║     ███████║ ╚████╔╝ █████╗  ██████╔╝     █████╔╝██║██╔██║██║██╔██║██║██╔██║
██║     ██╔══██╗██║   ██║╚════██║╚════██║    ╚════██║██║     ██╔══██║  ╚██╔╝  ██╔══╝  ██╔══██╗     ╚═══██╗████╔╝██║████╔╝██║████╔╝██║
╚██████╗██║  ██║╚██████╔╝███████║███████║    ███████║███████╗██║  ██║   ██║   ███████╗██║  ██║    ██████╔╝╚██████╔╝╚██████╔╝╚██████╔╝
 ╚═════╝╚═╝  ╚═╝ ╚═════╝ ╚══════╝╚══════╝    ╚══════╝╚══════╝╚═╝  ╚═╝   ╚═╝   ╚══════╝╚═╝  ╚═╝    ╚═════╝  ╚═════╝  ╚═════╝  ╚═════╝ v0.1
                                                                                                                                                                                                     
 - THE ULTIMATE CROSSWORD PUZZLE SOLVER

 
 */

#include <stdio.h>

// Variables
#define xSIZE 5
#define ySIZE 5

char grid[ySIZE][xSIZE] =         { {'#','#','#','#','#'},
                                    {'*','*','*','#','*'},
                                    {'#','#','#','#','#'},
                                    {'*','*','*','*','*'},
                                    {'#','#','#','*','*'}};

char wordsList[10][10] = {"hello","look","tan","brryr","brrnr","car"};


struct entry
{
    int number_of_letters;
    char word[10]; 
    int filled ;
    int oriantation ;
    int xPos, yPos; 

    char eligible_words[10][20];
    int eligible_words_curser ;


};
typedef struct entry Entry;

Entry crossword_entries[10];
int crossword_entries_curser = 0;





//utility functions
void printgrid(char grid[ySIZE][xSIZE] ){   
    for (int i = 0; i < ySIZE; i++)
    {
        for (int j = 0; j < xSIZE; j++)
        {
            printf("%c",grid[i][j]);
        }
        printf("\n");
        
    }
}

int size_of_string(char* _word ){
    int i=0;
    while ( *(_word+i) != '\0') { i++; }
    return i;

}

int isletter(char x){
    if (( x >= 'a' && x<= 'z' ) || ( x >= 'A' && x<= 'Z' ))
    {
       return 1 ;
    }else return 0;
    
}

void printEntry(Entry _entry){
    // for debuging purposes
    printf("word:%s\nNo.letters%d\nfilled:%d\noriantaion:%d\nxPos:%d yPos:%d\n", _entry.word,_entry.number_of_letters,_entry.filled,_entry.oriantation,_entry.xPos,_entry.yPos);
    for (int i = 0; i < _entry.eligible_words_curser; i++)
    {
        printf("%s",_entry.eligible_words[i]);
    }
    printf("\n-----------------\n");

}

void stringcpy(char* destination, const char* source)
{
    while (*source != '\0')
    {
        *destination = *source;
        destination++;
        source++;
    }
    *destination = '\0';
}
//


int search_grid(char* word, char grid[ySIZE][xSIZE])
{
    /*

        looks for the presence of the word in the grid

    */

   
    int grid_size = xSIZE;

    // Check if the word is present horizontally
    for (int i = 0; i < grid_size; i++)
    {
        for (int j = 0; j < grid_size - size_of_string(word) + 1; j++)
        {
            int found = 1;
            for (int k = 0; k < size_of_string(word); k++)
            {
                if (word[k] != grid[i][j + k])
                {
                    found = 0;
                    break;
                }
            }

            if (found)
            {
                return 1;
            }
        }
    }
// Check if the word is present vertically
    for (int i = 0; i < grid_size; i++)
    {
        for (int j = 0; j < grid_size - size_of_string(word) + 1; j++)
        {
            int found = 1;
            for (int k = 0; k < size_of_string(word); k++)
            {
                if (word[k] != grid[j + k][i])
                {
                    found = 0;
                    break;
                }
            }

            if (found)
            {
                return 1;
            }
        }
    }

    return 0;
}

void append_words(char _word[], Entry* _entry){
    
    int i=0;
    while ( *(_word+i) != '\0') { 
        
       
        _entry->eligible_words[_entry->eligible_words_curser][i] = *(_word+i);
        i++;
       
     }
     //printf("%s*",_entry.eligible_words[_entry.eligible_words_curser]);   // <--- for dubugging
    

    _entry->eligible_words_curser++;
    
}

void append_entries(char _word[], int numberOfLetters , int filled, int oriantation , int xPos, int yPos ){
    
    stringcpy(crossword_entries[crossword_entries_curser].word , _word) ; 
    crossword_entries[crossword_entries_curser].number_of_letters = numberOfLetters;
    crossword_entries[crossword_entries_curser].filled = filled;
    crossword_entries[crossword_entries_curser].oriantation = oriantation;
    crossword_entries[crossword_entries_curser].xPos = xPos;
    crossword_entries[crossword_entries_curser].yPos = yPos;


    crossword_entries_curser++; 

}


int pushword(int xPos, int yPos, char* _word, int oriantaion){
  
  /*
        this function check if the word can be inserted or not into the grid
  */


        if(oriantaion == 1){
            for (int i = 0; i < size_of_string(_word); i++)
        {
            if( isletter(grid[yPos][xPos + i]) && !(grid[yPos][xPos+i] == *(_word+i) || grid[yPos][xPos+i] == *(_word+i)+ 'a'-'A'|| grid[yPos][xPos+i] == *(_word+i)+ 'A'-'a')){return 0;}
            
        }

        }else if(oriantaion == 2){
            for (int i = 0; i < size_of_string(_word); i++)
        {
            if( isletter(grid[yPos + i][xPos]) && !(grid[yPos+i][xPos] == *(_word+i) || grid[yPos+i][xPos] == *(_word+i)+ 'a'-'A'|| grid[yPos+i][xPos] == *(_word+i)+ 'A'-'a')){return 0;}
            
        }
        }
    return 1;
       

}

void fill(int xPos, int yPos, char* _word, int oriantaion){
   
   /*
        fill the grid using the word
   */
   
        if(oriantaion == 1){
            for (int i = 0; i < size_of_string(_word); i++)
        {
            
            if(grid[yPos][xPos+i] != *(_word+i) && grid[yPos][xPos+i] != *(_word+i)+'a'-'A' && grid[yPos][xPos+i] != *(_word+i)+'A'-'a' )grid[yPos][xPos+i] = *(_word+i);
            
        }

        }else if(oriantaion == 2){
            for (int i = 0; i < size_of_string(_word); i++)
        {
            
            if(grid[yPos+i][xPos] != *(_word+i) && grid[yPos+i][xPos] != *(_word+i)+'a'-'A' &&  grid[yPos+i][xPos] != *(_word+i)+'A'-'a')grid[yPos+i][xPos] = *(_word+i);
            
        }
        }

        

}

void unfill(int xPos, int yPos, char* _word, int oriantaion){
   
   /*
        unfill the grid for the given word
   */
   
        if(oriantaion == 1){
            for (int i = 0; i < size_of_string(_word); i++)
        {
            
            grid[yPos][xPos+i] = *(_word+i);
        }

        }else if(oriantaion == 2){
            for (int i = 0; i < size_of_string(_word); i++)
        {
            
            grid[yPos+i][xPos] = *(_word+i);
        }
        }

        

}




void read_grid(){

    //tempory varibles
    int horizontal_wCount=0, vertical_wCount=0 , curser = 0,filled = 0,xPos,yPos;
    char reading_word[10] = "";

    //horizontal reading

    for (int i = 0; i < ySIZE; i++)
    {
        
        curser = 0;
        for (int j = 0; j < xSIZE; j++)
        {
            if(curser == 0 && (grid[i][j] == '#' || isletter(grid[i][j])) && (grid[i][j+1] == '#' || isletter(grid[i][j+1])) ){
                
                xPos = j;
                yPos = i;
                filled = isletter(grid[i][j]) && isletter(grid[i][j+1]);
                curser++;   
                
                }

            else if(curser > 0 && ((grid[i][j+1] != '#' && !isletter(grid[i][j+1])) || (j == xSIZE-1 ) )){
                
                // save reading word to reading_word varible
                for (int k = 0; k < curser+1; k++)
                {
                    reading_word[k] = grid[i][j-curser+k];
                }
 
                append_entries(reading_word,curser+1,filled,1,xPos,yPos);


                // clear reading_word varible
                for (int i = 0; i < curser+1; i++)
                {
                    reading_word[i] = *"";
                }
                
                curser = 0;
                filled = 0;
                horizontal_wCount++ ; 
            }

            else if(curser >0 ){curser++;}
                
        }
        
    }



    // vertical reading
    for (int i = 0; i < xSIZE; i++)
    {   
        
        curser = 0;
        for (int j = 0; j < ySIZE; j++)
        {
            if(curser == 0 && (grid[j][i] == '#' || isletter(grid[j][i]))  && (grid[j+1][i] == '#' || isletter(grid[j+1][i])) ){
                
                xPos = i;
                yPos = j;
                filled = isletter(grid[j][i]) && isletter(grid[j+1][i]);
                curser++;
            }

            else if(curser > 0 && ((grid[j+1][i] != '#' && !isletter(grid[j+1][i] )) || (j == ySIZE-1 ) )){

                  
                for (int k = 0; k < curser+1; k++)
                {
                    reading_word[k] = grid[j-curser+k][i];
                }
                    
                append_entries(reading_word,curser+1,filled,2,xPos,yPos);

                for (int i = 0; i < curser+1; i++)
                {
                    reading_word[i] = *"";
                }
                
                curser = 0;
                filled = 0;
                vertical_wCount++ ; 
            }
            else if(curser >0 ){curser++;
            
              
            
            }
        }
        
    }


}

void checkEligibleWords(){

    for (int i = 0; i < crossword_entries_curser; i++)
    {   
       
        for (int j = 0; j < 10; j++)
        {
            
            if (( crossword_entries[i].number_of_letters == size_of_string(wordsList[j]) ) && !crossword_entries[i].filled)
            {
                append_words(wordsList[j],&crossword_entries[i]);
    
            
            }
        }
        
       
        
    }

    

}

int solve(int entry_id){

    if (entry_id == crossword_entries_curser)
    {
        return 1;
    }
    
    // if that entry is filled don't do anything , go the next one
    if(crossword_entries[entry_id].filled){

        if (solve(entry_id + 1))
        {
            return 1;
        }
        else return 0;
        
    }
    

    for (int w = 0; w < crossword_entries[entry_id].eligible_words_curser; w++)
    {
        if(search_grid(crossword_entries[entry_id].eligible_words[w],grid)){continue;}
        if ( pushword(crossword_entries[entry_id].xPos , crossword_entries[entry_id].yPos, crossword_entries[entry_id].eligible_words[w],crossword_entries[entry_id].oriantation) )
        {
            
            fill(crossword_entries[entry_id].xPos , crossword_entries[entry_id].yPos, crossword_entries[entry_id].eligible_words[w],crossword_entries[entry_id].oriantation);
            
            
            if (solve(entry_id + 1))
            { 
                return 1;
            }


            unfill(crossword_entries[entry_id].xPos , crossword_entries[entry_id].yPos, crossword_entries[entry_id].word,crossword_entries[entry_id].oriantation);
        }
        // printgrid(grid);
    }
    
    
    return 0;

}


int main(){

    read_grid(grid);
    checkEligibleWords();

    if(solve(0)){
        printf("solved\n");
        printgrid(grid);
    }else{
        printf("not solved");
    }


   

    

    // for (int i = 0; i < crossword_entries_curser; i++)
    // {
    //    printEntry(crossword_entries[i]);
    // }
    


}
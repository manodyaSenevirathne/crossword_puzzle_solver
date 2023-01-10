/*

 ██████╗██████╗  ██████╗ ███████╗███████╗    ███████╗██╗      █████╗ ██╗   ██╗███████╗██████╗     ██████╗  ██████╗  ██████╗  ██████╗ ©
██╔════╝██╔══██╗██╔═══██╗██╔════╝██╔════╝    ██╔════╝██║     ██╔══██╗╚██╗ ██╔╝██╔════╝██╔══██╗    ╚════██╗██╔═████╗██╔═████╗██╔═████╗
██║     ██████╔╝██║   ██║███████╗███████╗    ███████╗██║     ███████║ ╚████╔╝ █████╗  ██████╔╝     █████╔╝██║██╔██║██║██╔██║██║██╔██║
██║     ██╔══██╗██║   ██║╚════██║╚════██║    ╚════██║██║     ██╔══██║  ╚██╔╝  ██╔══╝  ██╔══██╗     ╚═══██╗████╔╝██║████╔╝██║████╔╝██║
╚██████╗██║  ██║╚██████╔╝███████║███████║    ███████║███████╗██║  ██║   ██║   ███████╗██║  ██║    ██████╔╝╚██████╔╝╚██████╔╝╚██████╔╝
 ╚═════╝╚═╝  ╚═╝ ╚═════╝ ╚══════╝╚══════╝    ╚══════╝╚══════╝╚═╝  ╚═╝   ╚═╝   ╚══════╝╚═╝  ╚═╝    ╚═════╝  ╚═════╝  ╚═════╝  ╚═════╝ v1.0
                                                                                                                                                                                                     
 - THE ULTIMATE CROSSWORD PUZZLE SOLVER 

authors:
SENEVIRATHNE W.A.M.P.   (E/19/366)
DE SILVA D.M.           (E/18/059)

Note: Here a backtracking algorithm is used in 2 ways for solving.


1st method :                                                                   2nd method : 
                        ┌───────┐   ┌───────┐   ┌───────┐                                   ┌───────┐   ┌───────┐   ┌───────┐
             entry1     │ word1 │   │ word2 │   │ word3 │...                     word1      │entry1 │   │entry2 │   │entry3 │...
                        └───────┘   └───────┘   └───────┘                                   └───────┘   └───────┘   └───────┘
                            ↓                                 ------------->                    ↓
                        ┌───────┐   ┌───────┐                   if it takes                 ┌───────┐   ┌───────┐ 
             entry2     │ word1 │   │ word2 │  ...              too much time    word2      │entry1 │   │entry2 │  ...
                        └───────┘   └───────┘                   to solve or                 └───────┘   └───────┘
                            ↓                                   can't use                       ↓
                        ┌───────┐   ┌───────┐   ┌───────┐                                   ┌───────┐   ┌───────┐   ┌───────┐
             entry3     │ word1 │   │ word2 │   │ word3 │ ...                    word3      │entry1 │   │entry2 │   │entry3 | ...
                        └───────┘   └───────┘   └───────┘                                   └───────┘   └───────┘   └───────┘
                .                                                                   .
                .                                                                   .
                .                                                                   .

 
 */

#include <stdio.h>
#include <string.h>     

// Variables
#define xSIZE 50
#define ySIZE 50
int grid_XSize = xSIZE;
int grid_YSize = ySIZE;
char grid[ySIZE][xSIZE];

int grid_xsizeChanged = 0;


#define maxWords 50
#define maxSizeofWord 10

char wordsList[maxWords][maxSizeofWord] ;
int wordcounter = 0;


char used_words[maxWords][maxSizeofWord];
int used_entries[100];

struct entry
{
    int number_of_letters;
    char word[maxSizeofWord]; 
    int filled ;
    int oriantation ;
    int xPos, yPos; 

    char eligible_words[40][maxSizeofWord];
    int eligible_words_curser ;



};
typedef struct entry Entry;

typedef struct  _
{
    char word[maxSizeofWord];
} temp_save;            //used for return strings - 'temp_save' because returned string is temporarily saving previous state of entry


Entry crossword_entries[100];
int crossword_entries_curser = 0;



//utility functions
void printgrid(char grid[ySIZE][xSIZE]){   
    
    // print the grid

    for (int i = 0; i < grid_YSize; i++)
    {
        for (int j = 0; j < grid_XSize; j++)
        {
            printf("%c",grid[i][j]);
        }
        printf("\n");
        
    }
}

void printwords(char grid[maxWords][maxSizeofWord] ){   
    
    /*for debugging purposes - print the wordlist*/
    for (int i = 0; i < maxWords; i++)
    {
        for (int j = 0; j < maxSizeofWord; j++)
        {
            printf("%c",grid[i][j]);
        }
        printf("\n");
        
    }
}

int size_of_string(char* _word ){
    //return the size of given string
    int i=0;
    while ( *(_word+i) != '\0') { i++; }
    return i;

}

int isletter(char x){
    //check the given character is within the ASCII range of A-Z or a-z 
    if (( x >= 'a' && x<= 'z' ) || ( x >= 'A' && x<= 'Z' ))
    {
       return 1 ;
    }else return 0;
    
}

void strupper(char _word[maxSizeofWord]){

    for (int i = 0; i < size_of_string(_word); i++)
    {
        _word[i] &= ~32; 
    }
    

}

void printEntry(Entry _entry){
    // for debuging purposes
    printf("word:%s\nNo.letters%d\nfilled:%d\noriantaion:%d\nxPos:%d yPos:%d\n", _entry.word,_entry.number_of_letters,_entry.filled,_entry.oriantation,_entry.xPos,_entry.yPos);
    for (int i = 0; i < _entry.eligible_words_curser; i++)
    {
        printf("%s ",_entry.eligible_words[i]);
    }
    printf("\n-----------------\n");

}

void stringcpy(char* destination, const char* source)
{   //copy strings
    while (*source != '\0')
    {
        *destination = *source;
        destination++;
        source++;
    }
    *destination = '\0';
}

int isthereAspace(char grid[ySIZE][xSIZE]){

    /*check for '#'s in the grid*/

     for (int i = 0; i < grid_YSize; i++)
    {
        for (int j = 0; j < grid_XSize; j++)
        {
            if (grid[i][j]=='#')
        {
            return 1;
        }
            
        }
        
    }

    return 0;

}

int is_word_in_list( char word[maxSizeofWord],  char list[100][maxSizeofWord], size_t list_size) {
    
    /*check if the given word is already in the given list*/

    for (size_t i = 0; i < list_size; i++) {
        if (strcmp((const char*)word, (const char*)list[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int searchInvalidInputs_ingrid(char grid[ySIZE][xSIZE]){

    /*
        search for invalid charactors in the grid
    */

    for (int i = 0; i < grid_YSize; i++)
    {
        for (int j = 0; j < grid_XSize; j++)
        {
            if (!(isletter(grid[i][j]) || grid[i][j]=='#' || grid[i][j] == '*'))
        {
            return 1;
        }
            
        }
        
    }
    return 0;

}

int isExceedTreshold(int threshold){
    /*
        Use for check whether each entry has more words than threshold
    */

    int returnVar = 1;

    for (int i = 0; i < crossword_entries_curser; i++)
    {
        if(crossword_entries->eligible_words_curser > threshold)  returnVar &=1;
        else returnVar &=0 ; 
    }
    return returnVar;
}
//



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
            if( isletter(grid[yPos][xPos+i]) && ((grid[yPos][xPos+i] &~32)  != (*(_word+i) &~32) )){return 0;}
            
            
        }

        }else if(oriantaion == 2){
            for (int i = 0; i < size_of_string(_word); i++)
        {
            if(isletter(grid[yPos+i][xPos]) && ( (grid[yPos+i][xPos] &~32) != (*(_word+i) &~32) )){return 0;}
            
        }

        }
    return 1;
       

}

temp_save fill(int xPos, int yPos, char* _word, int oriantaion){
   
   /*
        fill the grid using the word
   */

        temp_save previous_word;
   
        if(oriantaion == 1){
            for (int i = 0; i < size_of_string(_word); i++)
        {
            previous_word.word[i] = grid[yPos][xPos+i];
            grid[yPos][xPos+i] = *(_word+i);
        }

        }else if(oriantaion == 2){
            for (int i = 0; i < size_of_string(_word); i++)
        {
            
            previous_word.word[i] = grid[yPos+i][xPos];
            grid[yPos+i][xPos] = *(_word+i);
        }
        }
    return previous_word;
        

}

void unfill(int xPos, int yPos, char* _word, int oriantaion,int size_of_word){
   
   /*
        unfill the grid for the given word
   */
   
        if(oriantaion == 1){
            for (int i = 0; i < size_of_word; i++)
        {   
            
            grid[yPos][xPos+i] = *(_word+i);
        }

        }else if(oriantaion == 2){
            for (int i = 0; i < size_of_word; i++)
        {
            
           grid[yPos+i][xPos] = *(_word+i);
        }
        }

        

}


// functions for extract/find informations about spaces

void read_grid(){


    //tempory varibles
    int horizontal_wCount=0, vertical_wCount=0 , curser = 0,filled = 0,xPos,yPos;
    char reading_word[maxSizeofWord] = "";

    //horizontal reading

    for (int i = 0; i < grid_YSize; i++)
    {
        
        curser = 0;
        for (int j = 0; j < grid_XSize; j++)
        {
            if(curser == 0 && (grid[i][j] == '#' || isletter(grid[i][j])) && (grid[i][j+1] == '#' || isletter(grid[i][j+1])) ){
                
                xPos = j;
                yPos = i;
                filled = isletter(grid[i][j]) && isletter(grid[i][j+1]);
                curser++;   
                
                }

            else if(curser > 0 && ((grid[i][j+1] != '#' && !isletter(grid[i][j+1])) || (j == grid_XSize-1 ) )){
                
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
    for (int j = 0; j < grid_XSize; j++)
    {   
        
        curser = 0;
        for (int i = 0; i < grid_YSize; i++)
        {
            if(curser == 0 && (grid[i][j] == '#' || isletter(grid[i][j]))  && (grid[i+1][j] == '#' || isletter(grid[i+1][j])) ){
                
                xPos = j;
                yPos = i;
                filled = isletter(grid[i][j]) && isletter(grid[i+1][j]);
                curser++;
            }

            else if(curser > 0 && ((grid[i+1][j] != '#' && !isletter(grid[i+1][j] )) || (i == grid_YSize-1 ) )){

                  
                for (int k = 0; k < curser+1; k++)
                {
                    reading_word[k] = grid[i-curser+k][j];
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

    /*check for suitable words for given space*/

    for (int i = 0; i < crossword_entries_curser; i++)
    {   
       
        for (int j = 0; j < maxWords ; j++)
        {
            if( !isletter(wordsList[j][0]))continue;
            if (( crossword_entries[i].number_of_letters == size_of_string(wordsList[j]) ) && !crossword_entries[i].filled)
            {
                append_words(wordsList[j],&crossword_entries[i]);
    
            
            }
        }
        
       
        
    }

    

}

// solving functions

int solve(int entry_id){
    /*
        Solving algorithm - backtracking for the grid
    */
    
    if (entry_id == crossword_entries_curser)
    {
        return 1;
    }

    if(!isthereAspace(grid)){   //if there is no spaces
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
        
       
            //printf("\n entry : %d trying word : %s \n",entry_id, crossword_entries[entry_id].eligible_words[w]); //<--- for debuging purposes
           

            while(is_word_in_list(crossword_entries[entry_id].eligible_words[w],used_words,100)){

                if(w+1 != crossword_entries[entry_id].eligible_words_curser)w++;
                else return 0;
            }

            

        if ( pushword(crossword_entries[entry_id].xPos , crossword_entries[entry_id].yPos, crossword_entries[entry_id].eligible_words[w],crossword_entries[entry_id].oriantation)  )
        {
            

           
            temp_save temp = fill(crossword_entries[entry_id].xPos , crossword_entries[entry_id].yPos, crossword_entries[entry_id].eligible_words[w],crossword_entries[entry_id].oriantation);
            stringcpy(used_words[entry_id], crossword_entries[entry_id].eligible_words[w]);

            // printf("\n --------%s-------------\n",temp.word);        //<--- for debuging purposes
            // printgrid(grid);
            // printf("\n ---------------------\n");
            
            if (solve(entry_id + 1))
            { 
                return 1;
            }else{
                unfill(crossword_entries[entry_id].xPos , crossword_entries[entry_id].yPos, temp.word,crossword_entries[entry_id].oriantation,crossword_entries[entry_id].number_of_letters);
                stringcpy(used_words[entry_id], "");

                continue;
            }


            
            
        }
        
    }
    
    
    return 0;

}

int solve2(int word_id){
    /*
        Solving algorithm 2 - backtracking for wordlist
    */
    
    if (word_id == wordcounter)
    {
        return 1;
    }

    // if(!isthereAspace(grid)){   //if there is no spaces
    //     return 1;
    // }
    

    

    for (int c = 0; c < crossword_entries_curser; c++)
    {  
        
       
            //printf("\n entry : %d trying word : %s \n",entry_id, crossword_entries[entry_id].eligible_words[w]); //<--- for debuging purposes
           
            

        if ( pushword(crossword_entries[c].xPos , crossword_entries[c].yPos, wordsList[word_id],crossword_entries[c].oriantation)  && (size_of_string(wordsList[word_id]) == crossword_entries[c].number_of_letters) && !crossword_entries[c].filled)
        {
            
           
           
            temp_save temp = fill(crossword_entries[c].xPos , crossword_entries[c].yPos, wordsList[word_id],crossword_entries[c].oriantation);
            crossword_entries[c].filled = 1;


            // printf("\n --------%s-------------\n",temp.word);        //<--- for debuging purposes
            // printgrid(grid);
            // printf("\n ---------------------\n");
            
            if (solve2(word_id + 1))
            { 
                return 1;
            }else{
                unfill(crossword_entries[c].xPos , crossword_entries[c].yPos, temp.word,crossword_entries[c].oriantation,crossword_entries[c].number_of_letters);
                crossword_entries[c].filled = 0;

                continue;
            }


            
            
        }
        if(crossword_entries[c].filled){
            continue;

        }
        
    }
    
    
    return 0;

}

// functions for taking inputs

void getGridInput(char grid[ySIZE][xSIZE])
{
    /*
        for taking grid input
    */
    for (int i = 0; i < ySIZE; i++)
    {
        char text[xSIZE];
        fgets(text, xSIZE, stdin);
        
        if(!grid_xsizeChanged){
            grid_XSize = size_of_string(text)-1;
            grid_xsizeChanged = 1;}
        
        if (text[0] == '\n')
        {   
            grid_YSize = i;
            stringcpy(grid[i], "\0");
            break;
        }
        stringcpy(grid[i], text);
    }
}

int input_words(char _wordslist[maxWords][maxSizeofWord]){

    /*
        for taking inputs for word list
    */
    int i=0;
    int isinvalid = 0;
    
    
    char line[maxSizeofWord];
    
    while (scanf("%[^\n]s", line) == 1) 
    {
        int itterVar = size_of_string(line);
        for (int k = 0; k < itterVar; k++)
        {
            
            if (!isletter(line[k]) )
            {
                isinvalid =1;
                
            }
            
        }
        
        getchar();
        stringcpy(_wordslist[i],line);
        wordcounter++;
        //strupper(_wordslist[i]);
        stringcpy(line, "");
        i++;
    }

    
    return isinvalid;
    
}



int main(){
    
    getGridInput(grid);
    //printf("%d %d",grid_XSize,grid_YSize);                                                               // for debugging purposes - use to see the grid input is correctly working
    
    int words_invalid = input_words(wordsList);
    int is_there_invalid_charactors_in_grid = searchInvalidInputs_ingrid(grid);


     if (is_there_invalid_charactors_in_grid || words_invalid)      
    {
        //printf("INVALID INPUT grid:%d words:%d",is_there_invalid_charactors_in_grid, words_invalid);     // for debugging purposes - use to see the which cause for invalid input    
        printf("INVALID INPUT");
        return 0;
    }

    //  printwords(wordsList);                                                                              // for debugging purposes - use to see the words list is correctly working

    

    read_grid(grid);            // extract informations from the grid
    checkEligibleWords();       // find suitable words for each space



    int solved = 0;
    if( wordcounter >= crossword_entries_curser || !isExceedTreshold(4)){
        /*
            Use 1st Algorithm when there are more words given than number of spaces or number of words that can be used for fill a space is less than given treshold
        */
       
    if(solve(0) ){

        solved = 1;
    }else{
        solved = 0;
    }

    }else{

        /*
            otherwise use 2nd Algorithm
        */
               
    if(solve2(0) ){

        solved = 1;
    }else{
        solved = 0;
    }


    }
    

    // Output for succesesfull input
    if(solved){

        printgrid(grid);
    }else{
        printf("IMPOSSIBLE");
    }

   

    
    // // for debugging purposes - use to see the information about spaces in puzzle
    
    // for (int i = 0; i < crossword_entries_curser; i++)
    // {
    //    printEntry(crossword_entries[i]);
    // }
    


}
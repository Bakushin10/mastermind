#include <stdio.h>
#include <stdlib.h>

/*

Shin Nagai
Mastermind Program
10/04/2015

*/

//function prototype
int getInt();
int** getIntArray(int row, int col);
void freeArray(int** intArray,int row, int* perm);
void printPerms(int* perm,int n,int k, int** intAray, int col,int row);
int checkBlack(int* perm, int n, int** intArray, int col, int row);
int checkWhite(int* perm, int n, int** intArray, int col, int row,int* used,int usedCount,int i);

int counter=0;

int main(){

    int loop = getInt();
    int i;

    for(i=0;i<loop;i++){
        int row = getInt();
        int color = getInt();
        int col = getInt();
        int** intArray = getIntArray(row,col); // get array
        int* perm = malloc(sizeof(int)*(row+1));//allocate row+1
        int p;
        for(p=0;p<row;p++)
            perm[p] = p;
        ///generate permutation
        printPerms(perm,0,color,intArray,col,row);
        printf("%i\n",counter);
        freeArray(intArray,col,perm);//free up all mallocs
        counter = 0;
    }
    return 0;

}///end of main

int checkWhite(int* perm, int n, int** intArray, int col,int row,int* blackused, int blackusedCount,int i){

    int j,p,m;
    int* used = malloc(sizeof(int)*(row+3));
    int sizeOfUsed=0;
    int whiteCount=0;
    int flag=0; ///flag prevents increment from happening
    int a;

        for(j=0;j<row;j++){

            for(p=0;p<row;p++){
                    ///check if a word is same and not same position
                    ///because we are checking a white peg
                    if((perm[p] == intArray[i][j]) && (p != j)){

                            /// this for loop checks if permutation is used for white peg
                            for(m=0;m<sizeOfUsed;m++){
                                if(p == used[m])
                                    flag =1;
                            }
                            ///this for loop checks if permutation is used for black peg
                            for(m=0;m<blackusedCount;m++){
                                if(p == blackused[m]) //compare the position
                                    flag=1;
                            }
                            ///this for loop checks if intArray is used for black peg
                            for(m=0;m<blackusedCount;m++){
                                if(j == blackused[m]) //compare the position
                                    flag=1;
                            }
                            if(flag == 0){
                                whiteCount++;
                                used[sizeOfUsed] = p;
                                sizeOfUsed++;
                                p=row;//terminates p for loop
                            }
                            flag=0;///put the flag back to 0 every time
                    }
            }
        }//end of inner for

        if(whiteCount != intArray[i][row+1]){
            free(used);
            return 0;
        }
        ///frees used
        free(used);
        return 1;
}//end of checkBlack

int checkBlack(int* perm, int n, int** intArray, int col,int row){
        int a;
        int i,j;
        int blackCount=0;
        int* blackused = malloc(sizeof(int)*(row+1));///this is a used function black
        int usedCount=0;

    for(i=0;i<col;i++){
        for(j=0;j<(row);j++){
            if(perm[j] == intArray[i][j]){
                blackCount++;
                blackused[usedCount] = j;///save a position of a black peg
                usedCount++;
            }//end of if
        }//end of inner for
        if(blackCount == intArray[i][row]){
            int whiteCount = checkWhite(perm,n+1,intArray,col,row,blackused,usedCount,i);
                if(whiteCount == 1){
                    ///if white is 1, then check the next testcase
                    ///so put everything back to initial conditions
                    blackCount=0;
                    int s;
                    for(s=0;s<usedCount;s++)
                        blackused[s]='\0';
                        usedCount=0;
                }else
                    return 0;
        }
        else{
            free(blackused);
            return 0;
        }
	}//end of outer for

	free(blackused);

    return 1;
}//end of checkBlack

void printPerms(int* perm,int n,int k,int** intArray, int col,int row){

    int i;
    if (n == row){
       ///this is a check function for black and white
       ///this function will return 1 if a testcase passes all clues
       int cb = checkBlack(perm,n+1,intArray,col,row);
       //
       if(cb == 1){
            counter++;
       }
    }//end of if

    else{
        for(i=0;i<k;i++){
            perm[n] = i;
            ///permutation function
            printPerms(perm,n+1,k,intArray,col,row);
        }
    }
}//end of fillPerm

//free all array
void freeArray(int** intArray,int row, int* perm){
    int i ;

    for(i=0;i<row;i++){
        free(intArray[i]);
    }

    free(intArray);
    free(perm);
}

int** getIntArray(int row, int col){
    //generate a 2d array for a input
    int** intarray = malloc(sizeof(int*)*col);
    int i,j;

    for(i=0;i<col;i++){
        intarray[i] = malloc(sizeof(int)*(row+3));
    }
    int num = row+2;//extra 2 for white and black
    int num1;
    for(i=0;i<col;i++){
            for(j=0;j<num;j++){
                scanf("%i",&num1);
                intarray[i][j]=num1;
            }
    }

    return intarray;
}//end of intArray

int getInt(){
  
    int num;
    scanf("%i",&num);

    return num;
}//end of firstinput



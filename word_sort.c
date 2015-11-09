//
//  main.c
//  word_sort
//
//  Created by Goragod Pongthanisorn on 10/28/2558 BE.
//  Copyright © 2558 Goragod Pongthanisorn. All rights reserved.
//

/***######## Include #########***/
#include <stdio.h>
#include <string.h>
#include <syslog.h>
#include <stdlib.h>
/***######## Define #########***/
#define STR_LENGTH                       100
#define WORD_BUFFER_SIZE        STR_LENGTH/5
/***######## Local Function #########***/
int WordExtract(char*, char**);

/**Error if not declare in inline func type**/
/**
 *@Name      compare_funtion <credit Boda Cydo.>
 *@Params    const void , const void
 *@Return     none
 *@Brief        This is comparative function using on QSORT by cast parameter
 of char pointer into array of char pointer
 ***/
static inline int compare_function(const void *name1, const void *name2)
{
    const char *name1_ = *(const char **)name1;
    const char *name2_ = *(const char **)name2;
    return strcmp(name1_, name2_);
}

/***######## Local Variable #########***/
FILE* dmp;

int main (int argc, char* argv[]) {
    char* bStr = malloc(sizeof(char) * STR_LENGTH);
    char* bWord[WORD_BUFFER_SIZE] ;
    int i;
    int cntWord = 0;
    dmp = fopen("dmp.txt", "w");
    
    if(dmp == NULL) {
        printf("Error opening file\n");
        return -1;
    }
    
    gets(bStr);
    fprintf(dmp,"%s\n", bStr);
    cntWord = WordExtract(bStr, bWord);
    ///Send to qsort function with array of char pointer (array of string) compare function
    qsort(bWord, cntWord, sizeof(char *), compare_function);
    
    for(i = 0; i < cntWord; ++i)
        fprintf(dmp,"%s ", bWord[i]);
    
    fclose(dmp);
    free(bStr);
    
    
    return 0;
}

/**
 *@Name      WordExtract
 *@Params    char* (string), char** (array of char)
 *@Return     pst (size of array)
 *@Brief        This function extract every word from string then store it in array
 and return word counter
 ***/
int WordExtract(char* seqStr, char** arr) {
    char* pch;
    int pst = 0;
    
    ///Strtok is used to skip space(' ') comma(,) full-stop(.) and minus sign(-)
    pch = strtok (seqStr," ,.-");
    while (pch != NULL) {
        arr[pst] = pch; ///Store value before each token occurence
        pch = strtok (NULL, " ,.-");
        pst++;
    }
    return pst;
}
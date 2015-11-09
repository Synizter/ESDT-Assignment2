
//
//  main.c
//  med_value
//
//  Created by Goragod Pongthanisorn on 10/28/2558 BE.
//  -Modify quick sort to print medain value without sort all data
//  Copyright © 2558 Goragod Pongthanisorn. All rights reserved.
//

/***######## Include #########***/
#include <stdio.h>
#include <string.h>
#include <syslog.h>
#include <stdlib.h>
#include <time.h>

/***######## Define #########***/
#define N       50
#define RSEED   5

/***######## Local Function #########***/
void swap(int*, int*);
void create_array(int[], int, int);
void print_array2(int a[], int l, int r);
void print_pivot(int, int[], int, int);
int partition(int[], int, int);
void quick_sort(int[], int, int);
int sort_decision(int pivot_pos);


/***######## Local Variable #########***/
int comp_count = 0;
FILE* dmp;

int main () {
    int a[N];
    
    dmp = fopen("dmpIO.txt", "w");
    srand((int) time(NULL));
    
    create_array(a, N, RSEED);
    fprintf(dmp, "unsort data are ");
    print_array2(a, 0, N - 1);
    printf("\n");
    quick_sort(a, 0, N - 1);
    fprintf(dmp, "unfinished sort data are ");
    print_array2(a, 0, N - 1);
    printf("\n");
    
    
    //Check if length of array are odd or even
    if((N) % 2 == 0) {
        fprintf(dmp, "Median value is %d\n", a[N/2]);
    }
    else {
        float med = (float) (a[N/2] + a[(N/2) + 1]) / 2;
        fprintf(dmp, "Median value is %.2f\n",med);
    }
    
    return 0;
}

/**
 *@Name     swap
 *@Param    *a, *b
 *@Ret      None
 *@Brief    Swap two variable using call reference styling
 **/
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

/**
 *@Name     create_array
 *@Param    a[], n, rand_seed
 *@Ret      None
 *@Brief    Create seqeunce of data accroding to accroding to n
            and store into array then shuffle data 2 times at random
            position of n
 **/
void create_array(int a[], int n, int rand_seed) {
    int i;
    
    for (i = 0; i < n; ++i )
        a[i] = i;
        
    for (i =0; i < n; ++i) {
        int j0 = rand() % n;
        int j1 = rand() % n;
        swap(&a[j0], &a[j1]);
        }
    
}

/**
 *@Name     print_array2
 *@Param    a[], l, r
 *@Ret      None
 *@Brief    print all element in array
 **/
void print_array2(int a[], int l, int r){
    int j;
    
    //Print output
    fprintf(dmp, "a[%d,%d] = {", l, r);
    for (j = 1; j <= r; j++) {
        if (j > 1)
            fprintf(dmp, ", ");
        fprintf(dmp, "%d", a[j]);
    }
    fprintf(dmp, "}\n");
    
}

/**
 *@Name     print_pivit
 *@Param    pivot, a, l ,r
 *@Ret      Noen
 *@Brief    Print out pivots
 **/
void print_pivot(int pivot, int a[], int l, int r){
    fprintf(dmp, "pivot(%d) : ", pivot);
    print_array2(a, l, r);
}


/**
 *@Name     partition
 *@Param    a[], left, right
 *@Ret      k
 *@Brief    Divide each element in array find the pivot for quick sort
 **/
int partition(int a[], int left, int right) {
    int pivot = a[right];
    int i = left;
    int k = right;
    
    while(i < k) {
        while(i < k && a[i] < pivot)
            i++;
        while(i < k && a[k] >= pivot)
            k--;
        if(i < k)
            swap(&a[i], &a[k]);
    }
    
    if(right > k)
        swap(&a[right], &a[k]);
    
    //print_pivot(pivot, a, left, right);
    comp_count += right - left - 1;
    return k;
}


/**
 *@Name     quick_sort
 *@Param    a[], left, right
 *@Ret      None
 *@Brief    Implement of quick sort algorithms by find pivot
            and divide into left and right then apply same procedure
            for each side till all of elements are sorted
 **/
void quick_sort(int a[], int left, int right) {
    int dec;
    
    if(left < right) {
        int pivot_pos = partition(a, left, right);
        /*** After fisnishing partition medain value are on position
            before sort the rest of data on left and right ***/
        
        dec = sort_decision(pivot_pos);
        
        if(dec == N/2) {
        }
        else if (dec == 1) {
            quick_sort(a, left, pivot_pos - 1);
            
        }
        else {
            quick_sort(a, pivot_pos + 1, right);
        }
        
    }
}

/**
 *@Name     sort_decision
 *@Param    pivot_pos
 *@Ret      decision value to sort left, right or no sort
 *@Brief    Function for make a decision after divide eache
            element into left and right. first partion get the
            pivot position so it use that value to decise to
            sort left or right
 **/
int sort_decision(int pivot_pos) {
    //Find position of pivot
    //compare to lenght of array/2
    if(pivot_pos == N/2) {
        //No sort
        return pivot_pos;
    }
    else if(pivot_pos > N/2) {
        //Sort left
        return 1;
    }
    else {
        //Sort right
        return 0;
    }
}


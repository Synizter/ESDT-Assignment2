// Author Goragod Pongthanisorn ICTES 12
//        Kasetsart University

/************************ Include ****************************/
#include<stdio.h>
#include<stdlib.h>

/***************** Function Prototype ************************/
void Merge(int*, int*, int, int*, int);
void MergeSort(int*, int);

/******************** Local Variable *************************/
FILE* dmp;


int main(int argc, char* argv[]) {
	int* A = malloc((argc - 1) * sizeof(int)); 
	int i,numberOfElements;

	dmp = fopen("dmpIO.txt", "w");

	fprintf(dmp, "Input Data : ");
	//Copy data into prepared array
	for(i = 0; i < (argc - 1); ++i) {
		A[i] = atoi(argv[i + 1]);
		fprintf(dmp, "%d ", A[i]);
	}


 	

	numberOfElements = (argc - 1); 
	// Calling merge sort to sort the array. 
	MergeSort(A,numberOfElements);

	fprintf(dmp, "\nSort Array : ");
	//printing all elements in the array once its sorted.
	for(i = 0;i < numberOfElements;i++) 
		fprintf(dmp, "%d ",A[i]);
	

	//EOP
	printf("\n");
	free(A);
	return 0;
}

void Merge(int *A,int *L,int leftCount,int *R,int rightCount) {
	int i = 0;
	int j = 0;
	int k = 0;
	
	while(i<leftCount && j< rightCount) {
		if(L[i]  < R[j]) 
			A[k++] = L[i++];
		else 
			A[k++] = R[j++];
	}
	while(i < leftCount) 
		A[k++] = L[i++];
	while(j < rightCount) 
		A[k++] = R[j++];
}

void MergeSort(int *A,int n) {
	int mid,i, *L, *R;
	if(n < 2) return; 

	mid = n/2; 

	L = (int*)malloc(mid*sizeof(int)); 
	R = (int*)malloc((n- mid)*sizeof(int)); 
	
	for(i = 0; i < mid; i++) 
		L[i] = A[i]; 
	for(i = mid; i < n; i++) 
		R[i-mid] = A[i]; 

	MergeSort(L,mid);  //sorting the left subarray
	MergeSort(R,n-mid);  //sorting the right subarray
	Merge(A,L,mid,R,n-mid);  //Merging L and R into A as sorted list.
    
    free(L);
    free(R);
}
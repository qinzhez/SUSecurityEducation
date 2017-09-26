#include "lab1.h"


void  generateNum(int *list, long count){
	
	srand(time(NULL));
	
	for(long i=0; i<count; i++){
		list[i] = rand() % 100;
	}
	
}

void ocall_print(int *list, long size){
	for(long i=0;i<size;i++){
		printf("(%ld:%d)", i,list[i]);
	}
	printf("\n");
}



void task_A(int *list, long size){
	sgx_status_t ret = SGX_ERROR_UNEXPECTED;
	int retval;
	
	assert(list != NULL);

	// ------------------------------------------ Part 2 -----------------------------------------------
	struct timeval t_start,t_end;

	printf("\n\nThe normal mode of sum computation begin...\n");

	//time start
	gettimeofday(&t_start,NULL);

	call_sum(list,size);
	
	//time end
	gettimeofday(&t_end,NULL);
	double duration = (double)(t_end.tv_sec - t_start.tv_sec)*1000000.0 + (t_end.tv_usec - t_start.tv_usec);
	printf("\nTime result: Sum function in normal mode cost: %f us\n", duration);

	//-----------------------------------------------------------------------------------------------------------
	printf("Normal mode finished\n\n======================================\nThe SGX mode of sum computation begin...\n");
	
	//time start
	gettimeofday(&t_start,NULL);
	
	ret = call_sum(global_eid, &retval,list,size);
	
	//time end
	gettimeofday(&t_end,NULL);
	duration = (double)(t_end.tv_sec - t_start.tv_sec)*1000000.0 + (t_end.tv_usec - t_start.tv_usec);
	printf("\nTime result: Sum function in SGX mode cost: %f us\n", duration);
	if(ret != SGX_SUCCESS)
		abort();

}



int InterfaceA(){
	printf("\n-------------------------------Task A-------------------------------\n");

	printf("Please enter a number for starting number, and a number for amount of numbers\n");
	int S = 0, C = 0;
	scanf("%d",&S);
	scanf("%d",&C);
	int sum = 0;
	int *testList = new int[C];
	for(int i=0;i<C;i++){
		testList[i] = S+i;
		sum += S+i;
	}

	double test = call_sum(testList, C);

	printf("The correct result should be %d. Your sum function output is %.0f\n",sum, test);
	delete[] testList;
	if(sum != (int)test){
		printf("Please return to check your sum function.\n");
		return 0;
	}


	long num=0;
	printf("\nEnter the amount of numbers need\n");
	
	scanf("%ld",&num);
	
	// --------------------------------------Task A---------------------------------------
	printf("%ld numbers will be generated.\n", num);
	
	int *list = new int[num];
	generateNum(list, num);

	task_A(list,num);
	// ------------------------------------Task A End-------------------------------------
	printf("\n-------------------------------------------------------------------------\n");
	delete[] list;
	return 0;
}



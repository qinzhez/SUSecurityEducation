#include <stdio.h>
#include <string.h>
#include <assert.h>

# include <unistd.h>
# include <pwd.h>
# define MAX_PATH FILENAME_MAX

#include "sgx_trts.h"
#include "sgx_urts.h"
//#include "sgx_status.h"
#include "App.h"
#include "Enclave_u.h"
#include <time.h>
#include <sys/time.h>

#include "sum_sln.h"
#include "bsort_sln.h"
#include "msort_sln.h"

#define MAX 100
#define MIN 0

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


void task_B(int *list, long size){
	sgx_status_t ret = SGX_ERROR_UNEXPECTED;
	int retval;

	
	assert(list != NULL);

	int sortType = 0;
	printf("\nPlease choose sort method:\n");
	printf("1 Bubble sort\n");
	printf("2 Merge sort\n");
	scanf("%d",&sortType);	
	
	printf("\n\n--------------------------------Sort------------------------------------\n\n");
	
	if(sortType == 1){
		call_bsort(list,size);
		printf("Bubble sort finished. The result is below: (index: value)\n\n");
		ocall_print(list,size);		
	}
	else if(sortType ==2 ){
		call_msort(list,size);
		printf("Merge sort finished. The result is below: (index: value)\n\n");
		ocall_print(list,size);
	}

	//if(ret != SGX_SUCCESS)
	//	abort();

}


int InterfaceA(){
	printf("\n-------------------------------Task A-------------------------------\n");

	long num=0;
	printf("Enter the amount of numbers need\n");
	
	scanf("%ld",&num);
	
	// --------------------------------------Task A---------------------------------------
	printf("%ld numbers will be generated.\n", num);
	
	int *list = new int[num];
	generateNum(list, num);

	task_A(list,num);
	// ------------------------------------Task A End-------------------------------------
	printf("\n-------------------------------------------------------------------------\n");
	delete[] list;
}

int InterfaceB(){
	// --------------------------------------Task B---------------------------------------
	printf("\n---------------------------------Task B---------------------------------------\n");
	
	long num = 0;
	printf("Please input amount of the list.\n");
	scanf("%ld",&num);
	printf("Please enter %ld numbers\n", num);

	int *list = new int[num];
	for(long i=0;i<num;i++){
		scanf("%d",&list[i]);
	}

	printf("\ninput completed\n");
	task_B(list, num);
	printf("\n-------------------------------------------------------------------------\n");
	delete[] list;
}


int Interface(){
	printf("\nPlease choose a task:\n");

	int ret = 1;
	//-------------------------Task list--------------------------
	printf("1 Task A: \n");
	printf("2 Task B: \n");
	printf("0 Quit\n");
	//------------------------------------------------------------

	int choice=-1;
	scanf("%d",&choice);

	switch(choice){
		case 0:
			ret=0;
			break;
		case 1:
			InterfaceA();
			break;
		case 2:
			InterfaceB();
			break;
	}
	return ret;
}


int ecall_foo1(int i, int j)
{
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;
    int retval;
    ret = ecall_foo(global_eid, &retval, i, j);

    if (ret != SGX_SUCCESS)
        abort();
    
    int cpuid[4] = {0x1, 0x0, 0x0, 0x0};
    ret = ecall_sgx_cpuid(global_eid, cpuid, 0x0);
    if (ret != SGX_SUCCESS)
        abort();
    return retval;
}

/* Global EID shared by multiple threads */
sgx_enclave_id_t global_eid = 0;

typedef struct _sgx_errlist_t {
    sgx_status_t err;
    const char *msg;
    const char *sug; /* Suggestion */
} sgx_errlist_t;

/* Error code returned by sgx_create_enclave */
static sgx_errlist_t sgx_errlist[] = {
    {
        SGX_ERROR_UNEXPECTED,
        "Unexpected error occurred.",
        NULL
    },
    {
        SGX_ERROR_INVALID_PARAMETER,
        "Invalid parameter.",
        NULL
    },
    {
        SGX_ERROR_OUT_OF_MEMORY,
        "Out of memory.",
        NULL
    },
    {
        SGX_ERROR_ENCLAVE_LOST,
        "Power transition occurred.",
        "Please refer to the sample \"PowerTransition\" for details."
    },
    {
        SGX_ERROR_INVALID_ENCLAVE,
        "Invalid enclave image.",
        NULL
    },
    {
        SGX_ERROR_INVALID_ENCLAVE_ID,
        "Invalid enclave identification.",
        NULL
    },
    {
        SGX_ERROR_INVALID_SIGNATURE,
        "Invalid enclave signature.",
        NULL
    },
    {
        SGX_ERROR_OUT_OF_EPC,
        "Out of EPC memory.",
        NULL
    },
    {
        SGX_ERROR_NO_DEVICE,
        "Invalid SGX device.",
        "Please make sure SGX module is enabled in the BIOS, and install SGX driver afterwards."
    },
    {
        SGX_ERROR_MEMORY_MAP_CONFLICT,
        "Memory map conflicted.",
        NULL
    },
    {
        SGX_ERROR_INVALID_METADATA,
        "Invalid enclave metadata.",
        NULL
    },
    {
        SGX_ERROR_DEVICE_BUSY,
        "SGX device was busy.",
        NULL
    },
    {
        SGX_ERROR_INVALID_VERSION,
        "Enclave version was invalid.",
        NULL
    },
    {
        SGX_ERROR_INVALID_ATTRIBUTE,
        "Enclave was not authorized.",
        NULL
    },
    {
        SGX_ERROR_ENCLAVE_FILE_ACCESS,
        "Can't open enclave file.",
        NULL
    },
};

/* Check error conditions for loading enclave */
void print_error_message(sgx_status_t ret)
{
    size_t idx = 0;
    size_t ttl = sizeof sgx_errlist/sizeof sgx_errlist[0];

    for (idx = 0; idx < ttl; idx++) {
        if(ret == sgx_errlist[idx].err) {
            if(NULL != sgx_errlist[idx].sug)
                printf("Info: %s\n", sgx_errlist[idx].sug);
            printf("Error: %s\n", sgx_errlist[idx].msg);
            break;
        }
    }
    
    if (idx == ttl)
        printf("Error: Unexpected error occurred.\n");
}

/* Initialize the enclave:
 *   Step 1: retrive the launch token saved by last transaction
 *   Step 2: call sgx_create_enclave to initialize an enclave instance
 *   Step 3: save the launch token if it is updated
 */
int initialize_enclave(void)
{
    char token_path[MAX_PATH] = {'\0'};
    sgx_launch_token_t token = {0};
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;
    int updated = 0;
    
    /* Step 1: retrive the launch token saved by last transaction */

/* __GNUC__ */
    /* try to get the token saved in $HOME */
    const char *home_dir = getpwuid(getuid())->pw_dir;
    
    if (home_dir != NULL && 
        (strlen(home_dir)+strlen("/")+sizeof(TOKEN_FILENAME)+1) <= MAX_PATH) {
        /* compose the token path */
        strncpy(token_path, home_dir, strlen(home_dir));
        strncat(token_path, "/", strlen("/"));
        strncat(token_path, TOKEN_FILENAME, sizeof(TOKEN_FILENAME)+1);
    } else {
        /* if token path is too long or $HOME is NULL */
        strncpy(token_path, TOKEN_FILENAME, sizeof(TOKEN_FILENAME));
    }

    FILE *fp = fopen(token_path, "rb");
    if (fp == NULL && (fp = fopen(token_path, "wb")) == NULL) {
        printf("Warning: Failed to create/open the launch token file \"%s\".\n", token_path);
    }

    if (fp != NULL) {
        /* read the token from saved file */
        size_t read_num = fread(token, 1, sizeof(sgx_launch_token_t), fp);
        if (read_num != 0 && read_num != sizeof(sgx_launch_token_t)) {
            /* if token is invalid, clear the buffer */
            memset(&token, 0x0, sizeof(sgx_launch_token_t));
            printf("Warning: Invalid launch token read from \"%s\".\n", token_path);
        }
    }

    /* Step 2: call sgx_create_enclave to initialize an enclave instance */
    /* Debug Support: set 2nd parameter to 1 */
    ret = sgx_create_enclave(ENCLAVE_FILENAME, SGX_DEBUG_FLAG, &token, &updated, &global_eid, NULL);
    if (ret != SGX_SUCCESS) {
        print_error_message(ret);
        if (fp != NULL) fclose(fp);
        return -1;
    }

    /* Step 3: save the launch token if it is updated */
/* __GNUC__ */
    if (updated == FALSE || fp == NULL) {
        /* if the token is not updated, or file handler is invalid, do not perform saving */
        if (fp != NULL) fclose(fp);
        return 0;
    }

    /* reopen the file with write capablity */
    fp = freopen(token_path, "wb", fp);
    if (fp == NULL) return 0;
    size_t write_num = fwrite(token, 1, sizeof(sgx_launch_token_t), fp);
    if (write_num != sizeof(sgx_launch_token_t))
        printf("Warning: Failed to save launch token to \"%s\".\n", token_path);
    fclose(fp);
    return 0;
}

/* OCall functions */
void ocall_bar(const char *str, int ret[1])
{
    /* Proxy/Bridge will check the length and null-terminate 
     * the input string to prevent buffer overflow. 
     */
    printf("%s", str);
    ret[0] = 13;
}

/*
void ocall_sum(const char *str)
{
	printf("%s", str);
}
*/

/* Application entry */
int SGX_CDECL main(int argc, char *argv[])
{
    int i = 3;
    int j = 5;
    /* Initialize the enclave */
printf("a\n");
    if(initialize_enclave() < 0){printf("Error enclave and exit\n");return -1;}
printf("b\n");
 
    /* Utilize edger8r attributes */
    edger8r_function_attributes();
    
printf("c\n");
    /* Utilize trusted libraries */
	
	int run = 1;
	while(run){
		run = Interface();
	}	
	
    /* Destroy the enclave */
    sgx_destroy_enclave(global_eid);
    printf("Info: SampleEnclave successfully returned.\n");
    return 0;
}


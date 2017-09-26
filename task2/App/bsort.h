

/* 
 * printf: 
 *   Invokes OCALL to display the enclave buffer to the terminal.
 */
int bar_print(const char *fmt, ...)
{
    int ret[1];
    char buf[BUFSIZ] = {'\0'};
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, BUFSIZ, fmt, ap);
    va_end(ap);
    ocall_bar(buf, ret);
    return ret[0];
}



int call_bsort(int *list, long size){
	for(long i=0;i<size;i++){
		for(long j = 0; /* Fill condition here */;j++){
			if(list[j]>list[j+1]){
				//Fill bubble sort steps	
			}
			bar_print("Iterating: i = %ld, j = %ld, j+1 = %ld\n",i,j,j+1);
		}
	}
}

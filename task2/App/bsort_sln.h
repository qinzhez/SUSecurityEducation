
/* 
 * printf: 
 *   Invokes OCALL to display the enclave buffer to the terminal.
 */
int bar(const char *fmt, ...)
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


void get_result(long index1,long index2){
	bar("Iterating: index1 = %ld, index2 = %ld \n",index1,index2);
}


int call_bsort(int *list, long size){
	for(long i=0;i<size;i++){
		for(long j = 0; j<size-i-1;j++){
			if(list[j]>list[j+1]){
				long tmp = list[j];
				list[j] = list[j+1];
				list[j+1] = tmp;
			}
			get_result(j,j+1);
		}
	}
}



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



int call_sum(int * list, long size){
	double result = 0;

	for(long i=0; i<size; i++){
		result += list[i];
	}

	bar_print("\nThe sum result is %f \n", result);
	return result;
}

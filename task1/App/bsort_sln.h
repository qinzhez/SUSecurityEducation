
int call_bsort(int *list, long size){
	for(long i=0;i<size;i++){
		for(long j = 0; j<size-i-1;j++){
			if(list[j]>list[j+1]){
				long tmp = list[j];
				list[j] = list[j+1];
				list[j+1] = tmp;
			}
			bar_print("Iterating: i = %ld, j = %ld, j+1 = %ld \n",i,j,j+1);
		}
	}
}

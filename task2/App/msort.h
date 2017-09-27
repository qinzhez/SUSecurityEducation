
/* In bubble sort, it is easy to print out the index accessed each iteration.
   In merge sort, you need to use following function to print out the right result.
   
   index1: indicate an index in the list passed from main is paticipating comparison.
   index2: indicate another index in the list passed from main is paticipating comparison.

   if no index2, please pass index2 = -1

   for example, 
   List(0-5) from main: 5 4 3 2 1 0
   
	- currently merging reaches list[0] = 5 and list[3] = 2, use indexPrint(0,3);
	
	- currently [0 1 2] and [3 4 5] need to be merged. The second list just needs to be appended at
	  the end of the first list. When appending the list[2] = 3 in the second list, use indexPrint(2,-1)
*/ 

void indexPrint(long index1, long index2){
	if(index2 == -1)
		bar("(%ld) ", index1);
	else{
		bar("(%ld %ld) ", index1, index2);
	}
}

void merge(/* fill your code here */) {
	/* fill your code here */
	bar("\n");
}


void divide(/* fill your code here */) {
	/* fill your code here */
}

void call_msort(int *list, long size) {
	divide(/* fill your code here*/);
}



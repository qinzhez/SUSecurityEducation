
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

void merge(int *list, long b1, long e1,long b2, long e2) {
	if (b1 == e2)
		return;
	int *l1 = new int[e1-b1+1];
	int *l2 = new int[e2-b2+1];

	for (long i = 0; i<e1 - b1 + 1; i++) {
		l1[i] = list[b1 + i];
	}
	for (long i = 0; i<e2 - b2 + 1; i++) {
		l2[i] = list[b2 + i];
	}

	long m = 0, n = 0;
	for (long i = 0; i<(e2 - b1 + 1); i++) {
		if (b1+m > e1) {
			list[i+b1] = l2[n];
			n++;
			indexPrint(b2+n,-1);
		}
		else if (b2+n > e2) {
			list[i + b1] = l1[m];
			m++;
			indexPrint(b1+m,-1);
		}
		else {
			indexPrint(b1+m,b2+n);
			if (l1[m]<l2[n]) {
				list[i + b1] = l1[m];
				m++;
			}
			else {
				list[i + b1] = l2[n];
				n++;
			}
		}
	}
	bar("\n");
}


void divide(int *list, long begin, long end) {
	if (begin >= end)
		return;

	divide(list, begin, (end + begin) / 2 );
	divide(list, (end + begin) / 2 + 1, end);

	merge(list, begin, (end + begin) / 2, (end + begin) / 2 + 1, end);
}

void call_msort(int *list, long size) {
	divide(list, 0, size - 1);
}



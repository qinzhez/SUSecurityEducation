
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
			bar_print("%ld ",b2+n);
		}
		else if (b2+n > e2) {
			list[i + b1] = l1[m];
			m++;
			bar_print("%ld ",b1+m);
		}
		else {
			if (l1[m]<l2[n]) {
				list[i + b1] = l1[m];
				m++;
				bar_print("%ld ",b1+m);
			}
			else {
				list[i + b1] = l2[n];
				n++;
				bar_print("%ld ",b2+n);
			}
		}
	}
	bar_print("\n");
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



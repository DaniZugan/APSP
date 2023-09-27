#include <stdbool.h>

bool isfinite_cust(float n);

double drand();
float frand();

bool containsValue(const int* array, int size, int target);     

void shuffle(int *array, int n);

typedef struct SimpleList SimpleList;

struct SimpleList {
	short label;
	
	SimpleList* next;
}

;
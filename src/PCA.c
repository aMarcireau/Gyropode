#include "PCA.h"

void initializePCA()
{
	CR = 1;
	PCA0CPM0 = 0xc2;
	PCA0CP0 = -3062; // 1.5 ms
	PCA0CPH0 = 244;

	PCA0CPM1 = 0xc2;
	PCA0CP1 = -3062; // 1.5 ms
	PCA0CPH1 = 244;
}
/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "sum.h"

int *
sumofarray_1_svc(sum *argp, struct svc_req *rqstp)
{
	static int  result;

	/*
	 * insert server code here
	 */
	int i;
	for(i = 0;i < argp->size;i++){
		result += argp->data[i];
	}
	return &result;
}

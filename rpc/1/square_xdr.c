/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "square.h"

bool_t
xdr_square (XDR *xdrs, square *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->a))
		 return FALSE;
	return TRUE;
}
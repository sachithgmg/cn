/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _SQUARE_H_RPCGEN
#define _SQUARE_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct square {
	int a;
};
typedef struct square square;

#define SQUARE_PROC 0x3012225
#define SQUARE_VERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define sqr 1
extern  int * sqr_1(square *, CLIENT *);
extern  int * sqr_1_svc(square *, struct svc_req *);
extern int square_proc_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define sqr 1
extern  int * sqr_1();
extern  int * sqr_1_svc();
extern int square_proc_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_square (XDR *, square*);

#else /* K&R C */
extern bool_t xdr_square ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_SQUARE_H_RPCGEN */

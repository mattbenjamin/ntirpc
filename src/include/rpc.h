/* This is a central clearing house for RPC definitions. Nothing
   should included anything related to RPC except this file */

#include "config.h"

#ifndef GANESHA_RPC_H
#define GANESHA_RPC_H

#include "config.h"

#ifdef _USE_GSSRPC
#include <gssrpc/rpc.h>
#include <gssrpc/types.h>
#include <gssrpc/svc.h>
#include <gssrpc/pmap_clnt.h>
#else
#ifdef _USE_TIRPC
#include <tirpc/rpc/rpc.h>
#include <tirpc/rpc/svc.h>
#include <tirpc/rpc/types.h>
#include <tirpc/rpc/pmap_clnt.h>
#include "RW_Lock.h"
#else
#include <rpc/rpc.h>
#include <rpc/types.h>
#include <rpc/svc.h>
#include <rpc/pmap_clnt.h>
#endif
#endif

#ifdef _USE_TIRPC
#define xdr_uint16_t xdr_u_int16_t
#define xdr_uint32_t xdr_u_int32_t
#define xdr_uint64_t xdr_u_int64_t
#endif


#ifdef _USE_TIRPC
typedef struct sockaddr_storage sockaddr_t;
#else
typedef struct sockaddr_in sockaddr_t
#endif

#if defined( _USE_TIRPC ) || defined( _FREEBSD )
#define XP_SOCK xp_fd
#else
#define XP_SOCK xp_sock
#endif

#ifdef _USE_TIRPC
void Svc_dg_soft_destroy(SVCXPRT * xport);
struct netconfig *getnetconfigent(const char *netid);
void freenetconfigent(struct netconfig *);
SVCXPRT *Svc_vc_create(int, u_int, u_int);
SVCXPRT *Svc_dg_create(int, u_int, u_int);
#else
void Svcudp_soft_destroy(SVCXPRT * xprt);
SVCXPRT *Svctcp_create(register int sock, u_int sendsize, u_int recvsize);
SVCXPRT *Svcudp_bufcreate(register int sock, u_int sendsz, u_int recvsz);
bool_t Svc_register(SVCXPRT * xprt, u_long prog, u_long vers, void (*dispatch) (),
                    int protocol);
#endif                          /* _USE_TIRPC */

#if _USE_TIRPC
/* public data : */
extern rw_lock_t Svc_lock;
extern rw_lock_t Svc_fd_lock;
#endif

int copy_xprt_addr(sockaddr_t *addr, SVCXPRT *xprt);
void sprint_sockaddr(sockaddr_t *addr, char *buf, int len);

#endif
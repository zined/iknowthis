#include <glib.h>
#include <errno.h>
#include <sys/syscall.h>

#include "sysfuzz.h"
#include "typelib.h"
#include "iknowthis.h"

// Get name of connected peer socket.
// TODO: make sockaddr types a resource?
// int getpeername(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
SYSFUZZ(getpeername, SYS_getpeername, SYS_NONE, CLONE_DEFAULT, 1000)
{
    glong       retcode;
    gpointer    addr;
    gpointer    addrlen;

    retcode = spawn_syscall_lwp(this, NULL, SYS_getpeername,                                // int
                                      typelib_get_resource(this, NULL, RES_FILE, RF_NONE),  // int sockfd
                                      typelib_get_buffer(&addr, PAGE_SIZE),                 // struct sockaddr *addr
                                      typelib_get_buffer(&addrlen, PAGE_SIZE));             // socklen_t *addrlen;

    typelib_clear_buffer(addr);
    typelib_clear_buffer(addrlen);

    return retcode;
}


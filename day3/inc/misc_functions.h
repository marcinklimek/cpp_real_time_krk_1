/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2010.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU Lesser General Public License as published   *
* by the Free Software Foundation, either version 3 or (at your option)   *
* any later version. This program is distributed without any warranty.    *
* See the files COPYING.lgpl-v3 and COPYING.gpl-v3 for details.           *
\*************************************************************************/

#ifndef MISC_FUNCTIONS_H
#define MISC_FUNCTIONS_H
#include <stdarg.h>
#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static char *ename[] = {
    /*   0 */ "",
    /*   1 */ "EPERM", "ENOENT", "ESRCH", "EINTR", "EIO", "ENXIO",
    /*   7 */ "E2BIG", "ENOEXEC", "EBADF", "ECHILD",
    /*  11 */ "EAGAIN/EWOULDBLOCK", "ENOMEM", "EACCES", "EFAULT",
    /*  15 */ "ENOTBLK", "EBUSY", "EEXIST", "EXDEV", "ENODEV",
    /*  20 */ "ENOTDIR", "EISDIR", "EINVAL", "ENFILE", "EMFILE",
    /*  25 */ "ENOTTY", "ETXTBSY", "EFBIG", "ENOSPC", "ESPIPE",
    /*  30 */ "EROFS", "EMLINK", "EPIPE", "EDOM", "ERANGE",
    /*  35 */ "EDEADLK/EDEADLOCK", "ENAMETOOLONG", "ENOLCK", "ENOSYS",
    /*  39 */ "ENOTEMPTY", "ELOOP", "", "ENOMSG", "EIDRM", "ECHRNG",
    /*  45 */ "EL2NSYNC", "EL3HLT", "EL3RST", "ELNRNG", "EUNATCH",
    /*  50 */ "ENOCSI", "EL2HLT", "EBADE", "EBADR", "EXFULL", "ENOANO",
    /*  56 */ "EBADRQC", "EBADSLT", "", "EBFONT", "ENOSTR", "ENODATA",
    /*  62 */ "ETIME", "ENOSR", "ENONET", "ENOPKG", "EREMOTE",
    /*  67 */ "ENOLINK", "EADV", "ESRMNT", "ECOMM", "EPROTO",
    /*  72 */ "EMULTIHOP", "EDOTDOT", "EBADMSG", "EOVERFLOW",
    /*  76 */ "ENOTUNIQ", "EBADFD", "EREMCHG", "ELIBACC", "ELIBBAD",
    /*  81 */ "ELIBSCN", "ELIBMAX", "ELIBEXEC", "EILSEQ", "ERESTART",
    /*  86 */ "ESTRPIPE", "EUSERS", "ENOTSOCK", "EDESTADDRREQ",
    /*  90 */ "EMSGSIZE", "EPROTOTYPE", "ENOPROTOOPT",
    /*  93 */ "EPROTONOSUPPORT", "ESOCKTNOSUPPORT",
    /*  95 */ "EOPNOTSUPP/ENOTSUP", "EPFNOSUPPORT", "EAFNOSUPPORT",
    /*  98 */ "EADDRINUSE", "EADDRNOTAVAIL", "ENETDOWN", "ENETUNREACH",
    /* 102 */ "ENETRESET", "ECONNABORTED", "ECONNRESET", "ENOBUFS",
    /* 106 */ "EISCONN", "ENOTCONN", "ESHUTDOWN", "ETOOMANYREFS",
    /* 110 */ "ETIMEDOUT", "ECONNREFUSED", "EHOSTDOWN", "EHOSTUNREACH",
    /* 114 */ "EALREADY", "EINPROGRESS", "ESTALE", "EUCLEAN",
    /* 118 */ "ENOTNAM", "ENAVAIL", "EISNAM", "EREMOTEIO", "EDQUOT",
    /* 123 */ "ENOMEDIUM", "EMEDIUMTYPE", "ECANCELED", "ENOKEY",
    /* 127 */ "EKEYEXPIRED", "EKEYREVOKED", "EKEYREJECTED",
    /* 130 */ "EOWNERDEAD", "ENOTRECOVERABLE", "ERFKILL", "EHWPOISON"
};

#define MAX_ENAME 133

void                    /* Print list of signals within a signal set */
printSigset(FILE *of, const char *prefix, const sigset_t *sigset)
{
    int sig, cnt;

    cnt = 0;
    for (sig = 1; sig < NSIG; sig++)
    {
        if (sigismember(sigset, sig))
        {
            cnt++;
            fprintf(of, "%s%d (%s)\n", prefix, sig, strsignal(sig));
        }
    }

    if (cnt == 0)
        fprintf(of, "%s<empty signal set>\n", prefix);
}

int                     /* Print mask of blocked signals for this process */
printSigMask(FILE *of, const char *msg)
{
    sigset_t currMask;

    if (msg != NULL)
        fprintf(of, "%s", msg);

    if (sigprocmask(SIG_BLOCK, NULL, &currMask) == -1)
        return -1;

    printSigset(of, "\t\t", &currMask);

    return 0;
}

int                     /* Print signals currently pending for this process */
printPendingSigs(FILE *of, const char *msg)
{
    sigset_t pendingSigs;

    if (msg != NULL)
        fprintf(of, "%s", msg);

    if (sigpending(&pendingSigs) == -1)
        return -1;

    printSigset(of, "\t\t", &pendingSigs);

    return 0;
}

static void
outputError(int useErr, int err, int flushStdout,
            const char *format, va_list ap)
{
#define BUF_SIZE 500
    char buf[BUF_SIZE], userMsg[BUF_SIZE], errText[BUF_SIZE];

    vsnprintf(userMsg, BUF_SIZE, format, ap);

    if (useErr)
        snprintf(errText, BUF_SIZE, " [%s %s]",
                 (err > 0 && err <= MAX_ENAME) ?
                 ename[err] : "?UNKNOWN?", strerror(err));
    else
        snprintf(errText, BUF_SIZE, ":");

    snprintf(buf, BUF_SIZE, "ERROR%s %s\n", errText, userMsg);

    if (flushStdout)
        fflush(stdout);       /* Flush any pending stdout */
    fputs(buf, stderr);
    fflush(stderr);           /* In case stderr is not line-buffered */
}


#define TRUE 1
#define FALSE 0

void
errExit(const char *format, ...)
{
    va_list argList;

    va_start(argList, format);
    outputError(TRUE, errno, TRUE, format, argList);
    va_end(argList);

    exit(1);
}

/**
 * writefd() - A variant of write(2)
 *
 * This function returns 0 if the write was successful, and the nonzero
 * errno code otherwise, with errno itself kept unchanged.
 * This function is safe to use in a signal handler;
 * it is async-signal-safe, and keeps errno unchanged.
 *
 * Interrupts due to signal delivery are ignored.
 * This function does work with non-blocking sockets,
 * but it does a very inefficient busy-wait loop to do so.
*/
int writefd(const int descriptor, const void *const data, const size_t size)
{
    const char       *head = (const char *)data;
    const char *const tail = (const char *)data + size;
    ssize_t           bytes;
    int               saved_errno, retval;

    /* File descriptor -1 is always invalid. */
    if (descriptor == -1)
        return EINVAL;

    /* If there is nothing to write, return immediately. */
    if (size == 0)
        return 0;

    /* Save errno, so that it can be restored later on.
     * errno is a thread-local variable, meaning its value is
     * local to each thread, and is accessible only from the same thread.
     * If this function is called in an interrupt handler, this stores
     * the value of errno for the thread that was interrupted by the
     * signal delivery. If we restore the value before returning from
     * this function, all changes this function may do to errno
     * will be undetectable outside this function, due to thread-locality.
    */
    saved_errno = errno;

    while (head < tail) {

        bytes = write(descriptor, head, (size_t)(tail - head));

        if (bytes > (ssize_t)0) {
            head += bytes;

        } else
        if (bytes != (ssize_t)-1) {
            errno = saved_errno;
            return EIO;

        } else
        if (errno != EINTR && errno != EAGAIN && errno != EWOULDBLOCK) {
            /* EINTR, EAGAIN and EWOULDBLOCK cause the write to be
             * immediately retried. Everything else is an error. */
            retval = errno;
            errno = saved_errno;
            return retval;
        }
    }

    errno = saved_errno;
    return 0;
}


int wrout(const char *const string)
{
    if (string)
        return writefd(STDOUT_FILENO, string, strlen(string));
    else
        return 0;
}

#endif

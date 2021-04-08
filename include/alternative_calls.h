#if !defined(__NR_lstat) && !defined(__NR3264_lstat)
#include <fcntl.h>
#if defined(__NR_fstatat)
#   define  r_lstat(path, buf)    native_syscall(__NR_fstatat, AT_FDCWD, path, buf, AT_SYMLINK_NOFOLLOW)
#elif defined(__NR3264_fstatat)
#   define  r_lstat(path, buf)    native_syscall(__NR3264_fstatat, AT_FDCWD, path, buf, AT_SYMLINK_NOFOLLOW)
#endif
#endif

#if !defined(__NR_readlink) && !defined(__NR3264_readlink)
#include <fcntl.h>
#if defined(__NR_readlinkat)
#   define  r_readlink(...)    native_syscall(__NR_readlinkat, AT_FDCWD, ## __VA_ARGS__)
#elif defined(__NR3264_readlinkat)
#   define  r_readlink(...)    native_syscall(__NR3264_readlinkat, AT_FDCWD, ## __VA_ARGS__)
#endif
#endif

#if !defined(__NR_open) && !defined(__NR3264_open)
#include <fcntl.h>
#if defined(__NR_openat)
#   define  r_open(...)    native_syscall(__NR_openat, AT_FDCWD, ## __VA_ARGS__)
#elif defined(__NR3264_openat)
#   define  r_open(...)    native_syscall(__NR3264_openat, AT_FDCWD, ## __VA_ARGS__)
#endif
#endif

#if !defined(__NR_dup2) && !defined(__NR3264_dup2)
#if defined(__NR_dup3)
#   define  r_dup2(oldfd, newfd)    (oldfd == newfd) ? (long) newfd : native_syscall(__NR_dup3, oldfd, newfd, 0)
#elif defined(__NR3264_dup3)
#   define  r_dup2(oldfd, newfd)    (oldfd == newfd) ? (long) newfd : native_syscall(__NR3264_dup3, oldfd, newfd, 0)
#endif
#endif

#if !defined(__NR_unlink) && !defined(__NR3264_unlink)
#include <fcntl.h>
#if defined(__NR_unlinkat)
#   define  r_unlink(pathname)    native_syscall(__NR_unlinkat, AT_FDCWD, pathname, 0)
#elif defined(__NR3264_unlinkat)
#   define  r_unlink(pathname)    native_syscall(__NR3264_unlinkat, AT_FDCWD, pathname, 0)
#endif
#endif

#if !defined(__NR_rmdir) && !defined(__NR3264_rmdir)
#include <fcntl.h>
#if defined(__NR_unlinkat)
#   define  r_rmdir(pathname)    native_syscall(__NR_unlinkat, AT_FDCWD, pathname, AT_REMOVEDIR)
#elif defined(__NR3264_unlinkat)
#   define  r_rmdir(pathname)    native_syscall(__NR3264_unlinkat, AT_FDCWD, pathname, AT_REMOVEDIR)
#endif
#endif

#if !defined(__NR_poll) && !defined(__NR3264_poll)
#include <time.h>
#if defined(__NR_ppoll)
#   define  r_poll(fds, nfds, timeout)    (timeout < 0)                                                                     \
                                              ? native_syscall(__NR_ppoll, fds, nfds, NULL, NULL)                           \
                                              : ({                                                                          \
                                                    const struct timespec tmo = { .tv_sec = (long) timeout, .tv_nsec = 0 }; \
                                                    native_syscall(__NR_ppoll, fds, nfds, &tmo, NULL);                      \
                                                })
#elif defined(__NR3264_fstatat)
#   define  r_poll(fds, nfds, timeout)    (timeout < 0)                                                                     \
                                              ? native_syscall(__NR3264_ppoll, fds, nfds, NULL, NULL)                       \
                                              : ({                                                                          \
                                                    const struct timespec tmo = { .tv_sec = (long) timeout, .tv_nsec = 0 }; \
                                                    native_syscall(__NR3264_ppoll, fds, nfds, &tmo, NULL);                  \
                                                })
#endif
#endif

#if !defined(__NR_epoll_wait) && !defined(__NR3264_epoll_wait)
#if defined(__NR_epoll_pwait)
#   define  r_epoll_wait(epfd, events, maxevents, timeout)    native_syscall(__NR_epoll_pwait, epfd, events, maxevents, timeout, NULL)
#elif defined(__NR3264_epoll_pwait)
#   define  r_epoll_wait(epfd, events, maxevents, timeout)    native_syscall(__NR3264_epoll_pwait, epfd, events, maxevents, timeout, NULL)
#endif
#endif

#if !defined(__NR_fork) && !defined(__NR3264_fork)
#include <signal.h>
#if defined(__NR_clone)
#   define  r_fork()    native_syscall(__NR_clone, SIGCHLD, NULL, NULL, NULL, NULL)
#elif defined(__NR3264_clone)
#   define  r_fork()    native_syscall(__NR3264_clone, SIGCHLD, NULL, NULL, NULL, NULL)
#endif
#endif

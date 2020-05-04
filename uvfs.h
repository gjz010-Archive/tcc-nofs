#ifndef UVFS_H
#define UVFS_H
typedef int UFD;

UFD vopen(const char* pathname, int flags, int modes);
ssize_t vread(UFD fd, char* buf, size_t count);
ssize_t vwrite(UFD fd, const char* but, size_t count);
int vlseek(UFD fd, int offset, int whence);
int vclose(UFD fd);
int vvdup(UFD oldfd);
#endif

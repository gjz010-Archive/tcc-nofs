#include "tcc.h"
#include "uvfs.h"
int uvfs_open(const char *pathname,int flags,...){
    va_list ap;
    size_t mode=0;
    va_start(ap, flags);
    if(flags & O_CREAT){
        mode = va_arg(ap, size_t);
    }
    va_end(ap);
    return vopen(pathname, flags, mode);
}
int uvfs_write(int fd, const void* buf, unsigned int count){
    return vwrite(fd, buf, count);
}

int uvfs_read(int fd, void* buf, unsigned int count){
    return vread(fd, buf, count);
}
int uvfs_close(int fd){
    return vclose(fd);
}
off_t uvfs_lseek(int fd, off_t offset, int whence){
    return vlseek(fd, offset, whence);
}
int uvfs_dup(int fd){
    return vvdup(fd);
}

// Remove libc io
int dprintf(int fd, char *fmt, ...) {
    char vsp_buffer[1024];
    va_list ap;
    int rc;
    va_start(ap, fmt);
    rc = vsprintf(vsp_buffer, fmt, ap);
    va_end(ap);
    if(rc>0) write(fd, vsp_buffer, rc);
    return rc;
}
void dputs(const char* str, int fd){
    dprintf(fd, "%s", str);
}

void dputc(char chr, int fd){
    write(fd, &chr, 1);
}

int dgetc(int fd){
    unsigned char buf;
    int ret=read(fd, &buf, 1);
    if(ret==0) return EOF;
    return buf;
}
char* dgets(char* s, int size, int fd){
    int offset=0;
    int buf;
    while(offset<(size-1) && ((buf=dgetc(fd))!=EOF) && (buf!='\n')){
        s[offset]=(char)buf;
        offset++;
    }
    if(offset==0 && buf==EOF) return 0;
    s[offset]=0;
    return s;
}



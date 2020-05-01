#include "tcc.h"
// Remove libc io
int dprintf(int fd, char *fmt, ...) {
    char vsp_buffer[1024];
    va_list ap;
    int rc;
    va_start(ap, &fmt);
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


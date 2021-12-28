#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "ps08.h"

static int isPidValid(const struct dirent *pid){
    const char *p;
    for (p=pid->d_name; *p; p++){
        if (!isdigit(*p))
            return 0;
    }
    return 1;
}

dirs *getpidinfo(void){
    dirs *pdir = (dirs *)malloc(sizeof(dirs));
    pdir->count = 0;
    DIR *proc;
    struct dirent *dir;
    proc = opendir("/proc");
    if (!proc){
        perror("opendir() error");
        exit(6);
    }
    while ((dir = readdir(proc))){
        if (!isPidValid(dir))
            continue;
        strcpy(pdir->larr[pdir->count], "/proc/");
        strcat(pdir->larr[pdir->count], dir->d_name);
        pdir->count++;
    }

    if (closedir(proc) == -1){
        perror("closedir() error");
        exit(4);
    }
    return pdir;
}

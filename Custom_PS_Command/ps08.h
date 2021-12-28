#ifndef ps08_h
#define ps08_h

#define PS 4200000
#define DIRSIZE 256

typedef struct info{
    char *pid;
    char *ppid;
    char *state;
    int file;
    char *command;
} info;

typedef struct{
    char larr[PS][DIRSIZE];
    int count;
} dirs;

info* getInfo(const char *path);
void printInfo(const info *pinfo);
dirs *getpidinfo(void);

#endif
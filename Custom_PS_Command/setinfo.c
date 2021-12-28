#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include "ps08.h"

#define DIRSIZE 256
#define LINE 256

static int file_ctr(const char *path){
    int count = 0;
    struct dirent *iterdir;
    DIR *dir;
    dir = opendir(path);
    if (dir == NULL)
        return -1;
    while ((iterdir = readdir(dir)) != NULL)
        count++;
    if (closedir(dir) == -1)
        exit(4);
    return count;
}

static void statline(info *pinfo, char *line){
    char *end, *dupl1, *dupl2;
    end = strchr(line, '\n');
    if (end)
        end[0] = '\0';
    end = strchr(line, ':');
    if (end)
    {
        end[0] = '\0';
        dupl1 = strdup(line);
        if (!dupl1)
            return;
        end++;
        while (end[0] && isspace(end[0]))
            end++;
        dupl2 = strdup(end);

        if (!dupl2)
            free(dupl1);
        else
        {
            if (strcmp(dupl1, "Pid") == 0)
                pinfo->pid = dupl2;
            else if (strcmp(dupl1, "PPid") == 0)
                pinfo->ppid = dupl2;
            else if (strcmp(dupl1, "State") == 0)
                pinfo->state = dupl2;
            else if (strcmp(dupl1, "Name") == 0)
                pinfo->command = dupl2;
            else
            {
                free(dupl1);
                free(dupl2);
            }
        }
    }
}

info *getInfo(const char *path){
    info *pinfo = (info *)malloc(sizeof(info));
    char spath[DIRSIZE];
    char fd[DIRSIZE];
    FILE *sfile;
    char line[LINE];

    strcpy(fd, path);
    strcat(fd, "/fd");
    strcpy(spath, path);
    strcat(spath, "/status");
    sfile = fopen(spath, "r");
    if (sfile == NULL){
	perror("Failed to open status file");
        exit(1);
    }
    while (fgets(line, sizeof(line), sfile) != NULL)
        statline(pinfo, line);
    fclose(sfile);
    pinfo->file = file_ctr(fd);
    return pinfo;
}

void printInfo(const info *pinfo){
    printf("%-8s%-8s%-15s", pinfo->pid, pinfo->ppid, pinfo->state);
    if (pinfo->file == -1)
        printf("%-14s", "-");
    else
        printf("%-14d", pinfo->file);
    printf("%s\n",pinfo->command);
}

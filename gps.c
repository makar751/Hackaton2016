#include "stdlib.h"
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


struct gpsdata{
    char lon[20],lat[20], name[20];
    unsigned long date,time;
} Data;


void dataInit(char *alon,char *alat, char *aname, unsigned long adate,unsigned long atime){
    strcpy(Data.lon,alon);
    strcpy(Data.lat,alat);
    strcpy(Data.name, aname);
    Data.date=adate;
    Data.time=atime;
}

void putCloseTags(FILE *track)
{
    fputs("</trkseg></trk>\n", track);
    fputs("</gpx>\n", track);
}

FILE *getFile(char *name)
{
    struct stat st = {0};
    if (stat("./tracks", &st) == -1)
        mkdir("./tracks", 0777);
    
    FILE *track;
    char path[40] = {"./tracks/"};
    strcat(path,name);
    strcat(path,".gpx");
    track = fopen(path, "r+");
    if (track == NULL)
    {
        track = fopen(path, "w");
        fputs("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n",track);
        fputs("<gpx version=\"1.0\">\n",track);
        char trname[50] = {"<name>"};
        strcat(trname, name);
        strcat(trname,"</name>\n");
        fputs(trname, track);
        fputs("<trk><trkseg>\n", track);
        putCloseTags(track);
        fclose(track);
        track = fopen(path, "r+");
    }
    return track;
}






#include <stdio.h>
#include <string.h>

char GPS_frame[100]="$GPGLL,4916.45,N,12311.12,W,225444,A,*1D\r\n";
int main(int argc, char *argv[])
{

    printf("%s",GPS_frame);

       char *header=strtok(GPS_frame,",");
       printf("header %s\n",header);
       char *latitude=strtok(NULL,",");
       printf("latitude %s\n",latitude);

       char *Dir=strtok(NULL,",");
       printf("Dir %s\n",Dir);
       char *longitude=strtok(NULL,",");
       printf("longitude %s\n",longitude);

    return 0;
}


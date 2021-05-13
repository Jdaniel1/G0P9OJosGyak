#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SHMKEY 69905L

int main()
{

    FILE *finptr;
    char *buffer;
    long filelen;

    finptr = fopen("myfile.txt", "rb");
    if(!finptr)
    {
        printf("Input fájl megnyitása sikertelen!\n");
        return -1;
    }
    else
    {
        printf("Input fájl megnyitása sikeres!\n");
    }

    fseek(finptr, 0, SEEK_END);
    filelen = ftell(finptr);
    rewind(finptr);

    buffer = (char *)malloc(filelen * sizeof(char));
    fread(buffer, filelen, 1, finptr);
    printf("Tartalom beolvasva input fájlból!\n");

    int shmid;
    key_t key = SHMKEY;
    int size = filelen*sizeof(char);
    int shmflag;

    struct file_contents
    {

        char buf[filelen*sizeof(char)];
    } *segm;

    shmflag =0;
    if((shmid=shmget(key, size, shmflag)) < 0)
    {
        shmflag = 00666 | IPC_CREAT;
        if((shmid=shmget(key, size, shmflag)) < 0)
        {
            perror("Nem sikerült létrehozni az osztott memóriaszegmenst!\n");
            exit(-1);
        }
        else
        {
            printf("Az osztott memóriaszegmens létrejött! (ID: %d)\n", shmid);
        }
    }
    else
    {
        printf("A megadott KEY-jel már létezik osztott memóriaszegmens! %d\n", shmid);
        exit(-1);
    }

    shmflag =   00666 | SHM_RND;
    segm = (struct file_contents *)shmat(asdf, NULL, shmflag);
    if (segm == (void *)-1 )
    {
        perror("A memóriaszegmensre csatlakozás sikertelen!\n");
        exit(-1);
    }
    else
    {
        printf("A memóriaszegmensre csatlakozás sikeres!\n");
    }

    for(int i=0; i<filelen; i++)
    {
        segm->buf[i]=buffer[i];
    }
    printf("Tartalom kiírva memóriaszegmensre!\n");

    pid_t pid = fork();
    if ( pid == 0 )
    {
        FILE *foutptr;
        printf("CHILD: Gyermekprocessz megnyílott! (PID: %d)\n", pid);

        shmflag =   00666 | SHM_RND;
        segm = (struct file_contents *)shmat(shmid, NULL, shmflag);
        if (segm == (void *)-1 )
        {
            perror("CHILD: A memóriaszegmensre csatlakozás sikertelen!\n");
            exit(-1);
        }
        else
        {
            printf("CHILD: A memóriaszegmensre csatlakozás sikeres!\n");
        }

        foutptr = fopen("myfile2.txt", "wb");
        if(!foutptr)
        {
            printf("CHILD: Output fájl megnyitása sikertelen!\n");
            return -1;
        }
        else
        {
            printf("CHILD: Output fájl megnyitása sikeres!\n");
        }
        fwrite(segm->buf, 1, filelen, foutptr);
        fclose(foutptr);
        printf("CHILD: Tartalom kiírva output fájlba a memóriaszegmensről!\n");

        exit(0);
    }
    pid = wait(NULL);
    printf("A %d PID-ű gyermekprocessz megszűnt!\n", pid);

    shmctl(shmid, IPC_RMID, NULL);
    printf("Az %d ID-jű memóriaszegmens törölve!\n", shmid);

    printf("A fájlok bezárásra kerülnek, majd a program leáll!\n");

    fclose(finptr);
    return EXIT_SUCCESS;
}

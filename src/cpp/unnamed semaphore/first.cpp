//
// Created by francesco
//    _______  __   _____  ___   _______         _______   ______   _____  ___   _______
//  |   __ "\|" \ (\"   \|"  \ /" _   "|       |   __ "\ /    " \ (\"   \|"  \ /" _   "|
//  (. |__) :)|  ||.\\   \    (: ( \___)       (. |__) :)/ ____  \|.\\   \    (: ( \___)
//  |:  ____/|:  ||: \.   \\  |\/ \            |:  ____/  /    ) :): \.   \\  |\/ \
//  (|  /    |.  ||.  \    \. |//  \ ___       (|  /  (: (____/ //|.  \    \. |//  \ ___
// /|__/ \   /\  |\    \    \ (:   _(  _|     /|__/ \  \        / |    \    \ (:   _(  _|
//(_______) (__\_|_)___|\____\)\_______)     (_______)  \"_____/   \___|\____\)\_______)
//
#include "common.hpp"

using namespace std;

void init_gestore(struct gestore_t *g)
{
    sem_init(&g->mutex,1,1);
    sem_init(&g->sa,1,0);
    sem_init(&g->sb,1,0);
}

int main (){
    int fd;
    fd = shm_open(RNAME_IMG_TOP, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd == -1){
        perror("shm_open error!");
        exit(EXIT_FAILURE);
    }
    if (ftruncate(fd, sizeof(struct region)) == -1){
        perror("ftruncate error!");
        exit(EXIT_FAILURE);
    }
    rptr = static_cast<region *>(mmap(NULL, sizeof(struct region), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
    if (rptr == MAP_FAILED){
        perror("mmap() failed!");
        exit(EXIT_FAILURE);
    }

    fd = shm_open(RNAME_GESTORE, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd == -1){
        printf("shm_open error! %s", strerror(errno));
        exit(EXIT_FAILURE);
    }
    if (ftruncate(fd, sizeof(struct gestore_t)) == -1){
        printf("ftruncate error! %s", strerror(errno));
        exit(EXIT_FAILURE);
    }
    gestore = static_cast<gestore_t *>(mmap(NULL, sizeof(struct region), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
    if (gestore == MAP_FAILED){
        printf("mmap error %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    init_gestore(gestore);

    cout << "waiting to second...\n";
    if (sem_wait(&gestore->sa) == -1)
        printf("error sem_wait %s", strerror(errno));
    cout<< "first I write to shared buffer" << endl;

    for (int i=0; i<50; i++)
        rptr->buf[i] = (char)(i+65);
    rptr->len = 50;

    sem_post(&gestore->sb);
    exit(EXIT_SUCCESS);
}

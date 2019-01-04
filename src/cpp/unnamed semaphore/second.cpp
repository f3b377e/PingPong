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


int main (){
    int fd = shm_open(RNAME_IMG_TOP, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
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
        printf("mmap error %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    int fd2 = shm_open(RNAME_GESTORE, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd2 == -1){
        perror("shm_open error!");
        exit(EXIT_FAILURE);
    }
    if (ftruncate(fd2, sizeof(struct gestore_t)) == -1){
        perror("ftruncate error!");
        exit(EXIT_FAILURE);
    }

    gestore = static_cast<gestore_t *>(mmap(NULL, sizeof(struct region), PROT_READ | PROT_WRITE, MAP_SHARED, fd2, 0));
    if (gestore == MAP_FAILED){
        printf("mmap error %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    sem_post(&gestore->sa);
    cout << "Waiting for first...\n";
    sem_wait(&gestore->sb);

    for (int i=0; i < rptr->len; i++)
        cout << rptr->buf[i] << " ";
    cout << "\nlen:" << rptr->len << endl;

    if(munmap(rptr, MAX_LEN) < 0)
        printf("unmap error %s", strerror(errno));
    shm_unlink(RNAME_IMG_TOP);
    shm_unlink(RNAME_GESTORE);
    close(fd);
    close(fd2);

    exit(EXIT_SUCCESS);
}

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
    sem_t *sem_second;
    sem_t *sem_first;

    sem_second = sem_open(SNAME_SECOND, 0);
    sem_first = sem_open(SNAME_FIRST, 0);

    if (sem_first == SEM_FAILED) {
        perror("sem_open(3) error");
        exit(EXIT_FAILURE);
    }
    if (sem_second == SEM_FAILED) {
        perror("sem_open(3) error");
        exit(EXIT_FAILURE);
    }


    /* Create shared memory object and set its size */
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
    if (rptr == MAP_FAILED) {
        printf("mmap error %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    cout<< "Ok first ci sono, puoi eseguire\n";
    sem_post(sem_first);
    cout<< "Mi blocco in attesa che first scriva\n";

    sem_wait(sem_second);
    cout<< "OK Now I can read from shared buffer: ";

    for (int i=0; i < rptr->len; i++)
        cout << rptr->buf[i] << " ";
    cout << "\nlen:" << rptr->len << endl;

    if(munmap(rptr, MAX_LEN) < 0)
        printf("unmap error %s", strerror(errno));
    shm_unlink(RNAME_IMG_TOP);
    close(fd);

    exit(EXIT_SUCCESS);
}

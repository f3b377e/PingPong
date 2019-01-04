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
    sem_second = sem_open(SNAME_SECOND, O_CREAT, 0644, 0);
    sem_first = sem_open(SNAME_FIRST, O_CREAT, 0644, 0);
    sem_unlink(SNAME_FIRST);
    sem_unlink(SNAME_SECOND);

    if (sem_first == SEM_FAILED) {
        perror("sem_open(3) error");
        exit(EXIT_FAILURE);
    }
    if (sem_second == SEM_FAILED) {
        perror("sem_open(3) error");
        exit(EXIT_FAILURE);
    }


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


    cout<< "waitng to second..." << endl;
    sem_wait(sem_first);

    cout<< "first I write to shared buffer" << endl;
    for (int i=0; i<50; i++)
        rptr->buf[i] = (char)(i+65);
    rptr->len = 50;

    sem_post(sem_second);


    exit(EXIT_SUCCESS);
}

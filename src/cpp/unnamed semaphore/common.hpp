//
// Created by francesco on 19/11/18.
//

#ifndef PINGPONG_COMMON_H
#define PINGPONG_COMMON_H

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>   /* shm_open, mmap, ftruncate    */
#include <sys/stat.h>   /* For mode constants */
#include <fcntl.h>      /* For O_* constants */
#include <semaphore.h>  /* named semaphore              */
#include <errno.h>
#include <string.h>
#include <pthread.h>

#define RNAME_IMG_TOP       "/Shared_Region_1"
#define RNAME_GESTORE   "/Shared_Region_2"
#define MAX_LEN 100

struct gestore_t {
    sem_t mutex;
    sem_t sa, sb;
} *gestore;

struct region {        /* Defines "structure" of shared memory */
    int len;
    char buf[MAX_LEN];
} *rptr;

#endif //PINGPONG_COMMON_H

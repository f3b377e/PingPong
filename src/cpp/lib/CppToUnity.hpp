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

#pragma once

#if defined(_MSC_VER)
//  Microsoft
    #define EXPORT __declspec(dllexport)
    #define IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
//  GCC LINUX
    #define DLL_EXPORT __attribute__((visibility("default")))
    #define DLL_IMPORT
#else
    #define EXPORT
    #define IMPORT
    #pragma warning Unknown dynamic link import/export semantics.
#endif

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
#include <iostream>
#include <fstream>

#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

#define RNAME_IMG_TOP   "/My_Shared_Region_mem_top"
#define RNAME_IMG_FRONT "/My_Shared_Region_mem_fro"
#define RNAME_POS       "/My_Shared_Region_mem_pos"

struct gestore_t {
    sem_t mutex;
    sem_t sread, swrite;
    int nr, nw, nbr, nbw;
};

struct shared_img_t {
    int height, width, channel;
    char rname[26];             // keep it track to close it
    gestore_t gestore;          // gestore to sync read writer access memory
    uint8_t imgdata[0];
};

struct pos_t{
    int x, y, z;
    gestore_t gestore;
};

extern "C" {
    /**
     * SetTextureCVMat allow you to write image in shared memory through shared library.
     * Unity project use this function to "send" the captured image from unity camera to Cpp exe.
     * A synchronization problem has been solved in this funcion! Multiple thread could read,
     * but only once at time can write; here we are interested only to write mode, read is delegated
     * to GetTextureCVMat().
     * To solve a sync issues the UNnamed Semaphore in shared memory as been used.
    */
    DLL_EXPORT void SetTextureCVMat(struct shared_img_t* img, unsigned char *texData);

    /**
     * GetTextureCVMat allow you to read image in shared memory through shared library.
     * Cpp exe use this function to capture the image from unity.
     * A synchronization problem has been solved in this funcion! Multiple thread could read,
     * but only once at time can write; here we are interested only to read mode, write is delegated
     * to SetTextureCVMat().
     * To solve a sync issues the UNnamed Semaphore in shared memory as been used.
    */
    DLL_EXPORT void GetTextureCVMat(struct shared_img_t* img, struct pos_t*pos, cv::Mat &frame);

    /**
    * InitSharedRegion allow you to initialize image in shared memory.
    * Unity project use this to set width and heigth of each image.
    */
    DLL_EXPORT void *InitSharedRegion(int width, int heigth, int channel, bool istopcam);

    /**
    * RemoveSharedRegion allow you to remove image and data in shared memory.
    * Unity project use this.
    */
    DLL_EXPORT void RemoveSharedRegion(struct shared_img_t* img);

    DLL_EXPORT void *InitSharePos();

    DLL_EXPORT void RemoveSharePos(struct pos_t* pos);

    DLL_EXPORT void SetPos(struct pos_t* pos, const int &x, const int &y, const int &z);

    DLL_EXPORT void GetPos(struct pos_t* pos, int &x, int &y, int &z);
}
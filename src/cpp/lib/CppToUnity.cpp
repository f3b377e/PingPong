//
// Created by francesco on 14/11/18.
//

#include "CppToUnity.hpp"

void init_gestore(struct gestore_t &gestore) {
    sem_init(&gestore.mutex,1,1);
    sem_init(&gestore.sread,1,0);
    sem_init(&gestore.swrite,1,0);

    gestore.nr=0;
    gestore.nbr=0;
    gestore.nw=0;
    gestore.nbw=0;
}

void preambleReadImg(struct gestore_t &img){
    sem_wait(&img.mutex);
    img.nbr++;
    if (img.nw == 0 && img.nr == 0) {
        img.nr++;
        img.nbr--;
        sem_post(&img.sread);
    }
    sem_post(&img.mutex);
    sem_wait(&img.sread);
}

void postambleReadImg(struct gestore_t &img, struct gestore_t &pos){
    sem_wait(&img.mutex);
    img.nr--;
    if (img.nbw > 0 && img.nr == 0 && img.nw ==0) {
        img.nbw--; img.nw++;
        sem_post(&img.swrite);
    }
    if (pos.nbw > 0 && pos.nw == 0 && pos.nr==0){
        pos.nbw--;
        pos.nw++;
        sem_post(&pos.swrite);
    }
    sem_post(&img.mutex);
}

void preambleWriteImg(struct gestore_t &gestore){
    sem_wait(&gestore.mutex);
    if (gestore.nr >0 || gestore.nw >0)
        gestore.nbw++;
    else {
        gestore.nw++;
        sem_post(&gestore.swrite);
    }
    sem_post(&gestore.mutex);
    sem_wait(&gestore.swrite);
}

void postambleWriteImg(struct gestore_t &img) {
    sem_wait(&img.mutex);
    img.nw--;
    if (img.nbr > 0 && img.nr == 0){
        img.nbr--;
        img.nr++;
        sem_post(&img.sread);
    }
    else if (img.nbw>0 && img.nbr == 0 && img.nr ==0){
        img.nw++;
        img.nbw--;
        sem_post(&img.swrite);
    }
    sem_post(&img.mutex);
}

void preambleWritePos(struct gestore_t &pos){
    sem_wait(&pos.mutex);
    if (pos.nr >0 || pos.nw >0)
        pos.nbw++;
    else {
        pos.nw++;
        sem_post(&pos.swrite);
    }
    sem_post(&pos.mutex);
    sem_wait(&pos.swrite);
}

void postambleWritePos(struct gestore_t &pos) {
    sem_wait(&pos.mutex);
    pos.nw--;
    if (pos.nbr > 0 && pos.nr == 0){
        pos.nbr--;
        pos.nr++;
        sem_post(&pos.sread);
    }
    else if (pos.nbw>0 && pos.nbr == 0 && pos.nr ==0){
        pos.nw++;
        pos.nbw--;
        sem_post(&pos.swrite);
    }
    sem_post(&pos.mutex);
}

void preambleReadPos(struct gestore_t &pos){
    sem_wait(&pos.mutex);
    pos.nbr++;
    if (pos.nw == 0 && pos.nr == 0) {
        pos.nr++;
        pos.nbr--;
        sem_post(&pos.sread);
    }
    sem_post(&pos.mutex);
    sem_wait(&pos.sread);
}

void postambleReadPos(struct gestore_t &pos){
    sem_wait(&pos.mutex);
    pos.nr--;
    if (pos.nbw > 0 && pos.nr == 0 && pos.nw == 0) {
        pos.nbw--; pos.nw++;
        sem_post(&pos.swrite);
    }
    sem_post(&pos.mutex);
}


void *mmap_region(const char *rname, size_t len){
    int fd = shm_open(rname, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd == -1){
        printf("shm_open() error, in mmap_region: %s",strerror(errno));
        exit(EXIT_FAILURE);
    }
    if (ftruncate(fd, len) == -1){
        printf("ftruncate() error, in mmap_region: %s",strerror(errno));
        exit(EXIT_FAILURE);
    }
    void *ret = mmap(nullptr, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ret == MAP_FAILED){
        printf("mmap() error, in mmap_region: %s",strerror(errno));
        exit(EXIT_FAILURE);
    }
    return ret;
}

DLL_EXPORT void *InitSharedRegion(int width, int heigth, int channel, bool istopcam){
    size_t len = sizeof(struct shared_img_t) + sizeof(uint8_t) * width * heigth * channel;
    std::string name = istopcam ? RNAME_IMG_TOP : RNAME_IMG_FRONT;

    auto ret = static_cast<shared_img_t *>(mmap_region(&name[0], len));
    ret->height = heigth;
    ret->width = width;
    ret->channel = channel;
    strcpy(ret->rname, name.c_str());
    init_gestore(ret->gestore);

    return ret;
}

DLL_EXPORT void *InitSharePos(){
    size_t len = sizeof(struct pos_t);
    auto ret = static_cast<pos_t *>(mmap_region(RNAME_POS, len));
    ret->x = 0;
    ret->y = 0;
    ret->z = 0;
    init_gestore(ret->gestore);

    return ret;
}

DLL_EXPORT void SetPos(struct pos_t* pos, const int &x, const int &y, const int &z){
    preambleWritePos(pos->gestore);

    if (x > 0) pos->x = x;
    if (y > 0) pos->y = y;
    if (z > 0) pos->z = z;

    postambleWritePos(pos->gestore);
}

DLL_EXPORT void GetPos(struct pos_t* pos, int &x, int &y, int &z){
    preambleReadPos(pos->gestore);

    x = pos->x;
    y = pos->y;
    z = pos->z;

    postambleReadPos(pos->gestore);
}

DLL_EXPORT void SetTextureCVMat(struct shared_img_t* img, unsigned char *texData){
    preambleWriteImg(img->gestore);

    size_t len = sizeof(uint8_t) * img->width * img->height * img->channel;
    memcpy(img->imgdata, texData, len);

    postambleWriteImg(img->gestore);
}

DLL_EXPORT void GetTextureCVMat(struct shared_img_t* img, struct pos_t*pos, cv::Mat &frame){
    preambleReadImg(img->gestore);

    frame = cv::Mat(img->height, img->width, CV_8UC4, img->imgdata);

    postambleReadImg(img->gestore, pos->gestore);
}

DLL_EXPORT void RemoveSharedRegion(struct shared_img_t* img){
    size_t len = sizeof(struct shared_img_t) + sizeof(uint8_t) * img->width * img->height *img->channel;
    shm_unlink(img->rname);
    if(munmap(img, len) < 0) {
        printf("unmap error %s", strerror(errno));
    }
}

DLL_EXPORT void RemoveSharePos(struct pos_t* pos){
    size_t len = sizeof(struct pos_t);
    shm_unlink(RNAME_POS);
    if(munmap(pos, len) < 0) {
        printf("unmap error %s", strerror(errno));
    }
}
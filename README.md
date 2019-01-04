Soft RealTime ball detection in using OpenCV & Unity 
=================
Il progetto consiste nella realizzazione di una racchetta da pingpong che intercetta la pallina rispondendo così alla battuta del giocatore. Per giocare si utilizza il mouse che simula il movimento della racchetta.
Il progetto è diviso in due parti principali: un programma per il rendering video, utilizzando Unity, e un programma in cpp per object detection.

Per poter comunicare tra un processo unity e un'altro in cpp ci sono diversi modi ([stackoverflow](https://stackoverflow.com/questions/32632645/fastest-way-to-do-local-ipc-between-a-unity-process-and-another-c-sharp-process)), quello scelto da me è forse il più utilizzato e prevede la creazione di una DLL in cpp per poter condividere le stesse funzioni sia lato unity che lato cpp.
Creata la nostra DLL il problema principale che bisogna affrontare è come passare da un'area di memoria gestita da un garbage collector (C# appunto) ad un' altra in cui non esiste alcun tipo di gestore (cpp)? Questo problema e la soluzione prendono il nome di [Marshaling](https://www.codeproject.com/Articles/66245/Marshaling-with-Csharp-Chapter-1-Introducing-Marsh.aspx).

Un secondo problema è come condividere e scambiare dati tra i due processi. 
Per risolvere questo problema ci creaiamo una nostra area di memoria condivisa a cui entrambi i processi potranno accedere (utiliziamo [mmap](http://man7.org/linux/man-pages/man2/mmap.2.html)).

A questo punto abbiamo più processi che possono accedere alla stessa area di memoria ma non un meccanismo di sincronizzazione. Per questo utilizziamo pthread ([some](https://computing.llnl.gov/tutorials/pthreads/) [link](https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html)) in memoria condivisa (secondo parametro settato a 1):
```cpp
void init_gestore(struct gestore_t &gestore) {  
  sem_init(&gestore.mutex,1,1);  
  sem_init(&gestore.sread,1,0); 
  sem_init(&gestore.swrite,1,0);
}
```

A questo punto abbiamo tutto il neccessario per poter:
* (unity) ottenere un immagine da una cam di unity
* (unity) ottenere il nostro puntatore immagine
* (DLL) **copiare** i dati dell'immagine nella nostra area di memoria condivisa
* (cpp) fare object detection (color detection is more appropriate) con l'aiuto della libreria opencv ottendendo così la posizione nello spazio della pallina.
* notificare la posizione della pallina al processo unity
* sincronizzare i processi

Unity
---
Lato unity il problema principale incontrato per la realizzazione è stato quello catturare le immagine di Unity in RealTime. Per osservare i tempi si è utilizzato il Profiler di Unity.
Grazie l'aiuto di [questa guida](https://medium.com/google-developers/real-time-image-capture-in-unity-458de1364a4c) sono riuscito ad ottenere FPS abbastanza alti per offrire un fluidità al gioco.
![FPS  > 30](https://i.imgur.com/bn3zzkW.jpg)


CPP
---
Problema di sincronizzazione tra thread è stato risolto assegnando  la seguente sequenzialità tra le azioni:
![enter image description here](https://i.imgur.com/0GdZygN.jpg)
E i metodi in questione sono i seguenti:

```cpp
DLL_EXPORT void SetTextureCVMat(struct shared_img_t* img, unsigned char *texData){
    preambleWriteImg(img->gestore); // blocking call

    size_t len = sizeof(uint8_t) * img->width * img->height * img->channel;
    memcpy(img->imgdata, texData, len);

    postambleWriteImg(img->gestore); // blocking call
}

DLL_EXPORT void SetPos(struct pos_t* pos, const int &x, const int &y, const int &z){
    preambleWritePos(pos->gestore); // blocking call

    if (x > 0) pos->x = x;
    if (y > 0) pos->y = y;
    if (z > 0) pos->z = z;

    postambleWritePos(pos->gestore); // blocking call
}

// same concept for get
DLL_EXPORT void GetTextureCVMat(..){..}
DLL_EXPORT void GetPos(..){..}

```

Ball Detection:
---
Per ottenere la posizione della pallina si è utilizzato un "trucco":
Si è passati dallo spazio originale RGB allo spazio HSV riuscendo così ad ottenere solo le componenti di colore della pallina.

di seguito un immagine che spiega meglio:
![ball detection img](https://i.imgur.com/kYix4nQ.jpg)

Risultato:
---
[![Watch the video](https://i.imgur.com/ZMlnisT.png)](https://www.dropbox.com/home/Public?preview=pingpong.mkv)

Download to try:
---
Only Linux: 
* [Download](https://www.dropbox.com/s/eb6ypo22pfw5luj/PingPong.tar.xz?dl=0)  - 6:37 PM Friday, January 4, 2019 (GMT+1)

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

#include <iostream>
#include "threads.hpp"

thread::thread(void *(*func) (void *), void *arg) {
    pthread_attr_init(&tattr_);

    int ret = pthread_create(&thread_, &tattr_, func, arg);
    if (ret)
        throw std::runtime_error("Error - pthread_create() return code:" + std::to_string(ret) +"\n");
}

thread::~thread() {
    pthread_attr_destroy(&tattr_);
}

pthread_t thread::getThread() const {
    return thread_;
}

void thread::setDetached(){
    pthread_attr_setdetachstate(&this->tattr_, PTHREAD_CREATE_DETACHED);
}

int joinThread(thread &t, void **retval){
    int ret = pthread_join(t.getThread(), (void **)retval);
    if (ret)
        throw std::runtime_error("Error - pthread_join() return code:" + std::to_string(ret) +"\n");

    return ret;
}
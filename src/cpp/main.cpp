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
#include <fstream>
#include "lib/CppToUnity.hpp"
#include "thread/threads.hpp"

#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace std;

void morphOps(cv::Mat &thresh, const cv::Size &size){
    cv::Mat dilateElement = getStructuringElement(cv::MORPH_RECT,size);

    dilate(thresh,thresh,dilateElement);
}

bool trackFilteredObject(int &x, int &y, const cv::Mat& threshold,
                        const int &MIN_OBJECT_AREA, const int &MAX_OBJECT_AREA){

    vector< vector<cv::Point> > contours;
    vector<cv::Vec4i> hierarchy;
    findContours(threshold,contours,hierarchy,cv::RETR_CCOMP,cv::CHAIN_APPROX_SIMPLE);
    bool objectFound = false;
    double refArea = 0;
    const int MAX_NUM_OBJECTS=10;

    if (!hierarchy.empty()) {
        int numObjects = static_cast<int>(hierarchy.size());
        if(numObjects<MAX_NUM_OBJECTS){
            for (int index = 0; index >= 0; index = hierarchy[index][0]) {
                cv::Moments moment = moments((cv::Mat)contours[index]);
                double area = moment.m00;
                    if(area>MIN_OBJECT_AREA && area<MAX_OBJECT_AREA && area>refArea){
                        x = static_cast<int>(moment.m10 / area);
                        y = static_cast<int>(moment.m01 / area);
                        objectFound = true;
                        refArea = area;
                    }else
                        objectFound = false;
            }
        }
    }

    return objectFound;
}

void *read_top_cam(void *arg){
    auto img = static_cast<shared_img_t *>(InitSharedRegion(368, 736, 4, true));
    auto pos = static_cast<pos_t *>(InitSharePos());

    const int H_MIN = 32;
    const int H_MAX = 60;
    const int S_MIN = 10;
    const int S_MAX = 256;
    const int V_MIN = 25;
    const int V_MAX = 256;
    const int MIN_OBJECT_AREA = 8*8;
    const int MAX_OBJECT_AREA = 20*20;
    int x=0, y=0;

    cv::Mat HSV;
    cv::Mat threshold;
    cv::Mat cameraFeed;
    cv::Size size {2,2};
    cv::Scalar lowerb {H_MIN,S_MIN,V_MIN};
    cv::Scalar upperb {H_MAX,S_MAX,V_MAX};

    while(1){
        GetTextureCVMat(img,pos,cameraFeed); // bloccante
        //imshow("Unity Cam", cameraFeed);
        cv::cvtColor(cameraFeed, HSV, cv::COLOR_BGR2HSV);
        //imshow("HSV Cam", HSV);
        cv::inRange(HSV, lowerb,upperb, threshold);
        morphOps(threshold, size);
        trackFilteredObject(x, y, threshold, MIN_OBJECT_AREA, MAX_OBJECT_AREA);
        //imshow("Ball Detection", threshold);
        SetPos(pos, -1, -1, y); // bloccante
        //cv::waitKey(2);
    }
}

void *read_front_cam(void *arg){
    auto img = static_cast<shared_img_t *>(InitSharedRegion(720, 360, 4, false));
    auto pos = static_cast<pos_t *>(InitSharePos());

    const int H_MIN = 32;
    const int H_MAX = 60;
    const int S_MIN = 10;
    const int S_MAX = 256;
    const int V_MIN = 25;
    const int V_MAX = 256;
    const int MIN_OBJECT_AREA = 2*2;
    const int MAX_OBJECT_AREA = 35*35;
    int x=0, y=0;

    cv::Mat HSV;
    cv::Mat threshold;
    cv::Mat cameraFeed;
    cv::Size size {2,2};
    cv::Scalar lowerb {H_MIN,S_MIN,V_MIN};
    cv::Scalar upperb {H_MAX,S_MAX,V_MAX};

    while(1){
        GetTextureCVMat(img, pos, cameraFeed);
        cv::cvtColor(cameraFeed, HSV, cv::COLOR_BGR2HSV);
        cv::inRange(HSV, lowerb, upperb, threshold);
        morphOps(threshold, size);
        trackFilteredObject(x, y, threshold, MIN_OBJECT_AREA, MAX_OBJECT_AREA);
        SetPos(pos, x, y, -1);
    }
}

int main (){
    struct shared_img_t *imgTop;    // w:368 * h:736 * c:4
    struct shared_img_t *imgFront;  // w:720 * h:360 * c:4

    thread tTop{read_top_cam};
    thread tFront(read_front_cam);
    system("./pingpong.x86_64");

    joinThread(tTop, nullptr);
    joinThread(tFront, nullptr);

    exit(EXIT_SUCCESS);
}
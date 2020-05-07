//
// Created by admin on 2020/5/7.
//

#ifndef UNTITLED_EPOLL_H
#define UNTITLED_EPOLL_H

#include <sys/epoll.h>

class Epoll {
public:
    Epoll();
    int epfd;
    epoll_event event;
    int wait(epoll_event *ev,int event_len);

    int operator +=(int fd);
    int operator -=(int fd);

};


#endif //UNTITLED_EPOLL_H

//
// Created by admin on 2020/5/7.
//

#include "Epoll.h"
#include <sys/epoll.h>
#include <stdio.h>
#include <unistd.h>
Epoll::Epoll(){

    epfd = epoll_create(1);
    if(epfd < 0){
        perror("create error");
    }
}
int Epoll::operator-=(int fd) {

    if(epoll_ctl(epfd,EPOLL_CTL_DEL,fd,&event) < 0){perror("delete fd error:"); return -1;};
    close(fd);
    return 0;
}


int Epoll::operator+=(int fd) {
    event.data.fd = fd;
    event.events = EPOLLIN;
    if(epoll_ctl(epfd,EPOLL_CTL_ADD,fd,&event) < 0){perror("add fd to epoll error: ");return -1;}
    return 0;
}

int Epoll::wait(epoll_event *ev,int event_len){
    while(true) {
        int len = epoll_wait(epfd, ev, event_len, -1);
        if(len > 0){
            return len;
        }
    }
}

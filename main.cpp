#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
//#include <errno.h>
#include <stdio.h>
#include <sys/epoll.h>
#include <string.h>
#include <unistd.h>
#include "Epoll.h"



int main(){

    epoll_event ev[1024],event;

    sockaddr_in ser;
    memset(ev,0,sizeof(epoll_event)*1024);
    memset(&ser,0,sizeof(socklen_t));

    int epfd, nfd;
    ser.sin_family = AF_INET;
    ser.sin_port = htons(9000);
    ser.sin_addr.s_addr = htonl(inet_addr("0.0.0.0"));

    if((nfd = socket(AF_INET,SOCK_STREAM,0)) < 0){
        perror("create socket error: ");
    }
    if(bind(nfd,(sockaddr*)&ser,sizeof(ser)) < 0){
        perror("bind error:");
    }
    if(listen(nfd,65536) < 0){
        perror("lisent error: ");
    }




    Epoll e;
    e += nfd;

    while(true) {
        int len = e.wait(ev, 1024);
        for (int i = 0; i < len; i++) {
            //链接事件
            if (ev[i].data.fd == nfd) {
                sockaddr_in cli;
                socklen_t  len = sizeof(cli);
                int cfd = accept(nfd,(sockaddr*)&cli,&len);
                if(cfd < 0){
                    perror("connect error: ");
                }
                else{
                    e += cfd;
                }
                printf("链接事件\n");
            }
            //end
            if(ev[i].data.fd>nfd && (ev[i].events & EPOLLIN)){
                char buf[1024];
                int rl = recv(ev[i].data.fd,buf,1024,0);
                buf[rl] = '\0';
                printf("%s",buf);
                if(rl <= 0){
                    e-=ev[i].data.fd;
                    printf("%d服务器断开链接\n",ev[i].data.fd);
                }

            }
        }
    }






//    if((epfd = epoll_create(1)) < 0){
//        perror("create epoll error: ");
//    }
//
//    //监听读取事件
//    event.data.fd = nfd;
//    event.events = EPOLLIN;
//    if(epoll_ctl(epfd,EPOLL_CTL_ADD,nfd,&event) < 0){
//        perror("add server fd error: ");
//    }




//    while(1){
//
//        int event_len = epoll_wait(epfd,ev,1025,-1);
//        printf("_______\n");
//        for(int i = 0;i < event_len;i++){
//            //对象没有链接 进入链接事件
//            if(ev[i].data.fd == nfd){
//                sockaddr_in cli;
//                socklen_t len = sizeof(cli);
//                int cfd = accept(nfd,(sockaddr*)&cli,&len);
//                if(cfd < 0){
//                    continue;
//                }
//                else{
//                    event.data.fd = cfd;
//                    event.events = EPOLLIN;
//                    if(epoll_ctl(epfd,EPOLL_CTL_ADD,cfd,&event)<0){perror("add error:");}
//                    printf("%d服务器链接成功\n",cfd);
//                }
//            }
//            //end
//            //换从区有数据 进入读取事件中
//            if(ev[i].data.fd>nfd && (ev[i].events & EPOLLIN)){
//                char buf[1024];
//                int rl = recv(ev[i].data.fd,buf,1024,0);
//                buf[rl] = '\0';
//                printf("%s",buf);
//                if(rl <= 0){
//                    if(epoll_ctl(epfd,EPOLL_CTL_DEL,ev[i].data.fd,&event)<0){perror("add error:");}
//                    close(ev[i].data.fd);
//                    printf("%d服务器断开链接\n",ev[i].data.fd);
//                }
//            }
//            //end
//            if(ev[i].events & EPOLLERR){
//                printf("error");
//            }
//        }
//    }
}
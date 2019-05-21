//
// Created by Алексей Пономарев on 2019-05-21.
//

#ifndef WEB_SERVER_EPOLL_API_H
#define WEB_SERVER_EPOLL_API_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/event.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <ctype.h>

#define exit_if(r, ...) if(r) {printf(__VA_ARGS__); printf("error no: %d error msg %s\n", errno, strerror(errno)); exit(1);}

const int kReadEvent = 1;
const int kWriteEvent = 2;


void setNonBlock(int fd) {
  int flags = fcntl(fd, F_GETFL, 0);
  exit_if(flags<0, "fcntl failed");
  int r = fcntl(fd, F_SETFL, flags | O_NONBLOCK);
  exit_if(r<0, "fcntl failed");
}

void updateEvents(int efd, int fd, int events, bool modify) {
  struct kevent ev[2];
  int n = 0;
  if (events & kReadEvent) {
    EV_SET(&ev[n++], fd, EVFILT_READ, EV_ADD|EV_ENABLE, 0, 0, (void*)(intptr_t)fd);
  } else if (modify){
    EV_SET(&ev[n++], fd, EVFILT_READ, EV_DELETE, 0, 0, (void*)(intptr_t)fd);
  }
  if (events & kWriteEvent) {
    EV_SET(&ev[n++], fd, EVFILT_WRITE, EV_ADD|EV_ENABLE, 0, 0, (void*)(intptr_t)fd);
  } else if (modify){
    EV_SET(&ev[n++], fd, EVFILT_WRITE, EV_DELETE, 0, 0, (void*)(intptr_t)fd);
  }
  printf("%s fd %d events read %d write %d\n",
         modify ? "mod" : "add", fd, events & kReadEvent, events & kWriteEvent);
  int r = kevent(efd, ev, n, NULL, 0, NULL);
  exit_if(r, "kevent failed ");
}

void handleAccept(int efd, int fd) {
  int new_fd;
  read(fd, &new_fd, sizeof(new_fd));
  if (new_fd < 0)
    return;
  setNonBlock(new_fd);
  updateEvents(efd, new_fd, kReadEvent, false);
}

void handleRead(int efd, int fd) {
  char buf[4096];
  int n = 0;
  while ((n=::read(fd, buf, sizeof buf)) > 0) {
    printf("read %d bytes\n", n);
    int r = ::write(fd, buf, n); //写出读取的数据
    //实际应用中，写出数据可能会返回EAGAIN，此时应当监听可写事件，当可写时再把数据写出
    exit_if(r<=0, "write error");
  }
  if (n<0 && (errno == EAGAIN || errno == EWOULDBLOCK))
    return;
  exit_if(n<0, "read error"); //实际应用中，n<0应当检查各类错误，如EINTR
  printf("fd %d closed\n", fd);
  close(fd);
}

void handleWrite(int efd, int fd) {
  //实际应用应当实现可写时写出数据，无数据可写才关闭可写事件
  updateEvents(efd, fd, kReadEvent, true);
}



#endif //WEB_SERVER_EPOLL_API_H

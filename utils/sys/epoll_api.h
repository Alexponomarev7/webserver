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
#include <sys/epoll.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <ctype.h>


void make_non_blocking(int fd) {
  int flags = fcntl(fd, F_GETFL);
  fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

enum {
  MaxPendingEvents = 10000
};

typedef struct {
  int fd;
  bool is_socket;
} data_t;

data_t* create_event_data(int epoll_fd, int fd) {
  make_non_blocking(fd);
  data_t *data = (data_t*)calloc(1, sizeof(*data));
  data->fd = fd;
  data->is_socket = false;

  struct epoll_event event_ready_read;
  event_ready_read.events = EPOLLIN;
  event_ready_read.data.ptr = data;

  epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &event_ready_read);

  return data;
}



#endif //WEB_SERVER_EPOLL_API_H

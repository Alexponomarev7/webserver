# WEB SERVER (Based on Ngnix)

Author: Alex Ponomarev

Langs: C++, C, CMake

## Описание

Proxy-server is implemented in C++ and tested under Mac OS HighSiera. I made daemon, which is controlled by current commands **sudo ./wserver start** and **sudo ./wserver stop**. Running under **sudo** is required. Running main server process hasn't root permissions.

Realized current levels of logging:
* SERVER *1*
* DAEMON *2*
* MONITOR *4*

In config **config.cfg** you can set up desired logging level.

## Structure

The server's architecture consists three parts: Server, Daemon, Monitor. Monitor looks after Daemon and Server. It tracks all signals, saves it's pid in **/var/run/web_server.pid**. Also it supports config reloading of working Daemon service.

Support multithreading. Daemon runs ThreadWorkload and tracks the execution, at the end it stops all threads.

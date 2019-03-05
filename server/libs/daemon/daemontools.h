//
// Created by Alexey A. Ponomarev on 05.03.19.
//

#ifndef WEB_SERVER_DAEMONTOOLS_H
#define WEB_SERVER_DAEMONTOOLS_H

#include <sys/fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <utils/string/string.h>
#include <sys/stat.h>

class DaemonTools {
public:
    static void StartDaemon();
    static void MonitorProc();
};


#endif //WEB_SERVER_DAEMONTOOLS_H

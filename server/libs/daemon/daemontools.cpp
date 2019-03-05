//
// Created by Alexey A. Ponomarev on 05.03.19.
//

#include "daemontools.h"

void DaemonTools::StartDaemon() {
    pid_t pid = fork();
    if (pid == -1) {
        throw (StringBuilder() << "Error: Start Daemon failed (" << strerror(errno) << ").").Get();
    } else if (pid == 0) {
        umask(0);
        setsid();
        chdir("/");

        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);

        DaemonTools::MonitorProc();
    }
}
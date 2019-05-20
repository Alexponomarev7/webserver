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
#include <signal.h>

#include <utils/logger/logger.h>
#include <utils/string/string.h>
#include <server/libs/connection/connection.h>
#include <server/libs/daemon/config.h>
#include <vector>
#include <thread>

namespace Daemon {

class DaemonTools {
 public:
  DaemonTools() = delete;

  static void StartDaemon(const Config& cfg);

  static void StopDaemon();

  static bool IsOpen() {
    return is_opened_;
  }

 private:
  static void MonitorProc();

  static void UpdatePidFile();

  static int WorkProc(int FD_LIMIT);

  static void InitWorkThread();

  static void DestroyWorkThread();

  static void Trampoline();

  static const std::string PID_FILE;

  static Config config_;

  static std::vector<std::thread> threads_;

  static bool is_opened_;
};

enum {
  CHILD_NEED_TERMINATE,
  CHILD_NEED_WORK,
};

static void signal_error(int sig, siginfo_t *si, void *ptr) {
  Logger::Log((StringBuilder() << "[DAEMON] Signal: %s, Addr: 0x%0.16X\n" << strsignal(sig)).Get());
  exit(CHILD_NEED_WORK);
}

}


#endif //WEB_SERVER_DAEMONTOOLS_H

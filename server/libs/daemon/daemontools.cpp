//
// Created by Alexey A. Ponomarev on 05.03.19.
//

#include "daemontools.h"
#include <string.h>

namespace Daemon {

void DaemonTools::Trampoline() {
  Logger::Log("[DAEMON] Scheduler start.", DAEMON);
  auto connection = Connection(config_.Get("Port"));
  std::vector<int> pipes;
  for (size_t i = 0; i < config_.Get("ThreadCount"); ++i) {
    int fds[2];
    pipe(fds);
    threads_.emplace_back(Connection::Handle, fds[0], &connection);
    pipes.push_back(fds[1]);
  }

  connection.Accept(pipes);
  Logger::Log("[DAEMON] Scheduler stop.", DAEMON);

  for (int p : pipes) {
    int closed = -1;
    write(p, &closed, sizeof(closed));

    close(p);
  }
}

void DaemonTools::InitWorkThread() {
  threads_.emplace_back(Trampoline);
}

void DaemonTools::DestroyWorkThread() {
  is_opened_ = false;
  for (size_t i = 0; i < 1 + config_.Get("ThreadCount"); ++i) {
    threads_[i].join();
  }
}

void DaemonTools::StartDaemon(const Config& cfg) {
  pid_t pid = fork();

  if (pid == -1) {
    throw std::runtime_error((StringBuilder() << "Error: Start Daemon failed (" << strerror(errno) << ").").Get());
  } else if (pid == 0) {
    config_ = cfg;

    Logger::SetLoggingLevel(config_.Get("LoggingLevel"));

    umask(0);
    setsid();
    chdir("/");

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    DaemonTools::MonitorProc();
  }
}

void DaemonTools::StopDaemon() {
  FILE* ptrFile = fopen(PID_FILE.c_str(), "r");

  pid_t pid;
  if (ptrFile != NULL) {
    fscanf(ptrFile, "%u", &pid);
    kill(pid, SIGTERM);
    fclose(ptrFile);
  } else {
    throw std::runtime_error("[DAEMON] No active daemons");
  }
}

int DaemonTools::WorkProc(int FD_LIMIT = 1024) {
  struct sigaction sigact;
  sigset_t sigset;
  int signo, status;

  sigact.sa_flags = SA_SIGINFO;
  sigact.sa_sigaction = signal_error;

  sigemptyset(&sigact.sa_mask);

  sigaction(SIGFPE, &sigact, 0); // FPU error
  sigaction(SIGILL, &sigact, 0); // instruction error
  sigaction(SIGSEGV, &sigact, 0); // error access to memory
  sigaction(SIGBUS, &sigact, 0); // physical memory error access

  sigemptyset(&sigset);

  sigaddset(&sigset, SIGQUIT);
  sigaddset(&sigset, SIGINT);
  sigaddset(&sigset, SIGTERM);
  sigaddset(&sigset, SIGUSR1);

  sigprocmask(SIG_BLOCK, &sigset, NULL);

  // Set max FD_Limit
  Config::SetFdLimit(FD_LIMIT);

  // Log about daemon starting
  Logger::Log("[DAEMON] Started\n", DAEMON);

  DaemonTools::InitWorkThread();

  while (true) {
    // wait for selected messages
    sigwait(&sigset, &signo);

    // Need to reload config
    if (signo == SIGUSR1) {
      // reload config
      // ReloadConfig();
    } else { // аny other signal stop
      break;
    }
  }
  // stop all working threads
  DaemonTools::DestroyWorkThread();

  Logger::Log("[DAEMON] Stopped\n", DAEMON);

  // Need to terminate
  return CHILD_NEED_TERMINATE;
}


void DaemonTools::MonitorProc() {
  int pid, status, need_start = 1;
  sigset_t sigset;
  siginfo_t siginfo;

  sigemptyset(&sigset);
  sigaddset(&sigset, SIGQUIT);
  sigaddset(&sigset, SIGINT);
  sigaddset(&sigset, SIGTERM);
  sigaddset(&sigset, SIGCHLD);
  sigaddset(&sigset, SIGUSR1);

  sigprocmask(SIG_BLOCK, &sigset, NULL);

  UpdatePidFile();
  while (true) {
    if (need_start) pid = fork();
    need_start = 1;

    if (pid == -1) {
      Logger::Log((StringBuilder() << "[MONITOR] Fork failed (" << strerror(errno) << ")\n").Get(), MONITOR);
    } else if (!pid) {
      status = WorkProc();
      exit(status);
    } else {
      sigwait(&sigset, NULL);

      if (siginfo.si_signo == SIGCHLD) {
        wait(&status);
        status = WEXITSTATUS(status);

        if (status == CHILD_NEED_TERMINATE) {
          Logger::Log("[MONITOR] Child stopped\n", MONITOR);
          break;
        } else if (status == CHILD_NEED_WORK) {
          Logger::Log("[MONITOR] Child restart\n", MONITOR);
        }
      } else if (siginfo.si_signo == SIGUSR1) {
        kill(pid, SIGUSR1);
        need_start = 0;
      } else {
        Logger::Log((StringBuilder() << "[MONITOR] Signal " << strsignal(siginfo.si_signo) << "\n").Get(), MONITOR);
        kill(pid, SIGTERM);
        status = 0;
        break;
      }
    }
  }

  Logger::Log("[MONITOR] Stop\n", MONITOR);
  unlink(PID_FILE.c_str());
}

void DaemonTools::UpdatePidFile() {
  FILE* ptrFile = fopen(PID_FILE.c_str(), "w+");

  if (ptrFile != NULL) {
    fprintf(ptrFile, "%u", getpid());
    fclose(ptrFile);
  } else {
    Logger::Log("[DAEMON] Failed to open PID_FILE\n", DAEMON);
  }
}

const std::string DaemonTools::PID_FILE = "/var/run/web_server.pid";

std::vector<std::thread> DaemonTools::threads_;

bool DaemonTools::is_opened_ = true;

Config DaemonTools::config_;


}
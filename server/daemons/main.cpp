#include <server/libs/connection/connection.h>
#include <server/libs/daemon/daemontools.h>
#include <utils/sys/cmdparser.h>
#include <utils/sys/helpers.h>
#include <server/libs/daemon/config.h>

#include <iostream>

int main(int argc, char* argv[])
{
    CmdParser cmd = CmdParser(argc, argv)
      .AddOption("exec", {"start", "restart", "stop", "info"}, REQUIRED_ARG);

    try {
      if (cmd.Get("exec") == "start") {
        Daemon::Config cfg = Daemon::Config::LoadConfig("config.cfg");
        Daemon::DaemonTools::StartDaemon(cfg);
      } else if (cmd.Get("exec") == "stop") {
        Daemon::DaemonTools::StopDaemon();
      } else if (cmd.Get("exec") == "restart") {
        Daemon::DaemonTools::StopDaemon();
        Daemon::Config cfg = Daemon::Config::LoadConfig("config.cfg");
        Daemon::DaemonTools::StartDaemon(cfg);
      } else if (cmd.Get("exec") == "info") {
        UNREACHABLE();
      }
    } catch (const std::exception &ex) {
      std::cerr << ex.what() << std::endl;
    }

    return 0;
};

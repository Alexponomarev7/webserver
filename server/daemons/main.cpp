#include <server/libs/connection/connection.h>
#include <server/libs/daemon/daemontools.h>

int main(int argc, char* argv[])
{
    Config cfg = Config::LoadConfig();

    try {
        DaemonTools::StartDaemon();
    } catch (const std::exception &ex) {
        std::cerr << ex.what() << std::endl;
    }
    return 0;
};

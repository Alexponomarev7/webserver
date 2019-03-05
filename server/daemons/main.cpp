#include <server/libs/connection/connection.h>


int main(int argc, char* argv[])
{
    auto conn = Connection();
    conn.BindPort(8080);
    conn.Handle();

    return 0;
};

#include <server/libs/connection/connection.h>
 
const char* response =
"HTTP/1.1 200 OK\r\n"
"Content-Type: text/html; charset=UTF-8\r\n\r\n"
"<doctype !html>\n"
"    <html>\n"
"        <head>\n"
"            <title>Bye-bye baby bye-bye</title>\n"
"            <style>body { background-color: #111 }\n"
"                   h1 { font-size:4cm; text-align: center; color: black;\n"
"                        text-shadow: 0 0 2mm red}\n"
"            </style>\n"
"        </head>\n"
"<body>\n"
"        <h1>Goodbye, world!</h1>\n"
"</body>\n"
"</html>\r\n";
 
int main(int argc, char* argv[])
{
    auto conn = Connection();
    conn.BindPort(8080);
    conn.Handle();

    return 0;
};

//
// Created by Alexey A. Ponomarev on 05.03.19.
//

#include "testlib.h"

Response SimpleResponse() {
    auto simple_response = Response();
    simple_response.SetVersion("HTTP/1.1");
    simple_response.SetStatusCode("200");
    simple_response.SetReasonPhrase("OK");

    simple_response.SetHeadAttr("Content-Type", "text/html; charset=UTF-8");

    simple_response.SetBody("<doctype !html>\n"
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
                            "</html>\n");
    return simple_response;
}
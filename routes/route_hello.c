#include <microhttpd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "katz/katz.h"

// GET handler for the /hello route
int hello_get_handler(struct MHD_Connection *connection) {
    const char *response_str = "Hello, World!\n";
    return katz_send_response(connection, MHD_HTTP_OK, response_str);
}

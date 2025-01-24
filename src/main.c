#include "katz/katz.h"
#include <unistd.h>

int main() {
    if (!katz_init("../config/config.json")) {
        return 1;
    }

    katz_start();

    while (1) {
        sleep(1);
    }

    katz_stop();
    katz_cleanup();
    return 0;
}
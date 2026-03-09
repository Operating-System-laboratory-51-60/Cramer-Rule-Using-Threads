#ifndef SYS_UTILS_H
#define SYS_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include "logger.h"

int get_cpu_cores() {
    FILE *fp = popen("lscpu | grep '^CPU(s):' | awk '{print $2}'", "r");
    if (!fp) {
        log_msg("[Warning] lscpu failed. Defaulting to 1 core.\n");
        return 1;
    }
    
    int cores = 1;
    if (fscanf(fp, "%d", &cores) != 1) {
        cores = 1;
    }
    pclose(fp);
    
    return (cores > 0) ? cores : 1;
}

#endif

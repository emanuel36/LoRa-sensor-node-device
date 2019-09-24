#ifndef MAX44009_H
#define	MAX44009_H

#include <stdint.h>
#include <stdbool.h>
#include "../../inc/MCC Drivers/i2c.h"

bool max44009Setup();
bool max44009Read(float *lux);

#define MAX44009_ADDR       0x94
#define CONFIG_REGISTER     0x02 
#define DEFAULT_CONFIG      0x00
#define REQUEST_COMMAND     0x03

#endif	/* MAX44009_H */


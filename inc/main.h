#ifndef MAIN_H
#define	MAIN_H

#include <stdbool.h>

bool systemStatus;
enum system_status {NORMAL = 0, WARNING} status;

bool getSystemStatus();
void setSystemStatus(bool state);


#endif	/* MAIN_H */


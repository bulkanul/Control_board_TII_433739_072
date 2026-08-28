#ifndef HARDWARE_H
#define HARDWARE_H

#include "global.h"

#include <stdbool.h>
bool is_alarm_ALARM (void);
bool is_alarm_emergency (void);
bool is_alarm_keylock (void);
bool is_alarm_interlock1 (void);
bool is_alarm_interlock2 (void);
bool is_alarm_QBH(void);
void set_pd_level_value(int id, float value);
#endif // HARDWARE_H

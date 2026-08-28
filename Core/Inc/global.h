#ifndef GLOBAL_DEF
#define GLOBAL_DEF

#include "main.h"
#include "stdio.h"
#include "string.h"
#ifndef TB_DEF
#include "params_func.h"
#endif

#include "setting_project.h"
#if HPLD_1500_COUNT > 0
#include "../../board_prj_driver_lib/drivers/HPLD_1500.h"
#endif
#if HPLD_1000_COUNT > 0
#include "../../board_prj_driver_lib/drivers/HPLD_1000.h"
#endif
#include "leds.h"

#include <assert.h>

#ifdef DEBUG_ENABLE 
	#if DEBUG_MESSAGE_FORMAT == 0
	#define debug_message(flag,buf,...) \
		do{if(flag){sprintf(buf,__VA_ARGS__); \
		debug_mess(buf);} }while(0)
	#elif DEBUG_MESSAGE_FORMAT == 1
		#define debug_message(flag,buf,...) \
		do{if(flag){printf(__VA_ARGS__);} }while(0)
	#endif 
#else
	#define debug_message(buf,...)
#endif


#ifdef DELAY_CAN_ENABLE
	#define DELAY_CAN_DEVICE(time) osDelay(time)
#else
	#define DELAY_CAN_DEVICE(TIME)
#endif

#pragma pack(push, 1)
typedef union alarms_u {
	struct {
		uint32_t keylock : 1;
		uint32_t emergency : 1;
		uint32_t alarm : 1;
		uint32_t qbh : 1;
		uint32_t interlock1 : 1;
		uint32_t interlock2 : 1;
		uint32_t overheat : 1;
		uint32_t reserved : 25;
	} bits;
	uint32_t val;
} alarms_t;
#pragma pack(pop)
static_assert(sizeof(alarms_t) == 4, "alarms_t must be exactly 4 bytes!");

typedef struct {
	uint32_t   ip [4];
	uint32_t   mac[6];

	int        therm_resi;
	int        therm_beta;
	float      v_ref;

	float      temperature_lvl             [THERMISTOR_COUNT];
	float      alarm_pd_lvl                [ALARM_PD_COUNT];

#if HPLD_1000_COUNT > 0
	float      hpld1000_curr               [HPLD_1000_COUNT];
#endif
#if HPLD_1500_COUNT > 0
	float      hpld1500_curr               [HPLD_1500_COUNT];
#endif
}
config_struct;

typedef struct
{
	int   output_started;
	float temperature[THERMISTOR_COUNT];
	float photo[4];
	float photo_diff;
}
user_mode_struct;

typedef struct {
	int                                         current_interface;

	config_struct                               config;
	user_mode_struct                            user_mode;

#if HPLD_1500_COUNT > 0
	hpld_1500_t      	                        hpld_1500			[HPLD_1500_COUNT];
#endif
#if HPLD_1000_COUNT > 0
	hpld_1000_struct   	                        hpld_1000			[HPLD_1000_COUNT];
#endif

	leds_t                                      leds;
	alarms_t                                    alarms;
}
device_struct;

extern QueueHandle_t send_can_mess_queue;

#endif

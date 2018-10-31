/*
 * Kedacom Hardware Abstract Level
 *
 * brd_hwmon.h
 *
 * Copyright (C) 2013-2020, Kedacom, Inc.
 *
 * History:
 *   2013/09/22 - [xuliqin] Create
 *
 */

#ifndef _BRD_MONITOR_H
#define _BRD_MONITOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <drvlib_def.h>

#ifndef USE_KLSP_DEFINES

/*
 * Hardware monitor definition
 * use u32 type variable
 *   D[31:16]: hwmon type
 *   D[ 7: 0]: index for each hwmon type
 */
#define HWMON_NO_SHIFT          0
#define HWMON_NO_MASK           0xff
#define HWMON_NO(v)             (((v) >> HWMON_NO_SHIFT) & HWMON_NO_MASK)

#define HWMON_TYPE_SHIFT        16
#define HWMON_TYPE_MASK         0xffff
#define HWMON_TYPE(v)           (((v) >> HWMON_TYPE_SHIFT) & HWMON_TYPE_MASK)

#define HWMON_ID(type, no) \
        (((type) << HWMON_TYPE_SHIFT) | \
         ((no)   << HWMON_NO_SHIFT))

#define HWMON_TYPE_LINE_IN      0 /* line input  on/off */
#define HWMON_TYPE_LINE_OUT     1 /* line output on/off */
#define HWMON_TYPE_FAN_SPEED    2 /* fan speed */
#define HWMON_TYPE_TEMP         3 /* temperature */
#define HWMON_TYPE_VOLT         4 /* voltage */
#define HWMON_TYPE_BRIGHT       5 /* brightness */

#define HWMON_ID_FAN_SPEED(n)   HWMON_ID(HWMON_TYPE_FAN_SPEED, n)
#define HWMON_ID_TEMP(n)        HWMON_ID(HWMON_TYPE_TEMP, n)
#define HWMON_ID_VOLT(n)        HWMON_ID(HWMON_TYPE_VOLT, n)

#endif /* USE_KLSP_DEFINES */

/* fan info: globle <struct fan_info board_fans[CFG_FAN_NUM];> */
typedef struct
{
	u32   dwCab;        /* see also: FAN_CAB_SPEED_SET */
	u32   dwSpeedMax;  /*  rotate speed, in RPM or 0-100(%) */
	u32   dwSpeedCur;  /* cuttent rotate speed, in RPM or 0-100(%) */
	u32   dwSpeedAlarm;/* if (speed_cur < speed_alarm) report alarm */
} TFanInfo;

/* temperature info */
typedef struct
{
	s32   dwCur;        /* cuttent temperature, in 0.001 degree C */
	s32   dwAlarmMin;  /* if (cur < alarm_min) report alarm */
	s32   dwAlarmMax;  /* if (cur > alarm_max) report alarm */
} TTempInfo;

/* voltage info */
typedef struct
{
	s32   dwCur;        /* cuttent voltage, in mVolt */
	s32   dwAlarmMin;  /* if (cur < alarm_min) report alarm */
	s32   dwAlarmMax;  /* if (cur > alarm_max) report alarm */
} TVoltInfo;

/* brightness info */
typedef struct {
        u32   dwCur;        /* cuttent brightness, in LM */
        u32   dwAlarmMin;  /* if (cur < alarm_min) report alarm */
        u32   dwAlarmMax;  /* if (cur > alarm_max) report alarm */
}TBrightInfo;

typedef struct
{
	u32   dwNo;    /* Input: 0 ~ hwmon_num-1 */

	u32   dwId;    /* see also: HWMON_ID_TEMP */
	char  achName[NAME_MAX_LEN]; /* hwmon obj name */
} THwmonInfo;

typedef struct
{
	u32   dwId;    /* see also: HWMON_ID_TEMP */
	int   nAlarm; /* hwmon state: 0 = normal; 1 = alarm on */

	union
	{
		u8 abyParam[256];
		TFanInfo    tFan;
		TTempInfo   tTemp;
		TVoltInfo   tVolt;
		TBrightInfo tBright;
	} tEntry;           /* append param for each HWMON_TYPE(id) */
} THwmonStat;

int BrdHwmonQueryInfo(THwmonInfo *ptInfo);
int BrdHwmonGetStatus(THwmonStat *ptStat);
int BrdHwmonSetStatus(THwmonStat *ptStat);

#ifdef __cplusplus
}
#endif

#endif

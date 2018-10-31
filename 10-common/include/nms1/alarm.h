#ifndef NMS_ALARM_H_
#define NMS_ALARM_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include "nmsmacro.h"

#define ALARM_VALUE_MAX_LEN         (s32)16
//�澯
class CAlarm : public CObject
{
public:
    u32	    m_dwDeviceID;           // �豸���
    u32	    m_dwAlarmCode;          // �澯��
    TCHAR   m_szAlarmValue[ALARM_VALUE_MAX_LEN];    //�澯ֵ
    TCHAR   m_szGenTime[TIME_LEN];  // �澯����ʱ��
    TCHAR   m_szResTime[TIME_LEN];  // �澯�ָ�ʱ��
    bool    m_bIsChecked;
    u8      m_byAlarmType;          // �²����ĸ澯/�澯�ָ�
    u8      m_byObjectTypeId;       // �澯��������Id

public:
    CAlarm() : m_dwDeviceID(0), m_dwAlarmCode(0), m_bIsChecked(false),
               m_byAlarmType(0), m_byObjectTypeId(0)
	{
        ZeroMemory( m_szAlarmValue, sizeof (m_szAlarmValue) );
        ZeroMemory( m_szGenTime,    sizeof (m_szGenTime) );
        ZeroMemory( m_szResTime,    sizeof (m_szResTime) );
	};

    CAlarm(const CAlarm &cAlarm) : m_dwDeviceID(cAlarm.m_dwDeviceID),
                                   m_dwAlarmCode(cAlarm.m_dwAlarmCode),
                                   m_bIsChecked(cAlarm.m_bIsChecked),
                                   m_byAlarmType(cAlarm.m_byAlarmType),
                                   m_byObjectTypeId(cAlarm.m_byObjectTypeId)
    {
		_tcsncpy( m_szAlarmValue, cAlarm.m_szAlarmValue,
                  sizeof (m_szAlarmValue) - 1 );
        _tcsncpy( m_szGenTime, cAlarm.m_szGenTime, sizeof (m_szGenTime) - 1 );
        m_szAlarmValue[sizeof (m_szAlarmValue) - 1] = 0;
        m_szGenTime[sizeof (m_szGenTime) - 1] = 0;
		//  ԭ�д�����û�и��ָ�ʱ�丳ֵ
    };

public:
	CAlarm & operator= (const CAlarm &cAlarm)
	{
        if ( this == &cAlarm )  //  wanghao 2005/11/03 ��ֹ�Ը�ֵ
        {
            return (*this);
        }

		m_dwDeviceID        = cAlarm.m_dwDeviceID;
		m_dwAlarmCode       = cAlarm.m_dwAlarmCode;
		_tcsncpy( m_szAlarmValue, cAlarm.m_szAlarmValue,
                  sizeof (m_szAlarmValue) - 1 );
        _tcsncpy( m_szGenTime, cAlarm.m_szGenTime, sizeof (m_szGenTime) - 1 );
        m_szAlarmValue[sizeof (m_szAlarmValue) - 1] = 0;
        m_szGenTime[sizeof (m_szGenTime) - 1] = 0;
		//  ԭ�д�����û�и��ָ�ʱ�丳ֵ
		m_bIsChecked        = cAlarm.m_bIsChecked;
        m_byAlarmType       = cAlarm.m_byAlarmType;
		m_byObjectTypeId    = cAlarm.m_byObjectTypeId;

		return (*this);
	}

	void Dump() const
	{
		OspLog( APPLICATION,
                "AlarmType = %d, EquipmentType = %d, DeviceID = %d, AlarmValue = %s, AlarmCode = %d, alarmTime = %s ",
                m_byAlarmType, m_byObjectTypeId, m_dwDeviceID, m_szAlarmValue,
                m_dwAlarmCode, m_szGenTime );
	}

    void Dump1() const
    {
		OspPrintf( TRUE, FALSE,
                   "AlarmType = %d, EquipmentType = %d, DeviceID = %d, AlarmValue = %s, AlarmCode = %d, alarmTime = %s ",
                   m_byAlarmType, m_byObjectTypeId, m_dwDeviceID,
                   m_szAlarmValue, m_dwAlarmCode, m_szGenTime );
    }

    /*=============================================================================
    �� �� ��:Print
    ��    ��:���ݴ�ӡ
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/03/30  4.0     ���    ����
    =============================================================================*/
    void Print(void) const
    {
        ::OspPrintf( TRUE, FALSE, "AlarmType = %d, ObjType = %d, DeviceID = %d, \
Value = %s\nAlarmCode = %d, GenTime = %s, ResTime = %s\n", m_byAlarmType,
                     m_byObjectTypeId, m_dwDeviceID, m_szAlarmValue,
                     m_dwAlarmCode, m_szGenTime, m_szResTime );
    }
};

typedef CTypedPtrList<CObList, CAlarm *> CAlarmList;//Alarm�б�

#endif
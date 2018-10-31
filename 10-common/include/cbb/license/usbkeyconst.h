/*=======================================================================
ģ����      :
�ļ���      : usbkeyconst.h
����ļ�    :
�ļ�ʵ�ֹ��� : usbkey�����궨��
����        : ���ƶ�
�汾        : KCMV1.0  Copyright(C) 2003-2008 Suzhou Keda Technology Co.Ltd
                    All rights reserved.
--------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2007/01/11  KCM1.0      ���ƶ�      ����
=======================================================================*/
#ifndef _USBKEYCONST_H
#define _USBKEYCONST_H


// License����

#define KEDA_AES_KEY						(LPCSTR)"kedacom200606231"			// ��֤16λ
#define KEDA_COPYRIGHT						(LPCSTR)"Suzhou Keda Technology Co.,ltd. Tel:86-512-68418188, Fax: 86-512-68412699, http://www.kedacom.com"

// �������ݵĳ���
#define LEN_KEYFILE_CONT					(u16)512

#define MAXLEN_USBKEY_NAME					(u16)512

//ȱʡ����Ȩ�� ��klms.kedacom.com����md5�������32λ�����
#define DEFAULT_MCULICENSE_AUTHCODE			(LPCSTR)"b2ae4e5afc3619dae447fd23dc0605b2"
#define USB_PATH							(LPCSTR)"USBKEY"					// дUSB��־
#define KEY_VALUE_SEPARETE					(LPCSTR)"&"							// Key-Value�Էָ���
#define KEY_VALUE_CONNECTOR					(LPCSTR)"="							// Key-Value���ӷ�

#define KEY_DESCRIPTION_FILE				(LPCSTR)"USBKey.ini"				// Keyֵ�����ļ�
#define KEY_TYPE_KEY						(LPCSTR)"TYPE"						// Keyֵ������
#define VALUE_MIN							(LPCSTR)"MIN"						// ��ֵ����Сֵ
#define VALUE_MAX							(LPCSTR)"MAX"						// ��ֵ�����ֵ
#define STRING_LENGTH						(LPCSTR)"LENGTH"					// �ַ�������󳤶�
#define ENUM_NUM							(LPCSTR)"ITEMNUM"					// ѡ���͸�����
#define ENUM_ITEM							(LPCSTR)"ITEM"						// ѡ���͸���
#define DATE_OUT_DATE						(LPCSTR)"MAX"						// �������

#define ERROR_CODE_DESCRIPTION_FILE			(LPCSTR)"licenseError.ini"		// �����������ļ�
#define ERROR_SEGMENT						(LPCSTR)"ERRORCODE"					// ���������

#define ENCRPT_LENGTH						(LPCSTR)"ENCRPT_LENGTH"				// ��Ϣ����

// ������ ////////////////////////////////////////////////////////////////
#define SUCCESS_LICENSE						(u16)0                      // �ɹ�
#define ERR_LICENSE_AUTH_FAILED				(u16)1                      // ��Ȩ����֤ʧ��
#define ERR_LICENSE_FORMAT_FAILED			(u16)2                      // ��Ϣ��ʽ����
#define ERR_LICENSE_NO_VER_FAILED			(u16)3                      // �ް汾��Ϣ
#define ERR_LICENSE_DEV_INFO_FAILED			(u16)4                      // �豸��Ϣ��ȫ
#define ERR_LICENSE_ENCRYPT_FAILED			(u16)5                      // ����ʧ��
#define ERR_LICENSE_WRITEKEY_FAILED			(u16)6                      // дlicense�ļ�ʧ��
#define ERR_LICENSE_SMALL_VALUE				(u16)7                      // ��ֵС������
#define ERR_LICENSE_BIG_VALUE				(u16)8                      // ��ֵ��������
#define ERR_LICENSE_LONG_STRING				(u16)9                      // �ַ������ȴ�������
#define ERR_LICENSE_NO_ITEM_ENUM			(u16)10                     // û�д�ѡ��
#define ERR_LICENSE_OUT_DATE				(u16)11                     // ���ڳ�������
#define ERR_LICENSE_NO_KEY					(u16)12                     // ��֧�ִ�KEYֵ
#define ERR_LICENSE_READ_CFG_FAIL			(u16)13                     // �������ļ�ʧ��
#define ERR_LICENSE_INVALID_PARAM			(u16)14                     // �����Ƿ�
#define ERR_LICENSE_NO_KEY_TYPE				(u16)15                     // ��֧�ִ�����
#define ERR_LICENSE_NO_USB_KEY				(u16)16                     // ��USBKEY
#define ERR_LICENSE_USB_CONNECT_FAIL		(u16)17                     // ����USB�豸ʧ��
#define ERR_LICENSE_USB_GET_FAIL			(u16)18                     // ��ռUSB�豸ʧ��
#define ERR_LICENSE_OPENFILE_FAILED			(u16)19                     // ���ļ�����
#define ERR_LICENSE_INVALID_USBKEY			(u16)20                     // License�ļ���USB�豸����
#define ERR_LICENSE_USB_FORMAT_FAIL			(u16)21                     // ��ʽ��USB�豸ʧ��
#define ERR_LICENSE_USB_VERY_PASSWORD		(u16)22                     // У��USB�豸����ʧ��
#define ERR_LICENSE_USB_CREATE_FILE_FAIL	(u16)23                     // USB�豸�����ļ�ʧ��
#define ERR_LICENSE_USB_OPEN_FILE_FAIL		(u16)24                     // USB�豸���ļ�ʧ��
#define ERR_LICENSE_USB_DELETE_FILE_FAIL	(u16)25                     // USB�豸�����ļ�ʧ��
#define ERR_LICENSE_READKEY_FAILED			(u16)26                     // ��license�ļ�ʧ��
#define ERR_LICENSE_TOO_MANY_CHAR           (u16)27                     // ��Ȩ��Ϣ����
#define ERR_LICENSE_UNKNOWN					(u16)1000                   // ����ԭ��Ĵ���
//////////////////////////////////////////////////////////////////////////

// �����KEYֵ ///////////////////////////////////////////////////////////
#define KEY_LICENSE_FILE_PATH				(LPCSTR)"KEY_LICENSE_FILE_PATH"		// дLicense�ļ�·��
#define KEY_LICENSE_KEY						(LPCSTR)"KEY_LICENSE_KEY"			// ���֤����(36λUUID)
//////////////////////////////////////////////////////////////////////////

#endif // _USBKEYCONST_H

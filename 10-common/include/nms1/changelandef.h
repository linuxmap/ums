#ifndef CHANGELANDEF_050909_H
#define CHANGELANDEF_050909_H

#define LANGTYPE_CHN                _T("chinese")
#define LANGTYPE_ENG                _T("english")

//////////////////////////////////////////////////////////////////////////
//error code
#define LANGUAGE_NOERROR            (u16)0
#define LANGUAGE_ERRORBASE          (u16)500
#define LANGUAGE_NOCREATE           (LANGUAGE_ERRORBASE + 1)   //δ����
#define LANGUAGE_ALOCMEM            (LANGUAGE_ERRORBASE + 2)   //�����ڴ����
#define LANGUAGE_OPENFILE           (LANGUAGE_ERRORBASE + 3)   //�ļ������ڻ�򿪴���
#define LANGUAGE_FILESIZE           (LANGUAGE_ERRORBASE + 4)   //�ļ�����Ϊ��
#define LANGUAGE_XMLOBJCREATE       (LANGUAGE_ERRORBASE + 5)   //XML���󴴽�����
#define LANGUAGE_XMLNODECREATE      (LANGUAGE_ERRORBASE + 6)   //XML�ڵ㴴������
#define LANGUAGE_NOTEXISTLANG       (LANGUAGE_ERRORBASE + 7)   //�����ڵ���������
#define LANGUAGE_ILLEGALPARAM       (LANGUAGE_ERRORBASE + 8)   //��������
#define LANGUAGE_NOCURRENTLAN       (LANGUAGE_ERRORBASE + 9)   //û���趨��ǰ����

//////////////////////////////////////////////////////////////////////////
//window type & ignore type
#define STYLE_IGNORETRANS           (0x00000001L)
#define STYLE_LISTCTRL              (0x00000002L)
#define STYLE_COMBOBOX              (0x00000004L)
#define STYLE_TREE                  (0x00000008L)
#define STYLE_TABTRL                (0x00000010L)
#define STYLE_CUSTOM                (0x80000000L)


//////////////////////////////////////////////////////////////////////////
//message
#define NOTIFY_MSG_CHANGLAN         (WM_USER + 11)
#define SENDMSG_MODE_ALL            (0x01)
#define SENDMSG_MODE_IGNORE         (0x02)
#endif
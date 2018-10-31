/*****************************************************************************
ģ����      : DcMtLib
�ļ���      : DcMtLibMacro.h
����ļ�    : 
�ļ�ʵ�ֹ���: DcMtLib�궨��
����		: chenhongbin
�汾        : V1.0
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾     �޸���             �޸�����
2005/05/26  1.0      chenhongbin         ����
******************************************************************************/
#ifndef _DCMTLIBMACRO_H
#define _DCMTLIBMACRO_H




#define ERR_DCMT_BGN    0
//�����ɹ�
#define DCMTLIB_OP_SUCCESS                     ERR_DCMT_BGN//26501
//��ʼ��ʧ��
#define ERR_DCMTLIB_INITIAL_FAIL               ERR_DCMT_BGN + 1
//���ܿ��Ѿ���ʼ��
#define ERR_DCMTLIB_ALWAYS_INIT                ERR_DCMT_BGN + 2
//���ܿ�����ʼ��
#define ERR_DCMTLIB_MUST_INIT                  ERR_DCMT_BGN + 3
//�ն��Ѿ��ڻ�����
#define ERR_DCMTLIB_ALWAYS_INCONF              ERR_DCMT_BGN + 4
//�ն˱����ڻ�����
#define ERR_DCMTLIB_MUST_INCONF                ERR_DCMT_BGN + 5
//��������
#define ERR_INVALID_PARAMETER                  ERR_DCMT_BGN + 6

//���칦���Ѿ�����
#define ERR_DCMTLIB_CHAT_ALWAYS_START          ERR_DCMT_BGN + 10
//���칦�ܱ��뿪��
#define ERR_DCMTLIB_CHAT_MUST_START            ERR_DCMT_BGN + 11
//���������
#define ERR_DCMTLIB_CHAT_NO_PARTICIPANT        ERR_DCMT_BGN + 12

//�ļ����书���Ѿ�����
#define ERR_DCMTLIB_MBFT_ALWAYS_START          ERR_DCMT_BGN + 20
//�ļ����书�ܱ��뿪��
#define ERR_DCMTLIB_MBFT_MUST_START            ERR_DCMT_BGN + 21
//���ļ��������
#define ERR_DCMTLIB_MBFT_NO_PARTICIPANT        ERR_DCMT_BGN + 22
//���ڷ����ļ�
#define ERR_DCMTLIB_MBFT_ALWAYS_SENDINGFILE    ERR_DCMT_BGN + 23
//��ǰ��δ�����ļ�
#define ERR_DCMTLIB_MBFT_NOT_SENDINGFILE       ERR_DCMT_BGN + 24
//�����ļ�ʧ��
#define ERR_DCMTLIB_MBFT_SENDFILE_FAIL         ERR_DCMT_BGN + 25

//�װ幦���Ѿ�����
#define ERR_DCMTLIB_SI_ALWAYS_START            ERR_DCMT_BGN + 30
//�װ幦�ܱ��뿪��
#define ERR_DCMTLIB_SI_MUST_START              ERR_DCMT_BGN + 31

//Ӧ�ù�������������δ�ɹ�
#define ERR_DCMTLIB_APPSHARE_CAPNEGOTIA        ERR_DCMT_BGN + 35


#endif//_DCMTLIBMACRO_H

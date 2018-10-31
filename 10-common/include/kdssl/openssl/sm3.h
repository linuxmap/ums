/*=================================================================================
  ģ����    ��SM3 ʵ��
  �ļ���    ��sm3.h
  ����ļ�  ����
  ʵ�ֹ���  ��sm3 ����
  ����      �������
  ��Ȩ��<Copyright(c) 2016-2016 Suzhou Keda Technology Co.,Ltd.All rights reserved.>
  --------------------------------------------------------------------------------
  �޸ļ�¼ :    �� ��        �� ��      �޸���  �߶���      �޸ļ�¼
                2016/11/04   V1.0       �����              �½�
==================================================================================*/

#ifndef HEADER_SM3_H
# define HEADER_SM3_H

#define SM3_DIGEST_LENGTH       32
#define SM3_BLOCK_SIZE          64

#include <sys/types.h>
#include <stdint.h>
#include <string.h>

# ifdef __cplusplus
extern "C" {
# endif


typedef struct sm3_ctx_st {
    uint32_t digest[8];                  /** V(i) �м������ */
    int nblocks;                         /** ����Ŀ���, ���������Լ128G (2^^31 * 64) */
    unsigned char block[64];             /** ������� */
    int num;                             /** ĩ�����ݳ���  n % 64 */
} sm3_ctx_t;

void sm3_init(sm3_ctx_t *ctx);
void sm3_update(sm3_ctx_t *ctx, const unsigned char* data, size_t data_len);
void sm3_final(sm3_ctx_t *ctx, unsigned char digest[SM3_DIGEST_LENGTH]);
void sm3(const unsigned char *data, size_t datalen, unsigned char digest[SM3_DIGEST_LENGTH]);


# ifdef __cplusplus
}
# endif
#endif /** HEADER_SM3_H */


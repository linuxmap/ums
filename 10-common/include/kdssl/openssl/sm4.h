/*=================================================================================
  ģ����    ��SM4 ʵ��
  �ļ���    ��sm4.h
  ����ļ�  ����
  ʵ�ֹ���  ��sm4 ����
  ����      �������
  ��Ȩ��<Copyright(c) 2016-2016 Suzhou Keda Technology Co.,Ltd.All rights reserved.>
  --------------------------------------------------------------------------------
  �޸ļ�¼ :    �� ��        �� ��      �޸���  �߶���      �޸ļ�¼
                2016/10/09   V1.0       �����              �½�
==================================================================================*/

#ifndef HEADER_SM4_H
#define HEADER_SM4_H

#define SM4_KEY_LENGTH      16
#define SM4_BLOCK_SIZE      16
#define SM4_IV_LENGTH       (SM4_BLOCK_SIZE)
#define SM4_NUM_ROUNDS      32

#include <sys/types.h>
#include <stdint.h>
#include <string.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	uint32_t rk[SM4_NUM_ROUNDS];
} sm4_key_t;

void sm4_set_encrypt_key(sm4_key_t *key, const unsigned char *user_key);
void sm4_set_decrypt_key(sm4_key_t *key, const unsigned char *user_key);
void sm4_encrypt(const unsigned char *in, unsigned char *out, const sm4_key_t *key);
#define sm4_decrypt(in,out,key)  sm4_encrypt(in,out,key)

void sm4_ecb_encrypt(const unsigned char *in, unsigned char *out,
	const sm4_key_t *key, int enc);
void sm4_cbc_encrypt(const unsigned char *in, unsigned char *out,
	size_t len, const sm4_key_t *key, unsigned char *iv, int enc);
void sm4_ctr128_encrypt(const unsigned char *in, unsigned char *out,
	size_t len, const sm4_key_t *key, unsigned char *iv,
	unsigned char ecount_buf[SM4_BLOCK_SIZE], unsigned int *num);
void sm4_ofb128_encrypt(const unsigned char *in, unsigned char *out,
                        size_t length, const sm4_key_t *key,
                        unsigned char *ivec, int *num);
#ifdef __cplusplus
}
#endif
#endif


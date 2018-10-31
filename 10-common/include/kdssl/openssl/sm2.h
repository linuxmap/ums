/*=================================================================================
  ģ����    ��SM2 ����
  �ļ���    ��sm2.h
  ����ļ�  ����
  ʵ�ֹ���  ��sm2 ����
  ����      �����ǿ�
  ��Ȩ��<Copyright(c) 2016-2016 Suzhou Keda Technology Co.,Ltd.All rights reserved.>
  --------------------------------------------------------------------------------
  �޸ļ�¼ :    �� ��        �� ��      �޸���  �߶���      �޸ļ�¼
                2017/8/17   V1.0        ���ǿ�              �½�
==================================================================================*/

#ifndef HEADER_SM2_H
# define HEADER_SM2_H

#define SM2_DIGEST_LENGTH       32
#define SM2_BLOCK_SIZE          64

#include <openssl/evp.h>

# ifdef __cplusplus
extern "C" {
# endif

typedef struct SM2Cipher_st SM2Cipher;


SM2Cipher *SM2Cipher_new(void);
void SM2Cipher_free(SM2Cipher *cipher);

SM2Cipher *d2i_SM2Cipher(SM2Cipher**cipher, const unsigned char **pp, long len);
int i2d_SM2Cipher(const SM2Cipher *cipher, unsigned char **pp);

void SM2Cipher_get0(const SM2Cipher *cipher,
                    const BIGNUM **pXCoordinate,
                    const BIGNUM **pYCoordinate,
                    const ASN1_OCTET_STRING **pHASH,
                    const ASN1_OCTET_STRING **pCipherText);

int SM2Cipher_set0(SM2Cipher *cipher,
                    BIGNUM *XCoordinate,
                    BIGNUM *YCoordinate,
                    ASN1_OCTET_STRING *HASH,
                    ASN1_OCTET_STRING *CipherText);


int sm2_ecdh(EVP_PKEY *cert_key_A, EVP_PKEY *tmp_key_A,
             EVP_PKEY *cert_key_B, EVP_PKEY *tmp_key_B,
             void *outkey, size_t keylen, int is_initiator); 

# ifdef __cplusplus
}
# endif
#endif /** HEADER_SM2_H */


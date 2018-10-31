/*! \file libipconf.h
    \brief �ṩIP��ͻ���֧��

    IP��ͻ���ģ�������ϲ�Ӧ��ͨ��API���ü��IP��ͻ��ʱ�佫��,�����⵽����IP��ͻ
    ���ϲ�Ӧ�����õĻص������ᱻ����.

    ��Ȩ���� 2007 kedacom \n
    �汾: 1.0 \n
    ��ʷ:  \n
      - ��ʼ�汾.     ��Ԫһ(070601)

    \author ��Ԫһ
    \date 2007-6-01
*/

/** @defgroup ipconf IP��ͻ���
    �ṩIP��ͻ���֧��<br><br>
    <b>��ʾ������������:</b>
    - <b>start interval</b> <br>
    ����IP��ͻ���, intervalΪ���ʱ����,�������IP��ͻ,�򽫴�ӡ������Ϣ:
    "MAC��ַΪ XX:XX:XX:XX:XX:XX �Ļ�����������������ͬ��IP��ַ: X.X.X.X",
    �����ӡ"���������."
    - <b>stop</b><br>
    ֹͣIP��ͻ���,���������IP��ͻ,���ӡ:"û�м�⵽IP��ַ��ͻ�ṩIP��ͻ���API֧��",
    �����ӡ:"�����ֹͣ."
    - <b>help</b><br>
    ��ʾ������Ϣ
    - <b>exit</b><br>
    �˳���ʾ����
 *  @{
 */

#ifndef IPCONFLICT_H
#define IPCONFLICT_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * �ص�����
 *
 * \param mac_addr     ������ͻ��������MAC��ַ
 * \param addr         ������ͻ��IP��ַ.
 * \return �޷���ֵ
 */
typedef void(*ipconf_func)(const u_char* mac_addr, const struct in_addr* addr);

/**
 * ��ʼIP��ͻ���
 *
 * \param user_func    ������ͻʱ�Ļص�����
 * \return ����ɹ�����0, ʧ�ܷ���-1.
 */
extern s32 ipconf_start(ipconf_func func,int tval);

/**
 * ֹͣIP��ͻ���
 *
 * \return ����ɹ�����0, ʧ�ܷ���-1
 */
extern s32 ipconf_stop(void);

#ifdef __cplusplus
}
#endif

/* @} */

#endif /* IPCONFLICT_H */


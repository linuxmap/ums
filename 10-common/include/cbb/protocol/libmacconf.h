/*! \file libmacconf.h
    \brief �ṩMAC��ͻ���֧��

    MAC��ͻ���ģ�������ϲ�Ӧ��ͨ��API����,�����⵽����MAC��ͻ
    ���ϲ�Ӧ�����õĻص������ᱻ����.

    ��Ȩ���� 2008 kedacom \n
    �汾: 1.0 \n
    ��ʷ:  \n
      - ��ʼ�汾.     ��᷹�(080108)

    \author ��᷹�
    \date 2008-01-08
*/

/** @defgroup macconf MAC��ͻ���
    �ṩMAC��ͻ���֧��<br><br>
    <b>��ʾ������������:</b>
    - <b>start</b> <br>
    ����MAC��ͻ���,�������MAC��ͻ,�򽫴�ӡ������Ϣ:
    "IP��ַΪ X.X.X.X �Ļ�����������������ͬ��MAC��ַ: XX:XX:XX:XX:XX:XX ",
    �����ӡ"���������."
    - <b>stop</b><br>
    ֹͣMAC��ͻ���,���������MAC��ͻ,
    �����ӡ:"�����ֹͣ."
    - <b>help</b><br>
    ��ʾ������Ϣ
    - <b>exit</b><br>
    �˳���ʾ����
 *  @{
 */

#ifndef MACCONFLICT_H
#define MACCONFLICT_H

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
typedef void(*macconf_func)(const u_char* mac_addr, const struct in_addr* addr,const char *local);

/**
 * ��ʼMAC��ͻ���
 *
 * \param user_func    ������ͻʱ�Ļص�����
 * \return ����ɹ�����0, ʧ�ܷ���-1.
 */
extern s32 macconf_start(macconf_func user_func);

/**
 * ֹͣMAC��ͻ���
 *
 * \return ����ɹ�����0, ʧ�ܷ���-1
 */
extern s32 macconf_stop(void);

#ifdef __cplusplus
}
#endif

/* @} */

#endif /* MACCONFLICT_H */


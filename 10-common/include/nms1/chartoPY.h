/*---------------------------------------------------------------------
* ��	����CCharToPY
* ��    �ܣ�����תƴ��
* ����˵�������ڻ�ȡ���ֵ�ƴ������ĸ
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2012/12/05	v1.0		Ф��Ȼ		����
----------------------------------------------------------------------*/

#if !defined(AFX_CHARTOPY_H__B2F2F86E_CDB6_4CD0_A359_06334B8FC32A__INCLUDED_)
#define AFX_CHARTOPY_H__B2F2F86E_CDB6_4CD0_A359_06334B8FC32A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCharToPY  
{
public:
	CCharToPY();
	virtual ~CCharToPY();

    /**
    * ����:	���ַ���ת��Ϊƴ������ĸ
	* @param [in]  strName �ַ���
    * @param [out]  strFirstLetter ƴ��
	* @return  ��
	* @remarks
	*/
    static void GetFirstLetter(CString strName, CString& strFirstLetter);

    static BOOL In(int Lp, int Hp,int Value);
    char GetPYChar(CString HZ) ;

    /**
    * ����:	��һ������ת��Ϊƴ������ĸ
	* @param [in]  c1��c2 ���ֵ������ַ�
	* @return  �ú��ֵ�ƴ��
	* @remarks
	*/
    static char GetPYChar(TCHAR c1,TCHAR c2); 

    //��������ƴ����
    static CString m_ArrQWSecond[32];   //��λ����ĸͷ: 56��~87����Ӧ0~30
};

#endif // !defined(AFX_CHARTOPY_H__B2F2F86E_CDB6_4CD0_A359_06334B8FC32A__INCLUDED_)

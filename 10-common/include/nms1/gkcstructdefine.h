/*****************************************************************************
ģ����      : GkcTestStruct
�ļ���      : GkcTestStruct.h
����ļ�    : GkcTestStruct.cpp
              
�ļ�ʵ�ֹ���: �������GkConsoleʹ�õ����ݽṹ
����        : �º��
ģ��汾    : V4.0  Copyright(C) 2002-2005 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��(n/m/d)      �ļ��汾        �޸���      �޸�����
2005/08/10         0.1            �º��      ����
******************************************************************************/
#ifndef GKCSTRUDEFINE_H_2005_08_10
#define GKCSTRUDEFINE_H_2005_08_10


//Ϊ���ϲ㷽��ʹ��,��װʵ����֤����(��ʽ)�Ĳ���
class CGkAuthMothod
{
public:
    CGkAuthMothod()
    {
        m_dwGkAuthMothod = 0;
    };
public:
    //������֤���Ե�32λֵ
    void SetAuthMethod(u32 dwGkAuthMothod)
    {
        m_dwGkAuthMothod = dwGkAuthMothod;
    }

    //��ȡ��֤���Ե�32λֵ
    u32 GetAuthMethod() const
    {
        return m_dwGkAuthMothod;
    }

    //���ò���Ҫ��֤
    void SetNotAuth()
    {
        m_dwGkAuthMothod = 0;
    };
    
    //�Ƿ���Ҫ��֤
    bool IsNeedAuth() const
    {
        if(m_dwGkAuthMothod & emAuthMethod_AuthIPAllow
            || m_dwGkAuthMothod & emAuthMethod_AuthIPForbid
            || m_dwGkAuthMothod & emAuthMethod_AuthAliasAllow
            || m_dwGkAuthMothod & emAuthMethod_AuthAliasForbid
            || m_dwGkAuthMothod & emAuthMethod_AuthPassword
            )
        {
            return true;
        }
        else
        {
            return false;
        }
    };
    
    //����ip��֤������Ч
    void SetAuthIPAllow()
    {
        m_dwGkAuthMothod &= ~emAuthMethod_AuthIPForbid;
        m_dwGkAuthMothod |= emAuthMethod_AuthIPAllow;       
    };

    //����ip��֤��ֹ��Ч
    void SetAuthIPForbid()
    {
        m_dwGkAuthMothod &= ~emAuthMethod_AuthIPAllow;
        m_dwGkAuthMothod |= emAuthMethod_AuthIPForbid;
    };
    
    //�Ƿ�ip��֤������Ч
    bool IsAuthIPAllow() const
    {
        if(m_dwGkAuthMothod & emAuthMethod_AuthIPAllow) 
        {
            return true;
        }
        else
        {
            return false;
        }
    };

    //�Ƿ�ip��֤��ֹ��Ч
    bool IsAuthIPForbid() const
    {
        if(m_dwGkAuthMothod & emAuthMethod_AuthIPForbid) 
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    //����ʵ����֤������Ч
    void SetAuthAliasAllow()
    {
        m_dwGkAuthMothod &= ~emAuthMethod_AuthAliasForbid;
        m_dwGkAuthMothod |= emAuthMethod_AuthAliasAllow;       
    };

    //����ʵ����֤��ֹ��Ч
    void SetAuthAliasForbid()
    {
        m_dwGkAuthMothod &= ~emAuthMethod_AuthAliasAllow;
        m_dwGkAuthMothod |= emAuthMethod_AuthAliasForbid;
    };
    
    //�Ƿ�ʵ����֤������Ч
    bool IsAuthAliasAllow() const
    {
        if(m_dwGkAuthMothod & emAuthMethod_AuthAliasAllow) 
        {
            return true;
        }
        else
        {
            return false;
        }
    };

    //�Ƿ�ʵ����֤��ֹ��Ч
    bool IsAuthAliasForbid() const
    {
        if(m_dwGkAuthMothod & emAuthMethod_AuthAliasForbid) 
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    //����������֤
    void SetAuthPassword()
    {
        m_dwGkAuthMothod |= emAuthMethod_AuthPassword;
    };
 
    //�Ƿ�������֤
    bool IsAuthPassword() const
    {
        if(m_dwGkAuthMothod & emAuthMethod_AuthPassword) 
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
private:
    u32 m_dwGkAuthMothod; //��֤����32λֵ
};





#endif //GKCSTRUDEFINE_H_2005_08_10
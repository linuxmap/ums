/*****************************************************************************
ģ����      : ����ؼ���
�ļ���      : UILibHead.h
����ļ�    : UITools.cpp
              CheckButton.cpp
              FlatButton.cpp
              SkinButton.cpp
              SkinEdit.cpp
              SkinComboBox.cpp
              SkinHeadCtrl.cpp
              SkinListCtrl.cpp
              SkinIPCtrl.cpp
              SkinMenu.cpp
              SkinScroll.cpp
              SkinSliderCtrl.cpp
              StaticEx.cpp
              SkinFrame.cpp
              FlatDDButton.cpp
              SkinDDListCtrl.cpp
              TextButton30.cpp
              SkinGroup.cpp
              SkinTab.cpp
              SkinPage.cpp
              SkinSheet.cpp
              SkinCheckList.cpp
�ļ�ʵ�ֹ���: ����windows��׼�ؼ�
����        : ������
�汾        : V1.0  Copyright(C) 1997-2004 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2004/03/24  1.0         ������      ����
2004/07/20  1.0         ������      ���������б���ť��
2004/07/21  1.0         ������      ����Text30��
2004/07/30  1.0         ������      ����Group��
2004/08/31  1.0         ������      ����Tab,Sheet,Pageϵ�С�
2004/09/20  1.0         ������      ����CheckListBox��
2005/03/28  1.0         ������      ����FlatButtonͼƬʱ��������ʾ��
2005/03/28  1.0         ������      �����������пؼ��ľ�̬��ɫ���á�
******************************************************************************/

#ifndef __UILIBHEAD_H
#define __UILIBHEAD_H

#if _MSC_VER > 1000
#pragma once
#endif

#include <afxtempl.h>
#include <afxole.h>
#include <afxdtctl.h>

//list����Ƚ�
typedef int (CALLBACK *PFNNEWCOMPARE)(LPARAM, LPARAM, LPARAM, LPARAM);


#define USESKINSCROLL

//ToolTip��ʾʱ�䣬����
#define TOOLTIP_SHOWTIME            (int)10000

//UI������  
class CUITools
{
public:
	CUITools();
	~CUITools();
    enum{STEPBK_VERT = 0, STEPBK_HORZ}; //����ɫ�ķ��� DrawStepBk��
public:
    /*====================================================================
    ������	��    CreateImage
    ����		������BMP��Դ�ŵõ�ͼƬ���
    �㷨ʵ��	������ѡ�
    ����ȫ�ֱ�������
    �������˵����nBitmap ͼƬ��Դ��
    ����ֵ˵����  ͼƬ��������ɹ�ΪNULL��
    ====================================================================*/
    static HBITMAP CreateImage(UINT nBitmap);

    /*====================================================================
    ������	��    DrawStepBk
    ����		��������ɫ
    �㷨ʵ��	������ɫ������ɫ�任���ٶȣ�Ȼ�����ÿ�ε���ɫ��Ϊ�����Ч��
                    ÿ�λ������ص���
    ����ȫ�ֱ�������
    �������˵����pDC ��ͼ��CDCָ��
                  crFrom ��ʼ����ɫ�������棨������ߣ�����ɫ��
                  crTo ��������ɫ�������棨�����ұߣ�����ɫ��
                  rcAll  ������ɫ�������������Χ��
                  rcItem ʵ�ʵ���ͼ������
                  nStyle ����ķ���STEPBK_VERT�����ϵ��£�STEPBK_HORZ�������ҡ�
    ����ֵ˵����  ��
    ====================================================================*/
    static void DrawStepBk(CDC *pDC, COLORREF crFrom, COLORREF crTo, CRect rcAll, CRect rcItem=CRect(0,0,0,0), UINT nStyle=STEPBK_VERT);
protected:
	
private:
};

//һЩ������

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//    CDropInfo  ���ڴ���������Ϣ����                                   //
//////////////////////////////////////////////////////////////////////////
class CDropInfo : public CObject
{
public:
	CDropInfo();
	CDropInfo(COleDataObject* pDataObject,DWORD dwKeyState,
		DROPEFFECT dropEffect,DROPEFFECT dropEffectList,CPoint point );
	virtual ~CDropInfo();

public:
	//CDDTarget member functions params
	COleDataObject* m_pDataObject;
	DWORD m_dwKeyState;
	DROPEFFECT m_dropEffect;
	DROPEFFECT m_dropEffectList;
	CPoint m_point;

	DECLARE_DYNAMIC( CDropInfo );
};

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// CDDTarget �̳�����Ŀ�����                                              //
// //////////////////////////////////////////////////////////////////////////
class CDDTarget : public COleDropTarget
{
public:
	BOOL MyRegist(CWnd* pWnd);
	CDDTarget();
	virtual ~CDDTarget();
    
protected:
    //����OnDropEx��Ϣ�Ǳ���ģ�����OnDrop�������ᱻִ��
    //��ȻҲ������OnDropEx�����д�������
	virtual DROPEFFECT OnDragEnter(CWnd* pWnd, COleDataObject* pDataObject,
		DWORD dwKeyState, CPoint point);
	virtual DROPEFFECT OnDragOver(CWnd* pWnd, COleDataObject* pDataObject,
		DWORD dwKeyState, CPoint point);
	virtual BOOL OnDrop(CWnd* pWnd, COleDataObject* pDataObject,
        DROPEFFECT dropEffect, CPoint point);
	virtual DROPEFFECT OnDropEx(CWnd* pWnd, COleDataObject* pDataObject,
		DROPEFFECT dropEffect, DROPEFFECT dropEffectList, CPoint point);
	virtual void OnDragLeave(CWnd* pWnd);
};



//�Ի��Ĺ�������
class CSkinScroll : public CStatic
{
// Construction
public:
	CSkinScroll();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinScroll)
    virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	void Set3DShow(BOOL bShow3D);
    //��̬��ɫ����  [zhuyr][3/28/2005]
    static void StaticSetChannelBk(COLORREF crBkFrom, COLORREF crBkTo=-1);
    static void StaticSetThumbColor(COLORREF crBk, COLORREF crFrame=-1);
    static void StaticSetArrowColor(COLORREF crFk, COLORREF crBk);

	void ReInit();
	UINT GetOldShowState();
	BOOL UpdateThumbSize();
	void SetShowAllways(BOOL bAllWays = TRUE);
	void UpdateRect();
	void ShowScroll(BOOL bShow = FALSE, BOOL bShowOld = FALSE);
	void SetChannelBk(COLORREF crBkFrom, COLORREF crBkTo=-1, BOOL bRepaint = FALSE);
	void SetThumbColor(COLORREF crBk, COLORREF crFrame=-1, BOOL bRepaint = FALSE);
	void SetArrowColor(COLORREF crFk, COLORREF crBk, BOOL bRepaint = FALSE);
	BOOL InitScrollBar(CWnd* pCtrl, UINT nStyle);
	void UpdateThumbPosition();
	virtual ~CSkinScroll();

	// Generated message map functions
protected:
	BOOL m_bShow3D; 
	BOOL m_bShowAllways;
	BOOL m_bOnce;
	int m_nLineWidth;
	int m_nThumbMetric;
	CRect m_rcFirstArrow;
    CRect m_rcLastArrow;
    CRect m_rcChannel;
    CRect m_rcThumb;
    
  
    BOOL m_bOldShow;
    BOOL m_bMouseDown;
	BOOL m_bLeftUp;
	BOOL m_bRightDown;
    BOOL m_bLeftUpPage;
    BOOL m_bRightDownPage;
	double m_dbThumbInterval;
	UINT m_nItemMetric;
	CWnd* m_pCtrl;
	UINT m_nScrollStyle;

    COLORREF m_crArrowFk;
    COLORREF m_crArrowBk;
    COLORREF m_crThumbBk;
    COLORREF m_crThumbFrame;
    COLORREF m_crChannelBk[2];

    //��̬��ɫ����  [zhuyr][3/28/2005]
    static COLORREF m_s_crArrowFk;
    static COLORREF m_s_crArrowBk;
    static COLORREF m_s_crThumbBk;
    static COLORREF m_s_crThumbFrame;
    static COLORREF m_s_crChannelBk[2];
    
	int m_nOldMax;
	int m_nPointInThumb;
	int m_nLenth;

	BOOL IsStopPage();
	void CreateArrowRgn(CRgn& rgnFirst, CRgn& rgnLast);
	void DrawArrow(CDC* pDC, int nStyle, CRect rect);
	void DrawThumb();
	void SendScrollMessage(UINT nMessageType, int nTime = 1);
	void LimitThumbPosition();
	//{{AFX_MSG(CSkinScroll)
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

//�˵�����Ϣ��
class CMenuItem
{
private:
    wchar_t *m_szMenuText;
    wchar_t *m_szHotItem;
public:
	CMenuItem(LPCSTR strText=NULL,HBITMAP hBitmap=NULL,HICON hIcon=NULL)
	{
        m_szMenuText = NULL;
        SetAnsiString(strText);
		m_hBitmap = hBitmap;
		m_hIcon   = hIcon;
        m_szHotItem = NULL;
        m_nFlags = 0;
        m_nID = -1;

        m_nWidth = 120;
        m_nHeight = 20;
	}
    virtual ~CMenuItem();
    CString GetString();
public:
	CString GetHotString();
	void SetHotString(const wchar_t *szHotString);
	void SetHotString(LPCSTR szHotString);
	void SetAnsiString(LPCSTR szAnsiString);
	void SetWideString(const wchar_t *szWideString);
    UINT        m_nFlags;
    UINT        m_nID;
    HBITMAP     m_hBitmap;
	HICON	    m_hIcon;
	int 	    m_nWidth;		
	int	        m_nHeight;
    CImageList* m_pImaList;
    int         m_nImage;
};


//�б�ͷ
class CSkinHeaderCtrl : public CHeaderCtrl
{
// Construction
public:
	CSkinHeaderCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinHeaderCtrl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDS);
// Implementation
public:
	void Set3DShow(BOOL bShow3D);
	void SetDivideColor(COLORREF crDivide, int npenStyle = PS_SOLID, BOOL bRepaint = FALSE);
	void SetFrameColor(COLORREF crFrame, BOOL bRepaint = FALSE);
	CString GetItemText(int nItem) const;
	void SetSortArrow(int nSortCol, BOOL bSortAscending);
	void SetBkColor(COLORREF crBk, BOOL bRepaint = TRUE);
	void SetTextColor(COLORREF crText, BOOL bRepaint = TRUE);
	virtual ~CSkinHeaderCtrl();

    //  [zhuyr][3/29/2005]
    static void staticSetColors(COLORREF crText, COLORREF crBk, COLORREF crFrame = -1);
	// Generated message map functions
protected:
	void DrawArrow(CDC* pDC, CRect rect);
	BOOL m_bSortAscending;
	BOOL m_bShow3D;  
	UINT m_nSortCol;
    COLORREF m_crText;
	COLORREF m_crBk;
    COLORREF m_crFrame;
    CPen     m_penDivide;
    
    //��̬��ɫ����  [zhuyr][3/29/2005]
    static COLORREF m_s_crText;
    static COLORREF m_s_crBk;
    static COLORREF m_s_crFrame;
	//{{AFX_MSG(CSkinHeaderCtrl)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
//
//      ������Ϣ��
//////////////////////////////////////////////////////////////////////////

class CDragDropMsg
{
public:
    CDragDropMsg();
private:
    static UINT     m_nStartMsgID;
public:
#define MSG_BEGINDRAG       0
#define MSG_DRAGENTER       1
#define MSG_DRAGOVER        2
#define MSG_DROP            3
#define MSG_DROPEX          4
#define MSG_DRAGLEAVE       5
    static void SetStartMsgID(UINT nStartMsgID);
    static UINT GetStartMsgID();
    static BOOL HasSetMsgID();
    static UINT GetDDMsgID(UINT nMsgType);
};


/************************************************************************/
/*   �˵�                                                               */
/************************************************************************/
class CSkinMenu : public CMenu  
{
    DECLARE_DYNAMIC(CSkinMenu)
public:
	BOOL CreatePopupMenu();
	BOOL InsertMenu(UINT nPosition, UINT nFlags, UINT nID, LPCTSTR lpstrText=NULL);
	int GetMenuString(UINT nIDItem, CString& rString, UINT nFlag = MF_BYPOSITION);
	int GetMenuString(UINT nIDItem, char** rString, UINT nSize, UINT nFlag = MF_BYPOSITION);
    void SetMenuString(UINT nIDItem, LPCSTR lpString, UINT nFlag = MF_BYPOSITION);
	LRESULT OnSkinMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu);
	void SetBkColor(COLORREF crFrom, COLORREF crTo, COLORREF crHilight = -1);
	void SetTextColor(COLORREF crText, COLORREF crHilight ,COLORREF crDisable = -1);


	BOOL LoadMenu(UINT uMenuID);
	BOOL LoadMenu(LPCTSTR lpszResourceName);
	BOOL InsertMenu(UINT nPosition, UINT nFlags, UINT nID, wchar_t *lpstrText, CImageList *il=NULL,int xoffset=0);
	BOOL AppendMenu(UINT nFlags, UINT nIDNewItem, LPCSTR lpszNewItem, UINT nIDBitmap=NULL,HICON hIcon=NULL);
	BOOL DeleteMenu(UINT nPosition, UINT nFlags);
    
	static BOOL IsMenu(HMENU hMenu);

	CSize GetMenuSize();
	CSkinMenu* FindMenuOption(int nID, int& nLoc);
	BOOL AppendODMenuW(wchar_t *lpstrText,UINT nFlags = MF_OWNERDRAW,UINT nID = 0,int nIconNormal = -1);
	BOOL AppendODMenuW(wchar_t *lpstrText,UINT nFlags,UINT nID, CImageList *il,int xoffset);
	void InsertSpaces();
	CSkinMenu();
	virtual ~CSkinMenu();

	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMIS);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);
	virtual BOOL DestroyMenu();

    /*=============================================================================
    �� �� ��:SetFont
    ��    ��:���ò˵���������
    ��    ��:CFont *pcFont              [in]    ����
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/11/08  4.0     ���    ����
    =============================================================================*/
    inline void SetFont(CFont *pcFont) { m_pcFont = pcFont; }

public:
    enum {TYPE_NORMAL = 0, TYPE_NMC};
    static int m_s_nType;
    static COLORREF m_s_crBk[3]; //0:From; 1:To; 2:Hilight
    static COLORREF m_s_crText[3];//0:Normal; 1:Hilight; 2:Disable
protected:
    void DrawItemText(CDC* pDC, COLORREF crText, CRect rect, CMenuItem* pItem);
	void DrawCheckMark(CDC* pDC,int x,int y,COLORREF color);
protected:
	BOOL m_bLoadMenu;
	COLORREF m_crBk[3];
    COLORREF m_crText[3];

    static CTypedPtrArray<CPtrArray, HMENU>  m_AllSubMenus;
    CTypedPtrArray<CPtrArray,CMenuItem *> m_MenuList;
    CTypedPtrArray<CPtrArray, HMENU> m_SubMenus;
    int			m_curSel;

    int m_nWidth;
    int m_nHeigth;

    CFont   *m_pcFont;
};


/*******************************************************************
������CFlatButton
���ܣ�ƽ��Ч����ť���趨������ɫ������ͼ����豳��ɫ��
*********************************************************************/
class CFlatButton : public CButton
{
    DECLARE_DYNAMIC(CFlatButton)
// Construction
public:
	CFlatButton();

    //��ť���
    static UINT m_s_nType;
    enum {TYPE_NORMAL = 0, TYPE_NMC};

    //ͼƬ������λ�ã����涨��λ������ʾλ��һ��  [zhuyr][3/28/2005]
    enum enTextPos {TEXT_POS_LEFTTOP,     TEXT_POS_TOP,       TEXT_POS_RIGHTTOP,
                    TEXT_POS_LEFT,        TEXT_POS_CENTER,    TEXT_POS_RIGHT,
                    TEXT_POS_LEFTBOTTOM,  TEXT_POS_BOTTOM,    TEXT_POS_RIGHTBOTTOM,
                    TEXT_POS_CUSTOM};
// �ӿ�
public:
    /*====================================================================
    ������  ��SetBitmaps
    ��  ��  ���趨��ť��ͼƬ
    ȫ�ֱ�������
    ���������nBitmapNormal: ��ť����״̬ʱ����ťͼƬ����Դ�š�
              nBitmapOver:   ��ť�������ʱ����ťͼƬ����Դ�š�
	          nBitmapDown:   ��ť������ʱ����ťͼƬ����Դ�š�
	          hBitmapDisable:��ťʧЧʱ����ťͼƬ����Դ�š�  (��ΪͼƬ���)
    ����ֵ  ����
    ====================================================================*/
	void SetBitmaps(UINT nBitmapNormal, UINT nBitmapOver = 0, UINT nBitmapDown = 0, UINT nBitmapDisable = 0);
	void SetBitmaps(HBITMAP hBitmapNormal, HBITMAP hBitmapOver = NULL, HBITMAP hBitmapDown = NULL, HBITMAP hBitmapDisable = NULL);
    
    /*====================================================================
    ������  ��SizeToContent
    ��  ��  ���趨��ť��ͼƬ��С����Ӧ��ϵ��
    ȫ�ֱ�������
    ���������bActivate:TRUEʱ��ť��ӦͼƬ��FALSEͼƬ��Ӧ��ť��
    ����ֵ  ����
    ====================================================================*/
	void SizeToContent(BOOL bEnable = TRUE);


    /*====================================================================
    ������  ��SetBkColor
    ��  ��  ���趨��ť��������ɫ
    ȫ�ֱ�������
    ���������crBkOut	��겻�ڰ�ť��ʱ����ť��������ɫ��
	          crBkIn	����ڰ�ť��ʱ����ť��������ɫ��
    	      crBkDown	��ť������ʱ����ť��������ɫ��
	          crBkDisable	��ťʧЧʱ����ť��������ɫ��
              bRepaint	����ֵΪTRUEʱ����ť�����ػ�������ֵΪFALSEʱ����ť���´�ˢ��ʱ�ػ���
    ����ֵ  ����
    ====================================================================*/
   	void SetBkColor(COLORREF crBkOut, COLORREF crBkIn, COLORREF crBkDown, COLORREF crBkDisable = -1, BOOL bRepaint = TRUE);
   	static void staticSetBkColor(COLORREF crBkOut, COLORREF crBkIn, 
        COLORREF crBkDown, COLORREF crBkDisable = -1);

    /*====================================================================
    ������  ��SetFrameColor
    ��  ��  ���趨��ť�߿����ɫ
    ȫ�ֱ�������
    ���������crFrameOut	��겻�ڰ�ť��ʱ����ť�߿����ɫ��
	          crFrameIn	����ڰ�ť��ʱ����ť�߿����ɫ��
    	      crFrameDown	��ť������ʱ����ť�߿����ɫ��
	          crFrameDisable	��ťʧЧʱ����ť�߿����ɫ��
              bRepaint	����ֵΪTRUEʱ����ť�����ػ�������ֵΪFALSEʱ����ť���´�ˢ��ʱ�ػ���
    ����ֵ  ����
    ====================================================================*/   
	void SetFrameColor(COLORREF crFrameOut, COLORREF crFrameIn, COLORREF crFrameDown, COLORREF crFrameDisable, BOOL bRepaint = TRUE);
	static void staticSetFrameColor(COLORREF crFrameOut, COLORREF crFrameIn, 
        COLORREF crFrameDown, COLORREF crFrameDisable);

    /*====================================================================
    ������  ��SetTextColor
    ��  ��  ���趨��ť�ı�����ɫ
    ȫ�ֱ�������
    ���������crTextOut	��겻�ڰ�ť��ʱ����ť�ı�����ɫ��
	          crTextIn	����ڰ�ť��ʱ����ť�ı�����ɫ��
    	      crTextDown	��ť������ʱ����ť�ı�����ɫ��
	          crTextDisable	��ťʧЧʱ����ť�ı�����ɫ��
              bRepaint	����ֵΪTRUEʱ����ť�����ػ�������ֵΪFALSEʱ����ť���´�ˢ��ʱ�ػ���
    ����ֵ  ����
    ====================================================================*/  
 	void SetTextColor(COLORREF crTextOut, COLORREF crTextIn, COLORREF crTextDown, COLORREF crTextDisable = -1, BOOL bRepaint = TRUE);
 	static void staticSetTextColor(COLORREF crTextOut, COLORREF crTextIn, 
        COLORREF crTextDown, COLORREF crTextDisable = -1);
   
    /*====================================================================
    ������  ��SetMenuEx
    ��  ��  ���趨�˵���ť��
    ȫ�ֱ�������
    ���������nMenu: �˵�����ԴID�š�
              hParentWnd: �����ھ�������ղ˵�Commad��Ϣ��
              bRepaint	����ֵΪTRUEʱ����ť�����ػ�������ֵΪFALSEʱ����ť���´�ˢ��ʱ�ػ���
    ����ֵ  ����
    ====================================================================*/
	void SetMenuEx(UINT nMenu, HWND hParentWnd, BOOL bRepaint = FALSE);

    /*====================================================================
    ������  ��SetMenuCallBack
    ��  ��  ���趨�˵��ص���Ϣ��
    ȫ�ֱ�������
    ���������hWnd:     ��Ϣ�����ߵľ����
              nMessage: ��Ϣ��ID�š�
              lParam:	���õĲ�����������Ϣ���ء�
    ����ֵ  ����
    ====================================================================*/
	void SetMenuCallBack(HWND hWnd, UINT nMessage, LPARAM lParam);

    
    /*====================================================================
    ������  ��EnableTooltipText
    ��  ��  ������Tooltip���ܡ�
    ȫ�ֱ�������
    ���������bActivate:�Ƿ�����Tooltip���ܡ�
    ����ֵ  ����
    ====================================================================*/
	void EnableTooltipText(BOOL bActivate = TRUE);

    /*====================================================================
    ������  ��SetTooltipText
    ��  ��  ������Tooltip�ı�
    ȫ�ֱ�������
    ���������lpszText: �ı����ݣ�
              bActivate:�Ƿ�����Tooltip���ܡ�
    ����ֵ  ����
    ====================================================================*/
	void SetTooltipText(UINT nText, BOOL bActivate = TRUE);
	void SetTooltipText(LPCTSTR lpszText, BOOL bActivate = TRUE);

    
    /*====================================================================
    ������  ��SetPressStyle
    ��  ��  ���趨��ť��ѹʱ����ť��ͼ��������ƶ��ķ���;��롣
    ȫ�ֱ�������
    ���������x: ˮƽ�����ϵ�λ�ơ�
              y: ��ֱ�����ϵ�λ�ơ�
    ����ֵ  ����
    ====================================================================*/
	void SetPressStyle(int x, int y);
	void SetPressStyle(CPoint ptPress);

    /*====================================================================
    ������  ��SetRectRound
    ��  ��  ���趨��ť��Բ�ǰ뾶��
    ȫ�ֱ�������
    ���������x: ˮƽ�����ϵ�Բ�ǰ뾶��
              y: ��ֱ�����ϵ�Բ�ǰ뾶��
    ����ֵ  ����
    ====================================================================*/
	void SetRectRound(int x, int y);
	void SetRectRound(CPoint ptRound);
    
    /*====================================================================
    ������	��    ShowFocus
    ����		���Ƿ���ʾ�����
    �㷨ʵ��	������ѡ�
    ����ȫ�ֱ�������
    �������˵����bShow���Ƿ���ʾ�ı�־��
    ����ֵ˵����  ��
    ====================================================================*/
	void ShowFocus(BOOL bShow);

    /*====================================================================
    ������	��    SetShowText
    ����		���Ƿ���ͼƬ��ť����ʾ��ť���⡣
    �㷨ʵ��	������ѡ�
    ����ȫ�ֱ�������
    �������˵����bShow���Ƿ���ʾ�ı�־��
                  TextPos: ������ʾ��λ�ã���Ҫ�õ�һ���ӿ���ΪTEXT_POS_CUSTOM����
                  ptPos:  ��ʾ����λ�õ����Ͻǣ��ڰ�ť�ϵ�λ�ã�TEXT_POS_CUSTOM����
    ����ֵ˵����  ��
    ====================================================================*/
    void SetShowText(BOOL bShow, enTextPos TextPos = TEXT_POS_CENTER);
    void SetShowText(BOOL bShow, CPoint ptPos);

    /*�������� SetTextPtOff
    ��    �ܣ���ͼƬ����ʾ���⣬ʹ��Ĭ��λ�ã�����ʱ���ĸ������������Ŀռ䡣 
    ��    ���� CRect rcOff
    �� �� ֵ�� 
    ˵    ���� ע�⣬������ʾ������С��������ʾ��������*/
    void SetTextPtOff(CRect rcOff);
    static void static_SetTextPtOff(RECT rcOff);
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlatButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDS);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PreSubclassWindow();
    virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	void DrawTextAtPt(CDC *pDC, RECT rect);
	virtual ~CFlatButton();

	// Generated message map functions
protected:
	void OnPopupMenu(CRect rect);
	void GetOwnRgn(CRect rect, CRgn& rgn);
	int GetCurState();
	void CancelHover();
	void DrawBitmap(CDC* pDC, RECT rect);
	void FreeResource();
	void DrawTexT(LPDRAWITEMSTRUCT lpDS);
	void InitTooltip();

    enum {STATE_OUT = 0, STATE_IN, STATE_DOWN, STATE_DISABLE, STATE_MAX};
    //����״̬��ͼƬ�������ɫ�� 
    HBITMAP  m_hBitmap[STATE_MAX];
    COLORREF m_crFrame[STATE_MAX];
    COLORREF m_crText[STATE_MAX];
    COLORREF m_crBk[STATE_MAX];
    COLORREF m_crRoundBk;

    //��̬��ɫ  [zhuyr][3/29/2005]
    static COLORREF m_s_crFrame[STATE_MAX];
    static COLORREF m_s_crText[STATE_MAX];
    static COLORREF m_s_crBk[STATE_MAX];
    static RECT     m_s_rcTextPtOff;

    BOOL m_bSizeToContent;     //��ť��ͼƬ��С��Ӧ��ϵ��TRUEʱΪ��ť��ӦͼƬ��

    COLORREF m_crFocus;  //��������ɫ��

    CToolTipCtrl m_ToolTip;

    //��ť״̬
    BOOL m_bDisable;
    BOOL m_bDown;
    BOOL m_bFocus;
    BOOL m_bMouseIn;

    BOOL m_bNeedFocus;

    CPoint m_ptRectRound;   //���ְ�ť��԰�ǵ����������ϵİ뾶��
    CPoint m_ptPressStyle;  //������ťʱͼƬ�������ƶ��ľ��롣
    CRect  m_rcTextPtOff;

    CSize m_sizeButton;
    CSize m_sizeBitmap;

    CBitmap m_bmpMask;

    BOOL m_bNeedFree;   //��Ҫ�ͷ�ͼƬ��Դ��

    //��ʾͼƬ��ť����  [zhuyr][3/28/2005]
    BOOL m_bShowText;
    enTextPos m_enPosType;
    CPoint    m_ptRealTextPos;

    //�˵���ر�����
//    HMENU		m_hMenu;
    CSkinMenu m_Menu;
    HWND m_hParentWndMenu;
	BOOL m_bMenuDisplayed;
	BOOL m_bChecked;


#pragma pack(1)
	typedef struct tagCallback
	{
		HWND		hWnd;			// Handle to window
		UINT		nMessage;		// Message identifier
		WPARAM		wParam;
		LPARAM		lParam;
	} TCallback;
#pragma pack()
    TCallback m_csCallbacks;
	//{{AFX_MSG(CFlatButton)
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnCancelMode();
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnClicked();
    afx_msg LRESULT OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu);
	//}}AFX_MSG
    afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
};

/*******************************************************************
������CFlatDDButton
���ܣ�ƽ��Ч����ť���࣬���ӽ����������ܡ�
*********************************************************************/
class CFlatDDButton : public CFlatButton  
{
public:
    
    /*====================================================================
    ������	��    SetReceiveMsgWnd
    ����		�����ý���������Ϣ�Ĵ��ڣ�Ĭ��Ϊ�丸���ڡ�
    �㷨ʵ��	������ѡ�
    ����ȫ�ֱ�������
    �������˵����
    ����ֵ˵����  ��
    ----------------------------------------------------------------------
    �޸ļ�¼:
    ��  ��		�汾		�޸���		�߶���    �޸�����
    2004/07/20	1.0			������                  ����
    ====================================================================*/
    void SetReceiveMsgWnd(HWND hRevMsgWnd = NULL);

	void Register();

	CFlatDDButton();
	virtual ~CFlatDDButton();
protected:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlatDDButton)
    virtual void PreSubclassWindow();
    virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
    virtual BOOL OnDrop(WPARAM pDropInfo, LPARAM lParam);
	virtual DROPEFFECT OnDropEx(WPARAM pDropInfo, LPARAM lParam);
	virtual DROPEFFECT OnDropOver(WPARAM pDropInfo, LPARAM lParam);

	//{{AFX_MSG(CSkinDDListCtrl)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

protected:
    CDDTarget   *m_pcDropTarget;      //��������
    HWND        m_hRevMsgWnd;
};


/*******************************************************************
������CCheckButton
���ܣ�Check, radio�ȵ�����
*********************************************************************/
class CCheckButton : public CButton
{
// Construction
public:
	CCheckButton();

// �ӿ�
public:
    /*====================================================================
    ������  ��SetBitmaps
    ��  ��  ���趨��ť��������ɫ
    ȫ�ֱ�������
    ���������n(h)BMPCheck:         ��ť��Ч��ѡ��ʱ����ťCheckͼƬ����Դ�ţ��������
              n(h)BMPUncheck:       ��ť��Ч��δѡ��ʱ����ťCheckͼƬ����Դ�ţ��������
	          n(h)BMPDisableCheck:  ��ťʧЧ��ѡ��ʱ����ťCheckͼƬ����Դ�ţ��������
	          n(h)BMPDisableUncheck:��ťʧЧ��δѡ��ʱ����ťCheckͼƬ����Դ�ţ��������
	          n(h)BMPHotCheck:  ��ť���������ѡ��ʱ����ťCheckͼƬ�ľ����
	          n(h)BMPHotUncheck:��ť���������δѡ��ʱ����ťCheckͼƬ�ľ����
	          n(h)BMPDownCheck:  ��갴����ѡ��ʱ����ťCheckͼƬ�ľ����
	          n(h)BMPDownUncheck:��갴����δѡ��ʱ����ťCheckͼƬ�ľ����
    ����ֵ  ����
    ====================================================================*/
	void SetBitmaps(UINT nBMPCheck, UINT nBMPUncheck, 
        UINT nBMPDisableCheck = 0, UINT nBMPDisableUncheck = 0,
        UINT nBMPHotCheck = 0, UINT nBMPHotUncheck = 0,
        UINT nBMPDownCheck = 0, UINT nBMPDownUncheck = 0);
	void SetBitmaps(HBITMAP hBMPCheck, HBITMAP hBMPUncheck, 
        HBITMAP hBMPDisableCheck = NULL, HBITMAP hBMPDisableUncheck = NULL,
        HBITMAP hBMPHotCheck = NULL, HBITMAP hBMPHotUncheck = NULL,
        HBITMAP hBMPDownCheck = NULL, HBITMAP hBMPDownUncheck = NULL);

    /*====================================================================
    ������  ��SetFrameSize
    ��  ��  ���趨Check��Ĵ�С
    ȫ�ֱ�������
    ���������nSize:Check��ı߳�����ֱ����Ĭ��Ϊ15��
    ����ֵ  ����
    ====================================================================*/
	void SetFrameSize(int nSize);
    
    /*====================================================================
    ������  ��SetFrameColor
    ��  ��  ���趨Check�����ɫ
    ȫ�ֱ�������
    ���������crFrame	��ť��Чʱ��Check�����ɫ��
	          crDisable	��ťʧЧʱ��Check�����ɫ��
              bRepaint	����ֵΪTRUEʱ����ť�����ػ�������ֵΪFALSEʱ����ť���´�ˢ��ʱ�ػ���
    ����ֵ  ����
    ====================================================================*/
	void SetFrameColor(COLORREF crFrame, COLORREF crDisable, BOOL bRepaint = FALSE);
    static void staticSetFrameColor(COLORREF crFrame, COLORREF crDisable);
    
    /*====================================================================
    ������  ��SetTextColor
    ��  ��  ���趨��ť��������ɫ
    ȫ�ֱ�������
    ���������crText	��ť��Чʱ����ť���ֵ���ɫ��
	          crDisable	��ťʧЧʱ����ť���ֵ���ɫ��
              bRepaint	����ֵΪTRUEʱ����ť�����ػ�������ֵΪFALSEʱ����ť���´�ˢ��ʱ�ػ���
    ����ֵ  ����
    ====================================================================*/
	void SetTextColor(COLORREF crText, COLORREF crDisable = -1, BOOL bRepaint = FALSE);
	static void staticSetTextColor(COLORREF crText, COLORREF crDisable = -1);

    /*====================================================================
    ������  ��SetCheckColor
    ��  ��  ���趨��ťѡ�б�ǵ���ɫ��С����Բ�㣩
    ȫ�ֱ�������
    ���������crCheck	��ť��Чʱ��ѡ�б�ǵ���ɫ��
	          crDisable	��ťʧЧʱ��ѡ�б�ǵ���ɫ��
              bRepaint	����ֵΪTRUEʱ����ť�����ػ�������ֵΪFALSEʱ����ť���´�ˢ��ʱ�ػ���
    ����ֵ  ����
    ====================================================================*/
	void SetCheckColor(COLORREF crCheck, COLORREF crDisable, BOOL bRepaint = FALSE);
	static void staticSetCheckColor(COLORREF crCheck, COLORREF crDisable);

    /*====================================================================
    ������  ��SetBkColor
    ��  ��  ���趨��ť��������ɫ
    ȫ�ֱ�������
    ���������crBk	��ť��������ɫ��
              bRepaint	����ֵΪTRUEʱ����ť�����ػ�������ֵΪFALSEʱ����ť���´�ˢ��ʱ�ػ���
    ����ֵ  ����
    ====================================================================*/
	void SetBkColor(COLORREF crBk, BOOL bRepaint = FALSE);
	static void staticSetBkColor(COLORREF crBk);

    /*====================================================================
    ������  ��SetBk
    ��  ��  ���������ڵı������Ƚϰ�ȫ����ʾ͸��Ч����
    ȫ�ֱ�������
    ���������CDC* pDC	�����ڻ�������CDCָ�롣
    ����ֵ  ����
    ====================================================================*/
	void SetBk(CDC* pDC);
    
    
    /*====================================================================
    ������  ��SetBkTrans
    ��  ��  ���趨��ť�Ƿ�͸����
    ȫ�ֱ�������
    ���������bTrans:TRUEʱ��ť͸��������ȡ�����ڣ�FALSE��ť��͸����
    ����ֵ  ����
    ====================================================================*/
	void SetBkTrans(BOOL bTrans = TRUE);

    /*====================================================================
    ������  ��EnableTooltipText
    ��  ��  ������Tooltip���ܡ�
    ȫ�ֱ�������
    ���������bActivate:�Ƿ�����Tooltip���ܡ�
    ����ֵ  ����
    ====================================================================*/
	void EnableTooltipText(BOOL bActivate = TRUE);

    /*====================================================================
    ������  ��SetTooltipText
    ��  ��  ������Tooltip�ı�
    ȫ�ֱ�������
    ���������lpszText: �ı����ݣ�
              bActivate:�Ƿ�����Tooltip���ܡ�
    ����ֵ  ����
    ====================================================================*/
	void SetTooltipText(UINT nText, BOOL bActivate = TRUE);
	void SetTooltipText(LPCTSTR lpszText, BOOL bActivate = TRUE);
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCheckButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PreSubclassWindow();
    virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	void FreeResource();
	void SetBkParent(CWnd* pParent);
	void SizeToContent(BOOL bEnable = TRUE);
	void InitTooltip();
	virtual ~CCheckButton();

	// Generated message map functions
protected:
	CSize m_sizeButton;
	CSize m_sizeBitmap;
	void CancelHover();
	CBitmap m_bmpBk;
	CBitmap* m_pbmpOldBk;
	CDC m_dcBk;
	BOOL m_bTrans;
	void PaintBk(CDC* pDC);
	void DrawBitmap(CDC* pDC, CRect rcBit);
	void DrawCheck(CDC* pDC, CRect rect, COLORREF crCheck);
	void DrawTextCheck(CDC* pDC, CRect rcCheckFrame);
	//{{AFX_MSG(CCheckButton)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnClicked();
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
    afx_msg LRESULT OnMouseLeave(WPARAM, LPARAM);
	afx_msg LRESULT OnRadioInfo(WPARAM, LPARAM);
	afx_msg LRESULT OnBMSetCheck(WPARAM, LPARAM);
	afx_msg LRESULT OnBMGetCheck(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
private:
    BOOL m_bMouseIn;
    BOOL m_bDisable;
    BOOL m_bDown;
    BOOL m_bIsFocussed;
	BOOL m_bChecked;
	DWORD m_Style;

    CWnd* m_pParent;
    int m_nFrameSize;
    CToolTipCtrl m_ToolTip;

    enum {STATE_CHECK = 0, STATE_UNCHECK, 
        STATE_DISCHECK, STATE_DISUNCHECK, 
        STATE_HOTCHECK, STATE_HOTUNCHECK,
        STATE_DOWNCHECK, STATE_DOWNUNCHECK,
        STATE_MAX};
    //����״̬��ͼƬ����� 
    HBITMAP m_hBitmap[STATE_MAX];

    COLORREF m_crFrame[2];
    COLORREF m_crText[2];
    COLORREF m_crCheck[2];
    COLORREF m_crBk;
    
    //��̬��ɫ����  [zhuyr][3/29/2005]
    static COLORREF m_s_crFrame[2];
    static COLORREF m_s_crText[2];
    static COLORREF m_s_crCheck[2];
    static COLORREF m_s_crBk;

    BOOL m_bSizeToContent;     //��ť��ͼƬ��С��Ӧ��ϵ��TRUEʱΪ��ť��ӦͼƬ��

    BOOL m_bNeedFree;

    COLORREF m_crFocus;  //��������ɫ��
};


/*******************************************************************
������CSkinFrame
���ܣ�CSkinListCtrl �ı߿�
*********************************************************************/
class CSkinFrame : public CStatic
{
// Construction
public:
	CSkinFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinFrame)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetFrameColor(COLORREF crFrame, BOOL bRepaint = FALSE);
    static COLORREF m_s_crFrame;
	virtual ~CSkinFrame();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSkinFrame)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
protected:
	COLORREF m_crFrame;
};

/************************************************************************/
/* �б�ؼ�                                                             */
/************************************************************************/
class CSkinListCtrl : public CListCtrl
{
    DECLARE_DYNAMIC(CSkinListCtrl)
// Construction
public:
	CSkinListCtrl();

// �ӿ�
public:
    /*====================================================================
    ������	��    SetTitleBkColor
    ����		�����ñ������ı���ɫ��
    �㷨ʵ��	������ѡ�
    ����ȫ�ֱ�������
    �������˵����crBk:���õı���������ɫ
                  bRepaint:�Ƿ������ػ���
    ����ֵ˵����  ��
    ====================================================================*/
	void SetTitleBkColor(COLORREF crBk, BOOL bRepaint = TRUE);
    
    /*====================================================================
    ������	��    SetTitleTextColor
    ����		�����ñ������������ɫ
    �㷨ʵ��	������ѡ�
    ����ȫ�ֱ�������
    �������˵����crText:�������������ɫ
                  bRepaint:�Ƿ������ػ���
    ����ֵ˵����  ��
    ====================================================================*/
	void SetTitleTextColor(COLORREF crText, BOOL bRepaint = TRUE);

    /*====================================================================
    ������	��    SetTitleFrameColor
    ����		�����ñ������߿���ɫ
    �㷨ʵ��	������ѡ�
    ����ȫ�ֱ�������
    �������˵����crFrame:���õı������߿�ɫ
                  bRepaint:�Ƿ������ػ���
    ����ֵ˵����  ��
    ====================================================================*/
	void SetTitleFrameColor(COLORREF crFrame, BOOL bRepaint = FALSE);
    
    /*====================================================================
    ������	��    SetTitleDivideColor
    ����		�����ñ������ָ����ߵ���ɫ�ͷ��
    �㷨ʵ��	������ѡ�
    ����ȫ�ֱ�������
    �������˵����crDivide:���õı������ָ����ߵ���ɫ
                  npenStyel:���ߵķ��PS_SOLID:ʵ�ģ�PS_DOT�����ߡ�
                  bRepaint:�Ƿ������ػ���
    ����ֵ˵����  ��
    ====================================================================*/
	void SetTitleDivideColor(COLORREF crFrame, int npenStyle = PS_SOLID, BOOL bRepaint = FALSE);

    /*====================================================================
    ������	��    SetTitleFont
    ����		�����ñ�����������
    �㷨ʵ��	������ѡ�
    ����ȫ�ֱ�������
    �������˵����pFont:���õ������ָ�롣
    ����ֵ˵����  ��
    ====================================================================*/
	void SetTitleFont(CFont* pFont);

    /*====================================================================
    ������	��    SetTextBkColor
    ����		�������������ݵı�����ɫ��
    �㷨ʵ��	������ѡ�
    ����ȫ�ֱ�������
    �������˵����crBk:��Чʱ�ı�����ɫ��
                  crDisable:ʧЧʱ�ı�����ɫ��
                  bRepaint:�Ƿ������ػ���
    ����ֵ˵����  ��
    ====================================================================*/
	void SetTextBkColor(COLORREF crBk, COLORREF crDisable=-1, BOOL bRepaint = TRUE);
    
    /*====================================================================
    ������	��    SetTextColor
    ����		�������������ݵ��ı���ɫ��
    �㷨ʵ��	������ѡ�
    ����ȫ�ֱ�������
    �������˵����crText:��Чʱ���ı���ɫ��
                  crDisable:ʧЧʱ���ı���ɫ��
                  bRepaint:�Ƿ������ػ���
    ����ֵ˵����  ��
    ====================================================================*/
	void SetTextColor(COLORREF crText, COLORREF crDisable, BOOL bRepaint = TRUE);
    
    /*====================================================================
    ������	��    SetTextFont
    ����		���������ݵ����塣
    �㷨ʵ��	������ѡ�
    ����ȫ�ֱ�������
    �������˵����pFont:����ָ�롣
    ����ֵ˵����  ��
    ====================================================================*/
	void SetTextFont(CFont *pFont);

    /*====================================================================
    ������	��    EnableHighlight
    ����		�����ù���µ����Ƿ�����Զ��ı䱳��ɫ��
    �㷨ʵ��	������ѡ�
    ����ȫ�ֱ�������
    �������˵����bHighlight:�Ƿ������ù��ܡ�
    ����ֵ˵����  ��
    ====================================================================*/
	void EnableHighlight(BOOL bHighlight);

    /*====================================================================
    ������	��    SetHighlightColor
    ����		�����ø�����ʾ�����ּ�������ɫ
    �㷨ʵ��	������ѡ�
    ����ȫ�ֱ�������
    �������˵����crText:������ɫ
                  crBk:����ɫ
                  bRepaint:�Ƿ������ػ���
    ����ֵ˵����  ��
    ====================================================================*/
	void SetHighlightColor(COLORREF crText=-1, COLORREF crBk=-1, BOOL bRepaint=TRUE);
   
    /*====================================================================
    ������	��    SetSelectColor
    ����		�����ñ�ѡ�е��е����弰����ɫ��
    �㷨ʵ��	������ѡ�
    ����ȫ�ֱ�������
    �������˵����crText:������ɫ
                  crBk:����ɫ
                  bRepaint:�Ƿ������ػ���
    ����ֵ˵����  ��
    ====================================================================*/
	void SetSelectColor(COLORREF crText=-1, COLORREF crBk=-1, BOOL bRepaint=TRUE);
    
    
    /*====================================================================
    ������	��    SetFrameColor
    ����		�����ñ߿����ɫ
    �㷨ʵ��	������ѡ�
    ����ȫ�ֱ�������
    �������˵����crFrame:�߿����ɫ��
                  bRepaint:�Ƿ������ػ���
                  bShow: �Ƿ���ʾ�߿�
    ����ֵ˵����  ��
    ====================================================================*/
	void SetFrameColor(COLORREF crFrame, BOOL bRepaint = FALSE, BOOL bShow = TRUE);

    /*====================================================================
    ������	��    EnableHeadDragDrop
    ����		���Ƿ����������ק��λ
    �㷨ʵ��	������ѡ�
    ����ȫ�ֱ�������
    �������˵����bEable:�Ƿ�����
    ����ֵ˵����  ��
    ====================================================================*/
	void EnableHeadDragDrop(BOOL bEnable = TRUE);

    /*====================================================================
    ������	��    EnableSort
    ����		���Ƿ�����������
    �㷨ʵ��	������ѡ�
    ����ȫ�ֱ�������
    �������˵����bEnable:�Ƿ�����
    ����ֵ˵����  ��
    ====================================================================*/
    void EnableSort(BOOL bEnable = TRUE);
    
    /*====================================================================
    ������	��    SetCompareFun
    ����		�����ñȽϻص���������������
    �㷨ʵ��	������ѡ�
    ����ȫ�ֱ�������
    �������˵����pfnCompare:�ȽϺ��������ú�������������Ϊ
                             static int CALLBACK FunName(LPARAM,LPARAM,LPARAM,LPARAM);
                             ǰ��������Ϊ�Ƚϵ����ݣ���SetItemData���ã���
                             ������Ϊ���ñȽϺ���ʱ���ݵĲ��������������ĵڶ�������lparam��
                             ���ĸ�Ϊ��ǰ������С�
                  lparam:������ص��������صĲ�����
    ����ֵ˵����  ��
    ====================================================================*/
	void SetCompareFun(PFNNEWCOMPARE pfnCompare, LPARAM lparam);

    /*====================================================================
    ������	��    SetToolTipStyle
    ����		������Tooltips��ʾ��ʽ��
    �㷨ʵ��	������ѡ�
    ����ȫ�ֱ�������
    �������˵����nStyle: TTS_WHOLEROW��ʾ��ʾ��������, TTS_HIDEITME��ʾֻ��ʾ������ȫ��ʾ�ĵ�Ԫ��
    ����ֵ˵����  ��
    ====================================================================*/
	void SetToolTipStyle(UINT nStyle);

    /*�������� SetHasFrame
    ��    �ܣ� 
    ��    ���� BOOL bFrame���Ƿ��б߿�
    �� �� ֵ�� 
    ˵    ���� */
    void SetShowFrame(BOOL bFrame){m_bShowFrame = bFrame;};

    /*====================================================================
    ������	��    staticSetBkColor, staticSetTextColor
    ����		�����þ�̬��ɫ������
    �㷨ʵ��	������ѡ�
    ����ȫ�ֱ�������
    ��    ���� COLORREF crBkNormal     ������״̬��ɫ
               COLORREF crBkDisable    ��ʧЧ״̬��ɫ
               COLORREF crBkSelect     ��ѡ��״̬��ɫ
               COLORREF crBkHighlight  ������״̬��ɫ
    ����ֵ˵����  ��
    ====================================================================*/
    static void staticSetBkColor(COLORREF crBkNormal, COLORREF crBkDisable, 
        COLORREF crBkSelect, COLORREF crBkHighlight);
    static void staticSetTextColor(COLORREF crTextNormal, COLORREF crTextDisable, 
        COLORREF crTextSelect, COLORREF crTextHighlight);
// Operations
public:
    void ResortItem(int nItem = -1);
     virtual int OnToolHitTest(CPoint point, TOOLINFO* pTI) const;
    enum{CRNORMAL=0, CRDISABLE, CRSELECT, CRHIGHLIGHT, CRMAX};
    enum{TTS_DISABLE=0, TTS_WHOLEROW=1, TTS_HIDEITME};

#ifdef USESKINSCROLL
	void SetScrollBkColor(COLORREF crFrom, COLORREF crTo=-1, BOOL bRepaint = FALSE);
	void SetScrollArrowColor(COLORREF crBk, COLORREF crArrow=0, COLORREF crFrame = -1, BOOL bRepaint = FALSE);
#endif 
	void SetColumnBkColor(int nColnum,COLORREF crBk, BOOL bRepaint = TRUE);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinListCtrl)
    virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PreSubclassWindow();
    virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	DWORD GetItemData(int nItem) const;
	BOOL SetItemData(int nItem, DWORD dwData);

    BOOL GetItem( LVITEM* pItem ) const;
    BOOL SetItem(const LVITEM* pItem);
    BOOL SetItem( int nItem, int nSubItem, UINT nMask, LPCTSTR lpszItem, int nImage, UINT nState, UINT nStateMask, LPARAM lParam );

	BOOL DeleteAllItems();
	BOOL DeleteItem(int nItem);
	void ResetIndex();
	int InsertItem( int nItem, LPCTSTR lpszItem, int nImage );
	int InsertItem( int nItem, LPCTSTR lpszItem );
	int InsertItem( UINT nMask, int nItem, LPCTSTR lpszItem, UINT nState, UINT nStateMask, int nImage, LPARAM lParam );
	int InsertItem( const LVITEM* pItem );
	virtual CString GetTooltipText(int nItem, int nSubItem) const;
	void EnableRowSelect(HWND hWnd, int row, BOOL bSelected);
	BOOL IsRowSelect(HWND hWnd, int row);

    //����Ϊ�����header���Ի����
    int InsertColumn(int nCol, const LVCOLUMN* pColumn);
	int InsertColumn(int nCol, LPCTSTR lpszColumnHeading,
		int nFormat = LVCFMT_LEFT, int nWidth = -1, int nSubItem = -1);
	
	virtual ~CSkinListCtrl();

	// Generated message map functions
#ifdef USESKINSCROLL
    CSkinScroll m_VScroll;
    CSkinScroll m_HScroll;
#endif
protected:
	void FreeData(int nItem);
	BOOL m_nODItemChanged;
	BOOL m_bOldHightState;
	BOOL m_bNewFont;
	HCURSOR m_hOldCursor;
	HCURSOR m_hCursor;
	BOOL m_bHighLight;
	CRect m_crClient;
	UINT m_uToolTipStyle;
	DWORD m_wHitMask;
	CBrush m_bkBrush;
	BOOL m_bReport;
	CSkinHeaderCtrl m_Header;
    CSkinFrame m_stFrame;
	
    BOOL m_bLockChange;
    BOOL m_bSortAscending;       //������
	BOOL m_bSort;                //�Ƿ�����
    PFNNEWCOMPARE m_pfn;         //�Զ���������
    LPARAM m_pVoid;              //���������Ĳ���
	int m_nSortColumn;           //��ǰ������к�

    BOOL m_bHighlight;           //�Ƿ������������ܡ�
    int m_nHighlighted;          //������ʾ���к�

    COLORREF m_crBk[CRMAX];          //����ɫ0����ͨ��1��ʧЧ��2��ѡ�У�3������
    COLORREF m_crText[CRMAX];        //�ı�ɫ

	BOOL    m_bShowFrame;           //�Ƿ���ʾ�߿�
    //��̬��ɫ����  [zhuyr][3/29/2005]
    static COLORREF m_s_crBk[CRMAX];  
    static COLORREF m_s_crText[CRMAX];

    int m_nSingleColBk;
    COLORREF m_crSingleBk;
	//{{AFX_MSG(CSkinListCtrl)
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnMove(int x, int y);
	afx_msg void OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPaint();
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
    afx_msg BOOL OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
    afx_msg void OnDestroy();
	//}}AFX_MSG
    afx_msg void OnCustomDrawList ( NMHDR* pNMHDR, LRESULT* pResult );

    virtual afx_msg BOOL OnToolTipText( UINT id, NMHDR * pNMHDR, LRESULT * pResult );
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
    DECLARE_MESSAGE_MAP()

	static int CALLBACK MyCompare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamData);
};


//////////////////////////////////////////////////////////////////////////
//                                                                      //
//      �����б���                                                      //
//////////////////////////////////////////////////////////////////////////
class CSkinDDListCtrl : public CSkinListCtrl
{
// Construction
public:
	CSkinDDListCtrl();
protected:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinDDListCtrl)
    virtual void PreSubclassWindow();
    virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
//	virtual CString GetTooltipText(int nItem, int nSubItem);
public:
    void SetReceiveMsgWnd(HWND hRevMsgWnd = NULL);
	virtual ~CSkinDDListCtrl();

    BOOL Register();
protected:
    CDDTarget   *m_pcDropTarget;      //��������
    HWND        m_hRevMsgWnd;
private:

	// Generated message map functions
protected:
    virtual BOOL OnDrop(WPARAM pDropInfo, LPARAM lParam);
	virtual DROPEFFECT OnDropEx(WPARAM pDropInfo, LPARAM lParam);
	virtual DROPEFFECT OnDropOver(WPARAM pDropInfo, LPARAM lParam);

	//{{AFX_MSG(CSkinDDListCtrl)
	afx_msg void OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};


/*******************************************************************
������CSkinSlider
���ܣ�����͸������豳��ɫ,�軬��ͼ��
*********************************************************************/
class CSkinSlider : public CSliderCtrl
{
// Construction
public:
	CSkinSlider();

// �ӿ�
public:
    /*====================================================================
    ������	��    SetTickImage
    ����		�����û���ͼƬ
    �㷨ʵ��	������ѡ�
    ����ȫ�ֱ�������
    �������˵����nBitmap:��Чʱ�����ͼƬ
                  crTans:ͼƬ�ı���ɫ���������θ���ɫ��͸����ʾ����ɫ������
                  nDisableBitmap:ʧЧʱ�Ļ���ͼƬ
                  crDisableTans:ʧЧʱ��ͼƬ��͸��ɫ��
    ����ֵ˵����  ��
    ====================================================================*/
    void SetTickImage(UINT nBitmap, COLORREF crTans = -1, UINT nDisableBitmap = 0, COLORREF crDisableTans = -1);
	void SetTickImage(HBITMAP hBitmap, COLORREF crTans = -1,HBITMAP hDisableBitmap = NULL, COLORREF crDisableTans = -1);
	
    /*====================================================================
    ������	��    SetBkImage
    ����		�����ñ���ͼ
    �㷨ʵ��	������ѡ�
    ����ȫ�ֱ�������
    �������˵����nBitmap:����ͼ
    ����ֵ˵����  ��
    ====================================================================*/
	void SetBkImage(UINT nBitmap);
	void SetBkImage(HBITMAP hBitmap);

    /*====================================================================
    ������	��    SetBkColor
    ����		���趨�ؼ�����ɫ
    �㷨ʵ��	������ѡ�
    ����ȫ�ֱ�������
    �������˵����crBk:����ɫ
                  bRepaint:�Ƿ������ػ���
    ����ֵ˵����  ��
    ====================================================================*/
	void SetBkColor(COLORREF crBk, BOOL bRepaint = TRUE);
    static void staticSetBkColor(COLORREF crBk);

    /*====================================================================
    ������	��    SetBkTransparent
    ����		���Ƿ񱳾�͸��
    �㷨ʵ��	������ѡ�
    ����ȫ�ֱ�������
    �������˵����bTans:�Ƿ񱳾�͸����
    ����ֵ˵����  ��
    ====================================================================*/
	void SetBkTransparent(BOOL bTans);
    

    /*=============================================================================
    �� �� ���� SetTickColor
    ��    �ܣ� 
    �㷨ʵ�֣� 
    ȫ�ֱ����� 
    ��    ���� COLORREF crNormal  :����
               COLORREF crSelect  :ѡ��
               COLORREF crDisable :ʧЧ
               BOOL bRepaint      :�Ƿ������ػ���
    �� �� ֵ�� void 
    =============================================================================*/
	void SetTickColor(COLORREF crNormal, COLORREF crSelect, COLORREF crDisable = -1, BOOL bRepaint = FALSE);
    static void staticSetTickColor(COLORREF crNormal, COLORREF crSelect, COLORREF crDisable);

    void SetAllBkImage(BOOL bAll = TRUE){m_bAllBkImage = bAll;};
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinSlider)
	//}}AFX_VIRTUAL

// Implementation
public:
	int GetState(UINT uState);
	HBITMAP CreateImage(UINT nBitmap);
	HBITMAP CreateMask(HBITMAP hSourceBitmap, DWORD dwWidth, DWORD dwHeight, COLORREF crTransColor);
	virtual ~CSkinSlider();

	// Generated message map functions
protected:
	void DrawBMPChannel(CDC *pDC, LPNMCUSTOMDRAW lpcd, BOOL& bFocus);
	void DrawTrans(CDC* pDC, CRect rect, BOOL& bFocus);

    enum {ISTATENORMAL = 0, ISTATEHOT, ISTATESELECT, ISTATEDISABLE, ISTATEMAX};

	CBrush m_brushBk;
	BOOL m_bTransparent;
    BOOL m_bAllBkImage;
    HDC m_hDCBk;

	HBITMAP m_BitmapBk;
	HBITMAP m_BitmapTrBk;
	HBITMAP m_OldBitmapBk;
    HBITMAP m_BitmapThumb[2];
    HBITMAP m_hThumbMask[2];

    COLORREF m_crBk;
    COLORREF m_crThumb[ISTATEMAX];

    //��̬��ɫ����  [zhuyr][3/29/2005]
    static COLORREF m_s_crBk;
    static COLORREF m_s_crThumb[ISTATEMAX];

    CRect m_rcThumb;
    BOOL m_bHot;

	void DrawThumb(CDC* pDC, LPNMCUSTOMDRAW lpcd);
	void DrawChannel(CDC* pDC, LPNMCUSTOMDRAW lpcd, BOOL& bFocus);
	//{{AFX_MSG(CSkinSlider)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnCustomdraw(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
    afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};


/*******************************************************************
������CSkinEdit
���ܣ��趨������ɫ������ɫ�ͱ߿�ɫ��
*********************************************************************/
class CSkinEdit : public CEdit
{
// Construction
public:
	CSkinEdit();
    enum {TYPE_NORMAL = 0, TYPE_NMC};
    static UINT m_s_nType;

// �ӿ�
public:
    /*====================================================================
    ������	��   SetBkColor
    ����		�����ñ༭��ı���ɫ��
    �㷨ʵ��	������ѡ�
    ����ȫ�ֱ�����crBk:��Чʱ�ı���ɫ��
                  crDisable:ʧЧʱ�ı���ɫ��
                  bRepaint:�Ƿ������ػ���
    �������˵������
    ����ֵ˵����  ��
    ====================================================================*/
	void SetBkColor(COLORREF crBk, COLORREF crDisable = -1, BOOL bRepaint = FALSE);
    static void staticSetBkColor(COLORREF crBk, COLORREF crDisable);

    /*====================================================================
	������	��   SetTextColor
	����		�����ñ༭��������ɫ��
	�㷨ʵ��	������ѡ�
	����ȫ�ֱ�������
    �������˵����crText: ���ֵ���ɫ��
                  crDisable:ʧЧʱ��������ɫ�� 
                  bRepaint:�Ƿ������ػ���
	����ֵ˵������
    ====================================================================*/
	void SetTextColor(COLORREF crText, COLORREF crDisable = -1, BOOL bRepaint = FALSE);
    static void staticSetTextColor(COLORREF crText, COLORREF crDisable);

    /*====================================================================
	������	��    SetFrameColor
	����		�����ñ༭��ı߿���ɫ��
	�㷨ʵ��	������ѡ�
	����ȫ�ֱ�������
    �������˵����crFrame:�߿����ɫ��
                  bRepaint:�Ƿ������ػ���
	����ֵ˵����  ��
    ====================================================================*/
	void SetFrameColor(COLORREF crFrame, BOOL bRepaint = FALSE);
    static void staticSetFrameColor(COLORREF crFrame);
    

    /*=============================================================================
    �� �� ���� UseCustomMenu
    ��    �ܣ� �Ƿ�ʹ���Զ�����Ҽ��˵�
    �㷨ʵ�֣� 
    ȫ�ֱ����� 
    ��    ���� BOOL bUseCustomMenu������TRUE��ʹ�ã�FALSE����ʹ�á�
    �� �� ֵ�� void 
    ----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��		�汾		�޸���		�߶���    �޸�����
    2004/8/26   1.0			������                  ����
    =============================================================================*/
	void UseCustomMenu(BOOL bUseCustomMenu);
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinEdit)
	protected:
    virtual void PreSubclassWindow();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSkinEdit();

	// Generated message map functions
protected:
	CBrush   m_brushBk[2];
    BOOL     m_bCustomMenu;

	COLORREF m_crBk[2];
    COLORREF m_crText[2];
    COLORREF m_crFrame;

    //��ɫ����  [zhuyr][3/29/2005]
    static COLORREF m_s_crBk[2];
    static COLORREF m_s_crText[2];
    static COLORREF m_s_crFrame;
	//{{AFX_MSG(CSkinEdit)
	afx_msg void OnPaint();
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/*******************************************************************
������CSkinIPCtrl
���ܣ��趨�߿�ɫ��
*********************************************************************/
class CSkinIPCtrl : public CIPAddressCtrl
{
// Construction
public:
	CSkinIPCtrl();

    enum {TYPE_NORMAL = 0, TYPE_NMC};
    static UINT m_s_nType;
// Attributes
public:

// Operations
public:
    /*====================================================================
	������	��   SetTextColor
	����		�����ÿؼ�������ɫ��
	�㷨ʵ��	������ѡ�
	����ȫ�ֱ�������
    �������˵����crText: ���ֵ���ɫ��
                  crDisable:ʧЧʱ��������ɫ��
                  bRepaint:�Ƿ������ػ���
	����ֵ˵������
    ====================================================================*/
	void SetTextColor(COLORREF crText, COLORREF crDisable = -1, BOOL bRepaint = FALSE);
    static void staticSetTextColor(COLORREF crText, COLORREF crDisable);

    /*====================================================================
    ������	��   SetBkColor
    ����		�����ÿؼ��ı���ɫ��
    �㷨ʵ��	������ѡ�
    ����ȫ�ֱ�����crBk:��Чʱ�ı���ɫ��
                  crDisable:ʧЧʱ�ı���ɫ��
                  bRepaint:�Ƿ������ػ���
    �������˵������
    ����ֵ˵����  ��
    ====================================================================*/
	void SetBkColor(COLORREF crBk, COLORREF crDisable, BOOL bRepaint = FALSE);
    static void staticSetBkColor(COLORREF crBk, COLORREF crDisable);

    /*====================================================================
	������	��    SetFrameColor
	����		�����ÿؼ��ı߿���ɫ��
	�㷨ʵ��	������ѡ�
	����ȫ�ֱ�������
    �������˵����crFrame:�߿����ɫ��
                  bRepaint:�Ƿ������ػ���
	����ֵ˵����  ��
    ====================================================================*/
	void SetFrameColor(COLORREF crFrame, BOOL bRepaint=FALSE);
	static void staticSetFrameColor(COLORREF crFrame);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinIPCtrl)
	public:
	protected:
    virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSkinIPCtrl();

	// Generated message map functions
protected:
	CBrush m_brushBk[2];

	COLORREF m_crBk[2];
    COLORREF m_crText[2];
    COLORREF m_crFrame;

    //��ɫ����  [zhuyr][3/29/2005]
    static COLORREF m_s_crBk[2];
    static COLORREF m_s_crText[2];
    static COLORREF m_s_crFrame;
	//{{AFX_MSG(CSkinIPCtrl)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnNcPaint();
    afx_msg void OnPaint();
	afx_msg void OnEnable(BOOL bEnable);
    afx_msg void OnMove(int x, int y);
    afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/*******************************************************************
������CStaticEx
���ܣ��趨������ɫ������͸������豳��ɫ��
*********************************************************************/
class CStaticEx : public CStatic
{
// Construction
public:
	CStaticEx();

// Attributes
public:

// �ӿ�
public:
    /*====================================================================
    ������  ��SetTextColor
    ��  ��  ������������ɫ��
    ȫ�ֱ�������
    ���������crText: ����ʱ������ɫ��
              crDisable:ʧЧʱ������ɫ��
              bRepaint: �Ƿ������ػ���
    ����ֵ  ����
    ====================================================================*/
	void SetTextColor(COLORREF crText, COLORREF crDisable = -1, BOOL bRepaint = TRUE);
    static void staticSetTextColor(COLORREF crText, COLORREF crDisable);
    
    /*====================================================================
    ������  ��SetBkTransparent
    ��  ��  �����ñ��������Ƿ�͸����
    ȫ�ֱ�������
    ���������bTrans: �Ƿ�͸����
    ����ֵ  ����
    ====================================================================*/
	void SetBkTransparent(BOOL bTrans = TRUE);
    
    /*====================================================================
    ������  ��SetBkColor
    ��  ��  �����ñ�����ɫ������������Ϊ͸��ʱ���ú�����Ч��
    ȫ�ֱ�������
    ���������crBk: ����ʱ�ı���ɫ��
              crDisable:ʧЧʱ�ı���ɫ��
              bRepaint: �Ƿ������ػ���
    ����ֵ  ����
    ====================================================================*/
	void SetBkColor(COLORREF crBk, COLORREF crDisable = -1, BOOL bRepaint = TRUE);
    static void staticSetBkColor(COLORREF crBk, COLORREF crDisable);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStaticEx)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
    virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetSingleLine(BOOL bSingleLine = FALSE);
	virtual ~CStaticEx();

	// Generated message map functions
protected:
	void EnableTooltip(BOOL bActive = TRUE);
	void InitToolTip();
	CToolTipCtrl m_toolTip;
	BOOL m_bShowToolTips;
    BOOL m_bTrans;
	BOOL m_bSingleLine;

	COLORREF m_crBk[2];
	COLORREF m_crText[2];

    //��ɫ����  [zhuyr][3/29/2005]
    static COLORREF m_s_crBk[2];
    static COLORREF m_s_crText[2];

    //{{AFX_MSG(CStaticEx)
	afx_msg void OnPaint();
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/*******************************************************************
������CSkinComboBox
���ܣ��ػ�ComboBox�������趨�������ֵ���ɫ��
*********************************************************************/
class CSkinComboBox : public CComboBox
{
// Construction
public:
	CSkinComboBox();
	virtual ~CSkinComboBox();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinComboBox)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDS);
    virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// �ӿ�
public:
    /*====================================================================
    ������  ��SetButtonImage
    ��  ��  �����ÿؼ�������ťͼƬ��
    ȫ�ֱ�������
    ���������nBitmap: ����ʱ��ťͼƬ��ԴID�ţ�
              nDisableBitmap: ʧЧʱ�İ�ťͼƬ��ԴID�š�(����)
    ����ֵ  ����
    ====================================================================*/
	void SetButtonImage(UINT nBitmap, UINT nDisableBitmap);
	void SetButtonImage(HBITMAP hBitmap, HBITMAP hDisableBitmap);

    /*====================================================================
    ������  ��SetButtonColor
    ��  ��  �����ÿؼ�������ť����ɫ�������˰�ťͼƬʱ���ú�����Ч��
    ȫ�ֱ�������
    ���������crFront: ��ťǰ�������ε���ɫ��
              crBk: ��ť�ı���ɫ��
              crDisableFt: ʧЧʱ�İ�ťǰ��ɫ��
              crDisableBk: ʧЧʱ�İ�ť����ɫ��
    ����ֵ  ����
    ====================================================================*/
	void SetButtonColor(COLORREF crFront, COLORREF crBk, COLORREF  crDisableFt, COLORREF crDisableBk);
	static void staticSetButtonColor(COLORREF crFront, COLORREF crBk,
        COLORREF  crDisableFt, COLORREF crDisableBk);

    /*====================================================================
    ������  ��SetFrameColor
    ��  ��  �����ÿؼ��߿���ɫ��
    ȫ�ֱ�������
    ���������crFrame: �߿���ɫ��
              bRepaint: �Ƿ������ػ���
    ����ֵ  ����
    ====================================================================*/
	void SetFrameColor(COLORREF crFrame, BOOL bRepaint = FALSE);
    static void staticSetFrameColor(COLORREF crFrame);

    /*====================================================================
    ������  ��SetBkColor
    ��  ��  �������ı�������ɫ��
    ȫ�ֱ�������
    ���������crBk: ����ʱ���ı�����ɫ��
              crHighlight:������ʾʱ���ı�����ɫ��
              bRepaint: �Ƿ������ػ���
    ����ֵ  ����
    ====================================================================*/
	void SetBkColor(COLORREF crBk, COLORREF crHighlight, BOOL bRepaint = FALSE);
    static void staticSetBkColor(COLORREF crBk, COLORREF crHighlight, COLORREF crDisable);

    /*====================================================================
    ������  ��SetTextColor
    ��  ��  �������ı���ɫ��
    ȫ�ֱ�������
    ���������crText: ����ʱ���ı�ɫ��
              crHighlight:������ʾʱ�ı���ɫ��
              bRepaint: �Ƿ������ػ���
    ����ֵ  ����
    ====================================================================*/
	void SetTextColor(COLORREF crText, COLORREF crHighlight, BOOL bRepaint = FALSE);
    static void staticSetTextColor(COLORREF crText, COLORREF crHighlight);

	// Generated message map functions
protected:
	void DrawImageButton(CDC* pDC, CRect rect);

	BOOL m_bDrawList;
	BOOL m_bEnable;
    BOOL m_bNeedFree;
	BOOL m_bDrop;

	CSize m_sizeButton;
    HBITMAP m_hBitmap[2];
    CBrush  m_brushBk[2];

	COLORREF m_crFrame;
	COLORREF m_crText[2];
	COLORREF m_crBk[3];
    COLORREF m_crButton[4];

    static COLORREF m_s_crFrame;
    static COLORREF m_s_crText[2];
    static COLORREF m_s_crBk[3];
    static COLORREF m_s_crButton[4];
	//{{AFX_MSG(CSkinComboBox)
	afx_msg void OnPaint();
	afx_msg BOOL OnDropdown();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

    virtual LRESULT DefWindowProc (UINT message, WPARAM wParam, LPARAM lParam);
};

/*******************************************************************
������CBMPDlg
���ܣ�ʵ���趨����ͼ
*********************************************************************/
class CBMPDlg : public CDialog
{
// ���캯���ͽӿ�
public:
    /*====================================================================
    ������  ��SizeToContent
    ��  ��  ���ı�Ի����С����ӦͼƬ��
    ====================================================================*/
	void SizeToContent();
    
    /*====================================================================
    ������  ��SetBkColor
    ��  ��  �����öԻ���ı���ɫ��������Ϊ����ɫ��
    ȫ�ֱ�������
    ���������crTop:�Ի������϶˵���ɫ��
              crBottom:�Ի������¶˵���ɫ��
    ����ֵ  ����
    ====================================================================*/
	void SetBkColor(COLORREF crTop, COLORREF crBottom = -1, BOOL bRepaint = FALSE);

    /*====================================================================
    ������  ��SetBkImage
    ��  ��  �����öԻ��򱳾�ͼ��
    ȫ�ֱ�������
    ���������hBitmap: ����ͼ�ľ����
              nBitmap:����ͼ����ԴID��
    ����ֵ  ����
    ====================================================================*/
	void SetBkImage(HBITMAP hBitmap);
	void SetBkImage(UINT nBitmap);
//�ӿ����


	CBMPDlg(CWnd* pParent = NULL);   // standard constructor
	CBMPDlg(UINT uResourceID, CWnd* pParent = NULL);
	CBMPDlg(LPCTSTR pszResourceID, CWnd* pParent = NULL);
    ~CBMPDlg();

// Dialog Data
	//{{AFX_DATA(CBMPDlg)
//	enum { IDD = _UNKNOWN_RESOURCE_ID_ };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBMPDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void DrawBk(CDC* pDC);
	void Init();
	void FreeResources();

    CBitmap m_Bitmap;
    HBITMAP m_OldBitmap;
    CDC m_BkDC;
	HBITMAP m_hBitmap;
    DWORD m_dwWidth;
    DWORD m_dwHeight;
    BOOL m_bSizeToContent;

    COLORREF m_crTop;
    COLORREF m_crBottom;

	// Generated message map functions
	//{{AFX_MSG(CBMPDlg)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/*******************************************************************
������CSkinSpinCtrl
���ܣ�ʵ���趨����ɫ��ǰ��ɫ
*********************************************************************/
class CSkinSpinCtrl : public CSpinButtonCtrl
{
// Construction
public:
	CSkinSpinCtrl();

// Attributes
public:
    enum {Outside=0, OnRightInside, OnLeftInside};
    enum {NoHot = 0, FirstHot, LastHot};
    enum {STNormal = 0, STPressed, STHilight, STDisable, STAll};
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinSpinCtrl)
	public:
	protected:
	virtual void PreSubclassWindow();
    virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
    
    /*====================================================================
    ������	��   SetForeColor 
    ����		���趨��ť��ǰ��ɫ�����ǣ�
    �㷨ʵ��	������ѡ�
    ����ȫ�ֱ�������
    �������˵����COLORREF crFore:����״̬�µ���ɫ
                  COLORREF crPressed����ѹʱ����ɫ
                  COLORREF crHilight���������ʱ����ɫ
                  BOOL bRepaint���Ƿ������ػ�
    ����ֵ˵����  ��
    ====================================================================*/
	void SetForeColor(COLORREF crFore, COLORREF crPressed, COLORREF crHilight, BOOL bRepaint = FALSE);
    static void staticSetForeColor(COLORREF crFore, COLORREF crPressed,
        COLORREF crHilight, COLORREF crDisable);
    
    /*====================================================================
    ������	��   SetBkColor 
    ����		���趨��ť�ı���ɫ
    �㷨ʵ��	������ѡ�
    ����ȫ�ֱ�������
    �������˵����COLORREF crBk:����״̬�µ���ɫ
                  COLORREF crPressed����ѹʱ����ɫ
                  COLORREF crHilight���������ʱ����ɫ
                  BOOL bRepaint���Ƿ������ػ�
    ����ֵ˵����  ��
    ====================================================================*/
	void SetBkColor(COLORREF crBk, COLORREF crPressed, COLORREF crHilight = -1, BOOL bRepaint = FALSE);
    static void staticSetBkColor(COLORREF crBk, COLORREF crPressed,
        COLORREF crHilight, COLORREF crDisable);

    /*�������� SetDisableColor
    ��    �ܣ� ����ʧЧʱ����ɫ��
    ��    ���� COLORREF crFore
               COLORREF crBk
    �� �� ֵ�� 
    ˵    ���� */
    void SetDisableColor(COLORREF crFore, COLORREF crBk);
	
    virtual ~CSkinSpinCtrl();
protected:
    CRect m_rcFirst;
    CRect m_rcLast;
    CRect m_rcPressed;
    UINT m_nSpinAlign;
	BOOL m_bVertical;
    BOOL m_bPressed;
    
    int  m_nMax;
    int  m_nMin;
    int  m_nPos;

	COLORREF m_crFore[STAll];
    COLORREF m_crBk[STAll];

    //��ɫ����  [zhuyr][3/29/2005]
    static COLORREF m_s_crFore[STAll];
    static COLORREF m_s_crBk[STAll];

	// Generated message map functions
protected:
	int m_nHotPos;
	void CreateArrowRgn(CRgn &rgnFirst, CRgn &rgnLast);
	//{{AFX_MSG(CSkinSpinCtrl)
	afx_msg void OnPaint();
	afx_msg BOOL OnDeltapos(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};


class CSkinGroup : public CButton
{
// Construction
public:
	CSkinGroup();
    enum {COLTYPE_TEXT = 1, COLTYPE_LINE = 2, COLTYPE_ALL = 3};

// �ӿ�
public:
    /*====================================================================
    ������	��    SetLMetric
    ����		���������ֵ���߿�ľ���
    �㷨ʵ��	������ѡ�
    ����ȫ�ֱ�������
    �������˵����nMetric������
    ����ֵ˵����  ��
    ----------------------------------------------------------------------
    �޸ļ�¼:
    ��  ��		�汾		�޸���		�߶���    �޸�����
    2004/07/30	1.0			������                  ����
    ====================================================================*/
	void SetLMetric(UINT nMetric = 7);

    /*====================================================================
    ������	��    SetGroupColor
    ����		�����ÿؼ���ɫ
    �㷨ʵ��	������ѡ�
    ����ȫ�ֱ�������
    �������˵����crNormal: ����ʱ��ʾ����ɫ, -1ʱ����ԭ������ɫ��
                  crDisable:ʧЧʱ��ʾ����ɫ, -1ʱ����ԭ������ɫ��
                  bRepaint:�Ƿ������ػ��ؼ���
    ����ֵ˵����  ��
    ----------------------------------------------------------------------
    �޸ļ�¼:
    ��  ��		�汾		�޸���		�߶���    �޸�����
    2004/07/30	1.0			������                  ����
    ====================================================================*/
	void SetGroupColor(COLORREF crNormal, COLORREF crDisable=-1,
        BOOL bRepaint = FALSE, int nType = COLTYPE_ALL);
    static void staticSetGroupColor(COLORREF crNormal, COLORREF crDisable,
        int nType = COLTYPE_ALL);

    /*=============================================================================
    �� �� ��:SetWindowText
    ��    ��:���ñ�������
    ��    ��:LPCTSTR lpszString         [in]    ��������
    ע    ��:ר�����ڴ�����Ӱ����
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/12/26  4.0     ���    ����
    =============================================================================*/
    void SetWindowText(LPCTSTR lpszString);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinGroup)
	public:
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSkinGroup();

	// Generated message map functions
protected:
    COLORREF m_crText[2];
    COLORREF m_crLine[2];
    CPen     m_penLine[2];
    UINT     m_nLMetric;
    CString  m_strTitle;

    static COLORREF m_s_crText[2];
    static COLORREF m_s_crLine[2];
	//{{AFX_MSG(CSkinGroup)
	afx_msg void OnPaint();
	afx_msg void OnEnable(BOOL bEnable);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

class CTextButton30 : public CButton
{
public:
    CTextButton30();
    virtual ~CTextButton30();

    /*====================================================================
    ������  ��EnableTooltipText
    ��  ��  ������Tooltip���ܡ�
    ȫ�ֱ�������
    ���������bActivate:�Ƿ�����Tooltip���ܡ�
    ����ֵ  ����
    ====================================================================*/
	void EnableTooltipText(BOOL bActivate = TRUE);

	void InitTooltip();

    /*====================================================================
    ������  ��SetTooltipText
    ��  ��  ������Tooltip�ı�
    ȫ�ֱ�������
    ���������lpszText: �ı����ݣ�
              bActivate:�Ƿ�����Tooltip���ܡ�
    ����ֵ  ����
    ====================================================================*/
	void SetTooltipText(LPCTSTR lpszText, BOOL bActivate = TRUE);

public:
    //��ť��ɫ��0������1ʧЧ�� over��click���ס�
    COLORREF m_crText;
    COLORREF m_crBk[2];
    COLORREF m_crFrame[2];

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextButton30)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDS);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PreSubclassWindow();
    virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

protected:

    BOOL m_bMouseIn;
    BOOL m_bDown;
    BOOL m_bDisable;
    BOOL m_bFocus;

    CToolTipCtrl m_ToolTip;

    //{{AFX_MSG(CTextButton30)
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnCancelMode();
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
    LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

private:
    void CancelHover();
};



class CSkinTab : public CTabCtrl
{
// Construction
public:
	CSkinTab();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinTab)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:

    /*=============================================================================
    �� �� ���� SetColors
    ��    �ܣ� 
    �㷨ʵ�֣� 
    ȫ�ֱ����� 
    ��    ���� COLORREF crFrame  :�߿���ɫ
               COLORREF crHBk    :����ҳ����ɫ
               COLORREF crLBk    :��ͨҳ����ɫ
               COLORREF crText   :������ɫ
    �� �� ֵ�� void 
    ˵����     ʹ��ͼƬʱ�Ż���crTextֵ���������壬����ʹ�ÿ��crFrame����ɫ
    =============================================================================*/
	void SetColors(COLORREF crFrame, COLORREF crHBk, COLORREF crLBk, COLORREF crText = RGB(80, 114, 170));
    void SetBKColor(COLORREF crBk);
    static void staticSetColors(COLORREF crFrame, COLORREF crHBk, COLORREF crLBk, COLORREF crText = RGB(80, 114, 170));
    static void staticSetBKColor(COLORREF crBk);

	void SetType(UINT nType);
	void SetMask(UINT nHLeft, UINT nHRight, UINT nLLeft, UINT nLRight);

    void SetSigleLine(BOOL bSigleLine){m_bSigleLine = bSigleLine;};
    
	void DrawSimpleBorder(CDC* pDC, CRect& rect, BOOL bSel);
	void DrawImageBorder(CDC* pDC, CRect rect, BOOL bSel);
	virtual ~CSkinTab();

    enum {TYPE_ROUNTRECT = 0, TYPE_POLYGON, TYPE_TRAPEZIA, TYPE_BITMAP};

	// Generated message map functions
protected:
	void GetRgn(CRect& rect, CRgn& rgn, BOOL bSel, int& nWidth);
	void DrawItem(LPDRAWITEMSTRUCT lpdis);
	//{{AFX_MSG(CSkinTab)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

    COLORREF m_crLBk;
    COLORREF m_crHBk;
    COLORREF m_crFrame;
    COLORREF m_crTableBK;
    COLORREF m_crText;  // ʹ��ͼƬʱ�Ż��ø�ֵ���������壬����ʹ�ÿ�ܵ���ɫ

    BOOL     m_bSigleLine;
    UINT     m_nType;
    UINT     m_nWidth;
    UINT     m_nImageWidth[4];

    CRect    m_rcClient;

    HBITMAP  m_hBitmap[4];
    CSkinSpinCtrl  m_Spin;

    static COLORREF m_s_crLBk;
    static COLORREF m_s_crHBk;
    static COLORREF m_s_crFrame;
    static COLORREF m_s_crTableBK;
    static COLORREF m_s_crText; // ʹ��ͼƬʱ�Ż��ø�ֵ���������壬����ʹ�ÿ�ܵ���ɫ
};


class CSkinSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CSkinSheet)
// Construction
public:
	CSkinSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CSkinSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:
    static COLORREF m_s_crBk;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinSheet)
	public:
	virtual BOOL OnInitDialog();
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
    void SetCreate(BOOL bCreate){m_bCreate = bCreate;};
	void MovePage(CPropertyPage* pPage);
	void FreshButton();
	CSkinTab* GetSkinTab();
	virtual ~CSkinSheet();
    enum{HMARGIN = 6, VMARGIN = 3};

	// Generated message map functions
	CTextButton30        m_btnCancel;
protected:
	void Init();
	//{{AFX_MSG(CSkinSheet)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
    CSkinTab *m_pTab;
	CTextButton30        m_btnFinish;
	CTextButton30        m_btnOK;
	CTextButton30        m_btnApply;
    CTextButton30        m_btnHelp;
	CTextButton30        m_btnBack;
	CTextButton30        m_btnNext;

    COLORREF             m_crBk;
    LONG                 m_nCapHeight;
    BOOL                 m_bWizard;
    CRect                m_rcCaption;

    BOOL                 m_bCreate;
};


class CSkinPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CSkinPage)

// Construction
public:
	void SetTitle(LPCSTR strTitle);
    void SetColorBk(COLORREF crBk){m_crBk = crBk;};
	CSkinPage(UINT nIDTemplate = 0);
	~CSkinPage();

// Dialog Data
	//{{AFX_DATA(CSkinPage)
//	enum { IDD = _UNKNOWN_RESOURCE_ID_ };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
    
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSkinPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:
    COLORREF m_crBk;
    CString  m_strTitle;
protected:
	// Generated message map functions
	//{{AFX_MSG(CSkinPage)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


class CSkinCheckList : public CCheckListBox
{
// Construction
public:
	CSkinCheckList();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinCheckList)
	public:
	protected:
	virtual void PreSubclassWindow();
	virtual BOOL OnChildNotify(UINT, WPARAM, LPARAM, LRESULT*);
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
    //�ӿ�
	void SetTextColor(COLORREF crNormal, COLORREF crDisable, COLORREF crHilight);
	void SetBkColor(COLORREF crNormal, COLORREF crDisable, COLORREF crHilight);
	static void staticSetTextColor(COLORREF crNormal, COLORREF crDisable, COLORREF crHilight);
	static void staticSetBkColor(COLORREF crNormal, COLORREF crDisable, COLORREF crHilight);

    void SetFrameColor(COLORREF crFrame){m_stFrame.SetFrameColor(crFrame);};
    
    void SetCheckBMP(UINT nCheck);
	virtual ~CSkinCheckList();
	// Generated message map functions
protected:
	//{{AFX_MSG(CSkinCheckList)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnPaint();
    afx_msg LRESULT OnLBGetItemData(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnLBSetItemCheck(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
    // Ԥ׼���Ի�
	void PreDrawItemSelf(LPDRAWITEMSTRUCT lpDIS);
    void DrawItem(LPDRAWITEMSTRUCT lpDIS);
	DECLARE_MESSAGE_MAP()

protected:
    COLORREF m_crBk[3];
    COLORREF m_crText[3];
    CSkinFrame  m_stFrame;
    CSkinScroll m_VScroll;

    static COLORREF m_s_crBk[3];
    static COLORREF m_s_crText[3];
};


//////////////////////////////////////////////////////////////////////////
//CColourPopup ��ɫѡ��ؼ�ʹ�õĵ���ѡ�񴰿�
//////////////////////////////////////////////////////////////////////////

// CColourPopup messages
#define CPN_SELCHANGE        WM_USER + 1001        // Colour Picker Selection change
#define CPN_DROPDOWN         WM_USER + 1002        // Colour Picker drop down
#define CPN_CLOSEUP          WM_USER + 1003        // Colour Picker close up
#define CPN_SELENDOK         WM_USER + 1004        // Colour Picker end OK
#define CPN_SELENDCANCEL     WM_USER + 1005        // Colour Picker end (cancelled)
#define CSM_GETCOLOR         WM_USER + 1010        // Colour Select get colour
#define CSM_SETCOLOR         WM_USER + 1011        // Colour Select set colour

// forward declaration
class CColourPicker;

// To hold the colours and their names
typedef struct {
    COLORREF crColour;
    TCHAR    *szName;
    TCHAR    *szEncname;
} ColourTableEntry;

/////////////////////////////////////////////////////////////////////////////
// CColourPopup window

class CColourPopup : public CWnd
{
// Construction
public:
    CColourPopup();
    CColourPopup(CPoint p, COLORREF crColour, COLORREF crDefault, CWnd* pParentWnd,
                 LPCTSTR szDefaultText = NULL, LPCTSTR szCustomText = NULL);
    void Initialise();

// Attributes
public:
    static BOOL m_s_bUserChinese;

// Operations
public:
    BOOL Create(CPoint p, COLORREF crColour, CWnd* pParentWnd, 
                LPCTSTR szDefaultText = NULL, LPCTSTR szCustomText = NULL);

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CColourPopup)
    public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
    virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~CColourPopup();

protected:
    BOOL GetCellRect(int nIndex, const LPRECT& rect);
    void FindCellFromColour(COLORREF crColour);
    void SetWindowSize();
    void CreateToolTips();
    void ChangeSelection(int nIndex);
    void EndSelection(int nMessage);
    void DrawCell(CDC* pDC, int nIndex);

    COLORREF GetColour(int nIndex)              { return m_crColours[nIndex].crColour; }
    LPCTSTR GetColourName(int nIndex)           { return m_s_bUserChinese ?
        m_crColours[nIndex].szName : m_crColours[nIndex].szEncname; }
    int  GetIndex(int row, int col) const;
    int  GetRow(int nIndex) const;
    int  GetColumn(int nIndex) const;

// protected attributes
protected:
    static ColourTableEntry m_crColours[];
    int            m_nNumColours;
    int            m_nNumColumns, m_nNumRows;
    int            m_nBoxSize, m_nMargin;
    int            m_nCurrentSel;
    int            m_nChosenColourSel;
    CString        m_strDefaultText;
    CString        m_strCustomText;
    CRect          m_CustomTextRect, m_DefaultTextRect, m_WindowRect;
    CFont          m_Font;
    CPalette       m_Palette;
    COLORREF       m_crInitialColour, m_crColour, m_crDefault;
    CToolTipCtrl   m_ToolTip;
    CWnd*          m_pParent;

    BOOL           m_bChildWindowVisible;

    //custom draw  [zhuyr][10/9/2005]
    COLORREF       m_crFrame;
    COLORREF       m_crBackground;
    COLORREF       m_crFont;
    COLORREF       m_crHilightBk;
    COLORREF       m_crCustomBk;

    // Generated message map functions
protected:
    //{{AFX_MSG(CColourPopup)
    afx_msg void OnNcDestroy();
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnPaint();
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg BOOL OnQueryNewPalette();
    afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnActivateApp(BOOL bActive, DWORD hTask);
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
//Office�����ɫѡ��ؼ�
//////////////////////////////////////////////////////////////////////////

void AFXAPI DDX_ColourPicker(CDataExchange *pDX, int nIDC, COLORREF& crColour);
class CColorSelCtrl : public CButton
{
// Construction
public:
	CColorSelCtrl();

// Attributes
public:

// Operations
public:
    COLORREF GetColor() const;
    void     SetColor(COLORREF coColor);

    COLORREF GetDefaultColor() const;
    void     SetDefaultColor(COLORREF coColor);

    void     SetCustomText(LPCSTR lpText);
    void     SetDefaultText(LPCSTR lpText);

    void     SetTrackSelection(BOOL bTrack);
    BOOL     GetTrackSelection(void) const;

    void     SetTextMode(BOOL bUseDefault);
    void     SetBtnImage(UINT nNoraml, UINT nHilight,
        UINT nDown, UINT nDisable);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorSelCtrl)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
    virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CColorSelCtrl();
	__declspec(property(get=GetColor,put=SetColor))						COLORREF	Color;
	__declspec(property(get=GetDefaultColor,put=SetDefaultColor))		COLORREF	DefaultColor;
	__declspec(property(get=GetTrackSelection,put=SetTrackSelection))	BOOL		TrackSelection;
	__declspec(property(put=SetCustomText))								LPCTSTR		CustomText;
	__declspec(property(put=SetDefaultText))							LPCTSTR		DefaultText;
	// Generated message map functions
protected:
    static void DrawArrow(CDC* pDC, 
						  RECT* pRect, 
						  int iDirection = 0,
						  COLORREF clrArrow = RGB(0,0,0));
    static HBITMAP CreateImage(UINT nBitmap);
    void CancelHover();
	//{{AFX_MSG(CColorSelCtrl)
	afx_msg BOOL OnClicked();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	afx_msg LONG OnSelEndOK(UINT lParam, LONG wParam);
    afx_msg LONG OnSelEndCancel(UINT lParam, LONG wParam);
    afx_msg LONG OnSelChange(UINT lParam, LONG wParam);
    LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

protected:
    enum {STATE_NORMAL = 0, STATE_HILIGHT, STATE_DOWN, STATE_DISABLE, STATE_MAX};
    COLORREF m_crColor;
	COLORREF m_crDefault;
	CString  m_strDefaultText;
	CString  m_strCustomText;
	BOOL	 m_bPopupActive;
	BOOL	 m_bTrackSelection;
    BOOL     m_bDefautText;
    BOOL     m_bMouseIn;
    HBITMAP  m_hBitmap[STATE_MAX];

    COLORREF m_crFrame;
    COLORREF m_crBackgroud;
};

class CSkinDateTime : public CDateTimeCtrl
{
// Construction
public:
	CSkinDateTime();

// Attributes
public:
    void SetFrameColor(COLORREF crFrame);
    void SetBackColor(COLORREF crBK, COLORREF crDisable);
    void SetTextColor(COLORREF crText, COLORREF crDisable);

    static void static_SetFrameColor(COLORREF crFrame);
    static void static_SetBackColor(COLORREF crBK, COLORREF crDisable);
    static void static_SetTextColor(COLORREF crText, COLORREF crDisable);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinDateTime)
	protected:
	virtual void PreSubclassWindow();
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSkinDateTime();

protected:  
    CSkinSpinCtrl m_Spin;

	CBrush   m_brushBk[2];

	COLORREF m_crBk[2];
    COLORREF m_crText[2];
    COLORREF m_crFrame;
    
    //��ɫ����  [zhuyr][3/29/2005]
    static COLORREF m_s_crBk[2];
    static COLORREF m_s_crText[2];
    static COLORREF m_s_crFrame;
	// Generated message map functions
protected:
	//{{AFX_MSG(CSkinDateTime)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#endif

#ifndef _LOG4CPLUS_SERVER_H_
#define _LOG4CPLUS_SERVER_H_

#include <string>
#include "kdvtype.h"

class CLog4plusclientMgr
{
public:
	virtual ~CLog4plusclientMgr();
	static CLog4plusclientMgr* GetInstance();

	BOOL32	AddClient(std::string strClient, u32 dwTaskId);
	BOOL32	DelClient(std::string strClient, u32 dwTaskId);
	void	Show();

private:
	CLog4plusclientMgr();
	CLog4plusclientMgr(const CLog4plusclientMgr&);
	CLog4plusclientMgr& operator = (const CLog4plusclientMgr&);

	std::map<u32, std::string>				m_mapClientInfo;

	static CLog4plusclientMgr				s_cLog4plusClientMgr;
};

API void showlogserver();
API void help();
API void ver();

u32 GetSelfTaskId();

#endif//_LOG4CPLUS_SERVER_H_
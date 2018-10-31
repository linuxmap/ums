#ifndef _CONVERT_H_
#define _CONVERT_H_

#include "common.h"
#include "struct.pb.h"


void ConvertViewTypeToPB(const EmViewType tReq, pbmsg::EmViewType& tPbReq);
void ConvertViewReqToPB(const TViewReq tReq, pbmsg::TViewReq& tPbReq);


void ConvertViewTypeFromPB(const pbmsg::EmViewType tPbReq, EmViewType& tReq);
void ConvertViewReqFromPB(const pbmsg::TViewReq tPbReq, TViewReq& tReq);

#endif //_CONVERT_H_
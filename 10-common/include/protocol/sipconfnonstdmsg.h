#ifndef _SIPCONFNONSTDMSG_H
#define _SIPCONFNONSTDMSG_H

//���������Ϣ
enum EmSipConfCtrlMsgType
{
	h_conf_invalidInterface		= 0,
	h_conf_nonstandard			= 1,//sip���xml��Ϣ͸��
	h_chan_flowControl	        = 2,
	h_chan_fastupdate           = 3
};

//�ŵ�������Ϣ
enum EmSipChanCtrlMsgType 
{
	h_chan_invalidInterface = 0,
	h_chan_videofastupdate,
	h_chan_flowControlCmd,
	h_chan_flowControlInd,
	h_chan_fastupdatewithoutid,
};

//FECC������Ϣ
enum EmFeccCtrlMsgType
{
	h_fecc_bind = 0,
	h_fecc_send_msg,
	h_fecc_open_chan,
	h_fecc_set_streamid,
	h_fecc_close_chan,
	h_fecc_keep_alive,
};

#endif 



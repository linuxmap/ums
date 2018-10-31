/********************************************************************
ģ����:      �������̨������Կ�
�ļ���:      McsGuiTestCom.h
����ļ�:    
�ļ�ʵ�ֹ��� �������̨�궨��
���ߣ�       ���
�汾��       3.5
------------------------------------------------------------------------
�޸ļ�¼:
��		��	�汾	�޸���	�߶���	�޸�����
2004/11/22	3.5		���	����
2004/08/03	4.0		����	�޸�    ����4.0�µ�����
2004/09/21	4.0		����	�޸�    ����4.0�µ�����
*********************************************************************/
#if _MSC_VER	> 1000
#pragma	once
#endif	// _MSG_VER > 1000

#include "mcustruct.h"
#include "umconst.h"


//������ԴIDȡ��ԭ�������̨resource.h�е�id
//	�˵���ԴID
//	��¼������ԴID------------------------------------------------------------
#define IDC_CB_MCU                      202
#define IDC_ET_USERNAME                 255
#define IDC_ET_PASSWORD                 256
#define IDC_BTN_SETUP                   271

const s32 IDC_CLOSE_BTN =				272;

//  ��½���ý���
#define IDC_CONFIGINFO_LIST             294
#define IDC_ADDMCU_BTN                  4
#define IDC_EDITMCU_BTN                 5
#define IDC_DELMCU_BTN                  6
#define IDC_MCUNAME_EDIT                292
#define IDC_MCUIP                       296
#define IDC_MONITOR_CK                  298


//	��������ԴID-------------------------------------------------------------
#define IDD_MAIN                        201
#define IDC_CONNECT                     203
#define IDC_HANGUP                      204
#define IDC_MCU_CB                      305
#define IDC_CONFMANAGE_BTN              321
#define IDC_SIMCONF_BTN                 322
#define IDC_CONFWATCH_BTN               323
#define IDC_SYSMANAGE_BTN               324
#define IDC_DEVMANAGE_BTN               282     // ������MCU����ť
#define IDC_HELP_ST                     460

//	���������ԴID-----------------------------------------------------------
#define IDC_WARNINFO                    299

//	ģ��᳡������ԴID-------------------------------------------------------
#define IDC_CONFLIST_CB                 310
#define IDC_PLATFORM_LIST               247
#define IDC_AUDIENCE_LIST               248
#define IDC_PLATFORM_TREELIST           667
#define IDC_AUDIENCE_TREE               669
#define IDC_CONFSETTING_BTN             249
#define IDC_CONFCALLING_BTN             250
#define IDC_CONFPOLL_BTN                251
#define IDC_CONFMESSAGE_BTN             252
#define IDC_CONFEND_BTN                 410
#define IDC_QUIET_CK                    260
#define IDC_MUTE_CK                     262
#define IDC_LEFTMOVE_BTN                272
#define IDC_RIGHTMOVE_BTN               271
#define IDC_SIM_VIDEO1                  430
#define IDC_SIM_VIDEO2                  431
#define IDC_SIM_VIDEO3                  432
#define IDC_SIM_VIDEO4                  433
#define IDC_SIM_VIDEO5                  434
#define IDC_SIM_VIDEO6                  435
#define IDC_SIMVIEWBIG_BTN              274
#define IDC_SIMVIEWSMALL_BTN            275
#define IDC_SIMVIEWTREE_BTN             276
#define IDC_LOCALQUIET_BTN              273
#define IDC_LOCALCANCELQUIET_BTN        279
#define IDC_LOCALMUTE_BTN               277
#define IDC_LOCALCANCELMUTE_BTN         278

//	���ջ��������ԴID-------------------------------------------------------
#define IDC_TODAYCONF_LIST              210
#define IDC_TODAYCONF1_BTN              211
#define IDC_MODMANAGE1_BTN              212
#define IDC_CONFLIST1_BTN               213
#define IDC_TODAYCONF2_BTN              242
#define IDC_MODMANAGE2_BTN              243
#define IDC_CONFLIST2_BTN               244
#define IDC_TODAYCONF3_BTN              206
#define IDC_MODMANAGE3_BTN              207
#define IDC_CONFLIST3_BTN               208

//	�����б������ԴID-------------------------------------------------------
#define IDC_CONFINFO_LIST               209
#define IDC_CREATECONF_BTN              210
#define IDC_EDITCONF_BTN                214

//  ������������Դ
#define IDC_BTN_WIZNEXT                 902
#define IDC_CONFMOD_LIST                352

#define IDC_RDO_STARTINSTANT            747
#define IDC_RDO_STARTTIME               748
#define IDC_STARTDATE_DTP               353
#define IDC_STARTTIME_DTP               354

//	����ģ�������ԴID-------------------------------------------------------

// ����ģ����������ԴID---------------------------------------------------
#define IDC_MODINFO_LIST                412

#define IDC_BTN_BASICDETAIL             272
#define IDC_BTN_MEDIADETAIL             274
#define IDC_BTN_MTDETAIL                275

#define IDC_CREATEMOD_BTN               361
#define IDC_CANCELCREATE_BTN            271
#define IDC_EDITMOD_BTN                 214
#define IDC_CANCELMODIFY_BTN            273
#define IDC_SAVEMOD_BTN                 215
#define IDC_DELMOD_BTN                  216
#define IDC_SOONHOLD_BTN                217
#define IDC_BOOKHOLD_BTN                218
#define IDC_COPYMOD_BTN                 219

#define IDC_CONFNAME_EDIT               220
#define IDC_CONFE164_EDIT               245
#define IDC_BITRATE_CB                  669
#define IDC_CONFHOUR_EDIT               226
#define IDC_CONFMINUTE_EDIT             228
#define IDC_CK_ENDMANUAL                263

#define IDC_MAINVFMT_CB                 853
#define IDC_MAINRES_CB                  852
#define IDC_MAINAFMT_CB                 854
#define IDC_CB_MAINFR                   857

#define IDC_MT_LIST                     443


// ������Ϣ���������ԴID---------------------------------------------------
#define IDC_BTN_BITRATEADV              272
#define IDC_BTN_BITRATEDEFAULT          271
#define IDC_CK_DOUBLERATE               260
#define IDC_CK_BRDLOWRATE               262
#define IDC_LOWBITRATE_CB               670

#define IDC_BTN_MISC                    273


//	����ģ��߼��ӽ��������ԴID--------------------------------------------

#define IDC_WZD_CASCADEMODE_CK          672

#define IDC_CONFMUTE_CK                 723
#define IDC_DATACONF_CK                 266
#define IDC_QOS_CK                      519
#define IDC_WIZUNIFORMMODE_CK           735
#define IDC_WDRETRANSFER_CK             260
#define IDC_WDVIDEOPRIORITY_CK          267
#define IDC_WDMULTIBROADCAST_CK         342
#define IDC_ADAPTER_CK                  264
#define IDC_DISCUSS_CK                  265
#define IDC_WDAUTOEND_CK                268

#define IDC_OPENMODE_CB                 202
#define IDC_ENCRYPTTRANS_CB             848
#define IDC_CONFPWDCFM_ET               845
#define IDC_CONFPWD_ET                  846
#define IDC_CONFCTRL_CK                 262

#define IDC_DATACONF_IP                 300
#define IDC_BTN_CALLCFG                 939

//  ý�������ӽ��������ԴID---------------------------------------------------
#define IDC_SECVFMT_CB                  856
#define IDC_SECRES_CB                   260
#define IDC_SECAFMT_CB                  255
#define IDC_CB_SECFR                    858

#define IDC_DSTREAMTYPE_CB              759
#define IDC_DSTREAMRES_CB               261
#define IDC_CB_DSFR                     859

#define IDC_SENSITIVITY_CB              202
#define IDC_SPEAKERSRC_CB               647
#define IDC_SPEAKERAUDIO_CK             855

#define IDC_ET_DELAYTIME                961


// �ն�ѡ���ӽ���
#define IDC_MT_LIST                     443
#define IDC_MTALIAS_ET                  857

#define IDC_DELMT_BTN                   235
#define IDC_ADDTOADDR_CK                520
#define IDC_ADDRBOOK_BTN                241
#define IDC_ADDMT_BTN                   232
#define IDC_ADDH320MT_BTN               233

#define IDC_BTN_CALLTYPECFG             863
#define IDC_BTN_VMPCFG                  864


#define IDD_MODVMP                      532
#define IDD_MODTVWALL                   531


// VMP �ӶԻ��������ԴID---------------------------------------------------
#define IDC_CK_ENABLEVMP                261
#define IDC_WDBRD_CK                    260

#define IDC_VMPSTYLE_CB                 202
#define IDC_CB_VMPSCHEMA                955

#define IDC_VMP_BTN1                    272
#define IDC_VMP_BTN2                    271
#define IDC_VMP_BTN3                    273
#define IDC_VMP_BTN4                    274
#define IDC_VMP_BTN5                    275
#define IDC_VMP_BTN6                    276
#define IDC_VMP_BTN7                    277
#define IDC_VMP_BTN8                    278
#define IDC_VMP_BTN9                    279
#define IDC_VMP_BTN10                   561
#define IDC_VMP_BTN11                   562
#define IDC_VMP_BTN12                   563
#define IDC_VMP_BTN13                   564
#define IDC_VMP_BTN14                   565
#define IDC_VMP_BTN15                   566
#define IDC_VMP_BTN16                   567



// TVWALL �ӶԻ��������ԴID---------------------------------------------------
#define IDC_CK_ENABLETVWALL             866
#define IDC_CB_TVWALL                   202

#define IDC_WDTVWALL_BTN1               272
#define IDC_WDTVWALL_BTN2               271
#define IDC_WDTVWALL_BTN3               273
#define IDC_WDTVWALL_BTN4               274
#define IDC_WDTVWALL_BTN5               275
#define IDC_WDTVWALL_BTN6               277
#define IDC_WDTVWALL_BTN7               276
#define IDC_WDTVWALL_BTN8               278
#define IDC_WDTVWALL_BTN9               279
#define IDC_WDTVWALL_BTN10              553
#define IDC_WDTVWALL_BTN11              554
#define IDC_WDTVWALL_BTN12              555
#define IDC_WDTVWALL_BTN13              556
#define IDC_WDTVWALL_BTN14              557
#define IDC_WDTVWALL_BTN15              558
#define IDC_WDTVWALL_BTN16              559




// �ն˸߼����ý��������ԴID---------------------------------------------------
#define IDC_MTBITRATE_CK                263
#define IDC_MTBITRATE_ET                258

#define IDC_MTCALL_CB                   329
#define IDC_CALLNUM_ET                  259
#define IDC_CALLTIMER_ET                261





//	���������򵼽�����ԴID-------------------------------------------------------
//  ����������ܶ�Ի���
//  ������mcs4.0�ѷ���

#define ID_WIZARD_OK                (WM_USER + 538)
#define ID_WIZARD_CANCEL            (WM_USER + 539)
#define ID_WIZARD_BACK              (WM_USER + 540)
#define ID_WIZARD_NEXT              (WM_USER + 541)
#define ID_WIZARD_FINISH			(WM_USER + 542)
#define ID_WIZARD_APPLY				(WM_USER + 543)
#define ID_WIZARD_CLOSE				(WM_USER + 544)



#define IDC_SELMOD_CK                   260
#define IDC_CONFMOD_LIST                352


#define IDC_WDCONFNAME_EDIT             347
#define IDC_WDCONFE164_EDIT             348
#define IDC_WDBITRATE_COMBO             670
#define IDC_SECBITRATE_CB               255

#define IDC_DOUBLEBITRATE_CK            677
#define IDC_BROADLOWBITRATE_CK          678
#define IDC_SAVEASDEFAULT_BTN           271
#define IDC_WDBITRATEDETAIL_BTN         272

//#define IDC_START_CK                    260
#define IDC_STARTDATE_DTP               353
#define IDC_STARTTIME_DTP               354
#define IDC_ENDDATE_DTP                 355
#define IDC_ENDTIME_DTP                 356
// #define IDC_END_CK                      261

#define IDC_RDO_STARTINSTANT            747
#define IDC_RDO_ENDMANUAL               749


//	��ؽ�����ԴID-----------------------------------------------------------
#define IDC_CONF_CB                     202
#define IDC_MT_LSIT                     280
#define IDC_VIEWONE_BTN                 272
#define IDC_VIEWTWO_BTN                 273
#define IDC_VIEWFOUR_BTN                274
#define IDC_VIEWSIX_BTN                 275
#define IDC_VIEWEIGHT_BTN               276
#define IDC_VIEWNINE_BTN                277
#define IDC_MONITOR_VIDEO1              414
#define IDC_MONITOR_VIDEO2              415
#define IDC_MONITOR_VIDEO3              416
#define IDC_MONITOR_VIDEO4              417
#define IDC_MONITOR_VIDEO5              418
#define IDC_MONITOR_VIDEO6              419
#define IDC_MONITOR_VIDEO7              420
#define IDC_MONITOR_VIDEO8              421
#define IDC_MONITOR_VIDEO9              422

//	ȷ����Ϣ������ԴID-------------------------------------------------------
#define IDC_CONFIRM_INFO                326



//	�����ն˽�����ԴID-------------------------------------------------------
//#define IDC_CALLMT_CB                   382
//#define IDC_ALIAS_EDIT                  383
#define IDC_ADDONEMT_BTN                271
//#define IDC_ADDMT_BTN                   232
#define IDC_CALLMT_EDIT                 255
//#define IDC_ADVANCE_BTN                 273
#define IDC_ADDTOADDR_CK                520
#define IDC_ADDR_BTN                    271
//#define IDC_ADDRBOOK_BTN                241
#define IDC_QUIT_CK                     260
#define IDC_MTBITRATE_CK                263
#define IDC_MTBITRATE_ET                258
#define IDC_BTN_ADDH320MT               273

// ���H320�ն˽�����ԴID
#define IDC_EDIT_LAYER                  255
#define IDC_EDIT_SLOT                   256
#define IDC_EDIT_CHANNEL                257
#define IDC_CHK_ADDTOADDR               260
#define IDC_CHK_MTBITRATE               742
#define IDC_EDIT_MTBITRATE              744

//	�ӵ�ַ�������ն˽�����ԴID-----------------------------------------------
#define IDC_MTINADDR_LIST               280
#define IDC_GROUPMT_LIST                280
#define IDC_ADDONE_BTN                  409
#define IDC_MT_LIST                     443
#define IDC_ALIASTYPE_CB                203

//	�Ҷ��ն˽�����ԴID-------------------------------------------------------
#define IDC_NOTIFY_MT                   260

//	�ն�ѡ��������ԴID-------------------------------------------------------
#define IDC_MTSELMT_CB                  203
#define IDC_MTSELTYPE_CB                404

//	�޸����������ԴID-------------------------------------------------------
#define IDC_OLD_CONFPWD_EDIT            250
#define IDC_CONFPWD_EDIT                249
#define IDC_CONFIRMPWD_EDIT             412

//	������ƽ�����ԴID-------------------------------------------------------
#define IDC_CONFCTRL_CB                 411

//	������������ԴID-------------------------------------------------------
#define IDC_DEFAULT_CK                  260

//	ȷ�Ͼ����������ԴID-----------------------------------------------------
#define IDC_CONFPWD_EDIT                249

//	ϵͳ���������ԴID-------------------------------------------------------
#define IDC_SYSADD_BTN                  285
#define IDC_SYSDEL_BTN                  286
#define IDC_SYSEDIT_BTN                 287
#define IDC_USERDEFINE_BTN              290

//	��ַ�����������ԴID-----------------------------------------------------
#define IDC_ADDRGROUP_LIST              280
#define IDC_ADDRESSBOOK_LIST            291
#define IDC_ADDENTRY_BTN                271
#define IDC_ADDENTRYH320_BTN            278
#define IDC_EDITENTRY_BTN               273
#define IDC_DELENTRY_BTN                274
#define IDC_ADDGROUP_BTN                275
#define IDC_EDITGROUP_BTN               276
#define IDC_DELGROUP_BTN                277
#define IDC_ADDMEMBER_BTN               232
#define IDC_DELMEMBER_BTN               235
#define IDC_ADDMEMBER_BTN               232
#define IDC_DELMEMBER_BTN               235

//	�û����������ԴID-------------------------------------------------------
#define IDC_USERMANAGE_LIST             288

//	����ϳɽ�����ԴID-------------------------------------------------------
#define IDC_MERGEMODE_CB                202
#define IDC_BROADCAST_CK                260
#define IDC_STARTVMP_BTN                288
#define IDC_STOPVMP_BTN                 289
#define IDC_VMPER_BTN1                  272
#define IDC_VMPER_BTN2                  273
#define IDC_VMPER_BTN3                  274
#define IDC_VMPER_BTN4                  275
#define IDC_VMPER_BTN5                  276
#define IDC_VMPER_BTN6                  277
#define IDC_VMPER_BTN7                  278
#define IDC_VMPER_BTN8                  279
#define IDC_VMPER_BTN9                  280
#define IDC_VMPER_BTN10                 281
#define IDC_VMPER_BTN11                 282
#define IDC_VMPER_BTN12                 283
#define IDC_VMPER_BTN13                 284
#define IDC_VMPER_BTN14                 285
#define IDC_VMPER_BTN15                 286
#define IDC_VMPER_BTN16                 287



//	����ǽ������ԴID---------------------------------------------------------
#define IDC_TVWALL_LIST                 451
#define IDC_TVWALL_BTN1                 272
#define IDC_TVWALL_BTN2                 273
#define IDC_TVWALL_BTN3                 274
#define IDC_TVWALL_BTN4                 275
#define IDC_TVWALL_BTN5                 276
#define IDC_TVWALL_BTN6                 277
#define IDC_TVWALL_BTN7                 278
#define IDC_TVWALL_BTN8                 279
#define IDC_TVWALL_BTN9                 280
#define IDC_TVWALL_BTN10                281
#define IDC_TVWALL_BTN11                282
#define IDC_TVWALL_BTN12                283
#define IDC_TVWALL_BTN13                284
#define IDC_TVWALL_BTN14                285
#define IDC_TVWALL_BTN15                286
#define IDC_TVWALL_BTN16                287

//	���ƻ���������ԴID-------------------------------------------------------
#define IDC_MIXMODE_CB                  208
#define IDC_CONFMIX_START               680
#define IDC_CONFMIX_STOP                681
#define IDC_CONFMIX_CANCEL              206
#define IDC_CONFMIX_BTN1                296
#define IDC_CONFMIX_BTN2                297
#define IDC_CONFMIX_BTN3                207
#define IDC_CONFMIX_BTN4                222
#define IDC_CONFMIX_BTN5                219
#define IDC_CONFMIX_BTN6                221
#define IDC_CONFMIX_BTN7                230
#define IDC_CONFMIX_BTN8                315
#define IDC_CONFMIX_BTN9                316
#define IDC_CONFMIX_BTN10               317
#define IDC_CONFMIX_BTN11               318
#define IDC_CONFMIX_BTN12               319
#define IDC_CONFMIX_BTN13               320
#define IDC_CONFMIX_BTN14               328
#define IDC_CONFMIX_BTN15               330
#define IDC_CONFMIX_BTN16               331

//	����Ϣ������ԴID---------------------------------------------------------
#define IDC_SHORTMSG_EDIT               408
#define IDC_CONFMT_LIST                 390
#define IDC_ADDONE_BTN                  409
#define IDC_POLLMT_LIST                 388
#define IDC_MSG_TIMES                   448
#define IDC_ROLLTYPE_COMBO              202
#define IDC_ROLLSPEED_COMBO             552
#define IDC_SAVEDMSG_CB                 590
#define IDC_SELFILE_BTN                 275
#define IDC_SAVEMSG_BTN                 276
#define IDC_DELMSG_BTN                  277
#define IDC_SELMSG_BTN                  278

//	������ѯ������ԴID-------------------------------------------------------
#define IDC_DEFPOLLINTERVAL_CK          260
#define IDC_DEFPOLLINTERVAL_EDIT        389
#define IDC_WITHAUDIO_CK                262
#define IDC_CONFMT_TREE                 715
#define IDC_POLLMT_LIST                 388
#define IDC_SELONE_BTN                  391
#define IDC_STARTPOLL_BTN               3
#define IDC_STOPPOLL_BTN                5
#define IDC_ET_POLLTIMES                255

// ����ǽ��ѯ������ԴID-------------------------------------------------------
#define IDC_CB_TVWALL2                  203
#define IDC_CB_PICTURE                  204
#define IDC_CONFMT_LIST                 390
#define IDC_POLLMT_LIST                 388
#define IDC_DEFPOLLINTERVAL_CK          260
#define IDC_DEFPOLLINTERVAL_EDIT        389
#define IDC_ET_POLLTIMES                255

//	�������������ԴID-------------------------------------------------------
#define IDC_CONFMT_TREE                 715
#define IDC_ADDCALLING_BTN              272
#define IDC_ADDCALLED_BTN               271

//	¼�������ԴID-----------------------------------------------------------
#define IDC_RECORDER                    202
#define IDC_START_BTN                   395
#define IDC_STOP_BTN                    396
#define IDC_PAUSE_BTN                   397
const s32 IDC_CLOSE = 272;

//	¼���ļ�ѡ����ԴID-------------------------------------------------------
#define IDC_FILENAME_EDIT               401
#define IDC_RECMODE_CK                  260
#define IDC_RECLOWBITRATE_CK            263
#define IDC_PUBTYPE_CB                  402
#define IDC_PUBSECRET_CK                262

//	���������ԴID-----------------------------------------------------------
#define IDC_RECORDER                    202
#define IDC_START_BTN                   395
#define IDC_STOP_BTN                    396
#define IDC_PAUSE_BTN                   397
#define IDC_PLAYER_SLD                  269

//  �����ļ�ѡ����ԴID-------------------------------------------------------
#define IDC_FILENAME_CB                 403



//	¼���豸������ԴID-------------------------------------------------------
#define IDC_RECORDERLIST_FILELIST       280
#define IDC_RECORDERLIST_PUBLISH        272
#define IDC_RECORDERLIST_CANCEL         271
#define IDC_RECORDERLIST_DELETE         273

//	��ַ����Ϣ������ԴID-----------------------------------------------------
#define IDC_ENTRYNAME_EDIT              255
#define IDC_MT_IP                       300
#define IDC_MT_E164                     257
#define IDC_MT_H323                     259
#define IDC_MTRATE_EDIT                 258

//	�û���Ϣ������ԴID-------------------------------------------------------
#define IDC_USERNAME_EDIT               290
#define IDC_PASSWORD_EDIT               291
#define IDC_CONFIRMPASSWORD_EDIT        292
#define IDC_FULLNAME_EDIT               301
#define IDC_USERTYPE_CB                 202
#define IDC_USERNOTE_EDIT               304



//	ȷ�����������ԴID-------------------------------------------------------
#define IDC_CONFPWD_EDIT                249

//	�ӳ����������ԴID-------------------------------------------------------
#define IDC_DELAYTIME_EDIT              406

//	��������ʱ�������ԴID---------------------------------------------------
#define IDC_SENSITIVITY_CB              202
#define IDC_ACTTIME_EDIT                255

//	�ն˷������ʽ�����ԴID---------------------------------------------------
#define IDC_MTBITRATE_EDIT              405

//	���������ԴID-----------------------------------------------------------
#define IDC_SAVEVIDEOSCHEME_BTN         272
#define IDC_SAVEAUDIOSCHEME_BTN         271
#define IDC_VIDEOSCHEME_CB              202
#define IDC_AUDIOSCHEME_CB              518
#define IDC_MAXTRIX_CLOSE               273
#define INVIDEO_BTN_BASE_ID     5000
#define OUTVIDEO_BTN_BASE_ID    5100
#define INAUDIO_BTN_BASE_ID     5200
#define OUTAUDIO_BTN_BASE_ID    5300

//	���󷽰�������ԴID---------------------------------------------------------
#define IDC_SCHEME_CB                   202
#define IDC_SCHEME_EDIT                 255

//	����˿�ͼ�����ý�����ԴID-------------------------------------------------
#define IDC_MATRIX_EDIT                 255
#define IDC_MATRIXINFO_LIST             280

//	����ͷ������ԴID-----------------------------------------------------------
#define IDC_UP_BTN                      272
#define IDC_LEFT_BTN                    273
#define IDC_RIGHT_BTN                   274
#define IDC_DOWN_BTN                    271
#define IDC_AUTOFOCUS_BTN               427
#define IDC_FOCUSINC_BTN                428
#define IDC_FOCUSDEC_BTN                429
#define IDC_ZOOMINC_BTN                 430
#define IDC_ZOOMDEC_BTN                 431
#define IDC_BRIGHTNESSINC_BTN           432
#define IDC_BRIGHTNESSDEC_BTN           433
#define IDC_POSITION_CB                 202
#define IDC_SAVEPOS_BTN                 438
#define IDC_LOADPOS_BTN                 439
#define IDC_CAMERACLOSE_BTN             576

//	�����������ԴID-----------------------------------------------------------
#define IDC_ADDRCONFGROUP_EDIT          255
#define IDC_ADDRMCUIP_IP                300

//	������ѡ����Ŀ������ԴID---------------------------------------------------
#define IDC_AVAILABLEENTRY_LIST         280
#define IDC_ADDENTRY_LIST               704
#define IDC_ADDONE_BTN                  409

//	�����Ϣ������ԴID---------------------------------------------------------
#define IDC_VIDEOINFO_ST                425
#define IDC_AUDIOINFO_ST                426

//	ץȡͼƬ������ԴID---------------------------------------------------------
#define IDC_PATHNAME_EDIT               458
#define IDC_SAVE_BTN                    272

//	�ն���ƵԴ�˿��л�������ԴID-----------------------------------------------
#define IDC_SCHEME_CB                   202
#define IDC_LOADSCHEME_BTN              271
#define IDC_SAVESCHEME_BTN              273
#define IDC_DELSCHEME_BTN               274
#define IDC_VIDEOSRCPORT_COMBO          714
#define IDC_CONFMT_LIST                 390
#define IDC_SELMT_LIST                  713
#define IDC_SELONE_BTN                  391

//  ���淽��������ԴID---------------------------------------------------------
#define IDC_NAME_EDIT                   301

//  �û����ý�����ԴID---------------------------------------------------------
#define IDC_REGGK_CK                    720
#define IDC_CURREGIP_IP                 721
#define IDC_REGGK_BTN                   275
#define IDC_CALLTYPEVMP_CK              725
#define IDC_CALLTYPECALLER_CK           726
#define IDC_CALLTYPECALLEE_CK           727

#define IDC_CB_LANGSET                  761
#define IDC_BTN_APPLYLANG               276

#define IDC_CK_USERDEFINEDMENU          797
#define IDC_BTN_MENUCONFIG              275


//  ��ƵԴ��ѯ������ԴID-------------------------------------------------------
#define IDC_MTVIDEOSRCPOLL_POLL_LIST    280
#define IDC_MTVIDEOSRCPOLL_SCHEME_CB    202
#define IDC_MTVIDEOSRCPOLL_LOADSCHEME_BTN 277
#define IDC_MTVIDEOSRCPOLL_SAVESCHEME_BTN 271
#define IDC_MTVIDEOSRCPOLL_DELSCHEME_BTN 273
#define IDC_MTVIDEOSRCPOLL_START_BTN    274
#define IDC_MTVIDEOSRCPOLL_STOP_BTN     275
#define IDC_MTVIDEOSRCPOLL_PUASE_BTN    276

#define IDC_VIDEOSRCPOLLMT_TIME_EDIT    255
#define IDC_VIDEOSRCPOLLMT_ALLPORT_LIST 280
#define IDC_SELONE_BTN                  391



// MCU �����л���ť��ԴID-------------------------------------------------------
#define IDC_MCUBASIC_BTN                793
#define IDC_MCUNETWORK_BTN              792
#define IDC_MCUCHIP_BTN                 794
#define IDC_MCUDEV_BTN                  795
#define IDC_MCUADDRBOOK_BTN             796
#define IDC_MCUUSER_BTN                 797

//	�豸���������ԴID-------------------------------------------------------
#define IDC_DEVMANGE_LIST               281


// MCU������Ϣ������ԴID-------------------------------------------------------
#define IDC_BTN_REFRESHMCU              277
#define IDC_BTN_SYNTIME                 272
#define IDC_BTN_CONFIG                  273
#define IDC_BTN_REBOOTMCU               276


// MCU���ý�����ԴID-------------------------------------------------------
#define IDC_TAB_MCUCFG                  860

#define IDC_BTN_MCU_NETWORKSAVE         272
#define IDC_BTN_MCUWIZ                  897

// ���öԻ�ҳ
#define IDD_MCUNETSHEET                 657
#define IDD_MCUQOSSHEET                 654
#define IDD_MCUSNMPSHEET                655
#define IDD_MCUNETMISCSHEET             658

// �����򵼶Ի���
#define IDC_BTN_WIZPREV                 901
#define IDC_BTN_WIZNEXT                 902

// Step 1
#define IDC_RDO_MCUWIZ1                 898
#define IDC_RDO_MCUWIZ2                 899
#define IDC_RDO_MCUWIZ3                 900

// Step 2
#define IDC_IP_MCUIP                    300
#define IDC_IP_MCUMASK                  301
#define IDC_IP_MCUGATEWAY               302

// Step 3
#define IDC_CK_MCU_REGGK                262
#define IDC_IP_MCUGK                    304
#define IDC_ET_MCUH323ID                255
#define IDC_ET_MCUE164                  265

// Step 4
#define IDC_CK_REBOOT                   904

// Step 5
#define IDC_ET_FILENAME                 255
#define IDC_BTN_BROWSE                  905

// Net Sheet
#define IDC_IP_MCUIP                    300
#define IDC_IP_MCUMASK                  301
#define IDC_IP_MCUGATEWAY               302

#define IDC_CK_MCU_REGGK                262
#define IDC_IP_MCUGK                    304
#define IDC_ET_GKPORT2                  260
#define IDC_ET_MCUH323ID2               261
#define IDC_ET_MCUE164                  265

#define IDC_IP_MCU_BRD                  781
#define IDC_ET_MCU_BRDPORT              255
#define IDC_ET_MCU_DATAPORT             256
#define IDC_ET_MCU_H225PORT             257
#define IDC_ET_MCU_MAXMT                258

// QoS
#define IDC_CB_MCU_QOSTYPE              205

#define IDC_CK_LOWDELAY                 944
#define IDC_CK_HIGHRELIABILITY          945
#define IDC_CK_HIGHTHROUGHPUT           946
#define IDC_CK_LOWEXPENSE               947

#define IDC_ET_MCU_QOSIPAUDIO           256
#define IDC_ET_MCU_QOSIPVIDEO           259
#define IDC_ET_MCU_QOSIPDATA            257
#define IDC_ET_MCU_QOSIPCMD             258
#define IDC_BTN_MCU_QOSDEFAULT          839

// Snmp
#define IDC_LS_SNMP                     280
#define IDC_BTN_MCU_SNMPADD             271
#define IDC_BTN_MCU_SNMPEDIT            274
#define IDC_BTN_MCU_SNMPDEL             273

// Snmp Edit Dlg
#define IDC_IP_MCU_SNMPIP               787
#define IDC_ET_MCU_SNMPRCOMM            275
#define IDC_ET_MCU_SNMPWCOMM            276
#define IDC_ET_MCU_SNMPGSPORT           277
#define IDC_ET_MCU_SNMPTRAPPORT         278

// misc
#define IDC_CK_SAVEBW                   263
#define IDC_ET_MCUWIZ_CHAINCK           256
#define IDC_ET_MCUWIZ_CHAINCKTIMES      260
#define IDC_ET_MCUWIZ_MTREFRATE         257
#define IDC_ET_MCU_AUDREFRATE           258
#define IDC_ET_MCU_VIDREFRATE           259

#define IDC_CK_MCU_MPC                  264
#define IDC_CK_MCU_MPCSTACK             265

#define IDC_CB_MCU_SYMMODE              202
#define IDC_ET_MCU_DRI                  261
#define IDC_ET_MCU_E1                   269

#define IDC_CK_DCSERVER                 948
#define IDC_IP_DCS                      301

#define IDC_BTN_MISCDEFAULT             909

// vmp config sheet
#define IDC_CB_VMPSCHEMA                955
#define IDC_BTN_SAVE                    962
#define IDC_BTN_RENAME                  931

#define IDC_CP_BK                       934
#define IDC_CP_MT                       935
#define IDC_CP_CM                       936
#define IDC_CP_SP                       937

/*
#define IDC_CB_VMPCONFIG_FONT           202
#define IDC_CB_VMPCONFIG_ALPHA          203
#define IDC_CB_VMPCONFIG_SIZE           204
#define IDC_BTN_TEXTFC                  276
#define IDC_BTN_TEXTBG                  277
#define IDC_CK_USECFG                   260
#define IDC_BTN_SELBG                   271
#define IDC_BTN_SELMT                   273
#define IDC_BTN_SELCM                   274
#define IDC_BTN_SELSP                   275
*/


// MCU�������ý�����ԴID-------------------------------------------------------
#define IDC_TAB_MCUCHIP                 860
#define IDC_LS_CHIP                     280
#define IDC_LS_CHIPMODULE               885
#define IDC_BTN_CHIPADD                 274
#define IDC_BTN_CHIPCFG                 272
#define IDC_BTN_CHIPDEL                 273
#define IDC_BTN_CHIPREBOOT              278


#define IDC_BTN_MODULEADD               275
#define IDC_BTN_MODULEDEL               276
#define IDC_BTN_MODULECFG               277

#define IDC_LS_CHIPMISC                 281
#define IDC_BTN_RECADD                  272
#define IDC_BTN_RECEDIT                 273
#define IDC_BTN_RECDEL                  274


#define IDC_BTN_MCU_CHIPSAVE            839

// �����������ô���
#define IDC_CB_CHIP                     202
#define IDC_ET_CHIPLAYER                255
#define IDC_ET_CHIPSLOT                 256
#define IDC_IP_CHIP                     300
#define IDC_CB_LANIF                    867
#define IDC_CK_CHIPBRD                  264


// ��������ģ�����ô���
#define IDC_CB_MODULE                   886
#define IDC_ET_CHIPMODUID               255
#define IDC_ET_CHIPMODUAlIAS            259
#define IDC_ET_MCUSTARTPORT             256
#define IDC_ET_SWITCHBRDIDX             258
#define IDC_ET_RUNNINGBRDIDX            260
#define IDC_ET_RECVSTARTPORT            261
#define IDC_CK_MAP0                     262
#define IDC_CK_MAP1                     263
#define IDC_CK_MAP2                     264
#define IDC_CK_MAP3                     265
#define IDC_CK_MAP4                     266
#define IDC_ET_MAXMIXCHNL               868
#define IDC_CB_VENCODEPIPE              202
#define IDC_IP_RECORDER                 300
#define IDC_BTN_PRSSET                  271

// �����ش�����
#define IDC_ET_MCU_RETIME1              267
#define IDC_ET_MCU_RETIME2              268
#define IDC_ET_MCU_RETIME3              269
#define IDC_ET_MCU_RETIME4              270

#define IDC_BTN_PRSDEFAULT              910

//	������������, ȡ��McsCom.h
#define VAC_BLUNTEST	30
#define VAC_BLUNTER		20
#define VAC_ORDINARY	15
#define VAC_SENSITIVER	10
#define VAC_SENSITIVEST	5

//	��ѯ����ն���Ϣ, ȡ��McsCom.h
#define WM_CODEC_QUERY_MT			(WM_USER + 552)
#define WM_CODEC_MTWITHAUDIO        (WM_USER + 553)
#define WM_CODEC_MTMUTE             (WM_USER + 554)
#define WM_CODEC_MTREAL             (WM_USER + 555)



// ����MCU�����еĳ���, ȡ��McsCom.h / mcuconst.h

// ����ͬ��ģʽ
#define MCUSYNMODE_VIBRATE  (u8)0   // ������
#define MCUSYNMODE_TRACK    (u8)1   // ����


// QoS ����
#define MCUQOS_SERV         (u8)0
#define MCUQOS_IP           (u8)1


#define IPSERVICETYPE_NONE              0   //ȫ����ѡ
#define IPSERVICETYPE_LOW_DELAY         1   //��С�ӳ�
#define IPSERVICETYPE_HIGH_THROUGHPUT   2   //���������
#define IPSERVICETYPE_HIGH_RELIABILITY  4   //��߿ɿ���
#define IPSERVICETYPE_LOW_EXPENSE       8   //��ͷ���


// ��������
#define MCUCHIP_APU  (u8)0
#define MCUCHIP_VPU  (u8)1
#define MCUCHIP_DEC5 (u8)2
#define MCUCHIP_CRI  (u8)3
#define MCUCHIP_DRI  (u8)4
#define MCUCHIP_MMP  (u8)5
#define MCUCHIP_MPC  (u8)0x0F
#define MCUCHIP_NORMAL (u8) 0xF0  // lib�ڲ���,��ʾ��MPC��

// ����ģ������, From mcsstruct.h
#define MIXER_MASK          (u8)0x01
#define TVWALL_MASK         (u8)0x02
#define ADAPTER_MASK        (u8)0x04
#define VMP_MASK            (u8)0x08
#define PRS_MASK            (u8)0x10
#define MULTITVWALL_MASK    (u8)0x20
#define REC_MASK            (u8)0x40 

// ����
#define LANG_CHS     (u8)0
#define LANG_EN      (u8)1

//����LISTCTRL��ʾ��������
#define MAXLEN_DISP_ALIAS           26
#define MAXLEN_NAME                 128
#define CONFCOL_CONFID                  16      //  �����

#define MATRIX_MAX_PORT 16
#define MATRIX_PORTNAME_LEN 16


//����õ��ľ���Ϸ���, ��ӡ�����������ļ���������
#define MCSUI_CHECK_HANDLE(hWnd)													\
	if (hWnd == NULL)																\
	{																				\
		CString strName = __FILE__;													\
		int nLeft = strName.ReverseFind('\\');										\
		TRACE("�ļ�%s�е�%d��---�ؼ�����Ƿ�!\n", strName.Mid(nLeft+1), __LINE__);	\
		return FALSE;																\
	}

//���鷵��ֵ
#define MCSUI_CHECK_RET(p)	if (!p)	return FALSE

//�������Ƿ�Ϸ�, ���Ϸ�����Ԥ����ť
#define MCSUI_CHECK_HANDLE_RET(hWnd)												\
	if (hWnd == NULL)																\
	{																				\
		CString strName = __FILE__;													\
		int nLeft = strName.ReverseFind('\\');										\
		TRACE("�ļ�%s�е�%d��---�ؼ�����Ƿ�!\n", strName.Mid(nLeft+1), __LINE__);	\
		MoveBtnClick(hCancelBtn);													\
		return FALSE;																\
	}

//�˳��Ի���
#define MCSUI_QUIT_DIALOG(bQuit, hWnd)												\
	if (bQuit)																		\
	{                                                                               \
		MoveBtnClick(hWnd);	    													\
		return FALSE;															    \
	}

//���ٵ����˵�
#define MCSUI_DESTROY_MENU(p)														\
	if (!p)																			\
	{																				\
		m_cGuiUnit.MouseMove(m_hHelpSt);											\
		m_cGuiUnit.MouseLClick();													\
		return FALSE;																\
	}

//�ȴ�500ms
#define MCSUI_SLEEP_500		m_bOprDelay ? Sleep(500) : NULL

//�ȴ�1s
#define MCSUI_SLEEP_1000	m_bOprDelay ? Sleep(1000) : NULL

//Ϊ��ʵ�ֽ�����������������������ʱ
#define MCSUI_SLEEP_SYS		Sleep(500)

//Ӧ�ó�����
#define MCSUI_APP_TITLE_NAME	_T("�ƴ�Ƽ��������̨4.0")
#define MCSUI_APP_EXE_NAME		_T("mcs.exe")

//ϵͳĬ���û�����
#define MCSUI_DEF_USER		_T("admin")
#define MCSUI_DEF_GROUP		_T("Administrators")

//���嵱ǰ���ڲ�������id
#define MCSUI_POS_INVALID				(BYTE)0	//�Ƿ�ֵ
#define MCSUI_POS_CONFMANAGE			(BYTE)1 //�������
#define MCSUI_POS_SIMCONF				(BYTE)2 //ģ��᳡
#define MCSUI_POS_MONITOR				(BYTE)3 //���
#define MCSUI_POS_SYSMANAGE				(BYTE)4 //ϵͳ����
#define MCSUI_POS_MCUMANAGE				(BYTE)5	//�豸����

//�ӽ���
#define MCSUI_POS_MAN_TODAYCONF			(BYTE)10	//���ջ���
#define MCSUI_POS_MAN_MODMANAGE			(BYTE)11	//ģ�����
#define MCSUI_POS_MAN_CONFLIST			(BYTE)12	//�����б�

#define MCSUI_POS_SYS_LOG				(BYTE)20	//�¼���־
#define MCSUI_POS_SYS_SETTING			(BYTE)21	//����


// ����4.0���� Mcu����
#define MCSUI_POS_MCU_BASIC             (BYTE)24	//������Ϣ
#define MCSUI_POS_MCU_NETWORK           (BYTE)25	//��������
#define MCSUI_POS_MCU_CHIP              (BYTE)26	//������Ϣ
#define MCSUI_POS_MCU_DEV               (BYTE)27	//��������

#define MCSUI_POS_SYS_ADDR				(BYTE)22	//��ַ��
#define MCSUI_POS_SYS_USER				(BYTE)23	//�û�����
//	�ն˲����˵�λ��
#define	MTOP_MENU_ADDMT				0
#define MTOP_MENU_DELMT				1
#define MTOP_MENU_CALLMT			2
#define MTOP_MENU_DROPMT			3
#define MTOP_MENU_SPECCHAIRMAN		5
#define MTOP_MENU_CANCELCHAIRMAN	6
#define MTOP_MENU_SPECSPEAKER		7
#define MTOP_MENU_CANCELSPEAKER		8
#define MTOP_MENU_MTINSPECT			10
#define MTOP_MENU_REC				11
#define MTOP_MENU_BITRATE			12
#define MTOP_MENU_QUIET				13
#define MTOP_MENU_MUTE				14
#define MTOP_MENU_UPDATEALIAS		15
#define MTOP_MENU_VIDEOSRC			16
#define MTOP_MENU_VIDEOSRC1			0
#define MTOP_MENU_VIDEOSRC2			1
#define MTOP_MENU_VIDEOSRC3			2
#define MTOP_MENU_VIDEOSRC4			3
#define MTOP_MENU_VIDEOSRC5			4
#define MTOP_MENU_VIDEOSRC6			5
#define MTOP_MENU_VIDEOSRCS			6
#define MTOP_MENU_MATRIX			7
#define MTOP_MENU_CAMERA			17
#define MTOP_MENU_CALLMODE			18
#define MTOP_MENU_CALLNONE			0
#define MTOP_MENU_CALLTIMER			1
#define MTOP_MENU_ADDTOADDR			19
#define MTOP_MENU_MCUOP             20
#define MTOP_MENU_REFRESHMCU        0
#define MTOP_MENU_LOCKSMCU          1
#define MTOP_MENU_STARTMTC          21      

//	������Ʋ˵�λ��


#define CONFCT_MENU_CREATECONF		0
#define CONFCT_MENU_MODIFYCONF		1
#define CONFCT_MENU_RELEASECONF		2
#define CONFCT_MENU_SAVECONF		3

//	�����趨�˵�λ��
#define CONFST_MENU_DELAY			0
#define CONFST_MENU_CTRL			1
#define CONFST_MENU_PWD				2
#define CONFST_MENU_DISCUSS			3
#define CONFST_MENU_MIX				4
#define CONFST_MENU_MIXSET          5
#define CONFST_MENU_REC				6
#define CONFST_MENU_PLAY			7
#define CONFST_MENU_VAC				8
#define CONFST_MENU_VACSETTING		9
#define CONFST_MENU_VMP				10
#define CONFST_MENU_TVWALL			11
#define CONFST_MENU_VMPTW			12
#define CONFST_MENU_FORCESPEAKER	13
#define CONFST_MENU_VIDEOSRC        14
#define CONFST_MENU_VIDEOSRCPOLL    15


//	����ϳɲ˵�λ��
#define VMP_MENU_STOP				0
#define VMP_MENU_MCSSPEC			2
#define VMP_MENU_CHAIRMAN			3
#define VMP_MENU_SPEAKER			4
#define VMP_MENU_POLL				5
#define VMP_MENU_TWPOLL             7

//	��ز˵�
#define MONITOR_MENU_STOP				0
#define MONITOR_MENU_REAL				1
#define MONITOR_MENU_QUIET				2
#define MONITOR_MENU_INFO				4
#define MONITOR_MENU_FULLSCREEN			5
#define MONITOR_MENU_BACKSCREEN			5
#define MONITOR_MENU_SAVEPIC			6
#define MONITOR_MENU_CAMERA				7

// ģ������ն�������ϯ�����˲˵�
#define MODMTLIST_MENU_CHAIRMAN     0
#define MODMTLIST_MENU_SPEAKER      1
#define MODMTLIST_MENU_DEL          2
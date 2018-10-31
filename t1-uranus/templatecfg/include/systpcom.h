//TPCfg 应用ID
#define AID_TP_CFGDATA 80
#define AID_TP_PROP	(u16)120

//定义文件同步初始化函数
#define EV_TPCFG_INIT_CMD        2001

//更新文件,修改文件持久化等候时间
#define EV_TP_UPDATE_CMD         2002

//立即持久化系统配置
#define EV_TP_SAVE_CMD           2003

//超时持久化系统配置
#define TIMER_SAVE_TP_CFGDATA    2004

//有效值存储
#define EV_TP_VALID_CMD          2005

//导入模板文件
#define EV_TP_UPLOAD_FILE		2006

//导出模板文件
#define EV_TP_DOWNLOAD_FILE		2007

//时间最大值,延迟写
#define SAVE_TIME_OUT	       5000

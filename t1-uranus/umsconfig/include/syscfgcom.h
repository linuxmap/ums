
//CIMtCfg 应用ID
#define AID_UMS_CFGDATA 60
#define AID_UMS_PROP	(u16)120

//定义文件同步初始化函数
#define EV_SYSCFG_INIT_CMD        999

//更新文件,修改文件持久化等候时间
#define EV_MTA_MTAC_UPDATE_CMD 1000

#define EV_MTA_MTAC_UPDATE_CONFTEMPCMD 1001

//立即持久化系统配置
#define EV_MTA_MTAC_SAVE_CMD   1002

//超时持久化系统配置
#define TIMER_SAVE_CFGDATA     1003

//时间最大值
#define SAVE_TIME_OUT	       5000

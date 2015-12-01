/******************************************************************************

                  版权所有 (C), 2005-2015, 国家电网通信与用电技术分公司

 ******************************************************************************
  文 件 名   : gbnx_31_api.h
  版 本 号   : 初稿
  作    者   : liming
  生成日期   : 2013年10月17日
  最近修改   :
  功能描述   : GB/T XXXX.31 2013 主站与采集终端通信协议解析api(C语言)
               该文件给出国家电力能力监测系统技术规范(国标) 第3-1部分
               主(子)站与电力通道信息集中与交互终端通信协议
               相关的定义及协议解析的基本接口

  缩写说明   : 主站              master       -> m
               交互终端(集中器)  concentrator -> c
               采集终端(终端)    terminal     -> t

               用户侧数据(默认字节对齐)
               封帧侧数据(用1 字节对齐)

  函数列表   :
  修改历史   :
  1.日    期   : 2013年10月17日
    作    者   : liming(vliming@126.com)
    修改内容   : 创建文件

******************************************************************************/
#ifndef _GBNX_31_API_H_
#define _GBNX_31_API_H_


/*******************************************************
 *  配置文件 编译宏
 *  用此API之前请配置好
 *
{*///
#ifndef _TYPE_DEF_LM_
#define _TYPE_DEF_LM_
#ifndef __RTL_H__
#define __RTL_H__
typedef char                BOOL;
#endif
#define TRUE                (1)
#define FALSE               (0)
typedef unsigned char       UCHAR;
typedef char                CHAR;
typedef unsigned short      USHORT;
typedef short               SHORT;
typedef unsigned long       ULONG;
typedef long                LONG;

#ifndef _TYPE_DEF_
#define _TYPE_DEF_
typedef char                INT8;       //c
typedef short               INT16;      //s
typedef int                 INT32;      //l
typedef unsigned char       UINT8;      //uc
typedef unsigned short      UINT16;     //us
typedef unsigned int        UINT32;     //ul

#ifdef MACHINE_64_BITS
typedef long                INT64;
typedef unsigned long       UINT64;
#else
typedef long long           INT64;
typedef unsigned long long  UINT64;
#endif

typedef char*               STRING;     //str
typedef char                ISBOOL;     //b
typedef unsigned int        IPADDR;     //ip
typedef double              DOUBLE;
typedef void*               FRWK_HANDLE;
#endif
#endif
///*}

/*******************************************************
 *  配置文件 编译宏
 *  用此API之前请配置好
 *
{*///

#define MC_CFG_SPT_MST         (1)         // 是否支持主站   配置文件 不支持将其改为 0
#define MC_CFG_SPT_CON         (1)         // 是否支持集中器 配置文件 不支持将其改为 0
#define MC_CFG_MEDIUM_NET      (1)         // 通信介质,将决定报文的最大长度 如果是以太置1 不是置0
#define MC_CFG_ENCRYPT         (0)         // 是否需要加密
#define MC_CFG_EC              (1)         // 附加域中默认允许加上Ec 
#define MC_CFG_TP              (1)         // 附加域中默认允许加上Tp
#define MC_CFG_PW              (1)         // 附加域中默认允许加上Pw
#define MC_CFG_IP_VER          (1)         // IP地址的版本 1-IPV4 0-IPV6         
///*}

/*******************************************************
 *  协议相关宏定义
 *
{*///

#define MC_PROTO_VERSION       (0x21)       // 本协议版本

#define METER_ADDR_LEN         (12)         // 电表地址长度
/****************************************
 *  地址域
 *  终端地址A2选址范围为1～65535。
 *  A2=0000H为无效地址，A2=FFFFH且A3的D0位为"1"时表示系统广播地址。
 *
 *
 *
{*///

#define MC_TML_ADDR_MIN        (1)         // 终端或集中器地址最大值
#define MC_TML_ADDR_MAX        (65535)     // 主站地址最大值
#define MC_TML_ADDR_BRD        (0xFFFF)    // 主站地址最大值

#define MC_MST_ADDR_MIN        (0)         // 主站地址最大值
#define MC_MST_ADDR_MAX        (127)       // 主站地址最大值

///*}

/****************************************
 *  应用数据域 数据单元标识
 *  对于一个确定的DaDt结构,最大支持 8个Pn 同时各对应用于下边 8个Fn
 *  所以需要 8*8个数据单元
 *
 *
 *
{*///
#define MC_PN_INDEX_MAX        (8)          // 用于数据单元的组织
#define MC_FN_INDEX_MAX        (8)          // 用于数据单元的组织
///*}

/****************************************
 *  解封、封装相关部分字节长
 *
 *
 *
{*///
#define MC_PW_LEN              (16)         // 消息认证长度
#define MC_PN_MAX              (2040)       // 数据单元标识 DA Pn 最大值
#define MC_PN_MIN              (0)          // 数据单元标识 Da Pn 最小值
#define MC_PN_NONE             (0xFFFF)     // 数据单元标识 Da Pn 无效值 即不用关心的值
 
#define MC_FN_MAX              (248)        // 数据单元标识 Dt Fn 最大值
#define MC_FN_MIN              (1)          // 数据单元标识 Dt Fn 最小值
#define MC_FN_NONE             (0xFF)       // 数据单元标识 Dt Fn 无效值 即不用关心的值

#define MC_UNIT_DATA_MAX       (128)        // 最大的数据单元字长

#define MC_FRM_MAX_WRLESS      (255)        // 采用专用无线数传信道,长度L1不大于255
#define MC_FRM_MAX_NET         (16384)      // 采用网络传输,长度L1不大于16383
#define MC_SEQ2CS_MAX          (2048)       // 每单帧允许SEQ与CS之间数据字节数最大值
#define MC_CA_LEN              (10)          // 控制域与地址域总字长
#define MC_VAC_LEN             (2)          // 变长帧中协议标识与应用控制域AC字节长度
#define MC_CANS_LEN            (8)          // 控制域C 地址域A AFN SEQ字节总长
#define MC_UN_USER_LEN         (8)          // 报文中非数据域总长度  0x68 0x68 L L CS 0x16
#define MC_DADT_LEN            (4)          // 数据标识字长 DaDt
#define MC_AFN_LEN             (1)          // AFN 字长
#define MC_DADT_ERR_LEN        (MC_DADT_LEN + 1)  // DaDt 与 ERR总字长

// 帧的最大字长
#if MC_CFG_MEDIUM_NET
#define MC_FRM_LEN_MAX         MC_FRM_MAX_NET
#else
#define MC_FRM_LEN_MAX         MC_FRM_MAX_WRLESS
#endif

#define MC_CS_LEN              (1)                          // 校验和CS字长
#define MC_FIXED_USR_LEN       (MC_A_LEN + MC_C_LEN + 1)    // 固定帧用户数据域字长 (控制域C + 地址域A + 链路用户数据D)
#define MC_FIXED_LEN           (MC_FIXED_USR_LEN + 3)       // 固定帧字长           (用户数据域 + 起始字符+ CS)
#define MC_STCHAR_FIXED        (0x10)                       // 固定帧起始字符
#define MC_STCHAR_ALTER        (0x68)                       // 可变帧起始字符
#define MC_FRM_END_CHAR        (0x16)                       // 结束符
#define MC_ALTER_USR_OTHER_LEN (MC_A_LEN + MC_C_LEN)        // 可变帧用户数据域字长(除链路用户数据)
#define MC_ALTER_BUT_USER_LEN  (8)                          // 可变帧除了(用户数据域之外的长度)
#define MC_ALTER_OTHER_LEN     (MC_ALTER_USR_OTHER_LEN + 8) // 可变帧除了链路用户数据外部分字长

#define MC_A2CS_BYTE_MAX       (MC_FRM_LEN_MAX - MC_ALTER_OTHER_LEN)  // 每单帧允许A与CS之间数据字节数最大值
#define MC_USER_MAX            (2*MC_A2CS_BYTE_MAX)                   // 用户侧等变长结构 smcPack smcBasePack 最大长度

// 帧的最小字长
#define MC_FRM_LEN_MIN         (MC_FIXED_LEN)               // 心跳、登录的帧长最小

// IP地址长度
#if MC_CFG_IP_VER
#define MC_IP_LEN              (4)                          // 对应IPv4 地址长度
#else 
#define MC_IP_LEN              (16)                         // 对应Ipv6 地址长度
#endif
///*}

/*******************************************************
 *  错误码定义 eMcErr
 *
{*///
typedef enum
{
    MC_OK,             // 无错误                    0
    MC_ERR_NULL,       // 指针为空                  1
    MC_ERR_OUTRNG,     // 参数越界                  2
    MC_ERR_NONE,       // 不存在,没有找到           3
    MC_ERR_IO,         // IO错误                    4
    MC_ERR_RES,        // 资源不足                  5
    MC_ERR_INIT,       // 没有初始化                6
    MC_ERR_PARA,       // 参数错误                  7
    MC_ERR_FN,         // 指定Afn 中不支持的 Fn     8
    MC_ERR_PN,         // 指定Afn 中不支持的 Pn     9
    MC_ERR_ADDR,       // 无效地址                  10
    MC_ERR_CTRL,       // 控制域错误                11
    MC_ERR_0x10,       // SEQ域错误                 12
    MC_ERR_A2CS,       // A2CS 错误错误             13
    MC_ERR_AFN,        // AFN 错误                  14
    MC_ERR_UNCOMP,     // 不完整的协议包            15
    MC_ERR_0x68,       // 错误的报文起始            16
    MC_ERR_PROTO,      // 错误的协议标识            17
    MC_ERR_CS,         // 错误的检测和              18
    MC_ERR_0x16,       // 错误的结尾符              19
    MC_ERR_LOGIC,      // 错误的处理逻辑            20
    MC_ERR_PACK,       // 不是一个有效的包          21
    MC_ERR_PFC,        // 序列号不对应              22
    MC_ERR_TIMEOUT,    // 报文超时                  23
    MC_ERR_PRM,        // 启动站标识错              24
    MC_ERR_TEAM,       // Fn或Pn不在同一个组        25
    MC_ERR_ENCRYPT,    // 加密错误                  26
    MC_ERR_DECRYPT,    // 解密错误                  27
    MC_ERR_L1L2,       // 帧中的L1和L2不相等        28
    MC_ERR_FCODE,      // 功能码错误                29
    MC_ERR_DIR,        // 报文的方向错误            30

}eMcErr;
///*}

/*******************************************************
 *  应用层功能码 AFN
 *
{*///
typedef enum
{
    MC_AFN_00_CONF  = 0x00,     // 确认否认                
    MC_AFN_01_RSET  = 0x01,     // 复位                     (下行报文, 上行报文为确认/否认报文)
    MC_AFN_02_LINK  = 0x02,     // 链路测试                 该AFN不存在于协议,这里添加为了实现方便,请注意
    MC_AFN_04_SETP  = 0x04,     // 设置参数                 (下行报文, 上行报文为确认/否认报文)
    MC_AFN_05_CTRL  = 0x05,     // 控制命令                 (下行报文, 上行报文为确认/否认报文)
    MC_AFN_06_AUTH  = 0x06,     // 身份认证及密钥协商       (上下行报文)
    MC_AFN_08_CASC  = 0x08,     // 请求被级联终端主动上报
    MC_AFN_10_GETP  = 0x0A,     // 查询参数                 (下行行报文, 上行应答数据)
    MC_AFN_12_ASKT  = 0x0C,     // 请求（定时上报）任务数据 (下行行报文, 上行应答数据)
    MC_AFN_13_ASKR  = 0x0D,     // 请求实时数据             (下行行报文, 上行应答数据)
    MC_AFN_14_ASKE  = 0x0E,     // 请求（主动上报）事件记录 (下行行报文, 上行应答数据)
    MC_AFN_15_FILE  = 0x0F,     // 文件传输                 
    MC_AFN_16_DATA  = 0x10,     // 数据转发
    MC_AFN_NULL     = 0xFF      // 不存在的AFN

}eMcAFN;
 ///*}

/*******************************************************
 *  命令码定义
 *  命名规则 MCMD_AFN_(xx)_F(xx)_NAME
 *  xx 表示数字
 *  F  表示信息类标识
 *  根据协议规则, 每组内的最多8个Fn可以组成一个数据标识
 *  上行: 终端或集中器到主站
 *  下行: 主站到终端或集中器
 *
{*///
typedef enum
{
    MCMD_AFN_F_UNKOWN,                                // 未知命令

    /**********************************
    * 类型: 确认/否认
    * AFN : 00H
    *  PN : p0
    * 上行: 有
    * 下行: 有
    {*///
    MCMD_AFN_0_F1_ALL_OK_DENY         = 0x0001,       // 全部确认/否认：对收到报文中的全部数据单元标识进行确认/否认
    MCMD_AFN_0_F2_ONE_BY_ONE          = 0x0002,       // 按数据单元标识确认和否认：对收到报文中的全部数据单元标识进行逐个确认/否认
    ///*}

    /**********************************
     * 类型: 复位命令
     * AFN : 01
     *  PN : p0 /监测终端号
     * 上行: AFN 00H 确认/否认
     * 下行: 有
    {*///
    MCMD_AFN_1_F1_HARD_INIT           = 0x0101,       // 硬件初始化
    MCMD_AFN_1_F2_DATA_INIT           = 0x0102,       // 数据区初始化
    MCMD_AFN_1_F3_FACTORY_RESET       = 0x0103,       // 参数及全体数据区初始化（即恢复至出厂配置）
    MCMD_AFN_1_F4_PARA_INIT           = 0x0104,       // 参数（除与系统主站通信有关的）及全体数据区初始化
    MCMD_AFN_1_F5_DATA_CLEAR          = 0x0105,       // 指定数据清零
    ///*}


    /**********************************
     * 链路接口检测
     * AFN : 无
     *  PN : 无
     * 上行: 有(F1 ~ F3)
     * 下行: 有(F4)
     * 说明: 仅该命令帧为固定帧,其余的帧格式为可变帧
    {*///
    MCMD_AFN_2_F1_LOG_IN              = 0x0201,       // 建立链路、登录系统
    MCMD_AFN_2_F2_LOG_OUT             = 0x0202,       // 拆除链路、退出系统
    MCMD_AFN_2_F3_HEART_BEAT          = 0x0203,       // 保持链路、在线心跳
    MCMD_AFN_2_F4_LINK_OK             = 0x0204,       // 确认(登录/退出/心跳)
    ///*}

    /**********************************
     * 类型: 设置参数
     * AFN : 04
     *  PN : 分组定义
     * 上行: 有
     * 下行: 有
    {*///
    // 组1   pn:p0
    MCMD_AFN_4_F1_CON_UP_CFG          = 0x0401,       // 信息集中与交互终端上行通信口通信参数
    MCMD_AFN_4_F2_MST_PARA            = 0x0402,       // 主(子)站参数
    MCMD_AFN_4_F3_CON_AUTH_PARA       = 0x0403,       // 信息集中与交互终端上行通信消息认证参数
    MCMD_AFN_4_F4_TEAM_ADDR           = 0x0404,       // 信息集中与交互终端组地址
    MCMD_AFN_4_F5_CON_IP_PORT         = 0x0405,       // 信息集中与交互终端IP地址和端口
    MCMD_AFN_4_F6_CON_CASC            = 0x0406,       // 信息集中与交互终端级联通信参数
    MCMD_AFN_4_F7_CON_DOWN_CFG        = 0x0407,       // 信息集中与交互终端下行以太网端口通信参数

    // 组2   pn:p0/监测终端号
    MCMD_AFN_4_F9_CON_EVENT_CFG       = 0x0409,       // 事件记录配置
    MCMD_AFN_4_F10_CON_STATE_INPUT    = 0x040A,       // 设备状态量输入参数

    // 组3   pn:监测终端号
    MCMD_AFN_4_F17_TML_UP_CFG         = 0x0411,       // 监测终端上行通信参数配置

    // 组4   pn:电气测量点号
    MCMD_AFN_4_F25_ELEC_MP_CFG        = 0x0419,       // 电气测量点配置参数
    MCMD_AFN_4_F26_ELEC_MP_BASE       = 0x041A,       // 电气测量点基本参数
    MCMD_AFN_4_F27_ELEC_LMIT_POWER    = 0x041B,       // 电气测量点电能量限值参数
    MCMD_AFN_4_F28_ELEC_LMIT_FACTR    = 0x041C,       // 电气测量点功率因素越限值参数
    MCMD_AFN_4_F29_ELEC_FIX_HARM      = 0x041D,       // 电气测量点谐波畸变率越限定值
    MCMD_AFN_4_F30_ELEC_FLASH         = 0x041E,       // 电气测量点闪变越限参数

    // 组5   pn:非电气测量点号
    MCMD_AFN_4_F33_NELC_MP_CFG        = 0x0421,       // 非电气测量点配置参数
    MCMD_AFN_4_F34_NELC_MP_PARA       = 0x0422,       // 非电气测量点数据参数
    MCMD_AFN_4_F35_NELC_MP_LMIT       = 0x0423,       // 非电气测量点越限数据参数

    // 组7  pn:任务号
    MCMD_AFN_4_F49_FREZ_TASK_PARA     = 0x0431,       // 冻结数据任务参数
    ///*}

    /**********************************
     * 类型: 控制命令
     * AFN : 05
     *  PN : 分组定义
     * 上行: AFN 00H 确认/否认
     * 下行: 有
    {*///
    // 组1  pn:p0
    MCMD_AFN_5_F1_CHECK_TIME          = 0x0501,       // 校时命令
    MCMD_AFN_5_F2_FREZ_TEMP           = 0x0502,       // 临时冻结命令
    MCMD_AFN_5_F3_AUTO_SAY_ON         = 0x0503,       // 允许信息集中与交互终端主动上报
    MCMD_AFN_5_F4_AUTO_SAY_OFF        = 0x0504,       // 禁止信息集中与交互终端主动上报
    MCMD_AFN_5_F5_CON_LINK_ON         = 0x0505,       // 激活信息集中与交互终端连接主(子)站
    MCMD_AFN_5_F6_CON_LINK_OFF        = 0x0506,       // 命令信息集中与交互终端断开连接

    // 组2  pn:p0/监测终端号
    MCMD_AFN_5_F9_REMOTE_OFF          = 0x0509,       // 遥控跳闸
    MCMD_AFN_5_F10_REMOTE_ON          = 0x050A,       // 允许合闸

    // 组3  pn:p0/监测终端号
    MCMD_AFN_5_F17_NX_MODEL_ACT       = 0x0511,       // 能效模型有效
    MCMD_AFN_5_F18_NX_MODEL_CLR       = 0x0512,       // 能效模型清除
    MCMD_AFN_5_F19_RQ_RESPN_ACT       = 0x0513,       // 需求响应信息有效
    MCMD_AFN_5_F20_RQ_RESPN_CLT       = 0x0514,       // 需求响应信息清除

    // 组4  pn:任务号
    MCMD_AFN_5_F25_REPT_FREZ_ON       = 0x0519,       // 启动定时上报冻结数据任务
    MCMD_AFN_5_F26_REPT_FREZ_OFF      = 0x051A,       // 禁止定时上报冻结数据任务
    MCMD_AFN_5_F27_TASK_FREZ_ON       = 0x051B,       // 冻结数据任务启动
    MCMD_AFN_5_F28_TASK_FREZ_OFF      = 0x051C,       // 冻结数据任务停止
    ///*}

    /**********************************
     * 类型: 身份认证及密钥协商
     * AFN : 06
     *  PN : p0
     * 上行: 有
     * 下行: 有
    {*///
    MCMD_AFN_6_F1_ID_AUTH_Q           = 0x0601,       // 身份认证请求
    MCMD_AFN_6_F2_ID_AUTH_A           = 0x0602,       // 身份认证响应
    MCMD_AFN_6_F3_RAND_Q              = 0x0603,       // 取随机数请求
    MCMD_AFN_6_F4_RAND_A              = 0x0604,       // 取随机数响应
    ///*}

    /**********************************
     * 类型: 请求被级联终端主动上报
     * AFN : 08
     *  PN : p0
     * 上行: 有主动上报数据时,
     *       无主动上报数据时, 应答否认报文 CMD_AFN_0_F2_ALL_DENY
     * 下行: 有
    {*///
    MCMD_AFN_8_F1_CALL_AUTO_REPT      = 0x0801,       // 请求被级联终端主动上报
    ///*}

    /**********************************
     * 类型: 查询参数
     * AFN : 0A
     *  PN : 分组定义
     * 上行: 有
     * 下行: 有
    {*///
    // 组1   pn:p0
    MCMD_AFN_A_F1_CON_UP_CFG          = 0x0A01,       // 查询信息集中与交互终端上行通信口通信参数
    MCMD_AFN_A_F2_MST_PARA            = 0x0A02,       // 查询主(子)站参数
    MCMD_AFN_A_F3_CON_AUTH_PARA       = 0x0A03,       // 查询信息集中与交互终端上行通信消息认证参数
    MCMD_AFN_A_F4_TEAM_ADDR           = 0x0A04,       // 查询信息集中与交互终端组地址
    MCMD_AFN_A_F5_CON_IP_PORT         = 0x0A05,       // 查询信息集中与交互终端IP地址和端口
    MCMD_AFN_A_F6_CON_CASC            = 0x0A06,       // 查询信息集中与交互终端级联通信参数
    MCMD_AFN_A_F7_CON_DOWN_CFG        = 0x0A07,       // 信息集中与交互终端下行以太网端口通信参数

    // 组2   pn:p0/监测终端号
    MCMD_AFN_A_F9_CON_EVENT_CFG       = 0x0A09,       // 查询事件记录配置
    MCMD_AFN_A_F10_CON_STATE_INPUT    = 0x0A0A,       // 查询设备状态量输入参数
    MCMD_AFN_A_F11_CON_LOGIC_ADDR     = 0x0A0B,       // 设备逻辑地址
    MCMD_AFN_A_F12_CON_VERSION        = 0x0A0C,       // 查询设备版本信息
    MCMD_AFN_A_F13_ELEC_MP_INFO       = 0x0A0D,       // 已配置电气测量点信息
    MCMD_AFN_A_F14_NELC_MP_INFO       = 0x0A0E,       // 已配置非电气测量点信息
    MCMD_AFN_A_F15_SUPT_EVENT         = 0x0A0F,       // 设备支持的事件记录

    // 组3   pn:监测终端号
    MCMD_AFN_A_F17_TML_UP_CFG         = 0x0A11,       // 查询监测终端的上行通信参数

    // 组4   pn:电气测量点号
    MCMD_AFN_A_F25_ELEC_MP_CFG        = 0x0A19,       // 查询电气测量点配置参数
    MCMD_AFN_A_F26_ELEC_MP_BASE       = 0x0A1A,       // 查询电气测量点基本参数


    #if 0 // 原国标版
    MCMD_AFN_A_F27_ELEC_LMIT_POWER    = 0x0A1C,       // 查询电气测量点电能量限值参数
    MCMD_AFN_A_F28_ELEC_LMIT_FACTR    = 0x0A1D,       // 查询电气测量点功率因素分段限值参数
    //MCMD_AFN_A_F29_ELEC_FIX_HARM      = 0x0A1E,       // 查询电气测量点谐波畸变率越限定值
    //MCMD_AFN_A_F30_ELEC_FLASH         = 0x0A1F,       // 查询电气测量点闪变越限参数
    #else // 电科院内部版
    
    MCMD_AFN_A_F27_ELEC_LMIT_POWER    = 0x0A1B,       // 查询电气测量点电能量限值参数
    MCMD_AFN_A_F28_ELEC_LMIT_FACTR    = 0x0A1C,       // 查询电气测量点功率因素分段限值参数
    MCMD_AFN_A_F29_ELEC_FIX_HARM      = 0x0A1D,       // 查询电气测量点谐波畸变率越限定值
    MCMD_AFN_A_F30_ELEC_FLASH         = 0x0A1E,       // 查询电气测量点闪变越限参数
    #endif

    // 组5   pn:非电气测量点号
    MCMD_AFN_A_F33_NELC_MP_CFG        = 0x0A21,       // 查询非电气测量点配置参数
    MCMD_AFN_A_F34_NELC_MP_PARA       = 0x0A22,       // 查询非电气测量点数据参数
    MCMD_AFN_A_F35_NELC_MP_LMIT       = 0x0A23,       // 查询非电气测量点越限数据参数

    // 组7  pn:任务号
    MCMD_AFN_A_F49_FREZ_TASK_PARA     = 0x0A31,       // 查询冻结数据任务参数

    // 组8  pn:p0
    MCMD_AFN_A_F57_TML_CFG_INFO       = 0x0A39,       // 查询已配置监测终端信息
    ///*}

    /**********************************
     * 类型: 请求(定时上报)任务数据
     * AFN : 12
     *  PN : 分组定义
     * 上行: 有
     * 下行: 有
    {*///
    // 组1   pn:p0
    MCMD_AFN_C_F1_FREZ_TEMP           = 0x0C01,       // 请求临时冻结命令的冻结数据

    // 组2   pn:任务号
    MCMD_AFN_C_F9_FREZ_AUTO           = 0x0C09,       // 请求（定时上报）冻结数据任务
    ///*}

    /**********************************
     * 类型: 请求实时数据
     * AFN : 13
     *  PN : 分组定义
     * 上行: 有
     * 下行: 有
    {*///
    // 组1   pn: p0/监测终端号
    MCMD_AFN_D_F1_CLOCK              = 0x0D01,       // 日历时钟
    MCMD_AFN_D_F2_PARA_STATE         = 0x0D02,       // 参数状态标志
    MCMD_AFN_D_F3_EVENT_1            = 0x0D03,       // 重要事件计数器当前值
    MCMD_AFN_D_F4_EVENT_2            = 0x0D04,       // 一般事件计数器当前值
    MCMD_AFN_D_F5_EVENT_STATE        = 0x0D05,       // 事件状态标志
    MCMD_AFN_D_F6_POWR_TIMES         = 0x0D06,       // 上电次数

    // 组2   pn:p0/监测终端号
    MCMD_AFN_D_F9_STATE              = 0x0D09,       // 状态量及变位标志
    MCMD_AFN_D_F10_SWITCH            = 0x0D0A,       // 控制输出回路开关接入状态量及变位标志

    // 组4   pn:p0/电气测量点号
    MCMD_AFN_D_F25_POWR_HAVE_T       = 0x0D19,       // 总有功功率
    MCMD_AFN_D_F26_POWR_NONE_T       = 0x0D1A,       // 总无功功率
    MCMD_AFN_D_F27_FACTR_T           = 0x0D1B,       // 总功率因数
    MCMD_AFN_D_F28_FACTR_A           = 0x0D1C,       // A相功率因素
    MCMD_AFN_D_F29_FACTR_B           = 0x0D1D,       // B相功率因数
    MCMD_AFN_D_F30_FACTR_C           = 0x0D1E,       // C相功率因数

    // 组5   pn:p0/电气测量点号
    MCMD_AFN_D_F33_DEMAND            = 0x0D21,       // 需量
    MCMD_AFN_D_F34_DEMAND_MAX        = 0x0D22,       // 日最大需量
    MCMD_AFN_D_F35_DEMAND_TIME       = 0x0D23,       // 日最大需量发生时间

    // 组6   pn:电气测量点号
    MCMD_AFN_D_F41_POWR_HAVE_A       = 0x0D29,       // A相有功功率
    MCMD_AFN_D_F42_POWR_HAVE_B       = 0x0D2A,       // B相有功功率
    MCMD_AFN_D_F43_POWR_HAVE_C       = 0x0D2B,       // C相有功功率
    MCMD_AFN_D_F44_POWR_NONE_A       = 0x0D2C,       // A相无功功率
    MCMD_AFN_D_F45_POWR_NONE_B       = 0x0D2D,       // B相无功功率
    MCMD_AFN_D_F46_POWR_NONE_C       = 0x0D2E,       // C相无功功率

    // 组7   pn:电气测量点号
    MCMD_AFN_D_F49_POWR_HAVE_FRTH    = 0x0D31,       // （正向）有功总电能示数
    MCMD_AFN_D_F50_POWR_HAVE_BACK    = 0x0D32,       // （反向）有功总电能示数
    MCMD_AFN_D_F51_POWR_NONE_FRTH    = 0x0D33,       // （正向）无功总电能示数
    MCMD_AFN_D_F52_POWR_NONE_BACK    = 0x0D34,       // （反向）无功总电能示数

    // 组8 pn:电气测量点号
    MCMD_AFN_D_F57_VOLT_A            = 0x0D39,       // A相电压
    MCMD_AFN_D_F58_VOLT_B            = 0x0D3A,       // B相电压
    MCMD_AFN_D_F59_VOLT_C            = 0x0D3B,       // C相电压
    MCMD_AFN_D_F60_VANGL_A           = 0x0D3C,       // A相电压相位角
    MCMD_AFN_D_F61_VANGL_B           = 0x0D3D,       // B相电压相位角
    MCMD_AFN_D_F62_VANGL_C           = 0x0D3E,       // C相电压相位角
    MCMD_AFN_D_F63_VOLT_UBL          = 0x0D3F,       // 电压不平衡度
    MCMD_AFN_D_F64_CIRCLE_V          = 0x0D40,       // 周波

    // 组9 pn:电气测量点号
    MCMD_AFN_D_F65_ELEC_A            = 0x0D41,       // A相电流
    MCMD_AFN_D_F66_ELEC_B            = 0x0D42,       // B相电流
    MCMD_AFN_D_F67_ELEC_C            = 0x0D43,       // C相电流
    MCMD_AFN_D_F68_ELEC_M            = 0x0D44,       // 中性线电流
    MCMD_AFN_D_F69_EANGL_A           = 0x0D45,       // A相电流相位角
    MCMD_AFN_D_F70_EANGL_B           = 0x0D46,       // B相电流相位角
    MCMD_AFN_D_F71_EANGL_C           = 0x0D47,       // C相电流相位角
    MCMD_AFN_D_F72_ELEC_UBL          = 0x0D48,       // 电流不平衡度

    // 组10 pn:电气测量点号
    MCMD_AFN_D_F73_VDMAX_A           = 0x0D49,       // 日A相电压极大值
    MCMD_AFN_D_F74_VDMAX_A_TIME      = 0x0D4A,       // 日A相电压极大值发生时间
    MCMD_AFN_D_F75_VDMAX_B           = 0x0D4B,       // 日A相电压极大值
    MCMD_AFN_D_F76_VDMAX_B_TIME      = 0x0D4C,       // 日A相电压极大值发生时间
    MCMD_AFN_D_F77_VDMAX_C           = 0x0D4D,       // 日A相电压极大值
    MCMD_AFN_D_F78_VDMAX_C_TIME      = 0x0D4E,       // 日A相电压极大值发生时间

    // 组11 pn:电气测量点号
    MCMD_AFN_D_F81_IDMAX_A           = 0x0D51,       // 日A相电流极大值
    MCMD_AFN_D_F82_IDMAX_A_TIME      = 0x0D52,       // 日A相电流极大值发生时间
    MCMD_AFN_D_F83_IDMAX_B           = 0x0D53,       // 日B相电流极大值
    MCMD_AFN_D_F84_IDMAX_B_TIME      = 0x0D54,       // 日B相电流极大值发生时间
    MCMD_AFN_D_F85_IDMAX_C           = 0x0D55,       // 日C相电流极大值
    MCMD_AFN_D_F86_IDMAX_C_TIME      = 0x0D56,       // 日C相电流极大值发生时间

    // 组12 pn:电气测量点号
    MCMD_AFN_D_F89_TFW_HAVE          = 0x0D59,       // 总基波有功功率  (Total Fundamental Wave)
    MCMD_AFN_D_F90_TFW_NONE          = 0x0D5A,       // 总基波无功功率
    MCMD_AFN_D_F91_THW_HAVE          = 0x0D5B,       // 总谐波有功功率  (Total Harmonic Wave)
    MCMD_AFN_D_F92_THW_NONE          = 0x0D5C,       // 总基波无功功率

    // 组13 pn:电气测量点号
    MCMD_AFN_D_F97_VDPP_TIME_A       = 0x0D61,       // A相电压越上上限日累计时间
    MCMD_AFN_D_F98_VDPP_TIME_B       = 0x0D62,       // B相电压越上上限日累计时间
    MCMD_AFN_D_F99_VDPP_TIME_C       = 0x0D63,       // C相电压越上上限日累计时间
    MCMD_AFN_D_F100_VDNN_TIME_A      = 0x0D64,       // A相电压越下下限日累计时间
    MCMD_AFN_D_F101_VDNN_TIME_B      = 0x0D65,       // B相电压越下下限日累计时间
    MCMD_AFN_D_F102_VDNN_TIME_C      = 0x0D66,       // C相电压越下下限日累计时间

    // 组14 pn:电气测量点号
    MCMD_AFN_D_F105_VMPP_TIME_A      = 0x0D69,       // A相电压越上上限月累计时间
    MCMD_AFN_D_F106_VMPP_TIME_B      = 0x0D6A,       // B相电压越上上限月累计时间
    MCMD_AFN_D_F107_VMPP_TIME_C      = 0x0D6B,       // C相电压越上上限月累计时间
    MCMD_AFN_D_F108_VMNN_TIME_A      = 0x0D6C,       // A相电压越下下限月累计时间
    MCMD_AFN_D_F109_VMNN_TIME_B      = 0x0D6D,       // B相电压越下下限月累计时间
    MCMD_AFN_D_F110_VMNN_TIME_C      = 0x0D6E,       // C相电压越下下限月累计时间

    // 组15 pn:电气测量点号 (aberrance)
    MCMD_AFN_D_F113_VABR_TOTL_A      = 0x0D71,       // A相电压总畸变率
    MCMD_AFN_D_F114_VABR_TOTL_B      = 0x0D72,       // B相电压总畸变率
    MCMD_AFN_D_F115_VABR_TOTL_C      = 0x0D73,       // C相电压总畸变率
    MCMD_AFN_D_F116_EABR_TOTL_A      = 0x0D74,       // A相电流总畸变率
    MCMD_AFN_D_F117_EABR_TOTL_B      = 0x0D75,       // B相电流总畸变率
    MCMD_AFN_D_F118_EABR_TOTL_C      = 0x0D76,       // C相电流总畸变率

    // 组16 pn:电气测量点号
    MCMD_AFN_D_F121_VABR_ODD_A       = 0x0D79,       // A相电压奇次畸变率
    MCMD_AFN_D_F122_VABR_EVN_A       = 0x0D7A,       // A相电压偶次畸变率
    MCMD_AFN_D_F123_VABR_ODD_B       = 0x0D7B,       // B相电压奇次畸变率
    MCMD_AFN_D_F124_VABR_EVN_B       = 0x0D7C,       // B相电压偶次畸变率
    MCMD_AFN_D_F125_VABR_ODD_C       = 0x0D7D,       // C相电压奇次畸变率
    MCMD_AFN_D_F126_VABR_EVN_C       = 0x0D7E,       // C相电压偶次畸变率

    // 组17 pn:电气测量点号
    MCMD_AFN_D_F128_EABR_OOD_A       = 0x0D80,       // A相电流奇次畸变率
    MCMD_AFN_D_F129_EABR_EVN_A       = 0x0D81,       // A相电流偶次畸变率
    MCMD_AFN_D_F130_EABR_OOD_B       = 0x0D82,       // B相电流奇次畸变率
    MCMD_AFN_D_F131_EABR_EVN_B       = 0x0D83,       // B相电流偶次畸变率
    MCMD_AFN_D_F132_EABR_OOD_C       = 0x0D84,       // C相电流奇次畸变率
    MCMD_AFN_D_F133_EABR_EVN_C       = 0x0D85,       // C相电流偶次畸变率

    // 组18 pn:电气测量点号
    MCMD_AFN_D_F137_FLS_SHRT_A       = 0x0D89,       // A相短时闪变
    MCMD_AFN_D_F138_FLS_SHRT_B       = 0x0D8A,       // B相短时闪变
    MCMD_AFN_D_F139_FLS_SHRT_C       = 0x0D8B,       // C相短时闪变
    MCMD_AFN_D_F140_FLS_LONG_A       = 0x0D8C,       // A相长时闪变
    MCMD_AFN_D_F141_FLS_LONG_B       = 0x0D8D,       // B相长时闪变
    MCMD_AFN_D_F142_FLS_LONG_C       = 0x0D8E,       // C相长时闪变

    // 组19 pn:电气测量点号
    MCMD_AFN_D_F145_HARM_VOLT_A      = 0x0D91,       // A相N次谐波电压
    MCMD_AFN_D_F146_HARM_VOLT_B      = 0x0D92,       // B相N次谐波电压
    MCMD_AFN_D_F147_HARM_VOLT_C      = 0x0D93,       // C相N次谐波电压
    MCMD_AFN_D_F148_HARM_ELEC_A      = 0x0D94,       // A相N次谐波电流
    MCMD_AFN_D_F149_HARM_ELEC_B      = 0x0D95,       // B相N次谐波电流
    MCMD_AFN_D_F150_HARM_ELEC_C      = 0x0D96,       // C相N次谐波电流

    // 组20 pn:电气测量点号
    MCMD_AFN_D_F153_HARM_VINC_A      = 0x0D99,       // A相N次谐波电压含有率
    MCMD_AFN_D_F154_HARM_VINC_B      = 0x0D9A,       // B相N次谐波电压含有率
    MCMD_AFN_D_F155_HARM_VINC_C      = 0x0D9B,       // C相N次谐波电压含有率
    MCMD_AFN_D_F156_HARM_EINC_A      = 0x0D9C,       // A相N次谐波电流含有率
    MCMD_AFN_D_F157_HARM_EINC_B      = 0x0D9D,       // B相N次谐波电流含有率
    MCMD_AFN_D_F158_HARM_EINC_C      = 0x0D9E,       // C相N次谐波电流含有率

    // 组30 pn:非电气测量点号
    MCMD_AFN_D_F233_NELC_VALUE       = 0x0DE9,       // 非电气量
    ///*}

    /**********************************
     * 类型: 请求（主动上报）事件记录
     * AFN : 0E
     *  PN : p0
     * 上行: 有
     * 下行: 有
    {*///
    MCMD_AFN_E_F1_EVENT_1             = 0x0E01,       // 请求重要事件
    MCMD_AFN_E_F2_EVENT_2             = 0x0E02,       // 请求一般事件
    MCMD_AFN_E_F3_EVENT_3             = 0x0E03,       // 请求指定事件
    ///*}

    /**********************************
     * 类型: 文件传输
     * AFN : 0F
     *  PN : p0
     * 上行: 有
     * 下行: 有
    {*///
    // 组1   pn:p0/监测终端号
    MCMD_AFN_F_F1_SOFT_DOWN           = 0x0F01,        // 软件下载
    MCMD_AFN_F_F2_SOFT_LEFT           = 0x0F02,        // 软件下载未收到数据段

    // 组2   pn:p0/监测终端号
    MCMD_AFN_F_F9_NXMD_DOWN           = 0x0F09,        // 软件下载
    MCMD_AFN_F_F10_NXMD_LEFT          = 0x0F0A,        // 软件下载未收到数据段

    // 组3   pn:p0/监测终端号
    MCMD_AFN_F_F17_REQS_DOWN          = 0x0F11,        // 软件下载
    MCMD_AFN_F_F18_REQS_LEFT          = 0x0F12,        // 软件下载未收到数据段
    ///*}

    /**********************************
     * 类型: 数据转发
     * AFN : 10H
     *  PN : p0
     * 上行: 有
     * 下行: 有
    {*///
    // 组1 Pn:P0
    MCMD_AFN_10_F1_TRANSMIT           = 0x1001,       // 透明转发
    ///*}

    /* 在这之上添加扩展命令字 */
    MCMD_AFN_FN_MAX
}eMcmd;
///*}

/*******************************************************
 *  事件类型定义 eMcErc
 *
{*///
typedef enum
{
    MC_ERC_UNKOWN,            // ERC0: 未知事件记录类型
    MC_ERC_1_RESET,           // ERC1: 复位事件
    MC_ERC_2_DATA_CLEAR,      // ERC2: 指定数据清零事件
    MC_ERC_3_SOFT_CHANGE,     // ERC3: 软件版本变更事件
    MC_ERC_4_PARA_CHANGE,     // ERC4: 参数变更事件
    MC_ERC_5_CHECK_TIME,      // ERC5: 校时事件
    MC_ERC_6_STATE_CHANGE,    // ERC6: 状态量变位事件
    MC_ERC_7_REMOTE_SWITCH,   // ERC7: 遥控跳闸事件
    MC_ERC_8_POWER_ON_OFF,    // ERC8: 停/上电事件
    MC_ERC_9_FACTOR_OVER,     // ERC9: 总功率因素越限事件
    MC_ERC_10_VOLT_EXCP,      // ERC10: 电压偏差越限事件
    MC_ERC_11_VOLT_CIRCLE,    // ERC11: 电压回路异常事件
    MC_ERC_12_ELEC_CRICLE,    // ERC12: 电流回路异常事件
    MC_ERC_13_VOLT_OVER,      // ERC13: 电压越限事件
    MC_ERC_14_ELEC_OVER,      // ERC14: 电流越限事件
    MC_ERC_15_UNBL_OVER_V,    // ERC15: 电压不平衡度越限事件
    MC_ERC_16_UNBL_OVER_I,    // ERC16: 电流不平衡度越限事件
    MC_ERC_17_HUNBL_OVER_V,   // ERC17: 谐波电压畸变率越限事件
    MC_ERC_18_HUNBL_OVER_I,   // ERC18: 谐波电流畸变率越限事件
    MC_ERC_19_FLASH_OVER,     // ERC19: 闪变越限事件
    MC_ERC_20_NELC_OVER,      // ERC20: 非电气量越限事件
    MC_ERC_NUM_MAX            // 事件类型最大值

}eMcEventRecord, eMcErc; // 事件类型定义

/*******************************************************
 *  帧侧与用户侧 数据结构转换函数类型定义
 *
{*///
typedef enum
{
    MC_TRANS_UNKOWN,    // 未知方向
    MC_TRANS_U2F,       // 用户侧数据结构到帧数据结构
    MC_TRANS_F2U,       // 帧侧数据结构到用户侧数据结构

}eMcTrans;              // 用户侧与帧侧数据结构转换方向

// 转换帧侧与用户侧数据结构的函数指针类型
// pusLen 为封装成帧侧的数据字节长
typedef eMcErr (*pMcFunc)(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*}

/************************************************************
 *  内部接口
 *
{*///

/*******************************************************************
 *  附录A 数据格式的定义与转换函数
 *
{*///

/*********************************************
 *  数据格式01 对于表A.1
 *  格式:
 *  字长: 6
 *  +-------+------+------+------+------+------+------+------+------+
 *  |              |                       字节格式                 |
 *  + 名 称 +------+------+------+------+------+------+------+------+
 *  |       |  D7  |  D6  |  D5  |  D4  |  D3  |  D2  |  D1  |  D0  |
 *  +-------+------+------+------+------+------+------+------+------+
 *  |   秒  |         BCD码十位         |         BCD码个位         |
 *  +-------+------+------+------+------+------+------+------+------+
 *  |   分  |         BCD码十位         |         BCD码个位         |
 *  +-------+------+------+------+------+------+------+------+------+
 *  |   时  |         BCD码十位         |         BCD码个位         |
 *  +-------+------+------+------+------+------+------+------+------+
 *  |   日  |         BCD码十位         |         BCD码个位         |
 *  +-------+------+------+------+------+------+------+------+------+
 *  |星期-月| 星期BCD个位        |月BCD |        月BCD码个位        |
 *  |       |                    |码十位|                           |
 *  +-------+------+------+------+------+------+------+------+------+
 *  |   年  |         BCD码十位         |         BCD码个位         |
 *  +-------+------+------+------+------+------+------+------+------+
 *  星期定义如下：D5 ~ D7编码表示 0 ~ 7，0：无效，1-7依次表示星期一至星期日
{*///
// 用户侧
typedef struct
{
    UINT8 ucYY;    // 年
    UINT8 ucMM;    // 月
    UINT8 ucWW;    // 星期
    UINT8 ucDD;    // 日
    UINT8 ucHH;    // 小时
    UINT8 ucmm;    // 分钟
    UINT8 ucss;    // 秒

}sMcUerClock, sMcFmt01, sMcYWMDhms;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8  bcd_ss_0:4;  //秒
    UINT8  bcd_ss_1:4;
    UINT8  bcd_mm_0:4;  // 分
    UINT8  bcd_mm_1:4;
    UINT8  bcd_HH_0:4;  // 时
    UINT8  bcd_HH_1:4;
    UINT8  bcd_DD_0:4;  // 日
    UINT8  bcd_DD_1:4;
    UINT8  bcd_MM_0:4;  // 月
    UINT8  bcd_MM_1:1;
    UINT8  bcd_WW_0:3;  // 星期
    UINT8  bcd_YY_0:4;  // 年
    UINT8  bcd_YY_1:4;

}sMcUerClock_f, sMcFmt01_f, sMcYWMDhms_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_YWMDhms(eMcTrans eTrans, sMcYWMDhms* psUser, sMcYWMDhms_f* psFrame);
///*}

/*********************************************
 *  数据格式2 对于表A.2
 *  单位: 年月日时分
 *  字长: 5
 *  格式:
 *  +------+------+------+------+------+------+------+------+------+
 *  |      |                       字节格式                        |
 *  + 名称 +------+------+------+------+------+------+------+------+
 *  |      |  D7  |  D6  |  D5  |  D4  |  D3  |  D2  |  D1  |  D0  |
 *  +------+------+------+------+------+------+------+------+------+
 *  |  分  |         BCD码十位         |         BCD码个位         |
 *  +------+------+------+------+------+------+------+------+------+
 *  |  时  |         BCD码十位         |         BCD码个位         |
 *  +------+------+------+------+------+------+------+------+------+
 *  |  日  |         BCD码十位         |         BCD码个位         |
 *  +------+------+------+------+------+------+------+------+------+
 *  |  月  |         BCD码十位         |         BCD码个位         |
 *  +------+------+------+------+------+------+------+------+------+
 *  |  年  |         BCD码十位         |         BCD码个位         |
 *  +------+------+------+------+------+------+------+------+------+
 *
{*///
// 用户侧
typedef struct
{
    UINT8  ucYY;        // 年
    UINT8  ucMM;        // 月
    UINT8  ucDD;        // 日
    UINT8  ucHH;        // 时
    UINT8  ucmm;        // 分

}sMcFmt02, sMcYYMMDDhhmm, sMcYMDhm;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8  bcd_mm_0:4;  // 分
    UINT8  bcd_mm_1:4;
    UINT8  bcd_hh_0:4;  // 时
    UINT8  bcd_hh_1:4;
    UINT8  bcd_DD_0:4;  // 日
    UINT8  bcd_DD_1:4;
    UINT8  bcd_MM_0:4;  // 月
    UINT8  bcd_MM_1:4;
    UINT8  bcd_YY_0:4;  // 年
    UINT8  bcd_YY_1:4;

}sMcFmt02_f,sMcYYMMDDhhmm_f, sMcYMDhm_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_YYMMDDhhmm(eMcTrans eTrans, sMcYMDhm* psUser, sMcYMDhm_f* psFrame);
///*}

/*********************************************
 *  数据格式3 对于表A.3
 *  单位: 月日时分
 *  字长: 4
 *  格式:
 *  +------+------+------+------+------+------+------+------+------+
 *  |      |                       字节格式                        |
 *  + 名称 +------+------+------+------+------+------+------+------+
 *  |      |  D7  |  D6  |  D5  |  D4  |  D3  |  D2  |  D1  |  D0  |
 *  +------+------+------+------+------+------+------+------+------+
 *  |  秒  |         BCD码十位         |         BCD码个位         |
 *  +------+------+------+------+------+------+------+------+------+
 *  |  分  |         BCD码十位         |         BCD码个位         |
 *  +------+------+------+------+------+------+------+------+------+
 *  |  时  |         BCD码十位         |         BCD码个位         |
 *  +------+------+------+------+------+------+------+------+------+
 *  |  日  |         BCD码十位         |         BCD码个位         |
 *  +------+------+------+------+------+------+------+------+------+
 *
{*///
// 用户侧
typedef struct
{
    UINT8  ucDD;        // 日
    UINT8  ucHH;        // 时
    UINT8  ucmm;        // 分
    UINT8  ucss;        // 秒
}sMcFmt03, sMcDDHHmmss;

// 帧侧
typedef struct
{
    UINT8  bcd_ss_0:4;  // 秒
    UINT8  bcd_ss_1:4;
    UINT8  bcd_mm_0:4;  // 分
    UINT8  bcd_mm_1:4;
    UINT8  bcd_HH_0:4;  // 时
    UINT8  bcd_HH_1:4;
    UINT8  bcd_DD_0:4;  // 日
    UINT8  bcd_DD_1:4;

}sMcFmt03_f, sMcDDHHmmss_f;

// 转换函数
eMcErr emc_trans_DDHHmmss(eMcTrans eTrans, sMcDDHHmmss* psDDHHmmss_u, sMcDDHHmmss_f* psDDHHmmss_f);
///*}

/*********************************************
 *  数据格式4 对于表A.4
 *  格式: (+)XXXXXX.XXXX
 *  字长: 5
 *  格式:
 *  +-------+------+------+------+------+------+------+------+------+
 *  |       |                       字节格式                        |
 *  + 名称  +------+------+------+------+------+------+------+------+
 *  |       |  D7  |  D6  |  D5  |  D4  |  D3  |  D2  |  D1  |  D0  |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE1 |        BCD码千分位        |        BCD码万分位        |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE2 |        BCD码十分位        |        BCD码百分位        |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE3 |         BCD码十位         |         BCD码个位         |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE4 |         BCD码千位         |         BCD码百位         |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE5 |        BCD码十万位        |          BCD码万位        |
 *  +-------+------+------+------+------+------+------+------+------+
{*///
// 用户侧
// double dXXXXXX.XXXX

// 帧侧
typedef struct
{
    UINT8 BCD_0_4:4;  // BCD 百分位
    UINT8 BCD_0_3:4;  // BCD 十分位
    UINT8 BCD_0_2:4;  // BCD 百分位
    UINT8 BCD_0_1:4;  // BCD 十分位
    UINT8 BCD_0  :4;  // BCD 个位
    UINT8 BCD_1  :4;  // BCD 十位
    UINT8 BCD_2  :4;  // BCD 百位
    UINT8 BCD_3  :4;  // BCD 千位
    UINT8 BCD_4  :4;  // BCD 万位
    UINT8 BCD_5  :4;  // BCD 十万位

}sMcFmt04, sMcFmt04_f,sMcFmt_XXXXXX_XXXX;

// 转换函数
eMcErr emc_trans_XXXXXX_XXXX(eMcTrans eTrans, double* psUser, sMcFmt_XXXXXX_XXXX* psFrame);
///*}

/*********************************************
 *  数据格式5 对于表A.5
 *  格式: (+)XXXXXX.XX
 *  字长: 4
 *  +-------+------+------+------+------+------+------+------+------+
 *  |       |                       字节格式                        |
 *  + 名称  +------+------+------+------+------+------+------+------+
 *  |       |  D7  |  D6  |  D5  |  D4  |  D3  |  D2  |  D1  |  D0  |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE1 |        BCD码十分位        |        BCD码百分位        |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE2 |         BCD码十位         |         BCD码个位         |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE3 |         BCD码千位         |         BCD码百位         |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE4 |        BCD码十万位        |         BCD码万位         |
 *  +-------+------+------+------+------+------+------+------+------+
{*///
// 用户侧
// double dXXXXXX.XX

// 帧侧
typedef struct
{
    UINT8 BCD_0_2:4;  // BCD 百分位
    UINT8 BCD_0_1:4;  // BCD 十分位
    UINT8 BCD_0  :4;  // BCD 个位
    UINT8 BCD_1  :4;  // BCD 十位
    UINT8 BCD_2  :4;  // BCD 百位
    UINT8 BCD_3  :4;  // BCD 千位
    UINT8 BCD_4  :4;  // BCD 万位
    UINT8 BCD_5  :4;  // BCD 十万位

}sMcFmt05, sMcFmt05_f, sMcFmt_XXXXXX_XX;

// 转换函数
eMcErr emc_trans_XXXXXX_XX(eMcTrans eTrans, double* psUser, sMcFmt_XXXXXX_XX* psFrame);
///*}

/*********************************************
 *  数据格式6 对于表A.6
 *  格式: (+/-)XX.XXXX
 *  字长: 3
 *  +-------+------+------+------+------+------+------+------+------+
 *  |       |                       字节格式                        |
 *  + 名称  +------+------+------+------+------+------+------+------+
 *  |       |  D7  |  D6  |  D5  |  D4  |  D3  |  D2  |  D1  |  D0  |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE1 |        BCD码千分位        |        BCD码万分位        |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE2 |        BCD码十分位        |        BCD码百分位        |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE3 |  S   |     BCD码十位      |         BCD码个位         |
 *  +-------+------+------+------+------+------+------+------+------+
{*///
// 用户侧
// float fXX.XXXX

// 帧侧
typedef struct
{
    UINT8 BCD_0_4:4;  // BCD 万分位
    UINT8 BCD_0_3:4;  // BCD 千分位
    UINT8 BCD_0_2:4;  // BCD 百分位
    UINT8 BCD_0_1:4;  // BCD 十分位
    UINT8 BCD_0  :4;  // BCD 个位
    UINT8 BCD_1  :3;  // BCD 十位
    UINT8 S      :1;  // 符号位
}sMcFmt06_f, sMcFmt_sXX_XXXX;

// 10 exp次方 exp < 10
int  nmc_pow(UINT8 exp);

// 转换函数
eMcErr emc_trans_sXX_XXXX(eMcTrans eTrans, float* psUser, sMcFmt06_f* psFrame);
///*}

/*********************************************
 *  数据格式07 对于表A.7
 *  格式: (+/-)XXX.X
 *  字长: 2
 *  +-------+------+------+------+------+------+------+------+------+
 *  |       |                       字节格式                        |
 *  + 名 称 +------+------+------+------+------+------+------+------+
 *  |       |  D7  |  D6  |  D5  |  D4  |  D3  |  D2  |  D1  |  D0  |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE1 |        BCD码个分位        |        BCD码十分位        |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE2 |  S   |     BCD码百位      |         BCD码十位         |
 *  +-------+------+------+------+------+------+------+------+------+
{*///
// 用户侧
// float fsXXX.X

// 帧侧
typedef struct
{
    UINT8 BCD_0_1:4;  // BCD 十分位
    UINT8 BCD_0  :4; // BCD 个位
    UINT8 BCD_1  :4; // BCD 十位
    UINT8 BCD_2  :3; // BCD 百位
    UINT8 S      :1; // BCD 符号位
}sMcFmt07, sMcFmt07_f, sMcFmt_sXXX_X;

// 转换函数
eMcErr emc_trans_sXXX_X(eMcTrans eTrans, float* psUser, sMcFmt07_f* psFrame);
///*}

/*********************************************
 *  数据格式08 对于表A.8
 *  格式: (+)XXX.X
 *  字长: 2
 *  +-------+------+------+------+------+------+------+------+------+
 *  |       |                       字节格式                        |
 *  + 名 称 +------+------+------+------+------+------+------+------+
 *  |       |  D7  |  D6  |  D5  |  D4  |  D3  |  D2  |  D1  |  D0  |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE1 |        BCD码个分位        |        BCD码十分位        |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE2 |         BCD码百位         |         BCD码十位         |
 *  +-------+------+------+------+------+------+------+------+------+
{*///
// 用户侧
// float fXXX.X

// 帧侧
typedef struct
{
    UINT8 BCD_0_1:4;  // BCD 十分位
    UINT8 BCD_0  :4;  // BCD 个位
    UINT8 BCD_1  :4;  // BCD 十位
    UINT8 BCD_2  :4;  // BCD 百位
}sMcFmt08, sMcFmt08_f, sMcFmt_XXX_X;

// 转换函数
eMcErr emc_trans_XXX_X(eMcTrans eTrans, float* psUser, sMcFmt_XXX_X* psFrame);
///*}

/*********************************************
 *  数据格式09 对于表A.9
 *  格式: (+/-)XXX.XXX
 *  字长: 3
 *  +-------+------+------+------+------+------+------+------+------+
 *  |       |                       字节格式                        |
 *  + 名称  +------+------+------+------+------+------+------+------+
 *  |       |  D7  |  D6  |  D5  |  D4  |  D3  |  D2  |  D1  |  D0  |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE1 |        BCD码百分位        |        BCD码千分位        |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE2 |         BCD码个位         |        BCD码十分位        |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE3 |  S   |     BCD码百位      |         BCD码十位         |
 *  +-------+------+------+------+------+------+------+------+------+
 *
{*///
// 用户侧
// float sXXX.XXX    (+/-)XXX.XXX

// 帧侧
typedef struct
{
    UINT8 BCD_0_3:4;  // BCD 千分位
    UINT8 BCD_0_2:4;  // BCD 百分位
    UINT8 BCD_0_1:4;  // BCD 十分位
    UINT8 BCD_0  :4;  // BCD 个位
    UINT8 BCD_1  :4;  // BCD 十位
    UINT8 BCD_2  :3;  // BCD 百位
    UINT8 S      :1;  // 符号位

}sMcFmt09,sMcFmt09_f,sMcFmt_sXXX_XXX;

// 转换函数
eMcErr emc_trans_sXXX_XXX(eMcTrans eTrans, float* psUser, sMcFmt_sXXX_XXX* psFrame);
///*}

/*********************************************
 *  数据格式10 对于表A.10 格式有变
 *  格式: (+)XX.XX
 *  字长: 2
 *  +-------+------+------+------+------+------+------+------+------+
 *  |       |                       字节格式                        |
 *  + 名 称 +------+------+------+------+------+------+------+------+
 *  |       |  D7  |  D6  |  D5  |  D4  |  D3  |  D2  |  D1  |  D0  |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE1 |        BCD码十分位        |        BCD码百分位        |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE2 |         BCD码十位         |         BCD码个位         |
 *  +-------+------+------+------+------+------+------+------+------+
{*///
// 用户侧
// float fXX.XX

// 帧侧
typedef struct
{
    UINT8 BCD_0_2:4;  // BCD 百分位
    UINT8 BCD_0_1:4;  // BCD 十分位
    UINT8 BCD_0  :4;  // BCD 个位
    UINT8 BCD_1  :4;  // BCD 十位
}sMcFmt10_f, sMcFmt_XX_XX;

// 转换函数
eMcErr emc_trans_XX_XX(eMcTrans eTrans, float* psUser, sMcFmt10_f* psFrame);
///*}

/*********************************************
 *  数据格式11 对于表A.11
 *  格式: (+/-)XXXXXXX
 *  字长: 4
 *  +-------+------+------+------+------+------+------+------+------+
 *  |       |                       字节格式                        |
 *  + 名 称 +------+------+------+------+------+------+------+------+
 *  |       |  D7  |  D6  |  D5  |  D4  |  D3  |  D2  |  D1  |  D0  |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE1 |         BCD码十位         |         BCD码个位         |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE2 |         BCD码千位         |         BCD码百位         |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE3 |        BCD码十万位        |         BCD码万位         |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE4 |  G3  |  G2  |  G1  |  S   |         BCD码百万位       |
 *  +-------+------+------+------+------+------+------+------+------+
 *  
 *  +-------+-------+-------+----------+
 *  |   G3  |  G2   |  G1   |   含义   |
 *  +-------+-------+-------+----------+
 *  |   0   |   0   |   0   |   10(4)  |
 *  +-------+-------+-------+----------+
 *  |   0   |   0   |   1   |   10(3)  |
 *  +-------+-------+-------+----------+
 *  |   0   |   1   |   0   |   10(2)  |
 *  +-------+-------+-------+----------+
 *  |   0   |   1   |   1   |   10(1)  |
 *  +-------+-------+-------+----------+
 *  |   1   |   0   |   0   |   10(0)  |
 *  +-------+-------+-------+----------+
 *  |   1   |   0   |   1   |   10(-1) |
 *  +-------+-------+-------+----------+
 *  |   1   |   1   |   0   |   10(-2) |
 *  +-------+-------+-------+----------+
 *  |   1   |   1   |   1   |   10(-3) |
 *  +-------+-------+-------+----------+
 *
 *  S 符号位:S = 0 正数 S = 1 表示负数
 *
{*///
// 用户侧
//double dValue
#define MC_SX7_MIN     (-99999990000.0)
#define MC_SX7_MAX     (99999990000.0)

typedef enum
{
    MC_PREC_UNKOWN,
    MC_PREC_P4,  // 范围 0, (+/-)10000~99999990000
    MC_PREC_P3,  // 范围 0, (+/-)1000~9999999000
    MC_PREC_P2,  // 范围 0, (+/-)100~999999900
    MC_PREC_P1,  // 范围 0, (+/-)10~99999990
    MC_PREC_P0,  // 范围 0, (+/-)1~9999999
    MC_PREC_N1,  // 范围 0, (+/-)0.1~999999.9
    MC_PREC_N2,  // 范围 0, (+/-)0.01~99999.99
    MC_PREC_N3,  // 范围 0, (+/-)0.001~9999.999

}eMcPrecise;            // 精度

typedef struct
{
    eMcPrecise  ePrec;
    double      dValue;   
}sMcFmt11, sMcDouble; 

// 帧侧
#pragma pack(1)
typedef struct
{
    UINT8 BCD_0  :4; // BCD 个位
    UINT8 BCD_1  :4; // BCD 十位
    UINT8 BCD_2  :4; // BCD 百位
    UINT8 BCD_3  :4; // BCD 千位
    UINT8 BCD_4  :4; // BCD 万位
    UINT8 BCD_5  :4; // BCD 十万位
    UINT8 BCD_6  :4; // BCD 百万位
    UINT8 SG123  :4;
    /*
    UINT8 S      :1; // 符号位 0 为正 1为负
    UINT8 G1     :1; // 
    UINT8 G2     :1; // 
    UINT8 G3     :1; // 
    */
}sMcFmt11_f, sMcFmt_sX7_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_sX7(eMcTrans eTrans, void* psUser, void* psFrame);
///*}
///*}

/******************************************************************************
 *  数据名称:float类型的
 *  数据说明:
 *  浮点数在机内用指数型式表示，分解为：数符，尾数，指数符，指数四部分。
 *  无论是单精度还是双精度在存储中都分为三个部分：
 1.符号位(Sign) : 0代表正，1代表为负
 2.指数位（Exponent）:用于存储科学计数法中的指数数据，并且采用移位存储
 3.尾数部分（Mantissa）：尾数部分
{*///
typedef union
{
    float v;
    struct
    {
        unsigned mantissa1 : 23;
        unsigned exponent  : 8;
        unsigned sign      : 1;
    }s;

}uMcFloatFmt;

int    nmc_get_float_sign(float fVal);              // 取得一个flaot的符号位  sign = -1 / +1
void   vmc_set_float_sign(float *pfVal, int sign);  // 设置一个浮点数的符号位 sign = -1 / +1
///*}

/******************************************************************************
 * 数据名称: double 类型的合成与解合成
 * 数据说明:
 * 浮点数在机内用指数型式表示，分解为：数符，尾数，指数符，指数四部分。
 * 无论是单精度还是双精度在存储中都分为三个部分：
 *   1.符号位(Sign) : 0代表正，1代表为负
 *   2.指数位（Exponent）:用于存储科学计数法中的指数数据，并且采用移位存储
 *   3.尾数部分（Mantissa）：尾数部分
 *
{*///
typedef union
{
    double v;
    struct
    {
        unsigned mantissa2 : 32;
        unsigned mantissa1 : 20;
        unsigned exponent  : 11;
        unsigned sign      :  1;
    } s;

}uMcDoubleFmt;

int    nmc_get_double_sign(double dVal);              // 取得一个double的符号位 sign = -1 / +1
void   vmc_set_double_sign(double *pdVal, int sign);  // 设置一个浮点数的符号位 sign = -1 / +1
///*}
///*}

/*********************************************
 *  BCD 转换函数
 *
 *
{*///
UINT8 ucmc_get_bcd_0(UINT8 ucData);        // 获得该数的BCD低位
UINT8 ucmc_get_bcd_1(UINT8 ucData);        // 获得该数的BCD高位
///*}

/***************************************************************************
 * BCD 与 字符串的转换函数
 * len 必须为偶数
 *
{*///
eMcErr emc_str_to_bcd(const UINT8* pstr, UINT8* pbcd, INT32 len);
eMcErr emc_bcd_to_str(const UINT8* pbcd, UINT8* pstr, INT32 len);
///*}

/*******************************************************
 *  子命令信息数据表及映射函数
 *
{*///
typedef enum
{
    MC_ROLE_UNKOWN,    // 未知身份
    MC_ROLE_MASTER,    // 主站
    MC_ROLE_CONTOR,    // 集中器 或 终端
    
}eMcRole;              // 协议应用模块的身份
 
typedef enum
{
    MC_DIR_UNKOWN,     // 未知报文方向
    MC_DIR_M2S,        // 主站到集中器  下行
    MC_DIR_S2M,        // 集中器到主站  上行

}eMcDir;               // 报文的发送方向

typedef enum
{
    MC_PN_UNKOWN,      // 未知PN类型
    MC_PN_P0,          // P0 不关心PN 集中器本身
    MC_PN_MP,          // 测量点号(measured point)
    MC_PN_TK,          // 任务号  (task number)
    MC_PN_TM,          // 终端号

}eMcPn;                // Pn类型

typedef struct
{
    eMcmd    eCmd;     // 子命令标识
    eMcDir   eDir;     // 该报文存在的方向类型
    eMcPn    ePn;      // Pn类型
    pMcFunc  pFunc;    // 该命令对应的用户侧数据与封装侧数据结构转换函数
    char*    pName;    // 该协议信息的中文含义

}sMcmdInfor;
///*}

// 通过命令类型和报文方向获得该命令对应的相关信息
eMcErr eMcGetCmdInfor(eMcmd eCmd, eMcDir eDir, sMcmdInfor* psInfor);
///*}

/************************************************************
 *  地址域A结构
 *
{*///
// 用户侧结构
#define MC_REGN_LEN   (6)      // 行政区划码A1 长度 (用户侧)
#define MC_A1_LEN     (3)      // 行政区划码A1 长度 (封帧侧)
#define MC_A_LEN      (8)      // 地址域 帧侧长度

typedef struct
{
    UINT8  acRegionCode[MC_REGN_LEN];   // 行政区划码A1 如北京 110000, 行政区划码按GB 2260-2007的规定执行
    UINT32 ulConAddress;                // 信息集中与交互终端地址A2 A2 范围(1~4294967295)
    BOOL   bTeam;                       // 为true 表示ulConAddress 为组地址, 为false 表示ulConAddress单一地址
    UINT8  ucMstAddress;                // 主站地址和组地址标志A3, 范围(0~127)

}sMcA, sMcAddress;

// 封帧侧结构
#pragma pack(1)
typedef struct
{
    UINT8  acRegionCode[MC_A1_LEN];     // 行政区划码A1           (BCD)  低字节在前  高字节在后
    UINT32 ulConAddress;                // 信息集中与交互终端地址A2 A2 范围(1~4294967295)
    //UINT8  ucTeam:1;                  // 为1表示 usTAddress 为组地址,A2 == 0xFFFF即广播地址, 为 0 表示单地址
    UINT8  ucMstAddress;                // 主站地址和组地址标志A3 (BIN)  最好不要用位域

}sMcA_f, sMcAddress_f; // 帧地址格式定义
#pragma pack()

// 转换函数
eMcErr emc_trans_address(eMcTrans eTrans, sMcAddress *psAddr_u, sMcAddress_f *psAddr_f);
///*}

/************************************************************
 *  控制域C 结构及转换函数
 *
 *  封帧侧为2字节
 *  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+
 *  | D15  | D14  | D13  | D12  | D11  | D10  |  D9  |  D8  |  D7  |  D6  |  D5  |  D4  |  D3  |  D2  |  D1  |  D0  |
 *  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+
 *  | DIR  | PRM  | 备用 |            启动帧序号PSEQ        |      启动帧序号PSEQ       |          帧功能码         |
 *  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+
 *
 *
 * DIR 传输方向位   DIR = 0 表示此帧报文是由主(子)站向信息集中与交互终端发出的下行报文
 *                  DIR = 1 表示此帧报文是由信息集中与交互终端向主(子)站发出的上行报文
 *
 * PRM 启动标志位   PRM = 0 表示此帧报文来自从动（响应）站，从动站（响应站）向启动站传输报文
 *                  PRM = 1 表示此帧报文来自启动站，启动站向从动站传输报文
 *
 *  启动帧序号PSEQ
 *      (1)启动帧序号PSEQ用编码表示0~31，用于区别和对应传输帧，以及防止信息传输的丢失或重复。
 *      (2)每一对启动站和从动站之间均有1个独立的计数器，用于记录当前PSEQ，启动站向同一
 *         从动站发起新的传输服务时，PSEQ+1。若超时未收到从动站的报文，
 *         或接收出现差错，则启动站不改变PSEQ，重复原来的传输服务
 *
 *  响应帧序号RSEQ
 *      (1)响应帧序号RSEQ在PRM=0时，即从动帧中有效，用编码表示0~15，用于多个从动帧对应一个启动帧的传输
 *      (2)每一对启动站和从动站之间均有1个独立的计数器，用于记录当前RSEQ，当只需一帧从动帧回应启动帧的，RSEQ=0；
 *         当需用n（n≤16）帧回应的，RSEQ从n-1起递减计数，每回送一帧减1，直至最后一帧RSEQ=0
 *         从动站发起新的传输服务时，PSEQ+1。若超时未收到从动站的报
 *
 *  帧功能码，固定帧和可变帧的帧功能码定义不同
 *
{*///

typedef enum
{
    MC_PRM_UNKWON,                 // 未知方向
    MC_PRM_A2P,                    // 该帧来自于主动站
    MC_PRM_P2A,                    // 该帧来自于从动站

}eMcPRM;                           // 控制域中PRM字段描述

// 获得某方向某命令该的PRM属性
eMcPRM emc_get_prm(eMcDir eDir, eMcAFN eAfn, BOOL bAuto);

typedef enum
{
    // 固定帧
    // PRM 0
    MC_FCD_LINK_OK      = 0,       // 确认

    // PRM 1
    MC_FCD_LOG_IN       = 1,       // 建立链路、登录系统
    MC_FCD_LOG_OUT      = 2,       // 拆除链路、退出系统
    MC_FCD_HEART_BEAT   = 3,       // 保持链路、在线心跳


    // 可变帧
    // PRM 0
    MC_FCD_OK           = 0,       // 链路用户确认
    MC_FCD_ANSWER       = 1,       // 以用户数据响应请求

    // PRM 1
    MC_FCD_NOTI         = 0,       // 发送 ∕无回答
    MC_FCD_CONF         = 1,       // 发送 ∕确认
    MC_FCD_ASK          = 2,       // 请求 ∕响应

    MC_FCD_MAX,

}eMcFcode;       // 控制域功能码

#define MC_C_LEN       (2)         // 控制域C　帧侧字长

#define MC_PSEQ_MIN    (0)         // PSEQ 最小值
#define MC_PSEQ_MAX    (31)        // PSEQ 最大值

#define MC_RSEQ_MIN    (0)         // PSEQ 最小值
#define MC_RSEQ_MAX    (15)        // PSEQ 最大值

// 用户侧
typedef struct
{
    eMcDir     eDir;               // 上下行
    eMcPRM     ePRM;               // 标志该报文是来自启动站 还是从动站
    UINT8      ucPSEQ;             // 启动帧序号 PSEQ
    UINT8      ucRSEQ;             // 响应帧序号 RSEQ
    eMcFcode   eFcode;             // 帧功能码

}sMctrl;

// 帧侧
// UINT16 usMcCtrl;
// 转换函数
eMcErr emc_trans_ctrl(eMcTrans eTrans, sMctrl* puCtrl, UINT16* pfCtrl);

// 获得 eMcFcode 帧侧对应的功能码
eMcErr emc_get_fcode(eMcmd eCmd, eMcDir eDir, eMcPRM ePRM, eMcFcode * peFcode);


// 封装函数
eMcErr emc_get_ctrl(eMcAFN eAFN, eMcDir eDir, eMcPRM ePRM, sMctrl *psCtrl);
///*}

/************************************************************
 *  应用控制域AC 结构及转换函数
 *
 *  封帧侧为1字节
 *  +------+------+------+------+------+------+------+------+
 *  |  D7  |  D6  |  D5  |  D4  |  D3  |  D2  |  D1  |  D0  |
 *  +------+------+------+------+------+------+------+------+
 *  |  Tpv |  ACD |  --  |          应用功能码 AFN          |
 *  +------+------+------+------+------+------+------+------+
 *
 *
 * Tpv 时间标签有效位 Tpv
 *     TpV=0：表示在附加信息域中[无]时间标签 Tp
 *     TpV=1：表示在附加信息域中[有]时间标签 Tp
 *
 * ACD 请示访问位
 *     ACD=1：表示有重要事件数据等待访问，且附加信息域中有 EC
 *     ACD=0：表示无重要事件数据等待访问
 *
 * AFN 应用功能码
 *     0   确认∕否认
 *     1   复位
 *     4   设置参数
 *     5   控制命令
 *     6   身份认证及密钥协商
 *     8   请求被级联信息集中与交互终端主动上报
 *     10  查询参数
 *     12  请求（定时上报）任务数据
 *     13  请求实时数据
 *     14  请求（主动上报）事件记录
 *     15  文件传输
 *     16  数据转发
 *
{*///
// 用户侧结构
typedef struct
{
    BOOL    bTp;    // 是否有Tp
    BOOL    bEc;    // 是否有Ec
    eMcAFN  eAfn;   // 应用功能码

}sMcAc;             // 应用控制域AC

// 封装侧结构
// ucAc;

// 转换函数
eMcErr emc_trans_ac(eMcTrans eTrans, sMcAc* puAc, UINT8* pfAc);
///*}

/************************************************************
 *  数据标识单元
 *  每个数据标识单元的信息是组的形式组织的
 *  每个数据标识单元包含最多(8)个Fn 及最多包含(8)个Pn
 *
 * -----
 * DADT 帧侧结构
 * 信息点 | DA | DA1 | D7 D6 D5 D4 D3 D2 D1 D0
 *        |    | DA2 | D7 D6 D5 D4 D3 D2 D1 D0
 * 信息类 | DT | DT1 | D7 D6 D5 D4 D3 D2 D1 D0
 *        |    | DT2 | D7 D6 D5 D4 D3 D2 D1 D0
 *
 * ---
 * 信息点DA由信息点元DA1和信息点组DA2两个字节构成
 * DA1 对位表示某一信息点组的1～8个信息点
 * DA2 采用二进制编码方式表示信息点组
 * DA1、DA2共同构成信息点标识pn（n = 1～2040）
 * 信息点标识pn对应于不同信息类标识Fn可以是以下各种含义
 * 测量点号、总加组号、控制轮次、直流模拟量端口号、任务号
 *
 * 信息点组DA2 | 信息点元DA1
 *       D7~D0 | D7    D6    D5    D4    D3    D2    D1    D0
 *           1 | p8    p7    p6    P5    p4    p3    p2    p1
 *           2 | p16   p15   p14   p13   p12   p11   p10   p9
 *           3 | p24   p23   p22   p21   p20   p19   p18   p17
 *          .. | ...   ...   ...   ...   ...   ...   ...   ...
 *          255| P2040 P2039 P2038 P2037 P2036 P2035 P2034 P2033
 *
 * ---
 * 信息类DT由信息类元DT1和信息类组DT2两个字节构成
 * DT1 对位表示某一信息类组的1～8种信息类型
 * DT2 采用二进制编码方式表示信息类组
 * DT1 DT2 共同构成信息类标识Fn（n = 1～248）
 *
 * 信息类组DT2 | 信息类元D T1
 *       D7~D0 | D7   D6   D5   D4   D3   D2   D1   D0
 *           0 | F8   F7   F6   F5   F4   F3   F2   F1
 *           1 | F16  F15  F14  F13  F12  F11  F10  F9
 *           2 | F24  F23  F22  F21  F20  F19  F18  F17
 *          .. | ...  ...  ...  ...  ...  ...  ...  ...
 *          30 | F248 F247 F246 F245 F244 F243 F242 F241
 *
{*///

// 用户侧结构
typedef struct
{

    UINT16  usPn[MC_PN_INDEX_MAX];      // Pn (0 ~ 2040)
                                        // MC_PN_MAX  最大值
                                        // MC_PN_MIN  最小值
                                        // MC_PN_NONE 无效值

    UINT8   ucFn[MC_FN_INDEX_MAX];      // Fn (1 ~ 248)
                                        // MC_FN_MAX  最大值
                                        // MC_FN_MIN  最小值
                                        // MC_FN_NONE 无效值
}sMcPnFn;

// 帧侧结构
typedef struct
{
    UINT8       ucDA1;         // 信息点元
    UINT8       ucDA2;         // 信息点组
    UINT8       ucDT1;         // 信息类元
    UINT8       ucDT2;         // 信息类组
}sMcDaDt;

// 转换函数
eMcErr emc_pnfn_to_dadt(sMcPnFn* psPnFn, sMcDaDt* psDaDt);
eMcErr emc_dadt_to_pnfn(sMcDaDt* psDaDt, sMcPnFn* psPnFn);

typedef struct
{
    eMcmd  eCmd;
    UINT16 usPn;
}sMcmdPn;

// 内部函数
// 获得命令对应的AFN
eMcAFN eMcGetCmdAfn(eMcmd eCmd);

// 获得命令对应的Fn
UINT8  ucMcGetCmdFn(eMcmd eCmd);

// 判断最8个Pn是否在同一个信息点组,同时取得所属的信息点组
BOOL bmc_same_team_pn(UINT16 *pUsPn8, UINT8* pucDa2);

// 判断一组Pn是否都为0
BOOL bmc_is_p0(UINT16 *pUsPn8);

// 获得pn对应的信息点组
UINT8 ucmc_get_pn_team(UINT16 usPn);

// 获得一组pn对应的信息点组
UINT8 ucmc_get_pn8_team(UINT16 *pusPn);

// 判断某一个pn是否在一组8个pn中
BOOL bmc_in_pn8(UINT16 usPn, UINT16 *pusPn8);

// 判断最8个Fn是否在同一个信息类组,同时取得所属的信息类组
BOOL bmc_same_team_fn(UINT8  *pUcFn8, UINT8* pucDt2);

// 获得Fn对应的信息点组
UINT8 ucmc_get_fn_team(UINT8 ucFn);

// 获得Fn对应的信息点在某组的bit
UINT8 ucmc_get_fn_bit(UINT8 ucFn);

// 获得一组Fn对应的信息点组
UINT8 ucmc_get_fn8_team(UINT8 *pucFn);

// 判断某一个fn是否在一组8个fn中
BOOL bmc_in_fn8(UINT8 ucFn, UINT8 *pucFn8);

// 转换函数
eMcErr emc_add_cmdpn(sMcmdPn* psCmdPn,sMcmdPn sNewCmdPn, UINT8 *pucNumCmdPn);
eMcErr emc_pnfn_to_cmdpn(eMcAFN eAfn, sMcPnFn* psPnFn, UINT8 ucNumPnFn,   sMcmdPn* psCmdPn, UINT8 *pucNumCmdPn);
eMcErr emc_cmdpn_to_pnfn(eMcAFN eAfn, sMcPnFn* psPnFn, UINT8 *pucNumPnFn, sMcmdPn* psCmdPn, UINT8  ucNumCmdPn);
eMcErr emc_dadt_to_cmdpn(eMcAFN eAfn, sMcDaDt* psDaDt, UINT8 ucNumDaDt,   sMcmdPn* psCmdPn, UINT8 *pucNumCmdPn);
eMcErr emc_cmdpn_to_dadt(eMcAFN eAfn, sMcDaDt* psDaDt, UINT8 *pucNumDaDt, sMcmdPn* psCmdPn, UINT8  ucNumCmdPn);
///*}


/************************************************************
 *  Tp 时间标签格式
 *
{*///
// 用户侧
typedef struct
{
    sMcFmt03 sTime;                 // 启动帧发送时标
    UINT8    ucPermitDelayMinutes;  // 允许发送传输延时时间(分钟);
}sMcTp;

// 封帧侧
#pragma pack(1)
typedef struct
{
    sMcFmt03_f sTime;                 // 启动帧发送时标
    UINT8      ucPermitDelayMinutes;  // 允许发送传输延时时间(分钟);
}sMcTp_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_tp(eMcTrans eTrans, sMcTp* pUser, sMcTp_f* pFrame);

// 获得当前用户侧Tp
eMcErr emc_get_tp(sMcTp *psuTp);   

// 以当前时间为基准判断一个tp是否超时
BOOL  bmc_tp_timeout(sMcTp *psTP);
///*}

/*******************************************
 *  数据项相关
 *  协议允许应答中每个实际的数据项为空,在帧侧需要将该数据内容域填充0xEE
{*///
BOOL   bmc_is_0xEE(UINT8* pData, UINT16 usLen);    // 判断帧侧某数据项是否是无效的
void   vmc_set_0xEE(UINT8* pData, UINT16 usLen);   // 将帧侧某数据项设置为无效

BOOL   bmc_is_none(UINT8* pData, UINT16 usLen);    // 数据项缺少
void   vmc_set_none(UINT8* pData, UINT16 usLen);   // 将数据项设置为缺少
///*}

/************************************************************
 *  附加信息域 AUX 定义
 *
{*///

BOOL   bmc_have_pw(eMcAFN eAFN, eMcDir eDir);      // 此类报文中是否应该有pw字段
BOOL   bmc_have_ec(eMcAFN eAFN, eMcDir eDir);      // 此类报文中是否应该有EC字段
BOOL   bmc_have_tp(eMcAFN eAFN, eMcDir eDir);      // 此类报文中是否应该有tp字段

// 用户侧
typedef struct
{
    UINT16 usEC1;              // 重要事件计数器 EC1
    UINT16 usEC2;              // 一般事件计数器 EC2
}sMcEc, sMcEc_f;

// 事件计数设置函数
void vmc_set_ec(sMcEc *psEc);

// 获得报文中附加域的帧侧的总字节数据
UINT16 usmc_get_aux_len(eMcAFN eAFN, eMcDir eDir, BOOL bEc, BOOL bTp); 
///*}
///*}

/*******************************************************
 *  加密与解密函数
 *  关键数据的加密
 *  加密算法:对于应用层需要加密的关键数据,采用对称算法进行数据加解密
 *  加密部分:应用层功能码、数据单元标识及数据单元部分
 *  加密长度:通过密码机采用对称密钥算法将明文数据加密成密文,用户数据长度会相应改变
 *           终端在收到采用对称密钥算法加密的密文信息后,对数据进行解密
 *           解密成功返回原始的明文信息及明文信息的数据长度
 *  报文类型:需要加密的报文类型
 *           (1)复位命令的下行报文
 *           (2)设置参数命令的下行报文
 *           (3)控制命令的下行报文
 *
 *  我的疑问: AFN是否应该加密   如果某加密将无法区分哪个类型加密
 *
{*///
#if MC_CFG_ENCRYPT
// 加密函数类型
typedef eMcErr (*peMcEncryptFunc)(UINT8* pInData, int nInLen, UINT8* pOutData, int *pOutLen);  

// 解密函数类型
typedef eMcErr (*peMcDecryptFunc)(UINT8* pInData, int nInLen, UINT8* pOutData, int *pOutLen);  
#endif
///*} 

/*******************************************************
 *  各数据项定义
 *  
 *  用户侧:默认字节对齐, 供上层调用时使用
 *  封帧侧:1字节对齐,用于封装帧和解析帧
 *  解析函数:实现对各Fn用户侧和封帧侧数据结构的转换功能  
 *  
 *
{*///

/*******************************************
 * 数据名称: 全部确认/否认：对收到报文中的全部数据单元标识进行确认/否认
 * 对应AFN : MC_AFN_00_CONF
 * 对应CMD : MCMD_AFN_0_F1_ALL_OK_DENY
 * PN 类型 : P0
{*///

// 用户结构
typedef enum
{
    MC_RES_OK          = 0,    // 确认
    MC_RES_NONE        = 1,    // 无请求的数据、无设置的参数、无要执行的功能
    MC_RES_NOT_READY   = 2,    // 请求的数据未产生、功能执行未满足
    MC_RES_REMOVE      = 3,    // 请求的数据已经被移出保存窗口
    MC_RES_DATA_OTRNG  = 4,    // 请求的数据超出支持的信息点范围
    MC_RES_PARA_OTRNG  = 5,    // 设置的参数超出支持的信息点范围
    MC_RES_NOT_SAME    = 6,    // 设置的接入端口号及属性与实际不符
    MC_RES_NOT_SUPT    = 7,    // 指定接口不支持转发
    MC_RES_DENY        = 255   // 否认
    
}eMcResCode, sMcAfn00F1;                   // 确认/否认信息码定义 

// eMcResCode    eResCode;

// 封帧结构
//UINT8  ucResCode;

// 转换函数
eMcErr emc_trans_afn00f1(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 逐个确认与否认
 * 对应AFN : MC_AFN_00_CONF
 * 对应CMD : MCMD_AFN_0_F2_ONE_BY_ONE
 * PN 类型 : P0
{*///
// 用户侧数据
typedef struct
{
    eMcmd       eCmd;         // 确认对应的功能码
    UINT16      usPn;         // Pn  0 ~ 2040
    eMcResCode  eResCode;     // 答复码
}sMcmdErr;                    // 确认与否认 用户侧数据结构

typedef struct
{
    eMcAFN        eAFN;       // 需要确认的AFN
    UINT8        ucNum;       // 需要确认 或 否认的 Fn个数
    sMcmdErr   sOne[1];       // ucNum 个sMtUFnPnErr  
}sMcOnebyOne;                 // 确认与否认 (用户侧数据结构)

// 帧侧数据
#pragma pack(1) 
typedef struct
{
    sMcPnFn     sPnFn;
    eMcResCode  eResCode;
}sMcFnPnErr;                   // 确认与否认 用户侧数据结构

typedef struct
{
    sMcDaDt     sDaDt;         // 数据单元标识
    UINT8       ucErr;         // 错误 标识   (0 正确 1 错误)
}sMcOne_f;                     // 确认与否认  帧侧数据结构   

typedef struct
{
    UINT8       ucAFN;
    sMcOne_f    sOne[1];
}sMcOneByOne_f;
#pragma pack()

// 转换函数
eMcErr emcTrans_OneByOne(eMcTrans eTrans,void* psUser, void* psFrame, UINT16* pusfLen);
///*} 

/*******************************************
 * 数据名称: 指定数据清零(仅实时数据单元标识有效)
 * 对应AFN : MC_AFN_01_RSET
 * 对应CMD : MCMD_AFN_1_F5_DATA_CLEAR
 * PN 类型 : P0
{*///

// 用户侧
typedef struct
{
    UINT8   ucNum;      // 清零的数据项个数
    sMcmdPn sCmdPn[1];  // ucNum 个命令与pn的组合

}sMcDataClear, sMcAfn01f5, sMcRtDataClear;

// 封装侧
#pragma pack(1)
typedef struct
{
    UINT8    ucNum;    // 数据单元标识个数
    sMcDaDt  sDaDt[1]; // ncNum个数据单元标识

}sMcDataClear_f, sMcAfn01f5_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn01f5(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 信息集中与交互终端上行通信口通信参数
 * 对应AFN : MC_AFN_04_SETP
 * 对应CMD : MCMD_AFN_4_F1_CON_UP_CFG
 * PN 类型 : P0
{*///
// 用户侧
typedef struct
{
    UINT8  ucPermitDelayM;    // 信息集中与交互终端作为启动站允许传输延时时间 (单位:分钟 0~255)
    UINT8  ucReSendTimes;     // 重发次数 (0~3)   0 表示不允许重发
    UINT8  ucHeartBeat;       // 心跳周期
    UINT16 usWaitTimeoutS;    // 信息集中与交互终端作为启动站等待应答的超时时间 (秒数 0~4095)
    BOOL   bPermitRt;         // 实时数据 是否允许信息集中与交互终端需要主(子)站确认
    BOOL   bPermitTk;         // 任务数据 是否允许信息集中与交互终端需要主(子)站确认
    BOOL   bPermitEv;         // 事件数据 是否允许信息集中与交互终端需要主(子)站确认

}sMcUpCfg, sMcAfn04f1;

// 封装侧
#pragma pack(1)
typedef struct
{
    UINT8  ucPermitDelayM;    // 信息集中与交互终端作为启动站允许传输延时时间
    UINT8  ucSWTS1;           // 信息集中与交互终端作为启动站等待应答的超时时间和重发次数
    UINT8  ucSWTS2;           // 终端等待从动站响应的超时时间和重发次数 wait ts
    UINT8  bs8Con;            // 信息集中与交互终端作为启动站需确认应答的传输服务标志 
    UINT8  ucHeartBeat;       // 心跳周期

}sMcUpCfg_f, sMcAfn04f1_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn04f1(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 主(子)站参数
 * 对应AFN : MC_AFN_04_SETP
 * 对应CMD : MCMD_AFN_4_F2_MST_PARA
 * PN 类型 : P0
{*///
typedef enum
{
    MC_IP_UNKOWN,
    MC_IP_V4,
    MC_IP_V6,
}eMcIp;

// IP地址 子网掩码
typedef struct
{
    eMcIp eVersion;
    UINT8 ip[MC_IP_LEN];
}sMcIp, sMcMask;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8  ucVersion;
    UINT8 ip[MC_IP_LEN];

}sMcIp_f, sMcMask_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_ip(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);

// 用户侧
typedef struct
{
    UINT8          ucID;   // 主站1的编号
    BOOL         bValid;   // 参数有效性
    UINT8       ucNoNum;   // 不允许其它主站或子站设置的数据单元标识个数 (0~8)  这个应该是有问题的
    sMcmdPn   sCmdPn[8];   // 不允许其它主站或子站设置的数据单元标识 ucNoNum
    sMcIp       sMainIP;   // 主用地址
    UINT16   usMainPort;   // 主用端口
    sMcIp       sBackIP;   // 备用地址
    UINT16   usBackPort;   // 备用端口 
    UINT8  ucascAPN[16];   // APN
    UINT8       usr[32];   // 用户名
    UINT8       pwd[32];   // 密码
}sMcMstParaOne;

typedef struct
{
    UINT8              ucN;  // 本次设置的主(子)站数n 取值范围 0～255 其中：0 表示删除所有的主(子)站参数)
    sMcMstParaOne  sOne[1];  // ucN个信息
}sMcMstPara, sMcAfn04f2;

// 封装侧
#pragma pack(1)
typedef struct
{
    UINT8             ucID;  // 主站1的编号
    UINT8         bs8Valid;  // 主(子)站有效性标志：表示对应的主(子)站的参数有效性，其中“D0”=1：有效，“D0”=0：删除，其他：备用
    sMcDaDt          sDaDt;  // 不允许其它主站或子站设置的数据单元标识
    sMcIp_f        sMainIP;   // 主用地址
    UINT16      usMainPort;   // 主用端口
    sMcIp_f        sBackIP;   // 备用地址
    UINT16      usBackPort;   // 备用端口 
    UINT8     ucascAPN[16];   // APN
    UINT8          usr[32];   // 用户名
    UINT8          pwd[32];   // 密码 
}sMcMstParaOne_f;

typedef struct
{
    UINT8               ucN;  // 本次设置的主(子)站数n 取值范围 0～255 其中：0 表示删除所有的主(子)站参数)
    sMcMstParaOne_f sOne[1];  
}sMcMstPara_f, sMcAfn04f2_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn04f2(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 信息集中与交互终端上行通信消息认证参数
 * 对应AFN : MC_AFN_04_SETP
 * 对应CMD : MCMD_AFN_4_F3_CON_AUTH_PARA
 * PN 类型 : P0
{*///
// 用户侧
typedef struct
{
    UINT8     ucTypeID;   // 用于表示由系统约定的各种消息认证方案，取值范围0～255，其中：0表示不认证，255表示专用硬件认证方案，1～254用于表示各种软件认证方案
    UINT16    usAuthPara; // 消息认证方案参数

}sMcAuthPara, sMcAfn04f3;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8     ucTypeID;   // 用于表示由系统约定的各种消息认证方案，取值范围0～255，其中：0表示不认证，255表示专用硬件认证方案，1～254用于表示各种软件认证方案
    UINT16    usAuthPara; // 消息认证方案参数

}sMcAuthPara_f, sMcAfn04f3_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn04f3(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 信息集中与交互终端组地址
 * 对应AFN : MC_AFN_04_SETP
 * 对应CMD : MCMD_AFN_4_F4_TEAM_ADDR
 * PN 类型 : P0
{*///

#define MC_TEAD_ADD_NUM (8)
// 用户侧
typedef struct
{
    UINT32 ulAddr[MC_TEAD_ADD_NUM];
    
}sMcTeamAddr, sMcAfn04f4;

// 封帧侧
typedef sMcTeamAddr sMcTeamAddr_f, sMcAfn04f4_f;

// 转换函数
eMcErr emc_trans_afn04f4(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 信息集中与交互终端IP地址和端口
 * 对应AFN : MC_AFN_04_SETP
 * 对应CMD : MCMD_AFN_4_F5_CON_IP_PORT
 * PN 类型 : P0
{*///
// 用户侧
typedef enum
{
    MC_DELG_UNKOWN,  // 未知代理 
    MC_DELG_NULL,    // 不使用代理
    MC_DELG_HTTP,    // 使用http connect代理
    MC_DELG_SOCK4,   // 使用sock4代理
    MC_DELG_SOCK5,   // 使用sock5代理
   
}eMcDelegate;

// 代理服务器连接方式
typedef enum
{
    MC_DELK_UNKOWN, // 未知方式
    MC_DELK_ANYONE, // 无需要验证
    MC_DELK_USRPWD, // 需要用户名和密码
}eMcDelgLink;

typedef struct
{
    UINT16          usPort;       // 信息集中与交互终端侦听端口 
    sMcIp           sConIp;       // 信息集中与交互终端IP地址
    sMcMask          sMask;       // 子网掩码地址
    sMcIp          sGateIp;       // 网关地址
    eMcDelegate  eDelegate;       // 代理类型
    sMcIp          sDelgIp;       // 代理服务地址IP地址
    UINT16      usDelgPort;       // 代理服务端口
    eMcDelgLink  eDelgLink;       // 代理服务器连接方式
    BOOL          bDlegUsr;       // 是否需要代理服务器用户名
    UINT8     ucDlegUsrLen;       // 代理服务器用户名长度 (1~20)
    UINT8    ucDlegUsr[20];       // 代理服务器用户名   
    BOOL          bDlegPwd;       // 是否需要
    UINT8     ucDlegPwdLen;       // 代理服务器密码长度   (1~20)
    UINT8    ucDlegPwd[20];       // 代理服务器密码
     
}sMcIpPort, sMcAfn04f5;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT16          usPort;       // 信息集中与交互终端侦听端口 
    sMcIp_f         sConIp;       // 信息集中与交互终端IP地址
    sMcMask_f        sMask;       // 子网掩码地址
    sMcIp_f        sGateIp;       // 网关地址
    UINT8       ucDelegate;       // 代理类型
    sMcIp_f        sDelgIp;       // 代理服务地址IP地址
    UINT16      usDelgPort;       // 代理服务端口
    UINT8       ucDelgLink;       // 代理服务器连接方式
    UINT8         ucUsrLen;       // 代理服务器用户名长度m (0~20) 0表示不需要用户名验证
    /* 以下为变长
    UINT8     ucDlegUsr[m];       // 代理服务器用户名
    UINT8     ucDlegPwdLen;       // 代理服务器密码长度 n  (0~20) 0表示不需要密码验证
    UINT8     ucDlegPwd[n];       // 代理服务器密码
    */ 
    
}sMcIpPort_f, sMcAfn04f5_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn04f5(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 信息集中与交互终端级联通信参数
 * 对应AFN : MC_AFN_04_SETP
 * 对应CMD : MCMD_AFN_4_F6_CON_CASC  和MCMD_AFN_A_F6_CON_CASC
 * PN 类型 : P0
{*///
typedef enum
{
    MC_BAUD_UNKOWN,
    MC_BAUD_DEFAULT,        // 无须设置或使用默认
    MC_BAUD_1200,            
    MC_BAUD_2400,
    MC_BAUD_4800,
    MC_BAUD_9600,
    MC_BAUD_19200,
    MC_BAUD_38400,         
    MC_BAUD_76800,   
}eMcSerBaud;                // 串口波特率

typedef enum
{
    MC_SBIT_5,
    MC_SBIT_6,
    MC_SBIT_7,
    MC_SBIT_8,

}eMcSerBit;

typedef struct
{
    eMcSerBaud      eBaud;  // 波特率
    BOOL           bStop1;  // 1停止位(true) 2停止位(false)
    BOOL           bCheck;  // 有校验(true) 无校验(false) 
    BOOL             bOdd;  // 奇校验(true) 偶校验(true)
    eMcSerBit        eBit;  // 5~8位数
}sMcAcsParaSer;             // 接入端口运行参数数据格式-串口

// 结构sMcAcsParaSer 转换函数
eMcErr emc_trans_serial(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);

typedef enum
{
    MC_CASC_UNKOWN,   // 未知级联方式
    MC_CASC_NULL,     // 不启用级联功能
    MC_CASC_RS485,    // RS485级联
    MC_CASC_ETH       // 以太网级联
}eMcTypeCasc;         // 级联方式

typedef struct
{
     UINT8  acRegionCode[MC_REGN_LEN];   // 被级联/级联方的信息集中与交互终端行政区划码
     UINT32 ulConAddr;                   // 被级联/级联方的信息集中与交互终端地址
     sMcIp  sIp;                         // 被级联/级联方的信息集中与交互终端通信地址
     UINT16 usPort;                      // 被级联/级联方的信息集中与交互终端端口地址
}sMcascAddr;          // 级联地址

// 用户侧
typedef struct
{
    eMcTypeCasc    eType;    // 信息集中与交互终端级联接入方式
    sMcAcsParaSer  sSer;     // 信息集中与交互终端级联通信控制字
    UINT8          ucWaitP;  // 接收等待报文超时时间(单位 100ms)
    UINT8          ucWaitC;  // 接收等待字节超时时间(单位 10ms)
    UINT8          ucReTry;  // 级联方（主动站）接收失败重发次数
    UINT8          ucPeriod; // 级联巡测周期(单位: 分钟)
    UINT8          ucN;      // 级联/被级联标志、及其对应的被级联/级联的信息集中与交互终端个数n
    sMcascAddr     sOne[1];  // ucN 
}sMcasc, sMcAfn04f6;

#pragma pack(1)
typedef struct
{
     UINT8     acRegionCode[MC_A1_LEN];     // 被级联/级联方的信息集中与交互终端行政区划码
     UINT32    ulConAddr;                   // 被级联/级联方的信息集中与交互终端地址
     sMcIp_f   sIp;                         // 被级联/级联方的信息集中与交互终端通信地址
     UINT16    usPort;                       // 被级联/级联方的信息集中与交互终端端口地址
}sMcascAddr_f;          // 级联地址

// 封帧侧
typedef struct
{
    UINT8          eType;    // 信息集中与交互终端级联接入方式
    UINT8          sSer;     // 信息集中与交互终端级联通信控制字
    UINT8          ucWaitP;  // 接收等待报文超时时间(单位 100ms)
    UINT8          ucWaitC;  // 接收等待字节超时时间(单位 10ms)
    UINT8          ucReTry;  // 级联方（主动站）接收失败重发次数
    UINT8          ucPeriod; // 级联巡测周期(单位: 分钟)
    UINT8          ucN;      // 级联/被级联标志、及其对应的被级联/级联的信息集中与交互终端个数n
    sMcascAddr_f   sOne[1];  // ucN 
}sMcasc_f, sMcAfn04f6_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn04f6(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 信息集中与交互终端下行以太网端口通信参数
 * 对应AFN : MC_AFN_04_SETP
 * 对应CMD : MCMD_AFN_4_F7_CON_DOWN_CFG
 * PN 类型 : P0
{*///

// 用户侧
#define MC_APN_LEN  (16)
typedef struct
{
    UINT8       ucPort;              // 信息集中与交互终端的下行通信端口号
    sMcIp       sMainIp;             // 主用IP地址
    UINT16      usMainPort;          // 主用端口地址
    sMcIp       sBackIp;             // 备用IP地址
    UINT16      usBackPort;          // 备用端口地址
    UINT8       ucAPN[MC_APN_LEN];   // APN
    UINT8       ucUsr[32];           // 用户名
    UINT8       ucPwd[32];           // 密码
    
}sMcDownCfg, sMcAfn04f7;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8       ucPort;              // 信息集中与交互终端的下行通信端口号
    sMcIp_f     sMainIp;             // 主用IP地址
    UINT16      usMainPort;          // 主用端口地址
    sMcIp_f     sBackIp;             // 备用IP地址
    UINT16      usBackPort;          // 备用端口地址
    UINT8       ucAPN[MC_APN_LEN];   // APN
    UINT8       ucUsr[32];           // 用户名
    UINT8       ucPwd[32];           // 密码
}sMcDownCfg_f, sMcAfn04f7_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn04f7(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 事件记录配置
 * 对应AFN : MC_AFN_04_SETP
 * 对应CMD : MCMD_AFN_4_F9_CON_EVENT_CFG
 * PN 类型 : P0
{*///

// 用户侧
typedef struct
{   
    UINT8      ucNeed;    // 需要记录的事件记录的类型个数   
    eMcErc  aNeed[64];    // ucErcNeed个需要记录的事件记录具体类型
    UINT8      ucImpt;    // 设置为重要事件的个数
    eMcErc  aImpt[64];    // ucErcImpt个事件设置为重要的事件(那么其余的就是一般事件)
                          // 事件重要性等级标志位：D0～D63 按顺序对位表示事件代码 ERC1～ERC64 所定义的事件。
                          //     置“1”：该位所对应的告警事件为重要事件，该事件发生后，如通道具备主动上报条件，
                          // 应主动上报事件记录，如不具备主动上报条件，通过 ACD 位上报；
                          //     置“0”：该位所对应的告警事件为一般事件，该事件发生后，只需要进行事件记录；
    UINT16   usImpRecNum; // 重要事件记录条数：指需要记录的重要事件条数，默认值为 255
    UINT16   usNmlRecNum; // 一般事件记录条数：指需要记录的一般事件条数，默认值为 255
}sMcEventCfg, sMcAfn04f9;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8     aNeed[8];   // 事件记录有效标志位
    UINT8     aImpt[8];   // 事件重要性等级标志位
    UINT16  usImpRecNum;  // 重要事件记录条数：指需要记录的重要事件条数，默认值为 255
    UINT16  usNmlRecNum;  // 一般事件记录条数：指需要记录的一般事件条数，默认值为 255
   
}sMcEventCfg_f, sMcAfn04f9_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn04f9(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 设备状态量输入参数
 * 对应AFN : MC_AFN_04_SETP
 * 对应CMD : MCMD_AFN_4_F10_CON_STATE_INPUT MCMD_AFN_A_F10_CON_STATE_INPUT
 * PN 类型 : P0
{*///
// 用户侧
typedef struct
{
    BOOL bIn[8];       // 状态量接入标志位（对应 1～8 路状态量）置true接入.      置 false 未接入
    BOOL bOn[8];       // 状态量属性标志位（对应 1～8 路状态量） 置true常开触点。置 false 常闭触点

}sMcStateInput, sMcAfn04f10;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8 bIn;
    UINT8 bOn;

}sMcStateInput_f, sMcAfn04f10_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn04f10(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 监测终端上行通信参数配置
 * 对应AFN : MC_AFN_04_SETP
 * 对应CMD : MCMD_AFN_4_F17_TML_UP_CFG  MCMD_AFN_A_F17_TML_UP_CFG
 * PN 类型 : P0
{*///

#define MC_TML_UP_PROTO   (1) // 终端上行通信协议类型
// 用户侧
typedef enum
{
   MC_TUPP_UNKOWN,              // 未知属性
   MC_TUPP_DEL,                 // 删除该监测终端号的配置参数
   MC_TUPP_SER,                 // 串口
   MC_TUPP_ETH,                 // 以太网

}eMcUpPara;                     // 监测终端上行通信端口属性

typedef struct
{
    UINT8       ucDownPort;     // 信息集中与交互终端的下行通信端口号
    UINT16    usListenPort;     // 监测终端侦听信端口号 
    eMcUpPara      eUpPara;     // 监测终端上行通信端口属性
    sMcA           sUpAddr;     // 监测终端上行通信地址
    UINT8        ucUpProto;     // 监测终端上行通信协议类型 MC_TML_UP_PROTO
    sMcIp            sUpIp;     // 监测终端上行IP地址
    sMcMask        sUpMask;     // 监测终端子网掩码地址
    sMcIp          sGateIp;     // 网关地址
    eMcDelegate  eDelegate;     // 代理类型
    sMcIp          sDelgIp;     // 代理服务地址IP地址
    UINT16      usDelgPort;     // 代理服务端口
    eMcDelgLink  eDelgLink;     // 代理服务器连接方式
    BOOL          bDlegUsr;     // 是否需要代理服务器用户名
    UINT8     ucDlegUsrLen;     // 代理服务器用户名长度 (1~20)
    UINT8    ucDlegUsr[20];     // 代理服务器用户名   
    BOOL          bDlegPwd;     // 是否需要
    UINT8     ucDlegPwdLen;     // 代理服务器密码长度   (1~20)
    UINT8    ucDlegPwd[20];     // 代理服务器密码
    UINT8   ucPermitDelayM;     // 监测终端作为启动站允许传输延时时间 (单位:分钟 0~255)
    UINT8    ucReSendTimes;     // 重发次数 (0~3)   0 表示不允许重发
    UINT8      ucHeartBeat;     // 心跳周期
    UINT16  usWaitTimeoutS;     // 监测终端作为启动站等待应答的超时时间 (秒数 0~4095)
    BOOL         bPermitRt;     // 实时数据 是否允许监测终端需要集中器确认
    BOOL         bPermitTk;     // 任务数据 是否允许监测终端需要集中器确认
    BOOL         bPermitEv;     // 事件数据 是否允许监测终端需要集中器确认

}sMcTmlUpCfg, sMcAfn04f17;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8       ucDownPort;     // 信息集中与交互终端的下行通信端口号(0~255)
    UINT16    usListenPort;     // 监测终端侦听信端口号 
    UINT8         ucUpPara;     // 监测终端上行通信端口属性 
    sMcA_f         sUpAddr;     // 监测终端上行通信地址 
    UINT8        ucUpProto;     // 监测终端上行通信协议类型
                                // 数值范围 1～255，其中，1：GB/TXXX.3-2-2013：
                                // 2~100：备用；101～255 为自定义协议。
    sMcIp_f          sUpIp;     // 监测终端上行IP地址
    sMcMask_f      sUpMask;     // 监测终端子网掩码地址
    sMcIp_f        sGateIp;     // 网关地址
    UINT8       ucDelegate;     // 代理类型
    sMcIp_f        sDelgIp;     // 代理服务地址IP地址
    UINT16      usDelgPort;     // 代理服务端口
    UINT8       ucDelgLink;     // 代理服务器连接方式
    UINT8         ucUsrLen;     // 代理服务器用户名长度m (0~20) 0表示不需要用户名验证
    /* 以下为变长
    UINT8     ucDlegUsr[m];     // 代理服务器用户名
    UINT8     ucDlegPwdLen;     // 代理服务器密码长度 n  (0~20) 0表示不需要密码验证
    UINT8     ucDlegPwd[n];     // 代理服务器密码

    // 和结构 sMcUpCfg_f 相同
    UINT8  ucPermitDelayM;      // 信息集中与交互终端作为启动站允许传输延时时间 
    UINT8  ucSWTS1;             // 信息集中与交互终端作为启动站等待应答的超时时间和重发次数
    UINT8  ucSWTS2;             // 终端等待从动站响应的超时时间和重发次数 wait ts
    UINT8  bs8Con;              // 信息集中与交互终端作为启动站需确认应答的传输服务标志 
    UINT8  ucHeartBeat;         // 心跳周期                     
    */ 
}sMcTmlUpCfg_f, sMcAfn04f17_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn04f17(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 电气测量点配置参数
 * 对应AFN : MC_AFN_04_SETP
 * 对应CMD : MCMD_AFN_4_F25_ELEC_MP_CFG
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef enum
{
   MC_ACS_PROT_UNKOWN,      // 未知通信协议类型
   //MC_ACS_PROT_GBNX31,    // GB/TXXXX.3.1-2013
   MC_ACS_PROT_GBNX_32,     // GB/TXXXX.3.1-2013
   MC_ACS_PROT_DLT645_97,   // DL/T645-1997
   MC_ACS_PROT_DLT645_07,   // DL/T645-2007
   MC_ACS_PROT_MODBUS,      // Modbus
   MC_ACS_PROT_USER = 128,  // (128~255)表示自定义

}eMcAcsProto;               // 接入设备通信类型

typedef enum
{
    MC_ACS_PORT_UNKOWN,     // 未知接口属性
    MC_ACS_PORT_DC,         // 直流模拟量
    MC_ACS_PORT_AC,         // 交流模拟量
    MC_ACS_PORT_SER,        // 串口(RS485/RS232)
    MC_ACS_PORT_ETH,        // 以太网
    MC_ACS_PORT_ZIGB,       // zigbee
    MC_ACS_PORT_USER = 128, // 128~255 用户自定义 
    
}eMcAcsPort;                // 接入端口属性

typedef struct
{
    UINT16          usPort; // 接入设备侦听端口号
    sMcIp          sAccess; // 接入设备IP地址
    /* 电科院内部版 
    sMcMask          sMask; // 子网掩码地址
    sMcIp            sGate; // 网关地址
    */
}sMcAcsParaEth;             // 接入端口运行参数数据格式-以太网

typedef struct
{
    UINT16             usID;     // 所属信息集中与交互终端/监测终端号
                                 // 是0 表示电气测量点接入信息集中与交互终端
                                 // 非0 表示电气测量点接入能效监测终端
    UINT8            ucPort;     // 1 ~ 255
    UINT8        ucAddr[16];     // 接入设备通信地址
    eMcAcsProto   eAcsProto;     // 接入设备通信协议类型
    UINT8          ucPwd[6];     // 通信密码
    
    eMcAcsPort     eAcsPort;     // 接入终端属性 决定 uPortPara的内容
    union
    {
                                 // eAcsPort == MC_ACS_PORT_DC   直流模拟量无参数数据
                                 // eAcsPort == MC_ACS_PORT_AC   交流模拟量无参数数据
        sMcAcsParaSer  sSer;     // eAcsPort == MC_ACS_PORT_SER  串口运行参数
        sMcAcsParaEth  sEth;     // eAcsPort == MC_ACS_PORT_ETH  以太网运行参数
        UINT32   ulAddrZigb;     // eAcsPort == MC_ACS_PORT_ZIGB Zigbee地址 
        
    }uPortPara;                  // 接入端口运行参数内容

    UINT16        usAcsPort;     // 接入设备侦听端口号

    sMcIp           sAccess;     // 接入设备IP地址

    /* 电科院内部版 
    sMcMask           sMask;     // 子网掩码地址
    sMcIp           sGateIp;     // 网关地址
    */

}sMcElecMpCfg, sMcAfn04f25;

// 封帧侧
#pragma pack(1)

typedef struct
{
    UINT16            usPort;    // 接入设备侦听端口号
    sMcIp_f          sAccess;    // 接入设备IP地址

    /*
    sMcMask_f          sMask;    // 子网掩码地址
    sMcIp_f            sGate;    // 网关地址
    */
}sMcAcsParaEth_f;                // 接入端口运行参数数据格式-以太网

typedef struct
{
    UINT16             usID;     // 所属信息集中与交互终端/监测终端号
                                 // 是0 表示电气测量点接入信息集中与交互终端
                                 // 非0 表示电气测量点接入能效监测终端
    UINT8            ucPort;     // 1 ~ 255
    UINT8      ucAddrBcd[8];     // 接入设备通信地址(BCD)
    UINT8         eAcsProto;     // 接入设备通信协议类型
    UINT8          ucPwd[6];     // 通信密码
    UINT8          eAcsPort;     // 接入终端属性
    UINT8      ucAcsParaLen;     // 对应的运行参数的结构长度

    /* 变长的运行参数结构
                                 // MC_ACS_PORT_DC 直流模拟量无参数数据
                                 // MC_ACS_PORT_AC 交流模拟量无参数数据
    UINT8            sSer;       // MC_ACS_PORT_SER  串口运行参数
    sMcAcsParaEth_f  sEth;       // MC_ACS_PORT_ETH  以太网运行参数
    UINT32   ulAddrZigb;         // MC_ACS_PORT_ZIGB Zigbee地址 

    */

    /* 以下接上边变长结构之后
    UINT16        usAcsPort;     // 接入设备侦听端口号
    sMcMask_f         sMask;     // 子网掩码地址
    sMcIp_f          sGateIp;    // 网关地址
    */
}sMcElecMpCfg_f, sMcAfn04f25_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn04f25(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 电气测量点基本参数
 * 对应AFN : MC_AFN_04_SETP
 * 对应CMD : MCMD_AFN_4_F26_ELEC_MP_BASE
 * PN 类型 : 电气测量点号
{*///

#define MC_DNUM_INTGR_MIN   (4)  // 整数位数最小值
#define MC_DNUM_INTGR_MAX   (7)  // 整数位数最大值

#define MC_DNUM_DECIM_MIN   (1)  // 小数位数最小值
#define MC_DNUM_DECIM_MAX   (4)  // 小数位数最大值

typedef struct
{
    UINT8       ucInteger; // 有功电能示值的整数位个数(4~7)
    UINT8       ucDecimal; // 有功电能示值的小数位个数(1~4)
}sMcDigitNum;    

typedef enum
{   
    MC_LINK_UNKOWN, // 未知
    MC_LINK_P3_L3,  // 三相三线
    MC_LINK_P3_L4,  // 三相四线
    MC_LINK_P1,     // 单相表
    
}eMcLink;

typedef enum
{
    MC_PHASE_UNKOWN, // 未知
    MC_PHASE_A,      // A 相
    MC_PHASE_B,      // B 相
    MC_PHASE_C,      // C 相
    
}eMcPhase;

typedef struct
{
    eMcLink    eLink;
    eMcPhase   ePhase;
    
}sMcLinkWay; // 电源接线方式

// 用户侧
typedef struct
{
    sMcDigitNum      sDigit; // 有功电能示值整数位及小数位个数
    UINT16         usTimesU; // 电压互感器倍率
    UINT16         usTimesI; // 电流互感器倍率
    float                fU; // 额定电压   (+)XXX.X  (V)
    float                fI; // 额定电流(+/-)XXX.XXX (A)
    sMcLinkWay     sLinkWay; // 电源接线方式
}sMcElecMpBase, sMcAfn04f26;

// 封帧侧
#pragma pack(1)
typedef struct
{   
    UINT8            sDigit; // 有功电能示值整数位及小数位个数
    UINT16         usTimesU; // 电压互感器倍率
    UINT16         usTimesI; // 电流互感器倍率
    sMcFmt_XXX_X         fU; // 额定电压   (+)XXX.X   (V)
    sMcFmt_sXXX_XXX      fI; // 额定电流 (+/-)XXX.XXX (A)
    UINT8          sLinkWay; // 电源接线方式
    
}sMcElecMpBase_f, sMcAfn04f26_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn04f26(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 电气测量点电能量限值参数
 * 对应AFN : MC_AFN_04_SETP
 * 对应CMD : MCMD_AFN_4_F27_ELEC_LMIT_POWER
 * PN 类型 : 电气测量点号
{*///
typedef struct
{
    float          fUpUp;        // 电压上上限(过压门限) (+)XXX.X
    UINT8         ucTime;        // 持续时间
    float        fFactor;        // 越限恢复系数         (+)XX.XX 
}sMcOverV;                       // 过压判别参数

typedef struct
{
    float      fDownDown;        // 电压下下限(过压门限) (+)XXX.X
    UINT8         ucTime;        // 持续时间
    float        fFactor;        // 越限恢复系数         (+)XX.XX   
}sMcLossV;                       // 欠压判别参数 

typedef struct
{
    float          fUpUp;        // 电流上上限() (+/-)XXX.XXX
    UINT8         ucTime;        // 持续时间
    float        fFactor;        // 越限恢复系数         (+)XX.XX   
}sMcOverI;                       // 过流判别参数

typedef struct
{
    float            fUp;        // 电流上限(额定电流上限) (+/-)XXX.XXX
    UINT8         ucTime;        // 持续时间
    float        fFactor;        // 越限恢复系数         (+)XX.XX   
}sMcSuperI;                      // 超额定电流判别参数

typedef struct
{
    float            fUp;        // 0序电流上限 (+/-)XXX.XXX
    UINT8         ucTime;        // 持续时间
    float        fFactor;        // 越限恢复系数         (+)XX.XX   
}sMcZeroI;                       // 零序电流超限判别参数

typedef struct
{
    float         fLimit;        // 三相电压不平衡度限值 (+/-)XX.XXXX
    UINT8         ucTime;        // 持续时间
    float        fFactor;        // 越限恢复系数         (+)XX.XX   
}sMcUnblnV;                      // 三相电压不平衡超限判别参数

typedef struct
{
    float         fLimit;        // 三相电流不平衡度限值 (+/-)XX.XXXX
    UINT8         ucTime;        // 持续时间
    float        fFactor;        // 越限恢复系数         (+)XX.XX   
}sMcUnblnI;                      // 三相电流不平衡超限判别参数

// 用户侧
typedef struct
{
    float             fDropV;    // 电压断相判别参数  (+)XXX.X
    UINT8        ucTimeLossV;    // 电压失压时间判别参数 minutes
    sMcOverV          sOverV;    // 过压判别参数
    sMcLossV          sLossV;    // 欠压判别参数
    sMcOverI          sOverI;    // 过流判别参数
    sMcSuperI        sSuperI;    // 超额定电流判别参数
    sMcZeroI          sZeroI;    // 零序电流超限判别参数
    sMcUnblnV          sUblV;    // 三相电压不平衡超限判别参数
    sMcUnblnI          sUblI;    // 三相电流不平衡超限判别参数
}sMcElecLimitPower, sMcAfn04f27;

// 封帧侧
#pragma pack(1)

typedef struct
{
    sMcFmt08_f     fUpUp;        // 电压上上限(过压门限) (+)XXX.X
    UINT8         ucTime;        // 持续时间
    sMcFmt10_f   fFactor;        // 越限恢复系数         (+)XX.XX 
}sMcOverV_f;                     // 过压判别参数

typedef struct
{
    sMcFmt08_f fDownDown;        // 电压下下限(过压门限) (+)XXX.X
    UINT8         ucTime;        // 持续时间
    sMcFmt10_f   fFactor;        // 越限恢复系数         (+)XX.XX   
}sMcLossV_f;                     // 欠压判别参数 

typedef struct
{
    sMcFmt09_f     fUpUp;        // 电流上上限() (+/-)XXX.XXX
    UINT8         ucTime;        // 持续时间
    sMcFmt10_f   fFactor;        // 越限恢复系数         (+)XX.XX   
}sMcOverI_f;                     // 过流判别参数

typedef struct
{
    sMcFmt09_f       fUp;        // 电流上(额定电流上限) (+/-)XXX.XXX
    UINT8         ucTime;        // 持续时间
    sMcFmt10_f   fFactor;        // 越限恢复系数         (+)XX.XX   
}sMcSuperI_f;                    // 超额定电流判别参数

typedef struct
{
    sMcFmt09_f       fUp;        // 0序电流上限 (+/-)XXX.XXX
    UINT8         ucTime;        // 持续时间
    sMcFmt10_f   fFactor;        // 越限恢复系数         (+)XX.XX   
}sMcZeroI_f;                     // 零序电流超限判别参数

typedef struct
{
    sMcFmt06_f    fLimit;        // 三相电压不平衡度限值 (+/-)XX.XXXX
    UINT8         ucTime;        // 持续时间
    sMcFmt10_f   fFactor;        // 越限恢复系数         (+)XX.XX   
}sMcUnblnV_f;                    // 三相电压不平衡超限判别参数

typedef struct
{
    sMcFmt06_f    fLimit;        // 三相电流不平衡度限值 (+/-)XX.XXXX
    UINT8         ucTime;        // 持续时间
    sMcFmt10_f   fFactor;        // 越限恢复系数         (+)XX.XX   
}sMcUnblnI_f;                    // 三相电流不平衡超限判别参数

typedef struct
{
    sMcFmt08_f        fDropV;    // 电压断相判别参数  
    UINT8        ucTimeLossV;    // 电压失压时间判别参数 minutes
    sMcOverV_f        sOverV;    // 过压判别参数
    sMcLossV_f        sLossV;    // 欠压判别参数
    sMcOverI_f        sOverI;    // 过流判别参数
    sMcSuperI_f      sSuperI;    // 超额定电流判别参数
    sMcZeroI_f        sZeroI;    // 零序电流超限判别参数
    sMcUnblnV_f        sUblV;    // 三相电压不平衡超限判别参数
    sMcUnblnI_f        sUblI;    // 三相电流不平衡超限判别参数
}sMcElecLimitPower_f, sMcAfn04f27_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn04f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 电气测量点功率因素越限值参数
 * 对应AFN : MC_AFN_04_SETP
 * 对应CMD : MCMD_AFN_4_F28_ELEC_LMIT_FACTR
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef struct
{
    float  fPara1;            // 总功率因数分段参数 1   (+)XX.XX
    float  fPara2;            // 总功率因数分段参数 2   (+)XX.XX
    float  fWarning;          // 总功率因数越限告警定值 (+)XX.XX
}sMcFactorLimit, sMcAfn04F28; // 电气测量点功率因数越限值参数数据单元格式  

// 封帧侧
#pragma pack(1)
typedef struct
{
    sMcFmt10_f  fPara1;      // 总功率因数分段参数 1
    sMcFmt10_f  fPara2;      // 总功率因数分段参数 2
    sMcFmt10_f  fWarning;    // 总功率因数越限告警定值
}sMcFactorLimit_f, sMcAfn04F28_f; // 电气测量点功率因数越限值参数数据单元格式  
#pragma pack()

// 转换函数
eMcErr emc_trans_afn04f28(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 电气测量点谐波畸变率越限定值
 * 对应AFN : MC_AFN_04_SETP
 * 对应CMD : MCMD_AFN_4_F29_ELEC_FIX_HARM
 * PN 类型 : 电气测量点号
{*///
// aberration 畸变
typedef struct
{
   float fTotal;              // 总畸变率越限定值    (+)XX.XX
   float   fOdd;              // 奇次畸变率越限定值  (+)XX.XX
   float  fEven;              // 偶次畸变率超限定值  (+)XX.XX
}sMcAberLimit; 

// 用户侧
typedef struct
{
    sMcAberLimit      sVa;    // A相电压畸变率越限定值
    sMcAberLimit      sVb;    // B相电压畸变率越限定值
    sMcAberLimit      sVc;    // C相电压畸变率越限定值
    sMcAberLimit      sIa;    // A相电流畸变率越限定值
    sMcAberLimit      sIb;    // B相电流畸变率越限定值
    sMcAberLimit      sIc;    // C相电流畸变率越限定值
     
}sMcElecFixHarm, sMcAfn04F29; // 电气测量点功率因数越限值参数数据单元格式  

// 封帧侧
#pragma pack(1)
typedef struct
{
   sMcFmt10_f fTotal;             // 总畸变率越限定值
   sMcFmt10_f   fOdd;             // 奇次畸变率越限定值
   sMcFmt10_f  fEven;             // 偶次畸变率超限定值
}sMcAberLimit_f;

typedef struct
{
    sMcAberLimit_f      sVa;    // A相电压畸变率越限定值
    sMcAberLimit_f      sVb;    // B相电压畸变率越限定值
    sMcAberLimit_f      sVc;    // C相电压畸变率越限定值
    sMcAberLimit_f      sIa;    // A相电流畸变率越限定值
    sMcAberLimit_f      sIb;    // B相电流畸变率越限定值
    sMcAberLimit_f      sIc;    // C相电流畸变率越限定值
    
}sMcElecFixHarm_f, sMcAfn04F29_f; // 电气测量点功率因数越限值参数数据单元格式  
#pragma pack()

// 转换函数
eMcErr emc_trans_afn04f29(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 电气测量点闪变越限参数
 * 对应AFN : MC_AFN_04_SETP
 * 对应CMD : MCMD_AFN_4_F30_ELEC_FLASH
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef struct
{
    float    fLong;      // 短时闪变越限值  (+)XX.XX
    float   fShort;      // 长时闪变越限值  (+)XX.XX
}sMcElecFlash, sMcAfn04f30;

// 封帧侧
#pragma pack(1)
typedef struct
{
    sMcFmt10_f    fLong;      // 短时闪变越限值
    sMcFmt10_f   fShort;      // 长时闪变越限值
}sMcElecFlash_f, sMcAfn04f30_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn04f30(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 非电气测量点配置参数
 * 对应AFN : MC_AFN_04_SETP
 * 对应CMD : MCMD_AFN_4_F33_NELC_MP_CFG
 * PN 类型 : 电气测量点号
{*///
///*} 

// 用户侧
typedef sMcElecMpCfg sMcNelecMpCfg;
typedef sMcAfn04f25  sMcAfn04f33;

// 封帧侧
typedef sMcElecMpCfg_f sMcNElecMpCfg_f;
typedef sMcAfn04f25_f  sMcAfn04f33_f; 

// 转换函数
eMcErr emc_trans_afn04f33(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 非电气测量点数据参数
 * 对应AFN : MC_AFN_04_SETP
 * 对应CMD : MCMD_AFN_4_F34_NELC_MP_PARA
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef enum
{
   MC_NELC_UNKOWN,
   MC_NELC_TEMP,       // 温度
   MC_NELC_FLOW,       // 流量
   MC_NELC_FV,         // 流速
   MC_NELC_PRESS,      // 压力
   MC_NELC_HUMI,       // 湿度
   MC_NELC_LIGHT,      // 照度
   MC_NELC_RV,         // 转速
   MC_NELC_420MA,      // 4~20MA

}eMcNElcType;

typedef struct
{
    eMcNElcType eType;           // 非电气量类型
    sMcDouble     sUp;           // 量程上限
    sMcDouble   sDown;           // 量程下限
}sMcNelcMpPara, sMcAfn04f34;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8       eType;            // 非电气量类型
    sMcFmt11_f    sUp;            // 量程上限
    sMcFmt11_f  sDown;            // 量程下限
}sMcNelcMpCfg_f, sMcAfn04f34_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn04f34(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 非电气测量点越限数据参数
 * 对应AFN : MC_AFN_04_SETP
 * 对应CMD : MCMD_AFN_4_F35_NELC_MP_LMIT
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef struct
{
    eMcNElcType eType;           // 非电气量类型
    sMcDouble    sUp;             // 越上限定值
    sMcDouble    sDown;           // 越下限定值

}sMcNelcMpLimit, sMcAfn0435;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8       eType;            // 非电气量类型
    sMcFmt11_f    sUp;            // 越上限定值
    sMcFmt11_f  sDown;            // 越下限定值
}sMcNelcMpLimit_f, sMcAfn0435_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn04f35(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 冻结数据任务参数
 * 对应AFN : MC_AFN_04_SETP
 * 对应CMD : MCMD_AFN_4_F49_FREZ_TASK_PARA
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef enum
{
    MC_PUNT_UNKOWN,  // 未知的周期单位
    MC_PUNT_MONTH,   // 月
    MC_PUNT_DAY,     // 日
    MC_PUNT_HOUR,    // 时
    MC_PUNT_MIN,     // 分钟
    MC_PUNT_SEC,     // 秒
    MC_PUNT_MS,      // 毫秒
}eMcPeriodUnit;      // 冻结周期单位

typedef struct
{
    UINT16         usPeriod;         // 冻结周期 为定时冻结的时间间隔，为0表示删除本项冻结任务。
    eMcPeriodUnit     eUnit;         // 冻结周期单位
    UINT8           ucTimes;         // 冻结周期数：表示以冻结周期为间隔，需冻结的次数，为0表示无限次数。 
}sMcFrezPeriod;

typedef struct
{
    sMcYWMDhms      sTimeFrez;         // 冻结基准时间：秒分时日月年 
    sMcYWMDhms      sTimeRprt;         // 上报基准时间：秒分时日月年
    sMcFrezPeriod      sFreez;         // 冻结周期
    UINT8         ucPeriodRpt;         // 定时上报周期    ：为定时上报数据的时间间隔，0为本项冻结任务内容无需定时上报。
    eMcPeriodUnit    eUnitRpt;         // 定时上报周期单位：数值范围1~4，依次分别表示分、时、日、月，其他备用
    UINT8           uCmdPnNum;         // 需要冻结的数据单元标识 个数
    sMcmdPn         sCmdPn[1];         // 需要冻结的数据单元标识 内容
    
}sMcFrezTaskPara, sMcAfn04f49;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT16         usPeriod;         // 冻结周期 为定时冻结的时间间隔，为0表示删除本项冻结任务。
    UINT8             eUnit;         // 冻结周期单位
    UINT8           ucTimes;         // 冻结周期数：表示以冻结周期为间隔，需冻结的次数，为0表示无限次数。 
}sMcFrezPeriod_f;

typedef struct
{
    sMcFmt01_f        sTimeFrez;     // 冻结基准时间：秒分时日月年 
    sMcFrezPeriod_f      sFreez;     // 冻结周期 
    UINT8             ucDaDtNum;     // 数据单元标识个数

    // 以下为变长
    /*
    sMcDaDt        sDaDt[1];         // ucDaDtNum 个数据单元标识
    sMcFmt01_f        sTimeRprt;     // 冻结基准时间：秒分时日月年 
    UINT8             eUnit;         // 定时上报周期
    UINT8           ucTimes;         // 定时上报周期单位 
    */
}sMcFrezTaskPara_f, sMcAfn04f49_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn04f49(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 校时命令
 * 对应AFN : MC_AFN_04_SETP
 * 对应CMD : MCMD_AFN_5_F1_CHECK_TIME
 * PN 类型 : 电气测量点号
{*///

// 用户侧
// sMcYWMDhms
// 封帧侧
// sMcYWMDhms_f

// 转换函数
eMcErr emc_trans_afn05f1(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 临时冻结命令
 * 对应AFN : MC_AFN_05_CTRL
 * 对应CMD : MCMD_AFN_5_F2_FREZ_TEMP
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef struct
{
    UINT8         ucNum;    // 数据单元标识个数
    sMcmdPn   sCmdPn[1];    // ucNum 个数据单元标识
}sMcFrezTemp, sMcAfn05f2;

// 封帧侧
typedef struct
{
    UINT8         ucNum;     // 数据单元标识个数 DaDt
    sMcDaDt    sDaDt[1];  // ucNum 个DaDt
}sMcFrezTemp_f, sMcAfn05f2_f;

// 转换函数
eMcErr emc_trans_afn05f2(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 遥控跳闸
 * 对应AFN : MC_AFN_05_CTRL
 * 对应CMD : MCMD_AFN_5_F9_REMOTE_OFF
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef struct
{
    BOOL         bOff[8];    // 第1-8输出开关是否跳闸
    sMcYMDhm sTimeStart;    // 跳闸开始时间 
    sMcYMDhm   sTimeEnd;    // 跳闸结束时间 
}sMcRemoteOff, sMcAfn05f9;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8         bOff;      // 每一bit表示第1-8输出开关是否合上
    sMcYMDhm_f sTimeStart;  // 跳闸开始时间 
    sMcYMDhm_f   sTimeEnd;  // 跳闸结束时间   

}sMcRemoteOff_f, sMcAfn05f9_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn05f9(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 允许合闸
 * 对应AFN : MC_AFN_05_CTRL
 * 对应CMD : MCMD_AFN_5_F10_REMOTE_ON
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef struct
{
    BOOL         bOn[8];    // 第1-8输出开关是否跳闸
}sMcRemoteOn, sMcAfn05f10;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8         bOn;      // 每一bit表示第1-8输出开关是否合上
 
}sMcRemoteOn_f, sMcAfn05f10_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn05f10(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 能效模型有效
 * 对应AFN : MC_AFN_05_CTRL
 * 对应CMD : MCMD_AFN_5_F17_NX_MODEL_ACT
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef struct
{
    UINT8        ucID;       // 第N个能效模式编号
    sMcYWMDhms  sTime;       // 起始时间:年月日时分秒
}sMcNxModelOne;

typedef struct
{
    UINT8              ucN;  // 能效模型个数
    sMcNxModelOne  sOne[1];  // 第n个能效模型 一共N个能效模型

}sMcNxModelAct, sMcAfn05f17;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8         ucID;       // 第N个能效模式编号
    sMcYWMDhms_f  sTime;      // 起始时间:年月日时分秒
}sMcNxModelOne_f;

typedef struct
{
    UINT8              ucN;  // 能效模型个数
    sMcNxModelOne_f   sOne[1];  // 第n个能效模型 一共N个能效模型
}sMcNxModelAct_f, sMcAfn05f17_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn05f17(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 能效模型清除
 * 对应AFN : MC_AFN_05_CTRL
 * 对应CMD : MCMD_AFN_5_F18_NX_MODEL_CLR
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef struct
{
    UINT8            ucN;  // 能效模型个数
    UINT8        ucID[1];  // 第n个能效模型编号
}sMcNxModelClr, sMcAfn05f18;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8            ucN;  // 能效模型个数
    UINT8        ucID[1];  // 第n个能效模型编号
}sMcNxModelClr_f, sMcAfn05f18_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn05f18(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 需求响应信息有效
 * 对应AFN : MC_AFN_05_CTRL
 * 对应CMD : MCMD_AFN_5_F19_RQ_RESPN_ACT
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef struct
{
    UINT8            ucN;  // 需求响应信息个数n
    UINT8        ucID[1];  // 第n个需求响应信息编号
}sMcRqRespnAct, sMcAfn05f19;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8            ucN;  // 需求响应信息个数n
    UINT8        ucID[1];  // 第n个需求响应信息编号
}sMcRqRespnAct_f, sMcAfn05f19_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn05f19(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 需求响应信息清除
 * 对应AFN : MC_AFN_05_CTRL
 * 对应CMD : MCMD_AFN_5_F20_RQ_RESPN_CLT
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef struct
{
    UINT8            ucN;  // 需求响应信息个数n
    UINT8        ucID[1];  // 第n个需求响应信息编号
}sMcRqRespnClr, sMcAfn05f20;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8            ucN;  // 需求响应信息个数n
    UINT8        ucID[1];  // 第n个需求响应信息编号
}sMcRqRespnClr_f, sMcAfn05f20_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn05f20(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 查询主(子)站参数  (命令参数)
 * 对应AFN : MC_AFN_10_GETP
 * 对应CMD : MCMD_AFN_A_F2_MST_PARA
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef struct
{
    UINT8            ucN;  // 本次查询的主(子)站数n
    UINT8        ucID[1];  // 第n个主(子)编号
}sMcMstParaQ, sMcAfn11f2q;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8            ucN;  // 本次查询的主(子)站数n
    UINT8        ucID[1];  // 第n个主(子)编号
}sMcMstParaQ_f, sMcAfn11f2q_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn10f2_m2s(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 查询主(子)站参数  (数据应答)
 * 对应AFN : MC_AFN_10_GETP
 * 对应CMD : MCMD_AFN_A_F2_MST_PARA
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sMcMstPara sMcMstParaA, sMcAfn11f2a;

// 封帧侧
#pragma pack(1)
typedef sMcMstPara_f sMcMstParaA_f, sMcAfn11f2a_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn10f2_s2m(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 信息集中与交互终端下行以太网端口通信参数 (询问)
 * 对应AFN : MC_AFN_10_GETP
 * 对应CMD : MCMD_AFN_A_F7_CON_DOWN_CFG
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef struct
{
    UINT16            usN;     // 本次查询数n
    UINT16        usPort[1];  // 第n个端口号
}sMcDownCfgQ, sMcAfn10f7q;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT16            usN;     // 本次查询数n
    UINT16        usPort[1];  // 第n个端口号
}sMcDownCfgQ_f, sMcAfn10f7q_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn10f7_m2s(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 信息集中与交互终端下行以太网端口通信参数 (应答)
 * 对应AFN : MC_AFN_10_GETP
 * 对应CMD : MCMD_AFN_A_F7_CON_DOWN_CFG
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef struct
{
    UINT8            ucN;     // 本次查询数n
    sMcDownCfg      sOne[1];  // 第n组配置
}sMcDownCfgA, sMcAfn10f7a;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8            ucN;     // 本次查询数n
    sMcDownCfg_f  sOne[1];    // 第n组配置
}sMcDownCfgA_f, sMcAfn10f7a_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn10f7_s2m(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 设备逻辑地址(询问没有参数 应答本结构)
 * 对应AFN : MC_AFN_10_GETP
 * 对应CMD : MCMD_AFN_A_F11_CON_LOGIC_ADDR
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sMcA sMcLogicAddr, sMcAfn10f11;

// 封帧侧
#pragma pack(1)
typedef sMcA_f sMcLogicAddr_f, sMcAfn10f11_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn10f11(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 查询设备版本信息(询问没有参数 应答为本结构)
 * 对应AFN : MC_AFN_10_GETP
 * 对应CMD : MCMD_AFN_A_F12_CON_VERSION
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef struct
{
    UINT8             ucID;       // 模块编号
    UINT8    strVersion[4];       // 模块版本号
    sMcYMDhm         sTime;       // 模块软件发布日期: 分时日月年
}sMcVerModel;

typedef struct
{
    UINT8    strFactory[4];       // 厂商代号
    UINT8      ucDevId[12];       // 设备ID  12位数字
    UINT8       strCap[11];       // 配置容量信息码
    UINT8       strSoft[4];       // 软件版本
    UINT8       strHard[4];       // 硬件版本
    sMcYMDhm         sTime;       // 软件发布日期: 分时日月年
    UINT8              ucN;       // 模块数n
    sMcVerModel    sOne[1];       // 第n个模块的详细数据
    
}sMcVersion, sMcAfn10f12;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8             ucID;       // 模块编号
    UINT8    strVersion[4];       // 模块版本号
    sMcYMDhm_f       sTime;       // 模块软件发布日期: 分时日月年
}sMcVerModel_f;

typedef struct
{
    UINT8    strFactory[4];       // 厂商代号
    UINT8       ucDevId[6];       // 设备ID  12位数字  这里为BCD
    UINT8       strCap[11];       // 配置容量信息码
    UINT8       strSoft[4];       // 软件版本
    UINT8       strHard[4];       // 硬件版本
    sMcYMDhm_f       sTime;       // 软件发布日期: 分时日月年
    UINT8              ucN;       // 模块数n
    sMcVerModel_f  sOne[1];       // 第n个模块的详细数据
    
}sMcVersion_f, sMcAfn10f12_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn10f12(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 已配置电气测量点信息(询问没有参数 应答本结构)
 * 对应AFN : MC_AFN_10_GETP
 * 对应CMD : MCMD_AFN_A_F13_ELEC_MP_INFO
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef struct
{
    UINT8    ucSprt;          // 支持的测量点信息点组数据n (1 < n < 255)
    UINT16    usNum;          // 已经配置的Pn个数
    UINT16  usPn[1];          // 配置的具体pn
}sMcElecMpInfo, sMcAfn10f13;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8   ucSprt;           // 支持的测量点信息点组数据n (1 < n < 255)
    UINT8   ucSDa2;           // 本帧上报的起始信息点组DA2 (1 < m < 255)
    UINT8   ucK;              // 本帧上报的个数
    UINT8   ucDa1[1];         // 第i 个信息点组DA2所对应的DA1（i=m~m+k-1） 
}sMcElecMpInfo_f, sMcAfn10f13_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn10f13(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 已配置非电气测量点信息(询问没有参数 应答本结构)
 * 对应AFN : MC_AFN_10_GETP
 * 对应CMD : MCMD_AFN_A_F14_NELC_MP_INFO
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef struct
{
    UINT8    ucSprt;          // 支持的测量点信息点组数据n (1 < n < 255)
    UINT16    usNum;          // 已经配置的Pn个数
    UINT16  usPn[1];          // 配置的具体pn
}sMcNelcMpInfo, sMcAfn10f14;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8   ucSprt;           // 支持的测量点信息点组数据n (1 < n < 255)
    UINT8   ucSDa2;           // 本帧上报的起始信息点组DA2 (1 < m < 255)
    UINT8   ucK;              // 本帧上报的个数
    UINT8   ucDa1[1];         // 第i 个信息点组DA2所对应的DA1（i=m~m+k-1） 
}sMcNelcMpInfo_f, sMcAfn10f14_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn10f14(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 设备支持的事件记录(询问没有参数 应答本结构)
 * 对应AFN : MC_AFN_10_GETP
 * 对应CMD : MCMD_AFN_A_F15_SUPT_EVENT
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef struct
{
   BOOL  bSuprt[MC_ERC_NUM_MAX];    // 对各事件是否支持
   
}sMcSuptEvent, sMcAfn10f15;

// 封帧侧
#pragma pack(1)
typedef struct
{
   UINT8   ucEvent[8];              // D0~D63按顺序对应表示事件代码ERC1~ERC64所定义的事件
   
}sMcSuptEvent_f, sMcAfn10f15_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn10f15(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 查询已配置监测终端信息(询问没有参数 应答本结构)
 * 对应AFN : MC_AFN_10_GETP
 * 对应CMD : MCMD_AFN_A_F57_TML_CFG_INFO
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef struct
{
    UINT8    ucSprt;          // 支持的测量点信息点组数据n (1 < n < 255)
    UINT16    usNum;          // 已经配置的Pn个数
    UINT16  usPn[1];          // 配置的具体pn
}sMcTmlCfgInfo, sMcAfn10f57;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8   ucSprt;           // 支持的测量点信息点组数据n (1 < n < 255)
    UINT8   ucSDa2;           // 本帧上报的起始信息点组DA2 (1 < m < 255)
    UINT8   ucK;              // 本帧上报的个数
    UINT8   ucDa1[1];         // 第i 个信息点组DA2所对应的DA1（i=m~m+k-1） 
}sMcTmlCfgInfo_f, sMcAfn10f57_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn10f57(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 日历时钟(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F1_CLOCK
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sMcUerClock sMcClock, sMcAfn13f1;

// 封帧侧
#pragma pack(1)
typedef sMcUerClock_f sMcClock_f, sMcAfn13f1_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn13f1(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 参数状态标志(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F2_PARA_STATE
 * PN 类型 : p0/监测终端号
{*///

// 目前可以设置的参数个数为20(MCMD_AFN_4_F1_CON_UP_CFG  到 MCMD_AFN_4_F49_FREZ_TASK_PARA)
#define MC_SET_NUM_MAX  (20)     

// 用户侧
typedef struct
{
    UINT8    ucNum;  // 已经设置的个数
    eMcmd  eCmd[1];  // 已经设置的参数类型
}sMcParaState, sMcAfn13f2;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8  ucSet[31];
}sMcParaState_f, sMcAfn13f2_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn13f2(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 重要事件计数器当前值(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F3_EVENT_1
 * PN 类型 : p0/监测终端号
{*///

// 用户侧
// UINT16 usEc1

// 封帧侧
// UINT16 usEc1_f

// 转换函数
eMcErr emc_trans_afn13f3(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 一般事件计数器当前值(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F4_EVENT_2
 * PN 类型 : p0/监测终端号
{*///

// 用户侧
// UINT16 usEc2

// 封帧侧
// UINT16 ucEc2_f

// 转换函数
eMcErr emc_trans_afn13f4(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 事件状态标志(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F5_EVENT_STATE
 * PN 类型 : p0/监测终端号
{*///

// 用户侧
typedef struct
{
    BOOL bHave[MC_ERC_NUM_MAX];      // 真:有事件 假: 无事件 
}sMcEventState, sMcAfn13f5;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8   ucHave[8];               // 每个bit代表是否有对应的事件发生
}sMcEventState_f, sMcAfn13f5_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn13f5(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 上电次数(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F6_POWR_TIMES
 * PN 类型 : p0/监测终端号
{*///

#define MC_POWR_TIMES_MAX (999999)
// 用户侧
typedef struct
{
    UINT32 ulTimes;    //  (0-999999)
}sMcPowerTimes, sMcAfn13f6;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8   ucBcd[3];       // BCD格式
}sMcPowerTimes_f, sMcAfn13f6_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn13f6(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 状态量及变位标志(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F9_STATE
 * PN 类型 : p0/监测终端号
{*///

// 用户侧
typedef struct
{
    BOOL bSt[8];   // 表示1-8路状态量的状态ST 真:合, 假:分          
    BOOL bCd[8];   // 表示1-8路状态量的变化CD 
                   // 真:自前次遥信传送后至少有一次状态变化
                   // 假:自前次遥信传送后没有状态变化
}sMcState, sMcAfn13f9;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8  ucSt8;
    UINT8  ucCd8;
}sMcState_f, sMcAfn13f9_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn13f9(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 控制输出回路开关接入状态量及变位标志(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F10_SWITCH
 * PN 类型 : p0/监测终端号
{*///

// 用户侧
typedef struct
{
    BOOL bSt[4];   // 表示1-4路控制输出常开、常闭触点接入开关跳闸回路状态量的状态ST     
                   // 真:接入 假:未接入
    BOOL bCd[4];   // 表示1-4路控制输出常开、常闭触点接入开关跳闸回路状态量的变化CD 
                   // 真:自前次遥信传送后至少有一次状态变化
                   // 假:自前次遥信传送后没有状态变化
}sMcSwitch, sMcAfn13f10;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8  ucSt8;
    UINT8  ucCd8;
}sMcSwitch_f, sMcAfn13f10_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn13f10(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 总有功功率(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F25_POWR_HAVE_T
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef struct
{
    float fXX_XXXX;              //  总有功功率(Kw) (+)XX.XXXX
}sMcPowerHaveT, sMcAfn13f25;

// 封帧侧
#pragma pack(1)
typedef struct
{
    sMcFmt06_f fXX_XXXX;       
}sMcPowerHaveT_f, sMcAfn13f25_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn13f25(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 总无功功率(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F26_POWR_NONE_T
 * PN 类型 : p0/监测终端号
{*///

// 用户侧
typedef struct
{
    float fXX_XXXX;             //  总无功功率(Kw) (+)XX.XXXX
}sMcPowerNoneT, sMcAfn13f26;

// 封帧侧
#pragma pack(1)
typedef struct
{
    sMcFmt06_f fXX_XXXX;       
}sMcPowerNoneT_f, sMcAfn13f26_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn13f26(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 总功率因数(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F27_FACTR_T
 * PN 类型 : p0/监测终端号
{*///

// 用户侧
typedef struct
{
    float fXX_XX;             //  总功率因数 (+)XX.XX
}sMcFactorT, sMcAfn13f27;

// 封帧侧
#pragma pack(1)
typedef struct
{
    sMcFmt10_f fXX_XX;       
}sMcFactorT_f, sMcAfn13f27_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: A相功率因素(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F28_FACTR_A
 * PN 类型 : p0/监测终端号
{*///

// 用户侧
typedef struct
{
    float fXX_XX;             //  A相功率因素 (+)XX.XX
}sMcFactorA, sMcAfn13f28;

// 封帧侧
#pragma pack(1)
typedef struct
{
    sMcFmt10_f fXX_XX;       
}sMcFactorA_f, sMcAfn13f28_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn13f28(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: B相功率因素(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F29_FACTR_B
 * PN 类型 : p0/监测终端号
{*///

// 用户侧
typedef struct
{
    float fXX_XX;             //  B相功率因素 (+)XX.XX
}sMcFactorB, sMcAfn13f29;

// 封帧侧
#pragma pack(1)
typedef struct
{
    sMcFmt10_f fXX_XX;       
}sMcFactorB_f, sMcAfn13f29_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn13f29(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: C相功率因素(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F30_FACTR_C
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef struct
{
    float fXX_XX;             //  C相功率因素 (+)XX.XX
}sMcFactorC, sMcAfn13f30;

// 封帧侧
#pragma pack(1)
typedef struct
{
    sMcFmt10_f fXX_XX;       
}sMcFactorC_f, sMcAfn13f30_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn13f30(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 需量(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F33_DEMAND
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef struct
{
    float fXX_XXXX;             //  需量 (+/-)XX.XXXX
}sMcDemand, sMcAfn13f33;

// 封帧侧
#pragma pack(1)
typedef struct
{
    sMcFmt06_f fXX_XXXX;       
}sMcDemand_f, sMcAfn13f33_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn13f33(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 日最大需量(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F34_DEMAND_MAX
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef struct
{
    float fXX_XXXX;             //  日最大需量 (+/-)XX.XXXX
}sMcDemandMax, sMcAfn13f34;

// 封帧侧
#pragma pack(1)
typedef struct
{
    sMcFmt06_f fXX_XXXX;       
}sMcDemandMax_f, sMcAfn13f34_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn13f34(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 日最大需量发生时间(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F35_DEMAND_TIME
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef struct
{
    sMcYMDhm sTime;             //  日最大需量发生时间 年月日时分
}sMcDemandTime, sMcAfn13f35;

// 封帧侧
#pragma pack(1)
typedef struct
{
    sMcFmt02_f sTime;       
}sMcDemandTime_f, sMcAfn13f35_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn13f35(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: A相有功功率(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F41_POWR_HAVE_A
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef struct
{
    float fXX_XX;             //  A相有功功率 (+)XX.XX
}sMcPowerHaveA, sMcAfn13f41;

// 封帧侧
#pragma pack(1)
typedef struct
{
    sMcFmt10_f fXX_XX;       
}sMcPowerHaveA_f, sMcAfn13f41_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn13f41(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: B相有功功率(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F42_POWR_HAVE_B
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sMcPowerHaveA sMcPowerHaveB;

// 封帧侧
// typdef sMcPowerHaveA_f sMcPowerHaveB_f;

// 转换函数
eMcErr emc_trans_afn13f42(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: C相有功功率(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F43_POWR_HAVE_C
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sMcPowerHaveA sMcPowerHaveC;

// 封帧侧
// typdef sMcPowerHaveA_f sMcPowerHaveC_f;

// 转换函数
eMcErr emc_trans_afn13f43(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: A相无功功率(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F44_POWR_NONE_A
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sMcPowerHaveA sMcPowerNoneA;

// 封帧侧
// typdef sMcPowerHaveA_f sMcPowerNoneA_f;

// 转换函数
eMcErr emc_trans_afn13f44(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: B相无功功率(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F45_POWR_NONE_B
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sMcPowerHaveA sMcPowerNoneB;

// 封帧侧
// typdef sMcPowerHaveA_f sMcPowerNoneB_f;

// 转换函数
eMcErr emc_trans_afn13f45(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: C相无功功率(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F46_POWR_NONE_C
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sMcPowerHaveA sMcPowerNoneC;

// 封帧侧
// typdef sMcPowerHaveA_f sMcPowerNoneC_f;

// 转换函数
eMcErr emc_trans_afn13f46(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: （正向）有功总电能示数(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F49_POWR_HAVE_FRTH
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef struct
{
    double dXXXXXX_XXXX;           // 电能示数    (+)XXXXXX.XXXX    
}sMcPowerHaveFrth, sMcAfn13f49;

// 封帧侧
#pragma pack(1)
typedef struct
{
    sMcFmt04_f dXXXXXX_XXXX;
}sMcPowerHaveFrth_f, sMcAfn13f49_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn13f49(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: （反向）有功总电能示数(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F50_POWR_HAVE_BACK
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sMcPowerHaveFrth sMcPowerHaveBack;

// 封帧侧
// typdef sMcPowerHaveFrth_f sMcPowerHaveBack_f;

// 转换函数
eMcErr emc_trans_afn13f50(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: （正向）无功总电能示数(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F51_POWR_NONE_FRTH
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef struct
{
    double dXXXXXX_XX;           // 电能示数    (+)XXXXXX.XX    
}sMcPowerNoneFrth, sMcAfn13f51;

// 封帧侧
#pragma pack(1)
typedef struct
{
    sMcFmt05_f dXXXXXX_XX;
}sMcPowerNoneFrth_f, sMcAfn13f51_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn13f51(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: （反向）有功总电能示数(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F52_POWR_NONE_BACK
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sMcPowerNoneFrth sMcPowerNoneBack;

// 封帧侧
// typdef sMcPowerNoneFrth_f sMcPowerNoneBack_f;

// 转换函数
eMcErr emc_trans_afn13f52(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: A相电压(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F57_VOLT_A
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef struct
{
    float fXXX_X;           // 电压示数 (V)   (+)XXX.X    
}sMcVoltA, sMcAfn13f57;

// 封帧侧
#pragma pack(1)
typedef struct
{
    sMcFmt08_f fXXX_X;
}sMcVoltA_f, sMcAfn13f57_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn13f57(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称:  B相电压(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F58_VOLT_B
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sMcVoltA sMcVoltB;

// 封帧侧
//typedef sMcVoltA_f sMcVoltB_f;

// 转换函数
eMcErr emc_trans_afn13f58(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: C相电压(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F59_VOLT_C
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sMcVoltA sMcVoltC;

// 封帧侧
//typedef sMcVoltA_f sMcVoltC_f;

// 转换函数
eMcErr emc_trans_afn13f59(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: A相电压相位角(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F60_VANGL_A
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef struct
{
    float fsXXX_X;           // 电压示数 (度)   (+/-)XXX.X    
}sMcVAngleA, sMcAfn13f60;

// 封帧侧
#pragma pack(1)
typedef struct
{
    sMcFmt07_f fsXXX_X;
}sMcVAngleA_f, sMcAfn13f60_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn13f60(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称:  B相电压相位角(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F61_VANGL_B
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sMcVAngleA sMcVAngleB;

// 封帧侧
// typedef sMcVAngleA_f sMcVAngleB_f;

// 转换函数
eMcErr emc_trans_afn13f61(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: C相电压相位角(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F62_VANGL_C
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sMcVAngleA sMcVAngleC;

// 封帧侧
// typedef sMcVAngleA_f sMcVAngleC_f;

// 转换函数
eMcErr emc_trans_afn13f62(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 电压不平衡度(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F63_VOLT_UBL
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sMcFactorT sMcVoltUbl;

// 封帧侧
// typedef sMcFactorT_f sMcVoltUbl_f;

// 转换函数
eMcErr emc_trans_afn13f63(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 周波(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F64_CIRCLE_V
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sMcAfn13f25 sMcVCircle;

// 封帧侧

// 转换函数
eMcErr emc_trans_afn13f64(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: A相电流(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F65_ELEC_A
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef struct
{
    float fsXXX_XXX;        //  (A) (+/-)XXX.XXX  
}sMcElecA, sMcAfn13f65;

// 封帧侧
#pragma pack(1)
typedef struct
{
    sMcFmt09_f fsXXX_XXX;
}sMcElecA_f, sMcAfn13f65_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn13f65(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: B相电流(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F66_ELEC_B
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sMcElecA sMcElecB;

// 封帧侧
// 转换函数
eMcErr emc_trans_afn13f66(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: C相电流(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F67_ELEC_C
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sMcElecA sMcElecC;

// 封帧侧
// 转换函数
eMcErr emc_trans_afn13f67(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 中性线电流(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F68_ELEC_M
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sMcElecA sMcElecM;

// 封帧侧
// 转换函数
eMcErr emc_trans_afn13f68(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: A相电流相位角(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F69_EANGL_A
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sMcAfn13f60 sMcEAngleA;

// 封帧侧
// 转换函数
eMcErr emc_trans_afn13f69(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: B相电流相位角(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F70_EANGL_B
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sMcAfn13f60 sMcEAngleB;

// 封帧侧
// 转换函数
eMcErr emc_trans_afn13f70(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: C相电流相位角(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F71_EANGL_C
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sMcAfn13f60 sMcEAngleC;

// 封帧侧
// 转换函数
eMcErr emc_trans_afn13f71(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 电流不平衡度(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F72_ELEC_UBL
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sMcAfn13f60 sMcElecUbl;

// 封帧侧
// 转换函数
eMcErr emc_trans_afn13f72(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 日A相电压极大值(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F73_VDMAX_A
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sMcVoltA sMcVMaxA;

// 封帧侧
// 转换函数
eMcErr emc_trans_afn13f73(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 日A相电压极大值发生时间(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F74_VDMAX_A_TIME
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sMcAfn13f35 sMcVMaxATime;

// 封帧侧
// 转换函数
eMcErr emc_trans_afn13f74(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 日B相电压极大值(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F75_VDMAX_B
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sMcVoltA sMcVMaxB;

// 封帧侧
// 转换函数
eMcErr emc_trans_afn13f75(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 日B相电压极大值发生时间(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F76_VDMAX_B_TIME
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sMcAfn13f35 sMcVMaxBTime;

// 封帧侧
// 转换函数
eMcErr emc_trans_afn13f76(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 日C相电压极大值(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F77_VDMAX_C
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sMcVoltA sMcVMaxC;

// 封帧侧
// 转换函数
eMcErr emc_trans_afn13f77(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 日C相电压极大值发生时间(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F78_VDMAX_C_TIME
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sMcAfn13f35 sMcVMaxCTime;

// 封帧侧
// 转换函数
eMcErr emc_trans_afn13f78(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 日A相电流极大值(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F81_IDMAX_A
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sMcElecA sMcIMaxA;

// 封帧侧
// 转换函数
eMcErr emc_trans_afn13f81(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 日A相电流极大值发生时间(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F82_IDMAX_A_TIME
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sMcAfn13f35 sMcIMaxATime;

// 封帧侧
// 转换函数
eMcErr emc_trans_afn13f82(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 日B相电流极大值(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F83_IDMAX_B
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sMcElecA sMcIMaxB;

// 封帧侧
// 转换函数
eMcErr emc_trans_afn13f83(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 日B相电流极大值发生时间(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F84_IDMAX_B_TIME
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sMcAfn13f35 sMcIMaxBTime;

// 封帧侧
// 转换函数
eMcErr emc_trans_afn13f84(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 日C相电流极大值(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F85_IDMAX_C
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sMcElecA sMcIMaxC;

// 封帧侧
// 转换函数
eMcErr emc_trans_afn13f85(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 日C相电流极大值发生时间(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F86_IDMAX_C_TIME
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sMcAfn13f35 sMcIMaxCTime;

// 封帧侧
// 转换函数
eMcErr emc_trans_afn13f86(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 总基波有功功率(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F89_TFW_HAVE
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sMcAfn13f25 sMcTfwHave;   // (Total Fundamental Wave)

// 封帧侧
// 转换函数
eMcErr emc_trans_afn13f89(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 总基波无功功率(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F90_TFW_NONE
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sMcAfn13f25 sMcTfwNone;   // (Total Fundamental Wave)

// 封帧侧
// 转换函数
eMcErr emc_trans_afn13f90(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 总谐波有功功率(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F91_THW_HAVE
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sMcAfn13f25 sMcThwHave;   // (Total Harmonic Wave)

// 封帧侧
// 转换函数
eMcErr emc_trans_afn13f91(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 总基波无功功率(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F92_THW_NONE
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sMcAfn13f25 sMcThwNone;   // (Total Harmonic Wave)

// 封帧侧
// 转换函数
eMcErr emc_trans_afn13f92(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: A相电压越上上限日累计时间(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F97_VDPP_TIME_A
 * PN 类型 : 电气测量点号
{*///
#define MC_BCD_XXXX_MAX  (9999)

// 用户侧
typedef struct
{
    UINT16    usMinutes;       // 时间 分钟 最大值 MC_BCD_XXXX_MAX
    
}sMcVDppTimeA, sMcAfn13f97;  

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8 ucBCD[2];
    
}sMcVDppTimeA_f, sMcAfn13f97_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn13f97(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: B相电压越上上限日累计时间(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F98_VDPP_TIME_B
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sMcVDppTimeA sMcVDppTimeB;
// 转换函数
// 同 eMcErr emc_trans_afn13f97(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: C相电压越上上限日累计时间(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F99_VDPP_TIME_C
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sMcVDppTimeA sMcVDppTimeC;
// 转换函数
// 同 eMcErr emc_trans_afn13f97(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 


/*******************************************
 * 数据名称: A相电压越下下限日累计时间(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F100_VDNN_TIME_A
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sMcVDppTimeA sMcVDnnTimeA;
// 转换函数
// 同 eMcErr emc_trans_afn13f97(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: B相电压越下下限日累计时间(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F101_VDNN_TIME_B
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sMcVDppTimeA sMcVDnnTimeB;
// 转换函数
// 同 eMcErr emc_trans_afn13f97(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: C相电压越下下限日累计时间(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F102_VDNN_TIME_C
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sMcVDppTimeA sMcVDnnTimeC;
// 转换函数
// eMcErr emc_trans_afn13f97(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: A相电压越上上限月累计时间(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F105_VMPP_TIME_A
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sMcPowerTimes sMcVMppTimeA;
// 转换函数
// 同 eMcErr emc_trans_afn13f6(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: B相电压越上上限月累计时间(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F106_VMPP_TIME_B
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sMcPowerTimes sMcVMppTimeB;
// 转换函数
// 同 eMcErr emc_trans_afn13f6(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: C相电压越上上限月累计时间(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F107_VMPP_TIME_C
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sMcPowerTimes sMcVMppTimeC;
// 转换函数
// 同 eMcErr emc_trans_afn13f6(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: A相电压越下下限月累计时间(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F108_VMNN_TIME_A
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sMcPowerTimes sMcVMnnTimeA;
// 转换函数
// 同 eMcErr emc_trans_afn13f6(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: B相电压越下下限月累计时间(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F109_VMNN_TIME_B
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sMcPowerTimes sMcVMnnTimeB;
// 转换函数
// 同 eMcErr emc_trans_afn13f6(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: C相电压越下下限月累计时间(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F110_VMNN_TIME_C
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sMcPowerTimes sMcVMnnTimeC;
// 转换函数
// 同 eMcErr emc_trans_afn13f6(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: A相电压总畸变率(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F113_VABR_TOTL_A
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sMcAfn13f27 sMcVabrTotalA;
// 转换函数
// 同 eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: B相电压总畸变率(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F114_VABR_TOTL_B
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sMcAfn13f27 sMcVabrTotalB;
// 转换函数
// 同 eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: C相电压总畸变率(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F115_VABR_TOTL_C
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sMcAfn13f27 sMcVabrTotalC;
// 转换函数
// 同 eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: A相电流总畸变率(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F116_EABR_TOTL_A
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sMcAfn13f27 sMcEabrTotalA;
// 转换函数
// 同 eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: B相电流总畸变率(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F117_EABR_TOTL_B
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sMcAfn13f27 sMcEabrTotalB;
// 转换函数
// 同 eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: C相电流总畸变率(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F118_EABR_TOTL_C
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sMcAfn13f27 sMcEabrTotalC;
// 转换函数
// 同 eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: A相电压奇次畸变率(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F121_VABR_ODD_A
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sMcAfn13f27 sMcVabrOddA;
// 转换函数
// 同 eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: A相电压偶次畸变率(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F122_VABR_EVN_A
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sMcAfn13f27 sMcVabrEvnA;
// 转换函数
// 同 eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: B相电压奇次畸变率(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F123_VABR_ODD_B
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sMcAfn13f27 sMcVabrOddB;
// 转换函数
// 同 eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: B相电压偶次畸变率(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F124_VABR_EVN_B
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sMcAfn13f27 sMcVabrEvnB;
// 转换函数
// 同 eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: CS相电压奇次畸变率(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F125_VABR_ODD_C
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sMcAfn13f27 sMcVabrOddC;
// 转换函数
// 同 eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: C相电压偶次畸变率(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F126_VABR_EVN_C
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sMcAfn13f27 sMcVabrEvnC;
// 转换函数
// 同 eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: A相电压奇次畸变率(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F128_EABR_OOD_A
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sMcAfn13f27 sMcEabrOddA;
// 转换函数
// 同 eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: A相电流偶次畸变率(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F129_EABR_EVN_A
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sMcAfn13f27 sMcEabrEvnA;
// 转换函数
// 同 eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: B相电流奇次畸变率(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F130_EABR_OOD_B
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sMcAfn13f27 sMcEabrOddB;
// 转换函数
// 同 eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: B相电流偶次畸变率(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F131_EABR_EVN_B
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sMcAfn13f27 sMcEabrEvnB;
// 转换函数
// 同 eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: C相电流奇次畸变率(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F132_EABR_OOD_C
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sMcAfn13f27 sMcEabrOddC;
// 转换函数
// 同 eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: C相电流偶次畸变率(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F133_EABR_EVN_C
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sMcAfn13f27 sMcEabrEvnC;
// 转换函数
// 同 eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: A相短时闪变(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F137_FLS_SHRT_A
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sMcAfn13f27 sMcFlashShortA;
// 转换函数
// 同 eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: B相短时闪变(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F138_FLS_SHRT_B
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sMcAfn13f27 sMcFlashShortB;
// 转换函数
// 同 eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: C相短时闪变(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F139_FLS_SHRT_C
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sMcAfn13f27 sMcFlashShortC;
// 转换函数
// 同 eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: A相长时闪变(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F140_FLS_LONG_A
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sMcAfn13f27 sMcFlashLongA;
// 转换函数
// 同 eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: B相长时闪变(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F141_FLS_LONG_B
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sMcAfn13f27 sMcFlashLongB;
// 转换函数
// 同 eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: C相长时闪变(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F142_FLS_LONG_C
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sMcAfn13f27 sMcFlashLongC;
// 转换函数
// 同 eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: A相N次谐波电压(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F145_HARM_VOLT_A
 * PN 类型 : 电气测量点号
{*///

#define MC_HARM_TIMES_MAX      (19) // 谐波次数最大值

// 用户侧
typedef struct
{
    UINT8        ucN;          // 谐波次数
    float    fXXX_X[1];        // 2 ~ n次谐波  (数组元素个数为 ucN - 1)
}sMcHarmVoltA, sMcAfn13f145;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8             ucN;      // 谐波次数
    sMcFmt08_f  fXXX_X[1];      // 2 ~ n次谐波  (数组元素个数为 ucN - 1)
}sMcHarmVoltA_f, sMcAfn13f145_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn13f145(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: B相N次谐波电压(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F146_HARM_VOLT_B
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sMcHarmVoltA sMcHarmVoltB;
// 转换函数
// 同 eMcErr emc_trans_afn13f145(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: C相N次谐波电压(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F147_HARM_VOLT_C
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sMcHarmVoltA sMcHarmVoltC;
// 转换函数
// 同 eMcErr emc_trans_afn13f145(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: A相N次谐波电流(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F148_HARM_ELEC_A
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef struct
{
    UINT8             ucN;          // 谐波次数
    float    fsXXX_XXX[1];          // 2 ~ n次谐波  (数组元素个数为 ucN - 1)
}sMcHarmElecA, sMcAfn13f148;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8                ucN;      // 谐波次数
    sMcFmt09_f  fsXXX_XXX[1];      // 2 ~ n次谐波  (数组元素个数为 ucN - 1)
}sMcHarmElecA_f, sMcAfn13f148_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn13f148(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: B相N次谐波电流(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F149_HARM_ELEC_B
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sMcHarmElecA sMcHarmElecB;

// 转换函数
// 同 eMcErr emc_trans_afn13f148(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: C相N次谐波电流(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F150_HARM_ELEC_C
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sMcHarmElecA sMcHarmElecC;

// 转换函数
// 同 eMcErr emc_trans_afn13f148(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: A相N次谐波电压含有率(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F153_HARM_VINC_A
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef struct
{
    UINT8             ucN;          // 谐波次数
    float       fXX_XX[1];          // 2 ~ n次谐波含有率  (数组元素个数为 ucN - 1)
}sMcHarmVincA, sMcAfn13f153;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8              ucN;      // 谐波次数
    sMcFmt10_f   fXX_XX[1];      // 2 ~ n次谐波含有率  (数组元素个数为 ucN - 1)
}sMcHarmVincA_f, sMcAfn13f153_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn13f153(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: B相N次谐波电压含有率(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F154_HARM_VINC_B
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sMcHarmVincA sMcHarmVincB;

// 转换函数
// 同 eMcErr emc_trans_afn13f153(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: C相N次谐波电压含有率(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F155_HARM_VINC_C
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sMcHarmVincA sMcHarmVincC;

// 转换函数
// 同 eMcErr emc_trans_afn13f153(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: A相N次谐波电流含有率(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F156_HARM_EINC_A
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sMcHarmVincA sMcHarmEincA;

// 转换函数
// 同 eMcErr emc_trans_afn13f153(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: B相N次谐波电流含有率(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F157_HARM_EINC_B
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sMcHarmVincA sMcHarmEincB;

// 转换函数
// 同 eMcErr emc_trans_afn13f153(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: C相N次谐波电流含有率(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F158_HARM_EINC_C
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sMcHarmVincA sMcHarmEincC;

// 转换函数
// 同 eMcErr emc_trans_afn13f153(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 非电气量(应答格式)
 * 对应AFN : MC_AFN_13_ASKR
 * 对应CMD : MCMD_AFN_D_F233_NELC_VALUE
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef struct
{
    eMcNElcType   eType;           // 非电气量类型
    sMcDouble   sDouble;           // 非电气量类型 数值
}sMcNelcValue, sMcAfn13f233;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8         eType;       // 非电气量类型
    sMcFmt11_f   sDouble;      // 非电气量类型  数值
}sMcNelcValue_f, sMcAfn13f233_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn13f233(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 


/*******************************************
 * 数据名称: 请求（定时上报）冻结数据任务(命令参数)
 * 对应AFN : MC_AFN_12_ASKT
 * 对应CMD : MCMD_AFN_C_F9_FREZ_AUTO
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef struct
{
    sMcYMDhm   sTs;    // 请求冻结数据任务中的数据的起始时间ts：分时日月年
    sMcYMDhm   sTe;    // 请求冻结数据任务中的数据的结束时间te：分时日月年

}sMcFrezAutoQ, sMcAfn12f9;

// 封帧侧
#pragma pack(1)
typedef struct
{
    sMcFmt02_f           sTs;         // 请求冻结数据任务中的数据的起始时间ts：分时日月年
    sMcFmt02_f           sTe;         // 请求冻结数据任务中的数据的结束时间te：分时日月年
}sMcFrezAutoQ_f, sMcAfn12f9_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn12f9_m2s(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 请求（定时上报）冻结数据任务(应答格式)
 * 对应AFN : MC_AFN_12_ASKT
 * 对应CMD : MCMD_AFN_C_F9_FREZ_AUTO
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef union
{
     // MCMD_AFN_D_F1_CLOCK
    sMcUerClock           sUerClock;
    
    // MCMD_AFN_D_F2_PARA_STATE
    // 参数状态标志
    sMcParaState          sParaState;       

    // MCMD_AFN_D_F3_EVENT_1
    // 重要事件计数器当前值
    UINT16                usEc1;            

    // MCMD_AFN_D_F4_EVENT_2
    // 一般事件计数器当前值
    UINT16                usEc2;           

    // MCMD_AFN_D_F5_EVENT_STATE
    // 事件状态标志
    sMcEventState         sEventState;      

    // MCMD_AFN_D_F6_POWR_TIMES
    sMcPowerTimes         sPowerTimes;

    // MCMD_AFN_D_F9_STATE 
    // 状态量及变位标志
    sMcState              sState;           
    
    // MCMD_AFN_D_F10_SWITCH 
    // 控制输出回路开关接入状态量及变位标志
    sMcSwitch             sSwitch;           
  
    // MCMD_AFN_D_F25_POWR_HAVE_T  总有功功率
    sMcPowerHaveT         sPowerHaveT;
    
    // MCMD_AFN_D_F26_POWR_NONE_T         
    // 总无功功率
    sMcPowerNoneT         sPowerNoneT;      
    
    // 总功率因数
    // MCMD_AFN_D_F27_FACTR_T               
    sMcFactorT            sFactorT;
    
    // MCMD_AFN_D_F28_FACTR_A               
    // A相功率因素
    sMcFactorA            sFactorA;
    
    // MCMD_AFN_D_F29_FACTR_B               
    // B相功率因数
    sMcFactorB            sFactorB;
    
    // MCMD_AFN_D_F30_FACTR_C               
    // C相功率因数
    sMcFactorC            sFactorC;
    
    // MCMD_AFN_D_F33_DEMAND                
    // 需量
    sMcDemand             sDemand;
    
    // MCMD_AFN_D_F34_DEMAND_MAX             
    // 日最大需量
    sMcDemandMax          sDemandMax;

    // MCMD_AFN_D_F35_DEMAND_TIME           
    // 日最大需量发生时间
    sMcDemandTime         sDemandTime;

    // MCMD_AFN_D_F41_POWR_HAVE_A            
    // A相有功功率
    sMcPowerHaveA         sPowerHaveA;

    // MCMD_AFN_D_F42_POWR_HAVE_B            
    // B相有功功率
    sMcPowerHaveB sPowerHaveB;

    // MCMD_AFN_D_F43_POWR_HAVE_C           
    // C相有功功率
    sMcPowerHaveC sPowerHaveC;

    // MCMD_AFN_D_F44_POWR_NONE_A           
    // A相无功功率
    sMcPowerNoneA sPowerNoneA;

    // MCMD_AFN_D_F45_POWR_NONE_B           
    // B相无功功率
    sMcPowerNoneB sPowerNoneB;

    // MCMD_AFN_D_F46_POWR_NONE_C            
    // C相无功功率
    sMcPowerNoneC sPowerNoneC;

    // MCMD_AFN_D_F49_POWR_HAVE_FRTH         
    // （正向）有功总电能示数
    sMcPowerHaveFrth sPowerHaveFrth;

    // MCMD_AFN_D_F50_POWR_HAVE_BACK         
    // （反向）有功总电能示数
    sMcPowerHaveBack sPowerHaveBack;

    // MCMD_AFN_D_F51_POWR_NONE_FRTH         
    // （正向）无功总电能示数
    sMcPowerNoneFrth sPowerNoneFrth;

    // MCMD_AFN_D_F52_POWR_NONE_BACK         
    // （反向）无功总电能示数
    sMcPowerNoneBack sPowerNoneBack;

    // MCMD_AFN_D_F57_VOLT_A                 
    // A相电压
    sMcVoltA sVoltA;

    // MCMD_AFN_D_F58_VOLT_B                
    // B相电压
    sMcVoltB sVoltB;

    // MCMD_AFN_D_F59_VOLT_C                
    // C相电压
    sMcVoltC sVoltC;

    // MCMD_AFN_D_F60_VANGL_A                
    // A相电压相位角
    sMcVAngleA sVAngleA;

    // MCMD_AFN_D_F61_VANGL_B                
    // B相电压相位角
    sMcVAngleB sVAngleB;

    // MCMD_AFN_D_F62_VANGL_C                
    // C相电压相位角
    sMcVAngleC sVAngleC;

    // MCMD_AFN_D_F63_VOLT_UBL               
    // 电压不平衡度
    sMcVoltUbl sVoltUbl;

    // MCMD_AFN_D_F64_CIRCLE_V               
    // 周波
    sMcVCircle sVCircle;

    // MCMD_AFN_D_F65_ELEC_A                 
    // A相电流
    sMcElecA sElecA;

    // MCMD_AFN_D_F66_ELEC_B                 
    // B相电流
    sMcElecB sElecB;

    // MCMD_AFN_D_F67_ELEC_C                  
    // C相电流
    sMcElecC sElecC;

    // MCMD_AFN_D_F68_ELEC_M                  
    // 中性线电流
    sMcElecM sElecM;

    // MCMD_AFN_D_F69_EANGL_A                 
    // A相电流相位角
    sMcEAngleA sEAngleA;

    // MCMD_AFN_D_F70_EANGL_B                 
    // B相电流相位角
    sMcEAngleB sEAngleB;

    // MCMD_AFN_D_F71_EANGL_C                 
    // C相电流相位角
    sMcEAngleC sEAngleC;

    // MCMD_AFN_D_F72_ELEC_UBL               
    // 电流不平衡度
    sMcElecUbl sElecUbl;

    // MCMD_AFN_D_F73_VDMAX_A                
    // 日A相电压极大值
    sMcVMaxA sVMaxA;

    // MCMD_AFN_D_F74_VDMAX_A_TIME            
    // 日A相电压极大值发生时间
    sMcVMaxATime sVMaxATime;

    // MCMD_AFN_D_F75_VDMAX_B                 
    // 日A相电压极大值
    sMcVMaxB sVMaxB;

    // MCMD_AFN_D_F76_VDMAX_B_TIME           
    // 日A相电压极大值发生时间
    sMcVMaxBTime sVMaxBTime;

    // MCMD_AFN_D_F77_VDMAX_C                
    // 日A相电压极大值
    sMcVMaxC sVMaxC;

    // MCMD_AFN_D_F78_VDMAX_C_TIME            
    // 日A相电压极大值发生时间
    sMcVMaxCTime sVMaxCTime;

    // MCMD_AFN_D_F81_IDMAX_A                 
    // 日A相电流极大值
    sMcIMaxA sIMaxA;

    // MCMD_AFN_D_F82_IDMAX_A_TIME            
    // 日A相电流极大值发生时间
    sMcIMaxATime sIMaxATime;

    // MCMD_AFN_D_F83_IDMAX_B                 
    // 日B相电流极大值
    sMcIMaxB sIMaxB;

    // MCMD_AFN_D_F84_IDMAX_B_TIME            
    // 日B相电流极大值发生时间
    sMcIMaxBTime sIMaxBTime;

    // MCMD_AFN_D_F85_IDMAX_C                
    // 日C相电流极大值
    sMcIMaxC sIMaxC;

    // MCMD_AFN_D_F86_IDMAX_C_TIME           
    // 日C相电流极大值发生时间
    sMcIMaxCTime sIMaxCTime;
    
    // MCMD_AFN_D_F89_TFW_HAVE              
    // 总基波有功功率  
    sMcTfwHave sTfwHave;

    // MCMD_AFN_D_F90_TFW_NONE                
    // 总基波无功功率
    sMcTfwNone sTfwNone;
    
    // MCMD_AFN_D_F91_THW_HAVE                
    // 总谐波有功功率
    sMcThwHave sThwHave;
    
    // MCMD_AFN_D_F92_THW_NONE                
    // 总基波无功功率
    sMcThwNone sThwNone;
    
    // MCMD_AFN_D_F97_VDPP_TIME_A             
    // A相电压越上上限日累计时间
    sMcVDppTimeA  sVDppTimeA;

    // MCMD_AFN_D_F98_VDPP_TIME_B             
    // B相电压越上上限日累计时间
    sMcVDppTimeB  sVDppTimeB;

    // MCMD_AFN_D_F99_VDPP_TIME_C             
    // C相电压越上上限日累计时间
    sMcVDppTimeC  sVDppTimeC;

    // MCMD_AFN_D_F100_VDNN_TIME_A            
    // A相电压越下下限日累计时间
    sMcVDnnTimeA sVDnnTimeA;

    // MCMD_AFN_D_F101_VDNN_TIME_B            
    // B相电压越下下限日累计时间
    sMcVDnnTimeB sVDnnTimeB;

    // MCMD_AFN_D_F102_VDNN_TIME_C            
    // C相电压越下下限日累计时间
    sMcVDnnTimeC sVDnnTimeC;

    // MCMD_AFN_D_F105_VMPP_TIME_A            
    // A相电压越上上限月累计时间
    sMcVMppTimeA  sVMppTimeA;

    // MCMD_AFN_D_F106_VMPP_TIME_B            
    // B相电压越上上限月累计时间
    sMcVMppTimeB sVMppTimeB;

    // MCMD_AFN_D_F107_VMPP_TIME_C            
    // C相电压越上上限月累计时间
    sMcVMppTimeC sVMppTimeC;

    // MCMD_AFN_D_F108_VMNN_TIME_A            
    // A相电压越下下限月累计时间
    sMcVMnnTimeA sVMnnTimeA;

    // MCMD_AFN_D_F109_VMNN_TIME_B            
    // B相电压越下下限月累计时间
    sMcVMnnTimeB sVMnnTimeB;

    // MCMD_AFN_D_F110_VMNN_TIME_C            
    // C相电压越下下限月累计时间
    sMcVMnnTimeC sVMnnTimeC;

    // MCMD_AFN_D_F113_VABR_TOTL_A            
    // A相电压总畸变率
    sMcVabrTotalA sVabrTotalA;

    // MCMD_AFN_D_F114_VABR_TOTL_B            
    // B相电压总畸变率
    sMcVabrTotalB sVabrTotalB;

    // MCMD_AFN_D_F115_VABR_TOTL_C            
    // C相电压总畸变率
    sMcVabrTotalC sVabrTotalC;
    
    // MCMD_AFN_D_F116_EABR_TOTL_A            
    // A相电流总畸变率
    sMcEabrTotalA sEabrTotalA;
    
    // MCMD_AFN_D_F117_EABR_TOTL_B            
    // B相电流总畸变率
    sMcEabrTotalB sEabrTotalB;
    
    // MCMD_AFN_D_F118_EABR_TOTL_C            
    // C相电流总畸变率
    sMcEabrTotalC sEabrTotalC;

    // MCMD_AFN_D_F121_VABR_ODD_A             
    // A相电压奇次畸变率
    sMcVabrOddA sVabrOddA;
    
    // MCMD_AFN_D_F122_VABR_EVN_A             
    // A相电压偶次畸变率
    sMcVabrEvnA sVabrEvnA;
    
    // MCMD_AFN_D_F123_VABR_ODD_B             
    // B相电压奇次畸变率
    sMcVabrOddB sVabrOddB;
    
    // MCMD_AFN_D_F124_VABR_EVN_B             
    // B相电压偶次畸变率
    sMcVabrEvnB sVabrEvnB;
    
    // MCMD_AFN_D_F125_VABR_ODD_C             
    // C相电压奇次畸变率
    sMcVabrOddC sVabrOddC;
    
    // MCMD_AFN_D_F126_VABR_EVN_C             
    // C相电压偶次畸变率
    sMcVabrEvnC sVabrEvnC;

    // MCMD_AFN_D_F128_EABR_OOD_A             
    // A相电流奇次畸变率
    sMcEabrOddA sEabrOddA;
    
    // MCMD_AFN_D_F129_EABR_EVN_A             
    // A相电流偶次畸变率
    sMcEabrEvnA sEabrEvnA;
    
    // MCMD_AFN_D_F130_EABR_OOD_B             
    // B相电流奇次畸变率
    sMcEabrOddB sEabrOddB;
    
    // MCMD_AFN_D_F131_EABR_EVN_B             
    // B相电流偶次畸变率
    sMcEabrEvnB sEabrEvnB;
    
    // MCMD_AFN_D_F132_EABR_OOD_C           
    // C相电流奇次畸变率
    sMcEabrOddC sEabrOddC;
    
    // MCMD_AFN_D_F133_EABR_EVN_C           
    // C相电流偶次畸变率
    sMcEabrEvnC sEabrEvnC;

    // MCMD_AFN_D_F137_FLS_SHRT_A             
    // A相短时闪变
    sMcFlashShortA sFlashShortA;
    
    // MCMD_AFN_D_F138_FLS_SHRT_B            
    // B相短时闪变
    sMcFlashShortB sFlashShortB;
    
    // MCMD_AFN_D_F139_FLS_SHRT_C     
    // C相短时闪变
    sMcFlashShortC sFlashShortC;
    
    // MCMD_AFN_D_F140_FLS_LONG_A       
    // A相长时闪变
    sMcFlashLongA sFlashLongA;
    
    // MCMD_AFN_D_F141_FLS_LONG_B   
    // B相长时闪变
    sMcFlashLongB sFlashLongB;
    
    // MCMD_AFN_D_F142_FLS_LONG_C             
    // C相长时闪变
    sMcFlashLongC sFlashLongC;

    // MCMD_AFN_D_F145_HARM_VOLT_A            
    // A相N次谐波电压
    sMcHarmVoltA sHarmVoltA;
    
    // MCMD_AFN_D_F146_HARM_VOLT_B          
    // B相N次谐波电压
    sMcHarmVoltB sHarmVoltB;
    
    // MCMD_AFN_D_F147_HARM_VOLT_C          
    // C相N次谐波电压
    sMcHarmVoltC sHarmVoltC;
    
    // MCMD_AFN_D_F148_HARM_ELEC_A             
    // A相N次谐波电流
    sMcHarmElecA sHarmElecA;
    
    // MCMD_AFN_D_F149_HARM_ELEC_B            
    // B相N次谐波电流
    sMcHarmElecB sHarmElecB;
    
    // MCMD_AFN_D_F150_HARM_ELEC_C            
    // C相N次谐波电流
    sMcHarmElecC sHarmElecC;

    // MCMD_AFN_D_F153_HARM_VINC_A           
    // A相N次谐波电压含有率
    sMcHarmVincA sHarmVincA;

    // MCMD_AFN_D_F154_HARM_VINC_B           
    // B相N次谐波电压含有率
    sMcHarmVincB sHarmVincB;

    // MCMD_AFN_D_F155_HARM_VINC_C            
    // C相N次谐波电压含有率
    sMcHarmVincC sHarmVincC;

    // MCMD_AFN_D_F156_HARM_EINC_A          
    // A相N次谐波电流含有率
    sMcHarmEincA sHarmEincA;

    // MCMD_AFN_D_F157_HARM_EINC_B           
    // B相N次谐波电流含有率
    sMcHarmEincB sHarmEincB;

    // MCMD_AFN_D_F158_HARM_EINC_C        
    // C相N次谐波电流含有率
    sMcHarmEincC sHarmEincC;

    // 组30 pn:非电气测量点号
    // MCMD_AFN_D_F233_NELC_VALUE      
    // 非电气量
    sMcNelcValue sNelcValue;
}uMcFrezApp;

typedef struct
{
    sMcmdPn    sCmdPn;
    uMcFrezApp uApp[1];       // ucN个
}sMcFrezOne;

typedef struct
{
    sMcYMDhm            sTs;    // 请求冻结数据任务中的数据的起始时间ts：分时日月年
    UINT16         usPeriod;    // 冻结周期 为定时冻结的时间间隔，为0表示删除本项冻结任务。
    eMcPeriodUnit     eUnit;    // 冻结周期单位
    UINT8               ucN;    // 冻结周期数：表示以冻结周期为间隔，需冻结的次数，为0表示无限次数。 
    UINT8               ucM;    // 本次应答（上报）的冻结数据任务中配置的数据单元标识数m
    sMcFrezOne      sOne[1];    // ucM 个    
}sMcFrezAutoA, sMcAfn12f9A;

// 封帧侧
#pragma pack(1)
typedef struct
{
    sMcFmt02_f          sTs;
    UINT16         usPeriod;     // 冻结周期 为定时冻结的时间间隔，为0表示删除本项冻结任务。
    UINT8             eUnit;     // 冻结周期单位
    UINT8               ucN;     // 冻结周期数：表示以冻结周期为间隔，需冻结的次数，为0表示无限次数。 
    UINT8               ucM;     // 本次应答（上报）的冻结数据任务中配置的数据单元标识数m
    UINT8         ucDaDt[1];     // 以下为变长
    
}sMcFrezAutoA_f, sMcAfn12f9A_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn12f9_s2m(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 请求重要事件(请求格式)
 * 对应AFN : MC_AFN_14_ASKE
 * 对应CMD : MCMD_AFN_E_F1_EVENT_1
 * PN 类型 : P0
 * 规则说明:
 *     所请求的事件记录个数Y满足下列计算公式：
 *     (1)当Pm＜Pn时，Y= Pn-Pm
 *     (2)当Pm＞Pn时，Y= 256＋Pn-Pm
 * 
{*///
// 用户侧
typedef struct
{
    UINT8   ucPm;           // 请求事件记录起始指针Pm
    UINT8   ucPn;           // 请求事件记录结束指针Pn
}sMcEventImpQ, sMcAfn14f1;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8   ucPm;           // 请求事件记录起始指针Pm
    UINT8   ucPn;           // 请求事件记录结束指针Pn
}sMcEventImpQ_f, sMcAfn14f1_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn14f1_m2s(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 请求重要事件(请求格式)
 * 对应AFN : MC_AFN_14_ASKE
 * 对应CMD : MCMD_AFN_E_F2_EVENT_2
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sMcEventImpQ sMcEventNmlQ;

// 封帧侧

// 转换函数
// 同 eMcErr emc_trans_afn14f1_m2s(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 请求指定事件(请求格式)
 * 对应AFN : MC_AFN_14_ASKE
 * 对应CMD : MCMD_AFN_E_F3_EVENT_3
 * PN 类型 : P0
{*///
// 用户侧
typedef struct
{
    UINT8        ucN;           // 请求事件标识个数
    eMcErc   eErc[1];           // 请求事件记录(第N个)
}sMcEventSpeQ, sMcAfn14f3;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8        ucN;           // 请求事件标识个数
    UINT8   ucErc[1];           // 请求事件记录(第N个)
}sMcEventSpeQ_f, sMcAfn14f3_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn14f3_m2s(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*}

/*******************************************
 * 数据名称: 软件版本变更事件
 * 对应AFN : MC_AFN_14_ASKE
 * 对应ERC : MC_ERC_1_RESET
 *
{*///
// 用户侧
typedef enum
{    
    MC_RESET_UNKOWN,           // 未知初始化类型
    MC_RESET_HARD_INIT,        // 硬件初始化
    MC_RESET_DATA_INIT,        // 数据区初始化
    MC_RESET_FACTORY_RESET,    // 参数及全体数据区初始化（即恢复至出厂配置）
    MC_RESET_PARA_INIT,        // 参数（除与系统主站通信有关的）及全体数据区初始化
}eMcReset;
typedef struct
{
    UINT16               usPN; // P0/监测终端号
    sMcYMDhm            sTime; // 事件发生时间,分时日月年
    eMcReset            eType; // 复位类别
}sMcErcReset, sMcErc1;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT16               usPN; // P0/监测终端号
    sMcYMDhm_f          sTime; // 事件发生时间,分时日月年
    UINT8               eType; // 变更前软件版本号
}sMcErcReset_f, sMcErc1_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_erc_1(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*}

/*******************************************
 * 数据名称: 指定数据清零事件
 * 对应AFN : MC_AFN_14_ASKE
 * 对应ERC : MC_ERC_2_DATA_CLEAR
 * 备注:     暂时用不到,暂未实现
{*///
// 用户侧
typedef union
{
    // 只限实时数据
}uMcDataPre;                  // 清零前的数据

typedef struct
{
    sMcmdPn       sCmdPn;     // 命令标识
    uMcDataPre  uPreData;     // 清零前的数据
}sMcPreCmdPn;

typedef struct
{
    UINT16          usPN; // P0/监测终端号
    sMcYMDhm       sTime; // 事件发生时间,分时日月年
    UINT8            ucN; // 复位类别
    sMcPreCmdPn  sOne[1]; // 清零之前的数据标识及数据内容       
}sMcErcDataClear, sMcErc2;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT16               usPN; // P0/监测终端号
    sMcYMDhm_f          sTime; // 事件发生时间,分时日月年
    UINT8                 ucN; // 变更前软件版本号
    /* 以下是变长
    sMcDaDt             sData;
    uMcData             uData[1]
    ......
    sMcDaDt             sData;
    uMcData             uData[1]
    */
}sMcErcDataClear_f, sMcErc2_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_erc_2(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*}

/*******************************************
 * 数据名称: 软件版本变更事件
 * 对应AFN : MC_AFN_14_ASKE
 * 对应ERC : MC_ERC_3_SOFT_CHANGE
 *
{*///
// 用户侧
typedef struct
{
    UINT16               usPN; // P0/监测终端号
    sMcYMDhm            sTime; // 事件发生时间,分时日月年
    UINT8      ucPreVerson[4]; // 变更前软件版本号
    sMcYMDhm         sPreTime; // 变更前软件版本发布时间
    UINT8      ucNewVerson[4]; // 变更后软件版本号
    sMcYMDhm         sNewTime; // 变更后软件版本发布时间
}sMcErcSoftChange, sMcErc3;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT16               usPN; // P0/监测终端号
    sMcYMDhm_f          sTime; // 事件发生时间,分时日月年
    UINT8      ucPreVerson[4]; // 变更前软件版本号
    sMcYMDhm_f       sPreTime; // 变更前软件版本发布时间
    UINT8      ucNewVerson[4]; // 变更后软件版本号
    sMcYMDhm_f       sNewTime; // 变更后软件版本发布时间
}sMcErcSoftChange_f, sMcErc3_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_erc_3(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*}

/*******************************************
 * 数据名称: 参数变更事件
 * 对应AFN : MC_AFN_14_ASKE
 * 对应ERC : MC_ERC_4_PARA_CHANGE
 *
{*///
// 用户侧
typedef struct
{
    UINT16               usPN; // P0/监测终端号
    sMcYMDhm            sTime; // 事件发生时间,分时日月年
    UINT8                 ucN; // 变更参数数据单元标识个数
    sMcmdPn         sCmdPn[1]; // 参数变量的单元标识
}sMcErcParaChange, sMcErc4;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT16               usPN; // P0/监测终端号
    sMcYMDhm_f          sTime; // 事件发生时间,分时日月年
    sMcDaDt          sDaDt[1]; // 个数由长层的le决定，由 UINT16* pusLen传入
}sMcErcParaChange_f, sMcErc4_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_erc_4(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*}

/*******************************************
 * 数据名称: 校时事件
 * 对应AFN : MC_AFN_14_ASKE
 * 对应ERC : MC_ERC_5_CHECK_TIME
 *
{*///
// 用户侧
typedef struct
{
    UINT16               usPN; // P0/监测终端号
    sMcYMDhm            sTime; // 事件发生时间,分时日月年
    sMcYWMDhms         sClock; // 校时时钟 
}sMcErcTimeCheck, sMcErc5;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT16               usPN;  // P0/监测终端号
    sMcYMDhm_f          sTime;  // 事件发生时间,分时日月年
    sMcYWMDhms_f        sClock; // 校时时钟 
}sMcErcTimeCheck_f, sMcErc5_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_erc_5(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*}

/*******************************************
 * 数据名称: 状态量变位事件
 * 对应AFN : MC_AFN_14_ASKE
 * 对应ERC : MC_ERC_6_STATE_CHANGE
 *
{*///
// 用户侧
typedef struct
{
    UINT16               usPN; // P0/监测终端号
    sMcYMDhm            sTime; // 事件发生时间,分时日月年
    BOOL           bChange[8]; // 1-8路是否发生变化
    BOOL               bSt[8]; // 1-8变化后状态 true:合 false:开
}sMcErcStateChange, sMcErc6;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT16               usPN; // P0/监测终端号
    sMcYMDhm_f          sTime; // 事件发生时间,分时日月年
    UINT8             bChange; // 1-8路是否发生变化
    UINT8                 bSt; // 1-8变化后状态 true:合 false:开
}sMcErcStateChange_f, sMcErc6_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_erc_6(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*}

/*******************************************
 * 数据名称: 遥控跳闸事件
 * 对应AFN : MC_AFN_14_ASKE
 * 对应ERC : MC_ERC_7_REMOTE_SWITCH
 *
{*///
// 用户侧
typedef struct
{
    UINT16               usPN; // P0/监测终端号
    sMcYMDhm            sTime; // 事件发生时间,分时日月年
    BOOL           bCircle[8]; // 跳闸轮数 (1-8)控制轮次是否跳闸
    float              fPower; // 跳闸时的功率    (+)XX.XXXX
    float             fPower2; // 跳闸后2分钟功率 (+)XX.XXXX
}sMcErcRemoteSwitch, sMcErc7;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT16               usPN; // P0/监测终端号
    sMcYMDhm_f          sTime; // 事件发生时间,分时日月年
    UINT8             bCircle; // 跳闸轮数 (1-8)控制轮次是否跳闸
    sMcFmt06_f         fPower; // 跳闸时的功率
    sMcFmt06_f        fPower2; // 跳闸后2分钟功率
}sMcErcRemoteSwitch_f, sMcErc7_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_erc_7(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*}

/*******************************************
 * 数据名称: 停/上电事件
 * 对应AFN : MC_AFN_14_ASKE
 * 对应ERC : MC_ERC_8_POWER_ON_OFF
 *
{*///
// 用户侧
typedef struct
{
    UINT16               usPN; // P0/监测终端号
    BOOL               bStart; // 事件起止
    sMcYMDhm            sTime; // 事件发生时间,分时日月年
}sMcErcPowerOnOff, sMcErc8;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT16               usPN; // P0/监测终端号
    sMcYMDhm_f          sTime; // 事件发生时间,分时日月年
}sMcErcPowerOnOff_f, sMcErc8_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_erc_8(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*}

/*******************************************
 * 数据名称: 总功率因素越限事件
 * 对应AFN : MC_AFN_14_ASKE
 * 对应ERC : MC_ERC_9_FACTOR_OVER
 *
{*///
// 用户侧
typedef struct
{
    UINT16               usPN; // P0/监测终端号
    sMcYMDhm            sTime; // 事件发生时间,分时日月年
    float              fOccur; // 越限时总功率因数          (+)XX.XX
    float              fLimit; // 越限时总功率越限告警定值  (+)XX.XX
}sMcErcFactorOver, sMcErc9;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT16               usPN; // P0/监测终端号
    sMcYMDhm_f          sTime; // 事件发生时间,分时日月年
    sMcFmt10_f         fOccur; // 越限时总功率因数          (+)XX.XX
    sMcFmt10_f         fLimit; // 越限时总功率越限告警定值  (+)XX.XX
}sMcErcFactorOver_f, sMcErc9_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_erc_9(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*}

/*******************************************
 * 数据名称: 电压偏差越限事件
 * 对应AFN : MC_AFN_14_ASKE
 * 对应ERC : MC_ERC_10_VOLT_EXCP
 *
{*///
// 用户侧
typedef struct
{
    UINT16         usPN;           // P0/监测终端号
    sMcYMDhm       sTime;          // 事件发生时间,分时日月年
    BOOL           bPhaseA;        // A相发生越限
    BOOL           bPhaseB;        // B相发生越限
    BOOL           bPhaseC;        // C相发生越限
    BOOL           bOverUpUp;      // 真:为越上上限 假:为越下下限
    float          fUa;            // 发生时的Ua/Uab  (+)XXX.X
    float          fUb;            // 发生时的Ub      (+)XXX.X
    float          fUc;            // 发生时的Ub      (+)XXX.X
}sMcErcVoltExcp, sMcErc10;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT16         usPN;           // P0/监测终端号
    sMcYMDhm_f     sTime;          // 事件发生时间,分时日月年
    UINT8          ucExcp;         // 越限标志
    sMcFmt08_f     fUa;
    sMcFmt08_f     fUb;
    sMcFmt08_f     fUc;
}sMcErcVoltExcp_f, sMcErc10_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_erc_10(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*}

/*******************************************
 * 数据名称: 电压回路异常事件
 * 对应AFN : MC_AFN_14_ASKE
 * 对应ERC : MC_ERC_11_VOLT_CIRCLE
 *
{*///
// 用户侧
typedef enum
{
    MC_VOLT_CIRCLE_UNKOWN,     // 未知 备用
    MC_VOLT_CIRCLE_DROP,       // 断相
    MC_VOLT_CIRCLE_LOSS,       // 失压
        
}eMcVoltCircle;

typedef struct
{
    UINT16         usPN;           // P0/监测终端号
    BOOL           bStart;         // TRUE 发生 FALSE 恢复
    sMcYMDhm       sTime;          // 事件发生时间,分时日月年
    eMcVoltCircle  eExcp;
    BOOL           bPhaseA;        // A 相是否发生异常
    BOOL           bPhaseB;        // B 相是否发生异常
    BOOL           bPhaseC;        // C 相是否发生异常
    float          fUa;            // 发生时的Ua/Uab    (+)XXX.X
    float          fUb;            // 发生时的Ub        (+)XXX.X
    float          fUc;            // 发生时的Uc/Ucb    (+)XXX.X
    float          fIa;            // 发生时的Ia        (+/-)XXX.XXX
    float          fIb;            // 发生时的Ib        (+/-)XXX.XXX
    float          fIc;            // 发生时的Ic        (+/-)XXX.XXX
}sMcErcVoltCircle, sMcErc11;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT16         usPN;           // P0/监测终端号
    sMcYMDhm_f     sTime;          // 事件发生时间,分时日月年
    UINT8          ucExcp;         // 越限标志
    sMcFmt08_f     fUa;
    sMcFmt08_f     fUb;
    sMcFmt08_f     fUc;
    sMcFmt09_f     fIa;            // 发生时的Ia        (+/-)XXX.XXX
    sMcFmt09_f     fIb;            // 发生时的Ib        (+/-)XXX.XXX
    sMcFmt09_f     fIc;            // 发生时的Ic        (+/-)XXX.XXX
}sMcErcVoltCircle_f, sMcErc11_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_erc_11(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*}

/*******************************************
 * 数据名称: 电流回路异常事件
 * 对应AFN : MC_AFN_14_ASKE
 * 对应ERC : MC_ERC_12_ELEC_CRICLE
 *
{*///
// 用户侧
typedef enum
{
    MC_ELEC_EXCP_UNKOWN,     // 未知 备用
    MC_ELEC_EXCP_SHORT,      // 短路
    MC_ELEC_EXCP_CARVE,      // 开路
    MC_ELEC_EXCP_BACK,       // 反向
}eMcElecExcp;

typedef struct
{
    UINT16         usPN;           // P0/监测终端号
    BOOL           bStart;         // TRUE 发生 FALSE 恢复
    sMcYMDhm       sTime;          // 事件发生时间,分时日月年
    eMcElecExcp    eExcp;          // 电流回路异常类型
    BOOL           bPhaseA;        // A 相是否发生异常
    BOOL           bPhaseB;        // B 相是否发生异常
    BOOL           bPhaseC;        // C 相是否发生异常
    float          fUa;            // 发生时的Ua/Uab    (+)XXX.X
    float          fUb;            // 发生时的Ub        (+)XXX.X
    float          fUc;            // 发生时的Uc/Ucb    (+)XXX.X
    float          fIa;            // 发生时的Ia        (+/-)XXX.XXX
    float          fIb;            // 发生时的Ib        (+/-)XXX.XXX
    float          fIc;            // 发生时的Ic        (+/-)XXX.XXX
}sMcErcElecCircle, sMcErc12;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT16         usPN;           // P0/监测终端号
    sMcYMDhm_f     sTime;          // 事件发生时间,分时日月年
    UINT8          ucExcp;         // 越限标志
    sMcFmt08_f     fUa;
    sMcFmt08_f     fUb;
    sMcFmt08_f     fUc;
    sMcFmt09_f     fIa;            // 发生时的Ia        (+/-)XXX.XXX
    sMcFmt09_f     fIb;            // 发生时的Ib        (+/-)XXX.XXX
    sMcFmt09_f     fIc;            // 发生时的Ic        (+/-)XXX.XXX
}sMcErcElecCircle_f, sMcErc12_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_erc_12(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*}

/*******************************************
 * 数据名称: 电压越限事件
 * 对应AFN : MC_AFN_14_ASKE
 * 对应ERC : MC_ERC_13_VOLT_OVER
 *
{*///
// 用户侧
typedef struct
{
    UINT16         usPN;           // P0/监测终端号
    BOOL           bStart;         // 事件起止
    sMcYMDhm       sTime;          // 事件发生时间,分时日月年
    BOOL           bPhaseA;        // A相发生越限
    BOOL           bPhaseB;        // B相发生越限
    BOOL           bPhaseC;        // C相发生越限
    BOOL           bOverUpUp;      // 真:为越上上限 假:为越下下限
    float          fUa;            // 发生时的Ua/Uab  (+)XXX.X
    float          fUb;            // 发生时的Ub      (+)XXX.X
    float          fUc;            // 发生时的Ub      (+)XXX.X
}sMcErcVoltOver, sMcErc13;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT16         usPN;           // P0/监测终端号
    sMcYMDhm_f     sTime;          // 事件发生时间,分时日月年
    UINT8          ucExcp;         // 越限标志
    sMcFmt08_f     fUa;
    sMcFmt08_f     fUb;
    sMcFmt08_f     fUc;
}sMcErcVoltOver_f, sMcErc13_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_erc_13(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*}

/*******************************************
 * 数据名称: 电流越限事件
 * 对应AFN : MC_AFN_14_ASKE
 * 对应ERC : MC_ERC_14_ELEC_OVER
 *
{*///
// 用户侧
typedef struct
{
    UINT16         usPN;           // P0/监测终端号
    BOOL           bStart;         // 事件起止
    sMcYMDhm       sTime;          // 事件发生时间,分时日月年
    BOOL           bPhaseA;        // A相发生越限
    BOOL           bPhaseB;        // B相发生越限
    BOOL           bPhaseC;        // C相发生越限
    BOOL           bOverUpUp;      // 真:为越上上限 假:为越上限
    float          fIa;            // 发生时的Ia        (+/-)XXX.XXX
    float          fIb;            // 发生时的Ib        (+/-)XXX.XXX
    float          fIc;            // 发生时的Ic        (+/-)XXX.XXX
}sMcErcElecOver, sMcErc14;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT16         usPN;           // P0/监测终端号
    sMcYMDhm_f     sTime;          // 事件发生时间,分时日月年
    UINT8          ucExcp;         // 越限标志
    sMcFmt09_f     fIa;            // 发生时的Ia        (+/-)XXX.XXX
    sMcFmt09_f     fIb;            // 发生时的Ib        (+/-)XXX.XXX
    sMcFmt09_f     fIc;            // 发生时的Ic        (+/-)XXX.XXX
}sMcErcElecOver_f, sMcErc14_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_erc_14(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*}

/*******************************************
 * 数据名称: 电压不平衡度越限事件
 * 对应AFN : MC_AFN_14_ASKE
 * 对应ERC : MC_ERC_15_UNBL_OVER_V
 *
{*///
// 用户侧
typedef struct
{
    UINT16         usPN;           // P0/监测终端号
    BOOL           bStart;         // 事件起止
    sMcYMDhm       sTime;          // 事件发生时间,分时日月年
    float          fUbl;           // 发生时电压不平衡度  (+)XX.XX(%)
    float          fUa;            // 发生时的Ua/Uab      (+)XXX.X
    float          fUb;            // 发生时的Ub          (+)XXX.X
    float          fUc;            // 发生时的Ub          (+)XXX.X
}sMcErcUblOverV, sMcErc15;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT16         usPN;           // P0/监测终端号
    sMcYMDhm_f     sTime;          // 事件发生时间,分时日月年
    sMcFmt10_f     fUbl;
    sMcFmt08_f     fUa;
    sMcFmt08_f     fUb;
    sMcFmt08_f     fUc;
}sMcErcUblOverV_f, sMcErc15_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_erc_15(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*}

/*******************************************
 * 数据名称: 电流不平衡度越限事件
 * 对应AFN : MC_AFN_14_ASKE
 * 对应ERC : MC_ERC_16_UNBL_OVER_I
 *
{*///
// 用户侧
typedef struct
{
    UINT16         usPN;           // P0/监测终端号
    BOOL           bStart;         // TRUE 发生 FALSE 恢复
    sMcYMDhm       sTime;          // 事件发生时间,分时日月年
    float          fUbl;           // 发生时电流不平衡度 
    float          fIa;            // 发生时的Ia        (+/-)XXX.XXX
    float          fIb;            // 发生时的Ib        (+/-)XXX.XXX
    float          fIc;            // 发生时的Ic        (+/-)XXX.XXX
}sMcErcUblOverI, sMcErc16;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT16         usPN;           // P0/监测终端号
    sMcYMDhm_f     sTime;          // 事件发生时间,分时日月年
    sMcFmt10_f     fUbl;
    sMcFmt09_f     fIa;            // 发生时的Ia        (+/-)XXX.XXX
    sMcFmt09_f     fIb;            // 发生时的Ib        (+/-)XXX.XXX
    sMcFmt09_f     fIc;            // 发生时的Ic        (+/-)XXX.XXX
}sMcErcUblOverI_f, sMcErc16_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_erc_16(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*}

/*******************************************
 * 数据名称: 谐波电压畸变率越限事件
 * 对应AFN : MC_AFN_14_ASKE
 * 对应ERC : MC_ERC_17_HUNBL_OVER_V
 *
{*///
// 用户侧
typedef struct
{
    UINT16         usPN;           // P0/监测终端号
    sMcYMDhm       sTime;          // 事件发生时间,分时日月年
    BOOL           bPhaseA;        // A相发生越限
    BOOL           bPhaseB;        // B相发生越限
    BOOL           bPhaseC;        // C相发生越限
    BOOL           bTotal;         // A相发生越限
    BOOL           bOdd;           // B相发生越限
    BOOL           bEven;          // C相发生越限
    float          fTotal;         // 发生时的谐波电压总畸变率   (+)XX.XX 
    float          fOdd;           // 发生时的谐波电压奇次畸变率 (+)XX.XX 
    float          fEven;          // 发生时的谐波电压偶次畸变率 (+)XX.XX 
}sMcErcHublOverV, sMcErc17;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT16         usPN;           // P0/监测终端号
    sMcYMDhm_f     sTime;          // 事件发生时间,分时日月年
    UINT8          ucExcp;         // 越限标志
    sMcFmt10_f     fTotal;         // 发生时的谐波电压总畸变率   
    sMcFmt10_f     fOdd;           // 发生时的谐波电压奇次畸变率
    sMcFmt10_f     fEven;          // 发生时的谐波电压偶次畸变率
}sMcErcHublOverV_f, sMcErc17_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_erc_17(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*}

/*******************************************
 * 数据名称: 谐波电流畸变率越限事件
 * 对应AFN : MC_AFN_14_ASKE
 * 对应ERC : MC_ERC_18_HUNBL_OVER_I
 *
{*///
// 用户侧
typedef sMcErcHublOverV sMcErcHublOverI, sMcErc18;

// 封帧侧

// 转换函数
eMcErr emc_trans_erc_18(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*}

/*******************************************
 * 数据名称: 闪变越限事件
 * 对应AFN : MC_AFN_14_ASKE
 * 对应ERC : MC_ERC_19_FLASH_OVER
 *
{*///
// 用户侧
typedef struct
{
    UINT16         usPN;           // P0/监测终端号
    sMcYMDhm       sTime;          // 事件发生时间,分时日月年
    BOOL           bPhaseA;        // A相发生越限
    BOOL           bPhaseB;        // B相发生越限
    BOOL           bPhaseC;        // C相发生越限
    BOOL           bLong;          // 是否为长闪变 否为短闪变
    float          fA;             // 发生时的A相闪变值   (+)XX.XX 
    float          fB;             // 发生时的B相闪变值   (+)XX.XX 
    float          fC;             // 发生时的C相闪变值   (+)XX.XX 
}sMcErcFlashOver, sMcErc19;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT16         usPN;           // P0/监测终端号
    sMcYMDhm_f     sTime;          // 事件发生时间,分时日月年
    UINT8          ucExcp;         // 越限标志
    sMcFmt10_f     fA;             // 发生时的A相闪变值   
    sMcFmt10_f     fB;             // 发生时的B相闪变值
    sMcFmt10_f     fC;             // 发生时的C相闪变值
}sMcErcFlashOver_f, sMcErc19_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_erc_19(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*}

/*******************************************
 * 数据名称: 非电气量越限事件
 * 对应AFN : MC_AFN_14_ASKE
 * 对应ERC : MC_ERC_20_NELC_OVER
 *
{*///
// 用户侧
typedef struct
{
    UINT16         usPN;           // P0/监测终端号
    BOOL           bStart;         // 事件起止
    sMcYMDhm       sTime;          // 事件发生时间,分时日月年
    BOOL           bUp;            // A相发生越限
    BOOL           bDown;          // B相发生越限
    sMcNelcValue   sValue;
}sMcErcNelcOver, sMcErc20;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT16         usPN;           // P0/监测终端号
    sMcYMDhm_f     sTime;          // 事件发生时间,分时日月年
    UINT8          ucExcp;         // 越限标志
    sMcNelcValue_f sValue;
}sMcErcNelcOver_f, sMcErc20_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_erc_20(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*}

/*******************************************
 * 数据名称: 请求重要事件(应答格式)
 * 对应AFN : MC_AFN_14_ASKE
 * 对应CMD : MCMD_AFN_E_F1_EVENT_1
 * PN 类型 : P0
 * 规则说明:
 *     所请求的事件记录个数Y满足下列计算公式：
 *     (1)当Pm＜Pn时，Y= Pn-Pm
 *     (2)当Pm＞Pn时，Y= 256＋Pn-Pm
 * 
{*///
typedef union
{
    sMcErc1    sReset;           // 对应 MC_ERC_1_RESET
    sMcErc2    sDataClear;       // 对应 MC_ERC_2_DATA_CLEAR
    sMcErc3    sChangeSoft;      // 对应 MC_ERC_3_SOFT_CHANGE
    sMcErc4    sParaChange;      // 对应 MC_ERC_4_PARA_CHANGE
    sMcErc5    sTimeCheck;       // 对应 MC_ERC_5_CHECK_TIME
    sMcErc6    sChangeState;     // 对应 MC_ERC_6_STATE_CHANGE
    sMcErc7    sRemoteSwitch;    // 对应 MC_ERC_7_REMOTE_SWITCH
    sMcErc8    sPowerOnOff;      // 对应 MC_ERC_8_POWER_ON_OFF
    sMcErc9    sFactorOver;      // 对应 MC_ERC_9_FACTOR_OVER
    sMcErc10   sVoltExcp;        // 对应 MC_ERC_10_VOLT_EXCP
    sMcErc11   sVoltCircle;      // 对应 MC_ERC_11_VOLT_CIRCLE
    sMcErc12   sElecCircle;      // 对应 MC_ERC_12_ELEC_CRICLE
    sMcErc13   sVoltOver;        // 对应 MC_ERC_13_VOLT_OVER
    sMcErc14   sElecOver;        // 对应 MC_ERC_14_ELEC_OVER
    sMcErc15   sUblOverV;        // 对应 MC_ERC_15_UNBL_OVER_V
    sMcErc16   sUblOverI;        // 对应 MC_ERC_16_UNBL_OVER_I
    sMcErc17   sHublOverV;       // 对应 MC_ERC_17_HUNBL_OVER_V
    sMcErc18   sHublOverI;       // 对应 MC_ERC_18_HUNBL_OVER_I
    sMcErc19   sFlashOver;       // 对应 MC_ERC_19_FLASH_OVER
    sMcErc20   sNelcOver;        // 对应 MC_ERC_20_NELC_OVER
}uMcRec;       // 事件记录数据结构

typedef struct
{
    eMcErc   eType;          // 事件类型
    uMcRec    uRec;          // 事件记录数据结构
}sMcErc;

// 用户侧
typedef struct
{
    UINT16  usEc1;           // 当前重要事件计数器EC1
    UINT16  usEc2;           // 当前一般事件计数器EC2
    UINT8    ucPm;           // 请求事件记录起始指针Pm
    UINT8    ucPn;           // 请求事件记录结束指针Pn
    sMcErc  sErc[1];         //  Y个事件记录     
}sMcEventImpA, sMcAfn14f1A;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT16  usEc1;           // 当前重要事件计数器EC1
    UINT16  usEc2;           // 当前一般事件计数器EC2
    UINT8   ucPm;            // 请求事件记录起始指针Pm
    UINT8   ucPn;            // 请求事件记录结束指针Pn
    UINT8   ucT1;            // 事件类型1 
    UINT8   ucLe1;           // 事件数据长度1
    UINT8   ucD1[1];         // 事件数据内容

    /*以下为变长*/
}sMcEventImpA_f, sMcAfn14f1A_f;
#pragma pack()

// 辅助函数
pMcFunc pMcGetRec(eMcErc eType);

// 转换函数
eMcErr emc_trans_afn14f1_s2m(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 请求一般事件(应答格式)
 * 对应AFN : MC_AFN_14_ASKE
 * 对应CMD : MCMD_AFN_E_F2_EVENT_2
 * PN 类型 : P0
 * 规则说明:
 *     所请求的事件记录个数Y满足下列计算公式：
 *     (1)当Pm＜Pn时，Y= Pn-Pm
 *     (2)当Pm＞Pn时，Y= 256＋Pn-Pm
 * 
{*///
// 用户侧
typedef sMcEventImpA sMcEventNmlA;

// 封帧侧

// 转换函数
eMcErr emc_trans_afn14f2_s2m(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 请求指定事件(应答格式)
 * 对应AFN : MC_AFN_14_ASKE
 * 对应CMD : MCMD_AFN_E_F3_EVENT_3
 * PN 类型 : P0
 * 
{*///
// 用户侧
typedef struct
{
    eMcErc       eType;     // 事件类型
    UINT8          ucM;     // 该事件记录的条数
    uMcRec   uRec[255];     // 事件记录数据结构 (为了占位不得不255)
                            // 暂时改为1,因上层空间不足,应该为255
}sMcSpeErc;

typedef struct
{
    UINT8      ucN;         // 事件记录代码数n
    sMcSpeErc sErc[1];      //  ucN个事件记录  
}sMcEventSpeA, sMcAfn14f3A;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8     ucN;         // 事件记录代码数n
    UINT8     ucErc1;      // 第一个事件代码ERC  
    UINT8     ucM1;        // 第一个事件代码ERC的事件记录数m 
    UINT8     ucLe1;       // 第一个事件代码ERC的事件记录数据单元长度Le

    /* 以下为变长
    // 第一个事件代码ERC的第一个事件记录数据单元
                 ...............
    // 第一个事件代码ERC的第m 个事件记录数据单元


    // 第n 个事件代码ERC
    // 第n 个事件代码ERC的事件记录数m 
    // 第n 个事件代码ERC的事件记录数据单元长度Le
    // 第n 个事件代码ERC的第一个事件记录数据单元
                 ...............
    // 第n 个事件代码ERC的第m 个事件记录数据单元
    */
}sMcEventSpeA_f, sMcAfn14f3A_f;
#pragma pack()
// 转换函数
eMcErr emc_trans_afn14f3_s2m(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 软件下载(命令格式-下行)
 * 对应AFN : MC_AFN_15_FILE
 * 对应CMD : MCMD_AFN_F_F1_SOFT_DOWN
 * PN 类型 : P0
 *
{*///
// 用户侧
typedef struct
{
    UINT8   ucFlag;       // 软件标识：
                          //“00H”：清除传输文件，恢复到升级前状态；
                          //“01H”：设备软件；
                          //  其他 ：各模块的软件编号
    UINT8   ucVersion[4]; // 软件版本                      
    UINT8   ucPos;        // 文件属性：
                          //“00H”：起始或中间帧；
                          //“01H”：结束帧；
                          //  其他 ：备用；
                          
    UINT8   ucWay;        // 文件指令：
                          //“00H”：报文方式传输；
                          //“01H”：FTP方式传输；
                          //“02H”：启用组地址；
                          //  其他 ：备用；    
    UINT16  usN;          // 总段数n
    UINT32  i;            // 第i 段标识或偏移（i=0～n）：除最后一段外，其他长度固定；
    UINT16  usLen;        // 第i 段数据长度
    UINT8   ucData[1];    // 文件数据： 长度 usLen 
                          // 报文传输时：文件内容 
                          // FTP传输时：ftp：//文件路经，账号/口令 
                          //  清除文件、启用组地址时：空
                          
}sMcSoftDownQ, sMcAfn15f1Q;

// 封帧侧
#pragma pack(1)
typedef struct
{
   UINT8   ucFlag;        // 软件标识：
                          //“00H”：清除传输文件，恢复到升级前状态；
                          //“01H”：设备软件；
                          //  其他 ：各模块的软件编号
    UINT8   ucVersion[4]; // 软件版本                      
    UINT8   ucPos;        // 文件属性：
                          //“00H”：起始或中间帧；
                          //“01H”：结束帧；
                          //  其他 ：备用；
                          
    UINT8   ucWay;        // 文件指令：
                          //“00H”：报文方式传输；
                          //“01H”：FTP方式传输；
                          //“02H”：启用组地址；
                          //  其他 ：备用；    
    UINT16  usN;          // 总段数n
    UINT32  i;            // 第i 段标识或偏移（i=0～n）：除最后一段外，其他长度固定；
    UINT16  usLen;        // 第i 段数据长度
    UINT8   ucData[1];    // 文件数据： 长度 usLen 
                          // 报文传输时：文件内容 
                          // FTP传输时：ftp：//文件路经，账号/口令 
                          //  清除文件、启用组地址时：空
}sMcSoftDownQ_f, sMcAfn15f1Q_f;
#pragma pack()

// 转换函数
eMcErr emc_trans_afn15f1_m2s(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 


///*} 

/***************************************
 *  通用部分封装函数  (低级抽象)
 *  在该函数内实现加密与解密过程
 *  两种类型的帧
 *  (1) 固定帧
 *
 *  +------+------+------+------+------+------+------+------+
 *  |       起始字符(10H)       |          启动字符         |
 *  |------+------+------+------+------+------+------+------|
 *  |          控制域C          |                           |
 *  |------+------+------+------|                           |  
 *  |          地址域A          |          用户数据         |
 *  |------+------+------+------|                           |  
 *  |        链路用户数据       |                           |
 *  |------+------+------+------+------+------+------+------|  
 *  |          校验和CS         |           帧校验          |
 *  +------+------+------+------+------+------+------+------+  
 *  
 *  链路用户数据
 *  +------+------+------+------+
 *  |         协议标识          |
 *  +------+------+------+------+
 *
 *  (2) 可变帧
 *
 *  +------+------+------+------+------+------+------+------+
 *  |        起始字符(68H)      |                           |
 *  |------+------+------+------|                           |  
 *  |           长度L           |                           |
 *  |------+------+------+------|            帧头           |  
 *  |           长度L           |                           |
 *  |------+------+------+------|                         |  
 *  |        起始字符(68H)      |                           |
 *  |------+------+------+------+------+------+------+------|  
 *  |          控制域C          |                           |
 *  |------+------+------+------|                           |  
 *  |          地址域A          |        用户数据           |
 *  |------+------+------+------|                           |  
 *  |        链路用户数据       |                           |
 *  |------+------+------+------+------+------+------+------|  
 *  |          校验和CS         |          帧校验           |
 *  |------+------+------+------+------+------+------+------|  
 *  |        结束字符(16H)      |         帧结束符          |
 *  +------+------+------+------+------+------+------+------+  
 *
 *  链路用户数据
 *  +------+------+------+------+
 *  |         协议标识          |
 *  |------+------+------+------|
 *  |        应用控制域AC       |
 *  |------+------+------+------|
 *  |       数据单元标识1       |
 *  |------+------+------+------|
 *  |         数据单元1         |
 *  |------+------+------+------|
 *  |         .........         |
 *  |------+------+------+------|
 *  |       数据单元标识n       |
 *  |------+------+------+------|
 *  |         数据单元n         |
 *  |------+------+------+------|
 *  |       附加信息域AUX       |
 *  +------+------+------+------+
 *
 *  说明:
 *  校验和CS:全部用户数据的算法和, 不考虑进位
 *
{*///

// 用户侧数据
typedef struct
{
    sMcAddress    sAddress;      // 地址域 A
    sMctrl        sCtrl;         // 控制域 C
    //sMcAc         sAc;           // 应用控制域Ac(Tp Ec Afn)    // 交到上层处理
    BOOL          bFixed;        // 固定帧 还是 可变帧 
    UINT16        usA2CsLen;     // 从addr 到 Cs 之间的数据长度
    UINT8         *pA2CsData;    // 从addr 到 Cs 之间的数据内容
    
}sMcPackCommon;


// 抽象帧头
// 固定帧


#pragma pack(1)
typedef struct
{
    UINT8   f10;      // 起始字符(10H) 
    UINT16  usC;      // 控制域C
    sMcA_f  stA;      // 地址域A
    UINT8   ucV;      // 本协议版本 定值 MC_PROTO_VERSION    
    UINT8   ucS;      // 校验和CS
    UINT8   ucE;      // 结束符
}sMcfHeadFixed;

// 可变帧
typedef struct
{
    UINT8   f68;      // 第一个 起始字符(68H)
    UINT16  usL1;     // 第一个长度L
    UINT16  usL2;     // 第二个长度L
    UINT8   s68;      // 第二个 起始字符(68H)
    UINT16  usC;      // 控制域C
    sMcA_f  stA;      // 地址域A
    UINT8   ucV;      // 本协议版本 定值 MC_PROTO_VERSION  
    UINT8   ucAc;     // 应用控制域AC
    
}sMcfHeadAlter;
#pragma pack()

// 计算检测和函数(校验和是全部用户数据的算术和,不考虑进位(模256))
UINT8 ucmc_get_check_sum(UINT8 *pStartPos, UINT16 usLen);

// 封装每个帧的公共部分 
eMcErr emc_pack_common(sMcPackCommon *psCommon,  UINT16 *pusLen, UINT8  *pOutBuf); 

// 解析公共部分
// 解析函数
eMcErr emc_unpack_common(sMcPackCommon *psUnpack, UINT8* pInBuf, UINT16 usLen);
///*}

/*******************************************************
 *  外部接口(用户只需关心以下接口)
 *
{*///

/***************************************
 *  协议模块初始化
 *  使该协议API需要先进行初始化
 *  
{*///
typedef struct
{
    eMcRole eRole;                  // 身份，主站或是从站
    UINT8   ucPermitDelayMinutes;   // 允许时延

#if  MC_CFG_SPT_MST   
    UINT8   aucPw[MC_PW_LEN];       // 消息认证码 仅在下行报文中
#endif

#if MC_CFG_ENCRYPT
    peMcEncryptFunc   EncryptFunc;  // 加密接口
    peMcDecryptFunc   DecryptFunc;  // 解密接口
#endif
    
}sMcInit;                           // 协议初始化数据结构

// 初始化函数
eMcErr eMcInit(sMcInit* psInit);
///*}

// 判断是否有是一个效帧
eMcErr emcIsValidPack(const UINT8* pInBuf, UINT16 usLen, BOOL *pbFiexed);

// 找到第一个有效的位置及其长度
eMcErr emcFindValidPack(UINT8* pinBuf, UINT16 usLen, UINT16* pusFirstOff, UINT16* pusFirstLen);

/***************************************************************************
 *  数据单元 应用层数据结构定义
 *  上行与下行同类型的数据结构有时会一不样
 *  
 *  终端在响应主站对终端的参数或数据请求时,
 *    如终端没有所需的某个数据项,则将应答报文中DT的对应标志位清除；
 *    如终端仅是没有某个数据项中的部分内容，则应将该数据项中的所缺部分
 *    内容的每个字节填写“EEH”。
 *    注意:在扩展应用层数据单元时,需要在每个定义中为每个数据项加上 
 *         有/无的标识 可以用一个BOOL 来表示 
 *  
{*///
typedef union
{
  /***************************************
     *  上下行通用
     *  主站到从站 和 从站到主站
     *  双向同样的数据结构
    {*///
    
    // MCMD_AFN_0_F1_ALL_OK_DENY
    // 全部确认/否认：对收到报文中的全部数据单元标识进行确认/否认
    eMcResCode            eResCode;         

    // MCMD_AFN_0_F2_ONE_BY_ONE
    // 按数据单元标识确认和否认：对收到报文中的全部数据单元标识进行逐个确认/否认
    sMcOnebyOne           sOneByOne;        

    // MCMD_AFN_4_F1_CON_UP_CFG
    // MCMD_AFN_A_F1_CON_UP_CFG 应答
    // 信息集中与交互终端上行通信口通信参数 
    sMcUpCfg              sConUpCfg;       

    // MCMD_AFN_4_F2_MST_PARA
    // MCMD_AFN_A_F2_MST_PARA 应答
    // 信息集中与交互终端上行通信口通信参数
    sMcMstPara            sMstPara;       

    // MCMD_AFN_4_F3_CON_AUTH_PARA
    // MCMD_AFN_A_F3_CON_AUTH_PARA
    // 信息集中与交互终端上行通信消息认证参数
    sMcAuthPara           sAuthPara;       

    // MCMD_AFN_4_F4_TEAM_ADDR
    // MCMD_AFN_A_F4_TEAM_ADDR 应答
    // 信息集中与交互终端组地址
    sMcTeamAddr           sTeamAddr;     
    
    // MCMD_AFN_4_F5_CON_IP_PORT
    // MCMD_AFN_A_F5_CON_IP_PORT 应答
    // 信息集中与交互终端IP地址和端口
    sMcIpPort             sIpPort;          

    // MCMD_AFN_4_F6_CON_CASC
    // MCMD_AFN_A_F6_CON_CASC 应答
    // 查询信息集中与交互终端级联通信参数
    sMcasc                sCasc;
    
    // MCMD_AFN_4_F7_CON_DOWN_CFG
    // 信息集中与交互终端下行以太网端口通信参数
    sMcDownCfg            sDownCfg;        
    
    // MCMD_AFN_4_F9_CON_EVENT_CFG
    // MCMD_AFN_A_F9_CON_EVENT_CFG
    // 事件记录配置
    sMcEventCfg           sEventCfg;       

    // MCMD_AFN_4_F10_CON_STATE_INPUT
    // MCMD_AFN_A_F10_CON_STATE_INPUT 应答
    // 设备状态量输入参数
    sMcStateInput         sStateInput;     
        
    // MCMD_AFN_4_F17_TML_UP_CFG
    // MCMD_AFN_A_F17_TML_UP_CFG 应答
    // 监测终端上行通信参数配置
    sMcTmlUpCfg           sTmlUpCfg;       

    // MCMD_AFN_4_F25_ELEC_MP_CFG
    // MCMD_AFN_A_F25_ELEC_MP_CFG 应答
    // 电气测量点配置参数
    sMcElecMpCfg          sElecMpCfg;      

    // MCMD_AFN_4_F26_ELEC_MP_BASE
    // MCMD_AFN_A_F26_ELEC_MP_BASE 应答
    // 电气测量点基本参数
    sMcElecMpBase         sElecMpBase;     

    // MCMD_AFN_4_F27_ELEC_LMIT_POWER
    // MCMD_AFN_A_F27_ELEC_LMIT_POWER 应答
    // 电气测量点电能量限值参数
    sMcElecLimitPower     sElecLimitPower; 

    // MCMD_AFN_4_F28_ELEC_LMIT_FACTR
    // MCMD_AFN_A_F28_ELEC_LMIT_FACTR 应答
    // 电气测量点功率因素越限值参数
    sMcFactorLimit        sFactorLimit;    

    // MCMD_AFN_4_F29_ELEC_FIX_HARM
    // MCMD_AFN_A_F29_ELEC_FIX_HARM 应答
    // 电气测量点谐波畸变率越限定值
    sMcElecFixHarm        sElecFixHarm;    

    // MCMD_AFN_4_F30_ELEC_FLASH
    // MCMD_AFN_A_F30_ELEC_FLASH 应答
    // 电气测量点闪变越限参数
    sMcElecFlash          sElecFlash;      
    
    // MCMD_AFN_4_F33_NELC_MP_CFG
    // MCMD_AFN_A_F33_NELC_MP_CFG 应答
    // 非电气测量点配置参数
    sMcNelecMpCfg         sNelecMpCfg;   

    // MCMD_AFN_4_F34_NELC_MP_PARA
    // MCMD_AFN_A_F34_NELC_MP_PARA 应答
    // 非电气测量点数据参数
    sMcNelcMpPara          sNelcMpPara;      

    // MCMD_AFN_4_F35_NELC_MP_LMIT
    // MCMD_AFN_A_F35_NELC_MP_LMIT 应答
    sMcNelcMpLimit        sNelcMpLimit;     
    // 非电气测量点越限数据参数
    
    // MCMD_AFN_4_F49_FREZ_TASK_PARA
    // MCMD_AFN_A_F49_FREZ_TASK_PARA
    // 冻结数据任务参数
    sMcFrezTaskPara       sFrezTaskPara;    
    ///*}

    /***************************************
     *  上行
     *  从站到主站
     *  通常是应答 响应
     *  以下的命令无数据项
     * MCMD_AFN_2_F1_LOG_IN
     * MCMD_AFN_2_F2_LOG_OUT
     * MCMD_AFN_2_F3_HEART_BEAT
     *
     *
    {*///
 
    // MCMD_AFN_A_F7_CON_DOWN_CFG
    // 信息集中与交互终端下行以太网端口通信参数
    sMcDownCfgA           sDownCfgA;        
    
    // MCMD_AFN_A_F11_CON_LOGIC_ADDR
    // 设备逻辑地址
    sMcLogicAddr          sLogicAddr;      

    // MCMD_AFN_A_F12_CON_VERSION
    // 查询设备版本信息
    sMcVersion            sVersion;        

    // MCMD_AFN_A_F13_ELEC_MP_INFO
    // 已配置电气测量点信息
    sMcElecMpInfo         sElecMpInfo;      

    // MCMD_AFN_A_F14_NELC_MP_INFO
    // 已配置非电气测量点信息
    sMcNelcMpInfo         sNelcMpInfo;     

    // MCMD_AFN_A_F15_SUPT_EVENT
    // 设备支持的事件记录
    sMcSuptEvent          sSuptEvent;       

    // MCMD_AFN_A_F57_TML_CFG_INFO
    // 查询已配置监测终端信息
    sMcTmlCfgInfo         sTmlCfgInfor;     

    // MCMD_AFN_D_F1_CLOCK
    sMcUerClock           sUerClock;
    
    // MCMD_AFN_D_F2_PARA_STATE
    // 参数状态标志
    sMcParaState          sParaState;       

    // MCMD_AFN_D_F3_EVENT_1
    // 重要事件计数器当前值
    UINT16                usEc1;            

    // MCMD_AFN_D_F4_EVENT_2
    // 一般事件计数器当前值
    UINT16                usEc2;           

    // MCMD_AFN_D_F5_EVENT_STATE
    // 事件状态标志
    sMcEventState         sEventState;      

    // MCMD_AFN_D_F6_POWR_TIMES
    sMcPowerTimes         sPowerTimes;

    // MCMD_AFN_D_F9_STATE 
    // 状态量及变位标志
    sMcState              sState;           
    
    // MCMD_AFN_D_F10_SWITCH 
    // 控制输出回路开关接入状态量及变位标志
    sMcSwitch             sSwitch;           
  
    // MCMD_AFN_D_F25_POWR_HAVE_T  总有功功率
    sMcPowerHaveT         sPowerHaveT;
    
    // MCMD_AFN_D_F26_POWR_NONE_T         
    // 总无功功率
    sMcPowerNoneT         sPowerNoneT;      
    
    // 总功率因数
    // MCMD_AFN_D_F27_FACTR_T               
    sMcFactorT            sFactorT;
    
    // MCMD_AFN_D_F28_FACTR_A               
    // A相功率因素
    sMcFactorA            sFactorA;
    
    // MCMD_AFN_D_F29_FACTR_B               
    // B相功率因数
    sMcFactorB            sFactorB;
    
    // MCMD_AFN_D_F30_FACTR_C               
    // C相功率因数
    sMcFactorC            sFactorC;
    
    // MCMD_AFN_D_F33_DEMAND                
    // 需量
    sMcDemand             sDemand;
    
    // MCMD_AFN_D_F34_DEMAND_MAX             
    // 日最大需量
    sMcDemandMax          sDemandMax;

    // MCMD_AFN_D_F35_DEMAND_TIME           
    // 日最大需量发生时间
    sMcDemandTime         sDemandTime;

    // MCMD_AFN_D_F41_POWR_HAVE_A            
    // A相有功功率
    sMcPowerHaveA         sPowerHaveA;

    // MCMD_AFN_D_F42_POWR_HAVE_B            
    // B相有功功率
    sMcPowerHaveB sPowerHaveB;

    // MCMD_AFN_D_F43_POWR_HAVE_C           
    // C相有功功率
    sMcPowerHaveC sPowerHaveC;

    // MCMD_AFN_D_F44_POWR_NONE_A           
    // A相无功功率
    sMcPowerNoneA sPowerNoneA;

    // MCMD_AFN_D_F45_POWR_NONE_B           
    // B相无功功率
    sMcPowerNoneB sPowerNoneB;

    // MCMD_AFN_D_F46_POWR_NONE_C            
    // C相无功功率
    sMcPowerNoneC sPowerNoneC;

    // MCMD_AFN_D_F49_POWR_HAVE_FRTH         
    // （正向）有功总电能示数
    sMcPowerHaveFrth sPowerHaveFrth;

    // MCMD_AFN_D_F50_POWR_HAVE_BACK         
    // （反向）有功总电能示数
    sMcPowerHaveBack sPowerHaveBack;

    // MCMD_AFN_D_F51_POWR_NONE_FRTH         
    // （正向）无功总电能示数
    sMcPowerNoneFrth sPowerNoneFrth;

    // MCMD_AFN_D_F52_POWR_NONE_BACK         
    // （反向）无功总电能示数
    sMcPowerNoneBack sPowerNoneBack;

    // MCMD_AFN_D_F57_VOLT_A                 
    // A相电压
    sMcVoltA sVoltA;

    // MCMD_AFN_D_F58_VOLT_B                
    // B相电压
    sMcVoltB sVoltB;

    // MCMD_AFN_D_F59_VOLT_C                
    // C相电压
    sMcVoltC sVoltC;

    // MCMD_AFN_D_F60_VANGL_A                
    // A相电压相位角
    sMcVAngleA sVAngleA;

    // MCMD_AFN_D_F61_VANGL_B                
    // B相电压相位角
    sMcVAngleB sVAngleB;

    // MCMD_AFN_D_F62_VANGL_C                
    // C相电压相位角
    sMcVAngleC sVAngleC;

    // MCMD_AFN_D_F63_VOLT_UBL               
    // 电压不平衡度
    sMcVoltUbl sVoltUbl;

    // MCMD_AFN_D_F64_CIRCLE_V               
    // 周波
    sMcVCircle sVCircle;

    // MCMD_AFN_D_F65_ELEC_A                 
    // A相电流
    sMcElecA sElecA;

    // MCMD_AFN_D_F66_ELEC_B                 
    // B相电流
    sMcElecB sElecB;

    // MCMD_AFN_D_F67_ELEC_C                  
    // C相电流
    sMcElecC sElecC;

    // MCMD_AFN_D_F68_ELEC_M                  
    // 中性线电流
    sMcElecM sElecM;

    // MCMD_AFN_D_F69_EANGL_A                 
    // A相电流相位角
    sMcEAngleA sEAngleA;

    // MCMD_AFN_D_F70_EANGL_B                 
    // B相电流相位角
    sMcEAngleB sEAngleB;

    // MCMD_AFN_D_F71_EANGL_C                 
    // C相电流相位角
    sMcEAngleC sEAngleC;

    // MCMD_AFN_D_F72_ELEC_UBL               
    // 电流不平衡度
    sMcElecUbl sElecUbl;

    // MCMD_AFN_D_F73_VDMAX_A                
    // 日A相电压极大值
    sMcVMaxA sVMaxA;

    // MCMD_AFN_D_F74_VDMAX_A_TIME            
    // 日A相电压极大值发生时间
    sMcVMaxATime sVMaxATime;

    // MCMD_AFN_D_F75_VDMAX_B                 
    // 日A相电压极大值
    sMcVMaxB sVMaxB;

    // MCMD_AFN_D_F76_VDMAX_B_TIME           
    // 日A相电压极大值发生时间
    sMcVMaxBTime sVMaxBTime;

    // MCMD_AFN_D_F77_VDMAX_C                
    // 日A相电压极大值
    sMcVMaxC sVMaxC;

    // MCMD_AFN_D_F78_VDMAX_C_TIME            
    // 日A相电压极大值发生时间
    sMcVMaxCTime sVMaxCTime;

    // MCMD_AFN_D_F81_IDMAX_A                 
    // 日A相电流极大值
    sMcIMaxA sIMaxA;

    // MCMD_AFN_D_F82_IDMAX_A_TIME            
    // 日A相电流极大值发生时间
    sMcIMaxATime sIMaxATime;

    // MCMD_AFN_D_F83_IDMAX_B                 
    // 日B相电流极大值
    sMcIMaxB sIMaxB;

    // MCMD_AFN_D_F84_IDMAX_B_TIME            
    // 日B相电流极大值发生时间
    sMcIMaxBTime sIMaxBTime;

    // MCMD_AFN_D_F85_IDMAX_C                
    // 日C相电流极大值
    sMcIMaxC sIMaxC;

    // MCMD_AFN_D_F86_IDMAX_C_TIME           
    // 日C相电流极大值发生时间
    sMcIMaxCTime sIMaxCTime;
    
    // MCMD_AFN_D_F89_TFW_HAVE              
    // 总基波有功功率  
    sMcTfwHave sTfwHave;

    // MCMD_AFN_D_F90_TFW_NONE                
    // 总基波无功功率
    sMcTfwNone sTfwNone;
    
    // MCMD_AFN_D_F91_THW_HAVE                
    // 总谐波有功功率
    sMcThwHave sThwHave;
    
    // MCMD_AFN_D_F92_THW_NONE                
    // 总基波无功功率
    sMcThwNone sThwNone;
    
    // MCMD_AFN_D_F97_VDPP_TIME_A             
    // A相电压越上上限日累计时间
    sMcVDppTimeA  sVDppTimeA;

    // MCMD_AFN_D_F98_VDPP_TIME_B             
    // B相电压越上上限日累计时间
    sMcVDppTimeB  sVDppTimeB;

    // MCMD_AFN_D_F99_VDPP_TIME_C             
    // C相电压越上上限日累计时间
    sMcVDppTimeC  sVDppTimeC;

    // MCMD_AFN_D_F100_VDNN_TIME_A            
    // A相电压越下下限日累计时间
    sMcVDnnTimeA sVDnnTimeA;

    // MCMD_AFN_D_F101_VDNN_TIME_B            
    // B相电压越下下限日累计时间
    sMcVDnnTimeB sVDnnTimeB;

    // MCMD_AFN_D_F102_VDNN_TIME_C            
    // C相电压越下下限日累计时间
    sMcVDnnTimeC sVDnnTimeC;

    // MCMD_AFN_D_F105_VMPP_TIME_A            
    // A相电压越上上限月累计时间
    sMcVMppTimeA  sVMppTimeA;

    // MCMD_AFN_D_F106_VMPP_TIME_B            
    // B相电压越上上限月累计时间
    sMcVMppTimeB sVMppTimeB;

    // MCMD_AFN_D_F107_VMPP_TIME_C            
    // C相电压越上上限月累计时间
    sMcVMppTimeC sVMppTimeC;

    // MCMD_AFN_D_F108_VMNN_TIME_A            
    // A相电压越下下限月累计时间
    sMcVMnnTimeA sVMnnTimeA;

    // MCMD_AFN_D_F109_VMNN_TIME_B            
    // B相电压越下下限月累计时间
    sMcVMnnTimeB sVMnnTimeB;

    // MCMD_AFN_D_F110_VMNN_TIME_C            
    // C相电压越下下限月累计时间
    sMcVMnnTimeC sVMnnTimeC;

    // MCMD_AFN_D_F113_VABR_TOTL_A            
    // A相电压总畸变率
    sMcVabrTotalA sVabrTotalA;

    // MCMD_AFN_D_F114_VABR_TOTL_B            
    // B相电压总畸变率
    sMcVabrTotalB sVabrTotalB;

    // MCMD_AFN_D_F115_VABR_TOTL_C            
    // C相电压总畸变率
    sMcVabrTotalC sVabrTotalC;
    
    // MCMD_AFN_D_F116_EABR_TOTL_A            
    // A相电流总畸变率
    sMcEabrTotalA sEabrTotalA;
    
    // MCMD_AFN_D_F117_EABR_TOTL_B            
    // B相电流总畸变率
    sMcEabrTotalB sEabrTotalB;
    
    // MCMD_AFN_D_F118_EABR_TOTL_C            
    // C相电流总畸变率
    sMcEabrTotalC sEabrTotalC;

    // MCMD_AFN_D_F121_VABR_ODD_A             
    // A相电压奇次畸变率
    sMcVabrOddA sVabrOddA;
    
    // MCMD_AFN_D_F122_VABR_EVN_A             
    // A相电压偶次畸变率
    sMcVabrEvnA sVabrEvnA;
    
    // MCMD_AFN_D_F123_VABR_ODD_B             
    // B相电压奇次畸变率
    sMcVabrOddB sVabrOddB;
    
    // MCMD_AFN_D_F124_VABR_EVN_B             
    // B相电压偶次畸变率
    sMcVabrEvnB sVabrEvnB;
    
    // MCMD_AFN_D_F125_VABR_ODD_C             
    // C相电压奇次畸变率
    sMcVabrOddC sVabrOddC;
    
    // MCMD_AFN_D_F126_VABR_EVN_C             
    // C相电压偶次畸变率
    sMcVabrEvnC sVabrEvnC;

    // MCMD_AFN_D_F128_EABR_OOD_A             
    // A相电流奇次畸变率
    sMcEabrOddA sEabrOddA;
    
    // MCMD_AFN_D_F129_EABR_EVN_A             
    // A相电流偶次畸变率
    sMcEabrEvnA sEabrEvnA;
    
    // MCMD_AFN_D_F130_EABR_OOD_B             
    // B相电流奇次畸变率
    sMcEabrOddB sEabrOddB;
    
    // MCMD_AFN_D_F131_EABR_EVN_B             
    // B相电流偶次畸变率
    sMcEabrEvnB sEabrEvnB;
    
    // MCMD_AFN_D_F132_EABR_OOD_C           
    // C相电流奇次畸变率
    sMcEabrOddC sEabrOddC;
    
    // MCMD_AFN_D_F133_EABR_EVN_C           
    // C相电流偶次畸变率
    sMcEabrEvnC sEabrEvnC;

    // MCMD_AFN_D_F137_FLS_SHRT_A             
    // A相短时闪变
    sMcFlashShortA sFlashShortA;
    
    // MCMD_AFN_D_F138_FLS_SHRT_B            
    // B相短时闪变
    sMcFlashShortB sFlashShortB;
    
    // MCMD_AFN_D_F139_FLS_SHRT_C     
    // C相短时闪变
    sMcFlashShortC sFlashShortC;
    
    // MCMD_AFN_D_F140_FLS_LONG_A       
    // A相长时闪变
    sMcFlashLongA sFlashLongA;
    
    // MCMD_AFN_D_F141_FLS_LONG_B   
    // B相长时闪变
    sMcFlashLongB sFlashLongB;
    
    // MCMD_AFN_D_F142_FLS_LONG_C             
    // C相长时闪变
    sMcFlashLongC sFlashLongC;

    // MCMD_AFN_D_F145_HARM_VOLT_A            
    // A相N次谐波电压
    sMcHarmVoltA sHarmVoltA;
    
    // MCMD_AFN_D_F146_HARM_VOLT_B          
    // B相N次谐波电压
    sMcHarmVoltB sHarmVoltB;
    
    // MCMD_AFN_D_F147_HARM_VOLT_C          
    // C相N次谐波电压
    sMcHarmVoltC sHarmVoltC;
    
    // MCMD_AFN_D_F148_HARM_ELEC_A             
    // A相N次谐波电流
    sMcHarmElecA sHarmElecA;
    
    // MCMD_AFN_D_F149_HARM_ELEC_B            
    // B相N次谐波电流
    sMcHarmElecB sHarmElecB;
    
    // MCMD_AFN_D_F150_HARM_ELEC_C            
    // C相N次谐波电流
    sMcHarmElecC sHarmElecC;

    // MCMD_AFN_D_F153_HARM_VINC_A           
    // A相N次谐波电压含有率
    sMcHarmVincA sHarmVincA;

    // MCMD_AFN_D_F154_HARM_VINC_B           
    // B相N次谐波电压含有率
    sMcHarmVincB sHarmVincB;

    // MCMD_AFN_D_F155_HARM_VINC_C            
    // C相N次谐波电压含有率
    sMcHarmVincC sHarmVincC;

    // MCMD_AFN_D_F156_HARM_EINC_A          
    // A相N次谐波电流含有率
    sMcHarmEincA sHarmEincA;

    // MCMD_AFN_D_F157_HARM_EINC_B           
    // B相N次谐波电流含有率
    sMcHarmEincB sHarmEincB;

    // MCMD_AFN_D_F158_HARM_EINC_C        
    // C相N次谐波电流含有率
    sMcHarmEincC sHarmEincC;

    // 组30 pn:非电气测量点号
    // MCMD_AFN_D_F233_NELC_VALUE      
    // 非电气量
    sMcNelcValue  sNelcValue;

    // MCMD_AFN_C_F9_FREZ_AUTO
    // 请求（定时上报）冻结数据任务
    sMcFrezAutoA   sFrezAutoA;    

    // MCMD_AFN_E_F1_EVENT_1
    // 请求重要事件(应答结构)
    sMcEventImpA   sEventImpA;

    // MCMD_AFN_E_F2_EVENT_2
    // 请求一般事件(应答结构)
    sMcEventNmlA   sEventNmlA;   

    // MCMD_AFN_E_F3_EVENT_3
    // 请求指定事件(应答结构) 暂时不处理这条
    //sMcEventSpeA    sEventSpeA;
    ///*}
    
    /***************************************
     *  下行
     *  主站到从站
     *  通常是命令 请求
     *
     *  以下命令无数据项
     * MCMD_AFN_1_F1_HARD_INIT
     * MCMD_AFN_1_F2_DATA_INIT
     * MCMD_AFN_1_F3_FACTORY_RESET
     * MCMD_AFN_1_F4_PARA_INIT
     * MCMD_AFN_2_F4_LINK_OK
     * MCMD_AFN_5_F3_AUTO_SAY_ON
     * MCMD_AFN_5_F4_AUTO_SAY_OFF
     * MCMD_AFN_5_F5_CON_LINK_ON
     * MCMD_AFN_5_F6_CON_LINK_OFF
     * MCMD_AFN_5_F25_REPT_FREZ_ON
     * MCMD_AFN_5_F26_REPT_FREZ_OFF
     * MCMD_AFN_5_F27_TASK_FREZ_ON
     * MCMD_AFN_5_F28_TASK_FREZ_OFF
     * MCMD_AFN_A_F1_CON_UP_CFG
     * MCMD_AFN_A_F3_CON_AUTH_PARA
     * MCMD_AFN_A_F4_TEAM_ADDR
     * MCMD_AFN_A_F5_CON_IP_PORT
     * MCMD_AFN_A_F6_CON_CASC
     * MCMD_AFN_A_F9_CON_EVENT_CFG
     * MCMD_AFN_A_F10_CON_STATE_INPUT
     * MCMD_AFN_A_F11_CON_LOGIC_ADDR
     * MCMD_AFN_A_F12_CON_VERSION
     * MCMD_AFN_A_F13_ELEC_MP_INFO
     * MCMD_AFN_A_F14_NELC_MP_INFO
     * MCMD_AFN_A_F15_SUPT_EVENT
     * MCMD_AFN_A_F17_TML_UP_CFG
     * MCMD_AFN_A_F25_ELEC_MP_CFG
     * MCMD_AFN_A_F26_ELEC_MP_BASE
     * MCMD_AFN_A_F28_ELEC_LMIT_POWER
     * MCMD_AFN_A_F29_ELEC_LMIT_FACTR
     * MCMD_AFN_A_F33_NELC_MP_CFG
     * MCMD_AFN_A_F34_NELC_MP_PARA
     * MCMD_AFN_A_F49_FREZ_TASK_PARA
     * MCMD_AFN_A_F57_TML_CFG_INFO
     * MCMD_AFN_C_F1_FREZ_TEMP
     * MCMD_AFN_D_F1_CLOCK 
     *
    {*///
    // MCMD_AFN_1_F5_DATA_CLEAR
    // 指定数据清零  
    sMcRtDataClear        sRtDataClear;    

    // MCMD_AFN_5_F1_CHECK_TIME
    // 校时命令
    sMcUerClock           sCheckClock;    

    // MCMD_AFN_5_F2_FREZ_TEMP
    // 临时冻结命令
    sMcFrezTemp           sFrezTemp;        

    // MCMD_AFN_5_F9_REMOTE_OFF
    // 遥控跳闸
    sMcRemoteOff          sRemoteOff;       

    // MCMD_AFN_5_F10_REMOTE_ON
    // 允许合闸
    sMcRemoteOn           sRemoteOn;        
    
    // MCMD_AFN_5_F17_NX_MODEL_ACT
    // 能效模型有效
    sMcNxModelAct         sNxModelAct;     
    
    // MCMD_AFN_5_F18_NX_MODEL_CLR
    // 能效模型清除
    sMcNxModelClr         sNxModelClr;      
    
    // MCMD_AFN_5_F19_RQ_RESPN_ACT
    // 需求响应信息有效
    sMcRqRespnAct         sRqRespnAct;     
    
    // MCMD_AFN_5_F20_RQ_RESPN_CLT
    // 需求响应信息清除
    sMcRqRespnClr         sRqRespnClr;     

    // MCMD_AFN_A_F2_MST_PARA  命令参数
    // 查询主(子)站参数
    sMcMstParaQ           sMstParaQ;       

    // MCMD_AFN_A_F7_CON_DOWN_CFG
    // 信息集中与交互终端下行以太网端口通信参数
    sMcDownCfgQ           sDownCfgQ;        
    
    // MCMD_AFN_C_F9_FREZ_AUTO
    // 请求（定时上报）冻结数据任务
    sMcFrezAutoQ          sFrezAutoQ;      

    // MCMD_AFN_E_F1_EVENT_1
    // 请求重要事件(命令参数)
    sMcEventImpQ          sEventImpQ;

    // MCMD_AFN_E_F2_EVENT_2
    // 请求一般事件(命令参数)
    sMcEventNmlQ          sEventNmlQ;  

    // MCMD_AFN_E_F3_EVENT_3
    // 请求指定事件(命令参数) 暂时不处理这条
    //sMcEventSpeQ         sEventSpeQ;
    ///*}
    
    // 仅用于占位 无应用意义
    UINT8            ucRev[MC_UNIT_DATA_MAX];
    
}uMcApp;

/***************************************
 *  帧内容数据结构 用户侧  (低级抽象)
 *  用于封装与解析
 *  变长结构
{*///
typedef struct
{
    sMcPnFn    sPnFn;
    uMcApp     *puApp[MC_PN_INDEX_MAX][MC_FN_INDEX_MAX];   // 保存最多64个数据单元的指针
}sMcBaseData;

typedef struct
{
    sMcAddress    sAddress;        // 地址域 A
    sMctrl        sCtrl;           // 控制域 C
    BOOL          bFixed;          // 固定帧还是可变帧 

    // 可变帧存在以下字段
    sMcAc         sAc;             // 应用控制域Ac(Tp Ec Afn)
    sMcEc         sEc;             // 事件计数器  决定于 sMcAc 域中的bEc (只存在于上行报文中)
    sMcTp         sTp;             // 时间标签    决定于 sMcAc 域中的bTp 
    UINT8         aPw[MC_PW_LEN];  // 消息认证码  (只存在于重要的下行报文中)
    
    // 数据单元域  变长域
    UINT16        usNum;           // 数据单元组的个数
    sMcBaseData   sData[1];        // 数据单元组
}smcBaskPack;

void vmc_free_base_data(sMcBaseData* pBaseData, INT32 Num);

// 封帧函数
eMcErr emc_pack_base(smcBaskPack* psPack, UINT8* pOutBuf, UINT16* pusLen);   

// 解帧函数
eMcErr emc_unPack_base(smcBaskPack *psUnpack, UINT8* pInBuf, UINT16 usLen);
///*}

/***************************************
 *  数据单元标识与对应的数据单元 (高级抽象)
 *  
 * 数据单元为按数据单元标识所组织的数据,包括参数、命令等。
 * 数据组织的顺序规则：离散方式
 * 即：命令标识 数据单元 一一对应的方式
 * 
{*///
typedef struct
{
    eMcmd        eCmd;        // 功能码
    UINT16       usPN;        // Pn (0 <= pn <= 2040 )
    BOOL         bApp;        // 是否有数据单元
    uMcApp       uApp;        // 对应不同的命令类型, 及上下行类型, 应用层数据时有时无
    
}sMcData;
///*}

/***************************************
 *  封帧与解帧(通用) 用户侧数据结构 (高级抽象)
 *  用于封装及解封装 
 *  变长结构
{*///
typedef struct
{    
    sMcAddress    sAddress;        // 地址域 A
    sMctrl        sCtrl;           // 控制域 C
    BOOL          bFixed;          // 固定帧还是可变帧 

    // 可变帧有以下可选字段
    sMcAc         sAc;             // 应用控制域Ac(Tp Ec Afn)
    sMcEc         sEc;             // 事件计数器  决定于 sMcAc 域中的bEc (只存在于上行报文中)
    sMcTp         sTp;             // 时间标签    决定于 sMcAc 域中的bTp 
    BOOL          bPw;             // 是否有Pw字段(只存在重要的下行的报文中)
    UINT8         aPw[MC_PW_LEN];  // 消息认证码  (只存在于重要的下行报文中)

    // 数据单元域  变长域
    UINT16        usNum;          // 数据单元组的个数
    sMcData       sData[1];       // usNum个数据单元组
    
}smcPack;

// 高级接口(用户使用)
// 封装函数
eMcErr emcPack(smcPack* psPack, UINT8* pOutBuf, UINT16* pusLen);   

// 解帧函数
eMcErr emcUnPack(smcPack *psUnpack, UINT8* pInBuf, UINT16 usLen);
///*}

/***************************************
 *  封帧与解帧(通用) (集中器接口 高级抽象)
 *  用于屏蔽集中器侧不需要关心的字段
 *  用于封装及解封装 
 *  变长结构
{*///
typedef struct
{
    sMcAddress    sAddress;        // 地址域 A
    BOOL          bReSend;         // 是否为重发  TRUE 重发的帧计数不会自动增加1 FALSE 会自增1
    BOOL          bActive;         // 是否为主动上报 (仅登录、心跳、退出登录、1类2类数据主动上报时为真)
    UINT8         ucRSEQ;          // 响应帧序号 RSEQ   (0~15)
                                   /*
                                      响应帧序号 RSEQ
                                       (1) 响应帧序号 RSEQ 在 PRM=0 时，即从动帧中有效，
                                           用编码表示 0~15，用于多个从动帧对应一个启动帧的传输。
                                       (2) 每一对启动站和从动站之间均有 1 个独立的计数器，
                                           用于记录当前 RSEQ，当只需一帧从动帧回应启动帧的，
                                           RSEQ=0；当需用 n （n≤16）帧回应的，RSEQ 从 n-1 起递减计数，
                                           每回送一帧减 1，直至最后一帧 RSEQ=0。
                                   */
    UINT16        usNum;           // 该包中含有子命令的个数 最少有一个子命令    
    sMcData       sData[1];        // usNum个数据单元组
}sMcPackCon;

// 封装函数
eMcErr emcPackCon(sMcPackCon* psPack, UINT8* pOutBuf, UINT16* pusLen);   

// 解帧函数
eMcErr emcUnPackCon(sMcPackCon *psUnpack, UINT8* pInBuf, UINT16 usLen);
///*}

/***************************************
 *  仅用于封帧 (主站接口 高级抽象)
 *  用于屏蔽主站侧不需要关心的字段
 *  用于封装及解封装 
 *  变长结构
{*///
typedef struct
{
    sMcAddress    sAddress;        // 地址域 A
    UINT8         ucPSEQ;          // 启动帧序号 PSEQ
    //UINT8         ucRSEQ;          // 响应帧序号 RSEQ
    UINT8         aPw[MC_PW_LEN];  // 消息认证码  (只存在于重要的下行报文中)

    // 数据单元域  变长域
    UINT16        usNum;           // 数据单元组的个数
    sMcData       sData[1];        // usNum个数据单元组

}sMcPackMst;

// 封装函数
eMcErr emcPackMst(sMcPackMst* psPack, UINT8* pOutBuf, UINT16* pusLen);   

// 仅用于解封装
typedef struct
{
    sMcAddress    sAddress;        // 地址域 A
    UINT8         ucPSEQ;          // 启动帧序号 PSEQ
    UINT8         ucRSEQ;          // 响应帧序号 RSEQ
    // 数据单元域  变长域
    UINT16        usNum;           // 数据单元组的个数
    sMcData       sData[1];        // usNum个数据单元组
}sMcUnpackMst;

// 解帧函数
eMcErr emcUnPackMst(sMcPackMst *psUnpack, UINT8* pInBuf, UINT16 usLen);
///*}

#endif // _GBNX_31_API_H_

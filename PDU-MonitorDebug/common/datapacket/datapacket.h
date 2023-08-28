#ifndef DATAPACKET_H
#define DATAPACKET_H
#include <QtCore>
#include <QColor>

#define LINE_NUM  3
#define PACK_ARRAY_SIZE LINE_NUM
#define OpSize  6

// 倍率定义
#define COM_RATE_VOL	1.0    // 电压
#define COM_RATE_CUR	10.0    // 电流
#define COM_RATE_POW	1000.0  // 功率
#define COM_RATE_ELE	10.0    // 电能
#define COM_RATE_PF     100.0   // 功率因数
#define COM_RATE_TEM	1.0    // 温度
#define COM_RATE_HUM	1.0    // 湿度
/**
 * 数据单元：包括当前值，阈值，临界值，告警状态等
 */
struct sDataUnit
{
    sDataUnit() {size=0;}

    ushort size;
    ushort value[PACK_ARRAY_SIZE]; // 值
    ushort min[PACK_ARRAY_SIZE]; // 最小值
    ushort max[PACK_ARRAY_SIZE]; // 最大值
    uchar alarm[PACK_ARRAY_SIZE]; // 报警值 0表示未报警  1表示已报警 2表示已记录
    uchar status[PACK_ARRAY_SIZE];
};



/**
 * 数据对象：包括电流，电压，功率，电能，开关状态，插接位名称
 */
struct sObjData
{
    sObjData() {size=0;}
    int size;
    sDataUnit vol; // 电压
    sDataUnit cur; // 电流
    sDataUnit tem; // 温度
    sDataUnit hum; // 湿度

    ushort pow[PACK_ARRAY_SIZE]; // 功率
    ushort powed[PACK_ARRAY_SIZE]; // 功率
    uint ele[PACK_ARRAY_SIZE]; // 电能

    uchar pf[PACK_ARRAY_SIZE]; // 功率因数
    uchar sw[PACK_ARRAY_SIZE]; // 开关状态 0 表示未启用
    ushort aPow[PACK_ARRAY_SIZE]; // 视在功率值
    uchar status[PACK_ARRAY_SIZE];
    ushort cured[PACK_ARRAY_SIZE]; // 电流

    ushort hz[PACK_ARRAY_SIZE]; // 电压频率
    ushort br;  // 00	表示波特率9600(00默认9600，01为4800，02为9600，03为19200，04为38400)
    ushort version;
    ushort reserve;
    uchar ip[10];
};

/**
 * 数据单元：包括当前值，阈值，临界值，告警状态等
 */
struct sUnitCfg
{
    uchar en;
    uchar id;
    float min; // 最小值
    float max; // 最大值

    float crMin; // 最小值
    float crMax; // 最大值
};



/**
 * 数据对象：包括电流，电压，功率，电能，开关状态，插接位名称
 */
struct sObjCfg
{
    sUnitCfg vol; // 电压
    sUnitCfg cur; // 电流
    sUnitCfg output; // 电流
    sUnitCfg opCur[OpSize]; // 输出位电流

    sUnitCfg tem; // 温度
    sUnitCfg hum; // 湿度
    sUnitCfg fantem;
    sUnitCfg pwm;
    sUnitCfg loopcur;
};

struct sTypeCfg
{
    uchar si_ac;
    uchar si_led;
    uchar si_horizontal;
    uchar si_lines;
    uchar si_series;
    uchar si_standar;
    uchar si_version;
    sObjCfg si_cfg;

    uchar ip_ac;
    uchar ip_lcd;
    uchar ip_lines;
    uchar ip_language;
    uchar ip_modbus;
    uchar ip_standard;
    uchar ip_version;
    // 1:IP-PDUV1 3:IP-PDUV3 4:IP-PDUV3-C3
    // 5:IP-PDUV3-EATON 6:IP-PDUV6 7:IP-PDUV6-HUAWEI
    // 9:IP_PDUV1_HUADA// IPV1华大 10:IP_PDUV3_BYTE 11:IP_PDUV3_SHATE 12:
    uchar security;
    uchar log_en;
    sObjCfg ip_cfg;
    QString ip_inFirst;
    QString ip_inSecond;
    QString ip_outFirst;
    QString ip_outSecond;
};

struct sDevType
{
    uchar devId;
    uchar devType; // 0 SI-PDU  1 IP-PDU
    uchar screen;//0 液晶 1 断码屏 2 数码管 3 V1和断码屏
    uchar lines;
    uchar ac;
    uchar version;
    // IP V1 V3
    // 1:IP-PDUV1 3:IP-PDUV3 4:IP-PDUV3-C3 5:IP-PDUV3-EATON 6:IP-PDUV6 7:IP-PDUV6-HUAWEI
    // 8:IP-PDUV1-YIXIN 9:IP_PDUV1_HUADA 10:IP_PDUV3_BYTE 11:IP_PDUV3_SHATE
    QString dev_type;
    QString sn;
};



/**
 * 设备数据结构体：
 */
struct sDevData
{
    sDevType dt; //设备类型
    sTypeCfg cfg; // 配置数据
    sObjData data;
};


enum {
    Test_Fun, // 功能
    Test_Start, // 开始
    Test_Seting,
    Test_Collect,
    Test_Ading,
    Test_vert, // 验证
    Test_Over, // 终止
    Test_End, // 完成

    Test_Info=0,
    Test_Pass=1,
    Test_Fail=2,
    Test_Standard=0,
    Test_AI=1,
    Test_Onebyone=2,
};

struct sProgress
{
    sProgress() {step=0;}

    uchar step; // 步骤
    QString time;
    QList<bool> pass;
    QStringList status;

    uchar result;    // 最终结果
    QTime startTime;
};


/**
 * 数据包
 */
class sDataPacket
{
    sDataPacket();
public:
    static sDataPacket *bulid();

    void init();
    sDevData *getDev() {return dev;}
    sProgress *getPro() {return pro;}

private:
    sDevData *dev;
    sProgress *pro;
};



#endif // DATAPACKET_H

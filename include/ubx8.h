#ifndef UBX
#define UBX

#include <stdint.h>

#pragma pack(push, 1)

typedef struct {  // 0x28 0x00
    uint32_t iTOW;
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t min;
    uint8_t sec;
    uint8_t valid;
    int32_t nano;
    uint8_t gpsFix;
    uint8_t flags;
    uint8_t reserved1[2];
    int32_t lon;
    int32_t lat;
    int32_t height;
    int32_t hMSL;
    int32_t gSpeed;
    int32_t speed;
    int32_t headMot;
    int32_t headVeh;
    uint32_t hAcc;
    uint32_t vAcc;
    uint32_t sAcc;
    uint32_t headAcc;
    uint8_t reserved2[4];
} HNR_PVT;

typedef struct {  // 0x01 0x60
    uint32_t iTOW;
    uint8_t aopCfg;
    uint8_t status;
    uint8_t reserved1[10];
} NAV_AOPSTATUS;

typedef struct {  // 0x01 0x05
    uint32_t iTOW;
    uint8_t version;
    uint8_t reserved1[3];
    int32_t roll;
    int32_t pitch;
    int32_t heading;
    uint32_t accRoll;
    uint32_t accPitch;
    uint32_t accHeading;
} NAV_ATT;

typedef struct {  // 0x01 0x22
    uint32_t iTOW;
    int32_t clkB;
    int32_t clkD;
    uint32_t tAcc;
    uint32_t fAcc;
} NAV_CLOCK;

typedef struct {  // 0x01 0x31
    uint32_t iTOW;
    int32_t age;
    int16_t baseId;
    int16_t baseHealth;
    uint8_t numCh;
    uint8_t status;
    uint8_t reserved1[2];
    struct {
        uint8_t svid;
        uint8_t flags;
        uint16_t ageC;
        float prc;
        float prrc;
    } buf[32];
} NAV_DGPS;

typedef struct {  // 0x01 0x04
    uint32_t iTOW;
    uint16_t gDOP;
    uint16_t pDOP;
    uint16_t tDOP;
    uint16_t vDOP;
    uint16_t hDOP;
    uint16_t nDOP;
    uint16_t eDOP;
} NAV_DOP;

typedef struct {  // 0x01 0x61
    uint32_t iTOW;
} NAV_EOE;

typedef struct {  // 0x01 0x39
    uint32_t iTOW;
    uint8_t version;
    uint8_t status;
    uint8_t numFences;
    uint8_t combState;
    struct {
        uint8_t state;
        uint8_t reserved1;
    } buf[32];
} NAV_GEOFENCE;

typedef struct {  // 0x01 0x09
    uint8_t version;
    uint8_t reserved1[3];
    uint32_t iTOW;
    uint32_t distance;
    uint32_t totalDistance;
    uint32_t distanceStd;
} NAV_ODO;

typedef struct {  // 0x01 0x34
    uint32_t iTOW;
    uint8_t version;
    uint8_t numSv;
    uint8_t reserved1[2];
    struct {
        uint8_t gnssId;
        uint8_t svId;
        uint8_t svFlag;
        uint8_t eph;
        uint8_t alm;
        uint8_t otherOrb;
    } buf[32];
} NAV_ORB;

typedef struct {  // 0x01 0x01
    uint32_t iTOW;
    int32_t ecefX;
    int32_t ecefY;
    int32_t ecefZ;
    uint32_t pAcc;
} NAV_POSECEF;

typedef struct {  // 0x01 0x02
    uint32_t iTOW;
    int32_t lon;
    int32_t lat;
    int32_t height;
    int32_t hMSL;
    uint32_t hAcc;
    uint32_t vAcc;
} NAV_POSLLH;

typedef struct {  // 0x01 0x07
    uint32_t iTOW;
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t min;
    uint8_t sec;
    uint8_t valid;
    uint32_t tAcc;
    int32_t nano;
    uint8_t fixType;
    uint8_t flags;
    uint8_t flags2;
    uint8_t numSV;
    int32_t lon;
    int32_t lat;
    int32_t height;
    int32_t hMSL;
    uint32_t hAcc;
    uint32_t vAcc;
    int32_t velN;
    int32_t velE;
    int32_t velD;
    int32_t gSpeed;
    int32_t headMot;
    uint32_t sAcc;
    uint32_t headAcc;
    uint16_t pDOP;
    uint8_t reserved1[6];
    int32_t headVeh;
    uint8_t reserved2[4];
} NAV_PVT;

typedef struct {  // 0x01 0x35
    uint32_t iTOW;
    uint8_t version;
    uint8_t numSvs;
    uint8_t reserved1[2];
    struct {
        uint8_t gnssId;
        uint8_t svId;
        uint8_t cno;
        int8_t elev;
        int16_t azim;
        int16_t prRes;
        uint32_t flags;
    } buf[32];
} NAV_SAT;

typedef struct {  // 0x01 0x32
    uint32_t iTOW;
    uint8_t geo;
    uint8_t mode;
    int8_t sys;
    uint8_t service;
    uint8_t cnt;
    uint8_t reserved1[3];
    struct {
        uint8_t svid;
        uint8_t flags;
        uint8_t udre;
        uint8_t svSys;
        uint8_t svService;
        uint8_t reserved2;
        int16_t prc;
        uint8_t reserved3[2];
        int16_t ic;
    } buf[32];
} NAV_SBAS;

typedef struct {  // 0x01 0x06
    uint32_t iTOW;
    int32_t fTOW;
    int16_t week;
    uint8_t gpsFix;
    uint8_t flags;
    int32_t ecefX;
    int32_t ecefY;
    int32_t ecefZ;
    uint32_t pAcc;
    int32_t ecefVX;
    int32_t ecefVY;
    int32_t ecefVZ;
    uint32_t sAcc;
    uint16_t pDOP;
    uint8_t reserved1;
    uint8_t numSV;
    uint8_t reserved2[4];
} NAV_SOL;

typedef struct {  // 0x01 0x03
    uint32_t iTOW;
    uint8_t gpsFix;
    uint8_t flags;
    uint8_t fixStat;
    uint8_t flags2;
    uint32_t ttff;
    uint32_t msss;
} NAV_STATUS;

typedef struct {  // 0x01 0x30
    uint32_t iTOW;
    uint8_t numCh;
    uint8_t globalFlags;
    uint8_t reserved1[2];
    struct {
        uint8_t chn;
        uint8_t svid;
        uint8_t flags;
        uint8_t quality;
        uint8_t cno;
        int8_t elev;
        int16_t azim;
        int32_t prRes;
    } buf[32];
} NAV_SVINFO;

typedef struct {  // 0x01 0x24
    uint32_t iTOW;
    uint32_t SOW;
    int32_t fSOW;
    int16_t week;
    int8_t leapS;
    uint8_t valid;
    uint32_t tAcc;
} NAV_TIMEBDS;

typedef struct {  // 0x01 0x25
    uint32_t iTOW;
    uint32_t galTow;
    int32_t fGalTow;
    int16_t galWno;
    int8_t leapS;
    uint8_t valid;
    uint32_t tAcc;
} NAV_TIMEGAL;

typedef struct {  // 0x01 0x23
    uint32_t iTOW;
    uint32_t TOD;
    int32_t fTOD;
    uint16_t Nt;
    uint8_t N4;
    uint8_t valid;
    uint32_t tAcc;
} NAV_TIMEGLO;

typedef struct {  // 0x01 0x20
    uint32_t iTOW;
    int32_t fTOW;
    int16_t week;
    int8_t leapS;
    uint8_t valid;
    uint32_t tAcc;
} NAV_TIMEGPS;

typedef struct {  // 0x01 0x26
    uint32_t iTOW;
    uint8_t version;
    uint8_t reserved1[3];
    uint8_t srcOfCurrLs;
    int8_t currLs;
    uint8_t srcOfLsChange;
    int8_t lsChange;
    int32_t timeToLsEvent;
    uint16_t dateOfLsGpsWn;
    uint16_t dateOfLsGpsDn;
    uint8_t reserved2[3];
    uint8_t valid;
} NAV_TIMELS;

typedef struct {  // 0x01 0x21
    uint32_t iTOW;
    uint32_t tAcc;
    int32_t nano;
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t min;
    uint8_t sec;
    uint8_t valid;
} NAV_TIMEUTC;

typedef struct {  // 0x01 0x11
    uint32_t iTOW;
    int32_t ecefVX;
    int32_t ecefVY;
    int32_t ecefVZ;
    uint32_t sAcc;
} NAV_VELECEF;

typedef struct {  // 0x01 0x12
    uint32_t iTOW;
    int32_t velN;
    int32_t velE;
    int32_t velD;
    uint32_t speed;
    uint32_t gSpeed;
    int32_t heading;
    uint32_t sAcc;
    uint32_t cAcc;
} NAV_VELNED;

#pragma pack(pop)

#endif
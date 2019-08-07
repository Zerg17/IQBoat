#ifndef UBX
#define UBX

#include <stdint.h>

#pragma pack(push, 1)

typedef struct {  // 0x01 0x60
    uint32_t iTOW;
    uint8_t config;
    uint8_t status;
    uint8_t reserved0;
    uint8_t reserved1;
    uint32_t avail;
    uint32_t reserved2;
    uint32_t reserved3;
} NAV_AOPSTATUS;

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
    uint16_t reserved1;
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

typedef struct {  // 0x01 0x40
    int32_t pulses;
    int32_t period;
    uint32_t gyroMean;
    int16_t temperature;
    int8_t direction;
    uint8_t calibStatus;
    int32_t pulseScale;
    int32_t gyroBias;
    int32_t gyroScale;
    int16_t accPulseScale;
    int16_t accGyroBias;
    int16_t accGyroScale;
    uint8_t measUsed;
    uint8_t resrved2;
} NAV_EKFSTATUS;

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

typedef struct {  // 0x01 0x32
    uint32_t iTOW;
    uint8_t geo;
    uint8_t mode;
    int8_t sys;
    uint8_t service;
    uint8_t cnt;
    uint8_t reserved0[3];
    struct {
        uint8_t svid;
        uint8_t flags;
        uint8_t udre;
        uint8_t svSys;
        uint8_t svService;
        uint8_t reserved1;
        int16_t prc;
        uint16_t reserved2;
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
    uint32_t reserved2;
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
    uint16_t reserved2;
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

typedef struct {  // 0x01 0x20
    uint32_t iTOW;
    int32_t fTOW;
    int16_t week;
    int8_t leapS;
    uint8_t valid;
    uint32_t tAcc;
} NAV_TIMEGPS;

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
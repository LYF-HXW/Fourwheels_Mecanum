#ifndef __MAIN_H__
#define __MAIN_H__

#include "stm32f10x.h"
#include "delay.h"
#include "rs485.h"

#define abs(x) ((x)>0? (x):(-(x)))

#define DRV_ALL_RESET_ID                              0x00
#define DRV_ALL_MODE_CHOICE_ID                        0x01
#define DRV_ALL_PWM_MODE_ID                           0x02
#define DRV_ALL_PWM_CURRENT_MODE_ID                   0x03
#define DRV_ALL_PWM_VELOCITY_MODE_ID                  0x04
#define DRV_ALL_PWM_POSITION_MODE_ID                  0x05
#define DRV_ALL_PWM_VELOCITY_POSITION_MODE_ID         0x06
#define DRV_ALL_CURRENT_VELOCITY_MODE_ID              0x07
#define DRV_ALL_CURRENT_POSITION_MODE_ID              0x08
#define DRV_ALL_CURRENT_VELOCITY_POSITION_MODE_ID     0x09
#define DRV_ALL_CONFIG_ID                             0x0a
#define DRV_ALL_RETURN_ID                             0x0b

#define DRV01_RESET_ID                                0x10
#define DRV01_MODE_CHOICE_ID                          0x11
#define DRV01_PWM_MODE_ID                             0x12
#define DRV01_PWM_CURRENT_MODE_ID                     0x13
#define DRV01_PWM_VELOCITY_MODE_ID                    0x14
#define DRV01_PWM_POSITION_MODE_ID                    0x15
#define DRV01_PWM_VELOCITY_POSITION_MODE_ID           0x16
#define DRV01_CURRENT_VELOCITY_MODE_ID                0x17
#define DRV01_CURRENT_POSITION_MODE_ID                0x18
#define DRV01_CURRENT_VELOCITY_POSITION_MODE_ID       0x19
#define DRV01_CONFIG_ID                               0x1a
#define DRV01_RETURN_ID                               0x1b

#define DRV02_RESET_ID                                0x20
#define DRV02_MODE_CHOICE_ID                          0x21
#define DRV02_PWM_MODE_ID                             0x22
#define DRV02_PWM_CURRENT_MODE_ID                     0x23
#define DRV02_PWM_VELOCITY_MODE_ID                    0x24
#define DRV02_PWM_POSITION_MODE_ID                    0x25
#define DRV02_PWM_VELOCITY_POSITION_MODE_ID           0x26
#define DRV02_CURRENT_VELOCITY_MODE_ID                0x27
#define DRV02_CURRENT_POSITION_MODE_ID                0x28
#define DRV02_CURRENT_VELOCITY_POSITION_MODE_ID       0x29
#define DRV02_CONFIG_ID                               0x2a
#define DRV02_RETURN_ID                               0x2b

#define DRV03_RESET_ID                                0x30
#define DRV03_MODE_CHOICE_ID                          0x31
#define DRV03_PWM_MODE_ID                             0x32
#define DRV03_PWM_CURRENT_MODE_ID                     0x33
#define DRV03_PWM_VELOCITY_MODE_ID                    0x34
#define DRV03_PWM_POSITION_MODE_ID                    0x35
#define DRV03_PWM_VELOCITY_POSITION_MODE_ID           0x36
#define DRV03_CURRENT_VELOCITY_MODE_ID                0x37
#define DRV03_CURRENT_POSITION_MODE_ID                0x38
#define DRV03_CURRENT_VELOCITY_POSITION_MODE_ID       0x39
#define DRV03_CONFIG_ID                               0x3a
#define DRV03_RETURN_ID                               0x3b

#define DRV04_RESET_ID                                0x40
#define DRV04_MODE_CHOICE_ID                          0x41
#define DRV04_PWM_MODE_ID                             0x42
#define DRV04_PWM_CURRENT_MODE_ID                     0x43
#define DRV04_PWM_VELOCITY_MODE_ID                    0x44
#define DRV04_PWM_POSITION_MODE_ID                    0x45
#define DRV04_PWM_VELOCITY_POSITION_MODE_ID           0x46
#define DRV04_CURRENT_VELOCITY_MODE_ID                0x47
#define DRV04_CURRENT_POSITION_MODE_ID                0x48
#define DRV04_CURRENT_VELOCITY_POSITION_MODE_ID       0x49
#define DRV04_CONFIG_ID                               0x4a
#define DRV04_RETURN_ID                               0x4b

#define DRV05_RESET_ID                                0x50
#define DRV05_MODE_CHOICE_ID                          0x51
#define DRV05_PWM_MODE_ID                             0x52
#define DRV05_PWM_CURRENT_MODE_ID                     0x53
#define DRV05_PWM_VELOCITY_MODE_ID                    0x54
#define DRV05_PWM_POSITION_MODE_ID                    0x55
#define DRV05_PWM_VELOCITY_POSITION_MODE_ID           0x56
#define DRV05_CURRENT_VELOCITY_MODE_ID                0x57
#define DRV05_CURRENT_POSITION_MODE_ID                0x58
#define DRV05_CURRENT_VELOCITY_POSITION_MODE_ID       0x59
#define DRV05_CONFIG_ID                               0x5a
#define DRV05_RETURN_ID                               0x5b

#define DRV06_RESET_ID                                0x60
#define DRV06_MODE_CHOICE_ID                          0x61
#define DRV06_PWM_MODE_ID                             0x62
#define DRV06_PWM_CURRENT_MODE_ID                     0x63
#define DRV06_PWM_VELOCITY_MODE_ID                    0x64
#define DRV06_PWM_POSITION_MODE_ID                    0x65
#define DRV06_PWM_VELOCITY_POSITION_MODE_ID           0x66
#define DRV06_CURRENT_VELOCITY_MODE_ID                0x67
#define DRV06_CURRENT_POSITION_MODE_ID                0x68
#define DRV06_CURRENT_VELOCITY_POSITION_MODE_ID       0x69
#define DRV06_CONFIG_ID                               0x6a
#define DRV06_RETURN_ID                               0x6b

#define DRV07_RESET_ID                                0x70
#define DRV07_MODE_CHOICE_ID                          0x71
#define DRV07_PWM_MODE_ID                             0x72
#define DRV07_PWM_CURRENT_MODE_ID                     0x73
#define DRV07_PWM_VELOCITY_MODE_ID                    0x74
#define DRV07_PWM_POSITION_MODE_ID                    0x75
#define DRV07_PWM_VELOCITY_POSITION_MODE_ID           0x76
#define DRV07_CURRENT_VELOCITY_MODE_ID                0x77
#define DRV07_CURRENT_POSITION_MODE_ID                0x78
#define DRV07_CURRENT_VELOCITY_POSITION_MODE_ID       0x79
#define DRV07_CONFIG_ID                               0x7a
#define DRV07_RETURN_ID                               0x7b

#define DRV08_RESET_ID                                0x80
#define DRV08_MODE_CHOICE_ID                          0x81
#define DRV08_PWM_MODE_ID                             0x82
#define DRV08_PWM_CURRENT_MODE_ID                     0x83
#define DRV08_PWM_VELOCITY_MODE_ID                    0x84
#define DRV08_PWM_POSITION_MODE_ID                    0x85
#define DRV08_PWM_VELOCITY_POSITION_MODE_ID           0x86
#define DRV08_CURRENT_VELOCITY_MODE_ID                0x87
#define DRV08_CURRENT_POSITION_MODE_ID                0x88
#define DRV08_CURRENT_VELOCITY_POSITION_MODE_ID       0x89
#define DRV08_CONFIG_ID                               0x8a
#define DRV08_RETURN_ID                               0x8b

#define DRV09_RESET_ID                                0x90
#define DRV09_MODE_CHOICE_ID                          0x91
#define DRV09_PWM_MODE_ID                             0x92
#define DRV09_PWM_CURRENT_MODE_ID                     0x93
#define DRV09_PWM_VELOCITY_MODE_ID                    0x94
#define DRV09_PWM_POSITION_MODE_ID                    0x95
#define DRV09_PWM_VELOCITY_POSITION_MODE_ID           0x96
#define DRV09_CURRENT_VELOCITY_MODE_ID                0x97
#define DRV09_CURRENT_POSITION_MODE_ID                0x98
#define DRV09_CURRENT_VELOCITY_POSITION_MODE_ID       0x99
#define DRV09_CONFIG_ID                               0x9a
#define DRV09_RETURN_ID                               0x9b

#define DRV10_RESET_ID                                0xa0
#define DRV10_MODE_CHOICE_ID                          0xa1
#define DRV10_PWM_MODE_ID                             0xa2
#define DRV10_PWM_CURRENT_MODE_ID                     0xa3
#define DRV10_PWM_VELOCITY_MODE_ID                    0xa4
#define DRV10_PWM_POSITION_MODE_ID                    0xa5
#define DRV10_PWM_VELOCITY_POSITION_MODE_ID           0xa6
#define DRV10_CURRENT_VELOCITY_MODE_ID                0xa7
#define DRV10_CURRENT_POSITION_MODE_ID                0xa8
#define DRV10_CURRENT_VELOCITY_POSITION_MODE_ID       0xa9
#define DRV10_CONFIG_ID                               0xaa
#define DRV10_RETURN_ID                               0xab

#define DRV11_RESET_ID                                0xa0
#define DRV11_MODE_CHOICE_ID                          0xa1
#define DRV11_PWM_MODE_ID                             0xa2
#define DRV11_PWM_CURRENT_MODE_ID                     0xa3
#define DRV11_PWM_VELOCITY_MODE_ID                    0xa4
#define DRV11_PWM_POSITION_MODE_ID                    0xa5
#define DRV11_PWM_VELOCITY_POSITION_MODE_ID           0xa6
#define DRV11_CURRENT_VELOCITY_MODE_ID                0xa7
#define DRV11_CURRENT_POSITION_MODE_ID                0xa8
#define DRV11_CURRENT_VELOCITY_POSITION_MODE_ID       0xa9
#define DRV11_CONFIG_ID                               0xaa
#define DRV11_RETURN_ID                               0xab

#define DRV12_RESET_ID                                0xa0
#define DRV12_MODE_CHOICE_ID                          0xa1
#define DRV12_PWM_MODE_ID                             0xa2
#define DRV12_PWM_CURRENT_MODE_ID                     0xa3
#define DRV12_PWM_VELOCITY_MODE_ID                    0xa4
#define DRV12_PWM_POSITION_MODE_ID                    0xa5
#define DRV12_PWM_VELOCITY_POSITION_MODE_ID           0xa6
#define DRV12_CURRENT_VELOCITY_MODE_ID                0xa7
#define DRV12_CURRENT_POSITION_MODE_ID                0xa8
#define DRV12_CURRENT_VELOCITY_POSITION_MODE_ID       0xa9
#define DRV12_CONFIG_ID                               0xaa
#define DRV12_RETURN_ID                               0xab

#define DRV13_RESET_ID                                0xa0
#define DRV13_MODE_CHOICE_ID                          0xa1
#define DRV13_PWM_MODE_ID                             0xa2
#define DRV13_PWM_CURRENT_MODE_ID                     0xa3
#define DRV13_PWM_VELOCITY_MODE_ID                    0xa4
#define DRV13_PWM_POSITION_MODE_ID                    0xa5
#define DRV13_PWM_VELOCITY_POSITION_MODE_ID           0xa6
#define DRV13_CURRENT_VELOCITY_MODE_ID                0xa7
#define DRV13_CURRENT_POSITION_MODE_ID                0xa8
#define DRV13_CURRENT_VELOCITY_POSITION_MODE_ID       0xa9
#define DRV13_CONFIG_ID                               0xaa
#define DRV13_RETURN_ID                               0xab

#define DRV14_RESET_ID                                0xa0
#define DRV14_MODE_CHOICE_ID                          0xa1
#define DRV14_PWM_MODE_ID                             0xa2
#define DRV14_PWM_CURRENT_MODE_ID                     0xa3
#define DRV14_PWM_VELOCITY_MODE_ID                    0xa4
#define DRV14_PWM_POSITION_MODE_ID                    0xa5
#define DRV14_PWM_VELOCITY_POSITION_MODE_ID           0xa6
#define DRV14_CURRENT_VELOCITY_MODE_ID                0xa7
#define DRV14_CURRENT_POSITION_MODE_ID                0xa8
#define DRV14_CURRENT_VELOCITY_POSITION_MODE_ID       0xa9
#define DRV14_CONFIG_ID                               0xaa
#define DRV14_RETURN_ID                               0xab

#define DRV15_RESET_ID                                0xa0
#define DRV15_MODE_CHOICE_ID                          0xa1
#define DRV15_PWM_MODE_ID                             0xa2
#define DRV15_PWM_CURRENT_MODE_ID                     0xa3
#define DRV15_PWM_VELOCITY_MODE_ID                    0xa4
#define DRV15_PWM_POSITION_MODE_ID                    0xa5
#define DRV15_PWM_VELOCITY_POSITION_MODE_ID           0xa6
#define DRV15_CURRENT_VELOCITY_MODE_ID                0xa7
#define DRV15_CURRENT_POSITION_MODE_ID                0xa8
#define DRV15_CURRENT_VELOCITY_POSITION_MODE_ID       0xa9
#define DRV15_CONFIG_ID                               0xaa
#define DRV15_RETURN_ID                               0xab

#define ENTER_PWM_MODE                                0x01
#define ENTER_PWM_CURRENT_MODE                        0x02
#define ENTER_PWM_VELOCITY_MODE                       0x03
#define ENTER_PWM_POSITION_MODE                       0x04
#define ENTER_PWM_VELOCITY_POSITION_MODE              0x05
#define ENTER_CURRENT_VELOCITY_MODE                   0x06
#define ENTER_CURRENT_POSITION_MODE                   0x07
#define ENTER_CURRENT_VELOCITY_POSITION_MODE          0x08

#endif

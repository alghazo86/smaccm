/* This file has been autogenerated by Ivory
 * Compiler version  0.1.0.3
 */
#ifndef __CANDRIVERTYPES_H__
#define __CANDRIVERTYPES_H__
#ifdef __cplusplus
extern "C" {
#endif
#include "ivory.h"
typedef struct can_message { uint32_t can_message_id;
                             int32_t can_message_len;
                             uint8_t can_message_buf[8U];
} can_message;

#ifdef __cplusplus
}
#endif
#endif /* __CANDRIVERTYPES_H__ */
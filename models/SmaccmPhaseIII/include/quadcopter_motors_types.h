/* This file has been autogenerated by Ivory
 * Compiler version  0.1.0.2
 */
#ifndef __QUADCOPTER_MOTORS_TYPES_H__
#define __QUADCOPTER_MOTORS_TYPES_H__
#ifdef __cplusplus
extern "C" {
#endif
#include "ivory.h"
#include "ivory_serialize.h"
typedef struct quadcopter_motors { float frontleft;
                                   float frontright;
                                   float backleft;
                                   float backright;
} quadcopter_motors;
void quadcopter_motors_get_le (const uint8_t * n_var0, uint32_t n_var1, struct quadcopter_motors * n_var2);
void quadcopter_motors_get_be (const uint8_t * n_var0, uint32_t n_var1, struct quadcopter_motors * n_var2);
void quadcopter_motors_set_le (uint8_t * n_var0, uint32_t n_var1, const struct quadcopter_motors * n_var2);
void quadcopter_motors_set_be (uint8_t * n_var0, uint32_t n_var1, const struct quadcopter_motors * n_var2);

#ifdef __cplusplus
}
#endif
#endif /* __QUADCOPTER_MOTORS_TYPES_H__ */
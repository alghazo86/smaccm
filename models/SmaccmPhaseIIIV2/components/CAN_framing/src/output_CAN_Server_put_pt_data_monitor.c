/* This file has been autogenerated by Ivory
 * Compiler version  0.1.0.3
 */
#include "output_CAN_Server_put_pt_data_monitor.h"
#include "smaccm_CAN_framing.h"

void callback_output_CAN_Server_put_pt_data_2(const uint8_t n_var0[80U])
{
    //CAN_Server_put_pt_data(n_var0);
    CAN_framing_write_to_server(n_var0);
}
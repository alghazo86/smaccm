/* This file has been autogenerated by Ivory
 * Compiler version  0.1.0.3
 */
#include "output_Server_CAN_put_pt_data_monitor.h"

void callback_output_Server_CAN_put_pt_data_2(const uint8_t n_var0[80U])
{
    //Server_CAN_put_pt_data(n_var0);
    Server_write_send_can(n_var0);
}

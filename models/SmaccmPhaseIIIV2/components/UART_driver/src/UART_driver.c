/*
 * Copyright 2014, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

#include <stdio.h>

#include <platsupport/chardev.h>
#include <platsupport/serial.h>
#include <utils/util.h>
#include <smaccm_UART_driver.h>
#include <UART_driver.h>

//#define BAUD_RATE 115200
#define BAUD_RATE 57600

#ifdef CONFIG_PLAT_EXYNOS5410
#define DEV_ID  PS_SERIAL1
#elif CONFIG_PLAT_IMX31
#define DEV_ID  IMX31_UART1
#else
#error
#endif

struct uart_token {
    size_t cur_bytes;
    size_t req_bytes;
    char* buf;
};

static ps_chardevice_t serial_device;

static void
interrupt_event(void* token)
{
    ps_chardevice_t* device;
    device = (ps_chardevice_t*)token;
    ps_cdev_handle_irq(device, 0);
    interrupt_reg_callback(&interrupt_event, token);
}

void pre_init(void)
{
    /* Iniitialise the UART */
    printf("Initialising UART driver\n");
    if(exynos_serial_init(DEV_ID, (void *) vaddr, NULL, NULL, &serial_device)){
        printf("Failed to initialise UART\n");
        while(1);
    }
    serial_configure(&serial_device, BAUD_RATE, 8, PARITY_NONE, 1);
    serial_device.flags &= ~SERIAL_AUTO_CR;

    /* Prime semaphore */
    read_sem_wait();

    /* Register for IRQs */
    interrupt_reg_callback(&interrupt_event, &serial_device);
}

static void
read_callback(ps_chardevice_t* device, enum chardev_status stat,
              size_t bytes_transfered, void* token){
    struct uart_token* t;
    t = (struct uart_token*)token;
    /* We might get a short read due to a timeout. */
    t->cur_bytes += bytes_transfered;
    t->buf += bytes_transfered;
    read_sem_post();
}

int uart_read(char *c, int rsize)
{
    struct uart_token token;

    token.cur_bytes = 0;
    token.req_bytes = rsize;
    token.buf = c;
    if(ps_cdev_read(&serial_device, token.buf, token.req_bytes, &read_callback, &token) < 0){
        printf("Error reading from UART\n");
        return -1;
    }
    read_sem_wait();

    return token.cur_bytes;
}

static void
write_callback(ps_chardevice_t* device, enum chardev_status stat,
               size_t bytes_transfered, void* token) {
    struct uart_token* t;
    const bool b;
    t = (struct uart_token*) token;
    t->cur_bytes += bytes_transfered;
    if (t->cur_bytes == t->req_bytes) {
      //uart_Output_recv_resp_0_write_bool(&b);
      UART_driver_recv_resp_write_bool(&b);
    }
}

bool get_packet_write_SMACCM_DATA__UartPacket_i(const SMACCM_DATA__UartPacket_i *packet) {
    struct uart_token token;

    token.cur_bytes = 0;
    token.req_bytes = packet->len;
    token.buf = (char*) packet->buff;
    if (ps_cdev_write(&serial_device, token.buf, token.req_bytes, &write_callback, &token) < 0) {
        printf("Error writing to UART\n");
        return false;
    }

    return true;
}

int run(void)
{
	struct SMACCM_DATA__UartPacket_i p;

	while (1) {
		int r = uart_read((char*) p.buff, 255);
		p.len = r;
		UART_driver_send_packet_write_SMACCM_DATA__UartPacket_i(&p);
	}
	return 0;
}

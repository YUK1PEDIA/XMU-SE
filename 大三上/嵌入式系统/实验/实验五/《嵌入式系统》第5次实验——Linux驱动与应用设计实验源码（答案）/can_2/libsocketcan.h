#ifndef _socketcan_netlink_h
#define _socketcan_netlink_h
#include "can_netlink.h"

#ifdef __cplusplus
extern "C" {
#endif

int can_do_restart(const char *name);
int can_do_stop(const char *name);
int can_do_start(const char *name);

int can_set_restart_ms(const char *name, __u32 restart_ms);
int can_set_bittiming(const char *name, struct can_bittiming *bt);
int can_set_ctrlmode(const char *name, struct can_ctrlmode *cm);
int can_set_bitrate(const char *name, __u32 bitrate);
int can_set_bitrate_samplepoint(const char *name, __u32 bitrate, __u32 sample_point);

int can_get_restart_ms(const char *name, __u32 *restart_ms);
int can_get_bittiming(const char *name, struct can_bittiming *bt);
int can_get_ctrlmode(const char *name, struct can_ctrlmode *cm);
int can_get_state(const char *name, int *state);
int can_get_clock(const char *name, struct can_clock *clock);
int can_get_bittiming_const(const char *name, struct can_bittiming_const *btc);
int can_get_berr_counter(const char *name, struct can_berr_counter *bc);
int can_get_device_stats(const char *name, struct can_device_stats *cds);

#ifdef __cplusplus
}
#endif

#endif

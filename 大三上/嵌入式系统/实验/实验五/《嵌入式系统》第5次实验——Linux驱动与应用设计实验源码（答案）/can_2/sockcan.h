#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/uio.h>
#include <net/if.h>
#include <linux/can.h>
#include <linux/socket.h>
#include <linux/can/raw.h>
#include "libsocketcan.h"
#include "can_config.h"

#define PF_CAN  29
#define AF_CAN  PF_CAN

int can_open(const char *name, unsigned int bitrate, struct can_filter *filter, unsigned int filter_num)
{
	int ret;
	struct can_bittiming bt;
	int socket_fd;
	int family = PF_CAN, type = SOCK_RAW, proto = CAN_RAW;
	struct sockaddr_can addr;
	struct ifreq ifr;
	memset(&bt, 0, sizeof(bt));
	bt.bitrate = bitrate;
	ret = can_do_stop(name);
	if (ret < 0) {
		fprintf(stderr, "failed to stop  %s\n", name);
		return ret;
	}
	ret = can_set_bittiming(name, &bt);
	if (ret < 0) {
		fprintf(stderr, "failed to set bitrate of %s to %u\n", name, bitrate);
		return ret;
	}	
	memset(&bt, 0, sizeof(bt));
	ret = can_get_bittiming(name, &bt);
	if (ret < 0) {
		fprintf(stderr, "failed to get bitrate of %s\n", name);
		return ret;
	}
	fprintf(stdout, "%s bitrate: %u, sample-point: %0.3f\n",
			name, bt.bitrate, (float)((float)bt.sample_point / 1000));
	ret = can_do_start(name);
	if (ret < 0) {
		fprintf(stderr, "failed to start %s\n", name);
		return ret;
	}
	socket_fd = socket(family, type, proto);
	if (socket_fd < 0) {
		perror("socket");
		return socket_fd;
	}
	addr.can_family =  family;
	strncpy(ifr.ifr_name, name, sizeof(ifr.ifr_name));
	ret = ioctl(socket_fd, SIOCGIFINDEX, &ifr);
	if (ret < 0) {
		perror("ioctl");
		close(socket_fd);
		return ret;
	}
	addr.can_ifindex = ifr.ifr_ifindex;
	ret = bind(socket_fd, (struct sockaddr *)&addr, sizeof(addr));
	if (ret < 0) {
		perror("bind");
		close(socket_fd);
		return ret;
	}
	if ((filter_num > 0) && (filter != NULL)) {
		ret = setsockopt(socket_fd, SOL_CAN_RAW, CAN_RAW_FILTER, filter, 
				filter_num * sizeof(struct can_filter));
		if (ret != 0) {
			perror("setsockopt");
			close(socket_fd);
			return ret;
		}
	}
	return socket_fd;
}

void can_close(const char *name, int fd)
{
	int ret;
	close(fd);
	ret = can_do_stop(name);
	if (ret < 0)
		fprintf(stderr, "failed to stop  %s\n", name);
}

int can_read(int fd, unsigned int *canid, unsigned char *data, int *extended)
{
	int nbyte = 0;
	struct can_frame frame;
	memset(&frame, 0, sizeof(struct can_frame));
	nbyte = read(fd, &frame, sizeof(struct can_frame));
	if (nbyte < 0) {
		perror("read");
		return nbyte;
	}
	if (frame.can_id & CAN_EFF_FLAG) { 
		*canid = frame.can_id & CAN_EFF_MASK;
		*extended = 1;
	} else {
		*canid = frame.can_id & CAN_SFF_MASK;
		*extended = 0;
	}
	for(nbyte = 0; nbyte < frame.can_dlc; nbyte ++) 
	{
		data[nbyte] = frame.data[nbyte];
	}
	return frame.can_dlc;
}

int can_write(int fd, unsigned int canid, unsigned char *data, unsigned int len, int extended)
{
	struct can_frame frame;
	int nbyte = 0;
	int i = 0;
	memset(&frame, 0, sizeof(struct can_frame));
	if (len < 0 || len > 8) {
		fprintf(stderr, "invalid argument\n");	
		return -1;
	}
	if (data == NULL) { 
		fprintf(stderr, "invalid argument\n");	
		return -1;
	}
	frame.can_id = canid;
	for(i = 0; i < len; i++)
	{
		frame.data[i] = data[i];
		if (i == 8)
			break;
	}
	frame.can_dlc = i;
	if (extended) {
		frame.can_id &= CAN_EFF_MASK;
		frame.can_id |= CAN_EFF_FLAG;
	} else {
		frame.can_id &= CAN_SFF_MASK;
	}
	nbyte = write(fd, &frame, sizeof(frame));
	if (nbyte < 0) {
		perror("write");	
	}
	return i;
}

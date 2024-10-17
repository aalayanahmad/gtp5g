#ifndef __ENCAP_H__
#define __ENCAP_H__

#include <linux/socket.h>

#include "dev.h"
#include "pktinfo.h"

#define PKT_TO_APP 1
#define PKT_FORWARDED 0
#define PKT_DROPPED -1

enum gtp5g_msg_type_attrs {
    GTP5G_BUFFER = 1,
    GTP5G_REPORT,

    __GTP5G_MSG_TYPE_ATTR_MAX,
};
#define GTP5G_MSG_TYPE_ATTR_MAX (__GTP5G_MSG_TYPE_ATTR_MAX - 1);

enum gtp5g_buffer_attrs {
    /* gtp5g_device_attrs in this part */

    GTP5G_BUFFER_PAD = 3,
    GTP5G_BUFFER_PACKET,
    GTP5G_BUFFER_ID,
    GTP5G_BUFFER_SEID,
    GTP5G_BUFFER_ACTION,

    /* Add newly supported feature ON ABOVE
     * for compatability with older version of
     * free5GC's UPF or libgtp5gnl
     * */

    __GTP5G_BUFFER_ATTR_MAX,
};
#define GTP5G_BUFFER_ATTR_MAX (__GTP5G_BUFFER_ATTR_MAX - 1)

int find_key(ArrivalTime* arrival_times, int count, const char* ip);
void add_or_update_key(ArrivalTime* arrival_times, int* count, const char* ip);
void free_memory(ArrivalTime* arrival_times, int count);
union Value lookup_uplink_value(const char* dst_ip, enum ValueType type);
extern struct sock *gtp5g_encap_enable(int, int, struct gtp5g_dev *);
extern void gtp5g_encap_disable(struct sock *);
extern int gtp5g_handle_skb_ipv4(struct sk_buff *, struct net_device *,
        struct gtp5g_pktinfo *);
int gtp5g_monitoring_init(void);
void gtp5g_monitoring_exit(void);
void send_monitoring_data_to_userspace(struct monitoring_data *data);
void convert_ip_to_string(__be32 ip, char *ip_str);
bool to_be_monitored(const char *src_ip, const char *dst_ip);
#endif // __ENCAP_H__

#include "ft_traceroute.h"

double  send_packet(int socketfd, uint32_t binip, int ttl)
{
	struct sockaddr_in  dest_addr;
    double              start_time;


	ft_bzero(&dest_addr, sizeof(struct sockaddr_in));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = 0;
    dest_addr.sin_addr.s_addr = binip;
	if (setsockopt(socketfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) < 0)
		ft_exit(RED, "Error generating packet!", 1, socketfd);
    start_time = get_time_ms();
	if (sendto(socketfd, NULL, 0, 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) <= 0)
        ft_exit(RED, "Error sending packet!", 1, socketfd);
    return (start_time);
}



t_request_result receive_packet(int socketfd, double start_time)
{
    struct sockaddr_in  src_addr;
    socklen_t           addr_len = sizeof(src_addr);
    struct ip           *ip_header;
    struct icmp         *icmp_header;
    char                buffer[512];
    struct timeval      timeout;
    t_request_result    result;

    timeout.tv_sec = 3;
    timeout.tv_usec = 0;
    ft_bzero(&src_addr, sizeof(src_addr));
    ft_bzero(buffer, sizeof(buffer));
    ft_bzero(&result, sizeof(result));
    if (setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0)
        ft_exit(RED, "Error setting socket timeout", 1, socketfd);
    else if (recvfrom(socketfd, &buffer, sizeof(buffer), 0, (struct sockaddr *)&src_addr, &addr_len) <= 0)
        return (result);
    result.time_ms = get_time_ms() - start_time;
    result.result = 1;
    ip_header = (struct ip *)buffer;
    icmp_header = struct( icmp *)(buffer + ip_header->ip_hl * 4);
    result.icmp_type = icmp_header->icmp_type;
    result.icmp_code = icmp_header->icmp_code;
    result.binip = ip_header->ip_src;
    return (result);
}

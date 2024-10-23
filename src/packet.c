
#include "ft_traceroute.h"

void send_packet(int socketfd, uint32_t binip, int ttl)
{
	struct sockaddr_in  dest_addr;
    double              buffer;

	ft_bzero(&dest_addr, sizeof(struct sockaddr_in));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = 0;
    dest_addr.sin_addr.s_addr = binip;
	if (setsockopt(socketfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) < 0)
		ft_exit(RED, "Error generating packet!", 1, socketfd);
    buffer = get_time_ms();
	if (sendto(socketfd, &buffer, sizeof(buffer), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) <= 0)
        ft_exit(RED, "Error sending packet!", 1, socketfd);
}



t_request_result receive_packet(int socketfd)
{
    struct sockaddr_in src_addr;
    socklen_t addr_len = sizeof(src_addr);
    double buffer;
    char ip_str[INET_ADDRSTRLEN];
    struct timeval timeout;
    t_request_result    result;

    timeout.tv_sec = 3;  // 3 secondes
    timeout.tv_usec = 0; // 0 microsecondes
    ft_bzero(&src_addr, sizeof(src_addr));
    if (setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0)
        ft_exit(RED, "Error setting socket timeout", 1, socketfd);
    else if (recvfrom(socketfd, &buffer, sizeof(buffer), 0, (struct sockaddr *)&src_addr, &addr_len) <= 0)
        ft_exit(RED, "Error reading packet!", 1, socketfd);
    result.time_ms = get_time_ms() - buffer;
    inet_ntop(AF_INET, &(src_addr.sin_addr), result.ip, INET_ADDRSTRLEN);
    return (result);
}


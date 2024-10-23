
#include "ft_traceroute.h"



static void	ft_traceroute_loop(int socketfd, t_argv arg)
{
	t_request_result	result;
	t_request_result	result2;

	result.icmp_type = 11;
	while (result.icmp_type == 11)
	{
		result->time_ms = send_packet(socketfd, arg.binip, arg.first_ttl);
		result = recieve_packet(socketfd, result->time_ms);
		ft_print_result(1, result, NULL, arg.first_ttl);
		result2 = result;
		result->time_ms = send_packet(socketfd, arg.binip, arg.first_ttl);
		result = recieve_packet(socketfd, result->time_ms);
		ft_print_result(2, result, &result2, arg.first_ttl);
		result2 = result;
		result->time_ms = send_packet(socketfd, arg.binip, arg.first_ttl);
		result = recieve_packet(socketfd, result->time_ms);
		ft_print_result(3, result, &result2, arg.first_ttl);
	}
}


void	ft_traceroute(t_argv arg)
{
	int					socketfd;
	struct sockaddr_in	addr;

	ft_bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(0);

	if ((socketfd = socket(AF_INET, SOCK_DGRAM, 0) <= 0))
		ft_exit(RED, "Error opening socket fd!", 1, 0);
    if (bind(socketfd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
		ft_exit(RED, "Error setting up bind!", 1, socketfd);
	ft_traceroute_loop(socketfd, arg);
    close(socketfd);
}



#include "ft_traceroute.h"

void	ft_exit(char *color, char *str, int icode, int sockfd)
{
	int	fd = 1;

	if (sockfd)
	close(sockfd);
	if (icode != 0)
		fd = 0;
	ft_putstr_fd(color, fd);
	ft_putstr_fd(str, fd);
	ft_putstr_fd(RESETN, fd);
	exit(icode);
}


double	get_time_ms(void)
{
	struct timeval		time;
	unsigned long long	ltime;

	gettimeofday(&time, NULL);
	ltime = time.tv_sec * 1000000 + time.tv_usec;
	return (ltime / 1000.0);
}
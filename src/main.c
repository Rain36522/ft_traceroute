
#include "ft_traceroute.h"

void	ft_help()
{
	printf("Version 1.0\n");
	printf("Usage : traceroute <ip> [-f first_ttl]\n");
	exit(0);
}


int	main(int argc, char **argv)
{
	t_argv	arg;
	if (argc > 4)
		ft_exit(RED, "Wrong amount of arguments", 1, 0);
	if (argc == 2 && !ft_strcmp("--help", argv[1]))
		ft_help();
	arg = parsing(argc, argv);
	return (0);
}
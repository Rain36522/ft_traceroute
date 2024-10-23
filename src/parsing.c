
#include "ft_traceroute.h"

static void	ft_check_ip_char(char *ip)
{
	int	j = 0;
	int	k = 0;
	int	wrong_pos = 0;

	if (ip[0] == '.' || ip[ft_strlen(ip) - 1] =='.')
		wrong_pos = 1;

	for (size_t i = 0; i < ft_strlen(ip) && !wrong_pos; i ++)
	{
		if (ip[i] == '.')
		{
			k ++;
			if (j == 0 || j > 3)
				wrong_pos = 1;
			j = 0;
		}
		else if (!ft_isdigit(ip[i]))
			ft_exit(RED, "Wrong character in ip address!", 1, 0);
		else
			j++;
	}
	if (wrong_pos || j > 3 || k != 3)
		ft_exit(RED, "Wrong quantity or position for \".\"in ip address!", 1, 0);
}

static void	ft_check_ip(char *ip)
{
	char    **a;
	int     ierror;

	ierror = 0;
	if (ft_strlen(ip) < 7 || ft_strlen(ip) > 15)
		ft_exit(RED, "Wrong len for ip address!", 1, 0);

	ft_check_ip_char(ip);

	if (!(a = ft_split(ip, '.')))
		ft_exit(RED, "Error alocating memory", 12, 0);
	for (size_t i = 0; a[i] && !ierror; i ++)
	{
		if ((ft_atoi(a[i])) > 255)
			ierror = 1;
	}
	for (size_t i = 0; a[i]; i ++)
		free(a[i]);
	free(a);
	if (ierror)
		ft_exit(RED, "Ip address as a to big value!", 1, 0);
	printf("%sIp address is valide!%s", GREEN, RESETN);
}

int ft_is_ip(char *ip)
{
	int	j;

	j = 0;
	while (*ip)
	{
		if (!ft_strchr("0123456789.", *ip))
			return (0);
		if (*ip == '.')
			j = 0;
		if (j > 2)
			return (0);
		ip ++;
	}
	return (1);
}

static void	ft_resolve_name_addr(uint32_t *binip, char *name)
{
	struct addrinfo 	hints;
	struct addrinfo		*res;
	struct sockaddr_in	*addr_in;

	ft_bzero(&hints, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_protocol = SOCK_STREAM;

	if (getaddrinfo(name, NULL, &hints, &res))
		ft_exit(RED, "Error while resolving adresse name!", 1, 0);
	if (!res)
		ft_exit(RED, "Unknow argument!", 1, 0);
	addr_in = (struct sockaddr_in *)res->ai_addr;
	*binip = addr_in->sin_addr.s_addr;
	freeaddrinfo(res);
}


t_argv	parsing(int argc, char **argv)
{
	int		flag = 0;
	t_argv	strctargv;

	ft_bzero(&strctargv, sizeof(t_argv));
	for (int i = 1; i < argc; i ++)
	{
		if (!argv[i] || !*argv[i])
			ft_exit(ORANGE, "Unknow argument!", 1, 0);
		else if (!ft_strcmp(argv[i], "-f"))
			flag ++;
		else if (ft_isint(argv[i]) && !strctargv.first_ttl)
			strctargv.first_ttl = ft_atoi(argv[i]);
		else if (!strctargv.binip && ft_is_ip(argv[i]))
		{
			ft_check_ip(argv[i]);
			if (inet_pton(AF_INET, argv[i], &strctargv.binip) <= 0)
				ft_exit(RED, "Error while converting ip in binary!", 1, 0);
			strctargv.str_ip = argv[i];
		}
		else if (!strctargv.binip)
		{
			ft_resolve_name_addr(&strctargv.binip, argv[i]);
			strctargv.str_ip = argv[i];
		}
		else
			ft_exit(RED, "Unknow argument!", 1, 0);
	}
	if (flag && strctargv.first_ttl == -1)
		ft_exit(RED, "Flag -f need to go with an argument!", 1, 0);
	if (flag > 1)
		ft_exit(RED, "Flag -f appear to mutch times!", 1, 0);
	if (!strctargv.str_ip)
		ft_exit(RED, "Adresse is missing!", 1, 0);
	return (strctargv);
}
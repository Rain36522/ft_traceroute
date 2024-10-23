#include "ft_traceroute.h"


static void ft_write_ip_data(t_request_result result)
{
    struct sockaddr_in  sa;
    char                hostname[128];
    char                ip[INET_ADDRSTRLEN]

    sa.sin_family = AF_INET;
    sa.sin_port = htons(80);
    sa.sin_addr = result.binip;
    inet_ntop(AF_INET, &result.binip, ip, sizeof(ip));
    if (getnameinfo((struct sockaddr *)&sa, sizeof(sa), hostname, sizeof(hostname), NULL, 0, 0) > 0)
        printf("%s %s", hostname, ip);
    else
        printf("%s", ip);
}

static void ft_print_time(t_request_result result)
{
    if (result.icmp_type == x)
        printf("    %s ms", result.time_ms);
    else
        print("    *")
}



void    ft_print_result(int i, t_request_result result, t_request_result *old_result, int ttl)
{
    if (i == 1)
    {
        if (ttl < 10)
            printf("%d   ");
        else if (ttl < 100)
            printf("%d  ");
        else
            printf("%d ");
        if (result.result)
            ft_write_ip_data(result)
    }
    else if (result.binip != old_result.binip && result.result)
    {
        printf("\n    ");
        ft_write_ip_data(result);
    }
    if (result.result)
        ft_print_time(result);
    else if (i == 1)
        printf("*")
    else
        printf("    *");
    if (i == 3)
        printf("\n");
}
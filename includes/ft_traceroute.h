/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pudry <pudry@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:35:23 by pudry             #+#    #+#             */
/*   Updated: 2024/10/09 18:35:29 by pudry            ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/ip_icmp.h>
#include <netinet/udp.h>
#include <signal.h>
#include "../libft/includes/libft.h"

#define RESET   " \033[0m"
#define RESETN  "\033[0m\n"
#define RED     "\033[31m"      
#define GREEN   "\033[32m"      
#define YELLOW  "\033[33m"
#define ORANGE  "\033[38;5;208m"      
#define BLUE    "\033[34m"      
#define MAGENTA "\033[35m"      
#define CYAN    "\033[36m"      
#define WHITE   "\033[37m"
#define	HBLUE	"\033[48;5;17m"
#define HRED	"\033[41m"
#define BOLD	"\033[1m"
#define NOBOLD	"\033[0m"
#define DEBUG printf("\033[31m %s, %d, %s", __FILE__, __LINE__, "\033[0m\n");

typedef struct s_argv {
    uint32_t    	binip;
	int				first_ttl;
	char			*str_ip;
} t_argv;

typedef struct s_request_result {
	uint32_t	binip;
	double		time_ms;
	int			icmp_type;
	int			icmp_code;
	int			result;
} t_request_result;

t_argv				parsing(int argc, char **argv);

double 				send_packet(int socketfd, uint32_t binip, int ttl);
t_request_result 	receive_packet(int socketfd);

void				ft_exit(char *color, char *str, int icode, int sockfd);
double				get_time_ms(void);

void				ft_traceroute(t_argv arg);
void				ft_print_result(int i, t_request_result result, t_request_result *old_result, int ttl);
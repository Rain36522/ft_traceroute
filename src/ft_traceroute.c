
#include "ft_traceroute.h"

void	ft_traceroute_loop(int socketfd, t_argv arg)
{
	
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
}


int main() {
    int socketfd;
    struct sockaddr_in addr;

    // Créer une socket
    socketfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketfd < 0) {
        perror("Error creating socket");
        return 1;
    }

    // Initialiser l'adresse de réception
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);  // Écouter sur toutes les interfaces
    addr.sin_port = htons(0);  // Port 0 pour laisser le système assigner un port

    // Lier la socket à l'adresse et au port
    if (bind(socketfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("Error binding socket");
        close(socketfd);
        return 1;
    }

    // Recevoir le paquet
    receive_packet(socketfd);

    // Fermer la socket
    close(socketfd);

    return 0;
}
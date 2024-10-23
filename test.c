#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>

int main() {
    struct sockaddr_in sa;
    char host[128];

    // Exemple d'adresse IP
    sa.sin_family = AF_INET;
    sa.sin_port = htons(80); // Port 80 pour HTTP
    inet_pton(AF_INET, "123.37.48.56", &sa.sin_addr); // Exemple d'adresse IP (ex. example.com)

    // Résolution du nom d'hôte
    int result = getnameinfo((struct sockaddr *)&sa, sizeof(sa),
                              host, sizeof(host),
                              NULL, 0, // Pas besoin de service ici
                              0);
    
    if (result == 0) {
        printf("Nom d'hôte: %s\n", host);
    } else {
        printf("getnameinfo() échoué: %s\n", gai_strerror(result));
    }

    return 0;
}

#include "../include.h"

int aparitii_upd(char *text){

    char udp[4] = "udp";

    int count = 0;
    while(strstr(text,udp)!= NULL){
        count++;
        text = strstr(text,udp) +3;
    }
    return count;
}

void eliminate_numbers(char *text){

    char dest[100];
    int i = 0;
    int ind = 0;
    while(i< strlen(text))
    {
        if (text[i]<'0' || text[i] > '9') 
        { 
            dest[ind] = text[i];
            ind++;
        }
        
        i++;
    }
    dest[ind]= '\0';
    strcpy(text, dest);
}

void client_process(){

    struct sockaddr_in server;
    
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(PORT);
    
    GSocket *sock = g_socket_new(G_SOCKET_FAMILY_IPV4,
                            G_SOCKET_TYPE_STREAM,
                            G_SOCKET_PROTOCOL_TCP,
                            0);

    
    GSocketAddress *sock_address = g_socket_address_new_from_native(&server, sizeof(server));

    g_socket_connect(sock,sock_address, 0, 0);

    char some_text[100] = "So5me udp3udp 4te7xt\n";  
    g_socket_send(sock, some_text, 100, 0, 0);
    
    int nr;
    g_socket_receive(sock, (gchar*) &nr,sizeof(int),0, 0);

    g_socket_receive(sock,some_text,100,0, 0);

    printf("Numar aparitii: %d\n", nr);
    printf("String-ul fara numere: %s\n", some_text);


}

void server_process(){
    
    struct sockaddr_in server;
    
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);
    
    GSocket *sock = g_socket_new(G_SOCKET_FAMILY_IPV4,
                            G_SOCKET_TYPE_STREAM,
                            G_SOCKET_PROTOCOL_TCP,
                            0);
    
    GSocketAddress *sock_address = g_socket_address_new_from_native(&server, sizeof(server));

    g_socket_bind(sock, sock_address,0,0);

    g_socket_listen(sock, 0);

    /* g_socket_accept (
    GSocket* socket,
    GCancellable* cancellable,
    GError** error) */

    GSocket* client = g_socket_accept(sock,0, 0);

    printf("Client connected\n");

    //char *text = calloc(1,100*sizeof(char));
    char text[100];

    //g_socket_receive (GSocket* socket,gchar* buffer,gsize size,GCancellable* cancellable,GError** error)

    g_socket_receive(client, text, 100, 0,0);

    int nr = aparitii_upd(text);
    g_socket_send(client, (gchar*)&nr, 4, 0, 0);
    
    eliminate_numbers(text);  

    g_socket_send(client, text, 100, 0, 0);   
    g_socket_close(client,0);
    
}

int main(){



    if(fork() == 0){
        
         
        //child - server process
        //In the child process make a function that eliminates all the numbers 
        //in a string received over the ipc and returns the new string back to the client process.

        
        server_process();
        

    }
    else{

        //parent - client process
        client_process();
    }
    
    return 0;
}
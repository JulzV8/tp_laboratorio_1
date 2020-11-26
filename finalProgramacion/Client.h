#ifndef CLIENT_H_
#define CLIENT_H_
typedef struct
{
    int id;
    char nombre[128];
    char apellido[128];
    char cuit[12];
}Client;

Client* client_new();
Client* client_newParametros(int id, char* nombre, char* apellido, char* cuit);
void client_delete(Client* this);

int client_setId(Client* this,int id);
int client_setNombre(Client* this,char* nombre);
int client_setApellido(Client* this,char* apellido);
int client_setCuit(Client* this,char* cuit);

int client_getId(Client* this,int* id);
int client_getNombre(Client* this,char* nombre);
int client_getApellido(Client* this,char* apellido);
int client_getCuit(Client* this,char* cuit);

int client_printSingle(void* this);
#endif // CLIENT_H_

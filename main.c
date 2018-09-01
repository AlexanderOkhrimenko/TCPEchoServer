#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc , char *argv[])
{
    // Переменные для создания массивов
    int p11 = 0, p12 = 0; // параметры для первого массива
    int p21 = 0, p22 = 0; // .....
    int p31 = 0, p32 = 0; // .....
    
    char seq1[101]; // массив для первой функции
    char seq2[101];
    char seq3[101];

    int* sets(int a, int b);
    
    // Стандартное для сокетов
    int socket_desc , client_sock , c , read_size;
    struct sockaddr_in server , client;
    char client_message[2000];

    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Сокет не возможно создать");
    }
    puts("Сокет создан");
    
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8888 );
    
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("bind failed. Error");
        return 1;
    }
    //puts("Подключено..");
    
    listen(socket_desc , 3);
    
    puts("Ожидание подключения...");
    c = sizeof(struct sockaddr_in);
    
    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }
    puts("Подключение установлено");
    
    //Прием данных от клиента
    while( (read_size = recv(client_sock , client_message , 2000 , 0)) > 0 )
    {
        //Ответ клиенту
        if (client_message[0] == 's' && client_message[1] == 'e' && client_message[2] == 'q' ) {
           
            // Разбор строк в команды со значениями
            // Нет времени писать разбор строки (от проблеа до пробела) поэтому будем считать что параметры в один символ!
            
            if (client_message[3] == '1') {
               // printf("%c", client_message[5]);
                p11 = atoi(&client_message[5]);
                p12 = atoi(&client_message[7]);
                //printf("%i",sets(p11, p12));
                
              //  int *ptr = (sets(p11, p12));
                
              //  for (int i=0; i<100; i++) {
              //      printf(" address=%p \t value=%d \n", ptr+i, *(ptr+i));
              //  }
               
                if ( (p11 == 0) || (p12 == 0) ) { // для фильтрации нулевых параметров
                    printf("00000");
                    } else {
                    
                        for (int i=p11, j=0; i<=100; i+=p12, j++) {
                            seq1[j] = i;
                            printf("%d \t", i);
                        }
                }
                
                write(client_sock , seq1, strlen(seq1)); // TELNET отображает только символьную информатцию...
                
            }
            if (client_message[3] == '2') {
                //printf("COMMAND seq2");
                p21 = atoi(&client_message[5]);
                p22 = atoi(&client_message[7]);
                printf("%i %i", p21 , p22);
               
            }
            if (client_message[3] == '3') {
                // printf("COMMAND seq3");
                p31 = atoi(&client_message[5]);
                p32 = atoi(&client_message[7]);
                printf("%i %i", p31 , p32);
      
            }
            printf("COMMAND seq");
        }
        
      // write(client_sock , sets(2, 2), strlen(seq1));
     //  write(client_sock , client_message, strlen(client_message));
    }
    
    if(read_size == 0)
    {
        puts("Клиент отключен");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("Передача не удалась");
    }
    return 0;
}

// Функция принимает параметры из коммандной строки и генерирует последовательность из 100 символов
int* sets(int a, int b)
{
    int *ptr = 0;
    int temp[101];
    for (int i=a, j=0; i<=100; i+=b, j++) {
       temp[j] = i;
      // printf("%d", i);
    }
    ptr = temp;
    for (int *ptr=temp; ptr<=&temp[100]; ptr++) {
        printf("address=%p \t value=%d \n", ptr, *ptr);
    }
    
    return ptr;
}



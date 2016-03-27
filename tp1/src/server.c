#include<limits.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "checksum.h"
#include "dynamic_array.h"
#include "protocol.h"
#include "socket_api.h"

// Sets filename and block_size
static void receive_file_info(sktinfo_t *skt, char *filename, 
        int filename_length, int *block_size);

// Receives a checksum array and initializes it with the info of sent by the
// client
static void receive_file_data(sktinfo_t *skt, array_t *chksm_array);

// Calculates the checksums of the server local files and compares them with
// the ones in the checksum array
static int compare_files(sktinfo_t *skt, char *filename, array_t *chksm_array,
        int block_size);

// Sends the index of the checksum of the common bytes between client and
// server
static void send_info_common_bytes(sktinfo_t *skt, int index);

void servidor(char *port) {
    sktinfo_t skt;

    socket_init(&skt, NULL, port);

    socket_bind(&skt);
    socket_listen(&skt, 10);
    
    // accept incoming connections
    socket_accept(&skt); 
    

    int filename_length;
    socket_receive(&skt, &filename_length, sizeof(filename_length));   

    char filename[filename_length];
    int block_size;
    receive_file_info(&skt, filename, filename_length, &block_size);
    array_t chksm_array;
    array_init(&chksm_array, 10);
    receive_file_data(&skt, &chksm_array);
    compare_files(&skt, filename, &chksm_array, block_size);
    array_destroy(&chksm_array);
    socket_destroy(&skt);
}

static void receive_file_info(sktinfo_t *skt, char *filename, 
        int filename_length, int *block_size) {
    //printf("%d\n", filename_length);
    socket_receive(skt, filename, filename_length);
    //printf("%s\n", filename);
    socket_receive(skt, block_size, sizeof(*block_size));
    //printf("%d\n", *block_size);
}

static void receive_file_data(sktinfo_t *skt, array_t *chksm_array) {
    int checksum, operation;
   
    socket_receive(skt, &operation, sizeof(operation));
    while (operation == 1) {
        socket_receive(skt, &checksum, sizeof(checksum));
        array_append(chksm_array, checksum);
        socket_receive(skt, &operation, sizeof(operation));
    }
}

static int compare_files(sktinfo_t *skt, char *filename, array_t *chksm_array,
        int block_size) {
    FILE *fp = fopen(filename, "r");
    //long actual_pos = ftell(fp);
    //long start_diff = actual_pos;
    //long end_diff = actual_pos;
     
    int server_chksm = 0;
    int client_chksm_pos = -1;
    int status  = 0;
    int a;
    while (!feof(fp)) {
        switch (status) {
            case 0:
                server_chksm = process_block(fp, block_size);
                if (server_chksm >= 0) {
                    client_chksm_pos = array_find(chksm_array, server_chksm);
                }

                if (client_chksm_pos == -1) {
                    printf("BAD ENTRANCE\n");
                    /*
                    end_diff = ftell(fp);
                    fseek(fp, end_diff - 1, SEEK_SET);
                    status = 1;
                    */
                } else {
                    status = 2;
                }
                break;
            case 1:
                server_chksm = process_block(fp, block_size);
                break;
            case 2:
                //actual_pos = ftell(fp);
                // send diff bytes from file (fp, s_diff, e_diff, a_pos)
                send_info_common_bytes(skt, client_chksm_pos);
                // send NB (client_chksm_pos)
                //start_diff = actual_pos;
                //end_diff = actual_pos;
                status = 0;
                printf("sv chksm %x\n", server_chksm);
                break;
        }
    }
    a = 5;
    socket_send(skt, &a, sizeof(a));
    fclose(fp);
    return 0;
}

static void send_info_common_bytes(sktinfo_t *skt, int index) {
    //socket_send(skt, "hola", sizeof("hola"));
    int status = 4;
    socket_send(skt, &status, sizeof(status)); 
    socket_send(skt, &index, sizeof(index));
    return;
}

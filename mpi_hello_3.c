#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;

    // Inicializar MPI
    MPI_Init(&argc, &argv);

    // Obtener el rango (identificador) del proceso actual
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Obtener el número total de procesos
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Mensaje que cada proceso enviará al proceso 0
    char message[100];
    snprintf(message, sizeof(message), "Hello from process %d", rank);

    // Mensaje de confirmación de recepción
    char confirmation[100];

    // Proceso 0 recibe los mensajes de los demás procesos y envía confirmación
    if (rank == 0) {
        printf("I'm process %d and I'm waiting to receive messages:\n", rank);
        for (int i = 1; i < size; i++) {
            MPI_Recv(message, sizeof(message), MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            snprintf(confirmation, sizeof(confirmation), "Received your message, process %d!", i);
            MPI_Send(confirmation, sizeof(confirmation), MPI_CHAR, i, 0, MPI_COMM_WORLD);
            printf("Received: %s\n", message);
        }
    } else {
        // Procesos distintos de 0 envían sus mensajes al proceso 0 y esperan confirmación
        printf("I'm process %d, sending a message to process 0:\n", rank);
        MPI_Send(message, sizeof(message), MPI_CHAR, 0, 0, MPI_COMM_WORLD);
        MPI_Recv(confirmation, sizeof(confirmation), MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Received confirmation: %s\n", confirmation);
    }

    // Finalizar MPI
    MPI_Finalize();

    return 0;
}

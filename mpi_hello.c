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

    if (argc != 2) {
        if (rank == 0) {
            printf("Uso: mpiexec -n <num_procesos> %s <num_procesos>\n", argv[0]);
        }
        MPI_Finalize();
        return 1;
    }

    int num_procesos;
    if (rank == 0) {
        num_procesos = atoi(argv[1]);
    }

    // Transmitir el número de procesos a todos los procesos
    MPI_Bcast(&num_procesos, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Asegurarse de que hay al menos num_procesos procesos en ejecución
    if (size < num_procesos) {
        if (rank == 0) {
            printf("Error: No hay suficientes procesos para ejecutar el programa.\n");
        }
        MPI_Finalize();
        return 1;
    }

    printf("Hello World, I'm process %d of %d!\n", rank, size);

    // Finalizar MPI
    MPI_Finalize();

    return 0;
}

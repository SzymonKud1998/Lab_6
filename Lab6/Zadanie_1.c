#include <stdio.h>
#include <math.h>
#include "mpi.h"

int main(int argc, char **argv)
{
    const int TAG = 55555;

    int wynik_obecny;
    int wszystkie;               
    MPI_Init(&argc, &argv); 
    MPI_Comm_size(MPI_COMM_WORLD, &wszystkie);
    MPI_Comm_rank(MPI_COMM_WORLD, &wynik_obecny);
    float odebrana_wartosc = 0;
    if(wynik_obecny != 0)
    {
        MPI_Status status;
        int nadawca = wynik_obecny-1;
        MPI_Recv(&odebrana_wartosc, 1, MPI_FLOAT, nadawca, TAG, MPI_COMM_WORLD, &status);
        printf("Procces %d odebral wartosc: %f\n", wynik_obecny, odebrana_wartosc);
    }

    float aktualna_wartosc = 4 * powf(-1, wynik_obecny) / (2.0f * (wynik_obecny+1) -1 );
    aktualna_wartosc += odebrana_wartosc;

    if(wynik_obecny != wszystkie-1)
    {
        int adresat = wynik_obecny + 1;
        MPI_Send(&aktualna_wartosc, 1, MPI_FLOAT, adresat, TAG, MPI_COMM_WORLD);
        printf("Procces %d wyslal wartosc: %f\n", wynik_obecny, aktualna_wartosc);
    }
    else
    {
        printf("Wyliczona wartosc to: %f\n", aktualna_wartosc);
    }


    MPI_Finalize();
    return 0;
}
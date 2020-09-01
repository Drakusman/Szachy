#include "stdio.h"

short int dia_r[256];
short int dia_l[256];   // tablice z zajêtymi przek¹tnymi
short int col[8];       // tablica z zajêtymi kolumnami
short int chart[8][8];  // tablica z ustawieniami hetmanów
int found = 0;          // licznik znalezionych pozycji
int n=0;
void printCombination(void) {
        int x,y;
	printf("kombinacja: %d\n", found);
	printf("  ABCDEFGH\n\n");
	for (y=n-1; y>=0; y--) {
		printf("%d ", y+1);
	    for (x=0; x<n; x++) {
	    	if (chart[x][y]) {
	    		printf("H");
	    	}
	        else {
	        	printf(" ");
	        }
	    }
	    printf("\n");
	}
	printf("\n\n");
}

void add_hetman(int row) {
        int i;
	for (i=0; i<n; i++) {
		if (!((col[i] == 1) || (dia_r[i-row+128] == 1) || (dia_l[row+i+128] == 1))) {
			dia_r[i-row+128] = 1;     // dodaj przek¹tne
            dia_l[row+i+128] = 1;
            col[i] = 1;               // dodaj kolumnê
            chart[i][row] = 1;        // postaw hetmana w tablicy
            if (row<n-1) {
            	add_hetman(row+1);       // analizuj nastepny wiersz (tylko jesli nie jestesmy juz w ostatnim)
            }
            else {                       // to jest ostatni hetman - zapisz wynik
            	found++;
                printCombination();
            }
            // po wyjsciu z procedury rekurencyjnej (add_hetman(row+1)) usun hetmana i szukaj dla niego nastepnego pola
            dia_r[i-row+128] = 0;
            dia_l[row+i+128] = 0;
            col[i] = 0;
            chart[i][row] = 0;
            }
        }
}

int main(void) {
        int i,j;
        printf("Podaj ilosc hetmanow\n");
        scanf("%d",&n);
        //inicjuj strukury
        for (i=0; i<256; i++) {
                dia_r[256] = 0;
                dia_l[256] = 0;
        }
        for (i=0; i<n; i++) {
                col[8] = 0;
        }
        for (i=0; i<n; i++) {
                for (j=0; j<n; j++) {
                        chart[i][j] = 0;
                }
        }

        add_hetman(0);             // postaw pierwszego hetmana

        return 0;
}

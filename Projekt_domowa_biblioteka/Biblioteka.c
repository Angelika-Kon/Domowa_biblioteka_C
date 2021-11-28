#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


#define MAXTYTUL 40
#define MAXAUTOR 40
#define MAXKAT 30
#define MAX 100 //maksymalna liczba ksiazek

struct ksiazka {    //tworzenie struktury
    char tytul[MAXTYTUL];
    char autor[MAXAUTOR];
    char kategoria[MAXKAT];
};

char* wczytaj(char* z, int ile) { //funkcja pozwalaj¹ca wczytac dane z zamiana znaku \n na \0
    char* wynik;
    char* tutaj;
    wynik = fgets(z, ile, stdin);
    if (wynik) {
        tutaj = strchr(z, '\n');//szukamy nowego wiersza
        if (tutaj)             //jesli adres jest rozny od NULL
            *tutaj = '\0';    //zmieniamy znak nowego wiersza na pusty
        else
            while (getchar() != '\n')
                continue;   //porzucenie reszty wiersza
    }
    return wynik;
}
void wypisanie()
{
    struct ksiazka bibl[MAX]; //tablica struktur
    int licznik = 0;
    int  licznikp;
    FILE* bibliotekap;
    int rozmiar = sizeof(struct ksiazka);
    if (fopen_s(&bibliotekap, "bibliotekap.dat", "a+b") != 0)
    {
        fputs("Nie moge otworzyc pliku bibliotekap.dat\n", stderr);
        exit(1);
    }
    rewind(bibliotekap); // przejscie na pocz¹tek pliku
    while (licznik < MAX && fread(&bibl[licznik], rozmiar,     //pêtla wczytuje kolejne struktury do tablicy bibl
        1, bibliotekap) == 1)
    {
        if (licznik == 0)
            puts("Biezaca zawartosc pliku bibliotekap.dat: ");
        printf("%s by %s : kategoria:%s \n", bibl[licznik].tytul, bibl[licznik].autor, bibl[licznik].kategoria); //Wypisanie zawartoœci pliku
        licznik++;
    }
    licznikp = licznik;
    if (licznik == MAX)
    {
        fputs("Plik bibliotekap.dat jest pelny.", stderr);
        exit(2);
    }
    fclose(bibliotekap);

}
void dopisanie()
{
    struct ksiazka bibl[MAX]; //tablica struktur
    int licznik = 0;
    int index, licznikp;
    FILE* bibliotekap;
    int rozmiar = sizeof(struct ksiazka);
    if (fopen_s(&bibliotekap, "bibliotekap.dat", "a+b") != 0)
    {
        fputs("Nie moge otworzyc pliku bibliotekap.dat\n", stderr);
        exit(1);
    }
    rewind(bibliotekap); // przejscie na pocz¹tek pliku
    while (licznik < MAX && fread(&bibl[licznik], rozmiar,     //pêtla wczytuje kolejne struktury do tablicy bibl
        1, bibliotekap) == 1)
           licznik++;
 
    licznikp = licznik;
    if (licznik == MAX)
    {
        fputs("Plik bibliotekap.dat jest pelny.", stderr);
        exit(2);
    }
    puts("Podaj nowe tytuly ksiazek.");                             
    puts("Aby zakonczyc, nacisnij [enter] na poczatku wiersza.");
    while (licznik < MAX && wczytaj(bibl[licznik].tytul, MAXTYTUL) != NULL && bibl[licznik].tytul[0] != '\0')  //Dodawanie ksi¹¿ek
    {
        puts("Teraz podaj autora.");
        wczytaj(bibl[licznik].autor, MAXAUTOR);
        puts("Podaj kategorie.");
        wczytaj(bibl[licznik++].kategoria, MAXKAT);
        if (licznik < MAX)
            puts("Podaj nastepny tytul.");
    }
    if (licznik > 0)
    {
        puts("Oto lista Twoich ksiazek:\n");                   
        for (index = 0; index < licznik; index++)        //Wypisanie listy ksi¹¿ek
            printf("%s,autor: %s,kategoria:%s \n", bibl[index].tytul,
                bibl[index].autor, bibl[index].kategoria);
        fwrite(&bibl[licznikp], rozmiar, licznik - licznikp, bibliotekap);
    }
    else
        puts("Zadnych ksiazek? Szkoda\n");
    puts("Koniec.\n");
    fclose(bibliotekap);

}
void wyszukiwanie() {
   
    char autors[MAXAUTOR];
    char nazwisko[MAXAUTOR];
    char tytul2[MAXTYTUL];
    char kategorie[MAXKAT];
    int wybor;
    int licz = 0;
    char slowo[20]; //s³owo klucz
    char* schowek;
    char* next = NULL;
    char* s = { " ,.:-" };
    struct ksiazka bibl[MAX]; //tablica struktur
    int licznik = 0;
    int licznikp;
    FILE* bibliotekap;
    int rozmiar = sizeof(struct ksiazka);
    if (fopen_s(&bibliotekap, "bibliotekap.dat", "a+b") != 0)
    {
        fputs("Nie moge otworzyc pliku bibliotekap.dat\n", stderr);
        exit(1);
    }
    rewind(bibliotekap); // przejscie na pocz¹tek pliku
    while (licznik < MAX && fread(&bibl[licznik], rozmiar,     //pêtla wczytuje kolejne struktury do tablicy bibl
        1, bibliotekap) == 1)
        licznik++;

    licznikp = licznik;
    if (licznik == MAX)
    {
        fputs("Plik bibliotekap.dat jest pelny.", stderr);
        exit(2);
    }
    rewind(bibliotekap);
    printf("Wybierz kryterium wyszukiwania:\n1.Autor\n2.Nazwisko autora\n3.Tytul\n4.Slowo kluczowe w tytule\n5.Kategoria\n");
    scanf_s("%d", &wybor);
    while (getchar() != '\n')
        continue;
    switch (wybor)
    {
    case 1:                                         //Wyszukiwanie po autorze
        printf("Podaj autora:\n");
        wczytaj(autors, MAXAUTOR);
        rewind(bibliotekap);
        for (int index = 0; index < MAX; index++)
        {
            if (_stricmp(autors, bibl[index].autor) == 0)   //porównanie dwóch ³añcuchów znaków pomijaj¹c wielkoœæ liter  
            {
                printf("%s,autor: %s,kategoria:%s \n", bibl[index].tytul,
                    bibl[index].autor, bibl[index].kategoria);
                licz++;
            }
        }
        if (licz < 1)
        {
            printf("Nie znaleziono autora.\n");
        }
        break;

    case 2:                                         //Wyszukiwanie po nazwisku autora
        printf("Podaj nazwisko autora:\n");
        wczytaj(nazwisko, sizeof(nazwisko));
        rewind(bibliotekap);
        for (int i = 0; i < licznikp; i++) {
            char zmienna[30];
            strncpy_s(zmienna, 30, bibl[i].autor, MAXAUTOR);    //kopiowanie ³añcuchów znaków
            schowek = strtok_s(zmienna, s, &next);  //podzia³ tekstu na s³owa
            while (schowek != NULL) {
                if (_stricmp(schowek, nazwisko) == 0) { 
                    printf("%s,autor: %s,kategoria:%s \n", bibl[i].tytul,
                        bibl[i].autor, bibl[i].kategoria);
                    licz++;
                }
                schowek = strtok_s(NULL, s, &next);
            }
        }
        if (licz < 1)
        {
            printf("Nie znaleziono.\n");
        }
        break;

    case 3:                                         //Wyszukiwanie po tytule
        printf("Podaj tytul:\n");
        wczytaj(tytul2, sizeof(tytul2));
        rewind(bibliotekap);
        for (int index = 0; index < MAX; index++)
        {
            if (_stricmp(tytul2, bibl[index].tytul) == 0)
            {
                printf("%s,autor: %s,kategoria:%s \n", bibl[index].tytul,
                    bibl[index].autor, bibl[index].kategoria);
                licz++;
            }
        }
        if (licz < 1)
        {
            printf("Nie znaleziono.\n");
        }
        break;

    case 4:                                         //Wyszukiwanie po s³owie kluczu
        printf("Podaj slowo klucz:\n");
        wczytaj(slowo, sizeof(slowo));
        rewind(bibliotekap);

        for (int i = 0; i < licznik; i++) {
            char zmienna[30];
            strncpy_s(zmienna, 30, bibl[i].tytul, MAXTYTUL); 

            schowek = strtok_s(zmienna, s, &next);          
            while (schowek != NULL) {
                if (_stricmp(schowek, slowo) == 0) { 
                    printf("%s,autor:%s,kategoria:%s \n", bibl[i].tytul,
                        bibl[i].autor, bibl[i].kategoria);
                    licz++;
                }
                schowek = strtok_s(NULL, s, &next);
            }
        }
        if (licz < 1)
        {
            printf("Nie znaleziono.\n");
        }
        break;

    case 5:                                         //Wyszukiwanie po kategorii
        printf("Podaj kategorie:\n");
        scanf_s("%s", kategorie, sizeof(kategorie));
        rewind(bibliotekap);
        for (int index = 0; index < MAX; index++)
        {
            if (_stricmp(bibl[index].kategoria, kategorie) == 0) 
            {
                printf("%s,autor: %s,kategoria:%s \n", bibl[index].tytul,
                    bibl[index].autor, bibl[index].kategoria);
                licz++;
            }
        }
        if (licz < 1)
        {
            printf("Nie znaleziono.\n");
        }
        break;
    }
    fclose(bibliotekap);

}


void menu()
{
    int m;
    puts("Twoja domowa biblioteka\n");
    printf("Aby rozpoczac wybierz numer:\n1.Wypisanie wszystkich ksiazek z biblioteki.\n2.Dopisanie nowych pozycji.\n3.Wyszukiwanie ksiazek.\n");
    scanf_s("%d", &m);
    while (getchar() != '\n')
        continue;
    switch (m)
    {
    case 1:
        wypisanie();
        int menu1;
        puts("1.Powrot do menu\n2.Zakoncz.\n");
        scanf_s("%d", &menu1);
        switch (menu1)
        {
        case 1:
            menu();
            break;
        case 2:
            printf("Pora na czytanie.\n");
            break;
        }
        break;
    case 2:
        dopisanie();
        int menu2;
        puts("1.Powrot do menu\n2.Zakoncz.\n");
        scanf_s("%d", &menu2);
        switch (menu2)
        {
        case 1:
            menu();
            break;
        case 2:
            printf("Pora na czytanie.\n");
            break;
        }
        break;
    case 3:
        wyszukiwanie();
        int menu3;
        puts("1.Powrot do menu\n2.Zakoncz.\n");
        scanf_s("%d", &menu3);
        switch (menu3)
        {
        case 1:
            menu();
            break;
        case 2:
            printf("Pora na czytanie.\n");
            break;
        }
        break;
    }
}








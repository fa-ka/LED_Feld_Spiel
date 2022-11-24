#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

//Index von 0 bis 7
void feld_anzeigen(int y, int x, int rand1y, int rand1x, int rand2y, int rand2x){
    char feld[8][8] = { 0 };
    feld[rand1y][rand1x] = 'O';
    feld[rand2y][rand2x] = 'O';
    feld[y][x] = 'X';
    int i, j;
    //Schleife für Zeilen, Y-Achse
    for(i=0; i<8; i++){
        //Schleife für Spalten, X-Achse
        for(j=0; j<8; j++){
            printf("%c ", feld[i][j]);
        }
        printf("\n");
    }
}

bool checke_spielfeldgraenze(int y, int x){
    if((y>=0)&&(y<=7)&&(x>=0)&&(x<=7)){return true;}
    else{return false;}
}

bool mache_einen_richtunngsschritt(int *y, int *x, int rand1y, int rand1x, int rand2y, int rand2x){
    bool status = true;
    char btn_richtung;
    char taste;
    printf("Bitte Richtungstaste drücken (j->Links k->Rechts i->Oben m->Unten)\n");
    scanf(" %c", &taste);

    if(taste == 'j'){btn_richtung='L';}
    else if(taste == 'k'){btn_richtung='R';}
    else if(taste == 'i'){btn_richtung='O';}
    else if(taste == 'm'){btn_richtung='U';}
    else if(taste == 'q'){btn_richtung='Q';}
    else{btn_richtung='X';}

    switch(btn_richtung){
        case 'L':
            *x=*x-1;                          //ein pixel nach links
            if(checke_spielfeldgraenze(*y,*x)==false){*x=*x+1;}
            break;
        case 'R':
            *x=*x+1;                          //ein pixel nach rechts
            if(checke_spielfeldgraenze(*y,*x)==false){*x=*x-1;}
            break;
        case 'O':
            *y=*y-1;                          //ein pixel nach oben
            if(checke_spielfeldgraenze(*y,*x)==false){*y=*y+1;}
            break;
        case 'U':
            *y=*y+1;                          //ein pixel nach unten
            if(checke_spielfeldgraenze(*y,*x)==false){*y=*y-1;}
            break;
        case 'Q':
            status = false;
            break;
        default:
            break;
    }
    feld_anzeigen(*y,*x,rand1y,rand1x,rand2y,rand2x);
    return status;
}

int main() {
    time_t zeit = time(NULL);
    srand(zeit);
    int rand1y = rand()%8;
    int rand1x = rand()%8;
    int rand2y = rand()%8;
    int rand2x = rand()%8;
    //Startwert des zu steuernden Pin definieren
    int y = 4;            //Startwert reihe
    int x = 4;            //Startwert spalte
    bool status = true;
    feld_anzeigen(y,x,rand1y,rand1x,rand2y,rand2x);
    while(status==true){
        status = mache_einen_richtunngsschritt(&y, &x,rand1y,rand1x,rand2y,rand2x);
    }
    return 0;
}
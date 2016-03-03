#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <stdio.h>

using namespace std;
//variables de inicialización de personajes
int numero_reina, numero_papa, numero_mama, numero_pret, numero_ex;
//variables de personajes
int reina[1], papa[1], mama[1], pret[1], exnovio[1];
// variables de casillas
int cas_re = 1, cas_pa = 2, cas_ma = 3, cas_pret = 4, cas_exn = 5;
int turno = 1;
int tablero[64];
int cas_llenas[8];
//variable de nueva posición
int new_pos;

//Inicia el tablero haciendo una iteración por todo el array tablero[] y asignando un valor 0 a cada espacio
void initab(){
    for(int i=0;i<64;i++){
            tablero[i]= 0;
    }
}

//Crea un número aleatorio entre 1 y 8 que definirá la acción al azar que realizará cada personaje

int ranmov()
{
    srand(time(NULL));
    return rand()%8 + 1;
}

//Inicia cada jugador con un número aleatorio entre 0 y 63 que será su posición en el tablero
//Nota: aún no tengo claro si es entre 1 y 64 o 0 y 63, hay que preguntar al profesor.

void iniciar_jug() {
srand(time(NULL));
numero_reina = rand()%64 + 1;

//cada uno de estos ciclos do/while realiza una comparación con cada una de las variables iniciadas
//anteriormente para que cada personaje tenga un valor diferente

do {
    numero_papa = rand()%64 + 1;

} while (numero_reina == numero_papa);
do {
    numero_mama = rand()%64 + 1;

} while (numero_papa == numero_mama || numero_reina == numero_mama);
do{
    numero_pret = rand()%64 + 1;
} while (numero_pret == numero_mama || numero_pret == numero_papa || numero_pret == numero_reina);
do {
    numero_ex = rand()%64 + 1;
} while (numero_pret == numero_ex || numero_ex == numero_papa || numero_ex == numero_mama || numero_ex == numero_reina);

//Una vez posicionadas las fichas, se le asigna un valor de acuerdo al personaje
//Reina = 1, papa = 2, mama = 3, pretendiente = 4, exnovio = 5

tablero[numero_reina] = cas_re;
tablero[numero_papa] = cas_pa;
tablero[numero_mama] = cas_ma;
tablero[numero_pret] = cas_pret;
tablero[numero_ex] = cas_exn;

//couts de debug para comprobar valores, inútiles si se ejecuta turn()
/*
cout<<"reina: "<<tablero[numero_reina]<<endl;
cout<<"papa: "<<tablero[numero_papa]<<endl;
cout<<"mama: "<<tablero[numero_mama]<<endl;
cout<<"pret: "<<tablero[numero_pret]<<endl;
cout<<"ex: "<<tablero[numero_ex]<<endl;
cout<<"numero reina: "<<numero_reina<<endl;
cout<<"numero papa: "<<numero_papa<<endl;
cout<<"numero mama: "<<numero_mama<<endl;
cout<<"numero pret: "<<numero_pret<<endl;
cout<<"numero ex: "<<numero_ex<<endl;*/
}

void imprimir()
{
    //ciclo for que dibuja el tablero en la consola
    int c=1;
    for(int x=0; x<8; x++)
    {
        cout<<"+---+---+---+---+---+---+---+---+\n";
        for(int y=0; y<8; y++)
        {
            cout<<"| ";
        switch(tablero[c])
        {
            // R para reina, P para Papá, M para Mamá, A para Ammigo(Pretendiente), E para Ex-novio
            //Si no hay ningun personaje en la casilla es espacio vacio

            case 1:cout<<"R"<<" ";break;
            case 2:cout<<"P"<<" ";break;
            case 3:cout<<"M"<<" ";break;
            case 4:cout<<"A"<<" ";break;
            case 5:cout<<"E"<<" ";break;
            case 0:cout<<"  ";break;
            default:cout<<"  ";break;
        }
        c++;
        }
        cout<<"|"<<endl;
    }
    cout<<"+---+---+---+---+---+---+---+---+\n";
}

//genera la coordenada de la fila en forma de array bidimensional (x, 0)
int matrix_x(int a)
{
int x=(a/8);
if(a%8!=0)
{
    x++;
}
return x;
}

// genera la coordenada de la columna en forma de array bidimensional (0, y)

int matrix_y(int a)
{
int x=matrix_x(a);
int y=(a-((x-1)*8));
y = abs(y);
return y;
}

//convierte la nueva posición, de matriz al valor numérico del arreglo.

int nueva_pos(int x, int y)
{
    return (((x-1)*8)+y);
}

//función para saber el jugador actual
int turno_act(){
if(turno%5==0){
    return 5;
}
else if(turno%5==1){
    return 1;
}
else if(turno%5==2){
    return 2;
}
else if(turno%5==3){
    return 3;
}
else if(turno%5==4){
    return 4;
}
}
int curr_jug() {
    int jugador;
    if(turno_act() == 1) {
        jugador = numero_reina;
    }
    if(turno_act() == 2) {
        jugador = numero_papa;
    }
    if(turno_act() == 3) {
        jugador = numero_mama;
    }
    if(turno_act() == 4) {
        jugador = numero_pret;
    }
    if(turno_act() == 5) {
        jugador = numero_ex;
    }
    return jugador;
}

//función para mover a la princesa

bool movimiento_reina(int jugada) {
    int pos;
    if(turno_act() == 1){
        pos = numero_reina;
    }
    int x = 0, y = 0, new_pos = 0;

    //Como la princesa se mueve como rey, este ciclo genera las 8 posibilidades.

    switch (jugada){
    case 0: x=matrix_x(pos);
            y=matrix_y(pos);break;
    case 1: x=matrix_x(pos)-1;
            y=matrix_y(pos);break;
    case 2: x=matrix_x(pos)-1;
            y=matrix_y(pos)+1;break;
    case 3: x=matrix_x(pos);
            y=matrix_y(pos)+1;break;
    case 4: x=matrix_x(pos)+1;
            y=matrix_y(pos)+1;break;
    case 5: x=matrix_x(pos)+1;
            y=matrix_y(pos);break;
    case 6: x=matrix_x(pos)+1;
            y=matrix_y(pos)-1;break;
    case 7: x=matrix_x(pos);
            y=matrix_y(pos)-1;break;
    case 8: x=matrix_x(pos)-1;
            y=matrix_y(pos)-1;break;}

    //Si se sale del tablero me devuelve false
    if(x<1||x>=8||y<1||y>8){return 0;}

    //Sino me convierte las coordenadas de new_pos al valor numérico del array
    new_pos = nueva_pos(x,y);

    //Si está vacía la casilla me coloca la ficha, sino me devuelve false
   switch(tablero[new_pos]){
    case 0:
        tablero[new_pos]=cas_re;
        tablero[pos]=0;
        numero_reina = new_pos;
        return 1;break;
    case 1:
        return 0;break;
    case 2:
        return 0;break;
    case 3:
        return 0;break;
    case 4:
        return 0;break;
    case 5:
        return 0;break;
    }
}

bool movimiento_pretendiente(int jugada) {
    int pos;
    if(turno_act() == 4){
        pos = numero_pret;
    }
    int x = 0, y = 0, new_pos = 0;

    //Como el pretendiente se mueve como rey, este ciclo genera las 8 posibilidades.

    switch (jugada){
    case 0: x=matrix_x(pos);
            y=matrix_y(pos);break;
    case 1: x=matrix_x(pos)-1;
            y=matrix_y(pos);break;
    case 2: x=matrix_x(pos)-1;
            y=matrix_y(pos)+1;break;
    case 3: x=matrix_x(pos);
            y=matrix_y(pos)+1;break;
    case 4: x=matrix_x(pos)+1;
            y=matrix_y(pos)+1;break;
    case 5: x=matrix_x(pos)+1;
            y=matrix_y(pos);break;
    case 6: x=matrix_x(pos)+1;
            y=matrix_y(pos)-1;break;
    case 7: x=matrix_x(pos);
            y=matrix_y(pos)-1;break;
    case 8: x=matrix_x(pos)-1;
            y=matrix_y(pos)-1;break;}

    //Si se sale del tablero me devuelve false
    if(x<1||x>=8||y<1||y>8){return 0;}

    //Sino me convierte las coordenadas de new_pos al valor numérico del array
    new_pos = nueva_pos(x,y);

    //Si está vacía la casilla me coloca la ficha, sino me devuelve false
   switch(tablero[new_pos]){
    case 0:
        tablero[new_pos]=cas_pret;
        tablero[pos]=0;
        numero_pret = new_pos;
        return 1;break;
    case 1:
        tablero[new_pos]=cas_pret;
        tablero[pos]=0;
        numero_pret = new_pos;
        reina[0]=-1;
        return 1;break;
    case 2:
        return 0;break;
    case 3:
        return 0;break;
    case 4:
        return 1;break;
    case 5:
        return 0;break;
    }
}

bool movimiento_exnovio(int jugada) {
    int pos;
    if(turno_act() == 5){
        pos = numero_ex;
    }
    int x = 0, y = 0, new_pos = 0;

    //Como el ex novio se mueve como rey, este ciclo genera las 8 posibilidades.

    switch (jugada){
    case 0: x=matrix_x(pos);
            y=matrix_y(pos);break;
    case 1: x=matrix_x(pos)-2;
            y=matrix_y(pos)+1;break;
    case 2: x=matrix_x(pos)-1;
            y=matrix_y(pos)+2;break;
    case 3: x=matrix_x(pos)+1;
            y=matrix_y(pos)+2;break;
    case 4: x=matrix_x(pos)+2;
            y=matrix_y(pos)+1;break;
    case 5: x=matrix_x(pos)+2;
            y=matrix_y(pos)-1;break;
    case 6: x=matrix_x(pos)+1;
            y=matrix_y(pos)-2;break;
    case 7: x=matrix_x(pos)-1;
            y=matrix_y(pos)-2;break;
    case 8: x=matrix_x(pos)-2;
            y=matrix_y(pos)-1;break;}

    //Si se sale del tablero me devuelve false
    if(x<1||x>=8||y<1||y>8){return 0;}

    //Sino me convierte las coordenadas de new_pos al valor numérico del array
    new_pos = nueva_pos(x,y);

    //Si está vacía la casilla me coloca la ficha, sino me devuelve false
   switch(tablero[new_pos]){
    case 0:
        tablero[new_pos]=cas_exn;
        tablero[pos]=0;
        numero_ex = new_pos;
        return 1;break;
    case 1:
        tablero[new_pos]=cas_exn;
        tablero[pos]=0;
        numero_ex = new_pos;
        reina[0]=-1;
        return 1;break;
    case 2:
        return 0;break;
    case 3:
        return 0;break;
    case 4:
        return 0;break;
    case 5:
        return 0;break;
    }
}

// Inicia papás

//funciones que devuelven los valores máximos que se puede mover el papá en cualquier dirección

int pos_arriba(int posicion){
    int x = matrix_x(posicion);
    int y = matrix_y(posicion);
    while(x>1){
        x--;
        posicion = nueva_pos(x, y);
    }
    return posicion;
}

int pos_abajo(int posicion){
    int x = matrix_x(posicion);
    int y = matrix_y(posicion);
    while(x<8){
        x++;
        posicion = nueva_pos(x, y);
    }
    return posicion;
}

int pos_derecha(int posicion){
    int x = matrix_x(posicion);
    int y = matrix_y(posicion);
    while(y<8){
        y++;
        posicion = nueva_pos(x, y);
    }
    return posicion;
}

int pos_izquierda(int posicion){
    int x = matrix_x(posicion);
    int y = matrix_y(posicion);
    while(y>1){
        y--;
        posicion = nueva_pos(x, y);
    }
    return posicion;
}


int pos_diagderecha(int posicion){
    int x = matrix_x(posicion);
    int y = matrix_y(posicion);
    while(x>1 && y<8){
        x--;
        y++;
        posicion = nueva_pos(x, y);
    }
    return posicion;
}

int pos_diagizquierda(int posicion){
    int x = matrix_x(posicion);
    int y = matrix_y(posicion);
    while(x>1 && y>1){
        x--;
        y--;
        posicion = nueva_pos(x, y);
    }
    return posicion;
}

int pos_diag_abderecha(int posicion){
    int x = matrix_x(posicion);
    int y = matrix_y(posicion);
    while(x<8 && y<8){
        x++;
        y++;
        posicion = nueva_pos(x, y);
    }
    return posicion;
}

int pos_diag_abizquierda(int posicion){
    int x = matrix_x(posicion);
    int y = matrix_y(posicion);
    while(x<8 && y>1){
        x++;
        y--;
        posicion = nueva_pos(x, y);
    }
    return posicion;
}

// función que verifica si hay algún otro personaje alrededor de una casilla dada

int cas_ady(int posicion, int j) {
    for (int i; i<8; i++){
        cas_llenas[i] = 0;
    }
    int x = matrix_x(posicion);
    int y = matrix_y(posicion);

    int pos_ady[] = {
    nueva_pos(x - 1, y),
    nueva_pos(x - 1, y + 1),
    nueva_pos(x, y + 1),
    nueva_pos(x + 1, y + 1),
    nueva_pos(x + 1, y),
    nueva_pos(x, y - 1),
    nueva_pos(x + 1, y - 1),
    nueva_pos(x -1, y - 1)
    };

    if(tablero[pos_ady[j]]!=0){
        cas_llenas[j] = 1;
        return cas_llenas[j];
    }else{
        return cas_llenas[j];
    }
}


// funciones para cada movimiento, 8 en total.

bool max_abajo(int posicion, int casilla){
    int posicion1 = posicion;
    int m_aba = pos_abajo(posicion);
    int x = matrix_x(posicion);
    int y = matrix_y(posicion);
    int max_x = matrix_x(m_aba);
    int max_y = matrix_y(m_aba);
    int posi;

    while(x<8){
        x++;
        posicion = nueva_pos(x, y);
        x = matrix_x(posicion);
        y = matrix_y(posicion);
        if(tablero[posicion]!=0){
            break;
        }
    };

    int cas_ini = cas_ady(posicion1, 4);
    int cas_des = cas_ady(posicion, 4);

    int new_pos = nueva_pos(x - 1, y);
    cout<<posicion1<<endl;
    cout<<posicion<<endl;
    cout<<cas_ady(posicion, 4)<<endl;
    switch(tablero[posicion]){
    case 0: tablero[posicion1]=0;
            tablero[posicion]=casilla;
            numero_papa = posicion;
            return 1;break;
    case 1: if(cas_ini!=0){
            return 0;
            }else{
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_papa = new_pos;
            return  1;
            };break;
    case 2: tablero[posicion]=casilla;
            numero_papa = posicion;
            return 0;break;
    case 3: if(cas_ini!=0){
            return 0;
            }else{
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_papa = new_pos;
            return 1;
            };break;
    case 4: if(cas_ini!=0 && cas_des!=0){
                return 0;
            }
            else if(matrix_x(posicion)!=8){
            while(x<max_x){
                x++;
            posi = nueva_pos(x, y);
            if(tablero[posi]!=0){
            posi = nueva_pos(x - 1, y);
            break;
            }
            };
            tablero[posicion1]=0;
            tablero[posicion] = casilla;
            tablero[posi]= cas_pret;
            numero_papa = posicion;
            numero_pret = posi;
            return 1;
            }else {
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_papa = new_pos;
            return 1;
            };
            break;
    case 5: if(cas_ini!=0 && cas_des!=0){
                return 0;
            }
            else if(matrix_x(posicion)!=8){
            while(x<max_x){
                x++;
            posi = nueva_pos(x, y);
            if(tablero[posi]!=0){
            posi = nueva_pos(x - 1, y);
            break;
            }
            };
            tablero[posicion1]=0;
            tablero[posi] = cas_exn;
            tablero[posicion]=casilla;
            numero_papa = posicion;
            numero_ex = posi;
            return 1;
            }
            else{
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_papa = new_pos;
            return 1;
            };
            break;
    default: return 0;break;
    };
}

bool max_arriba(int posicion, int casilla){
    int posicion1 = posicion;
    int m_arr = pos_arriba(posicion);
    int x = matrix_x(posicion);
    int y = matrix_y(posicion);
    int max_x = matrix_x(m_arr);
    int max_y = matrix_y(m_arr);
    int posi;

    while(x>1){
        x--;
        posicion = nueva_pos(x, y);
        x = matrix_x(posicion);
        y = matrix_y(posicion);
        if(tablero[posicion]!=0){
            break;
        }
    };

    int cas_ini = cas_ady(posicion1, 0);
    int cas_des = cas_ady(posicion, 0);

    int new_pos = nueva_pos(x + 1, y);

    switch(tablero[posicion]){
    case 0: tablero[posicion1]=0;
            tablero[posicion]=casilla;
            numero_papa = posicion;
            return 1;break;
    case 1: if(cas_ini!=0){
            return 0;
            }else{
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_papa = new_pos;
            return  1;
            };break;
    case 2: tablero[posicion]=casilla;
            numero_papa = posicion;
            return 0;break;
    case 3: if(cas_ini!=0){
            return 0;
            }else{
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_papa = new_pos;
            return 1;
            };break;
    case 4: if(cas_ini!=0 && cas_des!=0){
                return 0;
            }
            else if(matrix_x(posicion)!=1){
            while(x>max_x){
                x--;
            posi = nueva_pos(x, y);
            if(tablero[posi]!=0){
            posi = nueva_pos(x + 1, y);
            break;
            }
            };
            tablero[posicion1]=0;
            tablero[posicion] = casilla;
            tablero[posi]= cas_pret;
            numero_papa = posicion;
            numero_pret = posi;
            return 1;
            }else {
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_papa = new_pos;
            return 1;
            };
            break;
    case 5: if(cas_ini!=0 && cas_des!=0){
                return 0;
            }
            else if(matrix_x(posicion)!=1){
            while(x>max_x){
                x--;
            posi = nueva_pos(x, y);
            if(tablero[posi]!=0){
            posi = nueva_pos(x + 1, y);
            break;
            }
            };
            tablero[posicion1]=0;
            tablero[posi] = cas_exn;
            tablero[posicion]=casilla;
            numero_papa = posicion;
            numero_ex = posi;
            return 1;
            }
            else{
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_papa = new_pos;
            return 1;
            };
            break;
    default: return 0;break;
    };
}

bool max_derecha(int posicion, int casilla){
    int posicion1 = posicion;
    int m_der = pos_derecha(posicion);
    int x = matrix_x(posicion);
    int y = matrix_y(posicion);
    int max_x = matrix_x(m_der);
    int max_y = matrix_y(m_der);
    int posi;

    while(y<8){
        y++;
        posicion = nueva_pos(x, y);
        x = matrix_x(posicion);
        y = matrix_y(posicion);
        if(tablero[posicion]!=0){
            break;
        }
    };

    int cas_ini = cas_ady(posicion1, 2);
    int cas_des = cas_ady(posicion, 2);

    int new_pos = nueva_pos(x, y - 1);

    switch(tablero[posicion]){
    case 0: tablero[posicion1]=0;
            tablero[posicion]=casilla;
            numero_papa = posicion;
            return 1;break;
    case 1: if(cas_ini!=0){
            return 0;
            }else{
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_papa = new_pos;
            return  1;
            };break;
    case 2: tablero[posicion]=casilla;
            numero_papa = posicion;
            return 0;break;
    case 3: if(cas_ini!=0){
            return 0;
            }else{
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_papa = new_pos;
            return 1;
            };break;
    case 4: if(cas_ini!=0 && cas_des!=0){
                return 0;
            }
            else if(matrix_y(posicion)!=8){
            while(y<max_y){
                y++;
            posi = nueva_pos(x, y);
            if(tablero[posi]!=0){
            posi = nueva_pos(x, y - 1);
            break;
            }
            };
            tablero[posicion1]=0;
            tablero[posicion] = casilla;
            tablero[posi]= cas_pret;
            numero_papa = posicion;
            numero_pret = posi;
            return 1;
            }else {
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_papa = new_pos;
            return 1;
            };
            break;
    case 5: if(cas_ini!=0 && cas_des!=0){
                return 0;
            }
            else if(matrix_y(posicion)!=8){
            while(y<max_y){
                y++;
            posi = nueva_pos(x, y);
            if(tablero[posi]!=0){
            posi = nueva_pos(x, y - 1);
            break;
            }
            };
            tablero[posicion1]=0;
            tablero[posi] = cas_exn;
            tablero[posicion]=casilla;
            numero_papa = posicion;
            numero_ex = posi;
            return 1;
            }
            else{
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_papa = new_pos;
            return 1;
            };
            break;
    default: return 0;break;
    };
}

bool max_izquierda(int posicion, int casilla){
    int posicion1 = posicion;
    int m_izq = pos_izquierda(posicion);
    int x = matrix_x(posicion);
    int y = matrix_y(posicion);
    int max_x = matrix_x(m_izq);
    int max_y = matrix_y(m_izq);
    int posi;

    while(y>1){
        y--;
        posicion = nueva_pos(x, y);
        x = matrix_x(posicion);
        y = matrix_y(posicion);
        if(tablero[posicion]!=0){
            break;
        }
    };

    int cas_ini = cas_ady(posicion1, 6);
    int cas_des = cas_ady(posicion, 6);

    int new_pos = nueva_pos(x, y + 1);

    switch(tablero[posicion]){
    case 0: tablero[posicion1]=0;
            tablero[posicion]=casilla;
            numero_papa = posicion;
            return 1;break;
    case 1: if(cas_ini!=0){
            return 0;
            }else{
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_papa = new_pos;
            return  1;
            };break;
    case 2: tablero[posicion]=casilla;
            numero_papa = posicion;
            return 0;break;
    case 3: if(cas_ini!=0){
            return 0;
            }else{
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_papa = new_pos;
            return 1;
            };break;
    case 4: if(cas_ini!=0 && cas_des!=0){
                return 0;
            }
            else if(matrix_y(posicion)!=1){
            while(y>max_y){
                y--;
            posi = nueva_pos(x, y);
            if(tablero[posi]!=0){
            posi = nueva_pos(x, y + 1);
            break;
            }
            };
            tablero[posicion1]=0;
            tablero[posicion] = casilla;
            tablero[posi]= cas_pret;
            numero_papa = posicion;
            numero_pret = posi;
            return 1;
            }else {
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_papa = new_pos;
            return 1;
            };
            break;
    case 5: if(cas_ini!=0 && cas_des!=0){
                return 0;
            }
            else if(matrix_y(posicion)!=1){
            while(y>max_y){
                y--;
            posi = nueva_pos(x, y);
            if(tablero[posi]!=0){
            posi = nueva_pos(x, y + 1);
            break;
            }
            };
            tablero[posicion1]=0;
            tablero[posi] = cas_exn;
            tablero[posicion]=casilla;
            numero_papa = posicion;
            numero_ex = posi;
            return 1;
            }
            else{
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_papa = new_pos;
            return 1;
            };
            break;
    default: return 0;break;
    };
}

bool max_diagderecha(int posicion, int casilla){
    int posicion1 = posicion;
    int m_dider = pos_diagderecha(posicion);
    int x = matrix_x(posicion);
    int y = matrix_y(posicion);
    int max_x = matrix_x(m_dider);
    int max_y = matrix_y(m_dider);
    int posi;

    while(x>1 && y<8){
        x--;
        y++;
        posicion = nueva_pos(x, y);
        x = matrix_x(posicion);
        y = matrix_y(posicion);
        if(tablero[posicion]!=0){
            break;
        }
    };

    int cas_ini = cas_ady(posicion1, 1);
    int cas_des = cas_ady(posicion, 1);

    int new_pos = nueva_pos(x + 1, y - 1);

    switch(tablero[posicion]){
    case 0: tablero[posicion1]=0;
            tablero[posicion]=casilla;
            numero_papa = posicion;
            return 1;break;
    case 1: if(cas_ini!=0){
            return 0;
            }else{
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_papa = new_pos;
            return  1;
            };break;
    case 2: tablero[posicion]=casilla;
            numero_papa = posicion;
            return 0;break;
    case 3: if(cas_ini!=0){
            return 0;
            }else{
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_papa = new_pos;
            return 1;
            };break;
    case 4: if(cas_ini!=0 && cas_des!=0){
                return 0;
            }
            else if(matrix_y(posicion)!=8 && matrix_x(posicion)!=1){
            while(x>max_x && y<max_y){
                x--;
                y++;
            posi = nueva_pos(x, y);
            if(tablero[posi]!=0){
            posi = nueva_pos(x + 1, y - 1);
            break;
            }
            };
            tablero[posicion1]=0;
            tablero[posicion] = casilla;
            tablero[posi]= cas_pret;
            numero_papa = posicion;
            numero_pret = posi;
            return 1;
            }else {
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_papa = new_pos;
            return 1;
            };
            break;
    case 5: if(cas_ini!=0 && cas_des!=0){
                return 0;
            }
            else if(matrix_y(posicion)!=8 && matrix_x(posicion)!=1){
            while(x>max_x && y<max_y){
                x--;
                y++;
            posi = nueva_pos(x, y);
            if(tablero[posi]!=0){
            posi = nueva_pos(x + 1, y - 1);
            break;
            }
            };
            tablero[posicion1]=0;
            tablero[posi] = cas_exn;
            tablero[posicion]=casilla;
            numero_papa = posicion;
            numero_ex = posi;
            return 1;
            }
            else{
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_papa = new_pos;
            return 1;
            };
            break;
    default: return 0;break;
    };
}

bool max_diagizquierda(int posicion, int casilla){
    int posicion1 = posicion;
    int m_dizq = pos_diagizquierda(posicion);
    int x = matrix_x(posicion);
    int y = matrix_y(posicion);
    int max_x = matrix_x(m_dizq);
    int max_y = matrix_y(m_dizq);
    int posi;

    while(x>1 && y>1){
        x--;
        y--;
        posicion = nueva_pos(x, y);
        x = matrix_x(posicion);
        y = matrix_y(posicion);
        if(tablero[posicion]!=0){
            break;
        }
    };

    int cas_ini = cas_ady(posicion1, 7);
    int cas_des = cas_ady(posicion, 7);

    int new_pos = nueva_pos(x + 1, y + 1);

    switch(tablero[posicion]){
    case 0: tablero[posicion1]=0;
            tablero[posicion]=casilla;
            numero_papa = posicion;
            return 1;break;
    case 1: if(cas_ini!=0){
            return 0;
            }else{
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_papa = new_pos;
            return  1;
            };break;
    case 2: tablero[posicion]=casilla;
            numero_papa = posicion;
            return 0;break;
    case 3: if(cas_ini!=0){
            return 0;
            }else{
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_papa = new_pos;
            return 1;
            };break;
    case 4: if(cas_ini!=0 && cas_des!=0){
                return 0;
            }
            else if(matrix_y(posicion)!=1 && matrix_x(posicion)!=1){
            while(x>max_x && y>max_y){
                x--;
                y--;
            posi = nueva_pos(x, y);
            if(tablero[posi]!=0){
            posi = nueva_pos(x + 1, y + 1);
            break;
            }
            };
            tablero[posicion1]=0;
            tablero[posicion] = casilla;
            tablero[posi]= cas_pret;
            numero_papa = posicion;
            numero_pret = posi;
            return 1;
            }else {
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_papa = new_pos;
            return 1;
            };
            break;
    case 5: if(cas_ini!=0 && cas_des!=0){
                return 0;
            }
            else if(matrix_y(posicion)!=1 && matrix_x(posicion)!=1){
            while(x>max_x && y>max_y){
                x--;
                y++;
            posi = nueva_pos(x, y);
            if(tablero[posi]!=0){
            posi = nueva_pos(x + 1, y + 1);
            break;
            }
            };
            tablero[posicion1]=0;
            tablero[posi] = cas_exn;
            tablero[posicion]=casilla;
            numero_papa = posicion;
            numero_ex = posi;
            return 1;
            }
            else{
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_papa = new_pos;
            return 1;
            };
            break;
    default: return 0;break;
    };
}

bool max_diag_abderecha(int posicion, int casilla){
    int posicion1 = posicion;
    int m_abder = pos_diag_abderecha(posicion);
    int x = matrix_x(posicion);
    int y = matrix_y(posicion);
    int max_x = matrix_x(m_abder);
    int max_y = matrix_y(m_abder);
    int posi;

    while(x<8 && y<8){
        x++;
        y++;
        posicion = nueva_pos(x, y);
        x = matrix_x(posicion);
        y = matrix_y(posicion);
        if(tablero[posicion]!=0){
            break;
        }
    };

    int cas_ini = cas_ady(posicion1, 3);
    int cas_des = cas_ady(posicion, 3);

    int new_pos = nueva_pos(x - 1, y - 1);

    switch(tablero[posicion]){
    case 0: tablero[posicion1]=0;
            tablero[posicion]=casilla;
            numero_papa = posicion;
            return 1;break;
    case 1: if(cas_ini!=0){
            return 0;
            }else{
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_papa = new_pos;
            return  1;
            };break;
    case 2: tablero[posicion]=casilla;
            numero_papa = posicion;
            return 0;break;
    case 3: if(cas_ini!=0){
            return 0;
            }else{
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_papa = new_pos;
            return 1;
            };break;
    case 4: if(cas_ini!=0 && cas_des!=0){
                return 0;
            }
            else if(matrix_y(posicion)!=8 && matrix_x(posicion)!=8){
            while(x<max_x && y<max_y){
                x++;
                y++;
            posi = nueva_pos(x, y);
            if(tablero[posi]!=0){
            posi = nueva_pos(x - 1, y - 1);
            break;
            }
            };
            tablero[posicion1]=0;
            tablero[posicion] = casilla;
            tablero[posi]= cas_pret;
            numero_papa = posicion;
            numero_pret = posi;
            return 1;
            }else {
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_papa = new_pos;
            return 1;
            };
            break;
    case 5: if(cas_ini!=0 && cas_des!=0){
                return 0;
            }
            else if(matrix_y(posicion)!=8 && matrix_x(posicion)!=8){
            while(x<max_x && y<max_y){
                x++;
                y++;
            posi = nueva_pos(x, y);
            if(tablero[posi]!=0){
            posi = nueva_pos(x - 1, y - 1);
            break;
            }
            };
            tablero[posicion1]=0;
            tablero[posi] = cas_exn;
            tablero[posicion]=casilla;
            numero_papa = posicion;
            numero_ex = posi;
            return 1;
            }
            else{
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_papa = new_pos;
            return 1;
            };
            break;
    default: return 0;break;
    };
}

bool max_diag_abizquierda(int posicion, int casilla){
    int posicion1 = posicion;
    int m_abizq = pos_diag_abizquierda(posicion);
    int x = matrix_x(posicion);
    int y = matrix_y(posicion);
    int max_x = matrix_x(m_abizq);
    int max_y = matrix_y(m_abizq);
    int posi;

    while(x<8 && y>1){
        x++;
        y--;
        posicion = nueva_pos(x, y);
        x = matrix_x(posicion);
        y = matrix_y(posicion);
        if(tablero[posicion]!=0){
            break;
        }
    };

    int cas_ini = cas_ady(posicion1, 5);
    int cas_des = cas_ady(posicion, 5);

    int new_pos = nueva_pos(x - 1, y + 1);

    switch(tablero[posicion]){
    case 0: tablero[posicion1]=0;
            tablero[posicion]=casilla;
            numero_papa = posicion;
            return 1;break;
    case 1: if(cas_ini!=0){
            return 0;
            }else{
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_papa = new_pos;
            return  1;
            };break;
    case 2: tablero[posicion]=casilla;
            numero_papa = posicion;
            return 0;break;
    case 3: if(cas_ini!=0){
            return 0;
            }else{
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_papa = new_pos;
            return 1;
            };break;
    case 4: if(cas_ini!=0 && cas_des!=0){
                return 0;
            }
            else if(matrix_y(posicion)!=1 && matrix_x(posicion)!=8){
            while(x<max_x && y>max_y){
                x++;
                y--;
            posi = nueva_pos(x, y);
            if(tablero[posi]!=0){
            posi = nueva_pos(x - 1, y + 1);
            break;
            }
            };
            tablero[posicion1]=0;
            tablero[posicion] = casilla;
            tablero[posi]= cas_pret;
            numero_papa = posicion;
            numero_pret = posi;
            return 1;
            }else {
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_papa = new_pos;
            return 1;
            };
            break;
    case 5: if(cas_ini!=0 && cas_des!=0){
                return 0;
            }
            else if(matrix_y(posicion)!=1 && matrix_x(posicion)!=8){
            while(x<max_x && y>max_y){
                x++;
                y--;
            posi = nueva_pos(x, y);
            if(tablero[posi]!=0){
            posi = nueva_pos(x - 1, y + 1);
            break;
            }
            };
            tablero[posicion1]=0;
            tablero[posi] = cas_exn;
            tablero[posicion]=casilla;
            numero_papa = posicion;
            numero_ex = posi;
            return 1;
            }
            else{
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_papa = new_pos;
            return 1;
            };
            break;
    default: return 0;break;
    };
}

bool max_abajo_ma(int posicion, int casilla){
    int posicion1 = posicion;
    int m_aba = pos_abajo(posicion);
    int x = matrix_x(posicion);
    int y = matrix_y(posicion);
    int max_x = matrix_x(m_aba);
    int max_y = matrix_y(m_aba);
    int posi;

    while(x<8){
        x++;
        posicion = nueva_pos(x, y);
        x = matrix_x(posicion);
        y = matrix_y(posicion);
        if(tablero[posicion]!=0){
            break;
        }
    };

    int cas_ini = cas_ady(posicion1, 4);
    int cas_des = cas_ady(posicion, 4);

    int new_pos = nueva_pos(x - 1, y);
    cout<<posicion1<<endl;
    cout<<posicion<<endl;
    cout<<cas_ady(posicion, 4)<<endl;
    switch(tablero[posicion]){
    case 0: tablero[posicion1]=0;
            tablero[posicion]=casilla;
            numero_mama = posicion;
            return 1;break;
    case 1: if(cas_ini!=0){
            return 0;
            }else{
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_mama = new_pos;
            return  1;
            };break;
    case 2: tablero[posicion]=casilla;
            numero_mama = posicion;
            return 0;break;
    case 3: if(cas_ini!=0){
            return 0;
            }else{
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_mama = new_pos;
            return 1;
            };break;
    case 4: if(cas_ini!=0 && cas_des!=0){
                return 0;
            }
            else if(matrix_x(posicion)!=8){
            while(x<max_x){
                x++;
            posi = nueva_pos(x, y);
            if(tablero[posi]!=0){
            posi = nueva_pos(x - 1, y);
            break;
            }
            };
            tablero[posicion1]=0;
            tablero[posicion] = casilla;
            tablero[posi]= cas_pret;
            numero_mama = posicion;
            numero_pret = posi;
            return 1;
            }else {
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_mama = new_pos;
            return 1;
            };
            break;
    case 5: if(cas_ini!=0 && cas_des!=0){
                return 0;
            }
            else if(matrix_x(posicion)!=8){
            while(x<max_x){
                x++;
            posi = nueva_pos(x, y);
            if(tablero[posi]!=0){
            posi = nueva_pos(x - 1, y);
            break;
            }
            };
            tablero[posicion1]=0;
            tablero[posi] = cas_exn;
            tablero[posicion]=casilla;
            numero_mama = posicion;
            numero_ex = posi;
            return 1;
            }
            else{
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_mama = new_pos;
            return 1;
            };
            break;
    default: return 0;break;
    };
}

bool max_arriba_ma(int posicion, int casilla){
    int posicion1 = posicion;
    int m_arr = pos_arriba(posicion);
    int x = matrix_x(posicion);
    int y = matrix_y(posicion);
    int max_x = matrix_x(m_arr);
    int max_y = matrix_y(m_arr);
    int posi;

    while(x>1){
        x--;
        posicion = nueva_pos(x, y);
        x = matrix_x(posicion);
        y = matrix_y(posicion);
        if(tablero[posicion]!=0){
            break;
        }
    };

    int cas_ini = cas_ady(posicion1, 0);
    int cas_des = cas_ady(posicion, 0);

    int new_pos = nueva_pos(x + 1, y);

    switch(tablero[posicion]){
    case 0: tablero[posicion1]=0;
            tablero[posicion]=casilla;
            numero_mama = posicion;
            return 1;break;
    case 1: if(cas_ini!=0){
            return 0;
            }else{
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_mama = new_pos;
            return  1;
            };break;
    case 2: tablero[posicion]=casilla;
            numero_mama = posicion;
            return 0;break;
    case 3: if(cas_ini!=0){
            return 0;
            }else{
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_mama = new_pos;
            return 1;
            };break;
    case 4: if(cas_ini!=0 && cas_des!=0){
                return 0;
            }
            else if(matrix_x(posicion)!=1){
            while(x>max_x){
                x--;
            posi = nueva_pos(x, y);
            if(tablero[posi]!=0){
            posi = nueva_pos(x + 1, y);
            break;
            }
            };
            tablero[posicion1]=0;
            tablero[posicion] = casilla;
            tablero[posi]= cas_pret;
            numero_mama = posicion;
            numero_pret = posi;
            return 1;
            }else {
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_mama = new_pos;
            return 1;
            };
            break;
    case 5: if(cas_ini!=0 && cas_des!=0){
                return 0;
            }
            else if(matrix_x(posicion)!=1){
            while(x>max_x){
                x--;
            posi = nueva_pos(x, y);
            if(tablero[posi]!=0){
            posi = nueva_pos(x + 1, y);
            break;
            }
            };
            tablero[posicion1]=0;
            tablero[posi] = cas_exn;
            tablero[posicion]=casilla;
            numero_mama = posicion;
            numero_ex = posi;
            return 1;
            }
            else{
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_mama = new_pos;
            return 1;
            };
            break;
    default: return 0;break;
    };
}

bool max_derecha_ma(int posicion, int casilla){
    int posicion1 = posicion;
    int m_der = pos_derecha(posicion);
    int x = matrix_x(posicion);
    int y = matrix_y(posicion);
    int max_x = matrix_x(m_der);
    int max_y = matrix_y(m_der);
    int posi;

    while(y<8){
        y++;
        posicion = nueva_pos(x, y);
        x = matrix_x(posicion);
        y = matrix_y(posicion);
        if(tablero[posicion]!=0){
            break;
        }
    };

    int cas_ini = cas_ady(posicion1, 2);
    int cas_des = cas_ady(posicion, 2);

    int new_pos = nueva_pos(x, y - 1);

    switch(tablero[posicion]){
    case 0: tablero[posicion1]=0;
            tablero[posicion]=casilla;
            numero_mama = posicion;
            return 1;break;
    case 1: if(cas_ini!=0){
            return 0;
            }else{
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_mama = new_pos;
            return  1;
            };break;
    case 2: tablero[posicion]=casilla;
            numero_mama = posicion;
            return 0;break;
    case 3: if(cas_ini!=0){
            return 0;
            }else{
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_mama = new_pos;
            return 1;
            };break;
    case 4: if(cas_ini!=0 && cas_des!=0){
                return 0;
            }
            else if(matrix_y(posicion)!=8){
            while(y<max_y){
                y++;
            posi = nueva_pos(x, y);
            if(tablero[posi]!=0){
            posi = nueva_pos(x, y - 1);
            break;
            }
            };
            tablero[posicion1]=0;
            tablero[posicion] = casilla;
            tablero[posi]= cas_pret;
            numero_mama = posicion;
            numero_pret = posi;
            return 1;
            }else {
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_mama = new_pos;
            return 1;
            };
            break;
    case 5: if(cas_ini!=0 && cas_des!=0){
                return 0;
            }
            else if(matrix_y(posicion)!=8){
            while(y<max_y){
                y++;
            posi = nueva_pos(x, y);
            if(tablero[posi]!=0){
            posi = nueva_pos(x, y - 1);
            break;
            }
            };
            tablero[posicion1]=0;
            tablero[posi] = cas_exn;
            tablero[posicion]=casilla;
            numero_mama = posicion;
            numero_ex = posi;
            return 1;
            }
            else{
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_mama = new_pos;
            return 1;
            };
            break;
    default: return 0;break;
    };
}

bool max_izquierda_ma(int posicion, int casilla){
    int posicion1 = posicion;
    int m_izq = pos_izquierda(posicion);
    int x = matrix_x(posicion);
    int y = matrix_y(posicion);
    int max_x = matrix_x(m_izq);
    int max_y = matrix_y(m_izq);
    int posi;

    while(y>1){
        y--;
        posicion = nueva_pos(x, y);
        x = matrix_x(posicion);
        y = matrix_y(posicion);
        if(tablero[posicion]!=0){
            break;
        }
    };

    int cas_ini = cas_ady(posicion1, 6);
    int cas_des = cas_ady(posicion, 6);

    int new_pos = nueva_pos(x, y + 1);

    switch(tablero[posicion]){
    case 0: tablero[posicion1]=0;
            tablero[posicion]=casilla;
            numero_mama = posicion;
            return 1;break;
    case 1: if(cas_ini!=0){
            return 0;
            }else{
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_mama = new_pos;
            return  1;
            };break;
    case 2: tablero[posicion]=casilla;
            numero_mama = posicion;
            return 0;break;
    case 3: if(cas_ini!=0){
            return 0;
            }else{
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_mama = new_pos;
            return 1;
            };break;
    case 4: if(cas_ini!=0 && cas_des!=0){
                return 0;
            }
            else if(matrix_y(posicion)!=1){
            while(y>max_y){
                y--;
            posi = nueva_pos(x, y);
            if(tablero[posi]!=0){
            posi = nueva_pos(x, y + 1);
            break;
            }
            };
            tablero[posicion1]=0;
            tablero[posicion] = casilla;
            tablero[posi]= cas_pret;
            numero_mama = posicion;
            numero_pret = posi;
            return 1;
            }else {
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_mama = new_pos;
            return 1;
            };
            break;
    case 5: if(cas_ini!=0 && cas_des!=0){
                return 0;
            }
            else if(matrix_y(posicion)!=1){
            while(y>max_y){
                y--;
            posi = nueva_pos(x, y);
            if(tablero[posi]!=0){
            posi = nueva_pos(x, y + 1);
            break;
            }
            };
            tablero[posicion1]=0;
            tablero[posi] = cas_exn;
            tablero[posicion]=casilla;
            numero_mama = posicion;
            numero_ex = posi;
            return 1;
            }
            else{
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_mama = new_pos;
            return 1;
            };
            break;
    default: return 0;break;
    };
}

bool max_diagderecha_ma(int posicion, int casilla){
    int posicion1 = posicion;
    int m_dider = pos_diagderecha(posicion);
    int x = matrix_x(posicion);
    int y = matrix_y(posicion);
    int max_x = matrix_x(m_dider);
    int max_y = matrix_y(m_dider);
    int posi;

    while(x>1 && y<8){
        x--;
        y++;
        posicion = nueva_pos(x, y);
        x = matrix_x(posicion);
        y = matrix_y(posicion);
        if(tablero[posicion]!=0){
            break;
        }
    };

    int cas_ini = cas_ady(posicion1, 1);
    int cas_des = cas_ady(posicion, 1);

    int new_pos = nueva_pos(x + 1, y - 1);

    switch(tablero[posicion]){
    case 0: tablero[posicion1]=0;
            tablero[posicion]=casilla;
            numero_mama = posicion;
            return 1;break;
    case 1: if(cas_ini!=0){
            return 0;
            }else{
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_mama = new_pos;
            return  1;
            };break;
    case 2: tablero[posicion]=casilla;
            numero_mama = posicion;
            return 0;break;
    case 3: if(cas_ini!=0){
            return 0;
            }else{
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_mama = new_pos;
            return 1;
            };break;
    case 4: if(cas_ini!=0 && cas_des!=0){
                return 0;
            }
            else if(matrix_y(posicion)!=8 && matrix_x(posicion)!=1){
            while(x>max_x && y<max_y){
                x--;
                y++;
            posi = nueva_pos(x, y);
            if(tablero[posi]!=0){
            posi = nueva_pos(x + 1, y - 1);
            break;
            }
            };
            tablero[posicion1]=0;
            tablero[posicion] = casilla;
            tablero[posi]= cas_pret;
            numero_mama = posicion;
            numero_pret = posi;
            return 1;
            }else {
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_mama = new_pos;
            return 1;
            };
            break;
    case 5: if(cas_ini!=0 && cas_des!=0){
                return 0;
            }
            else if(matrix_y(posicion)!=8 && matrix_x(posicion)!=1){
            while(x>max_x && y<max_y){
                x--;
                y++;
            posi = nueva_pos(x, y);
            if(tablero[posi]!=0){
            posi = nueva_pos(x + 1, y - 1);
            break;
            }
            };
            tablero[posicion1]=0;
            tablero[posi] = cas_exn;
            tablero[posicion]=casilla;
            numero_mama = posicion;
            numero_ex = posi;
            return 1;
            }
            else{
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_mama = new_pos;
            return 1;
            };
            break;
    default: return 0;break;
    };
}

bool max_diagizquierda_ma(int posicion, int casilla){
    int posicion1 = posicion;
    int m_dizq = pos_diagizquierda(posicion);
    int x = matrix_x(posicion);
    int y = matrix_y(posicion);
    int max_x = matrix_x(m_dizq);
    int max_y = matrix_y(m_dizq);
    int posi;

    while(x>1 && y>1){
        x--;
        y--;
        posicion = nueva_pos(x, y);
        x = matrix_x(posicion);
        y = matrix_y(posicion);
        if(tablero[posicion]!=0){
            break;
        }
    };

    int cas_ini = cas_ady(posicion1, 7);
    int cas_des = cas_ady(posicion, 7);

    int new_pos = nueva_pos(x + 1, y + 1);

    switch(tablero[posicion]){
    case 0: tablero[posicion1]=0;
            tablero[posicion]=casilla;
            numero_mama = posicion;
            return 1;break;
    case 1: if(cas_ini!=0){
            return 0;
            }else{
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_mama = new_pos;
            return  1;
            };break;
    case 2: tablero[posicion]=casilla;
            numero_mama = posicion;
            return 0;break;
    case 3: if(cas_ini!=0){
            return 0;
            }else{
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_mama = new_pos;
            return 1;
            };break;
    case 4: if(cas_ini!=0 && cas_des!=0){
                return 0;
            }
            else if(matrix_y(posicion)!=1 && matrix_x(posicion)!=1){
            while(x>max_x && y>max_y){
                x--;
                y--;
            posi = nueva_pos(x, y);
            if(tablero[posi]!=0){
            posi = nueva_pos(x + 1, y + 1);
            break;
            }
            };
            tablero[posicion1]=0;
            tablero[posicion] = casilla;
            tablero[posi]= cas_pret;
            numero_mama = posicion;
            numero_pret = posi;
            return 1;
            }else {
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_mama = new_pos;
            return 1;
            };
            break;
    case 5: if(cas_ini!=0 && cas_des!=0){
                return 0;
            }
            else if(matrix_y(posicion)!=1 && matrix_x(posicion)!=1){
            while(x>max_x && y>max_y){
                x--;
                y++;
            posi = nueva_pos(x, y);
            if(tablero[posi]!=0){
            posi = nueva_pos(x + 1, y + 1);
            break;
            }
            };
            tablero[posicion1]=0;
            tablero[posi] = cas_exn;
            tablero[posicion]=casilla;
            numero_mama = posicion;
            numero_ex = posi;
            return 1;
            }
            else{
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_mama = new_pos;
            return 1;
            };
            break;
    default: return 0;break;
    };
}

bool max_diag_abderecha_ma(int posicion, int casilla){
    int posicion1 = posicion;
    int m_abder = pos_diag_abderecha(posicion);
    int x = matrix_x(posicion);
    int y = matrix_y(posicion);
    int max_x = matrix_x(m_abder);
    int max_y = matrix_y(m_abder);
    int posi;

    while(x<8 && y<8){
        x++;
        y++;
        posicion = nueva_pos(x, y);
        x = matrix_x(posicion);
        y = matrix_y(posicion);
        if(tablero[posicion]!=0){
            break;
        }
    };

    int cas_ini = cas_ady(posicion1, 3);
    int cas_des = cas_ady(posicion, 3);

    int new_pos = nueva_pos(x - 1, y - 1);

    switch(tablero[posicion]){
    case 0: tablero[posicion1]=0;
            tablero[posicion]=casilla;
            numero_mama = posicion;
            return 1;break;
    case 1: if(cas_ini!=0){
            return 0;
            }else{
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_mama = new_pos;
            return  1;
            };break;
    case 2: tablero[posicion]=casilla;
            numero_mama = posicion;
            return 0;break;
    case 3: if(cas_ini!=0){
            return 0;
            }else{
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_mama = new_pos;
            return 1;
            };break;
    case 4: if(cas_ini!=0 && cas_des!=0){
                return 0;
            }
            else if(matrix_y(posicion)!=8 && matrix_x(posicion)!=8){
            while(x<max_x && y<max_y){
                x++;
                y++;
            posi = nueva_pos(x, y);
            if(tablero[posi]!=0){
            posi = nueva_pos(x - 1, y - 1);
            break;
            }
            };
            tablero[posicion1]=0;
            tablero[posicion] = casilla;
            tablero[posi]= cas_pret;
            numero_mama = posicion;
            numero_pret = posi;
            return 1;
            }else {
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_mama = new_pos;
            return 1;
            };
            break;
    case 5: if(cas_ini!=0 && cas_des!=0){
                return 0;
            }
            else if(matrix_y(posicion)!=8 && matrix_x(posicion)!=8){
            while(x<max_x && y<max_y){
                x++;
                y++;
            posi = nueva_pos(x, y);
            if(tablero[posi]!=0){
            posi = nueva_pos(x - 1, y - 1);
            break;
            }
            };
            tablero[posicion1]=0;
            tablero[posi] = cas_exn;
            tablero[posicion]=casilla;
            numero_mama = posicion;
            numero_ex = posi;
            return 1;
            }
            else{
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_mama = new_pos;
            return 1;
            };
            break;
    default: return 0;break;
    };
}

bool max_diag_abizquierda_ma(int posicion, int casilla){
    int posicion1 = posicion;
    int m_abizq = pos_diag_abizquierda(posicion);
    int x = matrix_x(posicion);
    int y = matrix_y(posicion);
    int max_x = matrix_x(m_abizq);
    int max_y = matrix_y(m_abizq);
    int posi;

    while(x<8 && y>1){
        x++;
        y--;
        posicion = nueva_pos(x, y);
        x = matrix_x(posicion);
        y = matrix_y(posicion);
        if(tablero[posicion]!=0){
            break;
        }
    };

    int cas_ini = cas_ady(posicion1, 5);
    int cas_des = cas_ady(posicion, 5);

    int new_pos = nueva_pos(x - 1, y + 1);

    switch(tablero[posicion]){
    case 0: tablero[posicion1]=0;
            tablero[posicion]=casilla;
            numero_mama = posicion;
            return 1;break;
    case 1: if(cas_ini!=0){
            return 0;
            }else{
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_mama = new_pos;
            return  1;
            };break;
    case 2: tablero[posicion]=casilla;
            numero_mama = posicion;
            return 0;break;
    case 3: if(cas_ini!=0){
            return 0;
            }else{
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_mama = new_pos;
            return 1;
            };break;
    case 4: if(cas_ini!=0 && cas_des!=0){
                return 0;
            }
            else if(matrix_y(posicion)!=1 && matrix_x(posicion)!=8){
            while(x<max_x && y>max_y){
                x++;
                y--;
            posi = nueva_pos(x, y);
            if(tablero[posi]!=0){
            posi = nueva_pos(x - 1, y + 1);
            break;
            }
            };
            tablero[posicion1]=0;
            tablero[posicion] = casilla;
            tablero[posi]= cas_pret;
            numero_mama = posicion;
            numero_pret = posi;
            return 1;
            }else {
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_mama = new_pos;
            return 1;
            };
            break;
    case 5: if(cas_ini!=0 && cas_des!=0){
                return 0;
            }
            else if(matrix_y(posicion)!=1 && matrix_x(posicion)!=8){
            while(x<max_x && y>max_y){
                x++;
                y--;
            posi = nueva_pos(x, y);
            if(tablero[posi]!=0){
            posi = nueva_pos(x - 1, y + 1);
            break;
            }
            };
            tablero[posicion1]=0;
            tablero[posi] = cas_exn;
            tablero[posicion]=casilla;
            numero_mama = posicion;
            numero_ex = posi;
            return 1;
            }
            else{
            tablero[posicion1] = 0;
            tablero[new_pos] = casilla;
            numero_mama = new_pos;
            return 1;
            };
            break;
    default: return 0;break;
    };
}

bool movimiento_papa(int jugada) {
    int pos;
    if(turno_act() == 2){
        pos = numero_papa;
    }

    int x, y;

    switch (jugada){
    case 0: x=matrix_x(pos);
            y=matrix_y(pos);break;
    case 1: max_arriba(pos, cas_pa);break;
    case 2: max_diagderecha(pos, cas_pa);break;
    case 3: max_derecha(pos, cas_pa);break;
    case 4: max_diag_abderecha(pos, cas_pa);break;
    case 5: max_abajo(pos, cas_pa);break;
    case 6: max_diag_abizquierda(pos, cas_pa);break;
    case 7: max_izquierda(pos, cas_pa);break;
    case 8: max_diagizquierda(pos, cas_pa);break;};
}

bool movimiento_mama(int jugada) {
    int pos, pos1;
    if(turno_act() == 3){
        pos = numero_mama;
        pos1 = numero_mama;
    }

    int x, y;

    switch (jugada){
    case 0: x=matrix_x(pos);
            y=matrix_y(pos);break;
    case 1: max_arriba_ma(pos, cas_ma);break;
    case 2: max_diagderecha_ma(pos, cas_ma);break;
    case 3: max_derecha_ma(pos, cas_ma);break;
    case 4: max_diag_abderecha_ma(pos, cas_ma);break;
    case 5: max_abajo_ma(pos, cas_ma);break;
    case 6: max_diag_abizquierda_ma(pos, cas_ma);break;
    case 7: max_izquierda_ma(pos, cas_ma);break;
    case 8: max_diagizquierda_ma(pos, cas_ma);break;};
}





void turn(){
    system("cls");
    imprimir();
    int jugador = curr_jug();
    int jugada = ranmov();
    int n = 0;
    if(turno_act()==1){
    cout<<"Juega Princesa ";
    cout<<"Turno "<<turno<<endl;
    cout<<"Jugada "<<jugada<<endl;
    while(movimiento_reina(jugada)==0)
    {
        //si la función movimiento_reina devuelve false, suma números a la jugada hasta llegar a 8, si llega a 8 no se mueve.

        jugada++;
        if(jugada>8)
        {
            jugada=0;
        }
    };
    }

    // en cada uno de estos va lo mismo que en el de la reina, sólo que falta crear las funciones de movimiento
    if(turno_act()==2){
    cout<<"Juega Papa ";
    cout<<"Turno "<<turno<<endl;
    cout<<"Jugada: "<<jugada<<endl;
    while(movimiento_papa(jugada)==0)
    {
        //si la función movimiento_reina devuelve false, suma números a la jugada hasta llegar a 8, si llega a 8 no se mueve.

        jugada++;
        if(jugada>8)
        {
            jugada=0;
        }
    };
    }
    if(turno_act()==3){
    cout<<"Juega Mama ";
    cout<<"Turno "<<turno<<endl;
    cout<<"Jugada: "<<jugada<<endl;
        while(movimiento_mama(jugada)==0)
    {
        //si la función movimiento_reina devuelve false, suma números a la jugada hasta llegar a 8, si llega a 8 no se mueve.

        jugada++;
        if(jugada>8)
        {
            jugada=0;
        }
    };

    }
    if(turno_act()==4){
    cout<<"Juega Pretendiente ";
    cout<<"Turno "<<turno<<endl;
    cout<<"Jugada "<<jugada<<endl;
    while(movimiento_pretendiente(jugada)==0)
    {
        //si la función movimiento_reina devuelve false, suma números a la jugada hasta llegar a 8, si llega a 8 no se mueve.

        jugada++;
        if(jugada>8)
        {
            jugada=0;
        }
    };
    }
    if(turno_act()==5){
    cout<<"Juega Exnovio ";
    cout<<"Turno "<<turno<<endl;
    cout<<"Jugada "<<jugada<<endl;
    while(movimiento_exnovio(jugada)==0)
    {
        //si la función movimiento_reina devuelve false, suma números a la jugada hasta llegar a 8, si llega a 8 no se mueve.

        jugada++;
        if(jugada>8)
        {
            jugada=0;
        }
    };
    }
    //me suma un nuevo turno cada vez que se presiona cualquier tecla de flecha
    turno++;

    while(getch()!=224);

    //si el turno es menor a 10, sigue ejecutando, sino termina y debe mostrar si la princesa fue conquistada o no.
    //(Falta crear función)


        if(reina[0] == -1) {
        system("cls");
        imprimir();
        cout<<"Fin. Princesa Conquistada."<<endl;
        system("pause");
        exit(0);
        }
        else if(turno<=50)
        {
            turn();
        }
        else{
        system("cls");
        imprimir();
        cout<<"Fin. Princesa No conquistada."<<endl;
        system("pause");
        exit(0);
        }


}



int main() {
    initab();
    iniciar_jug();
    imprimir();
    turn();
}

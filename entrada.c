#include "organizador_academico.h"

char leerLetra()
{

    char buf[8];
    char tecla = '\0';


#ifdef _WIN32
    int ch;

    while (tecla == '\0')
    {
        ch = _getch();

        if (ch == 0 || ch == 224)   //Teclas especiales (flechas)
        {

        }else if(ch == '\b'){
        tecla = 127;
        }
        else if (ch == 13) //Tecla Enter
        {
        tecla = '\n';
        }else if(ch == 27)  //Tecla ESC
        {
        tecla = 27;
        }
        else if (ch >= 65 && ch <= 122 || ch == ' ')  //LETRAS
        {
        tecla = ch;
        }

    }

#else
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");

	while(tecla == '\0')
	{

        int n = read(0, buf, 1);
        if (n > 0) {
        if (buf[0] == 27) { // ESC key detected

            int flags = fcntl(0, F_GETFL, 0);
            fcntl(0, F_SETFL, flags | O_NONBLOCK);

            // Try to read more bytes (e.g., if an arrow key was pressed, '[' and 'A' are waiting)
            int n_extra = read(0, buf + 1, sizeof(buf) - 1);
            fcntl(0, F_SETFL, flags);

            if (n_extra <= 0)
            {
                //printf("Result: Standalone ESC key pressed instantly!\n");
                tecla = buf[0];
            }else{
                // Extra bytes exist, meaning it's an escape sequence (like an arrow key)
                //printf("Result: Escape sequence detected (Length: %d)\n", n_extra + 1);
                // buf[1] will typically be '[', and buf[2] will be 'A', 'B', 'C', or 'D'
            }
        	}
        	else if(buf[0] >= 65 && buf[0] <= 122){   //LETRAS
            	tecla = buf[0];
        	}
        	else if(buf[0] == '\n' || buf[0] == 127 || buf[0] == ' '){
        	tecla = buf[0];
        	}
     			}
    }

    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror ("tcsetattr ~ICANON");
#endif

    return tecla;

}

char leerTecla()
{

    char buf[8];
    char tecla = '\0';


#ifdef _WIN32
    int ch;

    while (tecla == '\0')
    {
        ch = _getch();

        if (ch == 0 || ch == 224)   //Teclas especiales (flechas)
        {
            int arrow = _getch();
            switch (arrow)
            {
                case 72:
                tecla = 'A';
                break;

                case 80:
                tecla = 'B';
                break;

                case 77:
                tecla = 'C';
                break;

                case 75:
                tecla = 'D';
                break;

            }
        }else if(ch == '\b')
        {
        tecla = 127;
        }else if (ch == 13) //Tecla Enter
        {
        tecla = '\n';
        }
        else if(ch == 27)  //Tecla ESC
        {
        tecla = 27;
        }
        else if (ch == 'A' || ch == 'B' || ch == 'C' || ch == 'D')
        {}
        else    //Cualquier otra tecla
        {
        tecla = ch;
        }

    }

#else
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");

        int n = read(0, buf, 1);
        if (n > 0) {
        if (buf[0] == 27) { // ESC key detected

            int flags = fcntl(0, F_GETFL, 0);
            fcntl(0, F_SETFL, flags | O_NONBLOCK);

            // Try to read more bytes (e.g., if an arrow key was pressed, '[' and 'A' are waiting)
            int n_extra = read(0, buf + 1, sizeof(buf) - 1);
            fcntl(0, F_SETFL, flags);

            if (n_extra <= 0)
            {
                //printf("Result: Standalone ESC key pressed instantly!\n");
                tecla = buf[0];
            }else {
                // Extra bytes exist, meaning it's an escape sequence (like an arrow key)
                //printf("Result: Escape sequence detected (Length: %d)\n", n_extra + 1);
                // buf[1] will typically be '[', and buf[2] will be 'A', 'B', 'C', or 'D'
                tecla = buf[2];
            }
        }else if(tecla == 'A' || tecla == 'B' || tecla == 'C' || tecla == 'D'){}
        else{   //Cualquier otra tecla
            tecla = buf[0];
        }
    }

    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror ("tcsetattr ~ICANON");
#endif

    return tecla;

}

bool leerContrasena(char cadena[], bool ocultar, size_t lon_cadena, int x, int y)
{
    char tecla;
    gotoxy(x, y);
    fflush(stdout);


    unsigned int i = 0;
    while(true)
    {
        tecla = leerTecla();

        if(tecla == 27) { // ESC para cancelar
            cadena[0] = '\0';
            return true;
        }
        else if(tecla == 127) {
            if(strlen(cadena) > 0 && i > 0)
            {
                // Limpiamos el área ocupada actualmente en pantalla
                limpiar_area(x, y, i, 1);

                i--;
                cadena[i] = '\0';

                gotoxy(x, y);
                if(ocultar)
                {
                    for(unsigned int j = 0; j < i; j++) {   printf("*");   }
                } else
                {
                    printf("%s", cadena);
                }
                fflush(stdout);
            }
        }
        else if(tecla == '\n' ) {    if(i > 0) break;   }
        else{
            if(i < lon_cadena - 1)
            {
                cadena[i] = tecla;
                cadena[i + 1] = '\0';

                if(ocultar) {
                    printf("*");
                } else {
                    printf("%c", tecla);
                }
                fflush(stdout);
                i++;
            }
        }
    }

    return false; // Retorna false si finalizó con Enter de forma normal
}

bool leerTexto(char cadena[], size_t lon_cadena, size_t margen, int x, int y)
{
  char tecla;
  gotoxy(x,y);
  fflush(stdout);

  unsigned int i = 0;
  while(true)
  {
  	tecla = leerLetra();

  	if(tecla == 27){

  	cadena[0] = '\0';
  	return true;

  	}
  	else if(tecla == 127){
  		if(strlen(cadena) > 0 && i > 0)
  		{
  		cadena[i-1] = '\0';

  		if(i >= margen)
  		{
  		limpiar_area(x,y + (i/margen), margen,1);
  		gotoxy(x, y + (i/margen));
  		printf ("%s", &(cadena[i - (i%margen)]));
  		}else{
  		limpiar_area(x,y, strlen(cadena) + 2,1);
  		gotoxy(x,y);
  		printf("%s", cadena);
  		}

  		fflush(stdout);
  		i--;
  		}
  	}
  	else if(tecla == '\n'){

    if(i > 2)
        return false;

  	}else{
  		if(i < lon_cadena-1)
  		{
  			cadena[i] = tecla;
            cadena[i + 1] = '\0';

            if(i >= margen && (i % margen == 0))
            {
            gotoxy(x, y + (i / margen));
            }

            printf("%c", tecla);
            fflush(stdout);
            i++;
  		}
  	}

  }

  return false;
}

bool pregunta()
{
    bool datoIncorrecto = false;
    char op = '\0';

    do
    {

    op = leerTecla();  //Lee el valor hasta que sea correcto
    op = toupper(op);

        switch(op)
        {
            case 'N':
                return false;
            break;

            case 'S':
                return true;
            break;

            default:
            datoIncorrecto = true;
            break;
        }

    }while(datoIncorrecto); //Validador

    return false;
}

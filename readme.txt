El programa crea un archivo horarios.csv organizando las entradas del usuario y correspondientes a su horario académico

Versión 0.2.1

Funcionamiento:
El programa primero verificará si ya existe un archivo "horarios.csv", esto a través de la función "leerArchivo". En caso de que el archivo ya exista el programa lo lee y muestra en pantalla, entonces se pide una confirmación al usuario de que ese horario sea el correcto. En caso de que el archivo no exista se le notifica al usuario y el programa  procede a pedir los horarios desde 0:

La función "main" en el archivo "main.c" se encarga de recibir la entrada de datos del usuario. Primero se pide el horario:
El programa le dará al usuario la opción de introducir cada hora manualmente, o introducir sólo las dos primeras horas y automáticamente calcular las demás. Estos datos se almacenan en un arreglo bidimensional llamado "hora"

Posteriormente el programa pedirá al usuario el número de clases correspondientes a cada día de la semana, y el usuario deberá introducir primero la clase que corresponde a la primera hora del primer dia, luego el programa pedirá qué horario tiene esta primera clase dependiendo del horario que el usuario introdujo anteriormente, después se realiza lo mismo con el segundo dia, y así cíclicamente hasta completar los 5 dias de la semana. Todas las asignaturas introducidas se almacenan en un arreglo bidimensional llamado "materias"

Entonces el programa llama a la función "formatearArchivo" del archivo "crearHorario.c". Esta funcion procesa los datos introducidos por el usuario y crea le archivo: "horarios.csv". El formato será:
Cabecera(Horarios,Lunes,Martes,...) esto es constante 
HORA,MATERIA1,MATERIA2,MATERIA3...

Detalles técnicos:

Las macros "TAM_MATERIAS" y "TAM_HORAS" tienen el valor máximo de sus respectivos arreglos, "materias" y "horas". Esto hace el programa más modular, ya no se utiliza la macro "sizeof" de versiones anteriores, sino que se cambia el valor de la macro en cada archivo cuando se quiere realizar un cambio.

Por otro lado, se puede observar que en la mayoría de funciones los arreglos son llamados con la palabra "const", esto es para evitar que los datos sean modificados por una función que no debería, la lectura de datos por ahora se realiza sólo en la función "main". La única excepción a la regla es la función "calcHora", que altera los valores del arreglo "hora"



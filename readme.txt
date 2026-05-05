El programa crea un archivo horarios.csv organizando las entradas del usuario y correspondientes a su horario académico

Versión 0.1
Primera version funcional del programa organizador académico

Funcionamiento:
La función "main" en el archivo "main.c" se encarga de recibir la entrada de datos del usuario. El programa pedirá al usuario una hora específica, esto cíclicamente hasta que el usuario haya introducido 7 horas académicas. Esta información se almacena en un arreglo de cadenas unidimensional.

Posteriormente el programa pedirá al usuario el número de clases correspondientes a cada día de la semana, y el usuario deberá introducir primero la clase que corresponde a la primera hora del primer dia y presionar enter, luego la clase que corresponde a la segunda y presionar enter, después se realiza lo mismo con el segundo dia, así cíclicamente hasta completar los 5 dias de la semana. Todas las asignaturas introducidas se almacenan en un arreglo bidimensional llamado "materias"

Entonces el programa llama a la función "formatearArchivo" del archivo "crearHorario.c". Esta funcion procesa los datos introducidos por el usuario y crea le archivo: "horarios.csv". El formato será:
Cabecera(Horarios,Lunes,Martes,...) esto es constante 
HORA,MATERIA1,MATERIA2,MATERIA3...

Detalles técnicos:

El lenguaje C no contiene una función preescrita para obtener el tamaño de un arreglo (después de todo los arreglos en C tienen su tamaño definido al tiempo de compilación), la función "sizeof()" sólo nos da el tamaño en bytes de nuestro arreglo completo, eso cuando le damos como parámetro un arreglo. Cuando le pasamos una variable a esta misma función obtenemos el tamaño en bytes de esta misma variable. Al dividir el tamaño del arreglo por el de una variable cualquiera de ese arreglo, tenemos el tamaño de ese arreglo como tal. Esa es la explicación de las órdenes de preprocesador (macros) "ARRAY_LENGTH" y "ARRAY_COLS". 





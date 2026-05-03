El programa crea un archivo horarios.csv organizando las entradas del usuario y correspondientes a su horario académico

Primero el programa por cada día de la semana pedirá al usuario el número de materias que le corresponde, luego, una hora y posteriormente los minutos correspondientes a esa hora, y al final se le pide el nombre de la materia correspondiente a esa hora, este proceso se repite hasta que el usuario introduce todas las materias que indicó corresponden a ese día. Repitiendo el proceso para todos los días de la semana

Versión 1.0
Primera version funcional del programa organizador académico

Funcionamiento:
La función "main" en el archivo "main.c" se encarga de recibir la entrada de datos del usuario. El programa pedirá al usuario una hora y unos minutos específicos correspondientes a esa hora, esto cíclicamente hasta que el usuario haya introducido 10 horas académicas.

Posteriormente el programa pedirá al usuario el número de clases correspondientes a cada día de la semana, y el usuario deberá introducir primero la clase que corresponde a la primera hora y presionar enter, luego la clase que corresponde a la segunda y presionar enter, así sucecivamente hasta completar los 5 dias de la semana.

Esta información se guardará en un archivo "temps.txt", un archivo temporal que el programa utilizará para leer los datos introducidos por el usuario, es el archivo para más fácil lectura por parte del programa. El formato será:
DIA,MATERIA1,HORA1,MATERIA2,HORA2...

Entonces el programa llama a la función "leerArchivo" del archivo "crearHorario.c", la cual se encarga de leer y el arhivo "temps.txt" completo y guardar los datos ordenados en dos arreglos: "hora" y "materias".

La misma función leerArchivo llama a la función formatearArchivo, esta última crea y escribe un archivo "horarios.csv" que es una versión ordenada de los horarios que el usuario introdujo al principio del programa, un archivo que debería poder abrirse con excel y tener un formato muy parecido al de cualquier horario académico convencional.

Detalles técnicos:
Primero, como es evidente, hay una función sin utilizar en el arhivo "main.c" llamada "preguntarHorario". Esta función falta implementarla pero responde a la cuestión de que algunas materias o asignaturas tienen más de una hora académica asignada seguidamente en el día que les corresponde.

El lenguaje C no contiene una función preescrita para obtener el tamaño de un arreglo (después de todo los arreglos en C tienen su tamaño definido al tiempo de compilación), la función "sizeof()" sólo nos da el tamaño en bytes de nuestro arreglo completo, eso cuando le damos como parámetro un arreglo. Cuando le pasamos una variable a esta misma función obtenemos el tamaño en bytes de esta misma variable. Al dividir el tamaño del arreglo por el de una variable cualquiera de ese arreglo, tenemos el tamaño de ese arreglo como tal. Esa es la explicación de las órdenes de preprocesador (macros) "ARRAY_LENGTH" y "ARRAY_COLS". 

Luego, en la función "leerArchivo" del archivo "crearHorario.c", tenemos mucho que explicar. Primero, la función tiene como argumento una cadena de carácteres, esto está en caso de realizar un cambio de nombre a futuro del archivo "temps.txt" no se tenga que cambiar todo el código (Quizás deberíamos crear una constante que contenga el nombre del archivo...), también podría servir a futuro por si esa misma función nos servirá para leer otro archivo.
La variable "buffer" almacena el contenido de todo el archivo que la función lee usando la función fgets. Las variables "i" y "j" son contadores utilizados para trabajar con los arreglos y llevar cuenta del número de filas o columnas.
El ciclo primer "while" que vemos en esa función lo que hace es leer todo el archivo (o copiarlo a la variable buffer), hasta que se encuentra el final del archivo. 
La variable token va a almacenar los diferentes "tokens" del archivo, es decir, todos los "campos" que están delimitados por comas y saltos de línea.
Esta variable va a almacenar cada ciclo, el valor o la cadena que se encontró en ese campo, destruyendo o convirtiendo a NULL los valores que va leyendo. Por ejemplo, al principio de cada fila va a almacenar el valor del día que corresponde a esa fila (Lunes, Martes, etc.) Y estos valores (especialmente los de los horarios y materias) se almacenan en sus arreglos globales correspondientes, "Hora" y "Materias". Para posteriormente ser usados por la función formatearArchivo.  




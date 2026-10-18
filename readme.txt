El programa crea un archivo horarios.csv organizando las entradas del usuario y correspondientes a su horario académico.
También permite introducir actividades académicas con su fecha correspondiente. Y posteriormente exportar estas actividades en un archivo de actividades semanal

Versión 0.5.0

Funcionamiento:
El programa primero verificará si ya existe un archivo "horarios.csv", esto a través de la función "leerArchivo". En caso de que el archivo ya exista el programa lo lee y continua. En caso de que el archivo no exista se le notifica al usuario y el programa  procede a pedir los horarios desde 0:

La función "main" en el archivo "main.c" se encarga de recibir la entrada de datos del usuario. Primero se pide el horario:

El programa pedirá al usuario el número de clases correspondientes a cada día de la semana, y el usuario deberá introducir primero la clase que corresponde a la primera hora del primer dia, luego el programa pedirá qué horario tiene esta primera clase, después se realiza lo mismo con el segundo dia, y así cíclicamente hasta completar los 5 dias de la semana. Todas las asignaturas introducidas se almacenan en un arreglo bidimensional llamado "materias". Este mismo arreglo es el que se guarda tal cual en el archivo "horarios.csv"

Entonces el programa llama a la función "formatearArchivo" del archivo "archivos.c". Esta funcion procesa los datos introducidos por el usuario y crea le archivo: "horarios.csv". El formato será:
Horarios,Lunes,Martes,... <--- Esto es la cabecera, es constante 
HORA1-HORA2,MATERIA1,MATERIA2,MATERIA3...
HORA2-HORA3,MATERIA4,MATERIA5,MATERIA6...
...

Dentro del menú principal el usuario tiene múltiples opciones:
		[Exportar archivo de actividades semanal]
-Le da al usuario dos opciones, "Semana Actual" o "Semana Proxima" (Además de la opción de salir). Dependiendo de esto crea un archivo llamado "Actividades Semanales.txt" donde se le da un formato a las actividades que el estudiante tiene esa semana, ordenandolas por materias, por día de la semana, etc.
		[Menú Calendario]
-Le da al usuario dos opciones "Ver calendario para este mes" o "Ver calendario para otro mes". 
El usuario selecciona el mes y se muestra en la parte derecha de la pantalla el mes correspondiente, con colores indicando en qué fecha hay una actividad. Debajo de este calendario aparecen las actividades y su materia correspondiente, remarcadas con el color que les corresponde. Si el mes está muy ocupado, el usuario puede presionar las flechas direccionales para ver todas las actividades que hay en el mes.
No se puede seleccionar un mes en el pasado
		[Modificar materias para este dia]
-Esta opcion se utiliza para actualizar las asignaturas que hay en un dia de la semana en particular, se le pide una confirmacion al usuario porque esto elimina todo lo que había guardado en ese día para poder hacer los cambios
		[Menú de actividades]
(Esta opción sólo es visible cuando se selecciona una casilla con una materia válida, y no funciona cuando se presiona un día de la semana)
Despliega un menú con dos opciones: "Introducir nueva actividad" o "Eliminar una actividad"
	{Introducir nueva actividad}
-Pedirá al usuario el nombre de esta actividad, y posteriormente la fecha.
	{Eliminar una actividad}
-Despliega un menu con todas las actividades guardadas para esa materia. Y el usuario selecciona cual desea eliminar

Detalles técnicos:

Las macros "TAM_MATERIAS" y "DIAS_SEM" tienen el valor máximo de sus respectivos arreglos, "materias" y "horas". Esto hace el programa más modular, ya no se utiliza la macro "sizeof" de versiones anteriores, sino que se cambia el valor de la macro en cada archivo cuando se quiere realizar un cambio.
Estas dos macros mencionadas definen el tamaño del arreglo "materias", donde la cantidad de columnas viene dada por los dias de la semana (Deberían ser 5 o 7) y las filas por la cantidad de horas máximas guardadas

Luego tenemos los arreglos "tareas" y "tareaFecha". El primero tiene un tamaño definido en la macro "TAM_MATERIA_TAREAS," dependiendo de la cantidad de materias posibles que haya. En este caso, se definió como si un cuarto de todas las casillas contivueran una asignatura distinta. Esto es para las filas.
Las columnas de este arreglo se definen con una macro más sencilla "TAM_TAREA" para un máximo de 10 actividades que se pueden registrar POR CADA MATERIA
Además, el arreglo tareas está diseñado para almacenar en su primer índice, siempre, a la materia que corresponde a todas las demás actividades. Es decir, la primera fila siempre está reservada para el nombre de las materias
El arreglo "tareaFecha" toma esto en cuenta para su estructura, como en él no se guarda el nombre de la materia, se utiliza el mismo tamaño que el el arreglo "tareas", pero a las columnas se les resta 1. Además este es un arreglo de estructuras. Donde se guardan todos los datos de una fecha en particular, en sus atributos "dia", "mes" y "ano"
(Para entender la estructura de los datos con más claridad, ver los diagramas)

Por otro lado, se puede observar que en la mayoría de funciones los arreglos son llamados con la palabra "const", esto es para evitar que los datos sean modificados por una función que no debería, la lectura de datos por ahora se realiza sólo en la función "main".

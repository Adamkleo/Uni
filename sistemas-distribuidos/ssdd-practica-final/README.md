Para compilar y ejecutar la aplicación en el puerto de preferencia(en este ejemplo 8080) los pasos son los siguientes:

1- Ejecutar comando make en la carpeta root del proyecto
2- Comenzar el servidor webservice con el comando: python3 ws-time.py
3- Iniciar servidor rpc con el comando: ./servidor_rpc
4- Iniciar servidor principal con el comando: ./servidor 8080.
5- Iniciar cliente de python con el comando: python3 client.py -s localhost -p 8080

Si se quiere ejecutar en otro puerto, se debe cambiar 8080 por el otro número de puerto escogido.

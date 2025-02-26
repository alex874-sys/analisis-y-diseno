#Funcion para verificar si es un palindromo, recibe un parametro
def es_palindromo_num(num):

    #convertinos el argumento o valor ingresado por el usuario a cadena de caracteres.
    cadena = str(num)

    #guardamos el resultado de comparar si la cadena es igual a la cadena inversa.
    es_palindromo = (cadena == cadena[::-1])

    #devolvemos el la variable que contiene la resuesta de si es o no un palindromo.
    return es_palindromo


#Solicitamos un numero al usuario
num = int(input("Ingresa un numero: "))
#mostramos el resultado despues de aber llamado a la funcion y haber mandado el argumento
print("Es palindromo", es_palindromo_num(num))
print("fin del programa...")
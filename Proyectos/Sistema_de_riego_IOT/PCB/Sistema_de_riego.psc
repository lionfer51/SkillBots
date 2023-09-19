Función regar
	res <- ''
FinFunción

Función dejarDeRegar
	res <- ''
FinFunción

Función leerInformacionServidor
res <- ''
FinFunción

Función accionarBomba
	res <- ''
FinFunción

Función res <- enviar(a,b,c)
	Definir res Como Real
	res <- a+b+c
FinFunción

Algoritmo Sistema_de_riego
	Definir hora, temperatura, humedad Como Entero
	Definir horario_servidor Como Entero
	Definir estadoh Como Entero
	Definir estado_sistema Como Cadena
	Definir encendido Como Entero
	Definir comp Como Entero
	Definir limite Como Entero
	encendido <- 1
	horario_servidor <- 0
	Mientras encendido==1 Hacer
		Leer estado_sistema
		Leer horario_servidor
		Leer estadoh
		Leer hora
		Leer temperatura
		Leer humedad
		Leer limite
		leerInformacionServidor
		Si estado_sistema=='Manual' Entonces
			Mientras estadoh==1 Y humedad<limite Hacer
				regar()
			FinMientras
		SiNo
			Si humedad<limite Entonces
				regar()
				Escribir (enviar(hora,temperatura,humedad))
			SiNo
				dejarDeRegar()
				Escribir (enviar(hora,temperatura,humedad))
			FinSi
		FinSi
	FinMientras
FinAlgoritmo

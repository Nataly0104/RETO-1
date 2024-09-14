Sistema de Adquisición y Análisis de Señales con Arduino
Este proyecto implementa un sistema embebido que captura señales analógicas utilizando un Arduino UNO. El sistema permite:

#Iniciar/Detener la adquisición#: La captura de datos se controla mediante pulsadores.
Análisis de Señales: El sistema calcula y muestra en una pantalla LCD:
Frecuencia (Hz)
Amplitud (V)
Forma de onda (senoidal, triangular, cuadrada, etc.)
Características Principales
Manejo de Interrupciones: Pulsadores controlan el inicio, pausa y análisis de la señal.
Procesamiento de Señales: Algoritmos para calcular frecuencia, amplitud e identificar la forma de onda.
Visualización de Datos: Resultados mostrados en una pantalla LCD.
Uso de C++ Avanzado: Implementación con punteros, arreglos y memoria dinámica.


Descripción del Diagrama de Flujo

Inicio: El programa comienza su ejecución.
Configuración Inicial:
Inicializa la pantalla LCD.
Configura los pines de los botones y del generador de señales.
Esperar Acción del Usuario:
Botón de Inicio Presionado:
Comienza la adquisición de datos.
Lee datos del pin analógico y almacena en el buffer.
Si el buffer está lleno o se detiene la adquisición, pasa al siguiente paso.
Botón de Información Presionado:
Procesa la información (frecuencia, amplitud, forma de onda).
Muestra la información en la pantalla LCD.
Identificar Forma de Onda:
Analiza los datos almacenados en el buffer.
Identifica la forma de onda (pulso, triangular, cuadrada, desconocida).
Mostrar Resultados:
Muestra la frecuencia, amplitud, y forma de onda en la pantalla LCD.
Reanudar Adquisición:
Continúa la adquisición de datos si fue pausada.
Fin: El proceso se repite continuamente.

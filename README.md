# PROYECTO 1, INFORMATICA II, 

# Adquisición y Análisis de Señales con Arduino

Este proyecto implementa un sistema de adquisición y análisis de señales analógicas utilizando una placa Arduino, dos pulsadores y una pantalla LCD. El sistema permite:

* **Adquirir datos:** Muestrea una señal analógica desde un pin analógico y almacena los datos en un buffer circular.
* **Analizar la señal:** Calcula la frecuencia, amplitud y forma de onda de la señal adquirida.
* **Visualizar resultados:** Muestra los resultados del análisis en una pantalla LCD.
* **Interactuar con el usuario:** Utiliza dos pulsadores para controlar el inicio/detención de la adquisición y la visualización de la información.
## Librerías

*   `LiquidCrystal.h`: Para controlar la pantalla LCD.

*   
## Componentes

*   Arduino UNO
*   Pantalla LCD 16x2
*   2 Pulsadores
*   Oscilador (para generar la señal de entrada)
*   Resistencias y cables de conexión

 ## Configuración

*  Se desarrollara el proyecto arduino en la plataforma tinkercad  ( Link acceso a la simulacion : [https://www.tinkercad.com/things/kmmxLiCjEbQ-shiny-blad/editel](https://www.tinkercad.com/things/kmmxLiCjEbQ-shiny-blad)
   ![image](![image](https://github.com/user-attachments/assets/468f2f1c-8a33-441e-a20c-b7e1de3a6297)
   
* Esquema del curcuito : ![image](https://github.com/user-attachments/assets/54f7bfb8-1d1a-4898-915c-f37f1684248f)


## Características principales

* **Adquisición de datos eficiente:** Utiliza un buffer circular para almacenar los datos de la señal, lo que optimiza el uso de memoria y evita reasignaciones costosas.
* **Análisis de señal robusto:** Implementa un cálculo de frecuencia basado en autocorrelación y una Transformada Discreta de Fourier (DFT) simple para obtener un análisis de frecuencia más preciso.
* **Identificación de forma de onda mejorada:** Utiliza criterios combinados basados en el ciclo de trabajo, la simetría y el espectro de frecuencias para identificar la forma de onda con mayor precisión.
* **Manejo de errores:** Incluye verificaciones para evitar posibles fallos, como la falta de memoria al asignar el buffer.
* **Interfaz de usuario sencilla:** Permite al usuario iniciar/detener la adquisición y visualizar los resultados mediante dos pulsadores.

* **El código presentado utiliza memoria dinámica a través de la función malloc() para asignar espacio en tiempo de ejecución para el buffer circular signalBuffer. Este enfoque tiene ventajas y desventajas en el contexto de este software:

* **Ventajas:

* **Flexibilidad: La memoria dinámica permite ajustar el tamaño del buffer en tiempo de ejecución, lo que podría ser útil si el tamaño de la señal a analizar varía.
Eficiencia: En escenarios donde el tamaño máximo del buffer es grande pero no siempre se utiliza por completo, la memoria dinámica puede ser más eficiente que reservar un buffer estático de tamaño fijo, lo que podría desperdiciar memoria


## Hardware requerido

* Placa Arduino (compatible con la biblioteca LiquidCrystal)
* Pantalla LCD 16x2
* 2 pulsadores
* Resistencias pull-up (o utilizar las resistencias pull-up internas de la placa Arduino)
* Cables de conexión

## Instalación

1. Clona este repositorio en tu entorno de desarrollo de Arduino.
2. Asegúrate de tener instalada la biblioteca `LiquidCrystal`. Si no la tienes, puedes instalarla desde el Administrador de Bibliotecas de Arduino.
3. Conecta los componentes de hardware según el diagrama del circuito (incluir diagrama o descripción del circuito si es posible).
4. Carga el código en tu placa Arduino.

## Funciones principales

### `setup()`

* **Propósito:** Configura los pines de entrada y salida, inicializa la comunicación serial y la pantalla LCD.
* **Acciones:**
    * Configura los pines de los botones como entradas con resistencias pull-up internas.
    * Inicializa la comunicación serial a 9600 baudios para depuración.
    * Inicializa la pantalla LCD y muestra un mensaje de bienvenida.

### `loop()`

* **Propósito:** Bucle principal del programa, lee los botones, gestiona el antirrebote y controla la adquisición y visualización de datos.
* **Acciones:**
    * Lee el estado de los botones de inicio y visualización.
    * Implementa antirrebote para evitar lecturas erróneas de los botones.
    * Si se presiona el botón de inicio, llama a `startAcquisition()` para comenzar la adquisición de datos.
    * Si se presiona el botón de información, llama a `showInformation()` para mostrar los resultados del análisis.
    * Si la adquisición está activa (`isAcquiring` es verdadero), llama a `acquireData()` para continuar adquiriendo muestras.

### `startAcquisition()`

* **Propósito:** Inicia la adquisición de datos de la señal analógica.
* **Acciones:**
    * Si la adquisición no está activa:
        * Establece la bandera `isAcquiring` en `true`.
        * Guarda el tiempo de inicio en `startTime`.
        * Reinicia el buffer circular (`bufferHead` y `bufferCount`).
        * Muestra un mensaje en la pantalla LCD indicando que se está adquiriendo.

### `acquireData()`

* **Propósito:** Adquiere una muestra de la señal analógica y la almacena en el buffer circular.
* **Acciones:**
    * Si la adquisición está activa:
        * Lee una muestra del pin analógico y la almacena en el buffer circular en la posición indicada por `bufferHead`.
        * Avanza `bufferHead` al siguiente espacio disponible en el buffer circular.
        * Incrementa `bufferCount` si el buffer aún no está lleno.

### `showInformation()`

* **Propósito:** Detiene la adquisición, analiza la señal y muestra los resultados en la pantalla LCD y el monitor serial.
* **Acciones:**
    * Detiene la adquisición estableciendo `isAcquiring` en `false`.
    * Verifica si hay suficientes muestras en el buffer para realizar el análisis.
    * Si hay suficientes muestras:
        * Llama a `analyzeSignal()` para analizar la señal.
        * Imprime los resultados (frecuencia, amplitud y forma de onda) en el monitor serial.
        * Muestra los resultados en la pantalla LCD, utilizando la clase `F()` para optimizar el uso de memoria.
    * Si no hay suficientes muestras, muestra un mensaje de error en la pantalla LCD.

### `analyzeSignal()`

* **Propósito:** Analiza la señal adquirida para calcular su frecuencia, amplitud y forma de onda.
* **Acciones:**
    * **Cálculo de frecuencia:** Utiliza la autocorrelación para encontrar el retardo donde la señal se repite y estima la frecuencia fundamental.
    * **Manejo de señales constantes o con poca variación:** Asigna una frecuencia de 0 y la forma de onda "Desconocida" si la señal no tiene una frecuencia clara.
    * **Cálculo de amplitud:** Calcula la amplitud pico a pico de la señal.
    * **Cálculo de ciclo de trabajo y simetría:** Calcula el ciclo de trabajo y la simetría de la señal.
    * **Transformada Discreta de Fourier (DFT):** Calcula el espectro de frecuencias hasta el quinto armónico.
    * **Identificación de forma de onda:** Utiliza criterios combinados basados en el ciclo de trabajo, la simetría y el espectro de frecuencias para identificar la forma de onda (cuadrada, triangular, sinusoidal o desconocida).

## Consideraciones

* El tamaño del buffer circular (`BUFFER_SIZE`) puede ajustarse según las necesidades de la aplicación y la memoria disponible en la placa Arduino.
* Los umbrales utilizados para la identificación de la forma de onda pueden requerir ajustes dependiendo de las características de las señales que se estén analizando.
* La implementación de la DFT es básica y puede no ser eficiente para señales muy largas o complejas. Si el rendimiento es crítico, considera utilizar una biblioteca de FFT optimizada.

¡Espero que esta documentación te sea útil! Si tienes alguna otra pregunta o necesitas más detalles sobre alguna parte del código, no dudes en preguntar.    

## Uso

1. Presiona el botón de "Inicio" para comenzar la adquisición de la señal.
2. Una vez finalizada la adquisición, presiona el botón de "Información" para visualizar los resultados del análisis en la pantalla LCD.
3. Los resultados también se imprimirán en el monitor serial para fines de depuración.

## Mejoras potenciales

* **Implementar una FFT optimizada:** Si el rendimiento es crítico, considera utilizar una biblioteca de FFT optimizada para un análisis de frecuencia más eficiente.
* **Añadir más criterios de identificación de forma de onda:** Explorar otras características de la señal, como el factor de cresta y el número de cruces por cero, para mejorar aún más la precisión de la identificación.
* **Ampliar la interfaz de usuario:** Agregar más información en la pantalla LCD, como gráficos de la señal o opciones de configuración.

## Contribuciones

¡Las contribuciones son bienvenidas! 

# PROYECTO 1, INFORMATICA II, 
## Proyecto de Adquisición y Análisis de Señales con Arduino

Este   tiene como objetivo  afianzar conceptos de programacion, logica de programacion, memoria dinamica, apuntadores( temas tratados en el modulo uno del curso) mediante  la implementacion en un proyecto desarollo basado en arduino y programado en C++ por medio  requerimientos tecniproyecto de implentacion,sistemas de control de versiones. El proyecto busca implementar un sistema que captura una señal analógica utilizando un Arduino, analiza sus características principales (frecuencia, amplitud y forma de onda), en base a estos datos, analiza e indica el tipo de onda y muestra los resultados en una pantalla LCD.

## Componentes

*   Arduino UNO
*   Pantalla LCD 16x2
*   2 Pulsadores
*   Oscilador (para generar la señal de entrada)
*   Resistencias y cables de conexión

## Funcionamiento

1.  **Inicio de la Adquisición:** Al presionar el pulsador de inicio, el sistema comienza a capturar la señal analógica y a almacenarla en un buffer en memoria dinámica.
2.  **Solicitud de Información:** Durante la adquisición, al presionar el pulsador de información, el sistema detiene temporalmente la captura, analiza la señal almacenada en el buffer y muestra los resultados (frecuencia, amplitud y forma de onda) en la pantalla LCD. Luego, reanuda la adquisición.

## Librerías

*   `LiquidCrystal.h`: Para controlar la pantalla LCD.

## Configuración

*  Se desarrollara el proyecto arduino en la plataforma tinkercad  ( Link acceso a la simulacion : https://www.tinkercad.com/things/0TnMxwyEGkg-bodacious-blad-bigery?sharecode=9QuFo_c_Os2HSAmafJ_z2uq_OlcXhcfT2o_cNjJYWlo)
   ![image](https://github.com/user-attachments/assets/696a9af4-038c-4370-98f6-4fa09b0999e7)
*   Ajustar el tamaño del buffer (`tamañoBuffer`) según la longitud de la señal que deseas capturar, en este caso seran 1024( Este valor de 1024 permite capturar un espacio importante de información de las señales,  sin completer una proporcion significativa del tamayo del arduino.
*   
## Algoritmo Generalizado 

*   Implementar la lectura de la señal analógica en la función `loop()`.
*   Implementar los algoritmos de análisis en la función 
*   Implementar la visualización de resultados en la función `mostrarResultados()`.


## Control de Versiones

Este proyecto utiliza Git para el control de versiones. Puedes clonar el repositorio y contribuir al desarrollo.


Este proyecto implementa un sistema que captura una señal analógica utilizando un Arduino, analiza sus características principales (frecuencia, amplitud y forma de onda) en base a estos valores es posible  analizar matematicamente la ecuacion general de la onda y determinar el tipo de onda en cuestion,(senoidal, triangular, cuadrada)  para finalmente mostrar  los resultados en una pantalla LCD.

#SE CONTINUARA  ACTUALIZANDO ESTE DOCUMENTO, PARA PROFUNDIZAR EN LA DOCUMENTACION DE LA FUNCIONES, Y ESTRUCTORA DEL SOFTWARE

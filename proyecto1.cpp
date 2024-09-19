

#include <LiquidCrystal.h>

// Pines para los pulsadores y la pantalla LCD
const int buttonPinStart = 6;     
const int buttonPinInfo = 7;     
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Variables para la adquisición y análisis de la señal
const int analogPin = A0;        

// Tamaño reducido del buffer circular
const int BUFFER_SIZE = 128;  
byte* signalBuffer = nullptr; 
int bufferHead = 0;
byte bufferCount = 0; 
bool isAcquiring = false;        
unsigned long startTime = 0;     

// Variables para las características de la señal
float frequency = 0.0;
int amplitude = 0; 
const char* waveform = waveform;

// Variables para antirrebote
unsigned long lastDebounceTime = 0; 
unsigned long debounceDelay = 50;   
int lastButtonStateStart = HIGH;
int lastButtonStateInfo = HIGH;
int buttonStateStart = HIGH;
int buttonStateInfo = HIGH;

// Usamos la clase F() para almacenar el String en la memoria flash
const char waveformUnknown[] PROGMEM = "Desconocida"; 
const char waveformSquare[] PROGMEM = "Cuadrada";
const char waveformTriangle[] PROGMEM = "Triangular";

void setup() {
    pinMode(buttonPinStart, INPUT_PULLUP);
    pinMode(buttonPinInfo, INPUT_PULLUP);
    Serial.begin(9600); 
    lcd.begin(16, 2);
    lcd.print(F("Listo para"));
    lcd.setCursor(0, 1);
    lcd.print(F("iniciar..."));

    // Asignar memoria dinámicamente para el buffer
    signalBuffer = (byte*) malloc(BUFFER_SIZE * sizeof(byte)); 

    if (signalBuffer == nullptr) {
        lcd.clear();
        lcd.print(F("Error: Memoria"));
        lcd.setCursor(0, 1);
        lcd.print(F("Insuficiente"));
        while (true); 
    }
}

void loop() {
    int readingStart = digitalRead(buttonPinStart);
    int readingInfo = digitalRead(buttonPinInfo);

    // Antirrebote para el pulsador de inicio
    if (readingStart != lastButtonStateStart) {
        lastDebounceTime = millis();
    }
    if ((millis() - lastDebounceTime) > debounceDelay) {
        if (readingStart != buttonStateStart) {
            buttonStateStart = readingStart;
            if (buttonStateStart == LOW) {
                startAcquisition();
            }
        }
    }
    lastButtonStateStart = readingStart;

    // Antirrebote para el pulsador de información
    if (readingInfo != lastButtonStateInfo) {
        lastDebounceTime = millis();
    }
    if ((millis() - lastDebounceTime) > debounceDelay) {
        if (readingInfo != buttonStateInfo) {
            buttonStateInfo = readingInfo;
            if (buttonStateInfo == LOW) {
                showInformation();
            }
        }
    }
    lastButtonStateInfo = readingInfo;

    if (isAcquiring) {
        acquireData();
    }
}

void startAcquisition() {
    if (!isAcquiring) {
        isAcquiring = true;
        startTime = millis(); 
        bufferHead = 0;
        bufferCount = 0;

        lcd.clear();
        lcd.print(F("Adquiriendo..."));
    }
}

void acquireData() {
    if (isAcquiring) {
        signalBuffer[bufferHead] = analogRead(analogPin);
        bufferHead = (bufferHead + 1) % BUFFER_SIZE; 
        if (bufferCount < BUFFER_SIZE) {
            bufferCount++;
        }
    }
}

void showInformation() {
    isAcquiring = false; 

    if (signalBuffer != nullptr) {
        analyzeSignal();

        Serial.print(F("Frecuencia: ")); Serial.println(frequency); 
        Serial.print(F("Amplitud: ")); Serial.println(amplitude); 
        Serial.print(F("Forma de Onda: ")); Serial.println(waveform); 

        lcd.clear();
        lcd.print(F("Frec:")); lcd.print(frequency); lcd.print(F(" Hz"));
        lcd.setCursor(0, 1);
        lcd.print(F("Amp:")); lcd.print(amplitude);
        lcd.setCursor(9, 1);

        lcd.print(F("F:")); 
        if (waveform == waveformUnknown) {
            lcd.print(F("Desconocida")); 
        } else if (waveform == waveformSquare) {
            lcd.print(F("Cuadrada")); 
        } else {
            lcd.print(F("Triangular"));
        }
    } else {
        lcd.clear();
        lcd.print(F("Error: Memoria"));
        lcd.setCursor(0, 1);
        lcd.print(F("Insuficiente"));
    }
}


void analyzeSignal() {
    // 1. Cálculo de Frecuencia (usando autocorrelación)
    int maxCorrelation = 0;
    int correlationLag = 0;

    // Calculamos la autocorrelación para diferentes retardos (lags)
    for (int lag = 0; lag < bufferCount / 2; lag++) {
        int correlation = 0;
        for (int i = 0; i < bufferCount - lag; i++) {
            correlation += signalBuffer[(i + bufferHead) % BUFFER_SIZE] * 
                           signalBuffer[(i + lag + bufferHead) % BUFFER_SIZE];
        }

        // Actualizamos la máxima correlación y el retardo correspondiente
        if (correlation > maxCorrelation) {
            maxCorrelation = correlation;
            correlationLag = lag;
        }
    }

    // Manejo de señales constantes o con poca variación
    if (correlationLag == 0) { 
        frequency = 0; // Señal constante o casi constante
        waveform = waveformUnknown;
        return; // Salimos de la función si la señal no tiene una frecuencia clara
    }

    // Calculamos la frecuencia basada en el retardo de máxima correlación
    unsigned long endTime = millis();
    float duration = (endTime - startTime) / 1000.0;
    float samplingPeriod = duration / bufferCount;
    frequency = 1.0 / (correlationLag * samplingPeriod);

    // 2. Cálculo de Amplitud (Pico a Pico) (sin cambios)
    int maxVal = signalBuffer[0];
    int minVal = signalBuffer[0];
    for (int i = 1; i < bufferCount; i++) {
        int value = signalBuffer[(i + bufferHead) % BUFFER_SIZE];
        if (value > maxVal) {
            maxVal = value;
        }
        if (value < minVal) {
            minVal = value;
        }
    }
    amplitude = maxVal - minVal;

    // 3. Identificación de Forma de Onda (Criterio de Simetría y Armónicos)

    // Cálculo de dutyCycle (sin cambios)
    int highTime = 0; 
    for (int i = 0; i < bufferCount; i++) {
        int value = signalBuffer[(i + bufferHead) % BUFFER_SIZE];
        if (value > (maxVal + minVal) / 2) { 
            highTime++;
        }
    }
    float dutyCycle = (float)highTime / bufferCount;

    // Cálculo de Simetría (sin cambios)
    float symmetryRatio;
    int midPoint = (maxVal + minVal) / 2;
    int aboveMidPoint = 0;
    int belowMidPoint = 0;
    for (int i = 0; i < bufferCount; i++) {
        int value = signalBuffer[(i + bufferHead) % BUFFER_SIZE];
        if (value > midPoint) {
            aboveMidPoint++;
        } else {
            belowMidPoint++;
        }
    }
    symmetryRatio = (float)aboveMidPoint / belowMidPoint;

    // 4. Transformada Discreta de Fourier (DFT) simple para obtener el espectro
    const int numHarmonics = 5; // Número de armónicos a analizar
    float spectrum[numHarmonics];
    for (int k = 1; k <= numHarmonics; k++) { // k representa el índice del armónico (1, 2, 3...)
        float realSum = 0;
        float imagSum = 0;
        for (int n = 0; n < bufferCount; n++) { // n representa el índice de la muestra en el tiempo
            float angle = 2 * PI * k * n / bufferCount;
            realSum += signalBuffer[(n + bufferHead) % BUFFER_SIZE] * cos(angle);
            imagSum -= signalBuffer[(n + bufferHead) % BUFFER_SIZE] * sin(angle);
        }
        spectrum[k-1] = sqrt(realSum * realSum + imagSum * imagSum) / bufferCount; 
    }

    // 5. Identificación de la forma de onda basada en criterios combinados
    if (abs(dutyCycle - 0.5) < 0.05 && spectrum[1] / spectrum[0] < 0.3) {
        waveform = waveformSquare; // Cuadrada: duty cycle cercano a 0.5 y pocos armónicos
    } else if (abs(symmetryRatio - 1.0) < 0.1 && spectrum[1] / spectrum[0] > 0.5) {
        waveform = waveformTriangle; // Triangular: simétrica y armónicos impares significativos
    } else if (spectrum[1] / spectrum[0] < 0.1 && spectrum[2] / spectrum[0] < 0.1) {
        waveform = "Sinusoidal"; // Sinusoidal: pocos armónicos
    } else {
        waveform = waveformUnknown;
    }
}

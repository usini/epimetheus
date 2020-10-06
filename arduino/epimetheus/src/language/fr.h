#include <Arduino.h> // String failed if not include
// Sensors
const String LANG_DATE = "Date";
const String LANG_TEMPERATURE = "Température";
const String LANG_HUMIDITY = "Humidité";
const String LANG_PRESSURE = "Pression Atmosphérique";
const String LANG_GAS = "Gaz";
const String LANG_LIGHT = "Luminosité";
const String LANG_BPM = "Battement par Minute";
const String LANG_ACC = "Accélération";
const String LANG_GYRO = "Gyroscope";

const String LANG_SENSOR_CHANGED = "[SENSOR] Changement dans les capteurs...";

const String LANG_BMP280_FULLNAME = "BMP280 - Capteur de température, pression";
const String LANG_BME280_FULLNAME = "BME280 - Capteur de température, humidité, pression";
const String LANG_BME680_FULLNAME = "BME680 - Capteur de température, humidité, pression et gaz";
const String LANG_TSL2561_FULLNAME = "TSL2561 - Capteur de luminosité digitale";
const String LANG_DS3231_FULLNAME = "DS3231 - Horloge Temps Réel (RTC) de précision";
const String LANG_BH1750_FULLNAME = "BH1750 - Capteur de luminosité";
const String LANG_MAX30102_FULLNAME = "MAX30102 - Capteur de rythme cardiaque";
const String LANG_MPU6050_FULLNAME = "MPU6050 - 6-DoF Capteur d'accélération et gyroscope";

const String LANG_DS3231 = "DS3231";
const String LANG_DS3231_ERROR = "[HORLOGE] Erreur d'initialisation de l'horloge";
const String LANG_DS3231_OK = "[HORLOGE] Horloge interne activé";
const String LANG_SAVING = "Sauvegarde";

// Wifi
const String LANG_WIFI_CONNECTION = "[WIFI] Essai de connexion";
const String LANG_WIFI_CONNECTION_ESTABLISHED = "[WIFI] Connexion établi à ";
const String LANG_WIFI_CONNECTION_FAILED = "[WIFI] Connexion impossible, Mode point d'accès - ";

// Web
const String LANG_DISCONNECT = "Déconnecté";
const String LANG_CONNECTED = "Connecté";
const String LANG_RECEIVED_MESSAGE = "[WEBSOCKET] Message reçu : ";
const String LANG_WIFI_SCAN = "[WIFI] Scan des réseaux wifi";
const String LANG_WIFI_NO_NETWORK = "[WIFI] Pas de réseaux wifi trouvé";
const String LANG_WIFI_NETWORK = "[WIFI] Réseau Wifi trouvé";

// WebSocket
const String LANG_WEBSOCKET_ERROR = "[WEBSOCKET] Erreur Websocket";
const String LANG_WEBSOCKET_INVALID_COMMAND = "[WEBSOCKET] Commande invalide";
const String LANG_WEBSOCKET_INVALID_JSON = "[WEBSOCKET] Commande non formaté en JSON";

// Flash Memory
const String LANG_FLASH_STATE_OK = "[FLASH] Mémoire interne fonctionnel";
const String LANG_FLASH_STATE_ERR = "[FLASH] Mémoire interne inacessible";
const String LANG_FLASH_STATE = "[FLASH] Sauvegarde : ";
const String LANG_FLASH_NAME_DEFINED = "[FLASH] Nom";
const String LANG_FLASH_NAME_UNDEFINED = "[FLASH] Génération du nom";
const String LANG_FLASH_SETTINGS_DEFINED = "[FLASH] Chargement de la configuration";
const String LANG_FLASH_SETTINGS_JSON_ERROR = "[FLASH] Configuration corrumpu, remise à zéro";
const String LANG_FLASH_SETTINGS_UNDEFINED = "[FLASH] Génération de la configuration par défaut";

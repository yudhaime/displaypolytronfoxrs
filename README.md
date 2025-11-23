# ESP32 CAN Bus Temperature Monitor

Monitor suhu ECU, Motor, dan Battery untuk kendaraan listrik melalui CAN Bus dengan display OLED.

## 📋 Fitur

- ✅ **Monitor 3 Parameter**: ECU, Motor, dan Battery temperature
- ✅ **4 Level Status**: Normal, Warm, High, Over
- ✅ **4 Halaman Display**: 
  - Page 1: Overview semua temperature
  - Page 2: Detail ECU dengan status
  - Page 3: Detail Motor dengan status  
  - Page 4: Detail Battery dengan status
- ✅ **100% Listen Only**: Tidak mengganggu sistem kendaraan
- ✅ **Smart Default**: Data selalu tersedia meski CAN offline
- ✅ **Easy Configuration**: Semua setting di satu file

## 🛠️ Hardware Required

### Komponen:
- ESP32 Development Board (ESP32 DOIT DEVKIT V1)
- OLED Display SSD1306 (128x32)
- CAN Bus Transceiver (SN65HVD230) Kode CJMCU-230
- Push Button
- Kabel Jumper
- Reducer 12v ke **5v (jika + ke pin VIN)** atau **3.3v (jika + ke pin 3v3)**

### Koneksi:
ESP32 OLED CAN Transceiver Button

3.3V ---> VCC

GND ---> GND

GPIO16 ---> SDA

GPIO17 ---> SCL

GPIO21 ---> TX

GPIO22 ---> RX

3.3V ---> VCC

GND ---> GND

GPIO25 ---> Button ---> GND (INPUT_PULLUP)


## ⚙️ Instalasi

1. **Download project** dari GitHub
2. **Buka di Arduino IDE**: File → Open → pilih folder project
3. **Install Library**:
   - Adafruit SSD1306
   - Adafruit GFX Library
4. **Konfigurasi**: Edit `config.h` sesuai hardware Anda
5. **Upload ke ESP32**

## 🔧 Konfigurasi

Edit file `config.h` untuk menyesuaikan dengan setup Anda:

### Pin Configuration:
```cpp
// Display
#define SDA_PIN GPIO_NUM_16
#define SCL_PIN GPIO_NUM_17

// Button
#define BUTTON_PIN GPIO_NUM_25

// CAN Bus
#define CAN_TX_PIN GPIO_NUM_21
#define CAN_RX_PIN GPIO_NUM_22
CAN Message IDs:

cpp
#define ID_CTRL_MOTOR   0x0A010810UL  // Controller & Motor
#define ID_BATT_5S      0x0E6C0D09UL  // Battery 5-sensor
#define ID_BATT_SINGLE  0x0A010A10UL  // Battery single
Temperature Thresholds:

cpp
// ECU (°C)
#define ECU_NORMAL_MAX 45
#define ECU_WARM_MAX   55
#define ECU_HIGH_MAX   65

// Motor (°C)
#define MOTOR_NORMAL_MAX 50
#define MOTOR_WARM_MAX   60
#define MOTOR_HIGH_MAX   70

// Battery (°C)  
#define BATT_NORMAL_MAX 35
#define BATT_WARM_MAX   40
#define BATT_HIGH_MAX   45
```


## 🎮 Cara Penggunaan

Power ON sistem
Tekan tombol untuk berpindah halaman:

Page 1: Overview semua temperature
Page 2: Detail ECU
Page 3: Detail Motor
Page 4: Detail Battery
Monitor status:

Normal: Operasi aman
Warm: Perhatian, monitor terus
High: Waspada, pertimbangkan untuk istirahat
Over: Bahaya, hentikan penggunaan

## 📁 Struktur File

```text
esp32-can-temperature-monitor/
├── displaypolytronmain.ino  # Main program
├── config.h                 # User configuration
├── canbus.h                 # CAN bus interface
├── canbus.cpp               # CAN bus implementation  
├── display.h                # Display interface
├── display.cpp              # Display implementation
└── README.md                # This file
```

## ⚠️ Safety Warning

- Jangan modifikasi kendaraan tanpa pengetahuan yang cukup
   - Saya tidak bertanggung jawab atas kerusakan yang bisa ditimbulkan jika ada kesalahan dalam mengimplementasikan kode ini

- Test di area aman sebelum digunakan di jalan


## 📄 License

MIT License - bebas untuk digunakan dan dimodifikasi.

## 🤝 Contributing

Pull requests welcome! Untuk major changes, buka issue terlebih dahulu.

Dibuat dengan ❤️ untuk komunitas kendaraan listrik Indonesia

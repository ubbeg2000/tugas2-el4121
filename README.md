# tugas2-el4121

![sim.JPG](https://github.com/ubbeg2000/tugas2-el4121/blob/main/sim.png?raw=true)

Repository yang berisikan source code untuk tugas 2 mata kuliah EL4121 Perancangan Sistem Embedded. Pada tugas ini, mahasiswa diminta untuk membuat simulasi HIL dari sistem pengendali pintu geser dengan menerapkan supervisory control. Simulasi dilakukan dengan menggunakan esp32 yang berperan sebagai pengendali dan program python yang berperan sebagai plant (motor). esp32 diprogram menggunakan ESP-IDF. Video demonstrasi tugas dapat dilihat di [sini](https://www.youtube.com/watch?v=FajcCW099rw).

## Struktur Folder

```
tugas2-el4121/
|
├─ fsm/ (source code fsm supervisory control)
├─ controller/ (source code PI controller)
├─ motor/ (source code model motor)
├─ esp/ (source code simulasi HIL fsm di esp32)
|
├─ hil.py
├─ system_simulation.c
|
├─ .gitignore
├─ README.md
├─ Makefile
├─ requirements.txt
```

## Panduan Penggunaan

1. Hubungkan pushbutton ke GPIO18 dan GPIO19 dengan konfigurasi pulldown
2. Program esp32 menggunakan ESP-IDF dengan perintah `idf.py build && idf.py -p (PORT) flash`
3. Install dependencies program `hil.py` dengan perintah `pip install -r requirements.txt`
4. Jalankan simulasi dengan perintah `py hil.py (PORT) (LOG_FILE)`
5. Untuk menghentikan simulasi, tekan tombol EN di esp32 atau tekan Ctrl+C

Sebagai contoh, jika esp32 berada di port COM8 dan hasil simulasi akan dicatat ke sebuah file bernama hil_log.csv, maka simulasi dijalankan dengan perintah

```
py hil.py COM8 hil_log.csv
```

## Pengaturan Simulasi

Pengaturan simulasi dapat diubah dengan mengganti nilai variabel-variabel berikut yang ada di file `hil.py`

- SIM_WINDOW_WIDTH (jumlah sampel dalam display simulasi)
- SIM_DURATION (jumlah sampel maksimal dalam simulasi)
- SIM_LOG_FILE_NAME (nilai default LOG_FILE)
- SIM_PORT (nilai default PORT)

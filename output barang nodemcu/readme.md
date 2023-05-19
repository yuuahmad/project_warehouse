# penjelasa umum
ini adalah program yang digunakan untuk memprogram node mcu agar dapat menghapus data rfid yang sebelumnya telah dilakukan scan pada program input barang. hasil penghapusan datanya dapat dilihat pada website [https://monitoring-warehouse-123.web.app/warehouse](https://monitoring-warehouse-123.web.app/warehouse).

# penjelasa singkat kode
- menggunakan i2c lcd untuk menampilkan informasi pentingnya.
- menggunakan modul RFID agar dapat membaca kartu dan tag.
- pin D8 dikoneksikan ke SDA RFID. dan pin D0 dikoneksikan ke RST RFID 
- menggunakan firebase firestore sebagai databasenya.
- akan menghapus data tag dengan ID kartu atau tag yang sama pada website.
- data yang sudah dihapus tidak dapat dilihat maupun dikembalikan lagi.
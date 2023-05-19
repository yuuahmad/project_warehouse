<template>
    <!-- bagian pertama -->
    <div>
        <div class="judul-satu ">tentang monitoring warehouse</div>
        <div class="text-xl">
            <div class="p-5 bg-slate-200 m-5 rounded-md">
                Di era modern ini, kemajuan teknologi telah membawa perubahan signifikan dalam industri pergudangan.
                Salah satu inovasi
                yang menarik adalah penggunaan warehouse pintar yang dilengkapi dengan sistem RFID (Radio Frequency
                Identification) dan
                monitoring kelembapan dan suhu udara.
            </div>

            <div class="p-5 bg-slate-200 m-5 rounded-md">
                Dalam warehouse pintar ini, sistem RFID digunakan untuk mengidentifikasi dan melacak barang secara
                otomatis. Setiap
                barang dilengkapi dengan tag RFID yang dapat dipindai secara efisien, memungkinkan proses pengelolaan
                inventaris yang
                lebih akurat dan efektif. Pemantauan yang real-time melalui RFID memungkinkan para pengelola untuk
                mengetahui dengan
                cepat lokasi dan status barang di dalam gudang.
            </div>

            <div class="p-5 bg-slate-200 m-5 rounded-md">
                Selain itu, kelembapan udara dan suhu udara menjadi faktor penting dalam menjaga kualitas barang yang
                disimpan di
                gudang. Dengan adanya sistem monitoring kelembapan dan suhu udara yang terintegrasi, pengelola dapat
                memantau kondisi
                lingkungan gudang secara real-time. Jika terjadi fluktuasi yang tidak diinginkan, sistem dapat
                memberikan notifikasi
                kepada pengelola untuk mengambil tindakan yang diperlukan, seperti penyesuaian suhu atau kelembapan.
            </div>

            <div class="p-5 bg-slate-200 m-5 rounded-md">
                Warehouse pintar dengan sistem RFID dan monitoring kelembapan serta suhu udara ini memberikan berbagai
                manfaat.
                Pengelolaan inventaris yang lebih efisien dan akurat memungkinkan pengurangan kesalahan dan kerugian.
                Selain itu,
                pemantauan kondisi lingkungan gudang secara real-time membantu mencegah kerusakan atau kerugian yang
                disebabkan oleh
                perubahan suhu atau kelembapan yang ekstrem.
            </div>

            <div class="p-5 bg-slate-200 m-5 rounded-md">
                Dengan adanya teknologi ini, warehouse pintar memberikan efisiensi operasional yang tinggi dan
                perlindungan terhadap
                aset yang disimpan di dalamnya. Ini merupakan langkah maju dalam mengoptimalkan pengelolaan gudang dan
                meningkatkan
                kepuasan pelanggan dengan menjamin kualitas barang yang disediakan.

            </div>

        </div>
    </div>

    <!-- bagian kedua -->
    <div>
        <div class="judul-satu">alamat maps kami</div>
        <div class=" bg-gray-400 aspect-video">
            <!-- <iframe
                src="https://www.google.com/maps/embed?pb=!1m18!1m12!1m3!1d3969.7470714154365!2d105.6849341153749!3d-5.749505595833192!2m3!1f0!2f0!3f0!3m2!1i1024!2i768!4f13.1!3m3!1m2!1s0x2e410f094b3cd7a9%3A0xe3ba58a13d181c10!2sKLINIK%20PRATAMA%20KARUNIA%20SEHAT!5e0!3m2!1sen!2sid!4v1667170086047!5m2!1sen!2sid"
                width=100% height=100% style="border:0;" allowfullscreen="" loading="lazy"
                referrerpolicy="no-referrer-when-downgrade"></iframe> -->
            <iframe
                src="https://www.google.com/maps/embed?pb=!1m18!1m12!1m3!1d2116.9465620422334!2d105.31364902003408!3d-5.358821325074207!2m3!1f0!2f0!3f0!3m2!1i1024!2i768!4f13.1!3m3!1m2!1s0x2e40c35634c1a611%3A0xcb3cf692dbb4f26!2sInstitut%20Teknologi%20Sumatera!5e0!3m2!1sen!2sid!4v1684257852736!5m2!1sen!2sid"
                width=100% height=100% style="border:0;" allowfullscreen="" loading="lazy"></iframe>
        </div>
    </div>

    <!-- <div>
        <div class="judul-satu">tim klinik karunia sehat</div>
        <div class="flex justify-center ">
            <div v-for="tim in tims" :key="tim.id" class="px-10 grid grid-cols-1 justify-items-center ">
                <img class="inline object-cover w-24 md:w-32 h-24 md:h-32 m-1 rounded-full " :src="tim.linkGambar"
                    alt="">
                <div class="text-center text-md md:text-xl capitalize">{{tim.nama}} </div>
                <div class="text-center text-sm md:text-md capitalize">{{tim.penanggungjawab}} </div>

            </div>
        </div>
    </div> -->

</template>

<script setup>
import { ref, onMounted, reactive } from 'vue'
import imageSatu from '/src/assets/satu.jpeg'
import imageDua from '/src/assets/dua.png'
import imageTiga from '/src/assets/hamzah.jpg'
import imageEmpat from "/src/assets/yusuf.jpeg"
import imageLima from "/src/assets/eko.jpeg"
import imageEnam from "/src/assets/robi.jpeg"


const tims = ref([
    {
        id: '1',
        nama: 'ahmad yusuf maulana',
        penanggungjawab: 'web developer',
        linkGambar: imageEmpat
    },
    {
        id: '2',
        nama: 'robiyanto',
        penanggungjawab: 'konten kreator',
        linkGambar: imageEnam
    },
])

</script>

<style scoped>

</style>
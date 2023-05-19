<!-- ini adalah template dummy untuk menghitung antrian (halaman antrian) -->


<template>
    <!-- lg:flex justify-between -->
    <div class=" py-10 flex-none">
        <div class="lg:flex items-center justify-around bg-gray-200 my-10 py-5 w-full">
            <div class="text-center">
                <div class=" text-2xl lg:text-4xl">Antrian Ke </div>
                <!-- <div class="font-bold text-5xl md:text-[100px] lg:text-[180px] mx-5">A-{{antrianKe.nomor}} </div> -->
                <div class="font-bold text-5xl md:text-[100px] lg:text-[180px] mx-5" v-if="antrianKe.nomor >=0">A-{{
                antrianKe.nomor}} </div>
                <div class="font-bold text-5xl md:text-[100px] lg:text-[180px] mx-5" v-else>
                    != antrian
                </div>
            </div>
            <div class="capitalize text-xl p-5 text-center">
                <div>nama : {{antrianKe.nama}} </div>
                <div>waktu daftar : {{moment(antrianKe.waktu).format("LLLL")}} </div>
                <div>umur : {{antrianKe.umur}} tahun</div>
                <!-- <div>jenis kelamin : {{antrianKe.jenisKelamin}} </div> -->
                <div>domisili : {{antrianKe.domisili}}</div>
            </div>
        </div>
        <div class="lg:flex items-center justify-around bg-gray-200 my-10 py-5 w-full">
            <div class="text-center">
                <div class=" text-2xl lg:text-4xl">Akhir Antrian </div>
                <!-- Date(antrianAkhir.nomor *1000).toLocaleTimeString("it-IT") -->
                <div class="font-bold text-5xl md:text-[100px] lg:text-[180px] mx-5" v-if="antrianAkhir.nomor >=0">
                    A-{{antrianAkhir.nomor}}
                </div>
                <div class="font-bold text-5xl md:text-[100px] lg:text-[180px] mx-5" v-else>
                    != antrian
                </div>
            </div>
            <div class="capitalize text-xl p-5 text-center">
                <div>nama : {{antrianAkhir.nama}} </div>
                <div>waktu daftar : {{moment(antrianAkhir.waktu).format("LLLL")}} </div>
                <div>umur : {{antrianAkhir.umur}} tahun </div>
                <!-- <div>jenis kelamin : {{antrianAkhir.jenisKelamin}} </div> -->
                <div>domisili : {{antrianAkhir.domisili}}</div>
            </div>
        </div>
    </div>


</template>

<script setup>
import { ref, onMounted, reactive } from 'vue'
import { v4 as uuidv4 } from 'uuid'
import { addDoc, collection, getDocs, getFirestore, updateDoc, query, where, onSnapshot, doc, setDoc, deleteDoc, orderBy, limit } from "firebase/firestore";
import moment from 'moment';
moment().format();


// konversi timestamp ke waktu detik menit jam
// const unixTimestamp = antrianAkhir.nomor;
// const date = new Date(unixTimestamp * 1000);
// const finaldate = ref(date.toLocaleTimeString("it-IT"))
onMounted(() => {
    onSnapshot(query(collection(getFirestore(), 'antrians'), orderBy('date', 'desc'), limit(1)), (querySnapshot) => {
        const cachefbAntrianAkhir = [];
        querySnapshot.forEach((doc) => {
            console.log(doc.id, " => ", doc.data())
            const fbAntrianAkhir = {
                waktu: doc.data().date,
                nomor: doc.data().nomor,
                nama: doc.data().nama,
                umur: doc.data().umur,
                // jenisKelamin: doc.data().jenisKelamin,
                domisili: doc.data().domisili
            }
            // var timestamp = (fbAntrianAkhir.nomor).toDate()
            // cachefbAntrianAkhir.nomor = timestamp.toHour()
            // fbTodos.push(todo)
            Object.assign(cachefbAntrianAkhir, fbAntrianAkhir)
        });
        antrianAkhir.value = cachefbAntrianAkhir
    });
})

onMounted(() => {
    onSnapshot(query(collection(getFirestore(), 'antrians'), orderBy('date', 'asc'), limit(1)), (querySnapshot) => {
        const cachefbAntrianKe = [];
        querySnapshot.forEach((doc) => {
            console.log(doc.id, " => ", doc.data())
            const fbAntrianKe = {
                waktu: doc.data().date,
                nomor: doc.data().nomor,
                nama: doc.data().nama,
                umur: doc.data().umur,
                // jenisKelamin: doc.data().jenisKelamin,
                domisili: doc.data().domisili
            }
            // fbTodos.push(todo)
            Object.assign(cachefbAntrianKe, fbAntrianKe)
        });
        antrianKe.value = cachefbAntrianKe
    });
})
const antrianKe = ref(
    {
        // keterangan: "Antrian Ke",
        // nomor: "12",
        // nama: "ahmad yusuf maulana",
        // umur: "23 tahun",
        // jenisKelamin: "laki-laki",
        // domisili: "lampung selatan"
    },
)
const antrianAkhir = ref(
    {
        // keterangan: "Akhir Antrian",
        // nomor: "32",
        // nama: "mukhammad khanafi",
        // umur: 19,
        // jenisKelamin: false,
        // domisili: "lampung barat"
    }
)
// const nilaiAntrianAkhir = ref(moment(antrianAkhir.nomor).format("h:mm:ss"))
console.log("waktu daftar:", antrianKe.waktu)
console.log("nomor urut ke:", antrianKe.nomor)

// const nilaiAntrianKe = ref(moment(antrianKe.nomor).format("h:mm:ss"))

</script>

<style>

</style>
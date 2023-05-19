<template>
    <!-- div daftar antrian -->
    <div>
        <div class="judul-satu">
            daftar antrian disini
        </div>
        <form class="grid grid-cols-1 gap-4" @submit.prevent="daftarAntrian(nomorKeDitambah.nomor)">
            <input v-model="nama"
                class="shadow appearance-none border rounded w-full py-3 px-3 text-gray-700 leading-tight focus:outline-none focus:shadow-outline"
                type="text" placeholder="nama">
            <input v-model="umur"
                class="shadow appearance-none border rounded w-full py-3 px-3 text-gray-700 leading-tight focus:outline-none focus:shadow-outline"
                type="text" placeholder="umur (masukkan angka)">
            <!-- <input v-model="jenisKelamin"
                class="shadow appearance-none border rounded w-full py-3 px-3 text-gray-700 leading-tight focus:outline-none focus:shadow-outline"
                type="text" placeholder="jenisKelamin"> -->
            <input v-model="domisili"
                class="shadow appearance-none border rounded w-full py-3 px-3 text-gray-700 leading-tight focus:outline-none focus:shadow-outline"
                type="text" placeholder="domisili">
            <div>
                <button :disabled="!nama" class="btn-green m-0 disabled:bg-green-300"> submit </button>
            </div>
        </form>
    </div>
    <!-- div reset antrian -->
    <div class="grid grid-cols-1 items-center">
        <div class="judul-satu">
            hapus antrian yang telah terlayani
        </div>
        <div class="text-center text-xl md:mx-24 lg:mx-64">
            jika anda menekan tombol ini, maka antrian yang telah terlayani akan terhapus. jika anda bukanlah admin
            klinik, jangan pernah menekan tombol ini. (patuhi peraturan ini demi kepentingan bersama) (budayakan hidup
            jujur) (budayakan antri)
        </div>
        <div class="text-center py-3">
            <button @click="deleteSelesaiPeriksa(nomorKeDihapus.id)" class="btn-red">hapus antrian terlayani</button>
        </div>
    </div>
</template>

<script setup>
import { ref, onMounted, reactive } from 'vue'
import { v4 as uuidv4 } from 'uuid'
import { addDoc, collection, getDocs, getFirestore, updateDoc, query, where, onSnapshot, doc, setDoc, deleteDoc, orderBy, limit, serverTimestamp } from "firebase/firestore";
import suarasaya from '/src/assets/audiosaya.mp3'

const nama = ref('')
const umur = ref('')
const domisili = ref('')
const mytrack = new Audio(suarasaya)

// mendapatkan data pertama yang ingin dihapus (yang udah dilayanin)
onMounted(() => {
    onSnapshot(query(collection(getFirestore(), 'antrians'), orderBy('date', 'asc'), limit(1)), (querySnapshot) => {
        const cachefbNomorKeDihapus = [];
        querySnapshot.forEach((doc) => {
            console.log(doc.id, " => ", doc.data())
            // nomorKeDihapus = doc.id
            const fbAntrianKe = {
                id: doc.id,
                nomor: doc.data().nomor,
            }
            // console.log("data saya :", fbAntrianKe.nomor)
            Object.assign(cachefbNomorKeDihapus, fbAntrianKe)
        });
        nomorKeDihapus.value = cachefbNomorKeDihapus
    });
})

onMounted(() => {
    onSnapshot(query(collection(getFirestore(), 'antrians'), orderBy('date', 'desc'), limit(1)), (querySnapshot) => {
        const cachefbNomorKeDitambah = [];
        querySnapshot.forEach((doc) => {
            console.log(doc.id, " => ", doc.data())
            // nomorKeDitambah = doc.id
            const fbAntrianKe = {
                id: doc.id,
                nomor: doc.data().nomor,
            }
            // console.log("data saya :", fbAntrianKe.nomor)
            Object.assign(cachefbNomorKeDitambah, fbAntrianKe)
        });
        nomorKeDitambah.value = cachefbNomorKeDitambah
    });
})

const nomorKeDihapus = ref({})
const nomorKeDitambah = ref({})

// console.log("data kedihapus :", nomorKeDihapus.id)
// console.log("nomor didapatkan", nomorKeDihapus.nomor)
// if (isNaN(nomorKeDihapus.nomor)) {
//     nomorKeDihapus.nomor = 0
// }

const daftarAntrian = (nomor) => {
    if (isNaN(nomor)) {
        nomor = 0
    }
    addDoc(collection(getFirestore(), "antrians"), {
        nomor: nomor += 1,
        nama: nama.value,
        umur: umur.value,
        domisili: domisili.value,
        date: Date.now(),
        isDone: false
    });
    nama.value = ''
    umur.value = ''
    domisili.value = ''
}

// delete antrian
const deleteSelesaiPeriksa = id => {
    // gunakan filter untuk menghapus todo
    deleteDoc(doc(getFirestore(), "antrians", id));
    console.log("data selesai telah dihapus")
    mytrack.play()
    // todos.value = todos.value.filter(todo => todo.id !== id)
}
</script>

<style>

</style>
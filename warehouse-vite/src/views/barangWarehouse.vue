<template>
    <div>
        <!-- judul -->
        <div class="capitalize text-3xl text-center p-4">Keadaan Barang di Warehouse</div>

        <!-- card edit keteragnan barang -->
        <div class="p-5 m-5 bg-slate-200 rounded-lg">
            <div class="judul-satu">
                Edit Data Barang
            </div>
            <form class="grid grid-cols-1 gap-4">
                <input v-model="jenisBarangEdit"
                    class="shadow appearance-none border rounded w-full py-3 px-3 text-gray-700 leading-tight focus:outline-none focus:shadow-outline"
                    type="text" placeholder="jenis barang">
                <!-- <input v-model="tanggalKedatanganEdit"
                    class="shadow appearance-none border rounded w-full py-3 px-3 text-gray-700 leading-tight focus:outline-none focus:shadow-outline"
                    type="text" placeholder="tanggal kedatangan"> -->
                <!-- sudah dihandle oleh mikrokon -->
                <input v-model="kelompokTaniEdit"
                    class="shadow appearance-none border rounded w-full py-3 px-3 text-gray-700 leading-tight focus:outline-none focus:shadow-outline"
                    type="text" placeholder="kelompok tani">
                <input v-model="beratEdit"
                    class="shadow appearance-none border rounded w-full py-3 px-3 text-gray-700 leading-tight focus:outline-none focus:shadow-outline"
                    type="text" placeholder="berat">
            </form>
        </div>

        <!-- card warehouse -->
        <div v-for="warehouse in warehouses" :key="warehouse.id">
            <div class="bg-white shadow-lg rounded p-5 my-2 md:flex justify-between items-center">
                <div>
                    <div class="capitalize text-xl text-center md:text-start">
                        tanggal kedatangan : {{new Date(warehouse.waktuScan * 1000)}}
                    </div>
                    <hr>
                    <div class="capitalize text-md text-center md:text-start">
                        id barang : {{warehouse.content}}
                    </div>
                    <div class="capitalize text-md text-center md:text-start">
                        jenis barang : {{warehouse.jenisBarang}}
                    </div>
                    <div class="capitalize text-md text-center md:text-start">
                        kelompok tani : {{warehouse.kelompokTani}}
                    </div>
                    <div class="capitalize text-md text-center md:text-start">
                        berat : {{warehouse.berat}}
                    </div>
                </div>

                <div class="uppercase text-center">
                    <button @click="updateWarehouseData(warehouse.id)" class="btn-green m-3">edit</button>
                    <button @click="deleteWarehouse(warehouse.id)" class="btn-red m-3">hapus</button>
                </div>
            </div>
        </div>
    </div>
</template>

<script setup>
// import
import { ref, onMounted, reactive } from 'vue'
import { v4 as uuidv4 } from 'uuid'
import { addDoc, collection, getDocs, getFirestore, updateDoc, query, where, onSnapshot, doc, setDoc, deleteDoc, orderBy, limit, Query } from "firebase/firestore";

// konstanta untuk vmodel
const jenisBarangEdit = ref('')
// const tanggalKedatanganEdit = ref('')
const kelompokTaniEdit = ref('')
const beratEdit = ref('')

// data warehouse
const warehouses = ref([
])

// perintah mendapatkan data barang warehouse dari firebase
onMounted(() => {
    onSnapshot(query(collection(getFirestore(), 'warehouses'), orderBy('waktuScan', 'desc')), (querySnapshot) => {
        const fbWarehouses = [];
        querySnapshot.forEach((doc) => {
            console.log(doc.id, " => ", doc.data())
            const warehouse = {
                id: doc.id, //id untuk ngurutin di tampilan
                content: doc.data().content, //nama barang
                jenisBarang: doc.data().jenisBarang, //jenis barang
                done: doc.data().done, //biarkan pajangan
                waktuScan: doc.data().waktuScan, //tanggal diterima
                kelompokTani: doc.data().kelompokTani, //kelompok tani
                berat: doc.data().berat, //berat barang
            }
            fbWarehouses.push(warehouse)
        });
        warehouses.value = fbWarehouses
    });
})

// program baru
const newWarehouseContent = ref('')

// const konversiWaktu = (waktuScan) => {
//     var utcSeconds = waktuScan;
//     var d = new Date(0);
//     d.setUTCSeconds(utcSeconds)
// }

const addWarehouse = () => {
    addDoc(collection(getFirestore(), "warehouses"), {
        content: newWarehouseContent.value,
        done: false,
        date: Date.now()
    });
    newWarehouseContent.value = ''
}
// perintah untuk delete barang warehouse
const deleteWarehouse = (id) => {
    // gunakan filter untuk menghapus warehouse
    deleteDoc(doc(getFirestore(), "warehouses", id));
    warehouses.value = warehouses.value.filter(warehouse => warehouse.id !== id)
}
// perintah untuk update data warehouse 
const updateWarehouseData = id => {
    const index = warehouses.value.findIndex(warehouse => warehouse.id === id)
    console.log("warehouse number :", index)
    console.log("warehouse value :", warehouses.value[index].done)

    updateDoc(doc(getFirestore(), "warehouses", id), {
        // done: !warehouses.value[index].done,
        jenisBarang: jenisBarangEdit.value,
        // tanggalKedatangan: tanggalKedatanganEdit.value,
        kelompokTani: kelompokTaniEdit.value,
        berat: beratEdit.value,
        // date: Date.now(),
        // isDone: false
    });
}
</script>

<style>

</style>
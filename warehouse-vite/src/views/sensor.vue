<template>
    <div>
        <!-- judul -->
        <div class="capitalize text-3xl text-center p-4">Keadaan suhu dan kelembapan di warehouse</div>

        <!-- card sensor -->
        <div v-for="sensor in sensors" :key="sensor.id">
            <div class="bg-white shadow-lg rounded p-5 my-2 md:flex justify-between items-center">
                <div>
                    <div class="capitalize text-xl text-center md:text-start">
                        tanggal input : {{new Date(sensor.waktuUpload * 1000)}}
                    </div>
                    <hr>
                    <div class="capitalize text-md text-center md:text-start">
                        suhu warehouse : {{sensor.suhu}}
                    </div>
                    <div class="capitalize text-md text-center md:text-start">
                        kelembapan warehouse : {{sensor.kelembapan}}
                    </div>
                </div>

                <div class="uppercase text-center">
                    <!-- <button @click="updateSensorData(sensor.id)" class="btn-green">edit</button> -->
                    <button @click="deleteSensor(sensor.id)" class="btn-red">hapus</button>
                </div>
            </div>
        </div>
    </div>
</template>

<script setup>
// import
import { ref, onMounted, reactive } from 'vue'
import { v4 as uuidv4 } from 'uuid'
import { addDoc, collection, getDocs, getFirestore, updateDoc, query, where, onSnapshot, doc, setDoc, deleteDoc, orderBy, limit } from "firebase/firestore";

// data sensor
const sensors = ref([
])

// perintah mendapatkan data barang sensor dari firebase
onMounted(() => {
    onSnapshot(query(collection(getFirestore(), 'sensors'), orderBy('waktuUpload', 'desc')), (querySnapshot) => {
        const fbSensors = [];
        querySnapshot.forEach((doc) => {
            console.log(doc.id, " => ", doc.data())
            const sensor = {
                id: doc.id, //id untuk ngurutin di tampilan
                waktuUpload: doc.data().waktuUpload,
                suhu: doc.data().suhu, //kelompok tani
                kelembapan: doc.data().kelembapan, //kelembapan di warehouse
            }
            fbSensors.push(sensor)
        });
        sensors.value = fbSensors
    });
})

// perintah untuk delete nilai sensor warehouse
const deleteSensor = (id) => {
    // gunakan filter untuk menghapus sensor
    deleteDoc(doc(getFirestore(), "sensors", id));
    sensors.value = sensors.value.filter(sensor => sensor.id !== id)
}
</script>

<style>

</style>
<!-- template dummy untuk aplikasi todo (latihan) -->

<template>
    <div>
        <!-- judul -->
        <div class="capitalize text-3xl text-center p-4">list yang ingin dilakukan</div>
        <!-- <div>todo saya: {{state.count}}</div>
        <button @click="tambahAngka">tambah angka</button> -->
        <!-- form dan submit -->
        <div>
            <form class="flex" @submit.prevent="addTodo">
                <input v-model="newTodoContent"
                    class="shadow appearance-none border rounded w-full py-3 px-3 text-gray-700 leading-tight focus:outline-none focus:shadow-outline"
                    type="text" placeholder="masukkan todo">
                <button :disabled="!newTodoContent" class="btn-green disabled:bg-green-300"> submit </button>
            </form>
        </div>
        <!-- card todo -->
        <div v-for="todo in todos" :key="todo.id">
            <div class="bg-white shadow-lg rounded p-5 my-2 md:flex justify-between items-center" :class="{
            'bg-green-200' : todo.done}">
                <div class="capitalize text-lg text-center md:text-start">
                    {{todo.content}}
                </div>
                <div class="uppercase text-center">
                    <button @click="doneTodo(todo.id)" class="btn-green">centang</button>
                    <button @click="deleteTodo(todo.id)" class="btn-red">silang</button>
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
// import {} from "firebase/firebase-database"
// import { getFirestore } from "firebase/firestore";
// import { collection, getDocs } from "firebase/firestore"
// const db = getFirestore(app);

// data todo
const todos = ref([
    // {
    //     id: '1', 
    //     content: 'makan nasi',
    //     done: false
    // },
    // {
    //     id: '2',
    //     content: 'mandi bunga di kali',
    //     done: true
    // },
    // {
    //     id: '3',
    //     content: 'berangkat nguli',
    //     done: false
    // },
    // {
    //     id: '4',
    //     content: 'jemput istri',
    //     done: true
    // },
    // {
    //     id: '4',
    //     content: 'makan sendiri',
    //     done: false
    // },
])

// dapatkan todo dari firebase
onMounted(() => {
    // yang sudah bisa 
    // const querySnapshot = await getDocs(collection(getFirestore(), 'todos'))
    // let fbTodos = []
    // querySnapshot.forEach((doc) => {
    //     // doc.data() is never undefined for query doc snapshots
    //     console.log(doc.id, " => ", doc.data())
    //     const todo = {
    //         id: doc.id,
    //         content: doc.data().content,
    //         done: doc.data().done
    //     }
    //     fbTodos.push(todo)
    // })
    // todos.value = fbTodos
    // // console.log("mounted")
    onSnapshot(query(collection(getFirestore(), 'todos'), orderBy('date', 'desc')), (querySnapshot) => {
        const fbTodos = [];
        querySnapshot.forEach((doc) => {
            console.log(doc.id, " => ", doc.data())
            const todo = {
                id: doc.id,
                content: doc.data().content,
                done: doc.data().done,
                date: Date.now()
            }
            fbTodos.push(todo)
        });
        todos.value = fbTodos
    });
})

// program baru
const newTodos = ref([])
const newTodoContent = ref('')
const addTodo = () => {
    // const newTodos = {
    //     id: uuidv4(),
    //     content: newTodoContent.value,
    //     done: false
    // }
    // todos.value.unshift(newTodos)
    // Add a new document in collection "cities"
    addDoc(collection(getFirestore(), "todos"), {
        content: newTodoContent.value,
        done: false,
        date: Date.now()
    });
    newTodoContent.value = ''
}
// delete todo
const deleteTodo = (id) => {
    // gunakan filter untuk menghapus todo
    deleteDoc(doc(getFirestore(), "todos", id));
    todos.value = todos.value.filter(todo => todo.id !== id)
}
// done todo 
const doneTodo = id => {
    const index = todos.value.findIndex(todo => todo.id === id)
    console.log("todo number :", index)
    console.log("todo value :", todos.value[index].done)

    // todos.value[index].done = !todos.value[index].done

    updateDoc(doc(getFirestore(), "todos", id), {
        done: !todos.value[index].done
    });
}

// program tambah angka sederhana
// const state = reactive({ count: 0 })

// function tambahAngka() {
//     state.count++
//     console.log('angka ditambahkan')
// }
</script>

<style>

</style>
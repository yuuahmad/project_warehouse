// import 'vuetify/styles' // Global CSS has to be imported
import { createApp } from 'vue'
// import { createVuetify } from 'vuetify'
import App from './App.vue'
import { loadFonts } from './plugins/webfontloader'
// import * as components from 'vuetify/components'
// import * as directives from 'vuetify/directives'
import 'material-design-icons-iconfont/dist/material-design-icons.css'
import '@mdi/font/css/materialdesignicons.css'
import router from './router'
import './style.css'


// semua tentang firebase
import { initializeApp } from "firebase/app";
import { getAnalytics } from "firebase/analytics";
import { getFirestore } from "firebase/firestore";
// const firebaseConfig = {
//     apiKey: "AIzaSyBACgKlBjRM1XFsRvzN3PcL8iM6BvbdD7w",
//     authDomain: "klinik-karunia-sehat.firebaseapp.com",
//     projectId: "klinik-karunia-sehat",
//     storageBucket: "klinik-karunia-sehat.appspot.com",
//     messagingSenderId: "1065936843297",
//     appId: "1:1065936843297:web:c19590bb2845bd2cb1e960",
//     measurementId: "G-XRJRJHK79T"
// };
const firebaseConfig = {
    apiKey: "AIzaSyBuVMlC_Pbu45KNLdtEvGArcvz7NUFMJO4",
    authDomain: "absensi-warehouse.firebaseapp.com",
    databaseURL: "https://absensi-warehouse-default-rtdb.asia-southeast1.firebasedatabase.app",
    projectId: "absensi-warehouse",
    storageBucket: "absensi-warehouse.appspot.com",
    messagingSenderId: "646417421148",
    appId: "1:646417421148:web:65bbc9ef4118aa6f4f6799"
};

loadFonts()
initializeApp(firebaseConfig);
// const db = getFirestore(app);
// const analytics = getAnalytics(app);
const app = createApp(App)
// const vuetify = createVuetify({
//   components,
//   directives,
//   ssr: true,
// }) // Replaces new Vuetify()
// app.use(vuetify)
app.use(router)
app.mount('#app')
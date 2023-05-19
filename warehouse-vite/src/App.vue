<template>
  <div class="flex flex-col h-screen justify-between">
    <div>
      <Header></Header>
      <div class="mx-auto container px-2">
        <router-view></router-view>
      </div>
    </div>
    <Footer></Footer>
  </div>
</template>

<script>
import Header from "./components/Header.vue";
import Footer from "./components/Footer.vue";
export default {
  data: () => ({
    drawer: null,
    items: [
      { title: "Home", icon: "mdi-home-outline", to: "/" },
      { title: "Tentang Klinik", icon: "mdi-information-outline", to: "/tentang" },
      { title: "Daftar Antrian", icon: "mdi-pencil-plus-outline", to: "/daftar" },
      { title: "Penghitung Antrian", icon: "mdi-account-multiple-plus-outline", to: "/penghitung" },
      { title: "Coba Todo App", icon: "mdi-history", to: "/todo" },
    ]
  }),
  components: { Header, Footer }
}
</script>
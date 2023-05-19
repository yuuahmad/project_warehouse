<template>
    <!-- div utama -->
    <div class="bg-slate-700 text-white uppercase text-lg ">
        <div class="mx-auto container flex justify-between items-center py-2 px-2 lg:px-0">
            <!-- div judul -->
            <div class="text-xl">Monitoring Warehouse 123</div>
            <button @click="lihatMenu = !lihatMenu" class="lg:hidden">
                <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.5"
                    stroke="currentColor" class="w-10 h-10">
                    <path stroke-linecap="round" stroke-linejoin="round"
                        d="M3.75 6.75h16.5M3.75 12h16.5m-16.5 5.25h16.5" />
                </svg>
            </button>
            <!-- desktop -->
            <div class="hidden lg:block">
                <router-link class="px-2" v-for="dataMenu in dataMenus" :key="dataMenu" :to="dataMenu.to">
                    {{dataMenu.judul}}
                </router-link>
            </div>
        </div>
        <!-- mobile -->
        <div v-if="lihatMenu" class=" grid grid-rows-1 container mx-auto text-center pb-3 lg:hidden">
            <router-link v-for="dataMenu in dataMenus" :key="dataMenu" :to="dataMenu.to">{{dataMenu.judul}}
            </router-link>
        </div>
    </div>
</template>

<script>
export default {
    data() {
        return {
            lihatMenu: false,
            dataMenus: [
                { judul: "Menu Utama", to: "/" },
                { judul: "Sensor", to: "/sensor" },
                { judul: "Warehouse", to: "/warehouse" },
            ]
        }
    }
}
</script>

<style>

</style>
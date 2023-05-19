import { createRouter, createWebHistory } from 'vue-router'
import Home from '../views/home.vue'

const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes: [
    {
      path: '/',
      name: 'home',
      component: Home
    },
    {
      path: '/sensor',
      name: 'sensor',
      // component: Home
      component: () => import('../views/sensor.vue')
    },
    {
      path: '/todo',
      name: 'todo',
      // component: Home
      component: () => import('../views/todoApp.vue')
    },
    {
      path: '/warehouse',
      name: 'warehouse',
      component: () => import('../views/barangWarehouse.vue')
    }
  ]
})

export default router

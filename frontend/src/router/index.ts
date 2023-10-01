/*
 * @Author: 睿超 刘 1152349903@qq.com
 * @Date: 2023-05-29 08:02:42
 * @LastEditors: 睿超 刘 1152349903@qq.com
 * @LastEditTime: 2023-06-15 19:48:31
 * @FilePath: \frontend\src\router\index.ts
 * @Description:
 *
 */
import { createRouter, createWebHistory, RouteRecordRaw } from "vue-router";

const routes: Array<RouteRecordRaw> = [
  {
    path: "/",
    name: "home",
    component: () => import("../views/HomeView.vue"),
  },
  {
    path: "/admin",
    name: "admin",
    component: () => import("../views/admin/AdminView.vue"),
  },
  {
    path: "/admin/department",
    name: "admdep",
    component: () => import("../views/admin/AdminView.vue"),
  },
  {
    path: "/admin/employee",
    name: "admemp",
    component: () => import("../views/admin/AdminView.vue"),
  },
  {
    path: "/admin/incent",
    name: "adminc",
    component: () => import("../views/admin/AdminView.vue"),
  },
  {
    path: "/admin/overtime",
    name: "admovt",
    component: () => import("../views/admin/AdminView.vue"),
  },
  {
    path: "/admin/admin",
    name: "admadm",
    component: () => import("../views/admin/AdminView.vue"),
  },
];

const router = createRouter({
  history: createWebHistory(process.env.BASE_URL),
  routes,
});

export default router;

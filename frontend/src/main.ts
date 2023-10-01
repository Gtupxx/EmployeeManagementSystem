/*
 * @Author: 睿超 刘 1152349903@qq.com
 * @Date: 2023-05-29 08:02:42
 * @LastEditors: 睿超 刘 1152349903@qq.com
 * @LastEditTime: 2023-05-31 17:33:35
 * @FilePath: \frontend\src\main.ts
 * @Description:
 *
 */
import { createApp } from "vue";
import App from "./App.vue";
import "./registerServiceWorker";
import router from "./router";
import store from "./store";
import ElementPlus from "element-plus";
import "element-plus/dist/index.css";
import * as ElementPlusIconsVue from "@element-plus/icons-vue";

const app = createApp(App);

for (const [key, component] of Object.entries(ElementPlusIconsVue)) {
  app.component(key, component);
}
app.use(store).use(ElementPlus).use(router);

app.mount("#app");

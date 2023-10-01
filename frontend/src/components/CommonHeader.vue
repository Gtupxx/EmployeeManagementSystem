<!--
 * @Author: 睿超 刘 1152349903@qq.com
 * @Date: 2023-05-29 21:56:38
 * @LastEditors: 睿超 刘 1152349903@qq.com
 * @LastEditTime: 2023-05-31 18:17:35
 * @FilePath: \frontend\src\components\CommonHeader.vue
 * @Description:  
 * 
-->
<template>
  <router-link to="/">
    <img
      alt="logo"
      src="../assets/280px-Girlsfrontline.webp"
      style="position: absolute; top: 0; left: 0; z-index: 9999"
      height="75"
    />
  </router-link>
  <router-view />
  <el-header style="text-align: right; font-size: 12px"></el-header>
  <slot></slot>
</template>

<script lang="ts">
export default {
  name: "CommonHeader",
};
</script>

<style scoped>
.el-header {
  height: 75px;
  width: 100%;
  position: absolute;
  top: 0;
  left: 0;
  background-color: rgba(0, 0, 0, 0.8);
  color: var(--el-text-color-primary);
}
</style>

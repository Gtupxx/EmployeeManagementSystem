<!--
 * @Author: 睿超 刘 1152349903@qq.com
 * @Date: 2023-05-29 08:02:42
 * @LastEditors: 睿超 刘 1152349903@qq.com
 * @LastEditTime: 2023-06-15 15:18:29
 * @FilePath: \frontend\src\App.vue
 * @Description: 
 * 
-->
<template>
  <div class="bg-image" id="app">
    <router-view></router-view>
  </div>
</template>

<style>
.bg-image {
  background-image: url(./assets/bg.jpg);
  background-size: cover;
  position: fixed;
  top: 0;
  left: 0;
  width: 100%;
  height: 100%;
  z-index: -1;
}
</style>

<style lang="stylus">
#app
 font-family Avenir, Helvetica, Arial, sans-serif
 -webkit-font-smoothing antialiased
 -moz-osx-font-smoothing grayscale
 text-align center
 color #2c3e50
 margin-top 0px
</style>

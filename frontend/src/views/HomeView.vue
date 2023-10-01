<!--
 * @Author: 睿超 刘 1152349903@qq.com
 * @Date: 2023-05-29 08:02:42
 * @LastEditors: 睿超 刘 1152349903@qq.com
 * @LastEditTime: 2023-05-31 17:13:14
 * @FilePath: \frontend\src\views\HomeView.vue
 * @Description:  
 * 
-->
<template>
  <div class="home"></div>
  <common-header> </common-header>
</template>

<script lang="ts">
import { defineComponent } from "vue";
import CommonHeader from "@/components/CommonHeader.vue";

export default defineComponent({
  name: "HomeView",
  components: { CommonHeader },
});
</script>

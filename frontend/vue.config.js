/*
 * @Author: 睿超 刘 1152349903@qq.com
 * @Date: 2023-05-29 08:02:42
 * @LastEditors: 睿超 刘 1152349903@qq.com
 * @LastEditTime: 2023-05-29 20:11:36
 * @FilePath: \人事管理系统\frontend\vue.config.js
 * @Description:
 *
 */
const { defineConfig } = require("@vue/cli-service");
module.exports = defineConfig({
  transpileDependencies: true,
});
module.exports = {
  pwa: {
    iconPaths: {
      favicon32: "icon.ico",
      favicon16: "icon.ico",
      appleTouchIcon: "icon.ico",
      maskIcon: "icon.ico",
      msTileImage: "icon.ico",
    },
  },
  chainWebpack: (config) => {
    config.module
      .rule("mp3")
      .test(/\.mp3$/)
      .use("file-loader")
      .loader("file-loader")
      .options({
        name: "[name].[hash:8].[ext]",
        outputPath: "assets",
        assetsDir: "static",
      });
  },
};

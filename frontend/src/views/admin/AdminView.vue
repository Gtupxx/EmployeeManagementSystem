<template>
  <common-header>
    <el-container class="adminview">
      <el-aside width="150px">
        <el-menu width="150px">
          <router-link to="/admin/employee">
            <el-menu-item index="employee">员工管理</el-menu-item>
          </router-link>
          <router-link to="/admin/department">
            <el-menu-item index="department">部门管理</el-menu-item>
          </router-link>
          <router-link to="/admin/incent">
            <el-menu-item index="incentive">奖惩管理</el-menu-item>
          </router-link>
          <router-link to="/admin/admin">
            <el-menu-item index="admin">高层管理</el-menu-item>
          </router-link>
          <router-link to="/admin/overtime">
            <el-menu-item index="overtime">加班管理</el-menu-item>
          </router-link>
        </el-menu>
      </el-aside>
      <el-main>
        <AdmEmp v-if="$route.path === '/admin/employee'"></AdmEmp>
        <AdmDep v-if="$route.path === '/admin/department'"></AdmDep>
        <AdmAdm v-if="$route.path === '/admin/admin'"></AdmAdm>
        <AdmInc v-if="$route.path === '/admin/incent'"></AdmInc>
        <AdmOvt v-if="$route.path === '/admin/overtm'"></AdmOvt>
      </el-main>
    </el-container>
  </common-header>
</template>

<script lang="ts" setup>
interface User {
  date: string;
  name: string;
  address: string;
}
</script>

<script lang="ts">
import CommonHeader from "@/components/CommonHeader.vue";
import AdmEmp from "@/views/admin/AdmEmp.vue";
import AdmDep from "@/views/admin/AdmDep.vue";
import AdmAdm from "@/views/admin/AdmAdm.vue";
import AdmInc from "@/views/admin/AdmInc.vue";
import AdmOvt from "@/views/admin/AdmOvt.vue";

export default {
  name: "AdminSide",
  components: {},
};
</script>

<style lang="scss" scoped>
// page-sizes选择器
::v-deep .el-select-dropdown__item li {
  background-color: transparent !important;
}
// prev和next箭头的样式
::v-deep .el-pagination .btn-next,
::v-deep .el-pagination .btn-prev {
  background: transparent !important;
  background-color: rgba(252, 185, 2, 0.327) !important;
}
// prev和next箭头disabled的样式
::v-deep .el-pagination button:disabled {
  background-color: transparent !important;
}
// 页码样式
::v-deep .el-pager li {
  background-color: transparent !important;
}
// active的页码样式
::v-deep .el-pager li.active {
  color: #ff2626 !important;
}
.table-wrapper {
  height: 80%;
  margin-top: 10px;
  ::v-deep .el-table--enable-row-hover .el-table__body tr:hover > td {
    background-color: rgba(0, 0, 0, 0.308);
    color: #fff;
  }
}

/* 删除表格下横线 */
.table-wrapper ::v-deep .el-table::before {
  left: 0;
  bottom: 0;
  width: 100%;
  height: 0px;
}

.table-wrapper ::v-deep .el-table,
.el-table__expanded-cell {
  background-color: transparent;
}

.table-wrapper ::v-deep .el-table tr {
  background-color: transparent !important;
}
.table-wrapper ::v-deep .el-table th {
  background-color: transparent !important;
  border-bottom: 1px solid transparent;
  color: #fff;
}
.table-wrapper ::v-deep .el-table td,
.el-table th.is-leaf {
  border-bottom: 3px solid #4f4f4f;
  background-color: rgba(0, 0, 0, 0.2);
  color: #fff;
}
</style>

<style>
a {
  text-decoration: none;
}

.router-link-active {
  text-decoration: none;
}
</style>
<style scoped>
.adminview .el-menu {
  background-color: rgba(0, 0, 0, 0.8);
  color: white;
  height: 100%;
  width: 150;
  position: fixed;
  top: 75px;
  left: 0px;
  border-right: none;
  text-align: center;
}
.adminview .el-menu-item {
  width: 150;
  color: #fff;
  text-align: center;
  display: flex;
  justify-content: center;
  align-items: center;
  font-size: 20px;
  line-height: 48px;
}
.adminview .el-main {
  background-color: rgba(0, 0, 0, 0.7);
  position: absolute;
  top: 75px;
  left: 120px;
  right: 0;
  bottom: 0;
  padding: 0;
}
.adminview .toolbar {
  display: inline-flex;
  align-items: center;
  justify-content: center;
  height: 100%;
  right: 20px;
}
.adminview .el-menu-item:hover {
  background-color: rgb(244, 196, 48);
  color: #fff;
}
</style>

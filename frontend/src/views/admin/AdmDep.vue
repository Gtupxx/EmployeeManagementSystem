<!--
 * @Author: 睿超 刘 1152349903@qq.com
 * @Date: 2023-06-11 23:25:02
 * @LastEditors: 睿超 刘 1152349903@qq.com
 * @LastEditTime: 2023-06-15 13:49:36
 * @FilePath: \frontend\src\views\admin\AdmDep.vue
 * @Description:  
 * 
-->
<template>
  <div class="table-wrapper">
    <el-table :data="displayData" style="width: 100%">
      <el-table-column
        label="部门号"
        prop="id"
        :fit="true"
        align="center"
        sortable
      >
        <template #default="scope">
          <div
            style="display: flex; align-items: center; justify-content: center"
          >
            <span style="margin-left: 10px">{{ scope.row.id }}</span>
          </div>
        </template>
      </el-table-column>
      <el-table-column label="部门名称" prop="name" :fit="true" align="center">
        <template #default="scope">
          <div
            style="display: flex; align-items: center; justify-content: center"
          >
            <span style="margin-left: 10px">{{ scope.row.name }}</span>
          </div>
        </template>
      </el-table-column>
      <el-table-column label="电话" prop="phone" :fit="true" align="center">
        <template #default="scope">
          <div
            style="display: flex; align-items: center; justify-content: center"
          >
            <span style="margin-left: 10px">{{ scope.row.phone }}</span>
          </div>
        </template>
      </el-table-column>
      <el-table-column
        label="管理员号"
        prop="adm"
        :fit="true"
        align="center"
        sortable
      >
        <template #default="scope">
          <div
            style="display: flex; align-items: center; justify-content: center"
          >
            <span style="margin-left: 10px">{{ scope.row.adm }}</span>
          </div>
        </template>
      </el-table-column>
      <el-table-column
        label="部门人数"
        prop="count"
        :fit="true"
        align="center"
        sortable
      >
        <template #default="scope">
          <div
            style="display: flex; align-items: center; justify-content: center"
          >
            <span style="margin-left: 10px">{{ scope.row.count }}</span>
          </div>
        </template>
      </el-table-column>
      <el-table-column width="180" align="center">
        <template #header>
          <el-button size="small" type="primary" @click="handleAdd"
            >添加</el-button
          >
        </template>
        <template #default="scope">
          <el-button size="small" @click="handleEdit(scope.$index, scope.row)"
            >编辑</el-button
          >
          <el-button
            size="small"
            type="danger"
            @click="handleDelete(scope.$index, scope.row)"
            >删除</el-button
          >
        </template>
      </el-table-column>
    </el-table>
    <el-pagination
      background
      layout="prev, pager, next"
      :total="totalLength"
      :page-size="10"
      @current-change="handlePageChange"
    />
    <!-- 编辑部门弹窗-->
    <el-dialog
      v-model="editVisible"
      title="修改部门信息"
      :close-on-click-modal="false"
    >
      <el-form model="form" ref="form">
        <el-form-item label="部门号" prop="id" label-width="100px">
          <el-input v-model="form_id" disabled placeholder="form_id"></el-input>
        </el-form-item>
        <el-form-item label="部门名称" prop="name" label-width="100px">
          <el-input v-model="form_name"></el-input>
        </el-form-item>
        <el-form-item label="电话" prop="phone" label-width="100px">
          <el-input
            v-model="form_phone"
            disabled
            placeholder="自动获取"
          ></el-input>
        </el-form-item>
        <el-form-item label="管理员号" prop="id" label-width="100px">
          <el-select v-model="form_adm" placeholder="admin id">
            <el-option
              v-for="item in admData"
              :key="item.id"
              :label="item.name"
              :value="item.id"
          /></el-select>
        </el-form-item>
        <el-button size="small" type="primary" @click="editConfirm"
          >确认</el-button
        >
        <el-button size="small" type="danger" @click="editCancle"
          >取消</el-button
        >
      </el-form>
    </el-dialog>
    <!-- 添加部门确认弹窗 -->
    <el-dialog
      v-model="addVisible"
      title="添加部门信息"
      :close-on-click-modal="false"
    >
      <el-form model="form" ref="form">
        <el-form-item label="部门号" prop="id" label-width="100px">
          <el-input v-model="form_id" disabled placeholder="form_id"></el-input>
        </el-form-item>
        <el-form-item label="部门名称" prop="name" label-width="100px">
          <el-input v-model="form_name"></el-input>
        </el-form-item>
        <el-form-item label="人数" prop="count" label-width="100px">
          <el-input v-model="form_count" disabled placeholder="0"></el-input>
        </el-form-item>
        <el-form-item label="管理员" prop="id" label-width="100px">
          <el-select v-model="form_adm" placeholder="admin id">
            <el-option
              v-for="item in admData"
              :key="item.id"
              :label="item.name"
              :value="item.id"
          /></el-select>
        </el-form-item>
        <el-button size="small" type="primary" @click="addConfirm"
          >确认</el-button
        >
        <el-button size="small" type="danger" @click="addCancle"
          >取消</el-button
        >
      </el-form>
    </el-dialog>
  </div>
</template>

<script lang="ts">
import axios from "axios";
import { defineComponent, Ref, onMounted, computed } from "vue";
import { ElMessage, ElMessageBox } from "element-plus";
import { ref } from "vue";

interface Department {
  id: string;
  name: string;
  adm: string;
  phone: string;
  count: number;
}
interface Admin {
  address: string;
  age: number;
  id: string;
  name: string;
  phone: string;
  pid: string;
  position: string;
  salary: number;
  sex: string;
}

export default defineComponent({
  name: "AdmAdm",
  setup() {
    const depData: Ref<Department[]> = ref([]);
    const admData: Ref<Admin[]> = ref([]);
    const totalLength: Ref<number> = ref(0);
    const pageSize = ref(10);
    const currentPage = ref(1); // 当前页码
    const editVisible = ref(false);
    const deleteVisible = ref(false);
    const addVisible = ref(false);
    const form_id: Ref<string> = ref("");
    const form_adm: Ref<string> = ref("");
    const form_name: Ref<string> = ref("");
    const form_phone: Ref<string> = ref("");
    const form_count: Ref<number> = ref(0);
    const handleAdd = () => {
      axios
        .get("http://localhost:7000/admin/admin")
        .then((response) => {
          console.log(response.data.data);
          admData.value = response.data.data;
          console.log(admData.value);
        })
        .catch((error) => {
          console.error(error);
        });
      const max = depData.value.reduce((acc, item) => {
        return parseInt(item.id) > acc ? parseInt(item.id) : acc;
      }, 0);
      const nextid = max + 1;
      form_id.value = nextid.toString();
      addVisible.value = true;
    };
    const handleEdit = (index: number, row: Department) => {
      axios
        .get("http://localhost:7000/admin/admin")
        .then((response) => {
          console.log(response.data.data);
          admData.value = response.data.data;
          console.log(admData.value);
        })
        .catch((error) => {
          console.error(error);
        });
      form_id.value = row.id;
      form_name.value = row.name;
      form_adm.value = row.adm;
      form_phone.value = row.phone;
      form_count.value = row.count;
      editVisible.value = true;
      console.log(index, row);
    };
    // 计算显示的数据
    const displayData = computed(() => {
      const start = (currentPage.value - 1) * pageSize.value;
      const end = start + pageSize.value;
      return depData.value.slice(start, end);
    });

    // 处理页码改变事件
    const handlePageChange = (newPage: number) => {
      currentPage.value = newPage;
    };

    const handleDelete = (index: number, row: Department) => {
      ElMessageBox.confirm("数据将会永久删除(真的很久！)", "警告", {
        confirmButtonText: "确认",
        cancelButtonText: "取消",
        type: "warning",
      })
        .then(() => {
          axios
            .delete(`http://localhost:7000/admin/depart/delete${row.id}`)
            .then((response) => {
              totalLength.value = response.data.Length;
              depData.value = response.data.data;
              console.log(`id=${row.id} has been deleted`);
            });
          console.log(index, row);
          ElMessage({
            type: "success",
            message: "删除成功",
          });
        })
        .catch(() => {
          ElMessage({
            type: "info",
            message: "删除取消",
          });
        });
    };

    onMounted(() => {
      axios
        .get("http://localhost:7000/admin/depart")
        .then((response) => {
          console.log(response.data.data);
          totalLength.value = response.data.Length;
          depData.value = response.data.data;
          console.log(depData.value);
        })
        .catch((error) => {
          console.error(error);
        });
    });
    const editConfirm = () => {
      const postData: Department = {
        id: form_id.value,
        name: form_name.value,
        adm: form_adm.value,
        phone: form_phone.value,
        count: form_count.value,
      };
      console.log(postData);
      axios
        .post(
          "http://localhost:7000/admin/depart/edit",
          {
            postData,
          },
          {
            headers: {
              "Content-Type": "application/json",
            },
          }
        )
        .then((response) => {
          totalLength.value = response.data.Length;
          depData.value = response.data.data;
          editVisible.value = false;
          ElMessage({
            type: "success",
            message: "编辑成功",
          });
        });
    };
    const editCancle = () => {
      editVisible.value = false;
      ElMessage({
        type: "info",
        message: "编辑取消",
      });
    };
    const addConfirm = () => {
      const postData: Department = {
        id: form_id.value,
        name: form_name.value,
        adm: form_adm.value,
        phone: form_phone.value,
        count: form_count.value,
      };
      console.log(postData);
      axios
        .post(
          "http://localhost:7000/admin/depart/add",
          {
            postData,
          },
          {
            headers: {
              "Content-Type": "application/json",
            },
          }
        )
        .then((response) => {
          totalLength.value = response.data.Length;
          depData.value = response.data.data;
          addVisible.value = false;
          ElMessage({
            type: "success",
            message: "添加成功",
          });
        });
    };
    const addCancle = () => {
      addVisible.value = false;
      ElMessage({
        type: "info",
        message: "添加取消",
      });
    };

    return {
      depData,
      admData,
      form_id,
      form_adm,
      form_name,
      form_phone,
      form_count,
      displayData,
      totalLength,
      editVisible,
      addVisible,
      deleteVisible,
      editConfirm,
      editCancle,
      addConfirm,
      addCancle,
      handleAdd,
      handlePageChange,
      handleEdit,
      handleDelete,
    };
  },
});
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
  background-color: rgba(89, 84, 14, 0.267) !important;
}
// prev和next箭头disabled的样式
::v-deep .el-pagination button:disabled {
  background-color: rgba(150, 0, 0, 0.579) !important;
}
// 页码样式
::v-deep .el-pager li {
  background-color: transparent !important;
}
// active的页码样式
::v-deep .el-pager li.active {
  color: #267aff !important;
}
.el-pagination {
  bottom: 0;
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

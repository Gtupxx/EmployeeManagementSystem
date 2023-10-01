<!--
 * @Author: 睿超 刘 1152349903@qq.com
 * @Date: 2023-06-11 23:25:02
 * @LastEditors: 睿超 刘 1152349903@qq.com
 * @LastEditTime: 2023-06-15 14:36:14
 * @FilePath: \frontend\src\views\admin\AdmAdm.vue
 * @Description:  
 * 
-->
<template>
  <div class="table-wrapper">
    <el-table :data="displayData" style="width: 100%">
      <el-table-column
        label="管理员号"
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
      <el-table-column label="姓名" prop="name" :fit="true" align="center">
        <template #default="scope">
          <div
            style="display: flex; align-items: center; justify-content: center"
          >
            <span style="margin-left: 10px">{{ scope.row.name }}</span>
          </div>
        </template>
      </el-table-column>
      <el-table-column
        label="性别"
        prop="sex"
        :fit="true"
        align="center"
        sortable
      >
        <template #default="scope">
          <div
            style="display: flex; align-items: center; justify-content: center"
          >
            <span style="margin-left: 10px">{{ scope.row.sex }}</span>
          </div>
        </template>
      </el-table-column>
      <el-table-column
        label="年龄"
        prop="age"
        :fit="true"
        align="center"
        sortable
      >
        <template #default="scope">
          <div
            style="display: flex; align-items: center; justify-content: center"
          >
            <span style="margin-left: 10px">{{ scope.row.age }}</span>
          </div>
        </template>
      </el-table-column>
      <el-table-column label="部门" prop="position" :fit="true" align="center">
        <template #default="scope">
          <div
            style="display: flex; align-items: center; justify-content: center"
          >
            <span style="margin-left: 10px">{{ scope.row.position }}</span>
          </div>
        </template>
      </el-table-column>
      <el-table-column label="住址" prop="address" :fit="true" align="center">
        <template #default="scope">
          <div
            style="display: flex; align-items: center; justify-content: center"
          >
            <span style="margin-left: 10px">{{ scope.row.address }}</span>
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
      <el-table-column label="身份证号" prop="pid" :fit="true" align="center">
        <template #default="scope">
          <div
            style="display: flex; align-items: center; justify-content: center"
          >
            <span style="margin-left: 10px">{{ scope.row.pid }}</span>
          </div>
        </template>
      </el-table-column>
      <el-table-column
        label="月薪"
        prop="salary"
        :fit="true"
        align="center"
        sortable
      >
        <template #default="scope">
          <div
            style="display: flex; align-items: center; justify-content: center"
          >
            <span style="margin-left: 10px">{{ scope.row.salary }}</span>
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
    <!-- 编辑用户弹窗-->
    <el-dialog
      v-model="editVisible"
      title="修改管理员信息"
      :close-on-click-modal="false"
    >
      <el-form model="form" ref="form">
        <el-form-item label="管理员号" prop="id" label-width="100px">
          <el-input v-model="form_id" disabled placeholder="form_id"></el-input>
        </el-form-item>
        <el-form-item label="姓名" prop="name" label-width="100px">
          <el-input v-model="form_name"></el-input>
        </el-form-item>
        <el-form-item label="性别" prop="sex" label-width="100px">
          <el-select v-model="form_sex" placeholder="form_sex">
            <el-option
              v-for="item in sex_select"
              :key="item.value"
              :label="item.label"
              :value="item.value"
          /></el-select>
        </el-form-item>
        <el-form-item label="年龄" prop="age" label-width="100px">
          <el-slider
            v-model="form_age"
            show-input
            :min="18"
            :max="65"
            :step="1"
          />
        </el-form-item>
        <el-form-item label="部门" prop="position" label-width="100px">
          <el-input v-model="form_position"></el-input>
        </el-form-item>
        <el-form-item label="住址" prop="address" label-width="100px">
          <el-input v-model="form_address"></el-input>
        </el-form-item>
        <el-form-item label="电话" prop="phone" label-width="100px">
          <el-input v-model="form_phone"></el-input>
        </el-form-item>
        <el-form-item label="身份证号" prop="pid" label-width="100px">
          <el-input v-model="form_pid"></el-input>
        </el-form-item>
        <el-form-item label="月薪" prop="salary" label-width="100px">
          <el-slider
            v-model="form_salary"
            show-input
            :min="0"
            :max="100000"
            :step="100"
          />
        </el-form-item>
        <el-button size="small" type="primary" @click="editConfirm"
          >确认</el-button
        >
        <el-button size="small" type="danger" @click="editCancle"
          >取消</el-button
        >
      </el-form>
    </el-dialog>
    <!-- 添加用户确认弹窗 -->
    <el-dialog
      v-model="addVisible"
      title="添加管理员信息"
      :close-on-click-modal="false"
    >
      <el-form model="form" ref="form">
        <el-form-item label="管理员号" prop="id" label-width="100px">
          <el-input v-model="form_id" disabled placeholder="form_id"></el-input>
        </el-form-item>
        <el-form-item label="姓名" prop="name" label-width="100px">
          <el-input v-model="form_name"></el-input>
        </el-form-item>
        <el-form-item label="性别" prop="sex" label-width="100px">
          <el-select v-model="form_sex" placeholder="form_sex">
            <el-option
              v-for="item in sex_select"
              :key="item.value"
              :label="item.label"
              :value="item.value"
          /></el-select>
        </el-form-item>
        <el-form-item label="年龄" prop="age" label-width="100px">
          <el-slider
            v-model="form_age"
            show-input
            :min="18"
            :max="65"
            :step="1"
          />
        </el-form-item>
        <el-form-item label="部门" prop="position" label-width="100px">
          <el-input v-model="form_position"></el-input>
        </el-form-item>
        <el-form-item label="住址" prop="address" label-width="100px">
          <el-input v-model="form_address"></el-input>
        </el-form-item>
        <el-form-item label="电话" prop="phone" label-width="100px">
          <el-input v-model="form_phone"></el-input>
        </el-form-item>
        <el-form-item label="身份证号" prop="pid" label-width="100px">
          <el-input v-model="form_pid"></el-input>
        </el-form-item>
        <el-form-item label="月薪" prop="salary" label-width="100px">
          <el-slider
            v-model="form_salary"
            show-input
            :min="0"
            :max="100000"
            :step="100"
          />
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

const sex_select = [
  {
    value: "男",
    label: "男",
  },
  {
    value: "女",
    label: "女",
  },
];

export default defineComponent({
  name: "AdmAdm",
  setup() {
    const admData: Ref<Admin[]> = ref([]);
    const totalLength: Ref<number> = ref(0);
    const pageSize = ref(10);
    const currentPage = ref(1); // 当前页码
    const editVisible = ref(false);
    const deleteVisible = ref(false);
    const addVisible = ref(false);
    const form_address: Ref<string> = ref("");
    const form_age: Ref<any> = ref(0);
    const form_id: Ref<string> = ref("");
    const form_name: Ref<string> = ref("");
    const form_phone: Ref<string> = ref("");
    const form_pid: Ref<string> = ref("");
    const form_position: Ref<string> = ref("");
    const form_salary: Ref<any> = ref(0);
    const form_sex: Ref<string> = ref("");
    const handleAdd = () => {
      const max = admData.value.reduce((acc, item) => {
        return parseInt(item.id) > acc ? parseInt(item.id) : acc;
      }, 0);
      const nextid = max + 1;
      form_id.value = nextid.toString();
      addVisible.value = true;
    };
    const handleEdit = (index: number, row: Admin) => {
      form_address.value = row.address;
      form_age.value = row.age;
      form_id.value = row.id;
      form_name.value = row.name;
      form_phone.value = row.phone;
      form_pid.value = row.pid;
      form_position.value = row.position;
      form_salary.value = row.salary;
      form_sex.value = row.sex;

      editVisible.value = true;
      console.log(index, row);
    };
    // 计算显示的数据
    const displayData = computed(() => {
      const start = (currentPage.value - 1) * pageSize.value;
      const end = start + pageSize.value;
      return admData.value.slice(start, end);
    });

    // 处理页码改变事件
    const handlePageChange = (newPage: number) => {
      currentPage.value = newPage;
    };

    const handleDelete = (index: number, row: Admin) => {
      ElMessageBox.confirm("数据将会永久删除(真的很久！)", "警告", {
        confirmButtonText: "确认",
        cancelButtonText: "取消",
        type: "warning",
      })
        .then(() => {
          axios
            .delete(`http://localhost:7000/admin/admin/delete${row.id}`)
            .then((response) => {
              totalLength.value = response.data.Length;
              admData.value = response.data.data;
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
        .get("http://localhost:7000/admin/admin")
        .then((response) => {
          console.log(response.data.data);
          totalLength.value = response.data.Length;
          admData.value = response.data.data;
          console.log(admData.value);
        })
        .catch((error) => {
          console.error(error);
        });
    });
    const editConfirm = () => {
      const postData: Admin = {
        address: form_address.value,
        age: parseInt(form_age.value),
        id: form_id.value,
        name: form_name.value,
        phone: form_phone.value,
        pid: form_pid.value,
        position: form_position.value,
        salary: parseFloat(form_salary.value),
        sex: form_sex.value,
      };
      console.log(postData);
      axios
        .post(
          "http://localhost:7000/admin/admin/edit",
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
          admData.value = response.data.data;
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
      const postData: Admin = {
        address: form_address.value,
        age: parseInt(form_age.value),
        id: form_id.value,
        name: form_name.value,
        phone: form_phone.value,
        pid: form_pid.value,
        position: form_position.value,
        salary: parseFloat(form_salary.value),
        sex: form_sex.value,
      };
      console.log(postData);
      axios
        .post(
          "http://localhost:7000/admin/admin/add",
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
          admData.value = response.data.data;
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
      admData,
      form_address,
      form_age,
      form_id,
      form_name,
      form_phone,
      form_pid,
      form_position,
      form_salary,
      form_sex,
      displayData,
      totalLength,
      editVisible,
      addVisible,
      deleteVisible,
      sex_select,
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

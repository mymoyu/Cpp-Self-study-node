<template>
<div>
  <div class="top-img">
    <img src="../../assets/img/Register/logo_u58.png">
  </div>
  <div class="section">
    <!-- 选项界面 -->
    <div class="select-option">
      <ul>
        <li><router-link :to="{name:'PhoneRegister'}" class="active-router">账号注册</router-link></li>
        <li><router-link :to="{name:'FindPassword'}" class="active-router">找回密码</router-link></li>
        <li><router-link :to="{name:'ChangeMail'}" class="active-router">邮箱改绑</router-link></li>
        <li><router-link :to="{name:'ChangePhone'}" class="active-router">手机改绑</router-link></li>
      </ul>
      <router-link to="/login" class="back-btn">
        返回登录
      </router-link>
    </div>
    <div class="view">
      <router-view></router-view>
    </div>
  </div>
</div>
</template>

<script>
export default {
  name:'MessagePage',
}
</script>

<style scoped>
.top-img {
  @apply w-96;
  height: 6.9rem;
}

.top-img img{
  @apply w-full h-full;
}

/* 左侧选择框 */
.select-option {
  @apply w-52 border-t-2 border-r-2;
  border-color: #6a85e0;
}

/* 每个选项的均高 */
.select-option li {
  margin-bottom: 11px;
}

.select-option a{
  display: block;
  @apply text-2xl px-12 py-4 relative;
  font-family: '黑体';
}

.select-option > ul > li > a {
  /* 该方法可以用来消除盒子缝隙 */
  top: -0.2px;
  right: -0.2px;
}

/* 右侧窗口设置 */
.view {
  @apply w-10/12 border-t-2;
  border-color: #6a85e0;
}

/* 中间部位设置 */
.section {
  @apply flex relative font-bold;
  max-width: 1700px;
  min-width: 1024px;
  min-height: 610px;
  color: #6a85e0;
}

/* 设置返回键位置 */
.back-btn {
  @apply relative;
  top: 270px;
}

.active-router.router-link-active {
  @apply text-white;
  background-color: #6a85e0;
}

</style>
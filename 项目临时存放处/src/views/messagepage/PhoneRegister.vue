<template>
  <div>
    <div class="register">
      <router-link :to="{name:'PhoneReg'}" class="active-router">手机注册</router-link>
      <router-link :to="{name:'MailReg'}" class="active-router">邮箱注册</router-link>
    </div>
  </div>
  <div class="Z-index">
    <transition name="view">
      <router-view></router-view>
    </transition>
  </div>
</template>

<script>
export default {
  name:'PhoneRegister',
}
</script>

<style scoped>
.register {
  @apply flex place-content-center mt-2;
}
.register a{
  display: inline-block;
  @apply text-2xl px-16 py-3 border-b-2;
  border-block-color: #6a85e0;
}
/* 路由选择激活 */
.active-router.router-link-active {
  @apply text-white;
  background-color: #6a85e0;
}

/* 切换路由页面效果 */
.view-enter-active {
    animation: viewchange 0.8s;
}

/* 离开时候激活的 */
.view-leave-active {
    animation: viewchange 0.8s reverse;
}

@keyframes viewchange {
    from {
      opacity: 0;
      transform: translateX(70%);
    }
    to {
        transform: translateX(0%);
    }
}
</style>
<template>
<div class="basic-layout">
  <div class="login-bar">
    <div>
        <div>
            <label for="uid">账号: </label>
            <input type="text" id="uid">
        </div>
        <div>
            <label for="password">密码: </label>
            <input type="password" id="password">
        </div>
    </div>
    <div class="change-password">
        <router-link :to="{name:'FindPassword'}">忘记密码</router-link>
    </div>
    <!-- 注册路由 -->
    <div class="register">
        <router-link to="/messagepage">
            没有账号? 立即注册!
        </router-link>
    </div>
  </div>
      <a class="login-ball">
        <div>登录</div>
        <svg class="h-16 w-16" fill="none" viewBox="0 0 24 24" stroke="white">
        <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M9 5l7 7-7 7" />
        </svg>
    </a>
</div>
</template>

<script>
export default {
    name:'Login',
}
</script>

<style scoped>
.basic-layout{
    background-color: #6a85e0;
}

.login-bar {
    @apply border rounded-xl w-7/12 max-w-2xl relative md:flex-shrink-0 shadow-xl z-50;
    background-color: #dde3f9;
}

.login-bar > div:nth-of-type(1){
    @apply mt-20 mx-16;
}

.login-bar > div > div{
    @apply mb-5 flex;
}

.login-bar label {
    @apply text-4xl font-bold w-40;
    color: #5c73c2;
}

.login-bar input {
    @apply w-full h-14 rounded-3xl relative text-3xl outline-none shadow-md;
    top: -5px;
    text-indent: 1rem;
}

/* 忘记密码 */
.change-password {
    @apply text-center text-xl mb-5;
    color: #5c73c2;
}

.change-password a {
    @apply hover:underline;
    @apply hover:text-gray-600;
}

/* 注册 */
.register a{
    @apply w-full block rounded-b-xl h-28 flex items-center place-content-center text-4xl text-gray-100 border-0;
    background: #63c5ef;
}

.register :hover {
    @apply opacity-80;
    font-size: 2.5rem;
    line-height: 3rem;
}

/* 登录小球 */
.login-ball {
    @apply relative w-52 h-52 rounded-full;
    background: #63c5ef;
    left: -170px;
}

.login-ball div{
    @apply text-6xl text-white relative font-bold;
    top: 75px;
    left: 45px;
}

.login-ball svg {
    @apply relative;
    top: 58px;
    left: 36px;
}

.login-ball div, svg{
    @apply inline-block;
}

/* 当移动到此处时 */
.login-ball:hover {
    animation: fadein 0.6s ease-in-out alternate;
    animation-fill-mode:forwards;
    /* left: 0; */
}
.login-ball:hover svg {
    @apply opacity-0;
}
/* 此时的弹窗动画 */
@keyframes fadein {
    0% {
        transform: translateX(0);
    }
    65% {
        transform: translateX(200px);
    }
    85% {
        transform: translateX(150px);
    }
    100% {
        transform: translateX(170px);
    }
}
</style>
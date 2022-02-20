<template>
  <div class="mainclass">
    <div>
      <div class="title">
        <div>找回密码</div> 
      </div>
      <div class="phone">
        <div>
            <span>手机号</span>：
            <input type="text" placeholder="请输入手机号">
        </div>
        <div>
            <span>短信验证码</span>：
            <input type="text" placeholder="请输入6位验证码">
            <button>获取验证码</button>
        </div>
      </div>
      <div class="reg-btn">
        <button>下一步</button>
      </div>
    </div>
  </div>
</template>

<script>
export default {
  name:'FindPassword',
  
}
</script>

<style scoped>
  .mainclass {
      @apply pl-24 pt-24 text-2xl;
      font-family: '黑体';
  }
  .mainclass input {
    @apply outline-none;
    width: 360px;
  }
  .mainclass span {
      display: inline-block;
      @apply w-40 text-justify;
      /* 加上该句可以使得文本双端对齐 */
      text-align-last:justify; 
  }

  .phone {
    @apply text-center mt-24;
  }
  .phone div {
    @apply mb-6;
  }
  .phone > div:nth-of-type(1) {
    @apply pr-6;
  }
  .phone > div:nth-of-type(2) > input{
      @apply w-48 mr-20;
  }
  .phone button {
      @apply text-base font-bold text-gray-50 p-4 rounded-full;
      background-color: #6a85e0;
  }

  /* 标题 */
  .title{
    @apply flex place-content-center text-4xl;
  }
  .title > div {
    @apply pb-2 w-48 text-justify;
    border-bottom: #6a85e0 3px solid;
    text-align-last: justify;
  }

  /* 注册键 */
  .reg-btn {
      @apply flex place-content-center;
  }
  .reg-btn button{
      @apply text-3xl my-6 py-5 px-20 rounded-full bg-gray-300 text-gray-50;
  }

  /* 注册键被激活 */
  .reg-btn-active {
      background-color: #6a85e0;
  }
</style>
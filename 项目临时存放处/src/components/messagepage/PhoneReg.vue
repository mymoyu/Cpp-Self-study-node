<template>
  <div class="mainclass">
      <div class="phone">
        <div>
            <div class="focus-div">
                <span>手机号</span>：
                <input type="text" placeholder="请输入手机号" >
            </div>
        </div>
        <div>
            <div class="focus-div">
                <span>短信验证码</span>：
                <input type="text" placeholder="请输入6位验证码" >
            </div>
            <button>获取验证码</button>
        </div>
      </div>
      <div>
          <div>
              <div class="focus-div">
                <span>密码</span>：
                <input type="password" placeholder="请输入8到16位的密码">
              </div>
          </div>
          <div >
              <div class="focus-div">
                <span>确认密码</span>：
                <input type="password" placeholder="请重新输入密码">
              </div>
          </div>
      </div>
      <div class="reg-btn">
        <button>立即注册！</button>
      </div>
  </div>
</template>

<script>
export default {
    name:'PhoneReg',
}
</script>

<style scoped>
    .mainclass {
        @apply pl-24 pt-24;
        font-family: '黑体';
    }
    .mainclass > div > div{
        @apply mb-5 text-2xl;
    }
    /* 实现焦点事件处理 */
    .mainclass > div > div > div{
        @apply px-4 py-2 inline-block relative rounded-full;
        left: -1rem;
    }
    .mainclass input {
        @apply outline-none w-96;
    }
    .mainclass span {
        @apply inline-block w-40 text-justify;
        /* 加上该句可以使得文本双端对齐 */
        text-align-last:justify; 
    }

    /* 手机信息框 */
    .phone {
        @apply pb-4 mb-12;
        border-bottom: 3px #6a85e0 solid;
    }
    .phone > div:nth-of-type(2) input{
        @apply w-56;
    }
    .phone > div:nth-of-type(2) > div {
        @apply mr-20;
    }
    .phone button {
        @apply text-base font-bold text-gray-50 p-4 rounded-full;
        background-color: #6a85e0;
    }

    /* 注册键 */
    .reg-btn {
        @apply flex place-content-center;
    }
    .reg-btn button{
        @apply text-3xl my-6 py-5 pl-20 pr-16 rounded-full bg-gray-300 text-gray-50;
    }

    /* 注册键被激活 */
    .reg-btn-active {
        background-color: #6a85e0;
    }

    /* 焦点事件 */
    .focus-div:focus-within{
        @apply text-gray-50;
        background-color: #6a85e0;
    }


</style>
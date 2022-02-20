<template>
  <div class="mainclass">
    <div>
      <div class="title">
        <div>邮箱改绑</div> 
      </div>
      <div class="mail">
        <div>
            <span>邮箱</span>：
            <input type="text" placeholder="请输入原邮箱">
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
  name:'ChangeMail',
  
}
</script>

<style scoped>
  .mainclass {
      @apply pl-24 pt-24 text-2xl;
      font-family: '黑体';
  }
  .mainclass input {
    @apply outline-none w-64;
  }
  .mainclass span {
      display: inline-block;
      @apply w-20 text-justify;
      /* 加上该句可以使得文本双端对齐 */
      text-align-last:justify; 
  }

  .mail {
    @apply text-center mt-24;
  }
  .mail div {
    @apply mb-16;
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
捕获子元素的焦点事件, 类似于下面这种写法, 可以捕获到内部div

```css
<div class="focus-div">
<span>电子邮箱</span>：
<input type="text" placeholder="请输入电子邮箱(xxx@xxx.com)">
</div>    
/* 焦点事件 */
.focus-div:focus-within{
    @apply text-gray-50;
    background-color: #6a85e0;
}
```


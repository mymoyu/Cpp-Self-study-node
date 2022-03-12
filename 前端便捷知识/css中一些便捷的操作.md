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



富有变化的css动画表

| 值                    | 描述                                                         |
| --------------------- | ------------------------------------------------------------ |
| linear                | 规定以相同速度开始至结束的过渡效果（等于 cubic-bezier(0,0,1,1)）。(匀速) |
| ease                  | 规定慢速开始，然后变快，然后慢速结束的过渡效果（cubic-bezier(0.25,0.1,0.25,1)）（相对于匀速，中间快，两头慢）。 |
| ease-in               | 规定以慢速开始的过渡效果（等于 cubic-bezier(0.42,0,1,1)）（相对于匀速，开始的时候慢，之后快）。 |
| ease-out              | 规定以慢速结束的过渡效果（等于 cubic-bezier(0,0,0.58,1)）（相对于匀速，开始时快，结束时候间慢，）。 |
| ease-in-out           | 规定以慢速开始和结束的过渡效果（等于 cubic-bezier(0.42,0,0.58,1)）（相对于匀速，（开始和结束都慢）两头慢）。 |
| cubic-bezier(n,n,n,n) | 在 cubic-bezier 函数中定义自己的值。可能的值是 0 至 1 之间的数值。 |


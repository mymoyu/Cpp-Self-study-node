居中方法1

在外面套一层div, 然后在里面的div里写上该属性

```css
.father {
    positon:relative;
}
.son{
    margin:auto;
    position:absolute;
    上下左右都为0
}
```

居中方法2

```css
.father {
    display: flex;
    justify-content: center;
    align-items: center;
}
```


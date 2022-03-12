##### 安装

npm install tailwindcss@npm:@tailwindcss/postcss7-compat @tailwindcss/postcss7-compat postcss@^7 autoprefixer@^9

##### 创建配置文件

npx tailwindcss init

OR

npx tailwindcss init -fill

##### 在项目根目录下创建postcss.config.js文件

```js
// postcss.config.js
module.exports = {
  plugins: {
    tailwindcss: {},
    autoprefixer: {},
  }
}
```

最后再main.js中引入tainwind css

import "tailwindcss/tailwind.css"
##### 安装路由

npm install vue-router@4

##### 创建router配置项

先在src文件中创建router/index.js

```js
import {createWebHistory, createRouter} from 'vue-router'

const history = createWebHistory()

const router = new createRouter({
    history,
})

export default router
```

##### 最后在main.js中

```js
import router from './router'

const app = createApp(App)
app.use(router)
```


import {createWebHistory, createRouter} from 'vue-router'

import Login from '../views/Login.vue'
import MessagePage from '../views/messagepage/MessagePage.vue'
import PhoneRegister from '../views/messagepage/PhoneRegister.vue'
import FindPassword from '../views/messagepage/FindPassword.vue'
import ChangeMail from '../views/messagepage/ChangeMail.vue'
import ChangePhone from '../views/messagepage/ChangePhone.vue'
import PhoneReg from '../components/messagepage/PhoneReg.vue'
import MailReg from '../components/messagepage/MailReg.vue'

const history = createWebHistory()

const router = new createRouter({
    history,
    routes:[
        {
            path:'/',
            redirect:'/login',
        },
        {
            path:'/login',
            name:'Login',
            component:Login,
            meta: { title:'登录一下', }
        },
        {
            path:'/messagepage',
            name:'MessagePage',
            component:MessagePage,
            meta: { title:'注册', },
            redirect:'/messagepage/phoneregister',
            children:[
                {
                    path:'phoneregister',
                    name:'PhoneRegister',
                    component:PhoneRegister,
                    meta: { title:'账号注册', },
                    redirect:'/messagepage/phoneregister/phonereg',
                    children:[
                        {
                            path:'phonereg',
                            name:'PhoneReg',
                            component:PhoneReg,
                        },
                        {
                            path:'mailreg',
                            name:'MailReg',
                            component:MailReg
                        }
                    ],
                },
                {
                    path:'findpassword',
                    name:'FindPassword',
                    component:FindPassword,
                    meta: {title:'找回密码'},
                },
                {
                    path:'changemail',
                    name:'ChangeMail',
                    component:ChangeMail,
                    meta: {title:'邮箱改绑'}
                },
                {
                    path:'changephone',
                    name:'ChangePhone',
                    component:ChangePhone,
                    meta: {title:'手机改绑'}
                }
            ],
        }
    ],
})

router.beforeResolve((to, from, next) => {
    window.document.title = to.meta.title
    next()
})

export default router
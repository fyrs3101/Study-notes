# Git 恢复版本的两种方法

## reset
通过
'''
git log --oneline
'''
查看希望回退到的版本的 id

## revert
修改之前某个版本的内容而保存之后版本的更改
一开始依旧查看版本 id
进行更改
'''
git revert -n 版本号


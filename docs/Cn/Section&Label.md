# Part 1 : 段与标签
## 1.1 段
### 1.1.1 段的概念
---
段是用来组织数据和代码的.段在整一个编译,链接发挥着重要作用.([如图](https://github.com/bzjsmdl/Seed-Language/blob/main/docs/Cn/deepseek_mermaid_20260130_726ad1.png)AI生成)

### 1.1.2 定义段
***

我们可以使用关键字``sec``去定义一个段,如下:
```Seed
sec .text{
    /* Code */
}
```
类似于nasm中的:
```nasm
section .text
    ; Code 
```
<br>
除了.text, .data, .bss等传统段,还支持自定义段.如下:<br>

```
sec mySection(alloc, exec){

}
```
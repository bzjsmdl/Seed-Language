# Seed简介
 Seed 是一个开源的编程语言.<br>
 它的主旨: 抽象并透明.
<li>
    <strong>结构化汇编</strong>:<br>
    如果你想完成<code>将10移动到EAX中</code>:<br> 
    汇编: <code><strong>mov eax, 10  ; Intel  (AT&T: mov $10, %eax)</strong></code><br> Seed: <code><strong>10 => eax;</strong></code>.
</li>
<li>
    <strong>强大的宏系统</strong>:<br>
    在Seed, 我们有一些宏属性. 它们是 <strong>@text</strong>, <strong>@res</strong> (REServed, 不优化), <strong>@resa</strong> (REServed Assembly — 像C语言中的内联汇编), 和 <strong>@null</strong>.
</li>
<li>
    <strong>贴近汇编</strong>:<br>
       在别的高级语言里有很多关键字去比较, 比如 <strong>if</strong>, <strong>else</strong>, <strong>switch</strong>, 但在Seed只有 <strong>cmp</strong>.
</li>


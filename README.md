# Seed-Language
## Introduce Seed
 Seed is a open-source programming language.<br>
 Its mian idea: More <strong>abstract</strong> than Assembly, More <strong>transparent</strong> than C, More <strong>explicit</strong> than Python.
<li>
    <strong>Structure Assembly</strong>:<br>
    To move 10 into EAX:<br> Assembly: <code><strong>mov eax, 10  ; Intel  (AT&T: mov $10, %eax)</strong></code><br> Seed: <code><strong>10 => eax;</strong></code>.
</li>
<li>
    <strong>Strong Macro</strong>:<br>
    In Seed we have several macro attributes. They're <strong>@text</strong>, <strong>@res</strong> (REServed, not optimized), <strong>@resa</strong> (REServed Assembly — like C's inline assembly), and <strong>@null</strong>.
</li>
<li>
    <strong>Near Assembly</strong>:<br>
       In other high-level languages there are many control keywords, such as <strong>if</strong>, <strong>else</strong>, <strong>switch</strong>, but in Seed the primary comparison instruction is <strong>cmp</strong>.
</li>

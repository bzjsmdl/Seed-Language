# Seed-Language
## Project Structure
```text
                   repositoriy
                   /         \
                 src         wedsite
             (C,Assembly,Seed) (HTML/CSS/Javascript)
               /      \         /    \
             main     stdlib   docs  (some code)
        (C, Assembly)  (Seed)  (HTML)
```
## Introduce Seed
 Seed is a open-source programming language.<br>
 Its mian idea: <strong>abstract</strong> but <strong>transparent</strong>
- ### <strong>Structure Assembly</strong>:<br>
    To move 10 into EAX:<br> Assembly: <code><strong>mov eax, 10  ; Intel  (AT&T: mov $10, %eax)</strong></code><br> Seed: <code><strong>10 => eax;</strong></code>.
- ### <strong>Strong Macro</strong>:<br>
    In Seed we have several macro attributes. They're <strong>@text</strong>, <strong>@res</strong> (REServed, not optimized), <strong>@resa</strong> (REServed Assembly — like C's inline assembly), and <strong>@null</strong>.
- ### <strong>Near Assembly</strong>:<br>
    In other high-level languages there are many control keywords, such as <strong>if</strong>, <strong>else</strong>, <strong>switch</strong>, but in Seed the primary comparison instruction is <strong>cmp</strong>.
## Fast Start
Write this into ```a.seed```:
```seed
sec .text {
  pub main {
    nop;
  }
}
```
Complie it with this:
```bash
./seed32 -f ./a.seed -o asm ./a.s
# 64: ./seed64 -f ./a.seed -o asm ./a.s
nasm -f win32 ./a.s -o ./a.obj
# Go to https://www.nasm.us/pub/nasm/releasebuilds/ to dwonload it
gcc ./a.obj -o ./a.exe
./a.exe
```
If no error, it can run.


## Q & A
### Q: Can I submit a PR for the language?<br>
#### A: **No**. Because I'm worried that you'll **destory our language's uniqueness** and my code is **very bad**. But you still can **fork it down** or **provide issues**.

### Q: Do the language have docs?
#### A: No. But I try faster.

### Q: Do the language have a wedsite?
#### A: Yes!! Today(2026.4.26) it's online!!! Please go to [https://seed-lang.pages.dev](https://seed-lang.pages.dev).

## Another thing
- If you have any questions that haven't been asked here(Q & A), you can send a email to bzjsmdl88@qq.com or bzjsmdl@outlook.com.
- I translate ```README.md``` by means of ```Deepseek``` and ```GitHub Copilot```(I use VSCode to write the first README.md) else...

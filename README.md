# RePulsar
## Описание
Это PoC реализция SMB-бэкдора, основанная на собственном исследовании ядра Windows и механизма SMB. Так как это всего лишь PoC, особого функционала нету. В будущем планируется поддержка базового функционала:
- Произвольные чтение/запись в память
- Выполнение шеллкода
- Т.д.

Также планирутеся подробное описание работы данного механизма.
На текущий момент стабильно работает на:
- Windows 10 1809
- Windows 10 21H2

## Description
This is a PoC implementation of an SMB backdoor based on our own research into the Windows kernel and the SMB mechanism. Since this is just a PoC, there is no special functionality. In the future, it is planned to support the basic functionality:
- Arbitrary read/write memory
- Shellcode execution
- Etc.

A detailed description of the operation of this mechanism is also planned.
Currently working stably on:
- Windows 10 1809
- Windows 10 21H2

## Полезная литература / Useful information
https://blog.zecops.com/research/smbleedingghost-writeup-part-iii-from-remote-read-smbleed-to-rce

https://sec-in.com/article/1354

https://zhuanlan.zhihu.com/p/567559622
 

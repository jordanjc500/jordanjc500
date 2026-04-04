## Background

Essentially a passion project of mine. I have always wanted to make an idle game since Adventure Capitalist and Cookie Clicker were in their prime in 2013-2017. Being obssesed with math, numbers, and the dopamine of watching them climb exponentially while learning new names for powers of 1000 ending in -illion, I decided I wanted to explore both the logic and organization of the code which is deceptively simple, and the math behind the scaling and balancing (what makes it fun? Too fast paced? Too slow?)

## How to build

### Windows (MSVC / Developer PowerShell)
1. Open **Developer PowerShell for VS 18**.
2. Navigate to the project folder.
3. Compile using the Microsoft C++ compiler:
   ```powershell
   cl /EHsc Idle1.cpp
The executable will be created, and can be ran by simply typing Idle1.exe

## How it works
Currently, the game uses very simple cost scaling where the price of each generator increases by 10% for each one purchased. Represented by the simple formula $Cost = B \times 1.10^n$
Upgrades that directly increase production are in the works, and will multiply your income of a single generator or all of them by a given percentage.

### Controls
a: 'click' to generate money
q: quit game
numbers 0-9 (currently only 1,2,3): buy generator

<!--
**jordanjc500/jordanjc500** is a ✨ _special_ ✨ repository because its `README.md` (this file) appears on your GitHub profile.

Here are some ideas to get you started:

- 🔭 I’m currently working on ...
- 🌱 I’m currently learning ...
- 👯 I’m looking to collaborate on ...
- 🤔 I’m looking for help with ...
- 💬 Ask me about ...
- 📫 How to reach me: ...
- 😄 Pronouns: ...
- ⚡ Fun fact: ...
-->

# Octo
Octo is an experimental, "mostly" standards-compliant browser engine built from the ground up. Browser always seemed like black boxes to me, so this is my attempt at understanding the "how" of browser work.

## 📈 Progress
I try to follow the [w3c spec](https://w3.org) with some features removed to focus on the core parts of the browser.

- [x] HTML/CSS Parser
- [x] Simple Style engine
- [ ] Text shaping (in-progress)
- [ ] Layout engine (in-progress)
- [ ] Resource Management
- [ ] Browser frontend
- [ ] Simple scripting (likely lua or python for easy integration)

## 🏗️ Building from Source

### Prerequisites
* CMake 3.20+
* Qt 6.x
* FreeType & HarfBuzz
* PkgConfig
* Compiler with CXX17 support

### Build Instruction
```
git clone https://github.com/l3k4n/octo.git
cd octo
mkdir build && cd build
cmake ..
make
```

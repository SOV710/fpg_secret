# :)

你怎么能直接 commit 到我的 main 分支啊？！GitHub 上不是这样！你应该先 fork 我的仓库，然后从 develop 分支 checkout 一个新的 feature 分支，比如叫 feature/confession。然后你把你的心意写成代码，并为它写好单元测试和集成测试，确保代码覆盖率达到95%以上。接着你要跑一下 Linter，通过所有的代码风格检查。然后你再 commit，commit message 要遵循 Conventional Commits 规范。之后你把这个分支 push 到你自己的远程仓库，然后给我提一个 Pull Request。在 PR 描述里，你要详细说明你的功能改动和实现思路，并且 @ 我和至少两个其他的评审。我们会 review 你的代码，可能会留下一些评论，你需要解决所有的 thread。等 CI/CD 流水线全部通过，并且拿到至少两个 LGTM 之后，我才会考虑把你的分支 squash and merge 到 develop 里，等待下一个版本发布。你怎么直接上来就想 force push 到 main？！GitHub 上根本不是这样！我拒绝合并！

<img src="https://pic3.zhimg.com/80/v2-7c805c0c8a6034cfe7e3c3d8594b9e3a_720w.webp">

好吧，不发点了。这个考核 repo 是基于我在大一时搓的现代 C++ 算法板子搓出来的，而我是在高考完才开始学算法的，所以我想这个板子的算法部分应该是难不住你们的。我主要想考察在实际场合下，对"代码之外的知识"的掌握和学习能力，比如说 CMake, C++特性；另外考察在面对稍微有点大小的代码库时，使用各种工具阅读代码和报错的能力，以及基础的 debug 能力。

## Quick Start

前置要求:
- Linux
- CMake 3.15+
- Make
- GCC

```sh
git clone https://github.com/SOV710/fpg_secret.git .

cd fpg_secret
mkdir build
cmake ..
make

./bin/main
```

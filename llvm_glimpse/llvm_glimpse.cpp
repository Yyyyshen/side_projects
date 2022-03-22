// llvm_glimpse.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

//
//了解编译原理
//从llvm开始
//
//参考
//https://zhuanlan.zhihu.com/p/122522485
//https://llvm.org/docs/tutorial/index.html （官方）
//clang手册 https://clang.llvm.org/docs/UsersManual.html
//

//
//Learn LLVM 12 中文译本
// https://github.com/xiaoweiChen/Learn-LLVM-12
//

//
//环境准备、编译安装LLVM
// 
// 编译环境
//  yum/apt/pkg/brew/dnf install -y gcc g++ git cmake ninja-build
// 
// （centos默认cmake版本过低需要升级 https://www.programminghunter.com/article/9691688343/）
// 
// 克隆项目
//  git clone https://github.com/llvm/llvm-project.git
//  （或只克隆某版本分支 git clone --branch llvmorg-12.0.0 https://github.com/llvm/llvm-project）
// 
// 构建过程
// cd llvm-project
// mkdir build
// cd build
// 
// 要生成将使用 Ninja 编译 LLVM 和 Clang 的构建系统文件，运行以下命令:
//  $ cmake–G Ninja - DLLVM_ENABLE_PROJECTS=clang ../llvm
/* 生成选项说明
    -G 选项告诉 CMake 要为哪个系统生成构建文件。最常用的选项如下:
    • Ninja: 对应 Ninja 的构建系统
    • Unix Makefiles: 对应 GNU Make
    • Visual Studio 15 VS2017 和 Visual Studio 16 VS2019: 对应 Visual Studio 和 MS Build
    • Xcode: 对应 Xcode 工程
    可以使用-D 选项设置各种变量来影响生成过程。通常，以 CMAKE (由 CMAKE 定义) 或
    LLVM (由 LLVM 定义) 作为前缀。使用 LLVM ENABLE PROJECTS=clang 变量设置，CMake
    为 LLVM 之外的 Clang 生成构建文件。命令的最后一部分告诉 CMake 在哪里可以找到 LLVM 核
    心库源代码。
*/
// 
// 编译
// ninja -j2
// 检查
// ninja check-all
// 
// 编译内存不够，需使用虚拟空间
// https://blog.csdn.net/cz_jjq/article/details/79990501
//

int main()
{
    std::cout << "Hello World!\n";
}

/**
 * ps:
 * 2021/3/8 更新了vs 16.9.0，看日志好像很强，不过发现新版本在推送完项目到github会被拉黑一段时间，不知道是不是bug
 */
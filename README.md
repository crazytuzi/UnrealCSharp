<div align="center">

![Logo](Resources/Logo.png)

# UnrealCSharp

**🚀 强大的虚幻引擎C#编程插件**

*基于.NET 8 (Mono)，让您在虚幻引擎中享受现代C#开发体验*

[![license](https://img.shields.io/badge/license-MIT-blue?style=for-the-badge)](https://github.com/crazytuzi/UnrealCSharp/blob/master/LICENSE)
[![release](https://img.shields.io/github/v/release/crazytuzi/UnrealCSharp?style=for-the-badge&color=green)](https://github.com/crazytuzi/UnrealCSharp/releases)
[![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen?style=for-the-badge)](https://github.com/crazytuzi/UnrealCSharp/pulls)
[![UE Version](https://img.shields.io/badge/UE-5.0--5.5-orange?style=for-the-badge&logo=unrealengine)](https://unrealengine.com/)

[🎯 快速开始](#-快速开始) • [📖 文档](https://unrealcsharp.github.io/docs/) • [💬 社区](#-社区) • [🌟 特性](#-核心特性)

</div>

---

## 🌟 核心特性

<table>
<tr>
<td width="50%">

### 🔧 开发体验
- ✅ **自动代码生成** - 支持全部反射类型
- 🔄 **热重载** - 编辑器下即时刷新C#代码
- 🐛 **便捷调试** - 无缝集成IDE调试体验
- 📦 **热更新** - 通过Pak实现运行时更新

</td>
<td width="50%">

### ⚡ 强大功能
- 🏗️ **动态类系统** - 直接生成UClass/UInterface/UStruct/UEnum
- 🔗 **完整绑定** - 静态导出所有数据类型和函数
- 🌐 **跨平台支持** - Windows/macOS/Linux/Android/iOS
- 🎯 **无蓝图依赖** - 纯C#实现游戏逻辑

</td>
</tr>
</table>

## 🎯 快速开始

### 环境要求

| 组件 | 版本要求 |
|------|----------|
| **虚幻引擎** | 5.0 - 5.5 |
| **.NET** | 8.0+ |
| **平台** | Windows / macOS / Linux |

### 安装步骤

```bash
# 1. 克隆仓库
git clone https://github.com/crazytuzi/UnrealCSharp.git

# 2. 复制插件到项目
cp -r UnrealCSharp /path/to/your/project/Plugins/

# 3. 重新生成项目文件
# 在UE项目根目录右键选择 "Generate Visual Studio project files"
```

### 第一个C#脚本

```csharp
using UnrealCSharp.CoreUObject;

[DynamicClass]
public class MyActor : AActor
{
    protected override void BeginPlay()
    {
        base.BeginPlay();
        
        Unreal.PrintString(GetWorld(), "Hello from C#!", duration: 5.0f);
    }
}
```

> 💡 **提示**: 查看我们的[详细文档](https://unrealcsharp.github.io/docs/document/getting-started)了解更多示例

## 🏗️ 项目结构

```
UnrealCSharp/
├── 📁 Script/           # C# 脚本核心
│   ├── UE/             # 虚幻引擎API绑定
│   ├── Dynamic/        # 动态类型系统
│   └── Library/        # 工具库
├── 📁 Source/           # C++ 插件源码
├── 📁 Template/         # 项目模板
└── 📁 Resources/        # 资源文件
```

## 🚀 支持的平台

<div align="center">

| 平台 | 开发 | 打包发布 | 状态 |
|------|------|----------|------|
| Windows | ✅ | ✅ | 完全支持 |
| macOS | ✅ | ✅ | 完全支持 |
| Linux | ✅ | ✅ | 完全支持 |
| Android | ❌ | ✅ | 仅发布支持 |
| iOS | ❌ | ✅ | 仅发布支持 |

</div>

## 📚 学习资源

<div align="center">

| 资源类型 | 链接 | 描述 |
|----------|------|------|
| 📖 **入门指南** | [开始上手](https://unrealcsharp.github.io/docs/document/getting-started) | 从零开始学习 |
| 🏗️ **动态类** | [动态类文档](https://unrealcsharp.github.io/docs/document/getting-started/dynamic) | 深入了解动态类系统 |
| 🐛 **调试指南** | [调试文档](https://unrealcsharp.github.io/docs/document/guides/debug) | 调试技巧和最佳实践 |
| ❓ **FAQ** | [常见问题](https://unrealcsharp.github.io/docs/document/FAQ) | 解答常见疑问 |

</div>

## 💬 社区

<div align="center">

[![QQ群](https://img.shields.io/badge/QQ群-326576868-blue?style=for-the-badge&logo=tencentqq)](https://qm.qq.com/q/JW43uTiOk4)
[![Discord](https://img.shields.io/badge/Discord-加入我们-7289da?style=for-the-badge&logo=discord&logoColor=white)](https://discord.gg/mPVWhRqxC7)

**加入我们的社区，获取支持、分享经验、参与讨论！**

</div>

## 🤝 贡献者

感谢所有为项目做出贡献的开发者们！

<div align="center">

<a href="https://github.com/crazytuzi/UnrealCSharp/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=crazytuzi/UnrealCSharp" />
</a>

**[成为贡献者](https://github.com/crazytuzi/UnrealCSharp/blob/master/CONTRIBUTING.md)**

</div>

---

<div align="center">

**⭐ 如果这个项目对您有帮助，请给我们一个 Star！**

Made with ❤️ by the UnrealCSharp Team

</div>
    
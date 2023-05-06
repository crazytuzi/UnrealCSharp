#pragma once

/*
MIT License
Copyright (c) 2021 JomiXedYu
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "CoreMinimal.h"


/*
 * 转义规则：
 * 对在a-z A-Z 0-9 _ 以外 并在[0, 127]的ascii范围内的可见字符进行转义
 * _h 会被视作转义符，对后面的内容进行转义
 * 转义结果为 _h + ascii码 + _ ，如字符 - 会被转换为 _h2D_
 * 如原字符串中存在转义符 _h ，那么会将转义符转义为下划线的ascii码， 字符串 _h 将被转换为 _h5F_
 * 以数字开头的字符串，将会在前面添加_h01_转义，如 3DWidget 转换为 _h01_3DWidget
 * 单下划线不会被转义
 * 支持为宽字符（ascii大于127）转义，需bEncodeWideString为true。例 技能3 将会被转义为 _hu8062FD80_3
 */

class FNameEncode
{
public:
	static UNREALCSHARPCORE_API FString Encode(const FString& InName, bool bEncodeWideString = false);

	static UNREALCSHARPCORE_API void Encode(TArray<FString>& InNames);

	static UNREALCSHARPCORE_API FString Decode(const FString& InName);

	static UNREALCSHARPCORE_API void Decode(TArray<FString>& InNames);
};

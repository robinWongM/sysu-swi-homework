---
layout: default
title: Lab 04 - What The F**k JavaScript - JS 中的一些奇妙行为
---

JavaScript is beautiful, right? 但由于 ECMAScript 在设计之初时的各种考虑不周（或者说 Fe ature），使得某些 JavaScript 代码会得到一些意想不到的结果。了解这些例子，除了能够让你感受到 JavaScript 的 crazy，还能对 JavaScript 的部分特性有更深的理解。

## 1. parseInt

```
parseInt("f*ck"); // -> NaN
parseInt("f*ck", 16); // -> 15
```

WoW，原来十进制下 f*ck 是 NaN，怎么到了十六进制下就变成 15 了呢？

Explaination: parseInt 会逐个解析字符，直到遇见它不认识的字符。在十进制中，f 不对应任何一个数字，故输出 NaN；而在十六进制中，f 对应 15，而 * 没有对应的数字，故输出 15。

所以，在转换 Infinity（无穷大）和 null 时也要小心一点哟：

```
//
parseInt("Infinity", 10); // -> NaN
// ...
parseInt("Infinity", 18); // -> NaN...
parseInt("Infinity", 19); // -> 18
// ...
parseInt("Infinity", 23); // -> 18...
parseInt("Infinity", 24); // -> 151176378
// ...
parseInt("Infinity", 29); // -> 385849803
parseInt("Infinity", 30); // -> 13693557269
// ...
parseInt("Infinity", 34); // -> 28872273981
parseInt("Infinity", 35); // -> 1201203301724
parseInt("Infinity", 36); // -> 1461559270678...
parseInt("Infinity", 37); // -> NaN
// 
parseInt(null, 24); // -> 23
```

Infinity 可能比较好理解，而 null 在被 parseInt 处理时会被转换成字符串 `"null"`。强制转换成字符串也适用于其他传给 parseInt 的第一个参数，比如：

```
parseInt({ toString: () => 2, valueOf: () => 1 }); // -> 2
Number({ toString: () => 2, valueOf: () => 1 }); // -> 1
```

此外在转换小数时也要格外小心：

```
parseInt(0.000001); // -> 0
parseInt(0.0000001); // -> 1
parseInt(1 / 1999999); // -> 5
```

这同样是强制转换成字符串时导致的。第一个 0.000001 会被转换成 `"0.000001"`，而第二个 0.0000001 会被转换为 `"1e-7"`，第三个会被转换成 `"5.00000250000125e-7"`，这样就好解释了（

## 2. 奇妙的数学

```
 3  - 1  // -> 2
 3  + 1  // -> 4
'3' - 1  // -> 2
'3' + 1  // -> '31'

'' + '' // -> ''
[] + [] // -> ''
{} + [] // -> 0
[] + {} // -> '[object Object]'
{} + {} // -> '[object Object][object Object]'

'222' - -'111' // -> 333

[4] * [4]       // -> 16
[] * []         // -> 0
[4, 4] * [4, 4] // NaN
```

Interesting, right?

Explaination: JavaScript 对于不同类型的加法执行以下规则：

> Number  + Number  -> addition
> Boolean + Number  -> addition
> Boolean + Boolean -> addition
> Number  + String  -> concatenation
> String  + Boolean -> concatenation
> String  + String  -> concatenation

而对于 {} 和 []，JS 引擎会调用内部的抽象操作方法 ToPrimitive 方法获得其原始值，其中会调用该对象的 toString 方法<sup>[来源请求]</sup>，{} 得到 `[object Object]`，[] 得到 `''`，再按照以上规则进行相加。

## 3. 箭头函数

先看这个例子：

```
let f = () => 10;
f(); // -> 10
```

好的，好像没什么问题，那这个呢？

```
let f = () => {};
f(); // -> undefined
```

为什么是 `undefined` 而不是 `{}` 呢？因为 `{}` 是语句块的标志，而这个块中没有 return 任何表达式，所以其返回值为 `undefined`。

## 4. Math.min() -> Infinity

```
Math.min(1, 4, 7, 2); // -> 1
Math.max(1, 4, 7, 2); // -> 7
Math.min(); // -> Infinity
Math.max(); // -> -Infinity
Math.min() > Math.max(); // -> true
```

持续颠覆数学三观。

Explaination: 其实 `Math.min` 的功能是返回一系列数字中的最小数字，而当没有参数传进去时，它[返回的是 Infinity](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Math/min#Return_value)。为什么是这么设计呢？

考虑一下 Math.min 只有一个参数时的情况，比如 `Math.min(5)`。自然地，这个表达式应该得到一个为 5 的值，但是这个 5 是相对于哪个（些）数字来说是最小的呢？在这种情况下，将 5 与 Infinity 进行比较是最佳选择。

## 5. More

本文的内容均来自于 (What the f*ck JavaScript?)[https://github.com/denysdovhan/wtfjs]（© Denys Dovhan, Licensed under WTFPL)，里面还有很多有趣的例子（

希望你能够爱上这门语言x
### 进展

1. 递归下降的语法分析已完成
2. 基于预测表的语法分析debuging...

### 运行

- 预测表相关单独编译`make table`并执行`table`，得到FIRST、FOLLOW集合以及预测表
- 主体部分编译`make`并执行`parser`

### 内部结构

终结符内码表：

| 内码 | 单词       | 内码 | 单词      | 内码 | 单词 | 内码 | 单词    |
| ---- | ---------- | ---- | --------- | ---- | ---- | ---- | ------- |
| 1    | PROGRAM    | 2    | CONST     | 3    | VAR  | 4    | INTEGER |
| 5    | LONG       | 6    | PROCEDURE | 7    | IF   | 8    | THEN    |
| 9    | WHILE      | 10   | DO        | 11   | READ | 12   | WRITE   |
| 13   | BEGIN      | 14   | END       | 15   | ODD  | 16   | +       |
| 17   | -          | 18   | *         | 19   | /    | 20   | =       |
| 21   | <>         | 22   | <         | 23   | <=   | 24   | >       |
| 25   | >=         | 26   | ,         | 27   | .    | 28   | ;       |
| 29   | :          | 30   | :=        | 31   | (    | 32   | )       |
| 33   | 无符号整数 | 34   | 标识符    | 35   | #    |      |         |

非终结符内码表：

- epsilon 0
- program 128
- programhead 129
- block 130
- constexp 131
- constdef 132
- varexp 133
- constsuff 134
- vardef 135
- varsuff 136
- prodef 137
- type 138
- prohead 139
- prosuff 140
- assign_or_call 141
- sentence 142
- suffix 143
- ifsent 144
- read 145
- whilesent 146
- idsuff 147
- write 148
- compsent 149
- exprsuff 150
- sentsuff 151
- condition 152
- termsuff 153
- express 154
- term 155
- factorsuff 156
- argument 157
- factor 158
- addopt 159
- mulopt 160
- relationopt 161

消除左递归的语法：

- <program>→<programhead><block>DOT
- <programhead>→PROGRAM标识符SEMICOLON
- <block>→<constexp><varexp><prodef> <compsent>
- <constexp>→CONST<constdef><constsuff> |ε
- <constdef>→标识符EQUAL无符号整数
- <constsuff>→COMMA<constdef><constsuff> |ε
- <varexp>→VAR<vardef><varsuff> |ε
- <vardef>→标识符<idsuff>COLON<type>SEMICOLON
- <idsuff>→COMMA标识符<idsuff> |ε
- <varsuff>→<vardef><varsuff> |ε
- <type>→INTEGER | LONG
- <prodef>→<prohead><block>SEMICOLON<prosuff>|ε
- <prohead>→PROCEDURE标识符<argument>SEMICOLON
- <argument>→(标识符COLON<type>)|ε
- <prosuff>→<prohead><block>SEMICOLON<prosuff>|ε
- <sentence>→<assign_or_call>|<ifsent>|<whilesent>|<read>|<write>|<compsent>|ε
- <assign_or_call>→标识符<suffix>
- <suffix>→ASSIGN<express>|(<express>)|ε
- <ifsent>→IF<condition>THEN<sentence>
- <whilesent>→WHILE<condition>DO <sentence>
- <read>→READ（标识符<idsuff>）
- <write>→WRITE（<express><exprsuff>）
- <exprsuff>→COMMA<express><exprsuff>|ε
- <compsent>→BEGIN<sentence><sentsuff>END
- <sentsuff>→SEMICOLON<sentence><sentsuff>|ε
- <condition>→<express><relationopt><express>|ODD<express>
- <express>→ADD<term><termsuff>|MIN<term><termsuff>|<term><termsuff>
- <termsuff>→<addopt><term><termsuff>|ε
- <term>→<factor><factorsuff>
- <factorsuff>→<mulopt><factor><factorsuff>|ε
- <factor>→标识符|无符号整数|（<express>）
- <addopt>→+|-
- <mulopt>→*|/
- <relationopt>→ =|<>|<|<=|>|>=
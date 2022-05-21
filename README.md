### 进展

1. 递归下降的语法分析已完成
2. 基于预测表的语法分析已完成

### 编译

- 预测表相关单独编译`make table`并执行`table`，得到FIRST、FOLLOW集合以及预测表
- 主体部分编译`make`并执行`parser`

### 运行

默认运行`parser`， 执行基于预测表的语法分析

**参数**

- `-p`：执行基于预测表的语法分析
- `-r`：执行基于递归下降的语法分析

### 预测分析表

(由于相关算法几经修改而测试样例没有经过所有分支，parser.cpp处的硬编码部分有几处没有更新为正确的跳转逻辑，如果语法正确且发生编译错误即在中断的那一行把相应的跳转命令改为预测分析表的命令即可)

```
FIRST SET:
128:1 2 27
129:1
130:2
131:0 2
132:34
133:0 3
134:0 26
135:34
136:0 34
137:0 2 6 28
138:4 5
139:6
140:0 2 6 28
141:34
142:0 7 9 11 12 13 34
143:0 30 31
144:7
145:11
146:9
147:0 26
148:12
149:13
150:0 26
151:0 28
152:0 16 17 18 19 20 21 22 23 24 25 31 33 34
153:0 16 17 18 19 31 33 34
154:16 17 18 19 31 33 34
155:18 19 31 33 34
156:0 18 19 31 33 34
157:0 31
158:31 33 34
159:16 17
160:18 19
161:20 21 22 23 24 25
FOLLOW SET:
128:256
129:2 256
130:27 28 256
131:2 3 6 13 28 256
132:2 3 6 13 26 28 256
133:2 6 13 28 256
134:2 3 6 13 28 256
135:2 6 13 28 34 256
136:2 6 13 28 256
137:13 256
138:28 32 256
139:2 256
140:13 256
141:14 28 256
142:14 28 256
143:14 28 256
144:14 28 256
145:14 28 256
146:14 28 256
147:29 32 256
148:14 28 256
149:14 27 28 256
150:32 256
151:14 256
152:8 10 256
153:8 10 14 20 21 22 23 24 25 26 28 32 256
154:8 10 14 20 21 22 23 24 25 26 28 32 256
155:8 10 14 16 17 18 19 20 21 22 23 24 25 26 28 31 32 33 34 256
156:8 10 14 16 17 18 19 20 21 22 23 24 25 26 28 31 32 33 34 256
157:28 256
158:8 10 14 16 17 18 19 20 21 22 23 24 25 26 28 31 32 33 34 256
159:18 19 31 33 34 256
160:31 33 34 256
161:16 17 18 19 31 33 34 256
not det:128
case:1
128->129 130 27
not det:129
case:1
129->1 34 28
not det:130
case:2
130->131 133 137 149
case:3
130->131 133 137 149
case:2
130->131 133 137 149
case:6
130->131 133 137 149
case:28
130->131 133 137 149
case:13
130->131 133 137 149
not det:131
case:2
131->2 132 134
case:2
131->0
case:3
131->0
case:6
131->0
case:13
131->0
case:28
131->0
case:256
131->0
not det:132
case:34
132->34 20 33
not det:133
case:3
133->3 135 136
case:2
133->0
case:6
133->0
case:13
133->0
case:28
133->0
case:256
133->0
not det:134
case:26
134->26 132 134
case:2
134->0
case:3
134->0
case:6
134->0
case:13
134->0
case:28
134->0
case:256
134->0
not det:135
case:34
135->34 147 29 138 28
not det:136
case:34
136->135 136
case:2
136->0
case:6
136->0
case:13
136->0
case:28
136->0
case:256
136->0
not det:137
case:6
137->139 130 28 140
case:13
137->0
case:256
137->0
not det:138
case:5
138->5
case:4
138->4
not det:139
case:6
139->6 157 28
not det:140
case:6
140->139 130 28 140
case:13
140->0
case:256
140->0
not det:141
case:34
141->34 143
not det:142
case:34
142->141
case:7
142->144
case:9
142->146
case:11
142->145
case:12
142->148
case:13
142->149
case:14
142->0
case:28
142->0
case:256
142->0
not det:143
case:30
143->30 154
case:31
143->31 154 32
case:14
143->0
case:28
143->0
case:256
143->0
not det:144
case:7
144->7 152 8 142
not det:145
case:11
145->11 31 34 147 32
not det:146
case:9
146->9 152 10 142
not det:147
case:26
147->26 34 147
case:29
147->0
case:32
147->0
case:256
147->0
not det:148
case:12
148->12 31 154 150 32
not det:149
case:13
149->13 142 151 14
not det:150
case:26
150->26 154 150
case:32
150->0
case:256
150->0
not det:151
case:28
151->28 142 151
case:14
151->0
case:256
151->0
not det:152
case:16
152->154 161 154
case:17
152->154 161 154
case:18
152->154 161 154
case:19
152->154 161 154
case:31
152->154 161 154
case:33
152->154 161 154
case:34
152->154 161 154
case:15
152->15 154
not det:153
case:16
153->159 155 153
case:17
153->159 155 153
case:8
153->0
case:10
153->0
case:14
153->0
case:20
153->0
case:21
153->0
case:22
153->0
case:23
153->0
case:24
153->0
case:25
153->0
case:26
153->0
case:28
153->0
case:32
153->0
case:256
153->0
not det:154
case:16
154->16 155 153
case:17
154->17 155 153
case:18
154->155 153
case:19
154->155 153
case:31
154->155 153
case:33
154->155 153
case:34
154->155 153
not det:155
case:31
155->158 156
case:33
155->158 156
case:34
155->158 156
not det:156
case:18
156->160 158 156
case:19
156->160 158 156
case:8
156->0
case:10
156->0
case:14
156->0
case:16
156->0
case:17
156->0
case:18
156->0
case:19
156->0
case:20
156->0
case:21
156->0
case:22
156->0
case:23
156->0
case:24
156->0
case:25
156->0
case:26
156->0
case:28
156->0
case:31
156->0
case:32
156->0
case:33
156->0
case:34
156->0
case:256
156->0
not det:157
case:31
157->31 34 29 138 32
case:28
157->0
case:256
157->0
not det:158
case:34
158->34
case:33
158->33
case:31
158->31 154 32
not det:159
case:16
159->16
case:17
159->17
not det:160
case:18
160->18
case:19
160->19
not det:161
case:20
161->20
case:21
161->21
case:22
161->22
case:23
161->23
case:24
161->24
case:25
161->25
```



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

- \<program\>→\<programhead\>\<block\>DOT
- \<programhead\>→PROGRAM标识符SEMICOLON
- \<block\>→\<constexp>\<varexp>\<prodef> \<compsent>
- \<constexp>→CONST\<constdef>\<constsuff> |ε
- \<constdef>→标识符EQUAL无符号整数
- \<constsuff>→COMMA\<constdef>\<constsuff> |ε
- \<varexp>→VAR\<vardef>\<varsuff> |ε
- \<vardef>→标识符\<idsuff>COLON<type>SEMICOLON
- \<idsuff>→COMMA标识符\<idsuff> |ε
- \<varsuff>→\<vardef>\<varsuff> |ε
- \<type>→INTEGER | LONG
- \<prodef>→\<prohead>\<block>SEMICOLON\<prosuff>|ε
- \<prohead>→PROCEDURE标识符\<argument>SEMICOLON
- \<argument>→(标识符COLON\<type>)|ε
- \<prosuff>→\<prohead>\<block>SEMICOLON\<prosuff>|ε
- \<sentence>→<assign_or_call>|\<ifsent>|\<whilesent>|\<read>|\<write>|\<compsent>|ε
- <assign_or_call>→标识符\<suffix>
- \<suffix>→ASSIGN\<express>|(\<express>)|ε
- \<ifsent>→IF\<condition>THEN\<sentence>
- \<whilesent>→WHILE\<condition>DO \<sentence>
- \<read>→READ（标识符\<idsuff>）
- \<write>→WRITE（\<express>\<exprsuff>）
- \<exprsuff>→COMMA\<express>\<exprsuff>|ε
- \<compsent>→BEGIN\<sentence>\<sentsuff>END
- \<sentsuff>→SEMICOLON\<sentence>\<sentsuff>|ε
- \<condition>→\<express>\<relationopt>\<express>|ODD\<express>
- \<express>→ADD\<term>\<termsuff>|MIN\<term>\<termsuff>|\<term>\<termsuff>
- \<termsuff>→\<addopt>\<term>\<termsuff>|ε
- \<term>→\<factor>\<factorsuff>
- \<factorsuff>→\<mulopt>\<factor>\<factorsuff>|ε
- \<factor>→标识符|无符号整数|（\<express>）
- \<addopt>→+|-
- \<mulopt>→*|/
- \<relationopt>→ =|<>|<|<=|>|>=
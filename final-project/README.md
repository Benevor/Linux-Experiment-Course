## 角色

- Server/服务器：响应下面三类客户端的请求
- Client/学生客户端：可以查看食品信息、购买食品
- Store/商家客户端：可以查看食品信息、查看购买记录、增加/删除/修改食品信息
- Monitor/监控程序：负责监控Server状态（向服务端发送心跳查询），并负责迁移

## 命令

### Host

用数据存放位置，模拟两台物理主机。

### Server

```bash
# 第一个参数指明服务端逻辑上属于学校A/B
# 第二个参数指明服务端物理上运行于主机A/B
# 本程序模拟两台物理服务器，只是端口和数据存放位置有区别
./server a a
./server b b
./server a b		# 与下文ar含义相同
./servre b a		# 与下文br含义相同
```

### Client

```bash
# 唯一的参数指明客户端所要连接的服务端
# ar表示服务端A迁移后重新恢复的服务，br同理
./client a
./client b
./client ar
./client br

# 启动后命令

# 输入用户姓名
# 执行指定命令
getfood				# 查看食品信息
buyfood|food1|3		# 购买3个food1
close				# 关闭连接，退出客户端
```

### Store

```bash
# 没有参数
./store

# 启动后命令

# 输入用户姓名
# 执行指定命令
getfood				# 查看食品信息
getrecord			# 查看购买记录
addfood|food1|2		# 添加食品food1，单价为2
recona				# 重新连接至服务端a（store可以切换服务端操作）
reconb
reconar
reconbr
close				# 关闭连接，退出客户端
```

### Monitor

```bash
# 唯一的参数表示监测的服务端
./monitor a
./monitor b

# 不断打印查询信息
# 监测到服务端异常后，进行数据迁移和反序列化，然后自身变为恢复后的服务端
```


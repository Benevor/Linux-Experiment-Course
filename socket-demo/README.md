## 问题记录

### 情况1

正常

- ./server
- 中断server
- ./server
- 中断server



### 情况2

异常

- ./server
- ./client
- 中断server
- ./server（bind error）
- 过一段时间后./server（正常）



### 情况3

异常

- ./server
- ./client
- 中断server
- make clean
- make
- ./server（bind error）
- 过一段时间后./server（正常）


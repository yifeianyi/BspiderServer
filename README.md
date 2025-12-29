# 项目背景

> 想要实现 低功�?*定期爬取B站某UP**的作品数据，用于后续粉丝站进一步建设�?
>
> 原来用来当爬虫服务器的老笔记本挂了，翻柜筒底找到一�?ESP32 ，故有了该项目�?

# BspiderServer

BspiderServer 是一个运行在 ESP32 上的轻量�?Wi‑Fi 爬虫节点，用于在受控条件下周期性获取网络数据，并将结果存储到本�?SD 卡中，同时通过局域网向上位机提供设备状态与数据访问能力�?

该项目采�?FreeRTOS 多任务架构，重点关注 **稳定性、资源可控性与任务隔离**，适用于需要长期运行的嵌入式联网设备场景�?

---

## 功能特�?

- 基于 FreeRTOS 的多任务架构  
- 使用 `esp_http_client` 进行受控 HTTP 请求  
- SPI 模式 SD 卡存储，独立 IO 任务  
- 系统资源监控（Heap、任务状态）  
- 局域网内设备管理与控制  
- 支持定时触发与指令触发的数据采集  

---

## 非目标（Non-Goals�?

- 不提供公�?Web Server  
- 不实�?RESTful API  
- 不作为通用爬虫框架使用  
- 不支持高并发或大规模数据抓取  

---

## 系统架构概览

```
PC Client (Qt / PyQt)
        �?
   Local Network
        �?
ESP32 (FreeRTOS)
 ├─ wifi_task        Wi-Fi ������״̬ά��
 ├─ http_task        HTTP ��������
 ├─ monitor_task     ϵͳ��Դ���
 └─ control_task     ��λ��ָ���
```

任务之间通过 Queue / Event 通信，避免直接资源访问�?

---

## 硬件要求

- ESP32‑WROOM�?2  
- SPI 接口 SD 卡模�? 
- 稳定�?3.3V 供电  

---

## 软件依赖

- ESP‑IDF  
- FreeRTOS  
- FATFS  
- esp_http_client  

---

## 构建与烧�?

```bash
idf.py set-target esp32
idf.py build
idf.py flash monitor
```

---

## 数据存储结构

SD 卡中数据以时间切片方式存储，示例�?

```
/sdcard/crawler/
  2025-12-11_01.json
  2025-12-11_02.json
```

---

## 项目状�?

该项目仍在开发中，当前重点为�?

- 核心任务架构稳定�? 
- 网络与存储资源隔�? 
- 长时间运行可靠性测�? 

接口与功能可能会发生调整�?

---

## 适用场景

- 嵌入式联网节点原�? 
- 受控环境下的数据采集设备  
- ESP32 + FreeRTOS 架构参考项�? 
- 嵌入式系统工程实践示�? 

---

## 许可协议

MIT License
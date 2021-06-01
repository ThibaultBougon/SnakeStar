#pragma once
#define LOG_INFO 0
#define LOG_WARN 1
#define LOG_ERR 2

void initLog();
void addLog(int level, char* msg);
void printLog(FILE* log, char* level, struct tm* date, char* msg);
void closeLog();
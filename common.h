#ifndef COMMON_H
#define COMMON_H


void msgMissingOp(FILE *stream, char *argv[]);
void msgErrorTime(FILE *stream, char *argv[]);
void msgErrorOpenFile(FILE *stream, char *argv[]);
void msgErrOption(FILE *stream, char *argv[]);
void msgErrCreatFile(FILE *stream, char *argv[]);
void msgErrZiseFileName(FILE *stream, char *argv[], int maxSize);

int allDigits(const char* str);
int allHexDigits(const char* str);

#endif//COMMON_H
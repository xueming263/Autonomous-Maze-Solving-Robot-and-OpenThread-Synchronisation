#ifndef PATH_H
#define PATH_H

// global path array and length
extern char path[256];
extern unsigned int path_length;

// path recording and optimization functions
void record_path(char dir);
void simplify_path();

#endif // PATH_H
#include <stdio.h>
#include <stdlib.h>

//実行時環境変数
char *BINDIR;
char *TMPDIR;
char *RESULTDIR;
char *TESTDIR;

char **testList = {
	"dhry2reg",
	"whetstone-double",
	"syscall",
	"pipe",
	"context1",
	"spawn",
	"execl",
	"fstime-w",
	"fstime-r",
	"fstime",
	"fsbuffer-w",
	"fsbuffer-r",
	"fsbuffer",
	"fdisk-w",
	"fdisk-r",
	"fdisk",
	"shell1",
	"shell8",
	"shell16",
	"short",
	"int",
	"long",
	"float",
	"double",
	"arithoh",
	"c",
	"dc",
	"hanoi",
	"grep",
	"sysexec",
	"index",
};

void set_environ(char **env){
	return;
}

void main(){
	return;
}


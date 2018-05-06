#define COMMAND_LEN 47

void auto_complete(char *buf) {
  char *commands[COMMAND_LEN] = {
    "cc", "cd", "cls",
    "copy", "cpuid", "del",
    "demo_graphics", "dkill", "echo",
    "exit", "fgman", "files",
    "find", "help", "kill",
    "libinfo", "loadmod", "lsdev",
    "lsext", "lsmod", "lspcut",
    "ls", "meminfo", "mem",
    "mkdir", "mount", "mouse",
    "newconsole", "off", "pause",
    "pcut", "procinfo", "procs",
    "pwd", "rempcut", "ren",
    "rmdir", "run", "set",
    "shutdown", "time", "type",
    "umount", "unload", "use",
    "ver",
  }
}
#define COMMAND_LEN 47
#define MAX_CLI 255

int getCommandIndex(char *buffer, char **commands) {
  char cmd[MAX_CLI];
  int substr, index,
      buf_len = strlen(buffer), cmd_len;

  for (index = 0; index < COMMAND_LEN; index++) {
    cmd_len = strlen(commands[index]);

    if (buf_len <= cmd_len) {
      for (substr = buf_len; substr <= cmd_len; substr++) {
        memcpy(cmd, commands[index], substr);
        cmd[substr] = '\0';

        if (strcmp(buffer, cmd) == 0) return index;
      }
    }
  }

  return -1;
}

int getBufferIndex(char *buffer) {
  char buf[MAX_CLI], *_;
  int count = 0;

  strcpy(buf, buffer);
  _ = strtok(buf, " ");

  while (_ != 0) {
    count++;
    _ = strtok(0, " ");
  }

  return count;
}

void writeToStdOut(char *cmd, char **buffer, DEX32_DDL_INFO *dev) {
  int offset;
  char buf[MAX_CLI];

  strcpy(buf, *buffer);

  for (offset = strlen(*buffer); offset < strlen(cmd); offset++) {
    Dex32PutChar(dev, Dex32GetX(dev), Dex32GetY(dev), cmd[offset], Dex32GetAttb(dev));
    buf[offset] = cmd[offset];
    
    // Update Dex32 X offset
    Dex32SetX(dev, Dex32GetX(dev) + 1);
  }

  // Space
  Dex32PutChar(dev, Dex32GetX(dev), Dex32GetY(dev), ' ', Dex32GetAttb(dev));
  buf[offset] = ' ';
  buf[offset + 1] = '\0';
  Dex32SetX(dev, Dex32GetX(dev) + 1);

  printf("%s", buf);

  memcpy(*buffer, buf, offset + 1);
}

void auto_complete(char **buf, DEX32_DDL_INFO *dev) {
  char *commands[COMMAND_LEN] = {
    "cal", "cc", "cd", "cls",
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
    "ver"
  };
  int index;

  if (getBufferIndex(*buf) == 1) {
    index = getCommandIndex(*buf, commands);
    
    if (index != -1) writeToStdOut(commands[index], buf, dev);
  }
}

#ifndef HAD_ULTIMATE_CLI_H
#define HAD_ULTIMATE_CLI_H

#define ULTIMATE_CLI_CLR_ERR 0x80
#define ULTIMATE_CLI_ABORT 0x40
#define ULTIMATE_CLI_DATA_ACC 0x2
#define ULTIMATE_CLI_PUSH_CMD 0x1

#define ULTIMATE_CLI_DATA_AV 0x80
#define ULTIMATE_CLI_STAT_AV 0x40
#define ULTIMATE_CLI_STATE_MASK 0x30
#define ULTIMATE_CLI_STATE_IDLE 0x00
#define ULTIMATE_CLI_STATE_BUSY 0x10
#define ULTIMATE_CLI_STATE_DATA_LAST 0x20
#define ULTIMATE_CLI_STATE_DATA_MORE 0x30
#define ULTIMATE_CLI_ERROR 0x08
#define ULTIMATE_CLI_CMD_BUSY 0x01

struct ultimate_cli_registers {
    unsigned char control;
    unsigned char command;
    unsigned char response;
    unsigned char status;
};

#define ULTIMATE_CLI (*(struct ultimate_cli_registers *)0xdf1c)

extern unsigned char ultimate_cli_status[];
extern unsigned char ultimate_cli_status_length;

/*
 Detect wether Ultimate CLI is available.
 Returns 1 if present, 0 if not.
*/
unsigned char ultimate_cli_detect(void);

/*
  End command.
  This discards all remaining data and puts CLI in idle state.
*/
void ultimate_cli_done(void);

/*
  Execute command written.
  Reads status into ultimate_cli_status and NUL-terminates it.
  Returns 0 if status is empty or "00", 1 otherwise.
*/  
unsigned char ultimate_cli_execute(void);

/*
  Read at most `length` bytes of response data into `data`.
  Returns the number of bytes read.
*/
unsigned int ultimate_cli_read(unsigned char *data, unsigned int length);

/*
  Write command data.
*/  
void ultimate_cli_write(const unsigned char *data, unsigned int length);

#endif /* HAD_ULTIMATE_CLI_H */
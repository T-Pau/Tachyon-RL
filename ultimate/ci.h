#ifndef HAD_ULTIMATE_CI_H
#define HAD_ULTIMATE_CI_H

#define ULTIMATE_CI_ciR_ERR 0x80
#define ULTIMATE_CI_ABORT 0x40
#define ULTIMATE_CI_DATA_ACC 0x2
#define ULTIMATE_CI_PUSH_CMD 0x1

#define ULTIMATE_CI_DATA_AV 0x80
#define ULTIMATE_CI_STAT_AV 0x40
#define ULTIMATE_CI_STATE_MASK 0x30
#define ULTIMATE_CI_STATE_IDLE 0x00
#define ULTIMATE_CI_STATE_BUSY 0x10
#define ULTIMATE_CI_STATE_DATA_LAST 0x20
#define ULTIMATE_CI_STATE_DATA_MORE 0x30
#define ULTIMATE_CI_ERROR 0x08
#define ULTIMATE_CI_CMD_BUSY 0x01

struct ultimate_ci_registers {
    unsigned char control;
    unsigned char command;
    unsigned char response;
    unsigned char status;
};

#define ULTIMATE_CI (*(struct ultimate_ci_registers *)0xdf1c)

extern unsigned char ultimate_ci_status_code;
extern unsigned char ultimate_ci_status[];
extern unsigned char ultimate_ci_status_length;

/*
 Detect wether Ultimate CI is available.
 Returns 1 if present, 0 if not.
*/
unsigned char ultimate_ci_detect(void);

/*
  End command.
  This discards all remaining data and puts CI in idle state.
*/
void ultimate_ci_done(void);

/*
  Execute command written.
  Reads status into ultimate_ci_status and NUL-terminates it.
  Returns 0 if status is empty or "00", 1 otherwise.
*/  
unsigned char ultimate_ci_execute(void);

/*
  Read at most `length` bytes of response data into `data`.
  Returns the number of bytes read.
*/
unsigned int ultimate_ci_read(unsigned char *data, unsigned int length);

/*
  Write command data.
*/  
void ultimate_ci_write(const unsigned char *data, unsigned int length);

/*
  Write NUL-terminated string to command data, converting to ASCII.
*/  
void ultimate_ci_write_string(const unsigned char *data);

/*
  Convert from ASCII to PETSCII.
*/
void ultimate_ci_ascii2pet(unsigned char *s, unsigned int len);

#endif /* HAD_ULTIMATE_CI_H */

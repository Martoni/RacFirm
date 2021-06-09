#ifndef DFR0299
#define DFR0299

#define DFPLAYER_PB_SOURCE_U     0
#define DFPLAYER_PB_SOURCE_TF    1
#define DFPLAYER_PB_SOURCE_AUX   2
#define DFPLAYER_PB_SOURCE_SLEEP 3
#define DFPLAYER_PB_SOURCE_FLASH 4

#define DFPLAYER_EQ_NORMAL 0
#define DFPLAYER_EQ_POP 1
#define DFPLAYER_EQ_ROCK 2
#define DFPLAYER_EQ_JAZZ 3
#define DFPLAYER_EQ_CLASSIC 4
#define DFPLAYER_EQ_BASS 5

#define DFPLAYER_DEVICE_U_DISK 1
#define DFPLAYER_DEVICE_SD 2
#define DFPLAYER_DEVICE_AUX 3
#define DFPLAYER_DEVICE_SLEEP 4
#define DFPLAYER_DEVICE_FLASH 5

#define DFPLAYER_RECEIVED_LENGTH 10
#define DFPLAYER_SEND_LENGTH 10

#define TimeOut 0
#define WrongStack 1
#define DFPlayerCardInserted 2
#define DFPlayerCardRemoved 3
#define DFPlayerCardOnline 4
#define DFPlayerPlayFinished 5
#define DFPlayerError 6
#define DFPlayerUSBInserted 7
#define DFPlayerUSBRemoved 8
#define DFPlayerUSBOnline 9
#define DFPlayerCardUSBOnline 10
#define DFPlayerFeedBack 11

#define Busy 1
#define Sleeping 2
#define SerialWrongStack 3
#define CheckSumNotMatch 4
#define FileIndexOut 5
#define FileMismatch 6
#define Advertise 7

#define Stack_Header 0
#define Stack_Version 1
#define Stack_Length 2
#define Stack_Command 3
#define Stack_ACK 4
#define Stack_Parameter 5
#define Stack_CheckSum 7
#define Stack_End 9


#define CMD_NEXT           0x01
#define CMD_PREVIOUS       0x02
#define CMD_SPECTRACK      0x03
#define CMD_INCREASEV      0x04
#define CMD_DECREASEV      0x05
#define CMD_SPECVOL        0x06
#define CMD_SPECEQ         0x07
#define CMD_PLAYBACKMODE   0x08
#define CMD_PLAYBACKSOURCE 0x09
#define CMD_STANDBY        0x0A
#define CMD_NORMALWORK     0x0B
#define CMD_RESET          0x0C
#define CMD_PLAYBACK       0x0D
#define CMD_PAUSE          0x0E
#define CMD_PLAYBACKFOLDER 0x0F
#define CMD_VOLUMEADJUST   0x10
#define CMD_REPEATPLAY     0x11

#define CMD_STAY1           0x3C
#define CMD_STAY2           0x3D
#define CMD_STAY3           0x3E
#define CMD_SENDINITPARS    0x3F
#define CMD_RETERR          0x40
#define CMD_REPLY           0x41
#define CMD_CURRENTSTATUS   0x42
#define CMD_CURVOLUME       0x43
#define CMD_CUREQ           0x44
#define CMD_CURPLAYBACKMODE 0x45
#define CMD_CURSOFTVERS     0x46
#define CMD_TFCARDFILESNUM  0x47
#define CMD_UDISKFILESNUM   0x48
#define CMD_FLASHFILESNUM   0x49
#define CMD_KEEPON          0x4A
#define CMD_CURTRACKTF      0x4B
#define CMD_CURTRACKUDISK   0x4C
#define CMD_CURTRACKFLASH   0x4D

/* Buffers */
extern uint8_t _received[DFPLAYER_RECEIVED_LENGTH];
extern uint8_t _sending[DFPLAYER_SEND_LENGTH];

extern uint8_t _example_send_play_nor_flash[DFPLAYER_SEND_LENGTH];
extern uint8_t _frame_get_current_status[DFPLAYER_SEND_LENGTH];

void uint16ToArray(uint16_t value, uint8_t *array);
uint16_t calculateCheckSum(uint8_t *buffer);


int rc_uart_send(uint8_t cmd, uint8_t feedback, uint16_t data);
int rc_uart_rcv(int fserial, int debug);

#endif /* DFR0299 */

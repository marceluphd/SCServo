#define DEBUG 1
//Definition of commands
#define CMD_PING        0x01
#define CMD_READ        0x02
#define CMD_WRITE       0x03
#define CMD_REG_WRITE   0x04
#define CMD_ACTION      0x05
#define CMD_SYNC_WRITE  0x83
#define CMD_RESET       0x06

//Definition of control table
#define VERSION_H     0x03
#define VERSION_L     0x04
#define SERVO_ID      0x05
#define BUS_BAUDRATE  0x06

#define CURRENT_POS_H 0x38
#define CURRENT_POS_L 0x39
#define TARGET_POS_H  0x2A
#define TARGET_POS_L  0x2B

#define WRITE_PROTECT 0x30

//Definition of Baudrate
#define BR1000000     0x00
#define BR500000      0x01
#define BR250000      0x02
#define BR128000      0x03
#define BR115200      0x04
#define BR76800       0x05
#define BR57600       0x06
#define BR38400       0x07


#define RES_DELAY 500000 //Define the delay between send command and receive message in us.
#define VERSION "1.2.13:Test Makefile"

int SerialInit(char*,int);
int SerialClose(int);


/*******************************************************************************
Command String for FeeTech Servo structure is like the following:
____________________________________________________________________
HEADER    | ID  |length |instruction  |parameters       |Checksum   |
0xFF 0xFF | ID  |N+2    |instruction  |N bytes          |           |
---------------------------------------------------------------------
ID: ID of the serial Servo
length: the length of data to send,
including N bytes parameters, 1 byte instruction and 1 byte for Checksum
Checksum: ~((ID+length+instruction+parameters)&0xFF).
*******************************************************************************/

class SCServo
{
public:
  SCServo(int fd, int ID); //Initialize Servo object with serial device(fd) and Servo ID(ID)
  unsigned char Ping();
  int ServoID;
  int GetCurrentPos();
  int SetPos(int);
  void SetID(int);
  //Baudrate is limited to 8 values. Please check the #define part or refer to the document.
  //ex. myServo.SetBaudRate(BR115200);
  void SetBaudRate(int);
private:
  int serialPort;
  char CtlTable[64];
  char CmdString[256]; //A single command length for a SCS Servo should be limited to 255
  char AnsString[256]; //An answer length should be limited to 255
  int GetAnswer(); //Get answer from serial port.
  char ChkSum();
  void ReadData(int,int);
  void WriteData(int,int);
  void GetCtlTable();


};

struct termios2
{
  tcflag_t c_iflag;		/* input mode flags */
  tcflag_t c_oflag;		/* output mode flags */
  tcflag_t c_cflag;		/* control mode flags */
  tcflag_t c_lflag;		/* local mode flags */
  cc_t c_line;			/* line discipline */
  cc_t c_cc[NCCS];		/* control characters */
  speed_t c_ispeed;		/* input speed */
  speed_t c_ospeed;		/* output speed */
};
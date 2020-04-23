
#define BC95G_ATTENTION        "AT"

#define BC95G_PRODUCT_ID       "ATI"

#define BC95G_ACTIVATE_ECHO    "ATE1"
#define BC95G_DEACTIVATE_ECHO  "ATE0"

#define BC95G_CON_STATUS       "AT+CSCON?"

#define BC95G_GET_IMEI         "AT+CGSN=1"

#define BC95G_CHECK_SIM        "AT+NCCID?"

#define BC95G_CHK_NETWORK      "AT+CEREG?"
#define BC95G_SET_NW_SEARCH    "AT+CEREG=1"

#define BC95G_SET_FUNC         "AT+CFUN=1"

#define BC95G_CHK_PDP          "AT+CGATT?"
#define BC95G_ATTACH_PDP       "AT+CGATT=1"
#define BC95G_DETACH_PDP       "AT+CGATT=0"

#define BC95G_DEFINE_PDP       "AT+CGDCONT"

#define BC95G_ACT_DEACT_PDP    "AT+CGACT"
#define BC95G_ACTIVATE_PDP     "AT+CGACT=1"
#define BC95G_DEACTIVATE_PDP   "AT+CGACT=0"

#define BC95G_GET_RSSI         "AT+CSQ"

#define BC95G_REBOOT           "AT+NRB"

#define BC95G_CHK_BANDS        "AT+NBAND?"

#define BC95G_CHK_NCFG         "AT+NCONFIG?"
#define BC95G_SET_CONFIG       "AT+NCONFIG"

#define BC95G_CREATE_SOCK      "AT+NSOCR"

#define BC95G_TCP_CONNECT      "AT+NOSCO"
#define BC95G_TCP_SEND         "AT+NSOSD"

#define BC95G_UDP_SEND         "AT+NSOST"
#define BC95G_UDP_SEND_FLAGS   "AT+NSOSTF" 

#define BC95G_GET_SERVER_IP    "AT+QDNS"

#define BC95G_CHECK_CONN       "AT+NPING"
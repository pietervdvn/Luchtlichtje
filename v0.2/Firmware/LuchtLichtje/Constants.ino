
// Time between two updates, in seconds
#define UPDATE_TIMEOUT 300
// Time in seconds between retries when failed. Should be a multiple of 4
#define RETRY_TIMEOUT 12


// Color encodings
#define EXTREMELY_GOOD 0 // Double green
#define VERY_GOOD 1 // single, lowest green
#define GOOD 2 // single, highest green

#define LOW_AVG 3 // lowest yellow
#define AVG 4 // TWO_YELLOWS
#define HIGH_AVG 5 // Highest yellow

#define BAD 6 // lowest red
#define VERY_BAD 7// highest red
#define EXTREMELY_BAD 8// two red

#define OFF 9

/******* Statuses ************/

#define NOT_YET_LOADED 0
#define UP_TO_DATE 1
#define NOT_CONNECTED 2
#define HTTPS_ERR 3
#define PARSE_ERR 4
#define AP_SETUP_ERR 5

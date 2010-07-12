/* pdu.h -- CoAP message structure
 *
 * (c) 2010 Olaf Bergmann <bergmann@tzi.org>
 */

#ifndef _PDU_H_
#define _PDU_H_

/* pre-defined constants that reflect defaults for CoAP */

#define COAP_DEFAULT_RESPONSE_TIMEOUT  1 /* response timeout in seconds */
#define COAP_DEFAULT_MAX_RETRANSMIT    5 /* max number of retransmissions */
#define COAP_DEFAULT_PORT          61616 /* CoAP default UDP port */
#define COAP_DEFAULT_MAX_AGE          60 /* default maximum object lifetime in seconds */
#define COAP_MAX_PDU_SIZE           1400 /* maximum size of a CoAP PDU */

#define COAP_DEFAULT_VERSION           1 /* version of CoAP supported */
#define COAP_DEFAULT_URI_WELLKNOWN "/.well-known/r" /* compact form of well-known resources URI */

/* CoAP message types */

#define COAP_MESSAGE_CON               0 /* confirmable message (requires ACK/RST) */
#define COAP_MESSAGE_NON               1 /* non-confirmable message (one-shot message) */
#define COAP_MESSAGE_ACK               2 /* used to acknowledge confirmable messages */
#define COAP_MESSAGE_RST               3 /* indicates error in received messages */

/* CoAP request methods */

#define COAP_REQUEST_GET       1
#define COAP_REQUEST_POST      2
#define COAP_REQUEST_PUT       3
#define COAP_REQUEST_DELETE    4

/* CoAP option types */

#define COAP_OPTION_CONTENT_TYPE  1 /* C, 8-bit uint, 1 B, 0 (text/plain) */
#define COAP_OPTION_MAXAGE        2 /* E, variable length, 1--4 B, 60 Seconds */
#define COAP_OPTION_URI_SCHEME    3 /* C, String, 1-270 B, "coap" */
#define COAP_OPTION_ETAG          4 /* E, sequence of bytes, 1-4 B, - */
#define COAP_OPTION_URI_AUTHORITY 5 /* C, String, 1-270 B, "" */
#define COAP_OPTION_LOCATION      6 /* E, String, 1-270 B, - */
#define COAP_OPTION_URI_PATH      9 /* C, String, 1-270 B, "" */

/* selected option types from draft-bormann-coap-misc-04 */

#define COAP_OPTION_BLOCK        13 /* C, unsigned integer, 1--3 B, 0 */

/* CoAP result codes (HTTP-Code / 100 * 40 + HTTP-Code % 100) */

#define COAP_RESPONSE_100       40   /* 100 Continue */
#define COAP_RESPONSE_200       80   /* 200 OK */
#define COAP_RESPONSE_201       81   /* 201 Created */
#define COAP_RESPONSE_304      124   /* 304 Not Modified */
#define COAP_RESPONSE_400      160   /* 400 Bad Request */
#define COAP_RESPONSE_404      164   /* 404 Not Found */
#define COAP_RESPONSE_405      165   /* 405 Method Not Allowed */
#define COAP_RESPONSE_415      175   /* 415 Unsupported Media Type */
#define COAP_RESPONSE_500      200   /* 500 Internal Server Error */
#define COAP_RESPONSE_504      204   /* 504 Gateway Timeout */

/* CoAP media type encoding */

#define COAP_MEDIATYPE_TEXT_PLAIN                     0 /* text/plain (UTF-8) */
#define COAP_MEDIATYPE_TEXT_XML                       1 /* text/xml (UTF-8) */
#define COAP_MEDIATYPE_TEXT_CSV                       2 /* text/csv (UTF-8) */
#define COAP_MEDIATYPE_TEXT_HTML                      3 /* text/html (UTF-8) */
#define COAP_MEDIATYPE_IMAGE_GIF                     21 /* image/gif */
#define COAP_MEDIATYPE_IMAGE_JPEG                    22 /* image/jpeg */
#define COAP_MEDIATYPE_IMAGE_PNG                     23 /* image/png */
#define COAP_MEDIATYPE_IMAGE_TIFF                    24 /* image/tiff */
#define COAP_MEDIATYPE_AUDIO_RAW                     25 /* audio/raw */
#define COAP_MEDIATYPE_VIDEO_RAW                     26 /* video/raw */
#define COAP_MEDIATYPE_APPLICATION_LINK_FORMAT       40 /* application/link-format */
#define COAP_MEDIATYPE_APPLICATION_XML               41 /* application/xml */
#define COAP_MEDIATYPE_APPLICATION_OCTET_STREAM      42 /* application/octet-stream */
#define COAP_MEDIATYPE_APPLICATION_RDF_XML           43 /* application/rdf+xml */
#define COAP_MEDIATYPE_APPLICATION_SOAP_XML          44 /* application/soap+xml  */
#define COAP_MEDIATYPE_APPLICATION_ATOM_XML          45 /* application/atom+xml  */
#define COAP_MEDIATYPE_APPLICATION_XMPP_XML          46 /* application/xmpp+xml  */
#define COAP_MEDIATYPE_APPLICATION_EXI               47 /* application/exi  */
#define COAP_MEDIATYPE_APPLICATION_X_BXML            48 /* application/x-bxml  */
#define COAP_MEDIATYPE_APPLICATION_FASTINFOSET       49 /* application/fastinfoset  */
#define COAP_MEDIATYPE_APPLICATION_SOAP_FASTINFOSET  50 /* application/soap+fastinfoset  */
#define COAP_MEDIATYPE_APPLICATION_JSON              51 /* application/json  */

/* CoAP transaction id */
typedef unsigned short coap_tid_t; 
#define COAP_INVALID_TID 0

#ifndef BYTE_ORDER
#  if (BSD >= 199103)
#    include <machine/endian.h>
#  elif defined(linux) || defined(__linux) || defined(__linux__)
#    include <endian.h>
#    define LITTLE_ENDIAN __LITTLE_ENDIAN
#    define BIG_ENDIAN    __BIG_ENDIAN
#    define BYTE_ORDER    __BYTE_ORDER
#  elif defined(sparc)
#    define LITTLE_ENDIAN 1234
#    define BIG_ENDIAN    4321
#    define BYTE_ORDER    BIG_ENDIAN
#  elif defined(sun386) || defined(i386)
#    define LITTLE_ENDIAN 1234
#    define BIG_ENDIAN    4321
#    define BYTE_ORDER    LITTLE_ENDIAN
#  else 
#    error "cannot determine byte order, please set BYTE_ORDER accordingly"
#  endif
#endif

#if BYTE_ORDER == BIG_ENDIAN
typedef struct {
  unsigned int version:2;	/* protocol version */
  unsigned int type:2;		/* type flag */
  unsigned int optcnt:4;	/* number of options following the header */
  unsigned int code:8;	        /* request method (value 1--10) or response code (value 40-255) */
  coap_tid_t id;		/* transaction id */
} coap_hdr_t;
#elif BYTE_ORDER == LITTLE_ENDIAN
typedef struct {
  unsigned int optcnt:4;	/* number of options following the header */
  unsigned int type:2;		/* type flag */
  unsigned int version:2;	/* protocol version */
  unsigned int code:8;	        /* request method (value 1--10) or response code (value 40-255) */
  coap_tid_t id;		/* transaction id (network byte order!) */
} coap_hdr_t;
#endif

#if BYTE_ORDER == BIG_ENDIAN
typedef union {
  struct {		        /* short form, to be used when length < 15 */
    unsigned int delta:4;      /* option type (expressed as delta) */
    unsigned int length:4;	/* number of option bytes (15 indicates extended form) */
    /* 0--14 bytes options */
  } sval;
  struct {			/* extended form, to be used when lengt==15 */
    unsigned int delta:4;      /* option type (expressed as delta) */
    unsigned int flag:4;	/* must be 15! */
    unsigned int length:8;	/* length - 15 */
    /* 15--270 bytes options */
  } lval;
} coap_opt_t;
#elif BYTE_ORDER == LITTLE_ENDIAN
typedef union {
  struct {		        /* short form, to be used when length < 15 */
    unsigned int length:4;	/* number of option bytes (15 indicates extended form) */
    unsigned int delta:4;      /* option type (expressed as delta) */
    /* 0--14 bytes options */
  } sval;
  struct {			/* extended form, to be used when lengt==15 */
    unsigned int flag:4;	/* must be 15! */
    unsigned int delta:4;      /* option type (expressed as delta) */
    unsigned int length:8;	/* length - 15 */
    /* 15--270 bytes options */
  } lval;
} coap_opt_t;
#endif

#define COAP_OPT_SVAL(opt) (opt).sval
#define COAP_OPT_LVAL(opt) (opt).lval
#define COAP_OPT_ISEXTENDED(opt) (COAP_OPT_LVAL(opt).flag == 15)

/* these macros should be used to access fields from coap_opt_t */
#define COAP_OPT_DELTA(opt) COAP_OPT_SVAL(opt).delta
#define COAP_OPT_SETDELTA(opt,val) COAP_OPT_SVAL(opt).delta = (val)

#define COAP_OPT_LENGTH(opt) \
  ( COAP_OPT_ISEXTENDED(opt) ? COAP_OPT_LVAL(opt).length + 15 : COAP_OPT_SVAL(opt).length )

#define COAP_OPT_SETLENGTH(opt,val)		\
  if ( (val) < 15 )				\
    COAP_OPT_SVAL(opt).length = (val) & 0x0f;	\
  else {								\
    COAP_OPT_LVAL(opt).length = ((val) - 15) & 0xff;			\
    COAP_OPT_LVAL(opt).flag = 15;					\
  }

#define COAP_OPT_VALUE(opt)						\
  ( (unsigned char *)&(opt) + ( COAP_OPT_ISEXTENDED(opt) ? 2 : 1 ) )

/* do not forget to adjust this when coap_opt_t is changed! */
#define COAP_OPT_SIZE(opt) ( COAP_OPT_LENGTH(opt) + ( COAP_OPT_ISEXTENDED(opt) ? 2: 1 ) )

/**
 * Structures for more convenient handling of options. (To be used with ordered
 * coap_list_t.) The option's data will be added to the end of the coap_option 
 * structure (see macro COAP_OPTION_DATA).
 */
typedef struct {
  unsigned short key;		/* the option key (no delta coding) */
  unsigned int length;
} coap_option;

#define COAP_OPTION_KEY(option) (option).key
#define COAP_OPTION_LENGTH(option) (option).length
#define COAP_OPTION_DATA(option) ((unsigned char *)&(option) + sizeof(coap_option))


/** Header structure for CoAP PDUs */

typedef struct {
  coap_hdr_t *hdr;
  unsigned short length;	/* PDU length (including header, options, data)  */
  unsigned char *data;		/* payload */
} coap_pdu_t;

/** 
 * Creates a new CoAP PDU. The object is created on the heap and must be released
 * using delete_pdu();
 */

coap_pdu_t *coap_new_pdu();
void coap_delete_pdu(coap_pdu_t *);

/** 
 * Adds option of given type to pdu that is passed as first parameter. coap_add_option() 
 * destroys the PDU's data, so coap_add_data must be called after all options have been
 * added.
 */

int coap_add_option(coap_pdu_t *pdu, unsigned char type, unsigned int len, const unsigned char *data);
coap_opt_t *coap_check_option(coap_pdu_t *pdu, unsigned char type);

/** 
 * Adds given data to the pdu that is passed as first parameter. Note that the PDU's 
 * data is destroyed by coap_add_option().
 */

int coap_add_data(coap_pdu_t *pdu, unsigned int len, const unsigned char *data);

#endif /* _PDU_H_ */

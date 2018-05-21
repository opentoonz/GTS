#ifndef cpu_byte_order_is_little_endian_h
#define cpu_byte_order_is_little_endian_h

#ifdef __cplusplus
extern "C" {
#endif

/* CPUが、Little Endianならtrueを返す、Big Endianならfalseを返す */
extern int cpu_byte_order_is_little_endian( void );

#ifdef __cplusplus
}
#endif

#endif /* !cpu_byte_order_is_little_endian_h */

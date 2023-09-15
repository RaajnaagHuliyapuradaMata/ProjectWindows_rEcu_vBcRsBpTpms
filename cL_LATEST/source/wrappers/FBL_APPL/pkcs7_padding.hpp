#ifndef _PKCS7_PADDING_H_
#define _PKCS7_PADDING_H_

#include <stdint.h>
#include <stddef.h>

int pkcs7_padding_pad_buffer( uint8_t *buffer,  size_t data_length, size_t buffer_size, uint8_t modulus );

int pkcs7_padding_valid( uint8_t *buffer, size_t data_length, size_t buffer_size, uint8_t modulus );

size_t pkcs7_padding_data_length( uint8_t * buffer, size_t buffer_size, uint8_t modulus );

#endif
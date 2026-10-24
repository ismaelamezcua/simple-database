#ifndef SIMPLEDB_H
#define SIMPLEDB_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255

#define size_of_attribute(struct_t, attribute_t)                               \
  sizeof(((struct_t *)0)->attribute_t)

typedef enum { EXECUTE_SUCESS, EXECUTE_TABLE_FULL } execute_result_t;

typedef struct {
  uint32_t id;
  char username[COLUMN_USERNAME_SIZE + 1];
  char email[COLUMN_EMAIL_SIZE + 1];
} row_t;

typedef enum {
  META_COMMAND_SUCCESS,
  META_COMMAND_UNRECOGNIZED_COMMAND
} meta_command_result_t;

typedef enum {
  PREPARE_SUCCESS,
  PREPARE_NEGATIVE_ID,
  PREPARE_SYNTAX_ERROR,
  PREPARE_STRING_TOO_LONG,
  PREPARE_UNRECOGNIZED_STATEMENT
} prepare_result_t;

typedef enum { STATEMENT_INSERT, STATEMENT_SELECT } statement_type_t;

typedef struct {
  statement_type_t type;
  row_t row_to_insert;
} statement_t;

typedef struct {
  char *buffer;
  size_t buffer_length;
  ssize_t input_length;
} input_buffer_t;

const uint32_t ID_SIZE = size_of_attribute(row_t, id);
const uint32_t USERNAME_SIZE = size_of_attribute(row_t, username);
const uint32_t EMAIL_SIZE = size_of_attribute(row_t, email);
const uint32_t ID_OFFSET = 0;
const uint32_t USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
const uint32_t EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE;
const uint32_t ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;

const uint32_t PAGE_SIZE = 4096;
#define TABLE_MAX_PAGES 100
const uint32_t ROWS_PER_PAGE = PAGE_SIZE / ROW_SIZE;
const uint32_t TABLE_MAX_ROWS = ROWS_PER_PAGE * TABLE_MAX_PAGES;

typedef struct {
  uint32_t num_rows;
  void *pages[TABLE_MAX_PAGES];
} table_t;

input_buffer_t *new_input_buffer();
void print_prompt();
void read_input(input_buffer_t *input_buffer);
void close_input_buffer(input_buffer_t *input_buffer);
meta_command_result_t do_meta_command(input_buffer_t *input_buffer);
prepare_result_t prepare_statement(input_buffer_t *input_buffer,
                                   statement_t *statement);
prepare_result_t prepare_insert(input_buffer_t *input_buffer,
                                statement_t *statement);
execute_result_t execute_statement(statement_t *statement, table_t *table);
execute_result_t execute_insert(statement_t *statement, table_t *table);
execute_result_t execute_select(statement_t *statement, table_t *table);
void serialize_row(row_t *source, void *destination);
void deserialize_row(void *source, row_t *destination);
void *row_slot(table_t *table, uint32_t row_num);
void print_row(row_t *row);
table_t *new_table();
void free_table(table_t *table);

#endif /* SIMPLEDB_H */

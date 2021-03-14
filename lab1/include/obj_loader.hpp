#ifndef TINOBJ_LOADER_C_H_
#define TINOBJ_LOADER_C_H_

#include <stddef.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sys/mman.h>
#include <limits.h>
#include <float.h>
#include <math.h>


typedef struct {
  char *name; /* group name or object name. */
  unsigned int face_offset;
  unsigned int length;
} obj_shape_t;

typedef struct { int v_idx, vt_idx, vn_idx; } obj_vertex_index_t;

typedef struct {
  unsigned int num_vertices;
  unsigned int num_normals;
  unsigned int num_texcoords;
  unsigned int num_faces;
  unsigned int num_face_num_verts;

  int pad0;

  float *vertices;
  float *normals;
  float *texcoords;
  obj_vertex_index_t *faces;
  int *face_num_verts;
  int *material_ids;
} obj_attrib_t;

typedef enum {
  COMMAND_EMPTY,
  COMMAND_V,
  COMMAND_VN,
  COMMAND_VT,
  COMMAND_F,
  COMMAND_G,
  COMMAND_O,
  COMMAND_USEMTL,
  COMMAND_MTLLIB

} CommandType;


#define OBJ_FLAG_TRIANGULATE (1 << 0)

#define OBJ_INVALID_INDEX (0x80000000)

#define OBJ_SUCCESS (0)
#define OBJ_ERROR_EMPTY (-1)
#define OBJ_ERROR_INVALID_PARAMETER (-2)
#define OBJ_ERROR_FILE_OPERATION (-3)

typedef void (*file_reader_callback)(void *ctx, const char *filename, int is_mtl, const char *obj_filename, char **buf, size_t *len);

extern int tinyobj_parse_obj(obj_attrib_t *attrib, obj_shape_t **shapes,
                             size_t *num_shapes,
                             size_t *num_materials, const char *file_name, file_reader_callback file_reader,
                             void *ctx, unsigned int flags);


extern void obj_attrib_init(obj_attrib_t &attrib);
extern void obj_attrib_free(obj_attrib_t &attrib);
extern void obj_shapes_free(obj_shape_t *shapes, size_t num_shapes);

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <errno.h>

#if defined(OBJ_MALLOC) && defined(OBJ_REALLOC) && defined(OBJ_CALLOC) && defined(OBJ_FREE)
/* ok */
#elif !defined(OBJ_MALLOC) && !defined(OBJ_REALLOC) && !defined(OBJ_CALLOC) && !defined(OBJ_FREE)
/* ok */
#else
#error "Must define all or none of OBJ_MALLOC, OBJ_REALLOC, OBJ_CALLOC and OBJ_FREE."
#endif

#ifndef OBJ_MALLOC
#include <stdlib.h>
#define OBJ_MALLOC malloc
#define OBJ_REALLOC realloc
#define OBJ_CALLOC calloc
#define OBJ_FREE free
#endif

#define OBJ_MAX_FACES_PER_F_LINE (16)
#define OBJ_MAX_FILEPATH (8192)

#define IS_SPACE(x) (((x) == ' ') || ((x) == '\t'))
#define IS_DIGIT(x) ((unsigned int)((x) - '0') < (unsigned int)(10))
#define IS_NEW_LINE(x) (((x) == '\r') || ((x) == '\n') || ((x) == '\0'))

typedef struct {
  float vx, vy, vz;
  float nx, ny, nz;
  float tx, ty;

  /* @todo { Use dynamic array } */
  obj_vertex_index_t f[OBJ_MAX_FACES_PER_F_LINE];
  size_t num_f;

  int f_num_verts[OBJ_MAX_FACES_PER_F_LINE];
  size_t num_f_num_verts;

  const char *group_name;
  unsigned int group_name_len;
  int pad0;

  const char *object_name;
  unsigned int object_name_len;
  int pad1;


  CommandType type;
} Command;

static void skip_space(const char **token) {
  while ((*token)[0] == ' ' || (*token)[0] == '\t') {
    (*token)++;
  }
}

static void skip_space_and_cr(const char **token) {
  while ((*token)[0] == ' ' || (*token)[0] == '\t' || (*token)[0] == '\r') {
    (*token)++;
  }
}

static int until_space(const char *token) {
  const char *p = token;
  while (p[0] != '\0' && p[0] != ' ' && p[0] != '\t' && p[0] != '\r') {
    p++;
  }

  return (int)(p - token);
}

static size_t length_until_newline(const char *token, size_t n) {
  size_t len = 0;

  for (len = 0; len < n - 1; len++) {
    if (token[len] == '\n') {
      break;
    }
    if ((token[len] == '\r') && ((len < (n - 2)) && (token[len + 1] != '\n'))) {
      break;
    }
  }

  return len;
}

static size_t length_until_line_feed(const char *token, size_t n) {
  size_t len = 0;

  for (len = 0; len < n; len++) {
    if ((token[len] == '\n') || (token[len] == '\r')) {
      break;
    }
  }

  return len;
}

static int my_atoi(const char *c) {
  int value = 0;
  int sign = 1;
  if (*c == '+' || *c == '-') {
    if (*c == '-') sign = -1;
    c++;
  }
  while (((*c) >= '0') && ((*c) <= '9')) { /* isdigit(*c) */
    value *= 10;
    value += (int)(*c - '0');
    c++;
  }
  return value * sign;
}

/* Make index zero-base, and also support relative index. */
static int fixIndex(int idx, size_t n) {
  if (idx > 0) return idx - 1;
  if (idx == 0) return 0;
  return (int)n + idx; /* negative value = relative */
}

/* Parse raw triples: i, i/j/k, i//k, i/j */
static obj_vertex_index_t parseRawTriple(const char **token) {
  obj_vertex_index_t vi;
  /* 0x80000000 = -2147483648 = invalid */
  vi.v_idx = (int)(0x80000000);
  vi.vn_idx = (int)(0x80000000);
  vi.vt_idx = (int)(0x80000000);

  vi.v_idx = my_atoi((*token));
  while ((*token)[0] != '\0' && (*token)[0] != '/' && (*token)[0] != ' ' &&
         (*token)[0] != '\t' && (*token)[0] != '\r') {
    (*token)++;
  }
  if ((*token)[0] != '/') {
    return vi;
  }
  (*token)++;

  /* i//k */
  if ((*token)[0] == '/') {
    (*token)++;
    vi.vn_idx = my_atoi((*token));
    while ((*token)[0] != '\0' && (*token)[0] != '/' && (*token)[0] != ' ' &&
           (*token)[0] != '\t' && (*token)[0] != '\r') {
      (*token)++;
    }
    return vi;
  }

  /* i/j/k or i/j */
  vi.vt_idx = my_atoi((*token));
  while ((*token)[0] != '\0' && (*token)[0] != '/' && (*token)[0] != ' ' &&
         (*token)[0] != '\t' && (*token)[0] != '\r') {
    (*token)++;
  }
  if ((*token)[0] != '/') {
    return vi;
  }

  /* i/j/k */
  (*token)++; /* skip '/' */
  vi.vn_idx = my_atoi((*token));
  while ((*token)[0] != '\0' && (*token)[0] != '/' && (*token)[0] != ' ' &&
         (*token)[0] != '\t' && (*token)[0] != '\r') {
    (*token)++;
  }
  return vi;
}

static int parseInt(const char **token) {
  int i = 0;
  skip_space(token);
  i = my_atoi((*token));
  (*token) += until_space((*token));
  return i;
}

static int tryParseDouble(const char *s, const char *s_end, double *result) {
  double mantissa = 0.0;
  int exponent = 0;

  char sign = '+';
  char exp_sign = '+';
  char const *curr = s;

  int read = 0;
  int end_not_reached = 0;

  /*
     BEGIN PARSING.
     */

  if (s >= s_end) {
    return 0; /* fail */
  }

  /* Find out what sign we've got. */
  if (*curr == '+' || *curr == '-') {
    sign = *curr;
    curr++;
  } else if (IS_DIGIT(*curr)) { /* Pass through. */
  } else {
    goto fail;
  }

  /* Read the integer part. */
  end_not_reached = (curr != s_end);
  while (end_not_reached && IS_DIGIT(*curr)) {
    mantissa *= 10;
    mantissa += (int)(*curr - 0x30);
    curr++;
    read++;
    end_not_reached = (curr != s_end);
  }

  /* We must make sure we actually got something. */
  if (read == 0) goto fail;
  /* We allow numbers of form "#", "###" etc. */
  if (!end_not_reached) goto assemble;

  /* Read the decimal part. */
  if (*curr == '.') {
    curr++;
    read = 1;
    end_not_reached = (curr != s_end);
    while (end_not_reached && IS_DIGIT(*curr)) {
      /* pow(10.0, -read) */
      double frac_value = 1.0;
      int f;
      for (f = 0; f < read; f++) {
        frac_value *= 0.1;
      }
      mantissa += (int)(*curr - 0x30) * frac_value;
      read++;
      curr++;
      end_not_reached = (curr != s_end);
    }
  } else if (*curr == 'e' || *curr == 'E') {
  } else {
    goto assemble;
  }

  if (!end_not_reached) goto assemble;

  /* Read the exponent part. */
  if (*curr == 'e' || *curr == 'E') {
    curr++;
    /* Figure out if a sign is present and if it is. */
    end_not_reached = (curr != s_end);
    if (end_not_reached && (*curr == '+' || *curr == '-')) {
      exp_sign = *curr;
      curr++;
    } else if (IS_DIGIT(*curr)) { /* Pass through. */
    } else {
      /* Empty E is not allowed. */
      goto fail;
    }

    read = 0;
    end_not_reached = (curr != s_end);
    while (end_not_reached && IS_DIGIT(*curr)) {
      exponent *= 10;
      exponent += (int)(*curr - 0x30);
      curr++;
      read++;
      end_not_reached = (curr != s_end);
    }
    if (read == 0) goto fail;
  }

assemble :

  {
    double a = 1.0; /* = pow(5.0, exponent); */
    double b  = 1.0; /* = 2.0^exponent */
    int i;
    for (i = 0; i < exponent; i++) {
      a = a * 5.0;
    }

    for (i = 0; i < exponent; i++) {
      b = b * 2.0;
    }

    if (exp_sign == '-') {
      a = 1.0 / a;
      b = 1.0 / b;
    }

    *result =
      /* (sign == '+' ? 1 : -1) * ldexp(mantissa * pow(5.0, exponent),
         exponent); */
      (sign == '+' ? 1 : -1) * (mantissa * a * b);
  }

  return 1;
fail:
  return 0;
}

static float parseFloat(const char **token) {
  const char *end;
  double val = 0.0;
  float f = 0.0f;
  skip_space(token);
  end = (*token) + until_space((*token));
  val = 0.0;
  tryParseDouble((*token), end, &val);
  f = (float)(val);
  (*token) = end;
  return f;
}

static void parseFloat2(float *x, float *y, const char **token) {
  (*x) = parseFloat(token);
  (*y) = parseFloat(token);
}

static void parseFloat3(float *x, float *y, float *z, const char **token) {
  (*x) = parseFloat(token);
  (*y) = parseFloat(token);
  (*z) = parseFloat(token);
}

static size_t my_strnlen(const char *s, size_t n) {
    const char *p = (char *) memchr(s, 0, n);
    return p ? (size_t)(p - s) : n;
}

static char *my_strdup(const char *s, size_t max_length) { //TODO Replace with gnu version
  char *d;
  size_t len;

  if (s == NULL) return NULL;

  /* Do not consider CRLF line ending(#19) */
  len = length_until_line_feed(s, max_length);
  /* len = strlen(s); */

  /* trim line ending and append '\0' */
  d = (char *)OBJ_MALLOC(len + 1); /* + '\0' */
  memcpy(d, s, (size_t)(len));
  d[len] = '\0';

  return d;
}

static char *my_strndup(const char *s, size_t len) {
  char *d;
  size_t slen;

  if (s == NULL) return NULL;
  if (len == 0) return NULL;

  slen = my_strnlen(s, len);
  d = (char *)OBJ_MALLOC(slen + 1); /* + '\0' */
  if (!d) {
    return NULL;
  }
  memcpy(d, s, slen);
  d[slen] = '\0';

  return d;
}

char *dynamic_fgets(char **buf, size_t *size, FILE *file) {
  char *offset;
  char *ret;
  size_t old_size;

  if (!(ret = fgets(*buf, (int)*size, file))) {
    return ret;
  }

  if (NULL != strchr(*buf, '\n')) {
    return ret;
  }

  do {
    old_size = *size;
    *size *= 2;
    *buf = (char*)OBJ_REALLOC(*buf, *size);
    offset = &((*buf)[old_size - 1]);

    ret = fgets(offset, (int)(old_size + 1), file);
  } while(ret && (NULL == strchr(*buf, '\n')));

  return ret;
}


/* Implementation of string to int hashtable */

#define HASH_TABLE_ERROR 1
#define HASH_TABLE_SUCCESS 0

#define HASH_TABLE_DEFAULT_SIZE 10

typedef struct hash_table_entry_t
{
  unsigned long hash;
  int filled;
  int pad0;
  long value;

  struct hash_table_entry_t* next;
} hash_table_entry_t;

typedef struct
{
  unsigned long* hashes;
  hash_table_entry_t* entries;
  size_t capacity;
  size_t n;
} hash_table_t;

static unsigned long hash_djb2(const unsigned char* str)
{
  unsigned long hash = 5381;
  int c;

  while ((c = *str++)) {
    hash = ((hash << 5) + hash) + (unsigned long)(c);
  }

  return hash;
}

static void create_hash_table(size_t start_capacity, hash_table_t* hash_table)
{
  if (start_capacity < 1)
    start_capacity = HASH_TABLE_DEFAULT_SIZE;
  hash_table->hashes = (unsigned long*) OBJ_MALLOC(start_capacity * sizeof(unsigned long));
  hash_table->entries = (hash_table_entry_t*) OBJ_CALLOC(start_capacity, sizeof(hash_table_entry_t));
  hash_table->capacity = start_capacity;
  hash_table->n = 0;
}

static void destroy_hash_table(hash_table_t* hash_table)
{
  OBJ_FREE(hash_table->entries);
  OBJ_FREE(hash_table->hashes);
}

/* Insert with quadratic probing */
static int hash_table_insert_value(unsigned long hash, long value, hash_table_t& hash_table)
{
  /* Insert value */
  size_t start_index = hash % hash_table.capacity;
  size_t index = start_index;
  hash_table_entry_t* start_entry = hash_table.entries + start_index;
  size_t i;
  hash_table_entry_t* entry;

  for (i = 1; hash_table.entries[index].filled; i++)
  {
    if (i >= hash_table.capacity)
      return HASH_TABLE_ERROR;
    index = (start_index + (i * i)) % hash_table.capacity;
  }

  entry = hash_table.entries + index;
  entry->hash = hash;
  entry->filled = 1;
  entry->value = value;

  if (index != start_index) {
    /* This is a new entry, but not the start entry, hence we need to add a next pointer to our entry */
    entry->next = start_entry->next;
    start_entry->next = entry;
  }

  return HASH_TABLE_SUCCESS;
}

static int hash_table_insert(unsigned long hash, long value, hash_table_t& hash_table)
{
  int ret = hash_table_insert_value(hash, value, hash_table);
  if (ret == HASH_TABLE_SUCCESS)
  {
    hash_table.hashes[hash_table.n] = hash;
    hash_table.n++;
  }
  return ret;
}

static hash_table_entry_t& hash_table_find(unsigned long hash, hash_table_t& hash_table)
{
  hash_table_entry_t *entry = hash_table.entries + (hash % hash_table.capacity);
  while (entry)
  {
    if (entry->hash == hash && entry->filled)
    {
      return *entry;
    }
    entry = entry->next;
  }
  return *hash_table.entries;
}

static void hash_table_maybe_grow(size_t new_n, hash_table_t& hash_table)
{
  size_t new_capacity;
  hash_table_t new_hash_table;
  size_t i;

  if (new_n <= hash_table.capacity) {
    return;
  }
  new_capacity = 2 * ((2 * hash_table.capacity) > new_n ? hash_table.capacity : new_n);
  /* Create a new hash table. We're not calling create_hash_table because we want to realloc the hash array */
  new_hash_table.hashes = hash_table.hashes = (unsigned long*) OBJ_REALLOC((void*) hash_table.hashes, sizeof(unsigned long) * new_capacity);
  new_hash_table.entries = (hash_table_entry_t*) OBJ_CALLOC(new_capacity, sizeof(hash_table_entry_t));
  new_hash_table.capacity = new_capacity;
  new_hash_table.n = hash_table.n;

  /* Rehash */
  for (i = 0; i < hash_table.capacity; i++)
  {
    hash_table_entry_t& entry = hash_table_find(hash_table.hashes[i], hash_table);
    hash_table_insert_value(hash_table.hashes[i], entry.value, new_hash_table);
  }

  OBJ_FREE(hash_table.entries);
  (hash_table) = new_hash_table;
}

static int hash_table_exists(const char* name, hash_table_t& hash_table)
{
  return hash_table_find(hash_djb2((const unsigned char*)name), hash_table).value != hash_table.entries[0].value;
}

static void hash_table_set(const char* name, size_t val, hash_table_t& hash_table)
{
  /* Hash name */
  unsigned long hash = hash_djb2((const unsigned char *)name);

  hash_table_entry_t& entry = hash_table_find(hash, hash_table);
  entry.value = (long)val;
  return;
}

static long hash_table_get(const char* name, hash_table_t& hash_table)
{
    hash_table_entry_t& ret = hash_table_find(hash_djb2((const unsigned char*)(name)), hash_table);
    return ret.value;
}

static int is_line_ending(const char *p, size_t i, size_t end_i) {
  if (p[i] == '\0') return 1;
  if (p[i] == '\n') return 1; /* this includes \r\n */
  if (p[i] == '\r') {
    if (((i + 1) < end_i) && (p[i + 1] != '\n')) { /* detect only \r case */
      return 1;
    }
  }
  return 0;
}



typedef struct {
    size_t pos;
    size_t len;
} LineInfo;

/* Find '\n' and create line data. */
static int get_line_infos(const char *buf, size_t buf_len, LineInfo **line_infos, size_t *num_lines)
{
    size_t i = 0;
    size_t end_idx = buf_len;
    size_t prev_pos = 0;
    size_t line_no = 0;
    size_t last_line_ending = 0;

    /* Count # of lines. */
    for (i = 0; i < end_idx; i++) {
        if (is_line_ending(buf, i, end_idx)) {
            (*num_lines)++;
            last_line_ending = i;
        }
    }

    if (end_idx - last_line_ending > 0) {
        (*num_lines)++;
    }

    if (*num_lines == 0) return OBJ_ERROR_EMPTY;

    *line_infos = (LineInfo *)OBJ_MALLOC(sizeof(LineInfo) * (*num_lines));

    /* Fill line infos. */
    for (i = 0; i < end_idx; i++) {
        if (is_line_ending(buf, i, end_idx)) {
            (*line_infos)[line_no].pos = prev_pos;
            (*line_infos)[line_no].len = i - prev_pos;
            prev_pos = i + 1;
            line_no++;
        }
    }
    if (end_idx - last_line_ending > 0) {
        (*line_infos)[line_no].pos = prev_pos;
        (*line_infos)[line_no].len = end_idx - 1 - last_line_ending;
    }

    return 0;
}


static int parseLine(Command &command, const char *p, size_t p_len,
        int triangulate) {
    char linebuf[4096];
    const char *token;
    assert(p_len < 4095);

    memcpy(linebuf, p, p_len);
    linebuf[p_len] = '\0';

    token = linebuf;

    command.type = COMMAND_EMPTY;

    /* Skip leading space. */
    skip_space(&token);

    assert(token);
    if (token[0] == '\0') { /* empty line */
        return 0;
    }

    if (token[0] == '#') { /* comment line */
        return 0;
    }

    /* vertex */
    if (token[0] == 'v' && IS_SPACE((token[1]))) {
        float x, y, z;
        token += 2;
        parseFloat3(&x, &y, &z, &token);
        command.vx = x;
        command.vy = y;
        command.vz = z;
        command.type = COMMAND_V;
        return 1;
    }

    /* normal */
    if (token[0] == 'v' && token[1] == 'n' && IS_SPACE((token[2]))) {
        float x, y, z;
        token += 3;
        parseFloat3(&x, &y, &z, &token);
        command.nx = x;
        command.ny = y;
        command.nz = z;
        command.type = COMMAND_VN;
        return 1;
    }

    /* texcoord */
    if (token[0] == 'v' && token[1] == 't' && IS_SPACE((token[2]))) {
        float x, y;
        token += 3;
        parseFloat2(&x, &y, &token);
        command.tx = x;
        command.ty = y;
        command.type = COMMAND_VT;
        return 1;
    }

    /* face */
    if (token[0] == 'f' && IS_SPACE((token[1]))) {
        size_t num_f = 0;

        obj_vertex_index_t f[OBJ_MAX_FACES_PER_F_LINE];
        token += 2;
        skip_space(&token);

        while (!IS_NEW_LINE(token[0])) {
            obj_vertex_index_t vi = parseRawTriple(&token);
            skip_space_and_cr(&token);

            f[num_f] = vi;
            num_f++;
        }

        command.type = COMMAND_F;

        if (triangulate) {
            size_t k;
            size_t n = 0;

            obj_vertex_index_t i0 = f[0];
            obj_vertex_index_t i1;
            obj_vertex_index_t i2 = f[1];

            assert(3 * num_f < OBJ_MAX_FACES_PER_F_LINE);

            for (k = 2; k < num_f; k++) {
                i1 = i2;
                i2 = f[k];
                command.f[3 * n + 0] = i0;
                command.f[3 * n + 1] = i1;
                command.f[3 * n + 2] = i2;

                command.f_num_verts[n] = 3;
                n++;
            }
            command.num_f = 3 * n;
            command.num_f_num_verts = n;

        } else {
            size_t k = 0;
            assert(num_f < OBJ_MAX_FACES_PER_F_LINE);
            for (k = 0; k < num_f; k++) {
                command.f[k] = f[k];
            }

            command.num_f = num_f;
            command.f_num_verts[0] = (int)num_f;
            command.num_f_num_verts = 1;
        }

        return 1;
    }


    /* group name */
    if (token[0] == 'g' && IS_SPACE((token[1]))) {
        /* @todo { multiple group name. } */
        token += 2;

        command.group_name = p + (token - linebuf);
        command.group_name_len = (unsigned int)length_until_newline(
                token, p_len - (size_t)(token - linebuf)) +
            1;
        command.type = COMMAND_G;

        return 1;
    }

    /* object name */
    if (token[0] == 'o' && IS_SPACE((token[1]))) {
        /* @todo { multiple object name? } */
        token += 2;

        command.object_name = p + (token - linebuf);
        command.object_name_len = (unsigned int)length_until_newline(
                token, p_len - (size_t)(token - linebuf)) +
            1;
        command.type = COMMAND_O;

        return 1;
    }

    return 0;
}

int obj_parse_obj(obj_attrib_t &attrib, obj_shape_t **shapes,
        size_t *num_shapes, const char *obj_filename,
        file_reader_callback file_reader, void *ctx,
        unsigned int flags) {
    LineInfo *line_infos = NULL;
    Command *commands = NULL;
    size_t num_lines = 0;

    size_t num_v = 0;
    size_t num_vn = 0;
    size_t num_vt = 0;
    size_t num_f = 0;
    size_t num_faces = 0;

    char *buf = NULL;
    size_t len = 0;
    file_reader(ctx, obj_filename, /* is_mtl */0, obj_filename, &buf, &len);

    if (len < 1) return OBJ_ERROR_INVALID_PARAMETER;
    if (shapes == NULL) return OBJ_ERROR_INVALID_PARAMETER;
    if (num_shapes == NULL) return OBJ_ERROR_INVALID_PARAMETER;
    if (buf == NULL) return OBJ_ERROR_INVALID_PARAMETER;

    obj_attrib_init(attrib);

    /* 1. create line data */
    if (get_line_infos(buf, len, &line_infos, &num_lines) != 0) {
        return OBJ_ERROR_EMPTY;
    }

    commands = (Command *)OBJ_MALLOC(sizeof(Command) * num_lines);

    /* 2. parse each line */
    {
        size_t i = 0;
        for (i = 0; i < num_lines; i++) {
            int ret = parseLine(commands[i], &buf[line_infos[i].pos],
                    line_infos[i].len, flags & OBJ_FLAG_TRIANGULATE);
            if (ret) {
                if (commands[i].type == COMMAND_V) {
                    num_v++;
                } else if (commands[i].type == COMMAND_VN) {
                    num_vn++;
                } else if (commands[i].type == COMMAND_VT) {
                    num_vt++;
                } else if (commands[i].type == COMMAND_F) {
                    num_f += commands[i].num_f;
                    num_faces += commands[i].num_f_num_verts;
                }
            }
        }
    }

    /* line_infos are not used anymore. Release memory. */
    if (line_infos) {
        OBJ_FREE(line_infos);
    }

    /* Construct attributes */

    {
        size_t v_count = 0;
        size_t n_count = 0;
        size_t t_count = 0;
        size_t f_count = 0;
        size_t face_count = 0;
        size_t i = 0;

        attrib.vertices = (float *)OBJ_MALLOC(sizeof(float) * num_v * 3);
        attrib.num_vertices = (unsigned int)num_v;
        attrib.normals = (float *)OBJ_MALLOC(sizeof(float) * num_vn * 3);
        attrib.num_normals = (unsigned int)num_vn;
        attrib.texcoords = (float *)OBJ_MALLOC(sizeof(float) * num_vt * 2);
        attrib.num_texcoords = (unsigned int)num_vt;
        attrib.faces = (obj_vertex_index_t *)OBJ_MALLOC(
                sizeof(obj_vertex_index_t) * num_f);
        attrib.num_faces = (unsigned int)num_f;
        attrib.face_num_verts = (int *)OBJ_MALLOC(sizeof(int) * num_faces);
        attrib.num_face_num_verts = (unsigned int)num_faces;

        for (i = 0; i < num_lines; i++) {
            if (commands[i].type == COMMAND_EMPTY) {
                continue;
            }  else if (commands[i].type == COMMAND_V) {
                attrib.vertices[3 * v_count + 0] = commands[i].vx;
                attrib.vertices[3 * v_count + 1] = commands[i].vy;
                attrib.vertices[3 * v_count + 2] = commands[i].vz;
                v_count++;
            } else if (commands[i].type == COMMAND_VN) {
                attrib.normals[3 * n_count + 0] = commands[i].nx;
                attrib.normals[3 * n_count + 1] = commands[i].ny;
                attrib.normals[3 * n_count + 2] = commands[i].nz;
                n_count++;
            } else if (commands[i].type == COMMAND_VT) {
                attrib.texcoords[2 * t_count + 0] = commands[i].tx;
                attrib.texcoords[2 * t_count + 1] = commands[i].ty;
                t_count++;
            } else if (commands[i].type == COMMAND_F) {
                size_t k = 0;
                for (k = 0; k < commands[i].num_f; k++) {
                    obj_vertex_index_t vi = commands[i].f[k];
                    int v_idx = fixIndex(vi.v_idx, v_count);
                    int vn_idx = fixIndex(vi.vn_idx, n_count);
                    int vt_idx = fixIndex(vi.vt_idx, t_count);
                    attrib.faces[f_count + k].v_idx = v_idx;
                    attrib.faces[f_count + k].vn_idx = vn_idx;
                    attrib.faces[f_count + k].vt_idx = vt_idx;
                }

                for (k = 0; k < commands[i].num_f_num_verts; k++) {
                    attrib.face_num_verts[face_count + k] = commands[i].f_num_verts[k];
                }

                f_count += commands[i].num_f;
                face_count += commands[i].num_f_num_verts;
            }
        }
    }

    /* 5. Construct shape information. */
    {
        unsigned int face_count = 0;
        size_t i = 0;
        size_t n = 0;
        size_t shape_idx = 0;

        const char *shape_name = NULL;
        unsigned int shape_name_len = 0;
        const char *prev_shape_name = NULL;
        unsigned int prev_shape_name_len = 0;
        unsigned int prev_shape_face_offset = 0;
        unsigned int prev_face_offset = 0;
        obj_shape_t prev_shape = {NULL, 0, 0};

        /* Find the number of shapes in .obj */
        for (i = 0; i < num_lines; i++) {
            if (commands[i].type == COMMAND_O || commands[i].type == COMMAND_G) {
                n++;
            }
        }

        /* Allocate array of shapes with maximum possible size(+1 for unnamed
         * group/object).
         * Actual # of shapes found in .obj is determined in the later */
        (*shapes) = (obj_shape_t*)OBJ_MALLOC(sizeof(obj_shape_t) * (n + 1));

        for (i = 0; i < num_lines; i++) {
            if (commands[i].type == COMMAND_O || commands[i].type == COMMAND_G) {
                if (commands[i].type == COMMAND_O) {
                    shape_name = commands[i].object_name;
                    shape_name_len = commands[i].object_name_len;
                } else {
                    shape_name = commands[i].group_name;
                    shape_name_len = commands[i].group_name_len;
                }

                if (face_count == 0) {
                    /* 'o' or 'g' appears before any 'f' */
                    prev_shape_name = shape_name;
                    prev_shape_name_len = shape_name_len;
                    prev_shape_face_offset = face_count;
                    prev_face_offset = face_count;
                } else {
                    if (shape_idx == 0) {
                        /* 'o' or 'g' after some 'v' lines. */
                        (*shapes)[shape_idx].name = my_strndup(
                                prev_shape_name, prev_shape_name_len); /* may be NULL */
                        (*shapes)[shape_idx].face_offset = prev_shape.face_offset;
                        (*shapes)[shape_idx].length = face_count - prev_face_offset;
                        shape_idx++;

                        prev_face_offset = face_count;

                    } else {
                        if ((face_count - prev_face_offset) > 0) {
                            (*shapes)[shape_idx].name =
                                my_strndup(prev_shape_name, prev_shape_name_len);
                            (*shapes)[shape_idx].face_offset = prev_face_offset;
                            (*shapes)[shape_idx].length = face_count - prev_face_offset;
                            shape_idx++;
                            prev_face_offset = face_count;
                        }
                    }

                    /* Record shape info for succeeding 'o' or 'g' command. */
                    prev_shape_name = shape_name;
                    prev_shape_name_len = shape_name_len;
                    prev_shape_face_offset = face_count;
                }
            }
            if (commands[i].type == COMMAND_F) {
                face_count++;
            }
        }

        if ((face_count - prev_face_offset) > 0) {
            size_t length = face_count - prev_shape_face_offset;
            if (length > 0) {
                (*shapes)[shape_idx].name =
                    my_strndup(prev_shape_name, prev_shape_name_len);
                (*shapes)[shape_idx].face_offset = prev_face_offset;
                (*shapes)[shape_idx].length = face_count - prev_face_offset;
                shape_idx++;
            }
        } else {
            /* Guess no 'v' line occurrence after 'o' or 'g', so discards current
             * shape information. */
        }

        (*num_shapes) = shape_idx;
    }

    if (commands) {
        OBJ_FREE(commands);
    }

    return OBJ_SUCCESS;
}

void obj_attrib_init(obj_attrib_t &attrib) {
    attrib.vertices = NULL;
    attrib.num_vertices = 0;
    attrib.normals = NULL;
    attrib.num_normals = 0;
    attrib.texcoords = NULL;
    attrib.num_texcoords = 0;
    attrib.faces = NULL;
    attrib.num_faces = 0;
    attrib.face_num_verts = NULL;
    attrib.num_face_num_verts = 0;
}

void obj_attrib_free(obj_attrib_t &attrib) {
    if (attrib.vertices) OBJ_FREE(attrib.vertices);
    if (attrib.normals) OBJ_FREE(attrib.normals);
    if (attrib.texcoords) OBJ_FREE(attrib.texcoords);
    if (attrib.faces) OBJ_FREE(attrib.faces);
    if (attrib.face_num_verts) OBJ_FREE(attrib.face_num_verts);
}

void obj_shapes_free(obj_shape_t *shapes, size_t num_shapes) {
    size_t i;
    if (shapes == NULL) return;

    for (i = 0; i < num_shapes; i++) {
        if (shapes[i].name) OBJ_FREE(shapes[i].name);
    }

    OBJ_FREE(shapes);
}

static char* mmap_file(size_t* len, const char* filename) {
  FILE* f;
  long file_size;
  char* p;
  int fd;

  (*len) = 0;

  f = fopen(filename, "r");
  if (!f) {
    perror("open");
    return NULL;
  }
  fseek(f, 0, SEEK_END);
  file_size = ftell(f);
  fclose(f);


  p = (char*)mmap(0, (size_t)file_size, PROT_READ, MAP_SHARED, fd, 0);

  if (p == MAP_FAILED) {
    perror("mmap");
    return NULL;
  }


  (*len) = (size_t)file_size;

  return p;

}

static char* get_dirname(char* path) {
  char* last_delim = NULL;

  if (path == NULL) {
    return path;
  }

#if defined(_WIN32)
  /* TODO: Unix style path */
  last_delim = strrchr(path, '\\');
#else
  last_delim = strrchr(path, '/');
#endif

  if (last_delim == NULL) {
    /* no delimiter in the string. */
    return path;
  }

  /* remove '/' */
  last_delim[0] = '\0';

  return path;
}

static void getFileData(void *ctx, const char *filename,
        const char *obj_filename, char **data, size_t *len) {

    (void) ctx;

    if (!filename) {
        std::cout << ERR_FLAG << "no filename\n";
        (*data) = NULL;
        (*len) = 0;
        return;
    }

    const char *ext = strrchr(filename, '.');

    size_t data_len = 0;

    char *basedirname = NULL;

    char tmp[1024];

    tmp[0] = '\0';

    strncat(tmp, filename, 1023 - strlen(tmp));
    tmp[strlen(tmp)] = '\0';

    printf("tmp = %s\n", tmp);

    if (basedirname) {
        free(basedirname);
    }


    *data = mmap_file(&data_len, tmp);


    (*len) = data_len;
}


int parse_obj() {
  int rc = obj_parse_obj(obj_attrib_t &attrib, obj_shape_t **shapes, size_t *num_shapes, const char *obj_filename, file_reader_callback file_reader, void *ctx, unsigned int flags)
  
}

#endif /* TINOBJ_LOADER_C_H_ */

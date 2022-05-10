// this module is for a string sequence ADT

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

struct sequence {
  int len;
  int maxlen;
  char **data;
};

// see sequence.h for documentation
struct sequence *sequence_create(void) {
  struct sequence *s = malloc(sizeof(struct sequence));
  s->len = 0;
  s->maxlen = 1;
  s->data = malloc(s->maxlen * sizeof(char *));
  return s;
}

// see sequence.h for documentation
void sequence_destroy(struct sequence *seq) {
  assert(seq);

  for (int i = 0; i < seq->len; i++) {
    free(seq->data[i]);
  }

  free(seq->data);
  free(seq);
}

// see sequence.h for documentation
int sequence_length(const struct sequence *seq) {
  assert(seq);
  return seq->len;
}

// see sequence.h for documentation
const char *sequence_item_at(const struct sequence *seq, int pos) {
  assert(seq);
  assert(pos >= 0);
  assert(pos < seq->len);
  return seq->data[pos];
}

// see sequence.h for documentation
void sequence_insert_at(struct sequence *seq, int pos, const char *s) {
  assert(seq);
  assert(s);
  assert(pos >= 0);
  assert(pos <= seq->len);

  seq->data = realloc(seq->data, (seq->len + 1) * sizeof(char *));


  char *prev_str = seq->data[pos];
  int str_len = strlen(s);
  char *temp_str = malloc((str_len + 1) * sizeof(char));
  for (int i = 0; i < str_len; i++) {
    temp_str[i] = s[i];
  }
  temp_str[str_len] = 0;
  seq->data[pos] = temp_str;
  seq->len += 1;

  for (int i = pos + 1; i < seq->len; i++) {
    char *temp = seq->data[i];
    seq->data[i] = prev_str;
    prev_str = temp;
  }
}

// see sequence.h for documentation
void sequence_remove_at(struct sequence *seq, int pos) {
  assert(seq);
  assert(pos >= 0);
  assert(pos < seq->len);
  free(seq->data[pos]);
  for (int i = pos; i < seq->len - 1; i++) {
    seq->data[i] = seq->data[i + 1];
  }
  seq->len -= 1;
}

// see sequence.h for documentation
bool sequence_equiv(const struct sequence *seq1, const struct sequence *seq2) {
  assert(seq1);
  assert(seq2);
  if (seq1->len != seq2->len) {
    return false;
  }
  for (int i = 0; i < seq1->len; i++) {
    int comp = strcmp(seq1->data[i], seq2->data[i]);
    if (comp != 0) {
      return false;
    }
  }
  return true;
}

// see sequence.h for documentation
void sequence_print(const struct sequence *seq) {
  assert(seq);
  printf("[");
  if (seq->len == 0) {
    printf("empty]\n");
    return;
  }
  for (int i = 0; i < seq->len; i++) {
    int str_len = strlen(seq->data[i]);
    for (int j = 0; j < str_len; j++) {
      printf("%c", seq->data[i][j]);
    }
    if (i == seq->len - 1) {
      printf("]\n");
    } else {
      printf(",");
    }
  }
}

// see sequence.h for documentation
void sequence_filter(struct sequence *seq, bool (*f)(const char *)) {
  assert(seq);
  assert(f);
  char **temp = malloc(seq->len * sizeof(char *));
  int pos = 0;
  for (int i = 0; i < seq->len; i++) {
    bool keep = f(seq->data[i]);
    if (keep) {
      temp[pos] = seq->data[i];
      pos++;
    } else {
      free(seq->data[i]);
    }
  }
  seq->len = pos;
  for (int i = 0; i < pos; i++) {
    seq->data[i] = temp[i];
  }
  free(temp);
}

// see sequence.h for documentation
void sequence_append(struct sequence *seq1, const struct sequence *seq2) {
  assert(seq1);
  assert(seq2);
  assert(seq1 != seq2);
  seq1->data = realloc(seq1->data, (seq1->len + seq2->len) * sizeof(char *));
  int len = seq1->len;
  seq1->len += seq2->len;
  for (int i = len; i < seq1->len; i++) {
    int str_len = strlen(seq2->data[i - len]);
    seq1->data[i] = malloc((str_len + 1) * sizeof(char));
    strcpy(seq1->data[i], seq2->data[i - len]);
  }
}

// see sequence.h for documentation
void sequence_remove_dups(struct sequence *seq) {
  assert(seq);
  char **temp = malloc(seq->len * sizeof(char *));
  int temp_len = 0;
  bool contain = false;
  for (int i = 0; i < seq->len; i++) {    
    for (int j = 0; j < temp_len; j++) {
      int same = strcmp(seq->data[i], temp[j]);
      if (same == 0) {
        contain = true;
        break;
      }
    }
    if (!contain) {
      temp[temp_len] = seq->data[i];
      temp_len++;
    } else {
      free(seq->data[i]);
    }
    contain = false;
  }

  seq->len = temp_len;
  seq->data = realloc(seq->data, temp_len * sizeof(char *));
  for (int i = 0; i < temp_len; i++) {
    seq->data[i] = temp[i];
  }
  free(temp);
}




#include <stdbool.h>

struct sequence;

// sequence_create() returns a pointer to a new (empty) sequence
// effects: allocates memory (caller must call sequence_destroy)
// time: O(1)
struct sequence *sequence_create(void);

// sequence_destroy(seq) frees all dynamically allocated memory 
// effects: the memory at seq is invalid (freed)
// time: O(n)
void sequence_destroy(struct sequence *seq);

// sequence_length(seq) returns the number of items in seq
// time: O(1)
int sequence_length(const struct sequence *seq);

// sequence_item_at(seq, pos) returns the item in seq at the given pos
// requires: 0 <= pos < length(seq)
// time: O(1)
const char *sequence_item_at(const struct sequence *seq, int pos);

// sequence_insert_at(seq, pos, s) inserts a new item with copy of
//   string s at position pos in seq
//   (changing the position of items at position >= pos)
// requires: and 0 <= pos <= length(seq)
// effects: seq is modified
// time: O(n + m) where n is the length of the sequence and 
//       m is the length of the string to be added
void sequence_insert_at(struct sequence *seq, int pos, const char *s);

// sequence_remove_at(seq, pos) removes the item at position pos in seq
//   (changing the position of items > pos)
// requires: 0 <= pos < length(seq)
// effects: seq is modified
// time: O(n)
void sequence_remove_at(struct sequence *seq, int pos);

// sequence_equiv(seq1, seq2) determines if seq1 and seq2 are equivalent
//   (they both have the same length and have identical sequences of items)
// time: O(n * m)
bool sequence_equiv(const struct sequence *seq1, const struct sequence *seq2);

// sequence_print(seq) prints out the items in seq
//   using the format: "[item_0,item_1,...,item_last]\n"
//   or "[empty]\n"
// effects: prints out a message
// time: O(n * m)
void sequence_print(const struct sequence *seq);

// sequence_filter(seq, f) removes all items i where f(i) is false
// effects: modifies seq
// time: O(n) * O(f(i))
void sequence_filter(struct sequence *seq, bool (*f)(const char *));

// sequence_append(seq1, seq2) appends a copy of all strings from seq2 to 
//   the end of seq1
// requires: seq1 and seq2 are different sequences
// effects: seq1 is modified
// time: O(n + k * m)
void sequence_append(struct sequence *seq1, const struct sequence *seq2);

// sequence_remove_dups(seq) removes all duplicates from seq
//   (keeping each first occurrence)
// examples: ["hi","again","world"] => ["hi","again","world"]
//           ["hi","hi","again","hi","world"] => ["hi","again","world"]
// effects: modifies seq
// time: O(n^2 * m)
void sequence_remove_dups(struct sequence *seq);

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>


/* config options */
// 35:34 70.53394543552517726000 (74815+328)
// F = 72.41617516783679877300 | BYTE = 31 | BIT = 34 | FS_SS = 74256
// F = 72.42151818483503997400 | BYTE = 31 | BIT = 34 | FS_SS = 74390
// F = 72.42685009158710008950 | BYTE = 33 | BIT = 34 | FS_SS = 74384
// F = 72.43061575073074254600 | BYTE = 33 | BIT = 34 | FS_SS = 74383
// F = 72.44105740145352693850 | BYTE = 37 | BIT = 38 | FS_SS = 74096
// F = 72.44057601459281208450 | BYTE = 33 | BIT = 34 | FS_SS = 74362 [5,13]
// 31..37

int MULTIPLIER_BYTE = 33;
int MULTIPLIER_BIT 	= 34;
int MAX_DB_SIZE		= 74383 + 345;
int MAX_JS_SIZE		= 345;
int FILTER_SIZE		= 0;
int FILTER_SIZE_MAX	= 100000;

#define WORD_BUF_SIZE	150
#define IF_CNT 			if (5 <= len && len <= 13)
#define ELSE_CNT 		else result = 0; // in_rnd(len);

/* helper functions */
void err(char *msg, ...);
void init_filter(unsigned char []);
void load_words(unsigned char [], char *);
void insert_word(unsigned char [], char *);
void testing_words(unsigned char [], char *, char *);
int in_dict(unsigned char [], char *);
int in_rnd(int);
void save2bin_file(unsigned char filter[], char *);
int is_corrcet_len(unsigned int);
int is_correct_quote(char []);

unsigned int hash_byte(char *);
unsigned int hash_bit(char *);
void set_bit(unsigned char *byte, int bit);
int get_bit(unsigned char byte, int bit);
void show_bits(unsigned char[]);


int main(int argc, char *argv[])
{
	srand((unsigned)time(NULL));
	unsigned char filter[FILTER_SIZE_MAX];

	if (argc == 1)
		err("usage:\n"
		"  ./prog -hash some_word\n"
		"  ./prog -m_byte 3 -m_bit 12 -hash some_word\n"
		"  ./prog -d_file dict.txt -tr_files test.txt result.txt\n"
		"  ./prog -d_file dict.txt -tr_files test.txt result.txt -b_file data.bin\n"
		"  ./prog -show_options\n"
		);

	FILTER_SIZE = MAX_DB_SIZE - MAX_JS_SIZE;

	init_filter(filter);

	int i;
	for (i = 0; i < argc; i++) {
		if (!strcmp(argv[i], "-m_byte")) {
			MULTIPLIER_BYTE = atoi(argv[i + 1]);
		}

		if (!strcmp(argv[i], "-m_bit")) {
			MULTIPLIER_BIT = atoi(argv[i + 1]);
		}

		if (!strcmp(argv[i], "-max_db")) {
			MAX_DB_SIZE = atoi(argv[i + 1]);
			FILTER_SIZE = MAX_DB_SIZE - MAX_JS_SIZE;
		}

		if (!strcmp(argv[i], "-max_js")) {
			MAX_JS_SIZE = atoi(argv[i + 1]);
			FILTER_SIZE = MAX_DB_SIZE - MAX_JS_SIZE;
		}

		if (!strcmp(argv[i], "-filter_size")) {
			FILTER_SIZE = atoi(argv[i + 1]);
		}

		if (FILTER_SIZE <= 0) {
			err("FILTER_SIZE must be > 0\n");
		}

		if (!strcmp(argv[i], "-hash")) {
			unsigned int byte = hash_byte(argv[i + 1]);
			unsigned int bit = hash_bit(argv[i + 1]);
			printf("%s:%d:%d\n", argv[i + 1], byte, bit);
		}

		// dictionary file
		if (!strcmp(argv[i], "-d_file")) {
			load_words(filter, argv[i + 1]);
		}

		// test file, result file
		if (!strcmp(argv[i], "-tr_files")) {
			testing_words(filter, argv[i + 1], argv[i + 2]);
		}

		// binary file
		if (!strcmp(argv[i], "-b_file")) {
			save2bin_file(filter, argv[i + 1]);
		}

		if (!strcmp(argv[i], "-show_options")) {
			printf("MAX_DB_SIZE     = %d;\n", MAX_DB_SIZE);
			printf("MAX_JS_SIZE     = %d;\n", MAX_JS_SIZE);
			printf("FILTER_SIZE     = %d;\n", FILTER_SIZE);
			printf("MULTIPLIER_BYTE = %d;\n", MULTIPLIER_BYTE);
			printf("MULTIPLIER_BIT  = %d;\n", MULTIPLIER_BIT);
		}
	}

	return 0;
}

void err(char *msg, ...)
{
	va_list args;
	va_start(args, msg);
	vfprintf(stderr, msg, args);
	va_end(args);
	exit(-1);
}

void init_filter(unsigned char filter[])
{
	unsigned int i;

	for (i = 0; i < FILTER_SIZE_MAX; i++) {
		filter[i] = 0;
	}
}

void load_words(unsigned char filter[], char *filename)
{
	FILE *fp = fopen(filename, "r");
	char word[WORD_BUF_SIZE + 1];

	if (!fp) {
		err("[e] %s: can't open file \"%s\"\n", __FUNCTION__, filename);
	}

	while (fgets(word, WORD_BUF_SIZE, (FILE *) fp)) {
		int len = strlen(word);

		if (len == WORD_BUF_SIZE - 1) {
			err("[e] WORD_BUF_SIZE is small\n");
		}

		word[strcspn(word, "\n")] = 0;
		len--;

		IF_CNT
			insert_word(filter, word);
	}

	fclose(fp);
}

void insert_word(unsigned char filter[], char *word)
{
	if (!word) {
		err("[e] word is NULL");
	}

	unsigned int byte = hash_byte(word);
	unsigned int bit = hash_bit(word);

	set_bit(&filter[byte], bit);
}

void testing_words(unsigned char filter[], char *file_in, char *file_res)
{
	FILE *fi = fopen(file_in, "r");
	FILE *fr = fopen(file_res, "w");

	char word[WORD_BUF_SIZE + 1];

	if (!fi) {
		err("[e] %s: can't open file \"%s\"\n", __FUNCTION__, file_in);
	}

	if (!fr) {
		err("[e] %s: can't open file \"%s\"\n", __FUNCTION__, file_res);
	}

	while (fgets(word, WORD_BUF_SIZE, (FILE *) fi)) {
		int len = strlen(word);

		if (len == WORD_BUF_SIZE - 1) {
			err("[e] WORD_BUF_SIZE is small\n");
		}

		word[strcspn(word, "\n")] = 0;
		len--;

		int result = 0;
		if (is_corrcet_len(len) && is_correct_quote(word)) {
			if (len == 1)
				result = 1;
			else {
				IF_CNT {
					result = in_dict(filter, word);
				}
				ELSE_CNT
			}
		}

		if (result) {
			fprintf(fr, "\"%s\": \"true\"\n", word);
		} else {
			fprintf(fr, "\"%s\": \"false\"\n", word);
		}
	}

	fclose(fi);
	fclose(fr);
}

int in_dict(unsigned char filter[], char *word)
{
	if (!word) {
		err("[e] word is NULL");
	}

	unsigned int byte = hash_byte(word);
	unsigned int bit = hash_bit(word);

	return get_bit(filter[byte], bit);
}

int in_rnd(int len) {
	double arr[] = {
		0.2355889724,
		0.5303571429,
		0.4332809889,
		0.4062591666,
		0.470413852,
		0.543142033,
		0.5907591493,
		0.6215456425,
		0.6315122759,
		0.6041853963,
		0.5763330962,
		0.5384971024,
		0.4891409238,
		0.4333298623,
		0.368964808,
		0.3017000108,
		0.2260091693,
		0.1597245748,
		0.1080629006,
		0.0596169174,
		0.0356754664,
		0.0188164096,
		0.00926039,
		0.0060242354,
		0.0030079087,
		0.0006392747,
		0.0009884889,
		0.0007864164,
		0.0018979834,
		0.0007696138,
		0.002919708,
		0.0020509315,
		0.0015308075,
		0.0013565453
	};

	double r = 0;
	int cnt = (int) (sizeof(arr) / sizeof(double));

	if (len < cnt)
		r = arr[len];

	double rnd = ((double) rand() / (double) RAND_MAX);
	//printf("[%e vs %e] = %d\n", r, rnd, (r > rnd));

	return (int) (r > rnd);
}

void save2bin_file(unsigned char filter[], char *filename) {
	FILE *fp = fopen(filename, "wb");
	int i;

	if (!fp) {
		err("[e] %s: can't open file \"%s\"\n", __FUNCTION__, filename);
	}

	for (i = 0; i < FILTER_SIZE; i++) {
		fprintf(fp, "%c", filter[i]);
	}

	fclose(fp);
}

int is_corrcet_len(unsigned int len) {
	if (len <= 34 || len == 45 || len == 58 || len == 60) {
		return 1;
	}

	return 0;
}

int is_correct_quote(char word[]) {
	int len = strlen(word);
	if (word[0] == '\'' || word[len - 1] == '\'')
		return 0;

	return 1;
}

unsigned int hash_byte(char *str)
{
	unsigned int h;
	unsigned char *p;

	h = 0;
	for (p = (unsigned char *) str; *p != '\0'; p++) {
		//printf("%c=%d, h = %d\n", *p, *p, h);
		h = MULTIPLIER_BYTE * h + *p;
		h %= FILTER_SIZE;
	}

	return h;
}

unsigned int hash_bit(char *str)
{
	unsigned int h;
	unsigned char *p;

	h = 0;
	for (p = (unsigned char *) str; *p != '\0'; p++) {
		h = MULTIPLIER_BIT * h + *p;
		h %= 8;
	}

	return h;
}

void set_bit(unsigned char *byte, int bit)
{
	*byte |= (1 << bit);

	return;
}

int get_bit(unsigned char byte, int bit)
{
	byte &= (1 << bit);

	return byte ? 1 : 0;
}

void show_bits(unsigned char filter[]) {
	unsigned int i;

	for (i = 0; i < FILTER_SIZE; i++)
		printf("0x%02x\n", filter[i]);
}
